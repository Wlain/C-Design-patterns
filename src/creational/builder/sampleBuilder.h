//
// Created by william on 2022/8/8.
//

#ifndef CPPDESIGNPATTERNS_SAMPLEBUILDER_H
#define CPPDESIGNPATTERNS_SAMPLEBUILDER_H

#include "sample.h"

class SampleBuilder
{
public:
    explicit SampleBuilder(std::string name) :
        m_sample(std::move(name)) {}
    operator Sample() const { return m_sample; }
    SampleBuilder& lives();
    SampleBuilder& at(std::string streetName);
    SampleBuilder& withPostCode(std::string postCode);
    SampleBuilder& in(std::string city);
    SampleBuilder& works();
    SampleBuilder& withCompany(std::string company);
    SampleBuilder& withPosition(std::string position);
    SampleBuilder& earning(std::string annualIncome);

private:
    Sample m_sample;
};

#endif // CPPDESIGNPATTERNS_SAMPLEBUILDER_H
