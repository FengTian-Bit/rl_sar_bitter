#时间戳
std_msgs/Header stamp
# uint8 mode           # 电机当前模式
uint8 id                # 电机ID
float32 q            # 电机当前位置（弧度）
float32 dq           # 电机当前速度（弧度/秒）
float32 tau          # 当前输出扭矩（牛·米）
#Kp ，Kd，反转参数reverse
float32 Kp
float32 Kd
#uint8 rv


