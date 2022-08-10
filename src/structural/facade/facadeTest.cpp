//
// Created by william on 2022/8/10.
//
#include <iostream>

// 报警器
struct Alarm
{
    void alarmOn()
    {
        std::cout << "alarm is on" << std::endl;
    }

    void alarmOff()
    {
        std::cout << "alarm is off" << std::endl;
    }
};

// 空调
struct Ac
{
    void acOn() { std::cout << "Ac is on" << std::endl; }
    void acOff() { std::cout << "AC is off" << std::endl; }
};

// 电视
struct Tv
{
    void tvOn() { std::cout << "Tv is on" << std::endl; }
    void tvOff() { std::cout << "TV is off" << std::endl; }
};

struct HouseFacade
{
    void goToWork()
    {
        m_ac.acOff();
        m_tv.tvOff();
        m_alarm.alarmOn();
    }
    void comeHome()
    {
        m_alarm.alarmOff();
        m_ac.acOn();
        m_tv.tvOn();
    }

private:
    Alarm m_alarm;
    Ac m_ac;
    Tv m_tv;
};

void facadeTest()
{
    HouseFacade hf;
    hf.goToWork();
    hf.comeHome();
}