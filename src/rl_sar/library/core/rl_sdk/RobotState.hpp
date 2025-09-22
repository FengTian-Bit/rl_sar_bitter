#ifndef ROBOT_STATE_HPP
#define ROBOT_STATE_HPP

#include <vector>


template <typename T>
struct RobotState
{
    struct IMU
    {
        std::vector<T> quaternion = {1.0, 0.0, 0.0, 0.0}; // w, x, y, z
        std::vector<T> gyroscope = {0.0, 0.0, 0.0};
        std::vector<T> accelerometer = {0.0, 0.0, 0.0};
    } imu;

    struct MotorState
    {
        std::vector<T> q = std::vector<T>(32, 0.0);
        std::vector<T> dq = std::vector<T>(32, 0.0);
        std::vector<T> ddq = std::vector<T>(32, 0.0);
        std::vector<T> tau_est = std::vector<T>(32, 0.0);
        std::vector<T> cur = std::vector<T>(32, 0.0);
    } motor_state;
};

#endif // ROBOT_STATE_HPP