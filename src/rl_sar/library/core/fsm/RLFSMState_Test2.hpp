/*
 * 
 * 2025.09.19
 */

#ifndef RLFSMSTATE_TEST2_HPP
#define RLFSMSTATE_TEST2_HPP

#include "fsm.hpp"
#include "rl_sdk.hpp"
#include "robot_msgs/Observation.h"
#include <ros/ros.h>

class RLFSMState_Test2 : public RLFSMState
{
public:
    RLFSMState_Test2(RL& rl, const RobotState<double>* state, RobotCommand<double>* command);

    ~RLFSMState_Test2() override;

    void enter() override;
    void run() override;
    void exit() override;
    std::string checkChange() override;

private:
    int count;
    // torch::Tensor clamped_obs;
    // robot_msgs::Observation obs_msg;
    ros::Publisher pub_obs;

};

#endif // RLFSMSTATE_TEST2_HPP
