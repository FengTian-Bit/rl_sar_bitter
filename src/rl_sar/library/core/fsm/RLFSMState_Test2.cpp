#include "RLFSMState_Test2.hpp"

//test2是测试整机的一个框架，可以修改机器人的command设置，从而规范每一次测试的命令值，
//同时会输出机器人的observation（自动使用rosbag录制并发布）

RLFSMState_Test2::RLFSMState_Test2(RL& rl, const RobotState<double>* state, RobotCommand<double>* command)
        : RLFSMState(rl, state, command, "RLFSMState_Test2") {}

RLFSMState_Test2::~RLFSMState_Test2(){}

void RLFSMState_Test2::enter()
{
    std::cout << LOGGER::INFO << "Enter FSM Test2 mode" << std::endl;
    
    // read params from yaml
    rl.config_name = rl.default_rl_config;
    std::string robot_path = rl.robot_name + "/" + rl.config_name;
    try
    {
        rl.InitRL(robot_path);
        rl.rl_init_done = true;
        std::cout << LOGGER::INFO << "InitRL() success" << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << LOGGER::ERROR << "InitRL() failed: " << e.what() << std::endl;
        rl.rl_init_done = false;
        rl.control.control_state = STATE::STATE_POS_GETUP;
    }

    this->count = 0;
    //pub obs
    this->pub_obs = ros::NodeHandle().advertise<robot_msgs::Observation>("/clamped_obs", 10);

}

void RLFSMState_Test2::run()
{
    //-----使用计数器当作计时器，控制命令值的改变-------//
    count ++;
    if (count <= 500) // 0.005s * 500 = 2.5s
    {
        rl.control.x = 0.1;
        rl.control.y = 0.0;
        rl.control.yaw = 0.0;
    } else if(count > 500 && count <= 1000) // 0.005s * 500 = 2.5s
    {
        rl.control.x = 0.2;
        rl.control.y = 0.0;
        rl.control.yaw = 0.0;
    } else if(count > 1000 && count <= 1500) // 0.005s * 500 = 2.5s
    {
        rl.control.x = 0.3;
        rl.control.y = 0.0;
        rl.control.yaw = 0.0;
    } else if(count > 1500)
    {
        rl.control.x = 0.0;
        rl.control.y = 0.0;
        rl.control.yaw = 0.0;
        //退出test2模式，进入getup模式，从而结束录制
        rl.control.SetControlState(STATE::STATE_POS_GETUP);
        count = 0;
    }
    //-------------------------------------//

    //--------将observation发布出去,运行应在us级---------//
    torch::Tensor clamped_obs = rl.ComputeObservation();
    robot_msgs::Observation obs_msg;
    // 1. 角速度（3个）
    for (int i = 0; i < 3; ++i)
        obs_msg.ang_vel[i] = clamped_obs[0][i].item<float>();
    // 2. 重力向量（3个）
    for (int i = 0; i < 3; ++i)
        obs_msg.gravity_vec[i] = clamped_obs[0][i + 3].item<float>();
    // 3. 指令（3个）
    for (int i = 0; i < 3; ++i)
        obs_msg.commands[i] = clamped_obs[0][i + 6].item<float>();
    // 4. 关节位置（16个）
    for (int i = 0; i < 16; ++i)
        obs_msg.dof_pos[i] = clamped_obs[0][i + 9].item<float>();
    // 5. 关节速度（16个）
    for (int i = 0; i < 16; ++i)
        obs_msg.dof_vel[i] = clamped_obs[0][i + 25].item<float>();
    // 6. 动作（16个）
    for (int i = 0; i < 16; ++i)
        obs_msg.actions[i] = clamped_obs[0][i + 41].item<float>();
    for (int i= 0; i < 57; i++)
        obs_msg.obs[i] = clamped_obs[0][i].item<float>();

    pub_obs.publish(obs_msg); 
    std::cout<<"clamped_obs: "<<clamped_obs<<std::endl;
    //----------------------------------------------------//

    //--------------如果还要加什么-----------------------//
                    
    //----------------------------------------------------//

    //--------设置command到电机（RLLocomotion原有的)---------//
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
    //---------------------------------------------------//

}

void RLFSMState_Test2::exit()
{
    std::cout << LOGGER::INFO << "Exit FSM Test2 mode" << std::endl;
    rl.rl_init_done = false;
}

std::string RLFSMState_Test2::checkChange()
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
