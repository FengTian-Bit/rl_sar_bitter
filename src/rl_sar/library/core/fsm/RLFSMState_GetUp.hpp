/*
 * 
 * 2025.08.08
 */

#ifndef RLFSMSTATE_GETUP_HPP
#define RLFSMSTATE_GETUP_HPP

#include "fsm.hpp"
#include "rl_sdk.hpp"

class RLFSMState_GetUp : public RLFSMState
{
public:
    RLFSMState_GetUp(RL& rl, const RobotState<double>* state, RobotCommand<double>* command);

    ~RLFSMState_GetUp() override;

    void enter() override;
    void run() override;
    void exit() override;
    std::string checkChange() override;


private:
};

#endif // RLFSMSTATE_GETUP_HPP
