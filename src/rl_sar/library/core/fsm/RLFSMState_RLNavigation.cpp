#include "RLFSMState_RLNavigation.hpp"


RLFSMState_RLNavigation::RLFSMState_RLNavigation(RL& rl, const RobotState<double>* state, RobotCommand<double>* command)
    : RLFSMState(rl, state, command, "RLFSMState_RLNavigation") {}

RLFSMState_RLNavigation::~RLFSMState_RLNavigation(){}

void RLFSMState_RLNavigation::enter()
{
    std::cout << LOGGER::INFO << "Enter FSM RLNavigation mode. " << std::endl;
    // read params from yaml
    rl.config_name = rl.default_rl_config;
    std::string robot_path = rl.robot_name + "/" + rl.config_name;
    try
    {
        rl.InitRL(robot_path);
        rl.rl_init_done = true;
    }
    catch (const std::exception& e)
    {
        std::cout << LOGGER::ERROR << "InitRL() failed: " << e.what() << std::endl;
        rl.rl_init_done = false;
        rl.control.control_state = STATE::STATE_POS_GETUP;
    }
}

void RLFSMState_RLNavigation::run()
{
    std::cout << "\r" << std::flush << LOGGER::INFO << "RL Controller x:" << rl.control.x << " y:" << rl.control.y << " yaw:" << rl.control.yaw << std::flush;
    torch::Tensor _output_dof_pos, _output_dof_vel;
    if (rl.output_dof_pos_queue.try_pop(_output_dof_pos) && rl.output_dof_vel_queue.try_pop(_output_dof_vel))
    {
        for (int i = 0; i < rl.params.num_of_dofs; ++i)
        {
            if (_output_dof_pos.defined() && _output_dof_pos.numel() > 0)
            {
                fsm_command->motor_command.q[i] = rl.output_dof_pos[0][i].item<double>();
            }
            if (_output_dof_vel.defined() && _output_dof_vel.numel() > 0)
            {
                fsm_command->motor_command.dq[i] = rl.output_dof_vel[0][i].item<double>();
            }
            fsm_command->motor_command.kp[i] = rl.params.rl_kp[0][i].item<double>();
            fsm_command->motor_command.kd[i] = rl.params.rl_kd[0][i].item<double>();
            fsm_command->motor_command.tau[i] = 0;
        }
    }
}

std::string RLFSMState_RLNavigation::checkChange()
{
    if (rl.control.control_state == STATE::STATE_POS_GETDOWN)
    {
        return "RLFSMState_GetDown";
    }
    else if (rl.control.control_state == STATE::STATE_POS_GETUP)
    {
        return "RLFSMState_GetUp";
    }
    else if (rl.control.control_state == STATE::STATE_RL_LOCOMOTION)
    {
        return "RLFSMState_RLLocomotion";
    }
    else if (rl.control.control_state == STATE::STATE_RL_NAVIGATION)
    {
        return "RLFSMState_RLNavigation";
    }
    else if (rl.control.control_state == STATE::STATE_WAITING)
    {
        return "RLFSMState_Waiting";
    }
    return _stateName;
}

void RLFSMState_RLNavigation::exit()
{
    std::cout << LOGGER::INFO << "Exit FSM RLNavigation mode. " << std::endl;
    rl.rl_init_done = false;
}
