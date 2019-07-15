#include"../include/ros_move.h"
#include"../include/tm_move_api.h"
#include"iostream"

void use_ros_move_control_robot(){
  robot_move_api::RosMove rosMove("tm_robot"); 
  std::vector<double> jointTarget1{-1.0,0.0,-1.0,0.0,-1.0,0.0};
  rosMove.joint_move(jointTarget1,false);
  ROS_INFO("end Joint target 1");
  auto eePosition1 = rosMove.get_current_end_effector_position();
  std::vector<double> jointTarget2{1.0,1.0,1.0,0.0,1.0,0.0};
  rosMove.joint_move(jointTarget2,false);
  ROS_INFO("end Joint target 2");
  auto eePosition2 = rosMove.get_current_end_effector_position();
  eePosition2[1]-=0.1;
  rosMove.cartesian_move(eePosition2,false);
  ROS_INFO("finish all");
}

void use_robot_point_control(){
  robot_move_api::RosMove rosMove("tm_robot"); 
  robot_move_api::RobotPointControl tmRobot(&rosMove);

  
  //std::vector<double> jointTarget1{-1.0,0.0,-1.0,0.0,-1.0,0.0};
  std::vector<double> jointTarget2{0.0,0.0,90.0,0.0,90.0,0.0};
  //tmRobot.record_position_joint("joint_target_1",jointTarget1);
  tmRobot.record_postion_joint_degree("joint_target_2",jointTarget2);
  //tmRobot.move_recorded_poisiton("joint_target_1",false);
  tmRobot.move_recorded_poisiton("joint_target_2",false);


  auto eePosition1 = rosMove.get_current_end_effector_position();
  eePosition1[1]+=0.1;

  tmRobot.record_position_cartesian("cartesian_target_1",eePosition1);

  tmRobot.move_recorded_poisiton("cartesian_target_1",false);
  ROS_INFO("finish all");
}

int main(int argc, char** argv){
  ros::init(argc, argv, "tm_move_api");
  ros::AsyncSpinner spinner(1);
  spinner.start();
  
  use_robot_point_control();
  

  return 0;
}