//
// Created by william on 2022/8/8.
//

#include "sampleBuilder.h"

SampleBuilder& SampleBuilder::lives()
{
    return *this;
}

SampleBuilder& SampleBuilder::at(std::string streetName)
{
    m_sample.m_streetAddress = std::move(streetName);
    return *this;
}

SampleBuilder& SampleBuilder::withPostCode(std::string postCode)
{
    m_sample.m_postCode = std::move(postCode);
    return *this;
}

SampleBuilder& SampleBuilder::in(std::string city)
{
    m_sample.m_city = std::move(city);
    return *this;
}

SampleBuilder& SampleBuilder::works()
{
    return *this;
}

SampleBuilder& SampleBuilder::withCompany(std::string company)
{
    m_sample.m_companyName = std::move(company);
    return *this;
}

SampleBuilder& SampleBuilder::withPosition(std::string position)
{
    m_sample.m_position = std::move(position);
    return *this;
}

SampleBuilder& SampleBuilder::earning(std::string annualIncome)
{
    m_sample.m_annualIncome = std::move(annualIncome);
    return *this;
}
