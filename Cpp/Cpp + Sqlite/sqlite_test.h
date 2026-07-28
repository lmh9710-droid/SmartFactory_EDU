#pragma once
#include <iostream>
#include <sqlite3.h>

class DataBase
{
    public:
     
     DataBase(const char* db_name, sqlite3* db);
    
     void Create_DB();
     void Insert_DB();
     void Select_DB();
     void Update_DB();
     void Delete_DB();

     std::string get_DBNAME() const;
    
     ~DataBase();
     private:
     std::string mdb_name; 
     sqlite3* mdb;

};