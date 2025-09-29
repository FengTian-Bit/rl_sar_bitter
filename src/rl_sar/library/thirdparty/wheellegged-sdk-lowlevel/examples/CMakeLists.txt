cmake_minimum_required(VERSION 3.5)

set(EXAMPLES_BIN_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}/bin)
set(EXAMPLES_LIB_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}/lib)

if (DEFINED CATKIN_DEVEL_PREFIX)
  set(EXAMPLES_BIN_INSTALL_PREFIX ${CATKIN_PACKAGE_BIN_DESTINATION})
  set(EXAMPLES_LIB_INSTALL_PREFIX ${CATKIN_GLOBAL_LIB_DESTINATION})
endif()

find_package(Eigen3 REQUIRED)

include_directories(./)
include_directories(${EIGEN3_INCLUDE_DIR})

set(COMMON_SRCS
  ./common/util.cpp
  ./wl_controller_base.cpp
)

if (WIN32)
  set(LINK_LIBS wheellegged_sdk_lowlevel shlwapi)
else()
  set(LINK_LIBS wheellegged_sdk_lowlevel pthread)
endif()

add_executable(wl_standup wl_standup.cpp ${COMMON_SRCS})
target_link_libraries(wl_standup ${LINK_LIBS})
install(TARGETS wl_standup DESTINATION ${EXAMPLES_BIN_INSTALL_PREFIX})

add_executable(wl_sitdown wl_sitdown.cpp ${COMMON_SRCS})
target_link_libraries(wl_sitdown ${LINK_LIBS})
install(TARGETS wl_sitdown DESTINATION ${EXAMPLES_BIN_INSTALL_PREFIX})

