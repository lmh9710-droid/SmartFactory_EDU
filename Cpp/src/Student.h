#pragma once 

#include <optional>
#include <string>

class Student {
    public:
       Student(int id, std:: string name, int age,
               std::optional<std::string> email = std::nullopt);
        
       Student(std::string name, int age, 
               std::optional<std::string> email = std::nullopt);
       
       int id() const noexcept;
       const std::string& name() const noexcept;
       int age() const noexcept;
       const std::optional<std::string>& email() const noexcept;

       void setName(std::string name);
       void setAge(int age);
       void setEmail(std::optional<std::string> email);
     
    private:
      int id_{0};
      std::string name_;
      int age_;
      std::optional<std::string> email_;
      
      static void validateName(const std::string& name);
      static void validateAge(int age);
};