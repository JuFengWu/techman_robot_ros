
#include"../include/tm_move_api.h"
#include "../include/utility.h"
#include <map>
namespace robot_points_control{
  
  void RobotRecordPoint::record_position(std::string positionName,std::vector<double> position){
    if(this->is_input_number_correct(position)){
	  this->positions.insert(std::pair<std::string, std::vector<double> >(positionName,position));
      }
      else{
        throw "input number is not correct\n";
    }
  }
  bool RobotRecordPoint::findPosition(std::string positionName, std::vector<double>& position){
    std::map<std::string, std::vector<double> >::iterator foundPosition;
    foundPosition = positions.find(positionName);
    if(foundPosition != positions.end()){
      position = foundPosition->second;
      return true;
    }
    else{
      return false;
    }
  }
  bool RobotRecordPoint::move_and_check_recorded_position(std::string positionName, bool isPlan){
    std::vector<double> position;
    if(findPosition(positionName,position)){

      move_to_target_position(position,isPlan);
      return true;
    }
    else{
      return false;
    }
  }
  
  std::map<std::string,std::vector<double> > RobotRecordPoint::get_recorded_position(){
    std::map<std::string,std::vector<double> > re(positions);
    
    return re;
  }
  bool RobotRecordPoint::delete_recorded_poisitons(std::string positionName){
    std::vector<double> position;
    if(findPosition(positionName,position)){
      positions.erase(positionName);
      return true;
    }
    else{
      return false;
    }
  }
  void RobotRecordPoint::delete_all_recorded_positions(){
    positions.erase(positions.begin(),positions.end());
  }
  bool RobotRecordJoints::move_to_target_position(std::vector<double> position,bool isPlan){
    return _robot->joint_move(position,isPlan);
  }
  bool RobotRecordJoints::is_input_number_correct(std::vector<double> input){
    if(input.size()!=(unsigned int)_robot->get_joint_number()){
      return false;
    }
    return true;
  }
  bool RobotRecordCartesianPositions::move_to_target_position(std::vector<double> position,bool isPlan){
    return _robot->cartesian_move(position,isPlan);
  }
  bool RobotRecordCartesianPositions::is_input_number_correct(std::vector<double> input){
    if(input.size()!= (unsigned int)_robot->get_cartesian_number()){
      return false;
    }
    return true;
  }

  bool RobotPointControl::record_postion_joint_degree(std::string positionName,std::vector<double> jointDegree){
    std::vector<double> jointRad;
    for (double degree : jointDegree){
      jointRad.push_back(Utilities::degree_to_rad(degree));
    }
    return record_position_joint(positionName,jointRad);
  }
  
  bool RobotPointControl::record_position_joint(std::string positionName,std::vector<double> jointPosition){
    try{
      jointPositions.record_position(positionName,jointPosition);
      return true;
    }
    catch(const char * str){
      std::cout<<str<<std::endl;
      return false;
    }
    
  }
  bool RobotPointControl::record_position_cartesian(std::string positionName,std::vector<double> cartesianPosition){
    try{
      cartesianPositions.record_position(positionName,cartesianPosition);
      return true;
    }
    catch(const char * str){
      std::cout<<str<<std::endl;
      return false;
    }
  }
    
  bool RobotPointControl::move_recorded_poisiton(std::string positionName,bool isPlan){
    if(jointPositions.move_and_check_recorded_position(positionName,isPlan)){
      return true;
    }
    else if(cartesianPositions.move_and_check_recorded_position(positionName,isPlan)){
      return true;
    }
    else{
      std::cout<<"the position is not exist!"<<std::endl;
      return false;
    }
  }
  bool RobotPointControl::move_recorded_joint_poisiton(std::string positionName,bool isPlan){
    if(!jointPositions.move_and_check_recorded_position(positionName,isPlan)){
      std::cout<<"the position is not exist!"<<std::endl;
      return false;
    }
    return true;
  }
  bool RobotPointControl::move_recorded_cartesian_poisiton(std::string positionName,bool isPlan){
    if(!cartesianPositions.move_and_check_recorded_position(positionName,isPlan)){
      std::cout<<"the position is not exist!"<<std::endl;
      return false;
    }
    return true;
  }
  std::map<std::string,std::vector<double> > RobotPointControl::get_two_position(RobotRecordPoint* first, RobotRecordPoint* second){
    std::map<std::string,std::vector<double> > re(first->get_recorded_position());
    for(auto item : second->get_recorded_position()){
      re.insert(item);
    }
    return re;
  }
  std::map<std::string,std::vector<double> > RobotPointControl::get_all_recorded_position(bool isJointShowFirst){
    
    if(isJointShowFirst){
      return get_two_position(&jointPositions,&cartesianPositions);
    }
    else{
      return get_two_position(&cartesianPositions,&jointPositions);
    }
  }
  std::map<std::string,std::vector<double> > RobotPointControl::get_recorded_joint_position(){
    return jointPositions.get_recorded_position();
  }
  std::map<std::string,std::vector<double> > RobotPointControl::get_recorded_cartesian_position(){
    return cartesianPositions.get_recorded_position();
  }

  bool RobotPointControl::delete_recorded_poisiton(std::string positionName){
    if(jointPositions.delete_recorded_poisitons(positionName)){
      return true;  
    }
    else if(cartesianPositions.delete_recorded_poisitons(positionName)){
      return true;
    }
    else{
      return false;
    }
  }
  bool RobotPointControl::delete_recorded_joint_poisiton(std::string positionName){
    return jointPositions.delete_recorded_poisitons(positionName);
  }
  bool RobotPointControl::delete_recorded_cartesian_poisiton(std::string positionName){
    return cartesianPositions.delete_recorded_poisitons(positionName);
  }

  void RobotPointControl::delete_all_recorded_position(){
    jointPositions.delete_all_recorded_positions();
    cartesianPositions.delete_all_recorded_positions();
  }
  void RobotPointControl::delete_all_recorded_joint_poisiton(){
    jointPositions.delete_all_recorded_positions();
  }
  void RobotPointControl::delete_all_recorded_cartesian_poisiton(){
    cartesianPositions.delete_all_recorded_positions();
  }
}