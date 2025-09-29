/**
 * @file wheel_legged_standup.cpp
 *
 * @brief This file contains the implementation of the WLStandUp class, which initiates the stand-up behavior of wheel-legged robots.
 *
 * © [2023] LimX Dynamics Technology Co., Ltd. All rights reserved.
 */

#include "wl_controller_base.h"

/**
 * @brief The WLStandUp class controls the stand-up behavior of wheel-legged robots.
 */
class WLStandUp : public ControllerBase
{
public:
  /**
   * @brief Overrides waits for data reception and then initiates the stand-up behavior.
   */
  void starting() override
  {
    std::cout << "Waiting to receive data...\n";
    while (!recv_)
    {
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    std::cout << "Received\n";

    homing();                                                    // Move to the home position
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Wait for stability
    standing();                                                  // Initiates the stand-up behavior
  }

private:
  /**
   * @brief Overrides the update function to do nothing, as the stand-up behavior does not require continuous updates.
   */
  void update() override
  {
    // No update needed for stand-up behavior
  }
};

/**
 * @brief The main function initializes the WheelLegged instance, creates an instance of WLStandUp, and starts the stand-up behavior.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return int Program exit status.
 */
int main(int argc, char *argv[])
{
  limxsdk::Wheellegged *wl = limxsdk::Wheellegged::getInstance();

  std::string robot_ip = "127.0.0.1";
  if (argc > 1)
  {
    robot_ip = argv[1];
  }
  if (!wl->init(robot_ip))
  {
    exit(1); // Exit if initialization fails
  }

  // bool is_calibration = false;

  // // Subscribing to diagnostic values for calibration state 订阅诊断值以获取校准状态
  // wl->subscribeDiagnosticValue([&](const limxsdk::DiagnosticValueConstPtr& msg) {
  //   // Check if the diagnostic message pertains to calibration 检查诊断消息是否与校准相关
  //   if (msg->name == "calibration") {
  //     if (msg->code == 0) {
  //       is_calibration = true;
  //     }
  //   }
  // });

  // std::cout << "Waitting calibration begin." << std::endl;
  // while(!is_calibration) {
  //   std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  // }
  // std::cout << "Waitting calibration end." << std::endl;

  WLStandUp ctl;
  ctl.starting(); // Start the stand-up behavior

  // Main loop
  while (true)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  return 0;
}
