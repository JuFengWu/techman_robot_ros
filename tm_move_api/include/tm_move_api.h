#pragma once
#include<vector>
#include<string>
#include <map>
#include<iostream>
#include"robot_move_interface.h"


namespace robot_points_control{
  

  class RobotRecordPoint{
  private:
    std::map<std::string,std::vector<double> > positions;
    bool findPosition(std::string positionName, std::vector<double>& position);
  protected:
    virtual bool is_input_number_correct(std::vector<double> input)=0;
    virtual bool move_to_target_position(std::vector<double> position,bool isPlan) = 0;
    RobotMove* _robot;
  public:
    RobotRecordPoint(RobotMove* robot):_robot(robot){};
    void record_position(std::string positionName,std::vector<double> position);
    bool move_and_check_recorded_position(std::string positionName,bool isPlan);
    std::map<std::string,std::vector<double> >get_recorded_position();
    bool delete_recorded_poisitons(std::string positionName);
    void delete_all_recorded_positions();
  };
  
  class RobotRecordJoints : public RobotRecordPoint{
  protected:
    bool is_input_number_correct(std::vector<double> input) override;
    bool move_to_target_position(std::vector<double> position,bool isPlan) override;
  public:
    RobotRecordJoints(RobotMove* robot):RobotRecordPoint(robot){};
  };
  
  class RobotRecordCartesianPositions : public RobotRecordPoint{
  protected:
    bool is_input_number_correct(std::vector<double> input) override;
    bool move_to_target_position(std::vector<double> position,bool isPlan) override;
  public:
    RobotRecordCartesianPositions(RobotMove* robot):RobotRecordPoint(robot){};
  };
  
  class RobotPointControl{
  private:
    RobotMove* _robot;
    RobotRecordJoints jointPositions;
    RobotRecordCartesianPositions cartesianPositions;
    
    std::map<std::string,std::vector<double> > get_two_position(RobotRecordPoint* first, RobotRecordPoint* second);
  public:
    RobotPointControl(RobotMove* robot):_robot(robot),jointPositions(robot),cartesianPositions(robot){};
    bool record_position_joint(std::string positionName,std::vector<double> jointPosition);
    bool record_postion_joint_degree(std::string positionName,std::vector<double> jointPosition);
    bool record_position_cartesian(std::string positionName,std::vector<double> cartesianPosition);
    
    bool move_recorded_poisiton(std::string positionName,bool isPlan);
    bool move_recorded_joint_poisiton(std::string positionName,bool isPlan);
    bool move_recorded_cartesian_poisiton(std::string positionName,bool isPlan);

    std::map<std::string,std::vector<double> > get_all_recorded_position(bool isJointShowFirst);
    std::map<std::string,std::vector<double> > get_recorded_joint_position();
    std::map<std::string,std::vector<double> > get_recorded_cartesian_position();

    bool delete_recorded_poisiton(std::string positionName);
    bool delete_recorded_joint_poisiton(std::string positionName);
    bool delete_recorded_cartesian_poisiton(std::string positionName);

    void delete_all_recorded_position();
    void delete_all_recorded_joint_poisiton();
    void delete_all_recorded_cartesian_poisiton();   
  };
}
