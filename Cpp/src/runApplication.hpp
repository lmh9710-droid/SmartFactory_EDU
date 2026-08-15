#include "StudentRepository.h"
#include "printmenu.hpp"
#include <iostream>
#include <string>

Student readStudent()
{    
    std::string name;
    int age; 
    std::string email;
    
    std::cout<< "이름을 입력: ";
    std::cin >> name;

    std::cout<< "나이를 입력 " ;
    std::cin >> age;

    std::cout<< "메일을 입력: ";
    std::cin >> email;
    
    Student student(name, age, email); 

    return student;

}

void registerStudent(StudentRepository& repo) {
    try {
        Student student = readStudent();
        int id = repo.insert(student);
        std::cout << "등록 ID: " << id << "\n";
    } catch (const std::invalid_argument& e) {
        std::cout << "입력 오류: " << e.what() << "\n";
    } catch (const SQLite::Exception& e) {
        std::cerr << "등록 DB 오류" << e.what() << "\n";
    }
}

void findStudent(StudentRepository& repo) {
    try{
       std::vector<Student> students = repo.findAll();
      for (auto iter = students.begin(); iter !=students.end(); ++iter)
      {
         std::string name = iter->email().value_or("미등록");
         std::cout<<"ID: "<< iter->id() << "\t"
                  <<"Name: "<<iter->name() << "\t"
                  <<"age: "<< iter->age() << "\t"
                  <<"email: "<< name <<std::endl;
      }

    } catch (const std::invalid_argument& e) {
       std::cout << "입력 오류: " << e.what() << "\n";
    } catch (const SQLite::Exception& e) {
        std::cerr << "등록 DB 오류" << e.what() << "\n";
    }
}

void modifyStudent(StudentRepository& repo) {
 
    int id;
    std::string name;
    int age;
    std::string email;
    
    std::cout<< "수정할 ID 입력: ";
    std::cin >> id;

    std::cout << "이름 입력: ";
    std::cin >> name;

    std::cout <<"나이 입력: ";
    std::cin >> age;

    std::cout <<"이메일 입력: ";
    std::cin >> email;

    
    Student student(id, name, age, email);
    repo.update(student);

}

void deleteStudent(StudentRepository& repo)
{
    int id;
   
    std::cout<< "삭제할 ID 입력: ";
    std::cin >> id;

    repo.remove(id);
}

void runApplication(SQLite::Database& db)
{
    std::cout << "프로그램을 실행합니다. " << std::endl;
    StudentRepository repo(db);
    printMenu();
 while(true) {
    int choice;
    std::cout << "실행할 번호 선택: "; 
    std::cin >> choice;

    switch(choice){
       case 1:
         registerStudent(repo);
         break;
       case 2:
         findStudent(repo);
         break; 
       case 3:
         modifyStudent(repo);
         break;
       case 4:
         deleteStudent(repo);
         break;
       case 5:
         return;         
       default:
          std::cout<<"번호 에러";  

    }
  } 

}

