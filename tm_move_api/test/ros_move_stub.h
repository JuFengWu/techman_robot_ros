#include "../include/robot_move_interface.h"

namespace test_move_api{
  class RosMoveStub : public robot_points_control::RobotMove
  {
  private:
    bool isPlan;
    std::vector<double> currentJointPosition;
    std::vector<double> currentEndEffectorPosition;
  public:
    RosMoveStub(std::string robotName):robot_points_control::RobotMove(robotName){};
    bool joint_move(std::vector<double> jointTarget, bool isPlan) override;
    bool cartesian_move(std::vector<double> cartesianTarget, bool isPlan) override;
    int get_joint_number() override;
    std::vector<double> get_current_end_effector_position() override;
    std::vector<double> get_current_joint_position() override;
    bool get_is_plan();
  };

  bool RosMoveStub::joint_move(std::vector<double> jointTarget, bool isPlan){
      currentJointPosition.clear();
      for(auto jointPosition : jointTarget){
          currentJointPosition.push_back(jointPosition);
      }
      this->isPlan = isPlan;
      return true;
  }
  bool RosMoveStub::cartesian_move(std::vector<double> cartesianTarget, bool isPlan){
      currentEndEffectorPosition.clear();
      for(auto cartesianPosition : cartesianTarget){
          currentEndEffectorPosition.push_back(cartesianPosition);
      }
      this->isPlan = isPlan;
      return true;
  }
  int RosMoveStub::get_joint_number(){
      return 6;
  }
  std::vector<double> RosMoveStub::get_current_end_effector_position(){
      return currentEndEffectorPosition;
  }
  std::vector<double> RosMoveStub::get_current_joint_position(){
      return currentJointPosition;
  }
  bool RosMoveStub::get_is_plan(){
      return isPlan;
  }
}