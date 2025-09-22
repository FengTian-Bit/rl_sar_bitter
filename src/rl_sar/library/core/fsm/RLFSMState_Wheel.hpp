/*
 * 
 * 2025.08.22
 */

#ifndef RLFSMSTATE_WHEEL_HPP
#define RLFSMSTATE_WHEEL_HPP

#include "fsm.hpp"
#include "rl_sdk.hpp"

class RLFSMState_Wheel : public RLFSMState
{
public:
    RLFSMState_Wheel(RL& rl, const RobotState<double>* state, RobotCommand<double>* command);

    ~RLFSMState_Wheel() override;

    void enter() override;
    void run() override;
    void exit() override;
    std::string checkChange() override;

private:
};

#endif // RLFSMSTATE_WHEEL_HPP
