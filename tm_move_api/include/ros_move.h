#pragma once
#include"robot_move_interface.h"
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit_msgs/DisplayRobotState.h>
#include <moveit_msgs/DisplayTrajectory.h>
#include <moveit_msgs/AttachedCollisionObject.h>
#include <moveit_msgs/CollisionObject.h>
#include <moveit_visual_tools/moveit_visual_tools.h>
namespace robot_move_api{
  class RosMove : public RobotMove
  {
  private:
      std::string PLANNING_GROUP ;
      void ros_initial();
      moveit::planning_interface::MoveGroupInterface *_move_group;
      moveit_visual_tools::MoveItVisualTools *_visual_tools;
      const robot_state::JointModelGroup* _joint_model_group;
      const double jump_threshold =0.0;
      const double eef_step = 0.01;
  public:
    RosMove(std::string robotName):RobotMove(robotName){
      ros_initial();
    };
    bool joint_move(std::vector<double> jointTarget, bool isPlan) override;
    bool cartesian_move(std::vector<double> cartesianTarget, bool isPlan) override;
    int get_joint_number() override;
    std::vector<double> get_current_end_effector_position() override;
    std::vector<double> get_current_joint_position() override;
  };
  
}