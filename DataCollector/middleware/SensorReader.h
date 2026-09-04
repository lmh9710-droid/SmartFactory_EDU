#pragma once
#include <string>
#include <windows.h>
#include "DatabaseManager.h"

/* 1. 최상위 기본 센서 리더 (공통 시리얼 로직 포함) */
class SensorReader {
 
 protected:
    HANDLE hSerial;
    std::string port_name;
    int baud_rate;
    DatabaseManager& db_manager; /* 자식 DB 매니저들을 부모형태로 안전하게 참조받음 */

 public:
    SensorReader(std::string port, int baud, DatabaseManager& db);
    virtual ~SensorReader();
    
    bool open_port();
    void start_listening();
    void close_port();
    
    /* 자식 클래스들이 데이터 수신 시 화면 출력이나 전처리를 다르게 하도록 가상함수 정의 */
    virtual void handle_received_line(std::string line) = 0;
};

/* 2. [자식] 온습도 전용 리더 (COM11용) */
class DHTReader : public SensorReader {
  public:
    DHTReader(std::string port, int baud, DatabaseManager& db);
    void handle_received_line(std::string line) override;
};

/* 3. [자식] 광도 전용 리더 (COM12용) */
class LightReader : public SensorReader {
  public:
    LightReader(std::string port, int baud, DatabaseManager& db);
    void handle_received_line(std::string line) override;
};
