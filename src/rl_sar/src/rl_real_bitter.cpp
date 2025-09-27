/*
 * Copyright (c) 2024-2025 Ziqi Fan
 * SPDX-License-Identifier: Apache-2.0
 */

#include "rl_real_bitter.hpp"
// #include "rl_sim.hpp"

// #define PLOT
// #define CSV_LOGGER

RL_Sim::RL_Sim()
{
    this->is_simulation = false;

    ros::NodeHandle nh;

    // read params from yaml
    nh.param<std::string>("robot_name", this->robot_name, "");
    nh.param<std::string>("config_name", this->default_rl_config, "");
    // this->ReadYamlBase(this->robot_name);
        // this->ReadYaml(this->robot_name);
        this->ReadYaml("bitter/robot_lab");

    // init torch
    torch::autograd::GradMode::set_enabled(false);
    torch::set_num_threads(4);

    // init robot
    this->joint_publishers_commands.resize(this->params.num_of_dofs);
    this->InitOutputs();
    this->InitControl();

    // publisher待改
    // ros::Publisher pub_cmd; //放在.h里
    pub_cmd = nh.advertise<robot_msgs::LowlevelCmd>("/BitterCmd", 10);


    // subscriber待改
    this->cmd_vel_subscriber = nh.subscribe<geometry_msgs::Twist>("/cmd_vel", 10, &RL_Sim::CmdvelCallback, this);
    this->joy_subscriber = nh.subscribe<sensor_msgs::Joy>("/joy", 10, &RL_Sim::JoyCallback, this);

    //BitterImu获取二代imu状态
    this->imu_state_subscriber = nh.subscribe<robot_msgs::BitterImu>("/BitterImu", 10, &RL_Sim::ImuCallback, this);

    //Bitter获得电机状态
    this->motor_state_subscriber = nh.subscribe<robot_msgs::LowlevelState>("/BitterState", 10, &RL_Sim::JointStatesCallback, this);
    for (int i = 0; i < this->params.num_of_dofs; ++i)
    {
        const std::string &joint_name = this->params.joint_controller_names[i];
        this->joint_positions[joint_name] = 0.0;
        this->joint_velocities[joint_name] = 0.0;
        this->joint_efforts[joint_name] = 0.0;
    }

    // this->model_state_subscriber = nh.subscribe<gazebo_msgs::ModelStates>("/gazebo/model_states", 10, &RL_Sim::ModelStatesCallback, this);

//待改

    // loop
    this->loop_control = std::make_shared<LoopFunc>("loop_control", this->params.dt, std::bind(&RL_Sim::RobotControl, this));
    this->loop_rl = std::make_shared<LoopFunc>("loop_rl", this->params.dt * this->params.decimation, std::bind(&RL_Sim::RunModel, this));
    this->loop_control->start();
    this->loop_rl->start();

    // keyboard
    this->loop_keyboard = std::make_shared<LoopFunc>("loop_keyboard", 0.05, std::bind(&RL_Sim::KeyboardInterface, this));
    this->loop_keyboard->start();

#ifdef PLOT
    this->plot_t = std::vector<int>(this->plot_size, 0);
    this->plot_real_joint_pos.resize(this->params.num_of_dofs);
    this->plot_target_joint_pos.resize(this->params.num_of_dofs);
    for (auto &vector : this->plot_real_joint_pos) { vector = std::vector<double>(this->plot_size, 0); }
    for (auto &vector : this->plot_target_joint_pos) { vector = std::vector<double>(this->plot_size, 0); }
    this->loop_plot = std::make_shared<LoopFunc>("loop_plot", 0.001, std::bind(&RL_Sim::Plot, this));
    this->loop_plot->start();
#endif
#ifdef CSV_LOGGER
    this->CSVInit(this->robot_name);
#endif

    std::cout << LOGGER::INFO << "RL_Sim start" << std::endl;
}

RL_Sim::~RL_Sim()
{
    this->loop_keyboard->shutdown();
    this->loop_control->shutdown();
    this->loop_rl->shutdown();
#ifdef PLOT
    this->loop_plot->shutdown();
#endif
    std::cout << LOGGER::INFO << "RL_Sim exit" << std::endl;
}

void RL_Sim::GetState(RobotState<double> *state)
{
    if (this->params.framework == "isaacgym")
    {
        state->imu.quaternion[3] = this->quaternion[0];
        state->imu.quaternion[0] = this->quaternion[1];
        state->imu.quaternion[1] = this->quaternion[2];
        state->imu.quaternion[2] = this->quaternion[3];
    }
    else if (this->params.framework == "isaacsim")
    {
        state->imu.quaternion[0] = this->quaternion[0];
        state->imu.quaternion[1] = this->quaternion[1];
        state->imu.quaternion[2] = this->quaternion[2];
        state->imu.quaternion[3] = this->quaternion[3];
    }

    state->imu.gyroscope[0] = this->gyroscope[0];
    state->imu.gyroscope[1] = this->gyroscope[1];
    state->imu.gyroscope[2] = this->gyroscope[2];

    // state->imu.accelerometer

    for (int i = 0; i < this->params.num_of_dofs; ++i)
    {//待改
        state->motor_state.q[i] = this->joint_positions[this->params.joint_controller_names[i]];
        state->motor_state.dq[i] = this->joint_velocities[this->params.joint_controller_names[i]];
        state->motor_state.tau_est[i] = this->joint_efforts[this->params.joint_controller_names[i]];
        // std::cout << "Joint " << this->params.joint_controller_names[i] 
        //       << " position: " << this->joint_positions[this->params.joint_controller_names[i]] 
        //       << " velocity: " << this->joint_velocities[this->params.joint_controller_names[i]] 
        //       << " effort: " << this->joint_efforts[this->params.joint_controller_names[i]] 
        //       << std::endl;
    }
}

// void RL_Sim::SetCommand(const RobotCommand<double> *command)
// {
    
//     for (int i = 0; i < this->params.num_of_dofs; ++i)
//     {
//         this->joint_publishers_commands[i].q = command->motor_command.q[i];
//         this->joint_publishers_commands[i].dq = command->motor_command.dq[i];
//         this->joint_publishers_commands[i].kp = command->motor_command.kp[i];
//         this->joint_publishers_commands[i].kd = command->motor_command.kd[i];
//         this->joint_publishers_commands[i].tau = command->motor_command.tau[i];
//     }

//     for (int i = 0; i < this->params.num_of_dofs; ++i)
//     {
//         this->joint_publishers[this->params.joint_controller_names[i]].publish(this->joint_publishers_commands[i]);
//     }
// }


void RL_Sim::SetCommand(const RobotCommand<double> *command)
{
    robot_msgs::LowlevelCmd lowlevel_cmd;

    for (int i = 0; i < this->params.num_of_dofs; ++i)
    {
        lowlevel_cmd.motorCmd[i].q = command->motor_command.q[i];
        lowlevel_cmd.motorCmd[i].dq = command->motor_command.dq[i];
        lowlevel_cmd.motorCmd[i].Kp = command->motor_command.kp[i];
        lowlevel_cmd.motorCmd[i].Kd = command->motor_command.kd[i];
        lowlevel_cmd.motorCmd[i].tau = command->motor_command.tau[i];
        if(i == 3 || i == 7 || i == 11 || i == 15) // 3, 4, 5为脚部电机
        {
            lowlevel_cmd.motorCmd[i].Kvp = command->motor_command.kp[i];
            lowlevel_cmd.motorCmd[i].Kvi = command->motor_command.kd[i];
        }
      
    }
    this->pub_cmd.publish(lowlevel_cmd);

}


void RL_Sim::RobotControl()
{
    // if (this->control.control_state == STATE_RESET_SIMULATION)//重置仿真环境
    // {
    //     gazebo_msgs::SetModelState set_model_state;
    //     set_model_state.request.model_state.model_name = this->gazebo_model_name;
    //     set_model_state.request.model_state.pose.position.z = 1.0;
    //     set_model_state.request.model_state.reference_frame = "world";
    //     this->gazebo_set_model_state_client.call(set_model_state);
    //     this->control.control_state = this->control.last_control_state;
    // }
    // if (this->control.control_state == STATE_TOGGLE_SIMULATION)//切换仿真状态
    // {
    //     std_srvs::Empty empty;
    //     if (simulation_running)
    //     {
    //         this->gazebo_pause_physics_client.call(empty); //调用 gazebo_pause_physics_client 服务，暂停模拟
    //         std::cout << std::endl << LOGGER::INFO << "Simulation Stop" << std::endl;
    //     }
    //     else
    //     {
    //         this->gazebo_unpause_physics_client.call(empty);
    //         std::cout << std::endl << LOGGER::INFO << "Simulation Start" << std::endl;
    //     }
    //     simulation_running = !simulation_running;
    //     this->control.control_state = this->control.last_control_state;
    // }
    // if (simulation_running)
    // {
        this->motiontime++;
        this->GetState(&this->robot_state);
        this->StateController(&this->robot_state, &this->robot_command);
        this->SetCommand(&this->robot_command);
    // }
}

// void RL_Sim::ModelStatesCallback(const gazebo_msgs::ModelStates::ConstPtr &msg)
// {
//     this->vel = msg->twist[2];
//     this->pose = msg->pose[2];
// }

void RL_Sim::ImuCallback(const robot_msgs::BitterImu::ConstPtr &msg)
{
    // this->vel = msg->twist[2];
    // this->pose = msg->pose[2];
    this->quaternion[0] = msg->quat[0];
    this->quaternion[1] = msg->quat[1];
    this->quaternion[2] = msg->quat[2];
    this->quaternion[3] = msg->quat[3];

    this->gyroscope[0] = msg->angular_vel_local[0];
    this->gyroscope[1] = msg->angular_vel_local[1];
    this->gyroscope[2] = msg->angular_vel_local[2];

    this->accelerometer[0] = msg->linear_acc_local[0];
    this->accelerometer[1] = msg->linear_acc_local[1];
    this->accelerometer[2] = msg->linear_acc_local[2];
}

void RL_Sim::CmdvelCallback(const geometry_msgs::Twist::ConstPtr &msg)
{
    this->cmd_vel = *msg;
    // std::cout << "Received cmd_vel: linear=(" << this->cmd_vel.linear.x << ", " << this->cmd_vel.linear.y << ", " << this->cmd_vel.linear.z << "), angular=(" << this->cmd_vel.angular.x << ", " << this->cmd_vel.angular.y << ", " << this->cmd_vel.angular.z << ")" << std::endl;
}

void RL_Sim::JoyCallback(const sensor_msgs::Joy::ConstPtr &msg)
{
    this->joy_msg = *msg;

    // joystick control
    // Description of buttons and axes(F710):
    // |__ buttons[]: A=0, B=1, X=2, Y=3, LB=4, RB=5, back=6, start=7, power=8, stickL=9, stickR=10
    // |__ axes[]: Lx=0, Ly=1, Rx=3, Ry=4, LT=2, RT=5
    if (this->joy_msg.buttons[5])
    {
        if (this->joy_msg.buttons[3]) // RB+Y
        {
            this->control.SetControlState(STATE_POS_GETUP);
        }
        else if (this->joy_msg.buttons[0]) // RB+A
        {
            this->control.SetControlState(STATE_POS_GETDOWN);
        }
        else if (this->joy_msg.buttons[1]) // RB+B
        {
            this->control.SetControlState(STATE_RL_LOCOMOTION);
        }
        else if (this->joy_msg.buttons[2]) // RB+X
        {
            this->control.SetControlState(STATE_RESET_SIMULATION);
        }
        else if (this->joy_msg.axes[7] < 0) // DOWN
        {
            this->control.SetControlState(STATE_RL_NAVIGATION);
        }
    }
    if (this->joy_msg.buttons[4]) // LB
    {
        this->control.SetControlState(STATE_TOGGLE_SIMULATION);
    }

    this->control.x = this->joy_msg.axes[1] * 1.5; // Ly
    this->control.y = this->joy_msg.axes[0] * 1.5; // Lx
    this->control.yaw = this->joy_msg.axes[3] * 1.5; // Rx
    
    //  if (this->joy_msg.axes[1] == 0.0 && this->joy_msg.axes[0] == 0.0 && this->joy_msg.axes[3] == 0.0)
    // {
    //     this->control.x = 0.0;
    //     this->control.y = 0.0;
    //     this->control.yaw = 0.0;
    // }
    // else
    // {
    //     this->control.x = this->joy_msg.axes[1] * 1.5; // Ly
    //     this->control.y = this->joy_msg.axes[0] * 1.5; // Lx
    //     this->control.yaw = this->joy_msg.axes[3] * 1.5; // Rx
    // }
}

void RL_Sim::JointStatesCallback(const robot_msgs::LowlevelState::ConstPtr &msg)
{
    for (int i = 0; i < this->params.num_of_dofs; ++i)
    {
        const auto& motor_state = msg->motorState[i];
        const std::string& joint_name = params.joint_controller_names[i];

        // 直接根据索引更新关节状态
        joint_positions[joint_name] = motor_state.q;
        joint_velocities[joint_name] = motor_state.dq;
        joint_efforts[joint_name] = motor_state.tau;
        // std::cout << "[JointStatesCallback] received " << msg->motorState.size() << " motors\n";
    }
}

void RL_Sim::RunModel()
{
    // if (this->rl_init_done && simulation_running)
    if (this->rl_init_done )
    {
        this->episode_length_buf += 1;
        //待改
        this->obs.lin_vel = torch::tensor({{this->vel.linear.x, this->vel.linear.y, this->vel.linear.z}});
        this->obs.ang_vel = torch::tensor(this->robot_state.imu.gyroscope).unsqueeze(0);
        // if (this->fsm._currentState->getStateName() == "RLFSMStateRL_Navigation")
        // {
        //     this->obs.commands = torch::tensor({{this->cmd_vel.linear.x, this->cmd_vel.linear.y, this->cmd_vel.angular.z}});
        // }
        // else
        // {
        //     this->obs.commands = torch::tensor({{this->control.x, this->control.y, this->control.yaw}});
        // }
        this->obs.commands = torch::tensor({{this->control.x, this->control.y, this->control.yaw}});
        std::cout << "\r" << std::flush << LOGGER::INFO << "RL111 Controller x:" << this->control.x << " y:" << this->control.y << " yaw:" << this->control.yaw << std::flush;
        //
        this->obs.base_quat = torch::tensor(this->robot_state.imu.quaternion).unsqueeze(0);
        this->obs.dof_pos = torch::tensor(this->robot_state.motor_state.q).narrow(0, 0, this->params.num_of_dofs).unsqueeze(0);
        this->obs.dof_vel = torch::tensor(this->robot_state.motor_state.dq).narrow(0, 0, this->params.num_of_dofs).unsqueeze(0);

        this->obs.actions = this->Forward();
        this->ComputeOutput(this->obs.actions, this->output_dof_pos, this->output_dof_vel, this->output_dof_tau);

        if (this->output_dof_pos.defined() && this->output_dof_pos.numel() > 0)
        {
            output_dof_pos_queue.push(this->output_dof_pos);
        }
        if (this->output_dof_vel.defined() && this->output_dof_vel.numel() > 0)
        {
            output_dof_vel_queue.push(this->output_dof_vel);
        }
        if (this->output_dof_tau.defined() && this->output_dof_tau.numel() > 0)
        {
            output_dof_tau_queue.push(this->output_dof_tau);
        }

        this->TorqueProtect(this->output_dof_tau);

#ifdef CSV_LOGGER
        torch::Tensor tau_est = torch::zeros({1, this->params.num_of_dofs});
        for (int i = 0; i < this->params.num_of_dofs; ++i)
        {
            tau_est[0][i] = this->joint_efforts[this->params.joint_controller_names[i]];
        }
        this->CSVLogger(this->output_dof_tau, tau_est, this->obs.dof_pos, this->output_dof_pos, this->obs.dof_vel);
#endif
     

    }
}

torch::Tensor RL_Sim::Forward()
{
    torch::autograd::GradMode::set_enabled(false);

    torch::Tensor clamped_obs = this->ComputeObservation();

    torch::Tensor actions;
    if (this->params.observations_history.size() != 0)
    {
        this->history_obs_buf.insert(clamped_obs);
        this->history_obs = this->history_obs_buf.get_obs_vec(this->params.observations_history);
        actions = this->model.forward({this->history_obs}).toTensor();
    }
    else
    {
        actions = this->model.forward({clamped_obs}).toTensor();
    }

    if (this->params.clip_actions_upper.numel() != 0 && this->params.clip_actions_lower.numel() != 0)
    {
        return torch::clamp(actions, this->params.clip_actions_lower, this->params.clip_actions_upper);
    }
    else
    {
        return actions;
    }
}


void RL_Sim::Plot()
 {
     this->plot_t.erase(this->plot_t.begin());
     this->plot_t.push_back(this->motiontime);

     plt::cla();
     plt::clf();

     for (int i = 0; i < this->params.num_of_dofs; ++i)
     {
         this->plot_real_joint_pos[i].erase(this->plot_real_joint_pos[i].begin());
         this->plot_target_joint_pos[i].erase(this->plot_target_joint_pos[i].begin());

         this->plot_real_joint_pos[i].push_back(this->joint_positions[this->params.joint_controller_names[i]]);
        //  this->plot_target_joint_pos[i].push_back(this->lowlevel_cmd[i].q);

         plt::subplot(4, 4, i + 1);
         plt::named_plot("_real_joint_pos", this->plot_t, this->plot_real_joint_pos[i], "r");
         plt::named_plot("_target_joint_pos", this->plot_t, this->plot_target_joint_pos[i], "b");
         double x_start = this->plot_t.front();
         double x_end = this->plot_t.back();
         if (x_start == x_end)
             x_end += 1.0;

        plt::xlim(x_start, x_end);
     }
     plt::pause(0.01);

}


void signalHandler(int signum)
{
    ros::shutdown();
    exit(0);
}

int main(int argc, char **argv)
{
    signal(SIGINT, signalHandler);
    ros::init(argc, argv, "rl_sar");
    RL_Sim rl_sar;
    ros::spin();
    return 0;
}

