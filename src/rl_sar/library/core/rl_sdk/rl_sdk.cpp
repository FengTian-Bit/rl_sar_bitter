/*
 * Copyright (c) 2024-2025 Ziqi Fan
 * SPDX-License-Identifier: Apache-2.0
 */

#include "rl_sdk.hpp"

#include "RLFSMState_Waiting.hpp"
#include "RLFSMState_GetUp.hpp"
#include "RLFSMState_GetDown.hpp"
#include "RLFSMState_RLLocomotion.hpp"
#include "RLFSMState_RLNavigation.hpp"
#include "RLFSMState_Wheel.hpp"
#include "RLFSMState_Test1.hpp"
#include "RLFSMState_Test2.hpp"

/* You may need to override this Forward() function
torch::Tensor RL_XXX::Forward()
{
    torch::autograd::GradMode::set_enabled(false);
    torch::Tensor clamped_obs = this->ComputeObservation();
    torch::Tensor actions = this->model.forward({clamped_obs}).toTensor();
    torch::Tensor clamped_actions = torch::clamp(actions, this->params.clip_actions_lower, this->params.clip_actions_upper);
    return clamped_actions;
}
*/

//构造函数
RL::RL()
{
    fsm.addState(std::make_shared<RLFSMState_Waiting>(*this, nullptr, nullptr));
    fsm.addState(std::make_shared<RLFSMState_GetUp>(*this, nullptr, nullptr));
    fsm.addState(std::make_shared<RLFSMState_GetDown>(*this, nullptr, nullptr));
    fsm.addState(std::make_shared<RLFSMState_RLLocomotion>(*this, nullptr, nullptr));
    fsm.addState(std::make_shared<RLFSMState_RLNavigation>(*this, nullptr, nullptr));
    fsm.addState(std::make_shared<RLFSMState_Wheel>(*this, nullptr, nullptr));
    fsm.addState(std::make_shared<RLFSMState_Test1>(*this, nullptr, nullptr));
    fsm.addState(std::make_shared<RLFSMState_Test2>(*this, nullptr, nullptr));

    fsm.setInitialState("RLFSMState_Waiting");
    // 使用*this作为参数实例
    keyboard_controller_ = std::make_unique<KeyboardController>(*this);
}

//接收一个机器人状态state和一个机器人指令command作为参数，并通过一个有限状态机（Finite State Machine，FSM）来处理这些信息
void RL::StateController(const RobotState<double>* state, RobotCommand<double>* command)
{
    auto updateState = [&](std::shared_ptr<FSMState> statePtr) //lambda函数 &捕获state和command ()是输入参数
    {
        if (auto rlfsm_statePtr = std::dynamic_pointer_cast<RLFSMState>(statePtr))//将statePtr动态转换为FSMState类型的智能指针
        {
            rlfsm_statePtr->fsm_state = state; //把基类的保护量指针传给派生类
            rlfsm_statePtr->fsm_command = command;
        }
    };
    for (auto& pair : fsm._states) //fsm是FSM的实例对象，存储了机器人控制系统的所有状态
    {
        updateState(pair.second); //或许只需要更新当前状态
    }

    fsm.run();  //在fsm.hpp中定义
}

//返回torch张量 
torch::Tensor RL::ComputeObservation()
{
    std::vector<torch::Tensor> obs_list; //创建一个向量存储各个观察张量

    for (const std::string &observation : this->params.observations) //遍历params.observations字符串列表
    {
        if (observation == "lin_vel")
        {
            // obs_list.push_back(this->obs.lin_vel * this->params.lin_vel_scale); //zyl：乘以缩放因子后添加到观察列表
            obs_list.push_back( this->QuatRotateInverse(this->obs.base_quat, this->obs.lin_vel, this->params.framework) * this->params.lin_vel_scale );//zry：将世界坐标系下的线速度转换到机体坐标系下
            // std::cout << "lin_vel: " << this->obs.lin_vel << std::endl;
        }
        /*
            QuatRotateInverse函数第一个参数是表示机器人姿态的四元数，第二个参数是世界坐标系下的向量
            函数输出将第二个参数从世界坐标系转换到机体坐标系下的值
            在IsaacGym中，角速度是世界坐标系的，训练时需要用QuatRotateInverse转换到机体坐标系
            在Gazebo中，角速度同样是世界坐标系的，需要用QuatRotateInverse转换到机体坐标系
            在某些真实机器人如Unitree中，如果角速度已经是机体坐标系的，则无需转换
            忘记转换或多次转换可能导致机器人旋转到180度时控制器崩溃
        */
        else if (observation == "ang_vel_body") // 如果观察类型是机体坐标系角速度
        {
            obs_list.push_back(this->obs.ang_vel * this->params.ang_vel_scale);
            // std::cout << "ang_vel_body: " << this->obs.ang_vel << std::endl;
        }
        else if (observation == "ang_vel_world") // 如果观察类型是世界坐标系角速度
        {   // 将世界坐标系角速度通过四元数逆旋转转换到机体坐标系后乘以缩放因子
            obs_list.push_back(this->QuatRotateInverse(this->obs.base_quat, this->obs.ang_vel, this->params.framework) * this->params.ang_vel_scale);
            // std::cout << "ss ang_vel_world: " << this->QuatRotateInverse(this->obs.base_quat, this->obs.ang_vel, this->params.framework) << std::endl;
        }
        else if (observation == "gravity_vec") // 如果观察类型是重力向量，这里没有缩放因子
        {   // 将重力向量通过四元数逆旋转转换到机体坐标系
            // std::cout<<"base_quat: "<< this->obs.base_quat <<std::endl;
            obs_list.push_back(this->QuatRotateInverse(this->obs.base_quat, this->obs.gravity_vec, this->params.framework)*this->params.gravity_vec_scale);
            // std::cout << "gravity_vec: " << this->QuatRotateInverse(this->obs.base_quat, this->obs.gravity_vec, this->params.framework) << std::endl;
        }
        else if (observation == "commands") // 如果观察类型是命令
        {
            obs_list.push_back(this->obs.commands * this->params.commands_scale); // 命令乘以缩放因子
            //打印this->obs.commands
            // std::cout << "commands: " << this->obs.commands << std::endl;
        }
        else if (observation == "dof_pos") // 如果观察类型是关节位置
        {
            torch::Tensor dof_pos_rel = this->obs.dof_pos - this->params.default_dof_pos; // 关节位置减去默认位置，所以默认位置是期望位置
            for (int i : this->params.wheel_indices)
            {
                dof_pos_rel[0][i] = 0.0;
            }
            obs_list.push_back(dof_pos_rel * this->params.dof_pos_scale); //偏差乘以缩放因子
            // std::cout<<"joint_pos: "<<this->obs.dof_pos<<std::endl;
        }
        else if (observation == "dof_vel") // 如果观察类型是关节速度
        {
            obs_list.push_back(this->obs.dof_vel * this->params.dof_vel_scale); // 关节速度乘以缩放因子
            // std::cout<<"joint_vel: "<<this->obs.dof_vel<<std::endl;
        }
        else if (observation == "actions") // 如果观察类型是动作
        {
            obs_list.push_back(this->obs.actions); // 动作直接添加到观察列表，没有缩放因子
            // std::cout<<"actions: "<<this->obs.actions<<std::endl;
        }
        
    }

    torch::Tensor obs = torch::cat(obs_list, 1); // 将所有观察张量在第1维度（列方向）拼接成完整观察向量

    torch::Tensor csv_obs_angvel = this->obs.ang_vel.reshape(-1);
    torch::Tensor csv_obs_gravity = this->obs.gravity_vec.reshape(-1);
    torch::Tensor csv_obs_command = this->obs.commands.reshape(-1);
    torch::Tensor csv_obs_dofpos = this->obs.dof_pos.reshape(-1);
    torch::Tensor csv_obs_dofvel = this->obs.dof_vel.reshape(-1);
    torch::Tensor csv_obs_action = this->obs.actions.reshape(-1);

    this->CSVLoggerOBS(this->csv_filename_obs, csv_obs_angvel, csv_obs_gravity, csv_obs_command, csv_obs_dofpos, csv_obs_dofvel, csv_obs_action);


    torch::Tensor clamped_obs = torch::clamp(obs, -this->params.clip_obs, this->params.clip_obs); // 将观察向量裁剪到[-clip_obs100, clip_obs100]范围内，防止数值溢出
    return clamped_obs;
}

// 初始化观察状态
void RL::InitObservations()
{
    this->obs.lin_vel = torch::tensor({{0.0, 0.0, 0.0}});
    this->obs.ang_vel = torch::tensor({{0.0, 0.0, 0.0}});
    this->obs.gravity_vec = torch::tensor({{0.0, 0.0, -1.0}});
    this->obs.commands = torch::tensor({{0.0, 0.0, 0.0}});
    // this->obs.base_quat = torch::tensor({{0.0, 0.0, 0.0, 1.0}}); //zyl
    if (this->params.framework == "isaacsim")
    {
        this->obs.base_quat = torch::tensor({{1.0, 0.0, 0.0, 0.0}});//isaacsim中四元数的表示顺序是(w, x, y, z)，实部w在最前
    }
    else if (this->params.framework == "isaacgym")
    {
        this->obs.base_quat = torch::tensor({{0.0, 0.0, 0.0, 1.0}});//isaacgym中四元数的表示顺序是(x, y, z, w)，实部w在最后
    }
    this->obs.dof_pos = this->params.default_dof_pos;
    this->obs.dof_vel = torch::zeros({1, this->params.num_of_dofs});
    this->obs.actions = torch::zeros({1, this->params.num_of_dofs});
}

void RL::InitOutputs()
{
    this->output_dof_tau = torch::zeros({1, this->params.num_of_dofs});
    this->output_dof_pos = this->params.default_dof_pos;
    this->output_dof_vel = torch::zeros({1, this->params.num_of_dofs});
}

void RL::InitControl()
{
    this->control.x = 0.0;
    this->control.y = 0.0;
    this->control.yaw = 0.0;
    
}

void RL::InitRL(std::string robot_path)
{
    this->ReadYaml(robot_path); //打印robot_path: go2w/robot_lab,bitter/robot_lab

    for (std::string &observation : this->params.observations)
    {
        if (observation == "ang_vel")
        {
            if (this->is_simulation == true)
            {
                // In Gazebo, the coordinate system for angular velocity is in the world coordinate system.
                observation = "ang_vel_world";
            }
            else
            {
                // In real robot, the coordinate system for angular velocity is in the body coordinate system.
                observation = "ang_vel_body";
            }
        }
    }

    // init rl
    if (!this->params.observations_history.empty()) //检查配置参数中是否启用了观测历史记录功能，通常用于配置是否需要缓存多步观测数据供强化学习模型使用
    {
        this->history_obs_buf = ObservationBuffer(1, this->params.num_observations, this->params.observations_history.size()); //创建一个ObservationBuffer实例，用于存储历史观测数据
    }

    // model .pt文件
    std::string model_path = std::string(CMAKE_CURRENT_SOURCE_DIR) + "/models/" + robot_path + "/" + this->params.model_name;
    //打印model_path: /home/tf/rl_sar_wjj-0716/rl_sar_wjj/src/rl_sar/models/go2w/robot_lab/policy.pt ,model_name: policy.pt
    this->model = torch::jit::load(model_path);

    this->InitObservations();
    this->InitOutputs();
    this->InitControl();
}

void RL::ComputeOutput(const torch::Tensor &actions, torch::Tensor &output_dof_pos, torch::Tensor &output_dof_vel, torch::Tensor &output_dof_tau)
{
    torch::Tensor actions_scaled = actions * this->params.action_scale;
    torch::Tensor pos_actions_scaled = actions_scaled.clone();
    // torch::Tensor pos_actions_scaled = torch::zeros({1, this->params.num_of_dofs});
    torch::Tensor vel_actions_scaled = torch::zeros_like(actions);

    for (int i : this->params.wheel_indices)
    {
        pos_actions_scaled[0][i] = 0.0;
        vel_actions_scaled[0][i] = actions_scaled[0][i];
    }

    // 其余关节使用位置控制
    for (int i = 0; i < this->params.num_of_dofs; ++i)
    {
        if (std::find(this->params.wheel_indices.begin(), this->params.wheel_indices.end(), i) == this->params.wheel_indices.end())
        {
            pos_actions_scaled[0][i] = actions_scaled[0][i];
            vel_actions_scaled[0][i] = 0.0;
        }
    }

    torch::Tensor all_actions_scaled = pos_actions_scaled + vel_actions_scaled;
    output_dof_pos = pos_actions_scaled + this->params.default_dof_pos;
    output_dof_vel = vel_actions_scaled;
    output_dof_tau = this->params.rl_kp * (all_actions_scaled + this->params.default_dof_pos - this->obs.dof_pos) - this->params.rl_kd * (output_dof_vel - this->obs.dof_vel);
    output_dof_tau = torch::clamp(output_dof_tau, -(this->params.torque_limits), this->params.torque_limits);
}

torch::Tensor RL::QuatRotateInverse(torch::Tensor q, torch::Tensor v, const std::string &framework)
{
    torch::Tensor q_w;
    torch::Tensor q_vec;
    if (framework == "isaacsim")
    {
        q_w = q.index({torch::indexing::Slice(), 0});
        q_vec = q.index({torch::indexing::Slice(), torch::indexing::Slice(1, 4)});
    }
    else if (framework == "isaacgym")
    {
        q_w = q.index({torch::indexing::Slice(), 3});
        q_vec = q.index({torch::indexing::Slice(), torch::indexing::Slice(0, 3)});
    }
    c10::IntArrayRef shape = q.sizes();

    torch::Tensor a = v * (2.0 * torch::pow(q_w, 2) - 1.0).unsqueeze(-1);
    torch::Tensor b = torch::cross(q_vec, v, -1) * q_w.unsqueeze(-1) * 2.0;
    torch::Tensor c = q_vec * torch::bmm(q_vec.view({shape[0], 1, 3}), v.view({shape[0], 3, 1})).squeeze(-1) * 2.0;
    return a - b + c;
}

void RL::TorqueProtect(torch::Tensor origin_output_dof_tau)
{
    std::vector<int> out_of_range_indices;
    std::vector<double> out_of_range_values;
    for (int i = 0; i < origin_output_dof_tau.size(1); ++i)
    {
        double torque_value = origin_output_dof_tau[0][i].item<double>();
        double limit_lower = -this->params.torque_limits[0][i].item<double>();
        double limit_upper = this->params.torque_limits[0][i].item<double>();

        if (torque_value < limit_lower || torque_value > limit_upper)
        {
            out_of_range_indices.push_back(i);
            out_of_range_values.push_back(torque_value);
        }
    }
    if (!out_of_range_indices.empty())
    {
        for (int i = 0; i < out_of_range_indices.size(); ++i)
        {
            int index = out_of_range_indices[i];
            double value = out_of_range_values[i];
            double limit_lower = -this->params.torque_limits[0][index].item<double>();
            double limit_upper = this->params.torque_limits[0][index].item<double>();

            std::cout << LOGGER::WARNING << "Torque(" << index + 1 << ")=" << value << " out of range(" << limit_lower << ", " << limit_upper << ")" << std::endl;
        }
        // Just a reminder, no protection
        // this->control.SetControlState(STATE_POS_GETDOWN);
        // std::cout << LOGGER::INFO << "Switching to STATE_POS_GETDOWN"<< std::endl;
    }
}

//姿态保护功能
void RL::AttitudeProtect(const std::vector<double> &quaternion, float pitch_threshold, float roll_threshold)
{
    float rad2deg = 57.2958;
    float w, x, y, z;

    if (this->params.framework == "isaacgym")
    {
        w = quaternion[3];
        x = quaternion[0];
        y = quaternion[1];
        z = quaternion[2];
    }
    else if (this->params.framework == "isaacsim")
    {
        w = quaternion[0];
        x = quaternion[1];
        y = quaternion[2];
        z = quaternion[3];
    }

    // Calculate roll (rotation around the X-axis)
    float sinr_cosp = 2 * (w * x + y * z);
    float cosr_cosp = 1 - 2 * (x * x + y * y);
    float roll = std::atan2(sinr_cosp, cosr_cosp) * rad2deg;

    // Calculate pitch (rotation around the Y-axis)
    float sinp = 2 * (w * y - z * x);
    float pitch;
    if (std::fabs(sinp) >= 1)
    {
        pitch = std::copysign(90.0, sinp); // Clamp to avoid out-of-range values
    }
    else
    {
        pitch = std::asin(sinp) * rad2deg;
    }

    if (std::fabs(roll) > roll_threshold)
    {
        // this->control.SetControlState(STATE_POS_GETDOWN);
        std::cout << LOGGER::WARNING << "Roll exceeds " << roll_threshold << " degrees. Current: " << roll << " degrees." << std::endl;
    }
    if (std::fabs(pitch) > pitch_threshold)
    {
        // this->control.SetControlState(STATE_POS_GETDOWN);
        std::cout << LOGGER::WARNING << "Pitch exceeds " << pitch_threshold << " degrees. Current: " << pitch << " degrees." << std::endl;
    }
}

//调用keyboard_controller类，在那里改键位
void RL::KeyboardInterface()
{

    this->keyboard_controller_->processInput();

}

template <typename T>
std::vector<T> ReadVectorFromYaml(const YAML::Node &node)
{
    std::vector<T> values;
    for (const auto &val : node)
    {
        values.push_back(val.as<T>());
    }
    return values;
}

void RL::ReadYamlBase(std::string robot_path)
{
    // The config file is located at "rl_sar/src/rl_sar/models/<robot_path>/base.yaml"
    // std::string config_path = std::string(CMAKE_CURRENT_SOURCE_DIR) + "/models/" + robot_path + "/base.yaml";
    std::string config_path = std::string(CMAKE_CURRENT_SOURCE_DIR) + "/models/" + robot_path + "/base.yaml";
    std::cout<<"RL ReadYamlBase: config_path: "<<config_path<<std::endl;

    YAML::Node config;
    try
    {
        config = YAML::LoadFile(config_path)[robot_path];
    }
    catch (YAML::BadFile &e)
    {
        std::cout << LOGGER::ERROR << "The file '" << config_path << "' does not exist" << std::endl;
        return;
    }

    this->params.dt = config["dt"].as<double>(); 
    this->params.decimation = config["decimation"].as<int>();
    this->params.wheel_indices = ReadVectorFromYaml<int>(config["wheel_indices"]);
    this->params.leg_indices = ReadVectorFromYaml<int>(config["leg_indices"]);
    this->params.num_of_dofs = config["num_of_dofs"].as<int>();
    this->params.fixed_kp = torch::tensor(ReadVectorFromYaml<double>(config["fixed_kp"])).view({1, -1});
    this->params.fixed_kd = torch::tensor(ReadVectorFromYaml<double>(config["fixed_kd"])).view({1, -1});
    this->params.torque_limits = torch::tensor(ReadVectorFromYaml<double>(config["torque_limits"])).view({1, -1});
    this->params.default_dof_pos = torch::tensor(ReadVectorFromYaml<double>(config["default_dof_pos"])).view({1, -1});
    this->params.joint_controller_names = ReadVectorFromYaml<std::string>(config["joint_controller_names"]);
    this->params.action_controller_names = ReadVectorFromYaml<std::string>(config["action_controller_names"]);
    this->params.command_mapping = ReadVectorFromYaml<int>(config["command_mapping"]);
    this->params.state_mapping = ReadVectorFromYaml<int>(config["state_mapping"]);

}



void RL::ReadYaml(std::string robot_path)
{
    // The config file is located at "rl_sar/src/rl_sar/models/<robot_path>/config.yaml"
    std::string config_path = std::string(CMAKE_CURRENT_SOURCE_DIR) + "/models/" + robot_path + "/config.yaml";

    std::cout << LOGGER::INFO << "Loading config for robot_path: " << robot_path << std::endl;
    std::cout << LOGGER::INFO << "Config file path: " << config_path << std::endl;

    YAML::Node config;
    try
    {
        config = YAML::LoadFile(config_path)[robot_path];
    }
    catch (YAML::BadFile &e)
    {
        std::cout << LOGGER::ERROR << "The file '" << config_path << "' does not exist" << std::endl;
        return;
    }
    this->params.dt = config["dt"].as<double>();
    this->params.decimation = config["decimation"].as<int>();
    this->params.model_name = config["model_name"].as<std::string>();
    this->params.framework = config["framework"].as<std::string>();
    this->params.num_observations = config["num_observations"].as<int>();
    this->params.observations = ReadVectorFromYaml<std::string>(config["observations"]);
    if (config["observations_history"].IsNull())
    {
        this->params.observations_history = {};
    }
    else
    {
        this->params.observations_history = ReadVectorFromYaml<int>(config["observations_history"]);
    }
    this->params.clip_obs = config["clip_obs"].as<double>();
    if (config["clip_actions_lower"].IsNull() && config["clip_actions_upper"].IsNull())
    {
        this->params.clip_actions_upper = torch::tensor({}).view({1, -1});
        this->params.clip_actions_lower = torch::tensor({}).view({1, -1});
    }
    else
    {
        this->params.clip_actions_upper = torch::tensor(ReadVectorFromYaml<double>(config["clip_actions_upper"])).view({1, -1});
        this->params.clip_actions_lower = torch::tensor(ReadVectorFromYaml<double>(config["clip_actions_lower"])).view({1, -1});
    }
    this->params.action_scale = torch::tensor(ReadVectorFromYaml<double>(config["action_scale"])).view({1, -1});
    this->params.wheel_indices = ReadVectorFromYaml<int>(config["wheel_indices"]);
    this->params.leg_indices = ReadVectorFromYaml<int>(config["leg_indices"]);
    this->params.num_of_dofs = config["num_of_dofs"].as<int>();
    this->params.lin_vel_scale = config["lin_vel_scale"].as<double>();
    this->params.ang_vel_scale = config["ang_vel_scale"].as<double>();
    this->params.dof_pos_scale = config["dof_pos_scale"].as<double>();
    this->params.dof_vel_scale = config["dof_vel_scale"].as<double>();
    this->params.gravity_vec_scale = config["gravity_vec_scale"].as<double>();
    this->params.commands_scale = torch::tensor(ReadVectorFromYaml<double>(config["commands_scale"])).view({1, -1});
    // this->params.commands_scale = torch::tensor({this->params.lin_vel_scale, this->params.lin_vel_scale, this->params.ang_vel_scale});
    this->params.rl_kp = torch::tensor(ReadVectorFromYaml<double>(config["rl_kp"])).view({1, -1});
    this->params.rl_kd = torch::tensor(ReadVectorFromYaml<double>(config["rl_kd"])).view({1, -1});
    this->params.fixed_kp = torch::tensor(ReadVectorFromYaml<double>(config["fixed_kp"])).view({1, -1});
    this->params.fixed_kd = torch::tensor(ReadVectorFromYaml<double>(config["fixed_kd"])).view({1, -1});
    this->params.torque_limits = torch::tensor(ReadVectorFromYaml<double>(config["torque_limits"])).view({1, -1});
    this->params.default_dof_pos = torch::tensor(ReadVectorFromYaml<double>(config["default_dof_pos"])).view({1, -1});
    this->params.joint_controller_names = ReadVectorFromYaml<std::string>(config["joint_controller_names"]);
    this->params.action_controller_names = ReadVectorFromYaml<std::string>(config["action_controller_names"]);
    this->params.command_mapping = ReadVectorFromYaml<int>(config["command_mapping"]);
    this->params.state_mapping = ReadVectorFromYaml<int>(config["state_mapping"]);
}

// void RL::CSVInit(std::string robot_path)
// {
//     csv_filename = std::string(CMAKE_CURRENT_SOURCE_DIR) + "/models/" + robot_path + "/motor";

//     // Uncomment these lines if need timestamp for file name
//     // auto now = std::chrono::system_clock::now();
//     // std::time_t now_c = std::chrono::system_clock::to_time_t(now);
//     // std::stringstream ss;
//     // ss << std::put_time(std::localtime(&now_c), "%Y%m%d%H%M%S");
//     // std::string timestamp = ss.str();
//     // csv_filename += "_" + timestamp;

//     csv_filename += ".csv";
//     std::ofstream file(csv_filename.c_str());

//     for(int i = 0; i < 12; ++i) { file << "tau_cal_" << i << ","; }
//     for(int i = 0; i < 12; ++i) { file << "tau_est_" << i << ","; }
//     for(int i = 0; i < 12; ++i) { file << "joint_pos_" << i << ","; }
//     for(int i = 0; i < 12; ++i) { file << "joint_pos_target_" << i << ","; }
//     for(int i = 0; i < 12; ++i) { file << "joint_vel_" << i << ","; }

//     file << std::endl;

//     file.close();
// }

// void RL::CSVLogger(torch::Tensor torque, torch::Tensor tau_est, torch::Tensor joint_pos, torch::Tensor joint_pos_target, torch::Tensor joint_vel)
// {
//     std::ofstream file(csv_filename.c_str(), std::ios_base::app);

//     for(int i = 0; i < 12; ++i) { file << torque[0][i].item<double>() << ","; }
//     for(int i = 0; i < 12; ++i) { file << tau_est[0][i].item<double>() << ","; }
//     for(int i = 0; i < 12; ++i) { file << joint_pos[0][i].item<double>() << ","; }
//     for(int i = 0; i < 12; ++i) { file << joint_pos_target[0][i].item<double>() << ","; }
//     for(int i = 0; i < 12; ++i) { file << joint_vel[0][i].item<double>() << ","; }

//     file << std::endl;

//     file.close();
// }

void RL::CSVInitJOINT(std::string csv_filename, std::string robot_name)
{
    // Uncomment these lines if need timestamp for file name
    // auto now = std::chrono::system_clock::now();
    // std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    // std::stringstream ss;
    // ss << std::put_time(std::localtime(&now_c), "%Y%m%d%H%M%S");
    // std::string timestamp = ss.str();
    // csv_filename += "_" + timestamp;

    std::cout << "Finished Init CSV Logger JOINT " << std::endl;
    std::cout << LOGGER::INFO << "Recording motor data in " << csv_filename << std::endl;
    std::ofstream file(csv_filename.c_str());
    std::vector<int> leg_indices = {0, 1, 2, 4, 5, 6, 8, 9, 10, 12, 13, 14};
    std::vector<int> wheel_indices = {3, 7, 11, 15};

    for(int i = 0; i < 16; ++i) { file << "joint_tau_cal_" << i << ","; }
    for(int i = 0; i < 16; ++i) { file << "joint_tau_est_" << i << ","; }
    for (int i : leg_indices) { file << "joint_pos_" << i << ","; }
    for (int i : leg_indices) { file << "joint_pos_target_" << i << ","; }
    for (int i : wheel_indices) { file << "joint_vel_" << i << ","; }
    for (int i : wheel_indices) { file << "joint_vel_target_" << i << ","; }
    // for(int i = 0; i < 16; ++i) { file << "joint_vel_" << i << ","; }
    // for(int i = 0; i < 4; ++i) { file << "joint_vel_target_" << i << ","; }

    file << std::endl;

    file.close();
}

void RL::CSVLoggerJOINT(std::string csv_filename, torch::Tensor joint_torque_cal, torch::Tensor joint_tau_est, torch::Tensor joint_pos, torch::Tensor joint_pos_target, torch::Tensor joint_vel, torch::Tensor joint_vel_target)
{
    std::ofstream file(csv_filename.c_str(), std::ios_base::app);
    std::vector<int> leg_indices = {0, 1, 2, 4, 5, 6, 8, 9, 10, 12, 13, 14};
    std::vector<int> wheel_indices = {3, 7, 11, 15};

    // for(int i = 0; i < 16; ++i) { file << joint_torque_cal[0][i].item<double>() << ","; }
    // for(int i = 0; i < 16; ++i) { file << joint_tau_est[0][i].item<double>() << ","; }
    // for (int i : leg_indices) { file << joint_pos[0][i].item<double>() << ","; }
    // for (int i : leg_indices) { file << joint_pos_target[0][i].item<double>() << ","; }
    // for (int i : wheel_indices) { file << joint_vel[0][i].item<double>() << ","; }
    // for (int i : wheel_indices) { file << joint_vel_target[0][i].item<double>() << ","; }

    for(int i = 0; i < 16; ++i) { file << joint_torque_cal[i].item<double>() << ","; }
    for(int i = 0; i < 16; ++i) { file << joint_tau_est[i].item<double>() << ","; }
    for (int i : leg_indices) { file << joint_pos[i].item<double>() << ","; }
    for (int i : leg_indices) { file << joint_pos_target[i].item<double>() << ","; }
    for (int i : wheel_indices) { file << joint_vel[i].item<double>() << ","; }
    for (int i : wheel_indices) { file << joint_vel_target[i].item<double>() << ","; }

    file << std::endl;

    file.close();
}
void RL::CSVInitOBS(std::string csv_filename, std::string robot_name)
{
    // Uncomment these lines if need timestamp for file name
    // auto now = std::chrono::system_clock::now();
    // std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    // std::stringstream ss;
    // ss << std::put_time(std::localtime(&now_c), "%Y%m%d%H%M%S");
    // std::string timestamp = ss.str();
    // csv_filename += "_" + timestamp;

    std::cout << "Finished Init CSV Logger OBS " << std::endl;
    std::cout << LOGGER::INFO << "Recording obs data in " << csv_filename << std::endl;
    std::ofstream file(csv_filename.c_str());

    for (int i = 0; i < 3; ++i) file << "obs_angvel_" << i << ",";
    for (int i = 0; i < 3; ++i) file << "obs_gravity_" << i << ",";
    for (int i = 0; i < 3; ++i) file << "obs_command_" << i << ",";
    for (int i = 0; i < 16; ++i) file << "obs_dofpos_" << i << ",";
    for (int i = 0; i < 16; ++i) file << "obs_dofvel_" << i << ",";
    for (int i = 0; i < 16; ++i) file << "obs_action_" << i << ",";

    file << std::endl;

    file.close();
}
void RL::CSVLoggerOBS(std::string csv_filename, torch::Tensor obs_angvel, torch::Tensor obs_gravity, torch::Tensor obs_command, torch::Tensor obs_dofpos, torch::Tensor obs_dofvel, torch::Tensor obs_action)
{
    std::ofstream file(csv_filename.c_str(), std::ios_base::app);

    for(int i = 0; i < 3; ++i) { file << obs_angvel[i].item<double>() << ","; }
    for(int i = 0; i < 3; ++i) { file << obs_gravity[i].item<double>() << ","; }
    for(int i = 0; i < 3; ++i) { file << obs_command[i].item<double>() << ","; }
    for(int i = 0; i < 16; ++i) { file << obs_dofpos[i].item<double>() << ","; }
    for(int i = 0; i < 16; ++i) { file << obs_dofvel[i].item<double>() << ","; }
    for(int i = 0; i < 16; ++i) { file << obs_action[i].item<double>() << ","; }

    file << std::endl;

    file.close();
}