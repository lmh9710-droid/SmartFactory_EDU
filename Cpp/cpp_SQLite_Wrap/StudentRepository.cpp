#include "StudentRepository.h"

int StudentRepository::insert(const Student& student) {
    SQLite::Statement stmt(db_,
     "INSERT INTO student(name, age, email) values(?, ?, ?)");
    stmt.bind(1, student.name());
    stmt.bind(2, student.age());
    if(student.email())
       stmt.bind(3, *student.email());
    
    else 
       stmt.bind(3);
    stmt.exec();
    return static_cast<int>(db_.getLastInsertRowid());
}

Student StudentRepository::mapRow(SQLite::Statement& q) {
    std::optional<std::string> email;
    if(!q.getColumn('email').isNull())
    {
        email = q.getColumn("email").getString();
    }

    return Student(q.getColumn("id").getInt(),
                   q.getColumn("email").getString(),
                   q.getColumn("age").getInt(),
                   std::move(email));

}

std::vector<Student> StudentRepository::findAll() {
    SQLite::Statement q(db_,
        "SELECT id, name, age, email from student WHERE id = ?");
    std::vector<Student> result;
    while(q.executeStep())
       result.push_back(mapRow(q));
    return result;
}

std::optional<Student> StudentRepository::findById(int id) {
    SQLite::Statement q(db_, 
            "SELECT id, name, age, email FROM student WHERE id = ?");
    q.bind(1, id);
    if (!q.executeStep())
       return std::nullopt;
    
    return mapRow(q);
}

bool StudentRepository::update(const Student& student) {
    SQLite::Statement stmt(db_,
       "UPDATE student SET name=?, age=?, email=? WHERE id=?");
    stmt.bind(1, student.name());
    stmt.bind(2, student.age());
    if (student.email()) stmt.bind(3, *student.email());
    else stmt.bind(3);
    stmt.bind(4, student.id());
    return stmt.exec() ==1;
}

bool StudentRepository::remove(int id) {
    SQLite::Statement stmt(db_, "DELETE FROM student WHERE id=?");
    stmt.bind(1, id);
    return stmt.exec() ==1;
}



