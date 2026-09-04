#include "SensorReader.h"
#include <iostream>
#include <thread>

SensorReader::SensorReader(std::string port, int baud, DatabaseManager& db) 
    : hSerial(INVALID_HANDLE_VALUE), port_name(port), baud_rate(baud), db_manager(db) {}

SensorReader::~SensorReader() { close_port(); }

bool SensorReader::open_port() {
    std::string full_port_path = "\\\\.\\" + port_name;
    hSerial = CreateFileA(full_port_path.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hSerial == INVALID_HANDLE_VALUE) return false;

    DCB dcb = {0}; dcb.DCBlength = sizeof(dcb); GetCommState(hSerial, &dcb);
    dcb.BaudRate = baud_rate; dcb.ByteSize = 8; dcb.StopBits = ONESTOPBIT; dcb.Parity = NOPARITY;
    dcb.fDtrControl = DTR_CONTROL_ENABLE; SetCommState(hSerial, &dcb);

    COMMTIMEOUTS timeouts = {0}; timeouts.ReadIntervalTimeout = MAXDWORD;
    timeouts.ReadTotalTimeoutConstant = 1000; SetCommTimeouts(hSerial, &timeouts);
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    return true;
}

void SensorReader::start_listening() {
    if (!open_port()) {
        std::cerr << "[" << port_name << "] 포트 개방 실패!\n"; return;
    }
    std::cout << "[" << port_name << "] 연결성공! 상속형 스레드 루프 시작...\n" << std::flush;

    char byteBuffer; DWORD bytesRead; std::string line_buffer = "";
    while (true) {
        if (ReadFile(hSerial, &byteBuffer, 1, &bytesRead, NULL) && bytesRead > 0) {
            if (byteBuffer == '\n') {
                if (!line_buffer.empty() && line_buffer.back() == '\r') line_buffer.pop_back();
                
                // 💡 다형성 핵심: 자식이 오버라이딩한 함수를 동적으로 호출함
                this->handle_received_line(line_buffer); 
                
                line_buffer.clear();
            } else { line_buffer += byteBuffer; }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void SensorReader::close_port() {
    if (hSerial != INVALID_HANDLE_VALUE) { EscapeCommFunction(hSerial, CLRDTR); CloseHandle(hSerial); hSerial = INVALID_HANDLE_VALUE; }
}

// --- 자식 온습도 리더 구현 ---
DHTReader::DHTReader(std::string port, int baud, DatabaseManager& db) : SensorReader(port, baud, db) {}
void DHTReader::handle_received_line(std::string line) {
    std::cout << "[COM11 온습도 스레드]: " << line << std::endl;
    db_manager.insert_data(port_name, line); // 부모 클래스가 쥐고 있는 자식 DB 호출
}

// --- 자식 광도 리더 구현 ---
LightReader::LightReader(std::string port, int baud, DatabaseManager& db) : SensorReader(port, baud, db) {}
void LightReader::handle_received_line(std::string line) {
    std::cout << "[COM12 광도 스레드]: " << line << std::endl;
    db_manager.insert_data(port_name, line);
}
