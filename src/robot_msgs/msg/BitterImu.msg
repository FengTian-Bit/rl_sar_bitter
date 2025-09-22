# 自定义IMU消息格式
Header header # ROS标准消息头

# 四元数姿态 (x, y, z, w)
float64[4] quat

# 角速度 (单位: rad/s)
float64[3] angular_vel_local

# 线性加速度 (单位: m/s²)
float64[3] linear_acc_local

# 协方差矩阵 (3x3, 按行优先展开)
float64[9] orientation_cov # 姿态协方差
float64[9] angular_vel_cov # 角速度协方差
float64[9] linear_acc_cov # 加速度协方差