#include <iostream>
#include <string>

class Person {
private:
    std::string name;
    int age;

public:
    // سازنده برای مقداردهی اولیه
    Person(const std::string& n, int a) : name(n), age(a) {}

    // متد برای دریافت نام
    std::string getName() const {
        return name;
    }

    // متد برای دریافت سن
    int getAge() const {
        return age;
    }

    // متد برای چاپ اطلاعات شخص
    void printInfo() const {
        std::cout << "Name: " << name << std::endl;
        std::cout << "Age: " << age << std::endl;
    }
};

int main() {
    // ایجاد یک شیء از کلاس Person
    Person p("Saba", 33);
    
    // چاپ اطلاعات با استفاده از متد printInfo
    p.printInfo();
    
    // همچنین می‌توانیم اطلاعات را به صورت جداگانه چاپ کنیم
    // std::cout << "Name: " << p.getName() << std::endl;
    // std::cout << "Age: " << p.getAge() << std::endl;

    return 0;
}

