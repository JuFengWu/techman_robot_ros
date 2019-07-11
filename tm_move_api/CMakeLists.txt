cmake_minimum_required(VERSION 2.8.3)
project(tm_move_api)


find_package(catkin REQUIRED COMPONENTS
  moveit_msgs
  moveit_visual_tools
  moveit_ros_planning_interface
  roscpp
  tm_api_msgs
)

find_package(GTest REQUIRED
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES robot_move
#  CATKIN_DEPENDS moveit_msgs moveit_visual_tools roscpp
#  DEPENDS system_lib
)


include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)



add_executable(tm_move_api src/ros_move.cpp src/tm_move_api.cpp src/move.cpp)
target_link_libraries(tm_move_api ${catkin_LIBRARIES})

set(${PROJECT_NAME}_SOURCES
  service/tm_move_cpp_service.cpp
  service/tm_move_api_connector.cpp
  test/ros_move_stub.cpp
  src/tm_move_api.cpp
  src/ros_move.cpp
   )

add_executable(tm_move_service ${${PROJECT_NAME}_SOURCES})
target_link_libraries(tm_move_service ${catkin_LIBRARIES})
add_dependencies(tm_move_service ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

catkin_add_gtest(test_move_api test/test_move_api.cpp test/ros_move_stub.cpp src/tm_move_api.cpp)
target_link_libraries(test_move_api ${GTEST_LIBRARIES} pthread)
