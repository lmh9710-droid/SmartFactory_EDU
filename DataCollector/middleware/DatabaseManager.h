#pragma once
#include <string>
#include <mutex>
#include <sqlite3.h>

extern std::mutex db_mutex;

/* 1. 최상위 기본 데이터베이스 매니저 (추상 클래스) */
class DatabaseManager {
  
  protected:
      sqlite3* db;
      std::string db_name;

  public:
      DatabaseManager(std::string name);
      virtual ~DatabaseManager();
      
      bool open_db();
      void close_db();
      
      // 자식들이 각자 테이블을 만들고 데이터를 넣도록 가상 함수 선언
      virtual bool init_table() = 0;
      virtual void insert_data(std::string port_name, std::string raw_data) = 0;
};

// 2. [자식] 온습도 센서 전용 DB 매니저 (COM11용)
class DHTDatabaseManager : public DatabaseManager {

    public:
        DHTDatabaseManager(std::string name);
        bool init_table() override;
        void insert_data(std::string port_name, std::string raw_data) override; /* 파싱 포함*/ 
};

// 3. [자식] 광도 센서 전용 DB 매니저 (COM12용)
class LightDatabaseManager : public DatabaseManager {

    public:
        LightDatabaseManager(std::string name);
        bool init_table() override;
        void insert_data(std::string port_name, std::string raw_data) override;
};
