//
// Created by william on 2022/8/11.
//
#include <functional>
#include <iostream>
#include <vector>
struct Walk
{
    void operator()()
    {
        std::cout << "Walk" << std::endl;
    }
};

struct Jog
{
    void operator()()
    {
        std::cout << "Jog" << std::endl;
    }
};

struct Run
{
    void operator()()
    {
        std::cout << "Run" << std::endl;
    }
};

struct MicroCommand : public std::vector<std::function<void()>>
{
    void operator()()
    {
        for (auto&& f : *this)
        {
            f();
        }
    }
};

void doIt(const std::function<void()>& f)
{
    f();
}

struct BankAccount
{
    void deposit(int32_t amount)
    {
        m_balance += amount;
    }
    void withDraw(int32_t amount)
    {
        m_balance -= amount;
    }
    int32_t m_balance;
};

struct Command
{
    virtual void execute() = 0;
    virtual void undo() = 0;
};

struct BankAccountCommand : public Command
{
    enum class Action : bool
    {
        Deposit,
        Withdraw
    };

    BankAccountCommand(BankAccount& ba, Action a, uint32_t amount) :
        m_bankAccount(ba), m_action(a), m_amount(amount)
    {
    }

    void execute() override
    {
        (m_action == Action::Deposit) ? m_bankAccount.deposit(m_amount) : m_bankAccount.withDraw(m_amount);
    }

    void undo() override
    {
        (m_action == Action::Deposit) ? m_bankAccount.withDraw(m_amount) : m_bankAccount.deposit(m_amount);
    }

public:
    BankAccount& m_bankAccount;
    Action m_action;
    int32_t m_amount{ 0 };
};

struct CompositeBankAccountCommand : std::vector<BankAccountCommand>, public Command
{
    CompositeBankAccountCommand(const std::initializer_list<value_type>& items) :
        std::vector<BankAccountCommand>(items)
    {
    }

    void execute() override
    {
        for (auto& cmd : *this)
            cmd.execute();
    }
    void undo() override
    {
        for (auto& cmd : *this)
            cmd.undo();
    }
};

void commandTest()
{
    doIt(Walk());
    doIt(Jog());
    doIt(Run());
    MicroCommand command;
    command.push_back(Walk());
    command.push_back(Jog());
    command.push_back(Run());
    command();
    // 200从一个银行账户到另一个银行账户的汇款
    BankAccount ba1{ 1000 };
    BankAccount ba2{ 1000 };
    std::vector<BankAccountCommand> commands{
        BankAccountCommand{ ba1, BankAccountCommand::Action::Withdraw, 200 },
        BankAccountCommand{ ba2, BankAccountCommand::Action::Deposit, 200 }
    };
    for (auto& cmd : commands)
        cmd.execute();
    for (auto& cmd : commands)
        cmd.undo();
    std::cout << ba1.m_balance << std::endl;
    std::cout << ba2.m_balance << std::endl;
    CompositeBankAccountCommand commands2{
        BankAccountCommand{ba1, BankAccountCommand::Action::Withdraw, 200},
        BankAccountCommand{ba2, BankAccountCommand::Action::Deposit, 200}
    };
    commands2.execute();
    commands2.undo();
    std::cout << ba1.m_balance << std::endl;
    std::cout << ba2.m_balance << std::endl;
}