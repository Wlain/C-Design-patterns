//
// Created by cwb on 2022/8/8.
//
#include <cmath>
#include <iostream>
#include <map>
#include <memory>

// 工厂方法
enum class PointType : u_int8_t
{
    Cartesian, // 笛卡尔坐标系
    Polar      // 极坐标系
};

class Point
{
public:
    friend std::ostream& operator<<(std::ostream& os, const Point& point);
    static Point newCartesian(float x, float y)
    {
        return { x, y, PointType::Cartesian };
    }
    static Point newPolar(float a, float b)
    {
        return { a * std::cos(b), a * std::sin(b), PointType::Polar };
    }

private:
    Point(const float x, const float y, PointType t) :
        m_x{ x }, m_y{ y }, m_type{ t } {}

private:
    float m_x;
    float m_y;
    PointType m_type;
};

std::ostream& operator<<(std::ostream& os, const Point& point)
{
    return os << "{ x: " << point.m_x << " y: " << point.m_y << "}" << std::endl;
}

// 经典工厂设计模式
namespace
{
class PointTest
{
public:
    friend std::ostream& operator<<(std::ostream& os, const PointTest& point);
    static PointTest newCartesian(float x, float y)
    {
        return { x, y };
    }
    static PointTest newPolar(float a, float b)
    {
        return { a * std::cos(b), a * std::sin(b) };
    }

private:
    PointTest(const float x, const float y) :
        m_x{ x }, m_y{ y } {}

private:
    float m_x;
    float m_y;
};

std::ostream& operator<<(std::ostream& os, const PointTest& point)
{
    return os << "{ x: " << point.m_x << " y: }" << point.m_y;
}
} // namespace

// 抽象工厂
namespace
{
struct PointBase
{
    virtual ~PointBase() = default;
    virtual std::unique_ptr<PointBase> create() = 0;
    virtual std::unique_ptr<PointBase> clone() = 0;
};

struct Point2D : PointBase
{
    std::unique_ptr<PointBase> create() { return std::make_unique<Point2D>(); }
    std::unique_ptr<PointBase> clone() { return std::make_unique<Point2D>(*this); }
};

struct Point3D : PointBase
{
    std::unique_ptr<PointBase> create() { return std::make_unique<Point3D>(); }
    std::unique_ptr<PointBase> clone() { return std::make_unique<Point3D>(*this); }
};

void whoAmI(PointBase* who)
{
    auto new_who = who->create();      // `create` the object of same type i.e. pointed by who ?
    auto duplicate_who = who->clone(); // `copy` the object of same type i.e. pointed by who ?
    delete who;
}
} // namespace

// 使用现代C++实现工厂设计模式的函数式方法
namespace
{

enum class PointTypeTest
{
    Point,
    Point2D,
    Point3D
};

struct PointTest1
{ /* . . . */
};
struct Point2DTest1 : PointTest1
{ /* . . . */
};
struct Point3DTest1 : PointTest1
{ /* . . . */
};
class PointFunctionalFactory
{
    std::map<PointTypeTest, std::function<std::unique_ptr<PointTest1>()>> m_factories;

public:
    PointFunctionalFactory()
    {
        m_factories[PointTypeTest::Point2D] = [] { return std::make_unique<Point2DTest1>(); };
        m_factories[PointTypeTest::Point3D] = [] { return std::make_unique<Point3DTest1>(); };
    }
    std::unique_ptr<PointTest1> create(PointTypeTest type) { return m_factories[type](); }
};

void test()
{
    PointFunctionalFactory pf;
    auto p2D = pf.create(PointTypeTest::Point2D);
}

} // namespace

void abstractFactorTest()
{
    auto p = Point::newPolar(5, M_PI_4);
    std::cout << p << std::endl;
}