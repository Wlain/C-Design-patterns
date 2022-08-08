//
// Created by william on 2022/8/8.
//

#ifndef CPPDESIGNPATTERNS_SAMPLE_H
#define CPPDESIGNPATTERNS_SAMPLE_H
#include <iostream>
class SampleBuilder;

class Sample
{
public:
    friend std::ostream& operator<<(std::ostream& os, const Sample& s);
    static SampleBuilder create(std::string name);

private:
    explicit Sample(std::string name) :
        m_name(std::move(name)){};

private:
    // 个人信息
    std::string m_name;
    std::string m_streetAddress;
    std::string m_postCode;
    std::string m_city;
    // 雇佣信息
    std::string m_companyName;
    std::string m_position; // position有职位的意思
    std::string m_annualIncome;
    friend class SampleBuilder;
};

#endif // CPPDESIGNPATTERNS_SAMPLE_H
