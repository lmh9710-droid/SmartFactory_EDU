#pragma once
#include <iostream>
#include "sqlite_test.h"

class Menu: public DataBase
{
    public:
    Menu(const char* db_name, sqlite3* db) ;
    void Print_Menu() const;
    void Switch_Case();
    ~Menu();

};