#include "RLFSMState_GetUp.hpp"

RLFSMState_GetUp::RLFSMState_GetUp(RL& rl, const RobotState<double>* state, RobotCommand<double>* command)
        : RLFSMState(rl, state, command, "RLFSMState_GetUp") {}

RLFSMState_GetUp::~RLFSMState_GetUp(){}   

void RLFSMState_GetUp::enter()
{
    std::cout << LOGGER::INFO << "Enter FSM GetUp mode. " << std::endl;
    rl.running_percent = 0.0f;
    rl.now_state = *fsm_state;
    rl.start_state = rl.now_state;
}

void RLFSMState_GetUp::run()
{
    if (rl.running_percent < 1.0f)
    {
        static int step_standup_counter = 0;
        rl.running_percent += 1.0f / 1000.0f;
        rl.running_percent = std::min(rl.running_percent, 1.0f);
        for (int i = 0; i < rl.params.num_of_dofs; ++i)
        {
            fsm_command->motor_command.q[i] = (1 - rl.running_percent) * rl.start_state.motor_state.q[i] + rl.running_percent * rl.params.default_dof_pos[0][i].item<double>();
            // fsm_command->motor_command.q[i]=calcCos(q[i], q_d[i], t_max, t);;
            fsm_command->motor_command.dq[i] = 0;
            fsm_command->motor_command.kp[i] = rl.params.fixed_kp[0][i].item<double>();
            fsm_command->motor_command.kd[i] = rl.params.fixed_kd[0][i].item<double>();
            fsm_command->motor_command.tau[i] = 0;
        }

        if (step_standup_counter == 0)
        {
            std::cout << '\n' << LOGGER::INFO << "CSV_STANDUP WRITING: " << rl.csv_filename_standup << '\n';
        }
        if(step_standup_counter++ % 5 == 0)
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
            rl.CSVLoggerJOINT(rl.csv_filename_standup, csv_joint_torque_cal, csv_joint_tau_est, csv_joint_pos, csv_joint_pos_target, csv_joint_vel, csv_joint_vel_target);
        }

        std::cout << "\r" << std::flush << LOGGER::INFO << "Getting up " << std::fixed << std::setprecision(2) << rl.running_percent * 100.0f << "%" << std::flush;
        
    }
}

void RLFSMState_GetUp::exit()
{
    std::cout << LOGGER::INFO << "Exit FSM GetUp mode. " << std::endl;
    rl.running_percent = 0.0f;
}

std::string RLFSMState_GetUp::checkChange()
{
    if (rl.running_percent >= 1.0f)
    {
        if (rl.control.control_state == STATE::STATE_RL_LOCOMOTION)
        {
            return "RLFSMState_RLLocomotion";
        }
        else if (rl.control.control_state == STATE::STATE_RL_NAVIGATION)
        {
            return "RLFSMState_RLNavigation";
        }
        else if (rl.control.control_state == STATE::STATE_POS_GETDOWN)
        {
            return "RLFSMState_GetDown";
        }
        else if (rl.control.control_state == STATE::STATE_WAITING)
        {
            return "RLFSMState_Waiting";
        }
        else if (rl.control.control_state == STATE::STATE_WHEEL)
        {
            return "RLFSMState_Wheel";
        }
        else if (rl.control.control_state == STATE::STATE_TEST1)
        {
            std::cout << LOGGER::INFO << "check Change mode Test1. " << std::endl;
            return "RLFSMState_Test1";
        }
        else if (rl.control.control_state == STATE::STATE_TEST2)
        {
            std::cout << LOGGER::INFO << "check Change mode Test2. " << std::endl;
            return "RLFSMState_Test2";
        }
    }
    return _stateName;
}

double RLFSMState_GetUp::calcCos(double start, double stop, double T, double t) const
{
  double A = (stop - start) / 2.0;
  return A * -cos(M_PI / T * t) + start + A;
}