/*
 * 
 * 2025.08.08 tf
 * 2025.09.30 zry
 */

#ifndef RLFSMSTATE_GETUP_HPP
#define RLFSMSTATE_GETUP_HPP

#include "fsm.hpp"
#include "rl_sdk.hpp"

# define GETUP_D_PERCENT  1.0/500 /* Delta percent for homing, standing up, down  200-1s 400-2s 500-2.5s 1000-5s*/
# define M_PI		3.14159265358979323846	/* pi */

class RLFSMState_GetUp : public RLFSMState
{
public:
    RLFSMState_GetUp(RL& rl, const RobotState<double>* state, RobotCommand<double>* command);

    ~RLFSMState_GetUp() override;

    void enter() override;
    void run() override;
    void exit() override;
    std::string checkChange() override;
    double calcCos(double start, double stop, double t) const;

private:
    int step_standup_counter = 0;
    double getup_percent = 0.0;
    double home_percent = 0.0;
};

#endif // RLFSMSTATE_GETUP_HPP
