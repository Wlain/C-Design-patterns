//
// Created by william on 2022/8/9.
//

#include "person.h"

#include <iostream>

struct Person::PersonImpl
{
    void greet(Person* p)
    {
        std::cout << "hello " << p->m_name << std::endl;
    }
};

Person::Person() :
    m_impl(new PersonImpl())
{
}

Person::~Person() = default;

void Person::greet()
{
    m_impl->greet(this);
}