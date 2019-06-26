#include "../include/ros_move.h"

#include<string>
namespace ros_robot{
    void RosMove::ros_initial(){
        
        ros::NodeHandle node_handle;
        
        PLANNING_GROUP = "arm";
        _move_group = new moveit::planning_interface::MoveGroupInterface(PLANNING_GROUP);
        _joint_model_group =_move_group->getCurrentState()->getJointModelGroup(PLANNING_GROUP);
        _visual_tools = new moveit_visual_tools::MoveItVisualTools("base_link");      
        
    }
    bool RosMove::joint_move(std::vector<double> jointTarget, bool isPlan){
        _move_group->setJointValueTarget(jointTarget);
        bool success;
        if(isPlan){
            moveit::planning_interface::MoveGroupInterface::Plan my_plan;
            success = (_move_group->plan(my_plan) == moveit::planning_interface::MoveItErrorCode::SUCCESS);            
            ROS_INFO("B");
        }
        else
        {
            _move_group->move();
            success = true;
        }
        return success;
    }

    bool RosMove::cartesian_move(std::vector<double> cartesianTarget, bool isPlan){
       
        geometry_msgs::Pose target_pose1;
        target_pose1.orientation.w = cartesianTarget[3];
        target_pose1.orientation.x = cartesianTarget[4];
        target_pose1.orientation.y = cartesianTarget[5];
        target_pose1.orientation.z = cartesianTarget[6];
        target_pose1.position.x = cartesianTarget[0];
        target_pose1.position.y = cartesianTarget[1];
        target_pose1.position.z = cartesianTarget[2];
        std::vector<geometry_msgs::Pose> waypoint;
        waypoint.push_back(target_pose1);
        moveit_msgs::RobotTrajectory trajectory;

        moveit::planning_interface::MoveGroupInterface::Plan my_plan;
        //bool success = (_move_group->plan(my_plan) == moveit::planning_interface::MoveItErrorCode::SUCCESS);
        //double fraction = _move_group->computeCartesianPath(waypoint, eef_step, jump_threshold, trajectory);
        _move_group->computeCartesianPath(waypoint, eef_step, jump_threshold, trajectory);

        if(!isPlan){
            my_plan.trajectory_ = trajectory;
            _move_group->execute(my_plan);
        }
        return true;
    }
    int RosMove::get_joint_number(){
        std::vector<double> joint_group_positions;
        moveit::core::RobotStatePtr current_state = _move_group->getCurrentState();
        current_state->copyJointGroupPositions(_joint_model_group, joint_group_positions);
        return joint_group_positions.size();
    }
    std::vector<double> RosMove::get_current_end_effector_position(){
        geometry_msgs::Pose pose = _move_group->getCurrentPose().pose;
        std::vector<double> endEffectorPosition;
        endEffectorPosition.push_back(pose.position.x);
        endEffectorPosition.push_back(pose.position.y);
        endEffectorPosition.push_back(pose.position.z);
        endEffectorPosition.push_back(pose.orientation.w);
        endEffectorPosition.push_back(pose.orientation.x);
        endEffectorPosition.push_back(pose.orientation.y);
        endEffectorPosition.push_back(pose.orientation.z);
        return endEffectorPosition;
    }
    std::vector<double> RosMove::get_current_joint_position(){
        std::vector<double> joint_group_positions;
        moveit::core::RobotStatePtr current_state = _move_group->getCurrentState();
        current_state->copyJointGroupPositions(_joint_model_group, joint_group_positions);
        return joint_group_positions;
    }
}