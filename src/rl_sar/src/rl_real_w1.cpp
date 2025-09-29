/*
 * 2025-09-25 田丰
 */

#include "rl_real_w1.hpp"

int tick_tick_state=0;
int tick_tick_command=0;

RL_Real::RL_Real()
{

    // init ros
    ros::NodeHandle nh;
    this->cmd_vel_subscriber = nh.subscribe<geometry_msgs::Twist>("/cmd_vel", 10, &RL_Real::CmdvelCallback, this); //暂时没用到

    this->robot_name = "w1";
    this->default_rl_config = "robot_lab";

    this->ReadYamlBase(this->robot_name);
    
    std::string robot_ip = "192.168.1.2";  // 10.192.1.2  192.168.1.2
    // init robot
    this->InitRobotStateClient(robot_ip); // 自创的w1 init 函数

    // init torch
    torch::autograd::GradMode::set_enabled(false);
    torch::set_num_threads(4);

    // init robot
    this->InitLowCmd(this->params.num_of_dofs);
    this->InitOutputs();
    this->InitControl();

    this->csv_filename_standup = std::string(CMAKE_CURRENT_SOURCE_DIR) + "/models/"+ this->robot_name+"/csv_data/csv_standup.csv";
    this->csv_filename_rl = std::string(CMAKE_CURRENT_SOURCE_DIR) + "/models/"+ this->robot_name+"/csv_data/csv_rl.csv";
    this->csv_filename_obs = std::string(CMAKE_CURRENT_SOURCE_DIR) + "/models/"+ this->robot_name+"/csv_data/csv_obs.csv";

    this->CSVInitJOINT(this->csv_filename_standup, this->robot_name);
    this->CSVInitJOINT(this->csv_filename_rl, this->robot_name);
    this->CSVInitOBS(this->csv_filename_obs, this->robot_name);

    // Subscribe to robot state updates and bind the callback function 订阅机器人状态更新并绑定回调函数
    this->rsc->subscribeRobotState(std::bind(&RL_Real::RobotStateCallback, this, std::placeholders::_1));
    // Subscribe to robot imu data updates and bind the callback function 订阅机器人 imu 数据更新并绑定回调函数
    this->rsc->subscribeImuData(std::bind(&RL_Real::ImuDataCallback, this, std::placeholders::_1));

    // loop
    this->loop_keyboard = std::make_shared<LoopFunc>("loop_keyboard", 0.05, std::bind(&RL_Real::KeyboardInterface, this));
    this->loop_control = std::make_shared<LoopFunc>("loop_control", this->params.dt, std::bind(&RL_Real::RobotControl, this));
    this->loop_rl = std::make_shared<LoopFunc>("loop_rl", this->params.dt * this->params.decimation, std::bind(&RL_Real::RunModel, this));
    this->loop_keyboard->start();
    this->loop_control->start();
    this->loop_rl->start();

#ifdef PLOT
    this->plot_t = std::vector<int>(this->plot_size, 0);
    this->plot_real_joint_pos.resize(this->params.num_of_dofs);
    this->plot_target_joint_pos.resize(this->params.num_of_dofs);
    for (auto &vector : this->plot_real_joint_pos) { vector = std::vector<double>(this->plot_size, 0); }
    for (auto &vector : this->plot_target_joint_pos) { vector = std::vector<double>(this->plot_size, 0); }
    this->loop_plot = std::make_shared<LoopFunc>("loop_plot", 0.002, std::bind(&RL_Real::Plot, this));
    this->loop_plot->start();
#endif
#ifdef CSV_LOGGER
    this->CSVInit(this->robot_name);
#endif
}

RL_Real::~RL_Real()
{
    this->loop_keyboard->shutdown();
    this->loop_control->shutdown();
    this->loop_rl->shutdown();
#ifdef PLOT
    this->loop_plot->shutdown();
#endif
    std::cout << LOGGER::INFO << "RL_Real exit" << std::endl;
}

void RL_Real::GetState(RobotState<double> *state)
{
    // this->control.x = this->joystick.ly();
    // this->control.y = -this->joystick.lx();
    // this->control.yaw = -this->joystick.rx();

    // if ((int)this->unitree_joy.components.R2 == 1)
    // {
    //     this->control.SetControlState(STATE_POS_GETUP);
    // }
    // else if ((int)this->unitree_joy.components.R1 == 1)
    // {
    //     this->control.SetControlState(STATE_RL_LOCOMOTION);
    // }
    // else if ((int)this->unitree_joy.components.L2 == 1)
    // {
    //     this->control.SetControlState(STATE_POS_GETDOWN);
    // }

    if (this->params.framework == "isaacgym")
    {
        state->imu.quaternion[3] = this->imu_data_.quat[0]; // w
        state->imu.quaternion[0] = this->imu_data_.quat[1]; // x
        state->imu.quaternion[1] = this->imu_data_.quat[2]; // y
        state->imu.quaternion[2] = this->imu_data_.quat[3]; // z
    }
    else if (this->params.framework == "isaacsim")
    {
        state->imu.quaternion[0] = this->imu_data_.quat[0]; // w
        state->imu.quaternion[1] = this->imu_data_.quat[1]; // x
        state->imu.quaternion[2] = this->imu_data_.quat[2]; // y
        state->imu.quaternion[3] = this->imu_data_.quat[3]; // z
    }

    for (int i = 0; i < 3; ++i)
    {
        state->imu.gyroscope[i] = this->imu_data_.gyro[i];
    }
    for (int i = 0; i < this->params.num_of_dofs; ++i)
    {
        state->motor_state.q[i] = this->robot_state_.q[state_mapping[i]];
        state->motor_state.dq[i] = this->robot_state_.dq[state_mapping[i]];
        state->motor_state.tau_est[i] = this->robot_state_.tau[state_mapping[i]];
    }

    tick_tick_state++;
    if(tick_tick_state> 250) // 每100次循环打印一次状态 500是2.5s
    {
        tick_tick_state = 0; // 重置计时器
        std::cout<<std::endl<< " GetState finish. " << std::endl;
        for (int i = 0; i < this->params.num_of_dofs; ++i) {
            float q = state->motor_state.q[i];
            float dq = state->motor_state.dq[i];
            float tor = state->motor_state.tau_est[i];
            std::cout << std::fixed << std::setprecision(4)
                      << " | Motor: " << std::setw(2) << i
                      << " | Pos: " << std::setw(8) << q
                      << " | Vel: " << std::setw(8) << dq
                      << " | Torque: " << std::setw(8) << tor
                      << " | Torque: " << std::setw(8) << tor
                      << std::endl;
            
        }

        //角速度
        // std::cout<<"角速度 imu.gyroscope x:"<<this->imu_data_.gyro[0]<<std::endl;
        // std::cout<<"角速度 imu.gyroscope y:"<<this->imu_data_.gyro[1]<<std::endl;
        // std::cout<<"角速度 imu.gyroscope z:"<<this->imu_data_.gyro[2]<<std::endl;
        //加速度
        // std::cout<<"linear加速度 imu.acc x"<<this->imu_data_.acc[0]<<std::endl;
        // std::cout<<"linear加速度 imu.acc y"<<this->imu_data_.acc[1]<<std::endl;
        // std::cout<<"linear加速度 imu.acc z"<<this->imu_data_.acc[2]<<std::endl;

    }

}

void RL_Real::SetCommand(const RobotCommand<double> *command)
{   
    robot_cmd_.resize(this->params.num_of_dofs);
    static const int map[4] = {0, 2, 1, 3};
    for (int i = 0; i < this->params.num_of_dofs; ++i)
    {
        this->robot_cmd_.mode[i] = 0;
        this->robot_cmd_.q[i] = command->motor_command.q[command_mapping[i]];
        this->robot_cmd_.dq[i] = command->motor_command.dq[command_mapping[i]];
        this->robot_cmd_.Kp[i] = command->motor_command.kp[command_mapping[i]];
        this->robot_cmd_.Kd[i] = command->motor_command.kd[command_mapping[i]];
        this->robot_cmd_.tau[i] = command->motor_command.tau[command_mapping[i]];
    }
    this->rsc->publishRobotCmd(robot_cmd_);

    //
    // tick_tick_command++;
    // if(tick_tick_command> 500) // 每100次循环打印一次状态
    // {
    //     tick_tick_command = 0; // 重置计时器
    //     std::cout<<std::endl<< " SetCommand finish. " << std::endl;
    //     for (int i = 0; i < this->params.num_of_dofs; ++i) {
    //         float q = command->motor_command.q[i];
    //         float dq = command->motor_command.dq[i];
    //         float tor = command->motor_command.tau[i];
    //         std::cout << std::fixed << std::setprecision(4)
    //                   << " | Motor: " << std::setw(2) << i
    //                   << " | Pos: " << std::setw(8) << q
    //                   << " | Vel: " << std::setw(8) << dq
    //                   << " | Torque: " << std::setw(8) << tor
    //                   << std::endl;
            
    //     }
    // }
    //
}

void RL_Real::RobotControl()
{
    this->motiontime++;

    this->GetState(&this->robot_state);
    this->StateController(&this->robot_state, &this->robot_command);
    this->SetCommand(&this->robot_command);
}

void RL_Real::RunModel()
{
    if (this->rl_init_done)
    {
        this->episode_length_buf += 1;
        this->obs.ang_vel = torch::tensor(this->robot_state.imu.gyroscope).unsqueeze(0);
        if (this->fsm._currentState->getStateName() == "RLFSMStateRL_Navigation")
        {
#ifdef USE_ROS
            this->obs.commands = torch::tensor({{this->cmd_vel.linear.x, this->cmd_vel.linear.y, this->cmd_vel.angular.z}});
#endif
        }
        else
        {
            this->obs.commands = torch::tensor({{this->control.x, this->control.y, this->control.yaw}});
        }
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

        // this->TorqueProtect(this->output_dof_tau);
        // this->AttitudeProtect(this->robot_state.imu.quaternion, 75.0f, 75.0f);

#ifdef CSV_LOGGER
        torch::Tensor tau_est = torch::tensor(this->robot_state.motor_state.tau_est).unsqueeze(0);
        this->CSVLogger(this->output_dof_tau, tau_est, this->obs.dof_pos, this->output_dof_pos, this->obs.dof_vel);
#endif
        std::cout << "Control commands: x=" << this->control.x 
                << ", y=" << this->control.y 
                << ", yaw=" << this->control.yaw << std::endl;
    }
}

torch::Tensor RL_Real::Forward()
{
    torch::autograd::GradMode::set_enabled(false);

    torch::Tensor clamped_obs = this->ComputeObservation();

    torch::Tensor actions;
    if (!this->params.observations_history.empty())
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

void RL_Real::Plot()
{
    this->plot_t.erase(this->plot_t.begin());
    this->plot_t.push_back(this->motiontime);
    plt::cla();
    plt::clf();
    for (int i = 0; i < this->params.num_of_dofs; ++i)
    {
        this->plot_real_joint_pos[i].erase(this->plot_real_joint_pos[i].begin());
        this->plot_target_joint_pos[i].erase(this->plot_target_joint_pos[i].begin());
        this->plot_real_joint_pos[i].push_back(this->robot_state_.q[i]);
        this->plot_target_joint_pos[i].push_back(this->robot_cmd_.q[i]);
        plt::subplot(4, 3, i + 1);
        plt::named_plot("_real_joint_pos", this->plot_t, this->plot_real_joint_pos[i], "r");
        plt::named_plot("_target_joint_pos", this->plot_t, this->plot_target_joint_pos[i], "b");
        plt::xlim(this->plot_t.front(), this->plot_t.back());
    }
    // plt::legend();
    plt::pause(0.0001);
}


void RL_Real::InitLowCmd(int num_of_dofs)
{
    this->robot_cmd_ = limxsdk::RobotCmd(num_of_dofs);
    this->robot_state_ = limxsdk::RobotState(num_of_dofs);
    for (uint16_t i = 0; i < this->robot_cmd_.q.size(); i++)
    {
      this->robot_cmd_.q[i] = 0;
      this->robot_cmd_.dq[i] = 0;
      this->robot_cmd_.Kp[i] = 0;
      this->robot_cmd_.Kd[i] = 0;
      this->robot_cmd_.tau[i]=0;
    }
}

void RL_Real::InitRobotStateClient(std::string robot_ip)
{   
    this->rsc = limxsdk::Wheellegged::getInstance();       
    if (!this->rsc->init(robot_ip))
    {
        exit(1); // Exit if initialization fails
    }

    //校准状态
    // bool is_calibration = false;
    // Subscribing to diagnostic values for calibration state
    // this->rsc->subscribeDiagnosticValue([&](const limxsdk::DiagnosticValueConstPtr& msg) {
    // // Check if the diagnostic message pertains to calibration
    // if (msg->name == "calibration") {
    //   if (msg->code == 0) {
    //     is_calibration = true;
    //   }
    //   std::cout<<"code: "<<is_calibration<<std::endl;
    // }
    // std::cout<<msg->name<<std::endl;
    // });

    // std::cout<<this->rsc->getMotorNumber()<<std::endl;
    // this->rsc->subscribeRobotState(std::bind(&RL_Real::RobotStateCallback, this, std::placeholders::_1));
    // std::cout << "Waitting calibration begin." << std::endl;
    // while(!is_calibration) {
    //     std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    // }
    // std::cout << "Waitting calibration end." << std::endl;
    //结束校准
}

void RL_Real::ImuDataCallback(const limxsdk::ImuDataConstPtr &msg)
{
  mtx_.lock();
  imu_data_ = *msg;
  mtx_.unlock();
}

void RL_Real::RobotStateCallback(const limxsdk::RobotStateConstPtr &msg)
{
  mtx_.lock();
  robot_state_ = *msg; //这里赋值了
  for (uint16_t i = 0; i < msg->q.size(); i++) 
  {
    robot_state_.q[i] = msg->q[i];
    // std::cout<<"joint "<< i<<": "<<robot_state_.q[i]<<std::endl;
  }
  mtx_.unlock();
//   if (!recv_)
//   {
//     recv_ = true;
//   }
}

void RL_Real::CmdvelCallback(const geometry_msgs::Twist::ConstPtr &msg)
{
    this->cmd_vel = *msg;
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
    // 启动rl
    RL_Real rl_sar;

    // ros::spin(); //有ros就用事件驱动

    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }

    return 0;
}
