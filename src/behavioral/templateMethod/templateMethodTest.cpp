//
// Created by william on 2022/8/10.
//
#include <iostream>
// turn: 回合
struct Game
{
    explicit Game(uint32_t players) :
        m_noOfPlayers(players)
    {}

    void run()
    {
        start();
        while (!haveWinner())
        {
            takeTurn();
        }
        std::cout << "Player:" << getWinner() << " wins!" << std::endl;
    }

protected:
    virtual void start() = 0;
    virtual bool haveWinner() = 0;
    virtual void takeTurn() = 0;
    virtual uint32_t getWinner() = 0;

protected:
    uint32_t m_currentPlayer{ 0 };
    uint32_t m_noOfPlayers{ 0 };
};

struct Cheese : public Game
{
    explicit Cheese() :
        Game{ 2 } {}

    void start() override
    {
        std::cout << "Starting Cheese with " << m_noOfPlayers << std::endl;
    }

    bool haveWinner() override
    {
        return m_turns == m_maxTurns;
    }

    void takeTurn() override
    {
        std::cout << "Turn " << m_turns << " taken by player " << m_currentPlayer << std::endl;
        m_turns++;
        m_currentPlayer = (m_currentPlayer + 1) % m_noOfPlayers;
    }

    uint32_t getWinner() override
    {
        return m_currentPlayer;
    }

private:
    uint32_t m_turns{ 0 }, m_maxTurns{ 4 };
};

void templateMethodTest()
{
    Cheese cheese;
    cheese.run();
}