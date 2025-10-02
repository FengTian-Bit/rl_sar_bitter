#include "RLFSMState_RLLocomotion.hpp"

RLFSMState_RLLocomotion::RLFSMState_RLLocomotion(RL& rl, const RobotState<double>* state, RobotCommand<double>* command)
        : RLFSMState(rl, state, command, "RLFSMState_RLLocomotion") {}

RLFSMState_RLLocomotion::~RLFSMState_RLLocomotion(){}

void RLFSMState_RLLocomotion::enter()
{
    std::cout << LOGGER::INFO << "Enter FSM RL_Locomotion mode" << std::endl;

    // read params from yaml
    rl.config_name = rl.default_rl_config;
    std::string robot_path = rl.robot_name + "/" + rl.config_name;
    std::cout << LOGGER::INFO << "FSM RL_Locomotion: config_name: " << rl.config_name << std::endl; 
    // std::cout << LOGGER::INFO << "FSM RL_Locomotion: robot_name: " << rl.robot_name << std::endl; 
    try
    {
        rl.InitRL(robot_path);
        rl.rl_init_done = true;
        // std::cout << LOGGER::INFO << "InitRL() success" << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << LOGGER::ERROR << "InitRL() failed: " << e.what() << std::endl;
        rl.rl_init_done = false;
        rl.control.control_state = STATE::STATE_POS_GETUP;
    }
}

void RLFSMState_RLLocomotion::run()
{
        std::cout << "\r" << std::flush << LOGGER::INFO << "RL Controller x:" << rl.control.x << " y:" << rl.control.y << " yaw:" << rl.control.yaw << std::flush;

        torch::Tensor _output_dof_pos, _output_dof_vel;
        if (rl.output_dof_pos_queue.try_pop(_output_dof_pos) && rl.output_dof_vel_queue.try_pop(_output_dof_vel))
        {
            static int step_rl_counter = 0;
            for (int i = 0; i < rl.params.num_of_dofs; ++i)
            {
                if (_output_dof_pos.defined() && _output_dof_pos.numel() > 0)
                {
                    fsm_command->motor_command.q[i] = rl.output_dof_pos[0][i].item<double>();
                }
                if (_output_dof_vel.defined() && _output_dof_vel.numel() > 0)
                {
                    fsm_command->motor_command.dq[i] = rl.output_dof_vel[0][i].item<double>();
                }
                fsm_command->motor_command.kp[i] = rl.params.rl_kp[0][i].item<double>();
                fsm_command->motor_command.kd[i] = rl.params.rl_kd[0][i].item<double>();
                fsm_command->motor_command.tau[i] = 0;
                // fsm_command->motor_command.tau[i] = rl.output_dof_tau[0][i].item<double>();

            }
            if (step_rl_counter == 0)
            {
                std::cout << '\n' << LOGGER::INFO << "CSV_RL WRITING: " << rl.csv_filename_rl << '\n';
            }
            if(step_rl_counter++ % 1 == 0)
            {
                torch::Tensor csv_pos_error = torch::tensor(fsm_command->motor_command.q,  torch::kDouble) -
                                        torch::tensor(fsm_state->motor_state.q,   torch::kDouble);
                torch::Tensor csv_vel_error = torch::tensor(fsm_command->motor_command.dq, torch::kDouble) -
                                        torch::tensor(fsm_state->motor_state.dq,  torch::kDouble);
                torch::Tensor csv_kp = torch::tensor(fsm_command->motor_command.kp, torch::kDouble);
                torch::Tensor csv_kd = torch::tensor(fsm_command->motor_command.kd, torch::kDouble);
    
                torch::Tensor csv_joint_torque_cal = csv_kp * csv_pos_error + csv_kd * csv_vel_error;
                torch::Tensor csv_joint_tau_est = torch::tensor(fsm_state->motor_state.tau_est, torch::kDouble);
                torch::Tensor csv_joint_pos = torch::tensor(fsm_state->motor_state.q, torch::kDouble);
                torch::Tensor csv_joint_pos_target = torch::tensor(fsm_command->motor_command.q, torch::kDouble);
                torch::Tensor csv_joint_vel = torch::tensor(fsm_state->motor_state.dq, torch::kDouble);
                torch::Tensor csv_joint_vel_target = torch::tensor(fsm_command->motor_command.dq, torch::kDouble);
                rl.CSVLoggerJOINT(rl.csv_filename_rl, csv_joint_torque_cal, csv_joint_tau_est, csv_joint_pos, csv_joint_pos_target, csv_joint_vel, csv_joint_vel_target);
            }

            // std::cout << "Output DOF Positions: ";
            // for (int i = 0; i < rl.params.num_of_dofs; ++i)
            // {
            //     std::cout << rl.output_dof_pos[0][i].item<double>() << " ";
            // }
            // std::cout << std::endl;

            // std::cout << "Output DOF Velocities: ";
            // for (int i = 0; i < rl.params.num_of_dofs; ++i)
            // {
            //     std::cout << rl.output_dof_vel[0][i].item<double>() << " ";
            // }
            // std::cout << std::endl;
        }
}

void RLFSMState_RLLocomotion::exit()
{
    std::cout << LOGGER::INFO << "Exit FSM RL_Locomotion mode" << std::endl;
    rl.rl_init_done = false;
}

std::string RLFSMState_RLLocomotion::checkChange()
{
    if (rl.control.control_state == STATE::STATE_POS_GETDOWN)
        {
            return "RLFSMState_GetDown";
        }
        else if (rl.control.control_state == STATE::STATE_POS_GETUP)
        {
            return "RLFSMState_GetUp";
        }
        else if (rl.control.control_state == STATE::STATE_RL_LOCOMOTION)
        {
            return "RLFSMState_RLLocomotion";
        }
        else if (rl.control.control_state == STATE::STATE_RL_NAVIGATION)
        {
            return "RLFSMState_RLNavigation";
        }
        else if (rl.control.control_state == STATE::STATE_WAITING)
        {
            return "RLFSMState_Waiting";
        }
        return _stateName;
}
