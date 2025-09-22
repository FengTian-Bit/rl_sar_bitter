#include "RLFSMState_Test1.hpp"

//test1是单电机调试，sint函数，将count，des和实际输出打印出来，用matlab绘制曲线

RLFSMState_Test1::RLFSMState_Test1(RL& rl, const RobotState<double>* state, RobotCommand<double>* command)
        : RLFSMState(rl, state, command, "RLFSMState_Test1") {}

RLFSMState_Test1::~RLFSMState_Test1(){}   

void RLFSMState_Test1::enter()
{
    std::cout << LOGGER::INFO << "Enter FSM Test1 mode. " << std::endl;
    // read params from yaml
    rl.config_name = rl.default_rl_config;
    std::string robot_path = rl.robot_name + "/" + rl.config_name;
    std::cout << LOGGER::INFO << "FSM Wheel robot_path: " << robot_path << std::endl; 
    rl.ReadYaml(robot_path);

}

void RLFSMState_Test1::run()
{
    // 设置轮电机控制参数
    for (int idx : {3,7,11,15})
    {
        fsm_command->motor_command.kp[idx] = rl.params.rl_kp[0][idx].item<double>();
        fsm_command->motor_command.kd[idx] = rl.params.rl_kd[0][idx].item<double>();
        fsm_command->motor_command.tau[idx] = 0;
    }
    // 其余关节使用位置控制
    for (int i = 0; i < rl.params.num_of_dofs; ++i)
    {
        if (std::find(rl.params.wheel_indices.begin(), rl.params.wheel_indices.end(), i) == rl.params.wheel_indices.end()) //跳过轮电机
        {
            fsm_command->motor_command.q[i] = rl.params.default_dof_pos[0][i].item<double>();
            fsm_command->motor_command.dq[i] = 0;
            fsm_command->motor_command.kp[i] = rl.params.fixed_kp[0][i].item<double>();
            fsm_command->motor_command.kd[i] = rl.params.fixed_kd[0][i].item<double>();
            fsm_command->motor_command.tau[i] = 0;
        }
    }
}

void RLFSMState_Test1::exit()
{
    std::cout << LOGGER::INFO << "Exit FSM Test1 mode. " << std::endl;
}

std::string RLFSMState_Test1::checkChange()
{
    if (rl.control.control_state == STATE::STATE_POS_GETUP)
    {
        return "RLFSMState_GetUp";
    }
    else if (rl.control.control_state == STATE::STATE_POS_GETDOWN)
    {
        return "RLFSMState_GetDown";
    }
    else if (rl.control.control_state == STATE::STATE_WAITING)
    {
        return "RLFSMState_Waiting";
    }
    return _stateName;
}
