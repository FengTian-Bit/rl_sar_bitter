/**
 * @file wl_controller_base.cpp
 * @brief Implementation of the base controller for a wheel-legged robot. 
 * @version 1.0
 * @date 2023-12-11
 *
 * © [2023] LimX Dynamics Technology Co., Ltd. All rights reserved. 保留所有权利
 *
 */

#include "wl_controller_base.h"

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

/**
 * @brief Constructor for the ControllerBase class. 
 * Initializes the robot command message and subscribes to robot state updates. 初始化机器人命令消息并订阅机器人状态更新。
 */
ControllerBase::ControllerBase()
    : robot_cmd_(16) // Assuming 16 is the size of robot command data 假设机器人命令数据的大小为16
    , robot_state_(16) // Assuming 16 is the size of robot state data 假设机器人状态数据的大小为16
{
  wl_ = limxsdk::Wheellegged::getInstance(); // Get instance of the WheelLegged class 获取 WheelLegged 类的实例

  loadParameters(); // Load controller parameters 加载控制器参数

  // Subscribe to robot state updates and bind the callback function 订阅机器人状态更新并绑定回调函数
  wl_->subscribeRobotState(std::bind(&ControllerBase::robotStateCallback, this, std::placeholders::_1));

  // Subscribe to robot imu data updates and bind the callback function 订阅机器人 imu 数据更新并绑定回调函数
  wl_->subscribeImuData(std::bind(&ControllerBase::imuDataCallback, this, std::placeholders::_1));
}

/**
 * @brief Destructor for the ControllerBase class. 析构函数
 */
ControllerBase::~ControllerBase()
{
}

/**
 * @brief Starts the control loop in a separate thread. 启动控制循环线程
 */
void ControllerBase::startLoop()
{
  // Define the control loop function 定义控制循环函数
  auto loop = [&]()
  {
    std::chrono::time_point<std::chrono::steady_clock> tp;
    tp = std::chrono::steady_clock::now(); //获得当前时间
    while (true)
    {
      update(); // Call the update function 调用更新函数，可以，非常简洁
      tp += std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::duration<double>(dt_)); //0.5ms
      std::this_thread::sleep_until(tp); // Sleep until the next control cycle 休眠直到下一个控制周期
    }
  };
  th_loop_ = std::thread(loop); // Start the control loop thread 启动控制循环线程
}

/**
 * @brief Loads controller parameters such as joint offsets, gains, and reference positions. 加载控制器参数，如关节偏移、增益和参考位置。
 */
void ControllerBase::loadParameters()
{
  // Set default proportional gains for position control 设置默认比例增益Kp用于位置控制
  joint_kp_.resize(robot_cmd_.Kp.size());
  joint_kp_ = Eigen::VectorXd::Constant(robot_cmd_.Kp.size(), 600); //600

  // Set default derivative gains for position control 设置默认速度增益Kd用于位置控制
  joint_kd_.resize(robot_cmd_.Kd.size());
  joint_kd_ = Eigen::VectorXd::Constant(robot_cmd_.Kd.size(), 4.5); //4.5

  // Set default damping gains 设置阻尼模式
  damping_kd_.resize(robot_cmd_.Kd.size());
  damping_kd_ << 4.5, 4.5, 4.5, 0.6,
      4.5, 4.5, 4.5, 0.6,
      4.5, 4.5, 4.5, 0.6,
      4.5, 4.5, 4.5, 0.6;

  // Set default home position 设置默认home位置
  home_q_.resize(robot_cmd_.q.size());
  home_q_ << 0.5, 1.3, 0, 0,
      0.5, 1.3, 0, 0,
      -0.5, 1.3, 0, 0,
      -0.5, 1.3, 0, 0;

  // Set default standing position 设置默认站立位置
  stand_q_.resize(robot_cmd_.q.size());
  stand_q_ << 0, -0.6, 0.6, 0,
      0, -0.6, 0.6, 0,
      0, -0.6, 0.6, 0,
      0, -0.6, 0.6, 0;
}

/**
 * @brief Sets all joint torques to zero. 将所有关节扭矩设置为零。
 */
void ControllerBase::zeroTorque()
{
  std::fill(robot_cmd_.dq.begin(), robot_cmd_.dq.end(), 0);
  std::fill(robot_cmd_.tau.begin(), robot_cmd_.tau.end(), 0);
  std::fill(robot_cmd_.Kp.begin(), robot_cmd_.Kp.end(), 0);
  std::fill(robot_cmd_.Kd.begin(), robot_cmd_.Kd.end(), 0);
  publish(robot_cmd_); // Publish the zero torque command 发布零扭矩命令
}

/**
 * @brief Applies damping control to the joints. 应用阻尼控制到关节。
 */
void ControllerBase::damping()
{
  std::fill(robot_cmd_.dq.begin(), robot_cmd_.dq.end(), 0);
  std::fill(robot_cmd_.Kp.begin(), robot_cmd_.Kp.end(), 0);
  robot_cmd_.Kd.assign(damping_kd_.data(), damping_kd_.data() + damping_kd_.size());
  publish(robot_cmd_); // Publish the damping control command 发布阻尼控制命令
}

/**
 * @brief Moves the robot to its home position at a given velocity. 以指定速度移动到home位置。
 * @param v Velocity of the movement. 移动速度。
 */
void ControllerBase::homing(double v)
{
  Eigen::VectorXd q(robot_cmd_.q.size());
  for (uint16_t i = 0; i < q.size(); i++)
  {
    q[i] = robotState().q[i];
  }
  goPos(q, home_q_, v, dt_); // Move to the home position 移动到home位置
  damping();                 // Apply damping control 应用阻尼控制
}

/**
 * @brief Moves the robot to its standing position at a given velocity. 以指定速度移动到站立位置。
 * @param v Velocity of the movement.
 */
void ControllerBase::standing(double v)
{
  Eigen::VectorXd q(robot_cmd_.q.size());
  for (uint16_t i = 0; i < q.size(); i++)
  {
    q[i] = robotState().q[i];
  }
  goPos(q, stand_q_, v, dt_); // Move to the standing position 移动到站立位置
}

/**
 * @brief Makes the robot sit down at a given velocity.
 * @param v Velocity of the movement.
 */
void ControllerBase::sitDown(double v)
{
  homing(v); // Sit down by moving to the home position
}

/**
 * @brief Calculates the position using a cosine interpolation.
 * @param start Starting position.
 * @param stop Ending position.
 * @param T Time period.
 * @param t Current time.
 * @return Interpolated position.
 */
double ControllerBase::calcCos(double start, double stop, double T, double t) const
{
  double A = (stop - start) / 2.0;
  return A * -cos(M_PI / T * t) + start + A;
}

/**
 * @brief Moves the robot joints to a desired position using cosine interpolation.
 * @param q Current joint positions.
 * @param q_d Desired joint positions.
 * @param speed Movement speed.
 * @param dt Time step.
 */
void ControllerBase::goPos(const Eigen::VectorXd q, const Eigen::VectorXd q_d, double speed, double dt)
{
  Eigen::VectorXd duration = (q_d - q) / speed;
  double t_max = duration.maxCoeff();
  if (t_max < 0.5)
  {
    t_max = 0.5;
  }

  double t = 0;
  std::chrono::time_point<std::chrono::steady_clock> tp;
  tp = std::chrono::steady_clock::now();
  while (true)
  {
    for (uint16_t i = 0; i < q.size(); i++)
    {
      robot_cmd_.q[i] = calcCos(q[i], q_d[i], t_max, t);
      robot_cmd_.Kp[i] = joint_kp_[i];
      robot_cmd_.Kd[i] = joint_kd_[i];
    }
    publish(robot_cmd_); // Publish the interpolated joint positions

    t += dt;
    if (t >= t_max)
    {
      return;
    }

    tp += std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::duration<double>(dt));
    std::this_thread::sleep_until(tp); // Sleep until the next time step
  }
}

/**
 * @brief Retrieves the current robot state.
 * @return Current robot state.
 */
limxsdk::RobotState ControllerBase::robotState()
{
  limxsdk::RobotState state;
  mtx_.lock();
  state = robot_state_;
  mtx_.unlock();
  return state;
}

/**
 * @brief Retrieves the current imu.
 * @return Current imu.
 */
limxsdk::ImuData ControllerBase::imuData()
{
  limxsdk::ImuData imu;
  mtx_.lock();
  imu = imu_data_;
  mtx_.unlock();
  return imu;
}

/**
 * @brief Publishes the robot command message after adjusting joint offsets.
 * @param msg Robot command message.
 */
void ControllerBase::publish(limxsdk::RobotCmd &msg)
{
  for (uint16_t i = 0; i < msg.q.size(); i++)
  {
    msg.q[i] = msg.q[i];
  }
  wl_->publishRobotCmd(msg); // Publish the adjusted robot command message
}

/**
 * @brief Callback function for receiving robot state updates.
 * Adjusts joint offsets and updates the robot state.
 * @param msg Pointer to the received robot state message.
 */
void ControllerBase::robotStateCallback(const limxsdk::RobotStateConstPtr &msg)
{
  mtx_.lock();
  robot_state_ = *msg;
  for (uint16_t i = 0; i < msg->q.size(); i++)
  {
    robot_state_.q[i] = msg->q[i];
  }
  mtx_.unlock();
  if (!recv_)
  {
    recv_ = true;
  }
}

/**
 * @brief Callback function for receiving imu updates.
 * Adjusts joint offsets and updates the imu.
 * @param msg Pointer to the received imu.
 */
void ControllerBase::imuDataCallback(const limxsdk::ImuDataConstPtr &msg)
{
  mtx_.lock();
  imu_data_ = *msg;
  mtx_.unlock();
}
