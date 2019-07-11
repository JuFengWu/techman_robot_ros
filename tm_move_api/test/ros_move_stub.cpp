#include"ros_move_stub.h"

bool test_move_api::RosMoveStub::joint_move(std::vector<double> jointTarget, bool isPlan){
      currentJointPosition.clear();
      for(auto jointPosition : jointTarget){
          currentJointPosition.push_back(jointPosition);
      }
      this->isPlan = isPlan;
      return true;
  }
  bool test_move_api::RosMoveStub::cartesian_move(std::vector<double> cartesianTarget, bool isPlan){
      currentEndEffectorPosition.clear();
      for(auto cartesianPosition : cartesianTarget){
          currentEndEffectorPosition.push_back(cartesianPosition);
      }
      this->isPlan = isPlan;
      return true;
  }
  int test_move_api::RosMoveStub::get_joint_number(){
      return 6;
  }
  std::vector<double> test_move_api::RosMoveStub::get_current_end_effector_position(){
      return currentEndEffectorPosition;
  }
  std::vector<double> test_move_api::RosMoveStub::get_current_joint_position(){
      return currentJointPosition;
  }
  bool test_move_api::RosMoveStub::get_is_plan(){
      return isPlan;
  }