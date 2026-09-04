#include <iostream>
#include <thread>
#include "DatabaseManager.h"
#include "SensorReader.h"

#define DB_PATH ("C:\\App\\src\\db\\sensor_data.db")

int main() {
    system("chcp 65001 > nul");
    std::cout << "====== OOP 상속 구조 기반 아두이노 멀티스레드 미들웨어 ======\n";

    /* 1. 각 센서 전용 DB 매니저 자식 객체 생성 및 초기화 */
    DHTDatabaseManager dht_db(DB_PATH);
    LightDatabaseManager light_db(DB_PATH);

    if (!dht_db.open_db() || !dht_db.init_table()) return -1;
    if (!light_db.open_db() || !light_db.init_table()) return -1;

    /* 2. 각 센서 전용 자식 리더 객체 생성 (알맞은 자식 DB 객체를 맵핑 주입) */
    DHTReader dht_reader("COM11", 115200, dht_db);
    LightReader light_reader("COM12", 115200, light_db);

    /* 3. 부모 클래스의 가상 실행 메커니즘을 타겟으로 멀티스레드 실행 */
    std::thread thread1(&SensorReader::start_listening, &dht_reader);
    std::thread thread2(&SensorReader::start_listening, &light_reader);

    /* 4. 메인 스레드 락 유지 */
    thread1.join();
    thread2.join();

    return 0;
}
