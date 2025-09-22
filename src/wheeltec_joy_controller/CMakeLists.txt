cmake_minimum_required(VERSION 3.0.2)
project(wheeltec_joy)  # 必须与 package.xml 的 <name> 一致

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
)

## 设置 C++11 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

## 头文件路径
include_directories(
  ${catkin_INCLUDE_DIRS}
)

## 关键修改：直接指定输出目录到 devel/lib/wheeltec_joy/
set(EXECUTABLE_OUTPUT_PATH ${CATKIN_DEVEL_PREFIX}/lib/wheeltec_joy)

## 生成可执行文件
add_executable(joycontrol src/control.cpp)
target_link_libraries(joycontrol ${catkin_LIBRARIES})
add_dependencies(joycontrol ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## 可选：生成第二个可执行文件（joy_node）
add_executable(joy_node src/joy_node.cpp)
target_link_libraries(joy_node ${catkin_LIBRARIES})
add_dependencies(joy_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})