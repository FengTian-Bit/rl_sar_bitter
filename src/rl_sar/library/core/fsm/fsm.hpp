#ifndef FSM_HPP
#define FSM_HPP

#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>
#include "RobotState.hpp"
#include "RobotCommand.hpp"

// 状态基类，最上层的，定义状态的基本行为，完全不负责具体实现，派生类中间层在rl_sdk
class FSMState
{
public:
    FSMState(std::string name) : _stateName(std::move(name)) {}
    virtual ~FSMState() = default;

    virtual void enter() = 0;
    virtual void run() = 0;
    virtual void exit() = 0;
    virtual std::string checkChange() { return _stateName; }

    const std::string &getStateName() const { return _stateName; }

protected:
    std::string _stateName;
};

// 状态机类，用于管理状态转换和执行
class FSM
{
public:
    FSM() : _currentState(nullptr), _nextState(nullptr), _mode(Mode::NORMAL) {}

    void addState(std::shared_ptr<FSMState> state)
    {
        _states[state->getStateName()] = state;
    }

    void setInitialState(const std::string &name)
    {
        _currentState = _states.at(name);
        _currentState->enter();
        _nextState = _currentState;
    }

    void run()
    {
        if (!_currentState) //防止空指针异常，确保状态机在未初始化时安全退出
            return;

        if (_mode == Mode::NORMAL)
        {
            _currentState->run(); //核心执行

            std::string next_state = _currentState->checkChange();
            if (next_state != _currentState->getStateName())
            {
                _mode = Mode::CHANGE;
                _nextState = _states.at(next_state); // map里的at函数获取目标状态，（键为状态名称字符串，值为状态对象的智能指针）
                std::cout << std::endl << "[FSM]  Switch from " << _currentState->getStateName() << " to " << _nextState->getStateName() << std::endl;
            }
        }
        else if (_mode == Mode::CHANGE)
        {
            _currentState->exit();
            _currentState = _nextState;

            _currentState->enter();
            _mode = Mode::NORMAL;
            _currentState->run();
        }
    }

    enum class Mode
    {
        NORMAL,
        CHANGE
    };

    std::unordered_map<std::string, std::shared_ptr<FSMState>> _states;
    std::shared_ptr<FSMState> _currentState;
    std::shared_ptr<FSMState> _nextState;
    Mode _mode;
};

#endif // FSM_HPP
