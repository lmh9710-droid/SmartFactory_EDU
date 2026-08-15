#include <SQLiteCpp/SQLiteCpp.h>
#include <iostream>
#include "runApplication.hpp"

int main() {


    try {
        SQLite::Database db("student.db", 
                            SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
        runApplication(db);
        return 0;
        } catch(const SQLite::Exception& e) {
        std::cerr << "데이터베이스 오류: "<< e.what() << "\n";
        } catch(const std::exception& e) {
            std::cerr << "오류: " << e.what() <<'\n';
        }
        return 1;
}