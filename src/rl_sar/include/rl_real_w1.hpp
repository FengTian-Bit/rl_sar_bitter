/*
 * 2025-09-25 田丰
 */

#ifndef RL_REAL_W1_HPP
#define RL_REAL_W1_HPP

// #define PLOT
// #define CSV_LOGGER

#include "rl_sdk.hpp"
#include "observation_buffer.hpp"
#include "loop.hpp"
#include <csignal>
#include <unistd.h>

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>
#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <algorithm>
#include <Eigen/Dense>
#include "limxsdk/wheellegged.h"
#include "common/util.h"
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;



class RL_Real : public RL
{
public:
    RL_Real();
    ~RL_Real();

private:
    // rl functions
    torch::Tensor Forward() override;
    void GetState(RobotState<double> *state) override;
    void SetCommand(const RobotCommand<double> *command) override;
    void RunModel();
    void RobotControl();

    // loop
    std::shared_ptr<LoopFunc> loop_keyboard;
    std::shared_ptr<LoopFunc> loop_control;
    std::shared_ptr<LoopFunc> loop_rl;
    std::shared_ptr<LoopFunc> loop_plot;

    // plot
    const int plot_size = 100;
    std::vector<int> plot_t;
    std::vector<std::vector<double>> plot_real_joint_pos, plot_target_joint_pos;
    void Plot();

    // w1 interface
    void InitRobotStateClient(std::string robot_ip); // 初始化w1状态客户端
    void InitLowCmd(int num_of_dofs); // 初始化w1 电机命令

    limxsdk::Wheellegged *rsc;    // Pointer to the WheelLegged object 指向 WheelLegged 对象的指针
    limxsdk::RobotCmd robot_cmd_; // Robot command 机器人命令

    bool recv_{false};            // Flag indicating if data has been received 是否接收到数据的标志,用在state callback里
    double dt_{2e-3};             // Time step 时间步长-控制频率是500Hz
    std::thread th_loop_;             // Thread for control loop 控制循环线程
    std::mutex mtx_;                  // Mutex for thread synchronization 线程同步互斥锁
    
    limxsdk::RobotState robot_state_; // Robot state 机器人状态
    void RobotStateCallback(const limxsdk::RobotStateConstPtr &msg); //机器人状态回调函数

    limxsdk::ImuData imu_data_;       // Robot imu data 机器人imu数据
    void ImuDataCallback(const limxsdk::ImuDataConstPtr &msg);       //imu数据回调函数



    // others
    int motiontime = 0;
    // std::vector<double> mapped_joint_positions;
    // std::vector<double> mapped_joint_velocities;
    int command_mapping[16] = {0, 1, 2, 3, 8, 9, 10, 11, 4, 5, 6, 7, 12, 13, 14, 15};
    int state_mapping[16] = {0, 1, 2, 3, 8, 9, 10, 11, 4, 5, 6, 7, 12, 13, 14, 15};

    
    // ros
    geometry_msgs::Twist cmd_vel;
    sensor_msgs::Joy joy_msg;
    ros::Subscriber cmd_vel_subscriber;
    ros::Subscriber joy_subscriber;
    void CmdvelCallback(const geometry_msgs::Twist::ConstPtr &msg);
    void JoyCallback(const sensor_msgs::Joy::ConstPtr &msg);

};

#endif // RL_REAL_W1_HPP
