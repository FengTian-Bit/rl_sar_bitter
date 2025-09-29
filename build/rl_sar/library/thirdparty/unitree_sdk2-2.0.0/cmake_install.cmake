# Install script for directory: /home/tf/rl_sar_bitter/rl_sar_w1/rl_sar_bitter/src/rl_sar/library/thirdparty/unitree_sdk2-2.0.0

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/tf/rl_sar_bitter/rl_sar_w1/rl_sar_bitter/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/tf/rl_sar_bitter/rl_sar_w1/rl_sar_bitter/src/rl_sar/library/thirdparty/unitree_sdk2-2.0.0/include/")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "/home/tf/rl_sar_bitter/rl_sar_w1/rl_sar_bitter/src/rl_sar/library/thirdparty/unitree_sdk2-2.0.0/lib/x86_64/libunitree_sdk2.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/unitree_sdk2" TYPE FILE FILES "/home/tf/rl_sar_bitter/rl_sar_w1/rl_sar_bitter/src/rl_sar/library/thirdparty/unitree_sdk2-2.0.0/cmake/unitree_sdk2Targets.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/unitree_sdk2" TYPE FILE FILES
    "/home/tf/rl_sar_bitter/rl_sar_w1/rl_sar_bitter/build/rl_sar/library/thirdparty/unitree_sdk2-2.0.0/unitree_sdk2Config.cmake"
    "/home/tf/rl_sar_bitter/rl_sar_w1/rl_sar_bitter/build/rl_sar/library/thirdparty/unitree_sdk2-2.0.0/unitree_sdk2ConfigVersion.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/tf/rl_sar_bitter/rl_sar_w1/rl_sar_bitter/build/rl_sar/library/thirdparty/unitree_sdk2-2.0.0/thirdparty/cmake_install.cmake")

endif()

