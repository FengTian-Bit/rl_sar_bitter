/*
 * 
 * 2025.08.08
 */

#ifndef RLFSMSTATE_GETDOWN_HPP
#define RLFSMSTATE_GETDOWN_HPP

#include "fsm.hpp"
#include "rl_sdk.hpp"

# define M_PI		3.14159265358979323846	
# define GETDOWN_D_PERCENT  1.0/500 /* Delta percent for homing, standing up, down  200-1s 400-2s 500-2.5s 1000-5s*/

class RLFSMState_GetDown : public RLFSMState
{
public:
    RLFSMState_GetDown(RL& rl, const RobotState<double>* state, RobotCommand<double>* command);

    ~RLFSMState_GetDown() override;

    void enter() override;
    void run() override;
    void exit() override;
    std::string checkChange() override;

    double calcCos(double start, double stop, double t) const;

private:
    double getdown_percent = 0.0;
};

#endif // RLFSMSTATE_GETDOWN_HPP
