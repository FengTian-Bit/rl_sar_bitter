/*
 * 
 * 2025.08.08
 */

#ifndef RLFSMSTATE_WAITING_HPP
#define RLFSMSTATE_WAITING_HPP

#include "fsm.hpp"
#include "rl_sdk.hpp"

//第三层派生类
class RLFSMState_Waiting : public RLFSMState
{
public:
    RLFSMState_Waiting(RL& rl, const RobotState<double>* state, RobotCommand<double>* command);

    ~RLFSMState_Waiting() override;

    void enter() override;
    void run() override;
    void exit() override;
    std::string checkChange() override;

private:

};

#endif // RLFSMSTATE_WAITING_HPP
