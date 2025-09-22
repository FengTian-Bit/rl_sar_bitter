/*
 * 
 * 2025.09.19
 */

#ifndef RLFSMSTATE_TEST1_HPP
#define RLFSMSTATE_TEST1_HPP

#include "fsm.hpp"
#include "rl_sdk.hpp"

class RLFSMState_Test1 : public RLFSMState
{
public:
    RLFSMState_Test1(RL& rl, const RobotState<double>* state, RobotCommand<double>* command);

    ~RLFSMState_Test1() override;

    void enter() override;
    void run() override;
    void exit() override;
    std::string checkChange() override;

private:
};

#endif // RLFSMSTATE_TEST1_HPP
