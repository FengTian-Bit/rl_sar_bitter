# uint8 mode           # motor target mode
# float32 q            # motor target position
# float32 dq           # motor target velocity
# float32 tau          # motor target torque
# float32 Kp           # motor spring stiffness coefficient
# float32 Kd           # motor damper coefficient
# uint32[3] reserve    # motor target torque

# uint8 mode           # 电机当前模式
uint8 id                # 电机ID
float32 q            # 电机当前位置（弧度）
float32 dq           # 电机当前速度（弧度/秒）
float32 tau          # 当前输出扭矩（牛·米）
#Kp ，Kd，反转参数reverse
float32 Kp
float32 Kd
float32 Kvp
float32 Kvi
#uint8 rv #反转参数
# int8 temperature     # 电机温度（由于温度传导缓慢，存在滞后现象）