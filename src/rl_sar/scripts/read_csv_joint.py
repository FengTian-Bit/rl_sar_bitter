import pandas as pd
import numpy as np
import matplotlib
matplotlib.use('Agg')  # 必须在 pyplot 前导入
import matplotlib.pyplot as plt
import os
from glob import glob

# ========================
# 配置参数
# ========================
# TASK = "standup"
TASK = "rl"
CSV_DIR = f"src/rl_sar/models/bitter/csv_data"
OUTPUT_DIR = f"src/rl_sar/models/bitter/csv_png"
CSV_FILE = os.path.join(CSV_DIR, f"csv_{TASK}.csv")


data_file = CSV_FILE
print(f"正在加载: {data_file}")
df = pd.read_csv(data_file)

# 检查数据行数
max_steps = len(df)
if max_steps == 0:
    raise ValueError("CSV 文件为空！")

# 我们最多画前 500 步，但如果数据不足，就画全部
N = min(500, max_steps)
timesteps = np.arange(N)  # x 轴：0 到 N-1

print(f"CSV 数据共 {max_steps} 行，将绘制前 {N} 步")

# ========================
# 提取列名并排序（按数字顺序）
# ========================
columns = df.columns.str.strip()


def extract_number(col):
    """从列名提取末尾的数字，用于排序"""
    parts = col.split('_')
    try:
        return int(parts[-1])
    except ValueError:
        return -1


# 按数值排序，确保 joint_0, joint_1, ..., joint_10, ... 顺序正确
tau_cal_cols = sorted([col for col in columns if col.startswith("joint_tau_cal_")], key=extract_number)
tau_est_cols = sorted([col for col in columns if col.startswith("joint_tau_est_")], key=extract_number)
pos_cols = sorted([col for col in columns if col.startswith("joint_pos_") and not col.startswith("joint_pos_target_")], key=extract_number)
pos_target_cols = sorted([col for col in columns if col.startswith("joint_pos_target_")], key=extract_number)
vel_cols = sorted([col for col in columns if col.startswith("joint_vel_") and not col.startswith("joint_vel_target_")], key=extract_number)
vel_target_cols = sorted([col for col in columns if col.startswith("joint_vel_target_")], key=extract_number)


def get_joint_id(col):
    return col.split('_')[-1]


# ========================
# 1. 扭矩对比图：16个子图（4x4）
# ========================
n_tau = len(tau_cal_cols)
if n_tau > 0:
    ncols, nrows = 4, 4
    fig, axes = plt.subplots(nrows, ncols, figsize=(18, 14))
    axes = axes.flatten()

    for idx, (cal_col, est_col) in enumerate(zip(tau_cal_cols, tau_est_cols)):
        if idx >= len(axes):
            break
        joint_id = get_joint_id(cal_col)
        
        y1 = df[cal_col][:N].to_numpy()      
        y2 = df[est_col][:N].to_numpy()
        
        axes[idx].plot(timesteps, y1, label="Calculated", linewidth=1.8, alpha=0.8)
        axes[idx].plot(timesteps, y2, linestyle='--', label="Estimated", linewidth=1.8, alpha=0.8)
        axes[idx].set_title(f"Torque Joint {joint_id}", fontsize=10)
        axes[idx].set_ylabel("Torque (Nm)", fontsize=9)
        axes[idx].set_xlabel("Timestep", fontsize=9)
        axes[idx].grid(True, alpha=0.5)
        axes[idx].legend(fontsize='x-small')

    # 隐藏多余子图
    for idx in range(n_tau, len(axes)):
        fig.delaxes(axes[idx])

    plt.suptitle(f"Joint Torque: {TASK}", fontsize=16)
    plt.tight_layout()
    output_image_torque = os.path.join(OUTPUT_DIR, f"csv_{TASK}_torque.png")
    plt.savefig(output_image_torque, dpi=200, bbox_inches='tight')
    plt.close()
    print(f"扭矩子图已保存至: {output_image_torque}")

# ========================
# 2. 位置对比图：12个子图（3x4）
# ========================
n_pos = len(pos_cols)
if n_pos > 0:
    ncols, nrows = 3, 4
    fig, axes = plt.subplots(nrows, ncols, figsize=(18, 12))
    axes = axes.flatten()

    for idx, (pos_col, target_col) in enumerate(zip(pos_cols, pos_target_cols)):
        if idx >= len(axes):
            break
        joint_id = get_joint_id(pos_col)
        
        y1 = df[pos_col][:N].to_numpy()
        y2 = df[target_col][:N].to_numpy()
        
        axes[idx].plot(timesteps, y1, label="Actual", linewidth=1.8, alpha=0.8)
        axes[idx].plot(timesteps, y2, linestyle='--', label="Target", linewidth=1.8, alpha=0.8)
        axes[idx].set_title(f"Position Joint {joint_id}", fontsize=10)
        axes[idx].set_ylabel("Position (rad)", fontsize=9)
        axes[idx].set_xlabel("Timestep", fontsize=9)
        axes[idx].grid(True, alpha=0.5)
        axes[idx].legend(fontsize='x-small')

    for idx in range(n_pos, len(axes)):
        fig.delaxes(axes[idx])

    plt.suptitle(f"Joint Position of Leg: {TASK}", fontsize=16)
    plt.tight_layout()
    output_image_position = os.path.join(OUTPUT_DIR, f"csv_{TASK}_position.png")
    plt.savefig(output_image_position, dpi=200, bbox_inches='tight')
    plt.close()
    print(f"位置子图已保存至: {output_image_position}")

# ========================
# 3. 速度对比图：4个子图（2x2）
# ========================
n_vel = len(vel_cols)
if n_vel > 0:
    ncols, nrows = 2, 2
    fig, axes = plt.subplots(nrows, ncols, figsize=(12, 10))
    axes = axes.flatten()

    for idx, (vel_col, target_col) in enumerate(zip(vel_cols, vel_target_cols)):
        if idx >= len(axes):
            break
        joint_id = get_joint_id(vel_col)
        
        y1 = df[vel_col][:N].to_numpy()
        y2 = df[target_col][:N].to_numpy()
        
        axes[idx].plot(timesteps, y1, label="Actual", linewidth=1.8, alpha=0.9)
        axes[idx].plot(timesteps, y2, linestyle='--', label="Target", linewidth=1.8, alpha=0.9)
        axes[idx].set_title(f"Velocity Joint {joint_id}", fontsize=11)
        axes[idx].set_ylabel("Velocity (rad/s)", fontsize=10)
        axes[idx].set_xlabel("Timestep", fontsize=10)
        axes[idx].grid(True, alpha=0.5)
        axes[idx].legend(fontsize='small')

    for idx in range(n_vel, len(axes)):
        fig.delaxes(axes[idx])

    plt.suptitle(f"Joint Velocity of Leg: {TASK}", fontsize=16)
    plt.tight_layout()
    output_image_velocity = os.path.join(OUTPUT_DIR, f"csv_{TASK}_velocity.png")
    plt.savefig(output_image_velocity, dpi=200, bbox_inches='tight')
    plt.close()
    print(f"速度子图已保存至: {output_image_velocity}")

print(f"✅ 绘图完成！共使用前 {N} 个时间步的数据。")