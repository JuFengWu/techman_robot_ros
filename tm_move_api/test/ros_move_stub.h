#pragma once
#include "../include/robot_move_interface.h"

namespace test_move_api{
  class RosMoveStub : public robot_move_api::RobotMove
  {
  private:
    bool isPlan;
    std::vector<double> currentJointPosition;
    std::vector<double> currentEndEffectorPosition;
  public:
    RosMoveStub(std::string robotName):robot_move_api::RobotMove(robotName){};
    bool joint_move(std::vector<double> jointTarget, bool isPlan) override;
    bool cartesian_move(std::vector<double> cartesianTarget, bool isPlan) override;
    int get_joint_number() override;
    std::vector<double> get_current_end_effector_position() override;
    std::vector<double> get_current_joint_position() override;
    bool get_is_plan();
  };

  
}