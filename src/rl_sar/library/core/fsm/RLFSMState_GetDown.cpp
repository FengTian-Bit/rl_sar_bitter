#include "RLFSMState_GetDown.hpp"


RLFSMState_GetDown::RLFSMState_GetDown(RL& rl, const RobotState<double>* state, RobotCommand<double>* command)
    : RLFSMState(rl, state, command, "RLFSMState_GetDown") {}

RLFSMState_GetDown::~RLFSMState_GetDown(){}

void RLFSMState_GetDown::enter()
{
    std::cout << LOGGER::INFO << "Enter FSM GetDown mode. " << std::endl;
    rl.running_percent = 0.0f;
    rl.now_state = *fsm_state;
}

void RLFSMState_GetDown::run()
{
    if (rl.running_percent < 1.0f)
    {
        rl.running_percent += 1.0f / 1000.0f;
        rl.running_percent = std::min(rl.running_percent, 1.0f);
        for (int i = 0; i < rl.params.num_of_dofs; ++i)
        {
            fsm_command->motor_command.q[i] = (1 - rl.running_percent) * rl.now_state.motor_state.q[i] + rl.running_percent * rl.start_state.motor_state.q[i];
            fsm_command->motor_command.dq[i] = 0;
            // fsm_command->motor_command.kp[i] = rl.params.fixed_kp[0][i].item<double>();
            fsm_command->motor_command.kp[i] = 0;
            fsm_command->motor_command.kd[i] = rl.params.fixed_kd[0][i].item<double>();
            fsm_command->motor_command.tau[i] = 0;
        }
        std::cout << "\r" << std::flush << LOGGER::INFO << "Getting down "<< std::fixed << std::setprecision(2) << rl.running_percent * 100.0f << "%" << std::flush;
    }
}

std::string RLFSMState_GetDown::checkChange() 
{
    if (rl.running_percent >= 1.0f)
    {
        return "RLFSMState_Waiting";
    }
    else if (rl.control.control_state == STATE::STATE_POS_GETUP)
    {
        return "RLFSMState_GetUp";
    }
    return _stateName;
}
void RLFSMState_GetDown::exit()
{
    std::cout << LOGGER::INFO << "Exit FSM GetDown mode. " << std::endl;
    rl.running_percent = 0.0f;
}