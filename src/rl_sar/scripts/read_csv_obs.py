import pandas as pd
import numpy as np
import matplotlib
matplotlib.use('Agg')  # 非交互式后端
import matplotlib.pyplot as plt
import os
from glob import glob

# ========================
# 配置参数
# ========================
TASK = "obs"  # 对应 csv_obs.csv
CSV_DIR = "src/rl_sar/models/bitter_isaacsim/csv_data"
OUTPUT_DIR = "src/rl_sar/models/bitter_isaacsim/csv_png"
CSV_FILE = os.path.join(CSV_DIR, f"csv_{TASK}.csv")

# 创建输出目录
os.makedirs(OUTPUT_DIR, exist_ok=True)

# ========================
# 加载数据
# ========================
if not os.path.exists(CSV_FILE):
    raise FileNotFoundError(f"找不到文件: {CSV_FILE}")

print(f"正在加载: {CSV_FILE}")
df = pd.read_csv(CSV_FILE)

max_steps = len(df)
if max_steps == 0:
    raise ValueError("CSV 文件为空！")

N = min(500, max_steps)  # 最多画前 500 步
timesteps = np.arange(N)
print(f"CSV 数据共 {max_steps} 行，将绘制前 {N} 步")

# ========================
# 1. 角速度、重力、命令 对比图（3x3 子图）
# ========================
fig, axes = plt.subplots(3, 3, figsize=(15, 10))
axes = axes.flatten()

# 定义要画的变量和标题
obs_vars = [
    ("obs_angvel_", "Angular Velocity", "rad/s"),
    ("obs_gravity_", "Gravity", "g"),
    ("obs_command_", "Command", "m/s")
]

for i, (prefix, title, unit) in enumerate(obs_vars):
    for j in range(3):
        col = f"{prefix}{j}"
        if col in df.columns:
            y = df[col][:N].to_numpy()
            axes[i*3 + j].plot(timesteps, y, linewidth=1.8, alpha=0.8)
            axes[i*3 + j].set_title(f"{title} Dim {j}", fontsize=10)
            axes[i*3 + j].set_ylabel(unit, fontsize=9)
            axes[i*3 + j].set_xlabel("Timestep", fontsize=9)
            axes[i*3 + j].grid(True, alpha=0.5)

# 隐藏多余的子图
for idx in range(9, len(axes)):
    fig.delaxes(axes[idx])

plt.suptitle("Observation: AngVel, Gravity, Command", fontsize=16)
plt.tight_layout()
output_image = os.path.join(OUTPUT_DIR, f"csv_{TASK}_others.png")
plt.savefig(output_image, dpi=200, bbox_inches='tight')
plt.close()
print(f"基础观测图已保存至: {output_image}")

# ========================
# 2. 关节位置 (dofpos)：16维 → 4x4 子图
# ========================
n_dof = 16
ncols, nrows = 4, 4
fig, axes = plt.subplots(nrows, ncols, figsize=(18, 14))
axes = axes.flatten()

for idx in range(n_dof):
    pos_col = f"obs_dofpos_{idx}"
    if pos_col not in df.columns:
        print(f"警告: 缺少列 {pos_col}")
        continue

    y = df[pos_col][:N].to_numpy()
    axes[idx].plot(timesteps, y, label="Actual", linewidth=1.8, alpha=0.8)
    axes[idx].set_title(f"DOF Pos {idx}", fontsize=10)
    axes[idx].set_ylabel("Position (rad)", fontsize=9)
    axes[idx].set_xlabel("Timestep", fontsize=9)
    axes[idx].grid(True, alpha=0.5)

for idx in range(n_dof, len(axes)):
    fig.delaxes(axes[idx])

plt.suptitle("Joint Position (DOF)", fontsize=16)
plt.tight_layout()
output_image = os.path.join(OUTPUT_DIR, f"csv_{TASK}_dofpos.png")
plt.savefig(output_image, dpi=200, bbox_inches='tight')
plt.close()
print(f"关节位置图已保存至: {output_image}")

# ========================
# 3. 关节速度 (dofvel)：16维 → 4x4 子图
# ========================
fig, axes = plt.subplots(nrows, ncols, figsize=(18, 14))
axes = axes.flatten()

for idx in range(n_dof):
    vel_col = f"obs_dofvel_{idx}"
    if vel_col not in df.columns:
        continue

    y = df[vel_col][:N].to_numpy()
    axes[idx].plot(timesteps, y, label="Actual", linewidth=1.8, alpha=0.8, color='orange')
    axes[idx].set_title(f"DOF Vel {idx}", fontsize=10)
    axes[idx].set_ylabel("Velocity (rad/s)", fontsize=9)
    axes[idx].set_xlabel("Timestep", fontsize=9)
    axes[idx].grid(True, alpha=0.5)

for idx in range(n_dof, len(axes)):
    fig.delaxes(axes[idx])

plt.suptitle("Joint Velocity (DOF)", fontsize=16)
plt.tight_layout()
output_image = os.path.join(OUTPUT_DIR, f"csv_{TASK}_dofvel.png")
plt.savefig(output_image, dpi=200, bbox_inches='tight')
plt.close()
print(f"关节速度图已保存至: {output_image}")

# ========================
# 4. 动作 (action)：16维 → 4x4 子图
# ========================
fig, axes = plt.subplots(nrows, ncols, figsize=(18, 14))
axes = axes.flatten()

for idx in range(n_dof):
    act_col = f"obs_action_{idx}"
    if act_col not in df.columns:
        continue

    y = df[act_col][:N].to_numpy()
    axes[idx].plot(timesteps, y, label="Action", linewidth=1.8, alpha=0.8, color='green')
    axes[idx].set_title(f"Action {idx}", fontsize=10)
    axes[idx].set_ylabel("Action", fontsize=9)
    axes[idx].set_xlabel("Timestep", fontsize=9)
    axes[idx].grid(True, alpha=0.5)

for idx in range(n_dof, len(axes)):
    fig.delaxes(axes[idx])

plt.suptitle("Action Output", fontsize=16)
plt.tight_layout()
output_image = os.path.join(OUTPUT_DIR, f"csv_{TASK}_action.png")
plt.savefig(output_image, dpi=200, bbox_inches='tight')
plt.close()
print(f"动作输出图已保存至: {output_image}")

print(f"✅ 所有观测绘图完成！共使用前 {N} 个时间步的数据。")