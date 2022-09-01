//
// Created by cwb on 2022/8/31.
//
#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <vector>
namespace
{
/// Event
enum class Event
{
    connect,
    connected,
    disconnect,
    timeout
};

inline std::ostream& operator<<(std::ostream& os, const Event& e)
{
    switch (e)
    {
    case Event::connect:
        os << "connect";
        break;
    case Event::connected:
        os << "connected";
        break;
    case Event::disconnect:
        os << "disconnect";
        break;
    case Event::timeout:
        os << "timeout";
        break;
    }
    return os;
}

struct State
{
    virtual std::unique_ptr<State> onEvent(Event e) = 0;
};

/// States

struct Idle : public State
{
    std::unique_ptr<State> onEvent(Event e) override;
};

struct Connecting : public State
{
    std::unique_ptr<State> onEvent(Event e) override;

private:
    uint32_t m_trial{ 0 };
    static constexpr u_int8_t m_maxTrial{ 3 };
};

struct Connected : public State
{
    std::unique_ptr<State> onEvent(Event e) override;
};

std::unique_ptr<State> Idle::onEvent(Event e)
{
    std::cout << "Idle -> " << e << std::endl;
    if (e == Event::connect) return std::make_unique<Connecting>();
    return nullptr;
}

std::unique_ptr<State> Connecting::onEvent(Event e)
{
    std::cout << "Connecting -> " << e << std::endl;
    switch (e)
    {
    case Event::connected:
        return std::make_unique<Connected>();
    case Event::timeout:
        return ++m_trial < m_maxTrial ? nullptr : std::make_unique<Idle>();
    }
    return nullptr;
}

std::unique_ptr<State> Connected::onEvent(Event e)
{
    std::cout << "Connected -> " << e << std::endl;
    if (e == Event::disconnect) return std::make_unique<Idle>();
    return nullptr;
}

struct Bluetooth
{
    void dispatch(Event e)
    {
        auto newState = m_currentState->onEvent(e);
        if (newState)
            m_currentState = std::move(newState);
    }
    /// 建立连接
    template <typename... Events>
    void establishConnection(Events... e)
    {
        (dispatch(e), ...);
    }
    std::unique_ptr<State> m_currentState = std::make_unique<Idle>();
};

/// test1还是有很多冗余的代码
void test1()
{
    Bluetooth bluetooth;
    bluetooth.establishConnection(Event::connect, Event::timeout, Event::connected, Event::disconnect);
}

struct EventConnect
{
    std::string m_address;
};

struct EventConnected
{};
struct EventDisconnect
{};
struct EventTimeout
{};

using Event2 = std::variant<EventConnect, EventConnected, EventDisconnect, EventTimeout>;

struct Idle2
{};
struct Connecting2
{
    std::string m_address;
    uint32_t m_trial{ 0 };
    static constexpr u_int8_t m_maxTrial{ 3 };
};

struct Connected2
{
};

using State2 = std::variant<Idle2, Connecting2, Connected2>;

struct Transitions
{
    std::optional<State2> operator()(Idle2&, const EventConnect& e)
    {
        std::cout << "Idle2 -> Connected2" << std::endl;
        return Connecting2{ e.m_address };
    }

    std::optional<State2> operator()(Connecting2&, const EventConnected& e)
    {
        std::cout << "Connecting2 -> Connected2" << std::endl;
        return Connected2();
    }
    std::optional<State2> operator()(Connecting2& connected, const EventTimeout& e)
    {
        std::cout << "Connecting2 -> timeout" << std::endl;
        return ++connected.m_trial < Connecting2::m_maxTrial ? std::nullopt : std::optional<State2>(Idle2{});
    }
    std::optional<State2> operator()(Connected2&, const EventDisconnect& e)
    {
        std::cout << "Connected2 -> Disconnect" << std::endl;
        return Idle2{};
    }

    template <typename State_t, typename Event_t>
    std::optional<State2> operator()(State_t&, const Event_t&) const
    {
        std::cout << "Unknow" << std::endl;
        return std::nullopt;
    }
};

template <typename StateVariant, typename EventVariant, typename Transitions>
struct Bluetooth2
{
    void dispatch(const EventVariant& event)
    {
        std::optional<StateVariant> newState = std::visit(Transitions{}, m_currentState, event);
        if (newState)
            m_currentState = *std::move(newState);
    }

    template <typename... Events>
    void establishConnection(Events... e)
    {
        (dispatch(e), ...);
    }

    StateVariant m_currentState;
};

/// 状态之间不是松散耦合的，如果状态的顺序变化，或者添加新的状态，一定会修改里面的条件
void test2()
{
    Bluetooth2<State2, Event2, Transitions> b;
    b.establishConnection(EventConnect{ "AA::BB::CC::DD" }, EventTimeout{}, EventConnected{}, EventDisconnect{});
}

enum class State3
{
    OffHook,
    Connecting,
    Connected,
    OnHold,
    OnHook
};

inline std::ostream& operator<<(std::ostream& os, State3& s)
{
    switch (s)
    {
    case State3::OffHook:
        os << "OffHook";
        break;
    case State3::Connecting:
        os << "Connecting";
        break;
    case State3::Connected:
        os << "Connected";
        break;
    case State3::OnHold:
        os << "OnHold";
        break;
    case State3::OnHook:
        os << "OnHook";
        break;
    }
    return os;
}

enum class Trigger
{
    CallDialed,
    HungUp,
    CallConnected,
    PlacedOnHold,
    TakenOffHold,
    LeftMessage,
    StopUsingPhone
};

inline std::ostream& operator<<(std::ostream& os, Trigger& t)
{
    switch (t)
    {
    case Trigger::CallDialed:
        os << "call dialed";
        break;
    case Trigger::HungUp:
        os << "hung up";
        break;
    case Trigger::CallConnected:
        os << "call connected";
        break;
    case Trigger::PlacedOnHold:
        os << "placed on hold";
        break;
    case Trigger::TakenOffHold:
        os << "taken off hold";
        break;
    case Trigger::LeftMessage:
        os << "left message";
        break;
    case Trigger::StopUsingPhone:
        os << "putting phone on hook";
        break;
    }
    return os;
}

void test3()
{
    std::map<State3, std::vector<std::pair<Trigger, State3>>> transitionTable;
    transitionTable[State3::OffHook] = {
        { Trigger::CallDialed, State3::Connecting },
        { Trigger::StopUsingPhone, State3::OnHook }
    };
    transitionTable[State3::Connecting] = {
        { Trigger::HungUp, State3::OffHook },
        { Trigger::CallConnected, State3::Connected }
    };
    transitionTable[State3::Connected] = {
        { Trigger::LeftMessage, State3::OffHook },
        { Trigger::HungUp, State3::OffHook },
        { Trigger::PlacedOnHold, State3::OnHold }
    };
    transitionTable[State3::OnHold] = {
        { Trigger::TakenOffHold, State3::Connected },
        { Trigger::HungUp, State3::OffHook }
    };

    State3 currentState{ State3::OffHook };
    State3 exitState{ State3::OnHook };
    for (;;)
    {
        std::cout << "The phone is currently " << currentState << std::endl;
        std::cout << "Select a trigger:\n";
        uint32_t i = 0;
        for (auto item : transitionTable[currentState])
            std::cout << i++ << ". " << item.first << "\n";
        uint32_t input;
        std::cin >> input;
        currentState = transitionTable[currentState][input].second; // Caution: index out of range not checked
        if (currentState == exitState) break;
    }
    std::cout << "We are done using the phone" << std::endl;
}

} // namespace

void stateTest()
{
    test1();
    std::cout << "=============" << std::endl;
    test2();
    std::cout << "=============" << std::endl;
    test3();
}