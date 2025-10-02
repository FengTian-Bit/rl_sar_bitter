#include "keyboard_controller.hpp"
#include "rl_sdk.hpp"
#include <cstdio>

KeyboardController::KeyboardController(RL& rl_instance) : rl_instance_(rl_instance) {
    // 保存原始终端设置
    tcgetattr(0, &original_term_);

    //下面是不需要按回车和无回显的设置
    termios new_term = original_term_;
    new_term.c_lflag &= ~(ICANON | ECHO);
    new_term.c_cc[VMIN] = 0;
    new_term.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &new_term);
}

bool KeyboardController::kbhit() {
    int byteswaiting;
    ioctl(0, FIONREAD, &byteswaiting);
    return byteswaiting > 0;
}

void KeyboardController::processInput() {
    if (kbhit()) {
        int c = fgetc(stdin);
        switch (c) {
        case '0':
            rl_instance_.control.SetControlState(STATE_POS_GETUP);
            break;
        case 'p':
            rl_instance_.control.SetControlState(STATE_RL_LOCOMOTION);
            break;
        case 'o':
            rl_instance_.control.SetControlState(STATE_WHEEL);
            break;
        case 'n':
            rl_instance_.control.SetControlState(STATE_RL_NAVIGATION);
            break;
        case '1':
            rl_instance_.control.SetControlState(STATE_POS_GETDOWN);
            break;
        case 'w':
            rl_instance_.control.x += 0.1;
            break;
        case 's':
            rl_instance_.control.x -= 0.1;
            break;
        case 'a':
            rl_instance_.control.yaw += 0.1;
            break;
        case 'd':
            rl_instance_.control.yaw -= 0.1;
            break;
        case 'j':
            rl_instance_.control.y += 0.1;
            break;
        case 'l':
            rl_instance_.control.y -= 0.1;
            break;
        case ' ':
            rl_instance_.control.x = 0;
            rl_instance_.control.y = 0;
            rl_instance_.control.yaw = 0;
            break;
        case 'r':
            rl_instance_.control.SetControlState(STATE_RESET_SIMULATION);
            break;
        case '\n':
            rl_instance_.control.SetControlState(STATE_TOGGLE_SIMULATION);
            break;
        case '2':
            rl_instance_.control.SetControlState(STATE_TEST2);
        default:
            std::cout << "Unknown key pressed: " << c << std::endl;
            break;
        }

    }
}


KeyboardController::~KeyboardController() {
    // 恢复终端设置
    tcsetattr(0, TCSANOW, &original_term_);
}
