#可单取出来
float32[3] ang_vel   # 角速度 wx, wy, wz
float32[3] gravity_vec  
float32[3] commands
float32[16] dof_pos
float32[16] dof_vel
float32[16] actions
#总观测量
float32[57] obs
