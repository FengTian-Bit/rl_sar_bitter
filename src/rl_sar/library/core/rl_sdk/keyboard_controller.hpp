#ifndef KEYBOARD_CONTROLLER_HPP
#define KEYBOARD_CONTROLLER_HPP

#include <termios.h>
#include <sys/ioctl.h>
#include <iostream>

// 添加RL类的前向声明（解决循环依赖）
class RL;

class KeyboardController {
public:
    KeyboardController(RL& rl_instance);
    ~KeyboardController();

    // 非阻塞检查键盘输入
    bool kbhit();

    // 处理键盘输入并更新控制状态
    void processInput();

private:
    RL& rl_instance_;   //存储RL实例引用 引用机器人控制对象
    termios original_term_;  // 保存原始终端设置
};

#endif // KEYBOARD_CONTROLLER_HPP