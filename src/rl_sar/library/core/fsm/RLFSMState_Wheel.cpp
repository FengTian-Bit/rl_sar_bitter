#include "RLFSMState_Wheel.hpp"

RLFSMState_Wheel::RLFSMState_Wheel(RL& rl, const RobotState<double>* state, RobotCommand<double>* command)
        : RLFSMState(rl, state, command, "RLFSMState_Wheel") {}

RLFSMState_Wheel::~RLFSMState_Wheel(){}   

void RLFSMState_Wheel::enter()
{
    std::cout << LOGGER::INFO << "Enter FSM Wheel mode. " << std::endl;
    
    // read params from yaml
    rl.config_name = rl.default_rl_config;
    std::string robot_path = rl.robot_name + "/" + rl.config_name;
    std::cout << LOGGER::INFO << "FSM Wheel robot_path: " << robot_path << std::endl; 
    rl.ReadYaml(robot_path);
    // 初始化时停止所有轮电机
    fsm_command->motor_command.dq[3] = 0;
    fsm_command->motor_command.dq[7] = 0;
    fsm_command->motor_command.dq[11] = 0;
    fsm_command->motor_command.dq[15] = 0;
}

void RLFSMState_Wheel::run()
{
    float max_linear_speed = 3.0;
    float max_angular_speed = 4.5;
    float vFL = 0.0;
    float vFR = 0.0;
    float vRL = 0.0;
    float vRR = 0.0;

    float linear_speed  = max_linear_speed * rl.control.x;    // 前进/后退速度
    float angular_speed = max_angular_speed * rl.control.yaw; // 转向角速度
    
    if (rl.control.x == 0 && rl.control.yaw != 0) // 中心转向
    {
        vFL = -angular_speed;
        vFR =  angular_speed;
        vRL = -angular_speed;
        vRR =  angular_speed;
    } else if (rl.control.x != 0 && rl.control.yaw == 0) // 仅前进/后退
    {
        vFL = linear_speed;
        vFR = linear_speed;
        vRL = linear_speed;
        vRR = linear_speed;
    } else if (rl.control.x != 0 && rl.control.yaw != 0) // 行进中转向
    {
        // 差速驱动模型计算左右轮速度
        float wheel_base = 0.7;// 两对轮子轴距
        float left_speed = linear_speed + (angular_speed * wheel_base) / 2.0f;
        float right_speed = linear_speed - (angular_speed * wheel_base) / 2.0f;
        vFL = left_speed;
        vFR = right_speed;
        vRL = left_speed;
        vRR = right_speed;
    }

    fsm_command->motor_command.dq[3] = vFL;
    fsm_command->motor_command.dq[11] = vRL;
    fsm_command->motor_command.dq[7] = vFR;
    fsm_command->motor_command.dq[15] = vRR;

    std::cout << "\r" << std::flush << LOGGER::INFO <<"lin_vel: "<<linear_speed <<" ang_vel: "<< angular_speed << "  vFL:" << vFL << " vFR:" << vFR << " vRL:" << vRL << " vRR:" << vRR << std::flush;
    
    for (int idx : {3,7,11,15})
    {
        fsm_command->motor_command.kp[idx] = rl.params.rl_kp[0][idx].item<double>();
        fsm_command->motor_command.kd[idx] = rl.params.rl_kd[0][idx].item<double>();
        fsm_command->motor_command.tau[idx] = 0;
    }
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

void RLFSMState_Wheel::exit()
{
    std::cout << LOGGER::INFO << "Exit FSM Wheel mode. " << std::endl;
    fsm_command->motor_command.dq[3] = 0;
    fsm_command->motor_command.dq[7] = 0;
    fsm_command->motor_command.dq[11] = 0;
    fsm_command->motor_command.dq[15] = 0;
}

std::string RLFSMState_Wheel::checkChange()
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
