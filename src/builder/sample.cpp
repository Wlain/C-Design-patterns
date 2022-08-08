//
// Created by william on 2022/8/8.
//

#include "sample.h"

#include "sampleBuilder.h"

SampleBuilder Sample::create(std::string name)
{
    return SampleBuilder(std::move(name));
}

std::ostream& operator<<(std::ostream& os, const Sample& sample)
{
    return os << "name:" << sample.m_name
              << std::endl
              << "lives : " << std::endl
              << "at " << sample.m_streetAddress
              << " with postcode " << sample.m_postCode
              << " in " << sample.m_city
              << std::endl
              << "works : " << std::endl
              << "with " << sample.m_companyName
              << " as a " << sample.m_position
              << " earning " << sample.m_annualIncome;
}