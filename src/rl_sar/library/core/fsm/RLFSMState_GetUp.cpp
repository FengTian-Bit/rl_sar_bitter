#include "RLFSMState_GetUp.hpp"

RLFSMState_GetUp::RLFSMState_GetUp(RL& rl, const RobotState<double>* state, RobotCommand<double>* command)
        : RLFSMState(rl, state, command, "RLFSMState_GetUp") {}

RLFSMState_GetUp::~RLFSMState_GetUp(){}   

void RLFSMState_GetUp::enter()
{
    std::cout << LOGGER::INFO << "Enter FSM GetUp mode. " << std::endl;
    rl.now_state = *fsm_state;
    this->step_standup_counter = 0;
    this->getup_percent = 0.0;
    this->home_percent = 0.0;
}

void RLFSMState_GetUp::run()
{
    if (this->home_percent < 1.0)
    {
        for (int i = 0; i < rl.params.num_of_dofs; ++i)
        {
            fsm_command->motor_command.q[i] = calcCos(rl.now_state.motor_state.q[i], rl.params.home_dof_pos[0][i].item<double>(), this->home_percent);
            fsm_command->motor_command.dq[i] = 0;
            fsm_command->motor_command.kp[i] = rl.params.fixed_kp[0][i].item<double>();
            fsm_command->motor_command.kd[i] = rl.params.fixed_kd[0][i].item<double>();
            fsm_command->motor_command.tau[i] = 0;
        }
        std::cout << "\r" << std::flush << LOGGER::INFO << "Homing: " << std::fixed << std::setprecision(2) << this->home_percent * 100.0 + 0.2 <<"% " << std::flush;
        this->home_percent += GETUP_D_PERCENT;
        this->home_percent = this->home_percent > 1.0 ? 1.0 : this->home_percent;
    }
    else if (this->getup_percent < 1.0)
    {
        if (this->getup_percent == 0)
        {   
            std::cout<<std::endl<< LOGGER::INFO << "Homing Completed " <<std::endl;
            for (int i = 0; i < rl.params.num_of_dofs; ++i)
            {
                rl.now_state.motor_state.q[i] = fsm_state->motor_state.q[i];
            }
            rl.start_state = rl.now_state; // homing positin for down 
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
        for (int i = 0; i < rl.params.num_of_dofs; ++i)
        {
            fsm_command->motor_command.q[i] = calcCos(rl.now_state.motor_state.q[i], rl.params.default_dof_pos[0][i].item<double>(), this->getup_percent);
            fsm_command->motor_command.dq[i] = 0;
            fsm_command->motor_command.kp[i] = rl.params.fixed_kp[0][i].item<double>();
            fsm_command->motor_command.kd[i] = rl.params.fixed_kd[0][i].item<double>();
            fsm_command->motor_command.tau[i] = 0;
        }
        std::cout << "\r" << std::flush << LOGGER::INFO << "Getting up: " << std::fixed << std::setprecision(2) << this->getup_percent * 100.0 + 0.2 <<"% "  << std::flush;
        this->getup_percent += GETUP_D_PERCENT; 
        this->getup_percent = this->getup_percent > 1.0 ? 1.0 : this->getup_percent;
    }

    // CSV Logger
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
    step_standup_counter++;
        
}

void RLFSMState_GetUp::exit()
{
    std::cout << LOGGER::INFO << "Exit FSM GetUp mode. " << std::endl;
    this->getup_percent = 0.0;
    this->home_percent = 0.0;
}

std::string RLFSMState_GetUp::checkChange()
{
    if (this->getup_percent >= 1.0f)
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

double RLFSMState_GetUp::calcCos(double start, double stop, double t) const
{
  double A = (stop - start) / 2.0;
  return A * -cos(M_PI * t) + start + A;
}