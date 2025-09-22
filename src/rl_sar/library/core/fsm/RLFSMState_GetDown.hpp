/*
 * 
 * 2025.08.08
 */

#ifndef RLFSMSTATE_GETDOWN_HPP
#define RLFSMSTATE_GETDOWN_HPP

#include "fsm.hpp"
#include "rl_sdk.hpp"

class RLFSMState_GetDown : public RLFSMState
{
public:
    RLFSMState_GetDown(RL& rl, const RobotState<double>* state, RobotCommand<double>* command);

    ~RLFSMState_GetDown() override;

    void enter() override;
    void run() override;
    void exit() override;
    std::string checkChange() override;

private:
};

#endif // RLFSMSTATE_GETDOWN_HPP
