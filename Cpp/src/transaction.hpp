#include "StudentRepository.h"

void insertMany(SQLite::Database& db,
                const std::vector<Student>& students)
{
    SQLite::Transaction transaction(db);
    SQLite::Statement insert(db, 
       "INSERT INTO student(name, age, email) VALUES(?, ?, ?)");
    for (const auto& student : students) {
        insert.reset();
        insert.clearBindings();
        insert.bind(1, student.name());
        insert.bind(2, student.age());
        if (student.email())
        {
            insert.bind(3, *student.email());
        }
        else
        {
            insert.bind(3);
        }

        insert.exec();
    }

    transaction.commit();
}

