#include<iostream>
#include<sstream>
#include<string>

struct Format {
    std::stringstream ss;
    template<typename T>
    Format& operator<<(const T& val) 
    {
        ss << val;
        return *this;
    }

    operator std::string() const
    {
        return ss.str();
    }

};