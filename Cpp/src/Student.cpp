#include "Student.h"
#include <stdexcept>
#include <utility>

Student::Student(int id, std::string name, int age, 
                  std::optional<std::string> email)
                 : id_(id), name_(std::move(name)), age_(age),
                   email_(std::move(email)) 
{
    validateName(name_);
    validateAge(age_);

}

Student::Student(std::string name, int age,
                 std::optional<std::string> email)
                 : Student(0, std::move(name), age, std::move(email))
                 {

                 }

int Student::id() const noexcept 
{
    return id_;
}

const std::string& Student::name() const noexcept
{
    return name_;
}

int Student::age() const noexcept
{
    return age_;
}

const std::optional<std::string>& Student::email() const noexcept
{
    return email_;
}

void Student::setName(std::string name) 
{
    validateName(name);
    name_ = std::move(name);
}

void Student::setAge(int age)
{
    validateAge(age);
    age_ = age;
}

void Student::setEmail(std::optional<std::string> email)
{
    email_ = std::move(email);
}

void Student::validateName(const std::string& name) 
{
    if(name.empty()) throw std::invalid_argument("이름은 필수 입니다.");
}

void Student::validateAge(int age)
{
    if(age < 0) throw std::invalid_argument("나이는 0 이사이어야 합니다.");
    
}




