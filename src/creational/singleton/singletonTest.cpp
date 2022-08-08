//
// Created by cwb on 2022/8/8.
//
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
class Singleton
{
public:
    Singleton(Singleton const&) = delete;
    Singleton& operator=(Singleton const&) = delete;
    static Singleton& get()
    {
        static Singleton db;
        return db;
    }

    const std::string_view getInfo(const std::string& name) { return "info"; }

private:
    Singleton() = default;
};

struct Database
{
    virtual int32_t getPopulation(const std::string& country) = 0;
};

class SingletonDatabase : Database
{
public:
    SingletonDatabase(SingletonDatabase const&) = delete;
    SingletonDatabase& operator=(SingletonDatabase const&) = delete;
    static SingletonDatabase& get()
    {
        static SingletonDatabase db;
        return db;
    }
    int32_t getPopulation(const std::string& country) override { return m_countries[country]; }

private:
    SingletonDatabase()
    {
        std::ifstream ifs("countries.txt");
        std::string city, population;
        while (getline(ifs, city))
        {
            getline(ifs, population);
            m_countries[city] = stoi(population);
        }
    }
    std::map<std::string, int32_t> m_countries;
};

class DummyDatabase : public Database
{
public:
    DummyDatabase() :
        m_countries{ { "alpha", 1 }, { "beta", 2 }, { "gamma", 3 } } {}
    int32_t getPopulation(const std::string& country) override { return m_countries[country]; }

private:
    std::map<std::string, int32_t> m_countries;
};

// Testing class
class ConfigurableRecordFinder
{
public:
    ConfigurableRecordFinder(Database& db) :
        m_db{ db } {}
    int32_t totalPopulation(const std::vector<std::string>& countries)
    {
        int32_t result = 0;
        for (auto& country : countries)
            result += m_db.getPopulation(country);
        return result;
    }

private:
    Database& m_db; // Dependency Injection
};

// 多实例设计模式
enum class Importance
{
    PRIMARY,
    SECONDARY,
    TERTIARY
};

template <typename T, typename Key = std::string>
struct Multiton
{
    static std::shared_ptr<T> get(const Key& key)
    {
        if (const auto it = m_instances.find(key); it != m_instances.end())
        { // C++17
            return it->second;
        }
        return m_instances[key] = std::make_shared<T>();
    }

private:
    static std::map<Key, std::shared_ptr<T>> m_instances;
};

template <typename T, typename Key>
std::map<Key, std::shared_ptr<T>> Multiton<T, Key>::m_instances; // Just initialization of static data member

struct Printer
{
    Printer() { std::cout << "Total instances so far = " << ++InstCnt << std::endl; }

private:
    inline static int InstCnt = 0;
};

void singletonTest()
{
    std::cout << Singleton::get().getInfo("xxx") << std::endl;
    DummyDatabase db;
    ConfigurableRecordFinder rf(db);
    std::cout << rf.totalPopulation({ "Japan", "India", "America" }) << std::endl;
    using mt = Multiton<Printer, Importance>;
    auto main = mt::get(Importance::PRIMARY);
    auto aux = mt::get(Importance::SECONDARY);
    auto aux2 = mt::get(Importance::SECONDARY);
}