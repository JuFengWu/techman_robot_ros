#pragma once
#include<vector>
#include<string>
namespace robot_points_control{
  class RobotMove{

  private:

  protected:
    std::string _robotName;
  public:
    RobotMove(std::string robotName): _robotName(robotName){};
    int get_cartesian_number(){return 7;}
    virtual bool joint_move(std::vector<double> jointTarget, bool isPlan)=0;
    virtual bool cartesian_move(std::vector<double> cartesianTarget, bool isPlan)=0;
    virtual int get_joint_number()=0;
    virtual std::vector<double> get_current_end_effector_position()=0;
    virtual std::vector<double> get_current_joint_position()=0;
    virtual ~RobotMove(){};
  };
}