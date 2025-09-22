/*
 * 
 * 2025.08.08
 */

#ifndef RLFSMSTATE_RLLOCOMOTION_HPP
#define RLFSMSTATE_RLLOCOMOTION_HPP

#include "fsm.hpp"
#include "rl_sdk.hpp"

class RLFSMState_RLLocomotion : public RLFSMState
{
public:
    RLFSMState_RLLocomotion(RL& rl, const RobotState<double>* state, RobotCommand<double>* command);

    ~RLFSMState_RLLocomotion() override;

    void enter() override;
    void run() override;
    void exit() override;
    std::string checkChange() override;

private:

};

#endif // RLFSMSTATE_GETUP_HPP
