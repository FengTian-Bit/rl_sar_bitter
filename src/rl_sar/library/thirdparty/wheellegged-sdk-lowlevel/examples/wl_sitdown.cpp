/**
 * @file wheel_legged_sitdown.cpp
 *
 * @brief This file contains the implementation of the WLSitDown class, which initiates the sit-down behavior of wheel-legged robots.
 *
 * © [2023] LimX Dynamics Technology Co., Ltd. All rights reserved.
 */

#include "wl_controller_base.h"

/**
 * @brief The WLSitDown class controls the sit-down behavior of wheel-legged robots.
 */
class WLSitDown : public ControllerBase
{
public:
  /**
   * @brief Overrides waits for data reception and then initiates the sit-down behavior.
   */
  void starting() override
  {
    std::cout << "Waiting to receive data...\n";
    while (!recv_)
    {
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    std::cout << "Received\n";

    sitDown(); // Initiates the sit-down behavior
  }

private:
  /**
   * @brief Overrides the update function to do nothing, as the sit-down behavior does not require continuous updates.
   */
  void update() override
  {
    // No update needed for sit-down behavior
  }
};

/**
 * @brief The main function initializes the WheelLegged instance, creates an instance of WLSitDown, and starts the sit-down behavior.
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

  // // Subscribing to diagnostic values for calibration state
  // wl->subscribeDiagnosticValue([&](const limxsdk::DiagnosticValueConstPtr& msg) {
  //   // Check if the diagnostic message pertains to calibration
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

  WLSitDown ctl;
  ctl.starting(); // Start the sit-down behavior

  // Main loop
  while (true)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  return 0;
}
