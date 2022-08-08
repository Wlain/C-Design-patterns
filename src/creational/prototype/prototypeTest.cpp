//
// Created by cwb on 2022/8/8.
//
#include <iostream>
#include <memory>
#include <string>
namespace
{
struct Office
{
    std::string m_street;
    std::string m_city;
    int32_t m_cubical;
};

struct EmployeeBad
{
    std::string m_name;
    Office m_office;
    EmployeeBad(std::string n, Office o) :
        m_name(n), m_office(o) {}
};

} // namespace

// 此时，必须为每个员工的详细信息一次又一次地写下主要办公室地址
void withoutPrototype()
{
    EmployeeBad john{ "William", Office{ "123 East Dr", "London", 123 } };
    EmployeeBad jane{ "William", Office{ "123 East Dr", "London", 124 } };
    EmployeeBad jack{ "William", Office{ "123 ORR", "Bangaluru", 300 } };
}

struct Employee
{
    std::string m_name;
    const Office* m_office;
    Employee(std::string n, Office* o) :
        m_name(n), m_office(o) {}
};

static Office LondonOffice{ "123 East Dr", "London", 123 };
static Office BangaluruOffice{ "RMZ Ecoworld ORR", "London", 123 };

void withPrototype()
{
    Employee john{ "William", &LondonOffice };
    Employee jane{ "William", &LondonOffice };
    Employee jack{ "Jack", &BangaluruOffice };
}

// prototype Factory

class EmployeeGood
{
public:
    EmployeeGood(const EmployeeGood& e) :
        m_name(e.m_name), m_office(new Office{ *e.m_office })
    {
    }
    EmployeeGood& operator=(const EmployeeGood& e)
    {
        if (&e == this)
            return *this;
        m_name = e.m_name;
        m_office = new Office{ *e.m_office };
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const EmployeeGood& o)
    {
        return os << o.m_name << " works at "
                  << o.m_office->m_street << " " << o.m_office->m_city << " seats @"
                  << o.m_office->m_cubical << std::endl;
    }

private:
    EmployeeGood(std::string n, Office* o) :
        m_name(n), m_office(o) {}

private:
    std::string m_name;
    Office* m_office;
    friend class EmployeeFactory;
};

class EmployeeFactory
{
public:
    static std::unique_ptr<EmployeeGood> newMainOfficeEmployee(std::string name, int32_t cubical)
    {
        return newEmployee(name, cubical, m_main);
    }
    static std::unique_ptr<EmployeeGood> newAuxOfficeEmployee(std::string name, int32_t cubical)
    {
        return newEmployee(name, cubical, m_aux);
    }

private:
    static std::unique_ptr<EmployeeGood> newEmployee(std::string name, int32_t cubical, EmployeeGood& proto)
    {
        auto e = std::make_unique<EmployeeGood>(proto);
        e->m_name = name;
        e->m_office->m_cubical = cubical;
        return e;
    }

private:
    inline static EmployeeGood m_main{ "", new Office{ "123 East Dr", "London", 123 } };
    inline static EmployeeGood m_aux{ "", new Office{ "RMZ Ecoworld ORR", "London", 123 } };
};
// 原型设计模式也可用于在不知道对象具体类型的情况下创建对象的副本

namespace
{
// 问题：
// C++支持使用其基类的虚析构函数进行多态对象破坏。
// 除非知道对象的静态类型，否则无法创建对象，因为编译器必须知道它需要分配的内存
//
struct AnimalBad
{
    virtual ~AnimalBad() { std::cout << "~AnimalBad\n"; }
};
struct DogBad : AnimalBad
{
    ~DogBad() override { std::cout << "~dog\n"; }
};
struct CatBad : AnimalBad
{
    ~CatBad() override { std::cout << "~cat\n"; }
};

void whoAmI(AnimalBad* who)
{
    delete who;
}

// 解决方案
// Virtual Constructor/Copy-Constructor 技术通过使用虚方法将创建和复制对象的行为委托给派生类，从而允许在 C++ 中多态地创建和复制对象
// 以下代码不仅实现虚复制构造函数（clone()），还实现了虚构造函数（create()）
struct Animal
{
    virtual ~Animal() = default;
    virtual std::unique_ptr<Animal> create() = 0;
    virtual std::unique_ptr<Animal> clone() = 0;
};

struct Dog : public Animal
{
    ~Dog() override = default;
    std::unique_ptr<Animal> create() override
    {
        return std::make_unique<Dog>();
    }
    std::unique_ptr<Animal> clone() override
    {
        return std::make_unique<Dog>(*this);
    }
};

struct Cat : public Animal
{
    ~Cat() override = default;
    std::unique_ptr<Animal> create() override
    {
        return std::make_unique<Cat>();
    }
    std::unique_ptr<Animal> clone() override
    {
        return std::make_unique<Cat>(*this);
    }
};

void whoAmIGood(Animal* who)
{
    auto newWho = who->create();
    auto duplicateWho = who->clone();
    delete who;
}

} // namespace

void prototypeTest()
{
    withoutPrototype();
    withPrototype();
    auto jane = EmployeeFactory::newMainOfficeEmployee("William", 125);
    auto jack = EmployeeFactory::newAuxOfficeEmployee("Jack", 123);
    std::cout << *jane << std::endl
              << *jack << std::endl;
}