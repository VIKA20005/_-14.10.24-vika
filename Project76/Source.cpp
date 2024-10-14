#include <iostream>
#include <initializer_list>

class MyString 
{
private:
    char* str;
    size_t size;

public:
    
    MyString() : str(nullptr), size(0) {}

    
    MyString(std::initializer_list<char> initList) 
    {
        size = initList.size();
        str = new char[size + 1];
        size_t i = 0;
        for (char c : initList) 
        {
            str[i++] = c;
        }
        str[size] = '\0';
    }

    
    MyString(MyString&& other) noexcept : str(other.str), size(other.size) 
    {
        other.str = nullptr;
        other.size = 0;
    }

    
    MyString& operator=(MyString&& other) noexcept 
    {
        if (this != &other) {
            delete[] str;
            str = other.str;
            size = other.size;
            other.str = nullptr;
            other.size = 0;
        }
        return *this;
    }

    
    ~MyString() 
    {
        delete[] str;
    }

    
    void print() const 
    {
        if (str) 
        {
            std::cout << str << std::endl;
        }
        else 
        {
            std::cout << "Empty string" << std::endl;
        }
    }
};

int main() 
{
   
    MyString obj{ 'H', 'e', 'l', 'l', 'o' };
    obj.print();  

    
    MyString obj2 = std::move(obj);
    obj2.print(); 
    obj.print(); 

    
    MyString obj3;
    obj3 = std::move(obj2);
    obj3.print(); 
    obj2.print(); 

    return 0;
}