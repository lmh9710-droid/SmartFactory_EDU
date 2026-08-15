#pragma once

#include "Student.h"
#include <SQLiteCpp/SQLiteCpp.h>
#include <optional>
#include <vector>

class StudentRepository {

    public: 
      explicit StudentRepository(SQLite::Database& db);
     
      int insert(const Student& student);
      std::vector<Student> findAll();
      std::optional<Student> findById(int id);
      bool update(const Student& student);
      bool remove(int id);
    
    private: 
      SQLite::Database& db_;
      static Student mapRow(SQLite::Statement& query);
};