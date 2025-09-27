/**
 * @file wl_controller_base.h
 * @brief Header file for the base class of the controller.
 * @version 1.0
 * @date 2023-12-11
 *
 * © [2023] LimX Dynamics Technology Co., Ltd. All rights reserved.保留所有权利。
 *
 */
#pragma once

#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <algorithm>
#include <Eigen/Dense>
#include "limxsdk/wheellegged.h"
#include "common/util.h"

/**
 * @brief Base class for the controller. 控制器基类
 *
 */
class ControllerBase
{
public:
  ControllerBase();  // Constructor 构造函数
  ~ControllerBase(); // Destructor 析构函数

protected:
  virtual void starting() = 0; // Virtual function for starting the controller 控制器启动的纯虚函数，派生类必须实现
  virtual void update() = 0;   // Virtual function for updating the controller 控制器更新的纯虚函数，派生类必须实现

  /**
   * @brief Start the control loop. 启动控制循环线程。
   *
   */
  void startLoop();

  /**
   * @brief Load parameters. 加载控制参数（增益、参考位姿等）
   *
   */
  void loadParameters();

  /**
   * @brief Publish zero torque command. 发布“零力矩”指令，让所有关节自由。
   *
   */
  void zeroTorque();

  /**
   * @brief Publish damping command. 发布阻尼控制指令，用于软停机或缓震。
   *
   */
  void damping();

  /**
   * @brief Perform homing. 回零位：以指定平均速度运动到 home 位姿。
   *
   * @param v The average speed of motion. 平均运动速度，默认 1.0。
   */
  void homing(double v = 1.0);

  /**
   * @brief Perform standing. 站立：以指定平均速度运动到站立位姿。
   *
   * @param v The average speed of motion.  平均运动速度，默认 0.3。
   */
  void standing(double v = 0.3);

  /**
   * @brief Perform sitting down. 坐下：以指定平均速度运动到坐下位姿。
   *
   * @param v The average speed of motion.  平均运动速度，默认 0.5。
   */
  void sitDown(double v = 0.5);

  /**
   * @brief Publish a message. 发布消息。
   *
   * @param msg The message to publish. 要发布的消息。
   */
  void publish(limxsdk::RobotCmd &msg);

  /**
   * @brief Get the current robot state. 获取当前机器人状态。
   *
   * @return The current robot state. 当前机器人状态。
   */
  limxsdk::RobotState robotState();

  /**
   * @brief Get the current imu data. 获取当前 imu 数据。
   *
   * @return The current imu data. 当前 imu 数据。
   */
  limxsdk::ImuData imuData();

  /**
   * @brief Move to a specific joint position. 以指定速度和时间步长，平滑地移动到目标关节位置。
   *
   * @param q The target joint positions. 目标关节位置。
   * @param q_d The desired joint positions. 目标关节位置。
   * @param speed The movement speed. 移动速度。
   * @param dt The time step. 时间步长。
   */
  void goPos(const Eigen::VectorXd q, const Eigen::VectorXd q_d, double speed, double dt);

  limxsdk::Wheellegged *wl_;    // Pointer to the WheelLegged object 指向 WheelLegged 对象的指针
  limxsdk::RobotCmd robot_cmd_; // Robot command 机器人命令
  bool recv_{false};            // Flag indicating if data has been received 是否接收到数据的标志
  double dt_{2e-3};             // Time step 时间步长

private:
  double calcCos(double start, double stop, double T, double t) const; 
  void robotStateCallback(const limxsdk::RobotStateConstPtr &msg); //机器人状态回调函数
  void imuDataCallback(const limxsdk::ImuDataConstPtr &msg);       //imu数据回调函数

  limxsdk::RobotState robot_state_; // Robot state 机器人状态
  limxsdk::ImuData imu_data_;       // Robot imu data 机器人imu数据
  std::thread th_loop_;             // Thread for control loop 控制循环线程
  std::mutex mtx_;                  // Mutex for thread synchronization 线程同步互斥锁

  Eigen::VectorXd joint_kp_;     // Proportional gains for joints 关节比例增益
  Eigen::VectorXd joint_kd_;     // Derivative gains for joints 关节微分增益
  Eigen::VectorXd damping_kd_;   // Derivative gains for damping 阻尼微分增益
  Eigen::VectorXd home_q_;       // Home joint positions 回零关节位置
  Eigen::VectorXd stand_q_;      // Standing joint positions 站立关节位置
};
