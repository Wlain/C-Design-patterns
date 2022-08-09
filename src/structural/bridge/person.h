//
// Created by william on 2022/8/9.
//

#ifndef CPPDESIGNPATTERNS_PERSON_H
#define CPPDESIGNPATTERNS_PERSON_H
#include <memory>
#include <string>

struct Person
{
    Person();
    ~Person();
    void greet();
    class PersonImpl;
    std::unique_ptr<PersonImpl> m_impl;
    std::string m_name;
};

#endif // CPPDESIGNPATTERNS_PERSON_H
