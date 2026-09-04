#include "DatabaseManager.h"
#include <iostream>
#include <sstream>

std::mutex db_mutex;

/* --- 기본 클래스 구현 --- */
DatabaseManager::DatabaseManager(std::string name) : db(nullptr), db_name(name) {}
DatabaseManager::~DatabaseManager() { close_db(); }

bool DatabaseManager::open_db() {
    if (sqlite3_open(db_name.c_str(), &db) != SQLITE_OK) {
        std::cerr << "[DB 에러] 열기 실패: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    return true;
}
void DatabaseManager::close_db() {
    if (db) { sqlite3_close(db); db = nullptr; }
}

/* --- 온습도 전용 DB 구현 (COM11) --- */
DHTDatabaseManager::DHTDatabaseManager(std::string name) : DatabaseManager(name) {}

bool DHTDatabaseManager::init_table() {
    std::string sql = 
        "CREATE TABLE IF NOT EXISTS dht_logs ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, port_name TEXT, temperature REAL, humidity REAL, created_at DATETIME DEFAULT CURRENT_TIMESTAMP);";
    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "[DHT DB] 테이블 생성 실패: " << errMsg << std::endl;
        sqlite3_free(errMsg); return false;
    }
    std::cout << "[DHT DB] 온습도 테이블 초기화 완료!\n";
    return true;
}

void DHTDatabaseManager::insert_data(std::string port_name, std::string raw_data) {
    std::lock_guard<std::mutex> lock(db_mutex);
    
    /* 콤마(,) 기준 데이터 파싱 로직 (예: "25.50,53.30")*/
    std::stringstream ss(raw_data);
    std::string temp_str, humi_str;
    double temperature = 0.0, humidity = 0.0;

    if (std::getline(ss, temp_str, ',') && std::getline(ss, humi_str, ',')) {
        try {
            temperature = std::stod(temp_str);
            humidity = std::stod(humi_str);
        } catch (...) {
            std::cerr << "[DHT 파싱 에러] 잘못된 데이터 포맷: " << raw_data << std::endl;
            return;
        }
    } else { return; }

    std::string sql = "INSERT INTO dht_logs (port_name, temperature, humidity) VALUES (?, ?, ?);";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, port_name.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_double(stmt, 2, temperature);
        sqlite3_bind_double(stmt, 3, humidity);
        sqlite3_step(stmt);
    }
    sqlite3_finalize(stmt);
}

/* --- 광도 전용 DB 구현 (COM12) --- */
LightDatabaseManager::LightDatabaseManager(std::string name) : DatabaseManager(name) {}

bool LightDatabaseManager::init_table() {
    std::string sql = 
        "CREATE TABLE IF NOT EXISTS light_logs ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, port_name TEXT, lux_value INTEGER, created_at DATETIME DEFAULT CURRENT_TIMESTAMP);";
    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "[Light DB] 테이블 생성 실패: " << errMsg << std::endl;
        sqlite3_free(errMsg); return false;
    }
    std::cout << "[Light DB] 광도 테이블 초기화 완료!\n";
    return true;
}

void LightDatabaseManager::insert_data(std::string port_name, std::string raw_data) {
    std::lock_guard<std::mutex> lock(db_mutex);

    /* 작은따옴표가 붙어 들어오는 경우 제거 (예: "'158'" -> "158") */
    std::string clean_data = "";
    for (char c : raw_data) {
        if (c != '\'') clean_data += c;
    }

    int lux_value = 0;
    try { lux_value = std::stoi(clean_data); } 
    catch (...) { return; }

    std::string sql = "INSERT INTO light_logs (port_name, lux_value) VALUES (?, ?);";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, port_name.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 2, lux_value);
        sqlite3_step(stmt);
    }
    sqlite3_finalize(stmt);
}
