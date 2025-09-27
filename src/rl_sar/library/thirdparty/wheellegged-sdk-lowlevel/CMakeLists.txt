cmake_minimum_required(VERSION 3.5)
project(wheellegged_sdk_lowlevel)

set(CMAKE_BUILD_TYPE "Release")

# ---------- 1. 根据 CPU 选对预编译库 ----------
if(${CMAKE_SYSTEM_PROCESSOR} MATCHES "x86_64|amd64|AMD64")
    set(LIB_PATH ${PROJECT_SOURCE_DIR}/lib/amd64)
    set(LIB_FILE ${LIB_PATH}/libwheellegged_sdk_lowlevel.so)
elseif(${CMAKE_SYSTEM_PROCESSOR} MATCHES "aarch64|arm64|ARM64")
    set(LIB_PATH ${PROJECT_SOURCE_DIR}/lib/aarch64)
    set(LIB_FILE ${LIB_PATH}/libwheellegged_sdk_lowlevel.so)
elseif(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "arm")
    set(LIB_PATH ${PROJECT_SOURCE_DIR}/lib/arm32)
    set(LIB_FILE ${LIB_PATH}/libwheellegged_sdk_lowlevel.so)
else()
    message(FATAL_ERROR "Unsupported architecture: ${CMAKE_SYSTEM_PROCESSOR}")
endif()

# ---------- 2. 创建 IMPORTED 目标，供上层 target_link_libraries ----------
add_library(wheellegged_sdk_lowlevel SHARED IMPORTED GLOBAL)
set_target_properties(wheellegged_sdk_lowlevel PROPERTIES
    IMPORTED_LOCATION "${LIB_FILE}"
    INTERFACE_INCLUDE_DIRECTORIES "${PROJECT_SOURCE_DIR}/include"
)

# 预编译库如果依赖线程、dl
find_package(Threads REQUIRED)
target_link_libraries(wheellegged_sdk_lowlevel INTERFACE Threads::Threads ${CMAKE_DL_LIBS})

# ---------- 3. ROS1 环境：拷贝到 devel 空间 ----------
if(DEFINED ENV{ROS_DISTRO} AND $ENV{ROS_VERSION} EQUAL 1)
    find_package(catkin REQUIRED)

    # 把头文件和库拷到 devel（catkin_make 习惯）
    add_custom_target(wheellegged_sdk_lowlevel_copy ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${PROJECT_SOURCE_DIR}/include/limxsdk
            ${CATKIN_DEVEL_PREFIX}/include/limxsdk
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${LIB_FILE}
            ${CATKIN_DEVEL_PREFIX}/lib/
        COMMENT "Copying wheellegged_sdk_lowlevel headers & library to devel"
    )

    # 安装规则（catkin_make install 用）
    install(DIRECTORY include/ DESTINATION ${CATKIN_GLOBAL_INCLUDE_DESTINATION})
    install(FILES ${LIB_FILE} DESTINATION ${CATKIN_GLOBAL_LIB_DESTINATION})
endif()

# ---------- 4. 可选：编译例子 ----------
option(EXAMPLE "Build examples ON/OFF" ON)
if(EXAMPLE)
    add_subdirectory(examples)
endif()