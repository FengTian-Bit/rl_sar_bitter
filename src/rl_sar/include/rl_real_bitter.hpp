/*
 * zyl
 * 
 */

#ifndef RL_SIM_HPP
#define RL_SIM_HPP

#include "rl_sdk.hpp"
#include "observation_buffer.hpp"
#include "loop.hpp"
#include <csignal>

#include <ros/ros.h>
#include "std_srvs/Empty.h"
#include <sensor_msgs/Joy.h>
#include <geometry_msgs/Twist.h>
#include <gazebo_msgs/ModelStates.h>
#include <gazebo_msgs/SetModelState.h>
#include "robot_msgs/MotorCommand.h"
#include "robot_msgs/MotorState.h"
// #include "robot_msgs/IMU.h"
#include "robot_msgs/BitterImu.h"
#include "matplotlibcpp.h"
#include "robot_msgs/LowlevelCmd.h"
#include "robot_msgs/LowlevelState.h"

namespace plt = matplotlibcpp;

class RL_Sim : public RL
{
public:
    RL_Sim();
    ~RL_Sim();

private:
    // rl functions
    std::ofstream log_file;
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

    // ros interface
    std::string ros_namespace;
    geometry_msgs::Twist vel;
    geometry_msgs::Pose pose;
    geometry_msgs::Twist cmd_vel;
    sensor_msgs::Joy joy_msg;
    // float quaternion[4];       // 存储四元数
    // float gyroscope[3];        // 存储陀螺仪数据
    // float accelerometer[3];    // 存储加速度计数据
    boost::array<float, 4> quaternion;       // 存储四元数
    boost::array<float, 3> gyroscope;       // 存储陀螺仪数据（角速度）
    boost::array<float, 3> accelerometer;   // 存储加速度计数据（加速度）
    // ros::Subscriber model_state_subscriber;
    ros::Publisher pub_cmd;
    ros::Subscriber imu_state_subscriber;
    ros::Subscriber cmd_vel_subscriber;
    ros::Subscriber motor_state_subscriber;
    ros::Subscriber joy_subscriber;
    ros::ServiceClient gazebo_set_model_state_client;
    ros::ServiceClient gazebo_pause_physics_client;
    ros::ServiceClient gazebo_unpause_physics_client;
    std::map<std::string, ros::Publisher> joint_publishers;
    std::map<std::string, ros::Subscriber> joint_subscribers;
    // std::vector<robot_msgs::MotorCommand> joint_publishers_commands;
    std::vector<robot_msgs::LowlevelCmd> joint_publishers_commands;
    // void ModelStatesCallback(const gazebo_msgs::ModelStates::ConstPtr &msg);
    void ImuCallback(const robot_msgs::BitterImu::ConstPtr &msg);
    // void JointStatesCallback(const robot_msgs::MotorState::ConstPtr &msg, const std::string &joint_name);
    void JointStatesCallback(const robot_msgs::LowlevelState::ConstPtr &msg);
    void CmdvelCallback(const geometry_msgs::Twist::ConstPtr &msg);
    void JoyCallback(const sensor_msgs::Joy::ConstPtr &msg);

    // others
    std::string gazebo_model_name;
    int motiontime = 0;
    std::map<std::string, double> joint_positions;
    std::map<std::string, double> joint_velocities;
    std::map<std::string, double> joint_efforts;
    // std::map<int, std::string> motor_id_to_joint_name;
};

#endif // RL_SIM_HPP
