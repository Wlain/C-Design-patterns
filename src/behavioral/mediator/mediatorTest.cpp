//
// Created by william on 2023/12/2.
//

#include <iostream>
#include <string>
#include <string_view>
#include <vector>

struct ChatRoom
{
    virtual void broadcast(std::string form, std::string msg) = 0;
    virtual void message(std::string form, std::string to, std::string msg) = 0;
};

struct Person
{
    Person(std::string_view n) :
        m_name(n) {}
    void say(std::string msg) const
    {
        m_room->broadcast(m_name, msg);
    }
    void pm(std::string to, std::string msg) const
    {
        m_room->message(m_name, to, msg);
    }
    void receive(std::string from, std::string msg)
    {
        std::string s(from + ": \"" + msg + "\"");
        std::cout << "[" << m_name << "'s chat session]" << s << std::endl;
        m_chatLog.emplace_back(s);
    }
    std::string m_name;
    ChatRoom* m_room = nullptr;
    std::vector<std::string> m_chatLog;
};

struct GoogleChat : ChatRoom
{
    void broadcast(std::string form, std::string msg) override
    {
        for (auto p : m_people)
        {
            if (p->m_name != form)
            {
                p->receive(form, msg);
            }
        }
    }

    void join(Person* p)
    {
        std::string joinMsg = p->m_name + " joins the chat";
        broadcast("room", joinMsg);
        m_people.push_back(p);
        p->m_room = this;
    }

    void message(std::string form, std::string to, std::string msg) override
    {
        auto target = std::find_if(std::begin(m_people), std::end(m_people), [&](const Person* p) {
            return p->m_name == to;
        });
        if (target != std::end(m_people))
        {
            (*target)->receive(form, msg);
        }
    }

    std::vector<Person*> m_people;
};

void mediatorTest()
{
    GoogleChat room;
    Person joe("Joe");
    Person jane("Jane");
    room.join(&joe);
    room.join(&jane);
    joe.say("hi room");
    jane.say("oh, hey joe");

    Person simon("Simon");
    room.join(&simon);
    simon.say("hi everyone");
    jane.pm("Simon", "glad you found us, simon!");
}