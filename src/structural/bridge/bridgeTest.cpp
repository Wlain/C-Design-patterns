//
// Created by william on 2022/8/9.
//
#include <iostream>
// 桥梁设计模式防止笛卡儿积复杂性爆炸
// 问题
struct DrawingAPI1Bad
{};
struct DrawingAPI2Bad
{};

struct ShapeBad
{
    virtual void draw() = 0;
};

struct Circle1Bad : ShapeBad, DrawingAPI1Bad
{};
struct Circle2Bad : ShapeBad, DrawingAPI2Bad
{};
struct Square1Bad : ShapeBad, DrawingAPI1Bad
{};
struct Square2Bad : ShapeBad, DrawingAPI2Bad
{};

// 桥接设计模式的典型实现
struct DrawingAPI
{
    virtual void drawCircle() = 0;
};

struct DrawingAPI1Good : DrawingAPI
{
    void drawCircle() { std::cout << "drawn by API 1" << std::endl; }
};
struct DrawingAPI2Good : DrawingAPI
{
    void drawCircle() { std::cout << "Drawn by API 2" << std::endl; }
};

struct Shape
{
    Shape(DrawingAPI& drawingAPI) :
        m_drawingAPI{ drawingAPI } {}
    virtual void draw() = 0;

protected:
    DrawingAPI& m_drawingAPI; // 此时不需要关心drawingAPI是啥
};

struct Circle : Shape
{
    Circle(DrawingAPI& drawingAPI) :
        Shape{ drawingAPI } {}
    void draw() { m_drawingAPI.drawCircle(); }
};

void test()
{
    DrawingAPI1Good api1;
    DrawingAPI2Good api2;
    Circle(api1).draw();
    Circle(api2).draw();
}
/// 使用PIMPL实现桥模式:PIMPLE 是桥接设计模式的体现
/// 安全和更快的 PIMPL
/// 问题：
/// unique_ptr这会导致一些运行时开销，因为我们必须每次都取消引用指针以进行访问
/// 我们还有构造和销毁开销，unique_ptr因为它在堆中创建了一个内存，其中涉及许多其他函数调用以及系统调用
/// 如果我们想访问内部的数据成员，比如传递指针等，我们还必须支持一些Person间接PersonImpl性this
/// 解决:
// 让我们通过放置新运算符和预先分配的对齐内存缓冲区来解决这个问题
namespace
{
#include <cstddef>
#include <string>
#include <type_traits>
// .h
struct Person
{
    Person();
    ~Person();
    void greet();

private:
    static constexpr size_t m_size = 1024;
    using pimplStorage = std::aligned_storage<m_size, std::alignment_of_v<max_align_t>>::type;
    std::string m_name;
    pimplStorage m_impl;
};
// .cpp
struct PersonImpl
{
    void greet(std::string& name)
    {
        std::cout << "hello " << name << std::endl;
    }
};
Person::Person()
{
    static_assert(sizeof(m_impl) >= sizeof(PersonImpl)); // 编译器安全
    new (&m_impl) PersonImpl;
}

Person::~Person()
{
    reinterpret_cast<PersonImpl*>(&m_impl)->~PersonImpl();
}
void Person::greet()
{
    reinterpret_cast<PersonImpl*>(&m_impl)->greet(m_name);
}
} // namespace

void bridgeTest()
{
    test();
}