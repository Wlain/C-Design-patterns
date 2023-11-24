//
// Created by william on 2023/11/23.
//
/**
 * 观察者模式:一个目标对象管理所有相依于它的观察者对象，并且在它本身的状态改变时主动发出通知。这通常透过呼叫各观察者所提供的方法来实现。此种模式通常被用在即时事件处理系统
 * 添附(Attach)：新增观察者到串炼内，以追踪目标对象的变化。
 * 解附(Detach)：将已经存在的观察者从串炼中移除。
 * 通知(Notify)：利用观察者所提供的更新函式来通知此目标已经产生变化
 */
#include <algorithm>
#include <iostream>
#include <list>
#include <vector>

// 抽象观察板
class ObserverBoardInterface
{
public:
    virtual void update(float a, float b, float c) = 0;
};

// 显示器的抽象接口
class DisplayBoardInterface
{
public:
    virtual void show() = 0;
};

// 抽象主题
class WeatherDataInterface
{
public:
    virtual void registerObserver(ObserverBoardInterface* ob) = 0;
    virtual void removeObserver(ObserverBoardInterface* ob) = 0;
    virtual void notifyObservers() = 0;
};

// 具体主题
class ParaWeatherData : public WeatherDataInterface
{
public:
    void SensorDataChange(float a, float b, float c)
    {
        m_humidity = a;
        m_temperature = b;
        m_pressure = c;
        notifyObservers();
    }

    void notifyObservers() override
    {
        auto pos = m_obs.begin();
        while (pos != m_obs.end())
        {
            ((ObserverBoardInterface*)(*pos))->update(m_humidity, m_temperature, m_pressure);
            (dynamic_cast<DisplayBoardInterface*>(*pos))->show();
            ++pos;
        }
    }

    void registerObserver(ObserverBoardInterface* ob) override
    {
        m_obs.push_back(ob);
    }

    void removeObserver(ObserverBoardInterface* ob) override
    {
        m_obs.remove(ob);
    }

private:
    std::list<ObserverBoardInterface*> m_obs;
    float m_humidity;    // 温度
    float m_temperature; // 湿度
    float m_pressure;    // 气压
};

// 一个具体的观察者A
class CurrentConditionBoard : public ObserverBoardInterface, public DisplayBoardInterface
{
public:
    explicit CurrentConditionBoard(WeatherDataInterface& data) :
        m_data(data)
    {
        m_data.registerObserver(this);
    }
    ~CurrentConditionBoard() = default;

    void update(float a, float b, float c) override
    {
        m_h = a;
        m_t = b;
        m_p = c;
    }

    void show() override
    {
        std::cout << "_____CurrentConditionBoard_____" << std::endl;
        std::cout << "温度: " << m_t << std::endl;
        std::cout << "湿度: " << m_h << std::endl;
        std::cout << "气压: " << m_p << std::endl;
        std::cout << "_____________________________" << std::endl;
    }

private:
    float m_h{};
    float m_t{};
    float m_p{};
    WeatherDataInterface& m_data;
};

// 一个具体的观察者B
class StatisticBoard : public ObserverBoardInterface, public DisplayBoardInterface
{
public:
    explicit StatisticBoard(WeatherDataInterface& data) :
        m_data(data)
    {
        m_data.registerObserver(this);
    }
    ~StatisticBoard() = default;

    void update(float h, float t, float p) override
    {
        ++m_count;
        if (t > m_maxt)
            m_maxt = t;
        if (t < m_mint)
            m_mint = t;
        m_avet = (m_avet * (m_count - 1) + t) / m_count;
    }

    void show() override
    {
        std::cout << "_____StatisticBoard_____" << std::endl;
        std::cout << "最大温度: " << m_maxt << std::endl;
        std::cout << "最小温度: " << m_mint << std::endl;
        std::cout << "平均温度: " << m_avet << std::endl;
        std::cout << "_________________________" << std::endl;
    }

private:
    float m_maxt;
    float m_mint;
    float m_avet;
    int m_count;
    WeatherDataInterface& m_data;
};

// 观察者，负责观察Observable
template <typename T>
struct Observer
{
    virtual void fieldChanged(T& source, const std::string& fieldName) = 0;
};

// 被观察者，负责通知Observer
template <typename T>
struct Observable
{
    void notify(T& source, const std::string& fieldName)
    {
        for (auto observer : m_observers)
            observer->fieldChanged(source, fieldName);
    }

    void subscribe(Observer<T>& observer)
    {
        m_observers.push_back(&observer);
    }

    void unsubscribe(Observer<T>& observer)
    {
        m_observers.erase(std::remove(m_observers.begin(), m_observers.end(), &observer), m_observers.end());
    }

private:
    std::vector<Observer<T>*> m_observers;
};

// 被观察者
struct Person : Observable<Person>
{
    void setAge(uint8_t age)
    {
        auto oldCanVote = getCanVote();
        m_age = age;
        notify(*this, "age");
        if (oldCanVote != getCanVote())
        {
            notify(*this, "can_vote");
        }
    }
    inline uint8_t getAge() const { return m_age; }
    bool getCanVote() const { return m_age >= 16; }

private:
    uint8_t m_age;
};

// 观察者
struct TrafficAdministration : Observer<Person>
{
    void fieldChanged(Person& source, const std::string& fieldName)
    {
        if (fieldName == "age")
        {
            if (source.getAge() < 17)
            {
                std::cout << "Not old enough to drive!\n";
            }
            else
            {
                std::cout << "Mature enough to drive!\n";
                source.unsubscribe(*this);
            }
        }
    }
};

void observerTest()
{
    /// test1
    std::unique_ptr<ParaWeatherData> wdata = std::make_unique<ParaWeatherData>();
    std::unique_ptr<CurrentConditionBoard> currentB = std::make_unique<CurrentConditionBoard>(*wdata);
    std::unique_ptr<StatisticBoard> statisticB = std::make_unique<StatisticBoard>(*wdata);
    wdata->SensorDataChange(10.2, 28.2, 1001);
    wdata->SensorDataChange(12, 30.12, 1003);
    wdata->SensorDataChange(10.2, 26, 806);
    wdata->SensorDataChange(10.3, 35.9, 900);
    wdata->registerObserver(currentB.get());
    wdata->SensorDataChange(100, 40, 1900);

    /// test2
    Person p;
    TrafficAdministration ta;
    p.subscribe(ta);
    p.setAge(16);
    p.setAge(17);
}
