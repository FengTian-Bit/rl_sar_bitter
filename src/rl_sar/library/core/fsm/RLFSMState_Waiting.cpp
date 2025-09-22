#include "RLFSMState_Waiting.hpp"

RLFSMState_Waiting::RLFSMState_Waiting(RL& rl, const RobotState<double>* state, RobotCommand<double>* command)
        : RLFSMState(rl, state, command, "RLFSMState_Waiting") {}

RLFSMState_Waiting::~RLFSMState_Waiting(){}

void RLFSMState_Waiting::enter()
    {
        std::cout << LOGGER::INFO << "Enter FSM Waiting mode. " << std::endl;
    }

void RLFSMState_Waiting::run()
    {
        for (int i = 0; i < rl.params.num_of_dofs; ++i)
        {
            fsm_command->motor_command.q[i] = fsm_state->motor_state.q[i];
            //kpkd=0
            fsm_command->motor_command.kp[i] = 0;
            fsm_command->motor_command.kd[i] = 0;
        }
        //Kp和Kd由yaml在rl_sdk.cpp给定
    }

void RLFSMState_Waiting::exit()
    {
        std::cout << LOGGER::INFO << "Exit FSM Waiting mode. " << std::endl;
    }

std::string RLFSMState_Waiting::checkChange()
    {
        if (rl.control.control_state == STATE::STATE_POS_GETUP)
        {
            return "RLFSMState_GetUp";
        }
        else if (rl.control.control_state == STATE::STATE_WAITING)
        {
            return "RLFSMState_Waiting";
        }
        return _stateName;
    }