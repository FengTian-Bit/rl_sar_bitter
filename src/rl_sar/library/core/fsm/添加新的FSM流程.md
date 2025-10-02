```markdown
<!--
Author : 田丰
Date   : 2025-08-22
-->

# 新增 FSM（有限状态机）操作指南

> 适用于 `rl_sar` 项目，按顺序完成即可在状态机中注册并触发自定义状态。

---

## 1. 创建状态源文件
进入目录  
`rl_sar/library/core/fsm`  
- 参照已有文件（如 `RLStateWheel.cpp / .hpp`）新建一对 `.cpp` 与 `.hpp`  
- 实现构造函数、`enter()`、`execute()`、`exit()` 等标准接口

---

## 2. 注册状态到 SDK（源文件）
打开  
`rl_sar/library/core/rl_sdk/rl_sdk.cpp`  
1. 添加头文件  
   ```cpp
   #include "RLState<YourName>.hpp"
   ```
2. 在 `RLSdk` 构造函数里追加  
   ```cpp
   addState(new RLState<YourName>(...));
   ```

---

## 3. 注册状态到 SDK（头文件）
打开  
`rl_sar/library/core/rl_sdk/rl_sdk.hpp`  
- 于 `enum class STATE` 末尾插入新枚举值，例如  
  ```cpp
  STATE_YOUR_NAME,
  ```

---

## 4. 绑定键盘触发（可选）
编辑  
`rl_sar/library/core/rl_sdk/keyboard_controller.cpp`  
- 在 `processInput()` 的 `switch` 分支里模仿现有写法，增加按键判断并调用  
  ```cpp
  rl_instance_.control.SetControlState(STATE_YOUR_NAME);
  ```

---

## 5. 绑定手柄触发（可选）
根据运行场景二选一：
- 仿真：`rl_sar/src/rl_sim.cpp`  
- 真机：`rl_sar/src/rl_real_bitter.cpp`  

在 `JoyCallback()` 函数内添加判断，如  
```cpp
if (joy->buttons[BUTTON_X]) {
    control.SetControlState(STATE_YOUR_NAME);
}
```

---

## 6. 编译验证
```bash
cd <workspace>
colcon build --packages-select rl_sar --cmake-args -DCMAKE_BUILD_TYPE=Release
source install/setup.bash
```
运行节点后，通过键盘或手柄触发新状态，确认机器人行为符合预期即完成。
```