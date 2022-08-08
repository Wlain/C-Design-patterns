//
// Created by cwb on 2022/8/8.
//

#include <iostream>

// 经典适配器模式
namespace
{
struct Point
{
    int32_t m_x;
    virtual void draw()
    {
        std::cout << "Point" << std::endl;
    }
};

struct Point2D : public Point
{
    int32_t m_y;
    void draw() override
    {
        std::cout << "Point2D" << std::endl;
    }
};

void drawPoint(Point& p)
{
    p.draw();
}

struct Line
{
    Point2D m_start;
    Point2D m_end;
    void draw() { std::cout << "Line\n"; }
};

// 模板
template <class T>
struct GenericLineAdapter : Point
{
    T& m_line;
    GenericLineAdapter(T& line) :
        m_line(line) {}
    void draw() { m_line.draw(); }
};

struct LineAdapter : Point
{
    Line& m_line;
    explicit LineAdapter(Line& line) :
        m_line(line) {}
    void draw() override { m_line.draw(); }
};

void withAdapter()
{
    Line l;
    LineAdapter lineAdapter(l);
    drawPoint(lineAdapter);
    LineAdapter lineAdapterTest(l);
    drawPoint(lineAdapter);
}

} // namespace

// 使用现代C++

namespace
{
struct Beverage
{
    virtual void getBeverage() = 0;
};

struct CoffeeMaker : Beverage
{
    void Brew() { std::cout << "brewing coffee" << std::endl; }
    void getBeverage() override { Brew(); }
};

void makeDrink(Beverage& drink)
{
    drink.getBeverage();
}

struct JuiceMaker
{
    void Squeeze() { std::cout << "making Juice" << std::endl; }
};

struct Adapter : public Beverage
{
    std::function<void()> m_request;
    explicit Adapter(CoffeeMaker* cm)
    {
        m_request = [cm]() { cm->Brew(); };
    }

    explicit Adapter(JuiceMaker* jm)
    {
        m_request = [jm]() { jm->Squeeze(); };
    }
    void getBeverage() { m_request(); }
};

void Test()
{
    Adapter adp1(new CoffeeMaker());
    makeDrink(adp1);
    Adapter adp2(new JuiceMaker());
    makeDrink(adp2);
}

} // namespace

void adapterTest()
{
    withAdapter();
    Test();
}