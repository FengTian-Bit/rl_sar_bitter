/*
 * 
 * 2025.08.08
 */

#ifndef RLFSMSTATE_RLNAVIGATION_HPP
#define RLFSMSTATE_RLNAVIGATION_HPP

#include "fsm.hpp"
#include "rl_sdk.hpp"

class RLFSMState_RLNavigation : public RLFSMState
{
public:
    RLFSMState_RLNavigation(RL& rl, const RobotState<double>* state, RobotCommand<double>* command);

    ~RLFSMState_RLNavigation() override;

    void enter() override;
    void run() override;
    void exit() override;
    std::string checkChange() override;

private:

};

#endif // RLFSMSTATE_RLNAVIGATION_HPP
