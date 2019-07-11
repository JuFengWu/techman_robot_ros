#include "../include/tm_move_api_connector.h"
#include"../include/ros_move.h"
#include "../include/utility.h"

bool TmMoveApiConnector::start_work(tm_api_msgs::start_work::Request &req,tm_api_msgs::start_work::Response &res){
    
    if((bool)req.is_test){
        robotMove = new test_move_api::RosMoveStub("test_robot");
    }
    else{
        robotMove = new ros_robot::RosMove("tm_robot");
    }
    ROS_INFO("start_work is called");
    robotPointControl = new robot_points_control::RobotPointControl(robotMove);
    isInitialed = true;
    ROS_INFO("finish start_work");
    return true;
}
bool TmMoveApiConnector::check_initialize(){
    if(isInitialed){
        return true;
    }
    ROS_INFO("please initial robot move api(use 'start_work' function)");
    return false;
}
bool TmMoveApiConnector::check_vector_size_correct(std::vector<double> input,int idealInputSize,std::string errorMessage){
    if(input.size()==(unsigned int)idealInputSize){
        return true;
    }
    std::cout<<errorMessage<<std::endl;
    return false;
}
bool TmMoveApiConnector::record_position_joint_connector(tm_api_msgs::record::Request &req, tm_api_msgs::record::Response &res){
    if(check_initialize() && 
    check_vector_size_correct(req.jointPositionRad,robotMove->get_joint_number(),"send to record_position_joint_connector joint size not correct")){
        res.success = robotPointControl->record_position_joint((std::string)req.positionName,req.jointPositionRad);
        ROS_INFO("record_position_joint is called");
        return true;
    }
    ROS_INFO("error! check initialized before or the input size");
    return false;
}
bool TmMoveApiConnector::record_postion_joint_degree_connector(tm_api_msgs::record::Request &req, tm_api_msgs::record::Response &res){
    ROS_INFO("record_postion_joint_degree_connector is called");
    if(check_initialize() && 
    check_vector_size_correct(req.jointPositionDeg,robotMove->get_joint_number(),"send to record_postion_joint_degree joint size not correct")){
        res.success =robotPointControl->record_postion_joint_degree((std::string)req.positionName,req.jointPositionDeg);
        ROS_INFO("record_postion_joint_degree is called");
        return true;
    }
    ROS_INFO("error! check initialized before or the input size");
    return false;
}
bool TmMoveApiConnector::record_position_cartesian_connector(tm_api_msgs::record::Request &req, tm_api_msgs::record::Response &res){
    if(check_initialize() && 
    check_vector_size_correct(req.cartesianPosition,robotMove->get_cartesian_number(),"send to record_position_cartesian joint size not correct")){
        res.success = robotPointControl->record_position_cartesian((std::string)req.positionName,req.cartesianPosition);
        ROS_INFO("record_position_cartesian is called");
        return true;
    }
    ROS_INFO("error! check initialized before or the input size");
    return false;
}

bool TmMoveApiConnector::move_recorded_poisiton_connector(tm_api_msgs::move_to_record::Request &req, tm_api_msgs::move_to_record::Response &res){
    if(check_initialize()){
        res.success = robotPointControl->move_recorded_poisiton(req.positionName,req.isPlan);
        ROS_INFO("move_recorded_poisiton is called");
        return true;
    }
    ROS_INFO("error! check initialized before");
    return false;
}
bool TmMoveApiConnector::move_recorded_joint_poisiton_connector(tm_api_msgs::move_to_record::Request &req, tm_api_msgs::move_to_record::Response &res){
    if(check_initialize()){
        res.success = robotPointControl->move_recorded_joint_poisiton(req.positionName,req.isPlan);
        ROS_INFO("move_recorded_joint_poisiton is called");
        return true;
    }
    ROS_INFO("error! check initialized before");
    return false;
}
bool TmMoveApiConnector::move_recorded_cartesian_poisiton_connector(tm_api_msgs::move_to_record::Request &req, tm_api_msgs::move_to_record::Response &res){
    if(check_initialize()){
        res.success = robotPointControl->move_recorded_cartesian_poisiton(req.positionName,req.isPlan);
        ROS_INFO("move_recorded_cartesian_poisiton is called");
        return true;
    }
    ROS_INFO("error! check initialized before");
    return false;
}
bool TmMoveApiConnector::get_recorded_joint_position_connector(tm_api_msgs::get_record::Request &req, tm_api_msgs::get_record::Response &res){
    if(check_initialize()){
        ROS_INFO("get_recorded_joint_position start called");
        auto jointPositions= robotPointControl->get_recorded_joint_position();
        std::vector<std::string> name;
        std::vector<double> j1,j2,j3,j4,j5,j6;
        for (const auto& kv : jointPositions) {
            name.push_back(kv.first);
            j1.push_back(kv.second[0]);j2.push_back(kv.second[1]);j3.push_back(kv.second[2]);
            j4.push_back(kv.second[3]);j5.push_back(kv.second[4]);j6.push_back(kv.second[5]);
        }
        res.recorded_joint_positions_name = name;
        res.j1 = j1;res.j2 = j2;res.j3 = j3;
        res.j4 = j4;res.j5 = j5;res.j6 = j6;
        ROS_INFO("get_recorded_joint_position is called");
        return true;
    }
    ROS_INFO("error! check initialized before");
    return false;
}
bool TmMoveApiConnector::get_recorded_cartesian_position_connector(tm_api_msgs::get_record::Request &req, tm_api_msgs::get_record::Response &res){
    if(check_initialize()){
        auto cartesianPositions= robotPointControl->get_recorded_cartesian_position();
        std::vector<std::string> name;
        std::vector<double> c1,c2,c3,c4,c5,c6,c7;
        for (const auto& kv : cartesianPositions) {
            name.push_back(kv.first);
            c1.push_back(kv.second[0]);c2.push_back(kv.second[1]);c3.push_back(kv.second[2]);
            c4.push_back(kv.second[3]);c5.push_back(kv.second[4]);c6.push_back(kv.second[5]);
            c7.push_back(kv.second[6]);
        }
        res.recorded_cartesian_positions_name = name;
        res.c1 = c1;res.c2 = c2;res.c3 = c3;
        res.c4 = c4;res.c5 = c5;res.c6 = c6;
        res.c7 = c7;
        ROS_INFO("get_recorded_cartesian_position is called");
        return true;
    }
    ROS_INFO("error! check initialized before");
    return false;
}

bool TmMoveApiConnector::delete_recorded_poisiton_connector(tm_api_msgs::delete_point::Request &req, tm_api_msgs::delete_point::Response &res){
    if(check_initialize()){
        res.success = robotPointControl->delete_recorded_poisiton(req.positionName);
        ROS_INFO("delete_recorded_poisiton is called");
        return true;
    }
    ROS_INFO("error! check initialized before");
    return false;
}
bool TmMoveApiConnector::delete_recorded_joint_poisiton_connector(tm_api_msgs::delete_point::Request &req, tm_api_msgs::delete_point::Response &res){
    if(check_initialize()){
        res.success = robotPointControl->delete_recorded_joint_poisiton(req.positionName);
        ROS_INFO("delete_recorded_joint_poisiton is called");
        return true;
    }
    ROS_INFO("error! check initialized before");
    return false;
}
bool TmMoveApiConnector::delete_recorded_cartesian_poisiton_connector(tm_api_msgs::delete_point::Request &req, tm_api_msgs::delete_point::Response &res){
    if(check_initialize()){
        res.success = robotPointControl->delete_recorded_cartesian_poisiton(req.positionName);
        ROS_INFO("delete_recorded_cartesian_poisiton is called");
        return true;
    }
    ROS_INFO("error! check initialized before");
    return false;
}

bool TmMoveApiConnector::delete_all_recorded_position_connector(tm_api_msgs::delete_point::Request &req, tm_api_msgs::delete_point::Response &res){
    if(check_initialize()){
        robotPointControl->delete_all_recorded_position();
        ROS_INFO("delete_all_recorded_position is called");
        return true;
    }
    ROS_INFO("error! check initialized before");
    return false;
}
bool TmMoveApiConnector::delete_all_recorded_joint_poisiton_connector(tm_api_msgs::delete_point::Request &req, tm_api_msgs::delete_point::Response &res){
    if(check_initialize()){
        robotPointControl->delete_all_recorded_joint_poisiton();
        ROS_INFO("delete_all_recorded_joint_poisiton is called");
        return true;
    }
    ROS_INFO("error! check initialized before");
    return false;
}
bool TmMoveApiConnector::delete_all_recorded_cartesian_poisiton_connector(tm_api_msgs::delete_point::Request &req, tm_api_msgs::delete_point::Response &res){
    if(check_initialize()){
        robotPointControl->delete_all_recorded_cartesian_poisiton();
        ROS_INFO("delete_all_recorded_cartesian_poisiton is called");
        return true;
    }
    ROS_INFO("error! check initialized before");
    return false;
}
std::vector<double> TmMoveApiConnector::get_current_joint_rad(){
    if(isInitialed){
        
        return robotMove->get_current_joint_position();
    }
    std::vector<double> voidVector = {-999,-999,-999,-999,-999,-999};
    return voidVector;
    
}
std::vector<double> TmMoveApiConnector::get_current_joint_deg(){
    if(isInitialed){
        auto jointPositions = robotMove->get_current_joint_position();
        std::vector<double> re;
        for(auto joint : jointPositions){
            auto jointDeg = Utilities::rad_to_degree(joint);
            re.push_back(jointDeg);
        }
        return re;
    }
    std::vector<double> voidVector = {-999,-999,-999,-999,-999,-999};
    return voidVector;
}
std::vector<double> TmMoveApiConnector::get_current_cartesian(){
    if(isInitialed){
        return robotMove->get_current_end_effector_position();
    }
    std::vector<double> voidVector = {-999,-999,-999,-999,-999,-999,-999};
    return voidVector;
}
bool TmMoveApiConnector::end_work(tm_api_msgs::start_work::Request &req,tm_api_msgs::start_work::Response &res){
    ROS_INFO("end_work is called");

    if(isInitialed){
        isInitialed = false;
        delete robotMove;
        ROS_INFO("delete robotMove is called");
        return true;
    }
    else{
        ROS_INFO("delete it is before!!!");
        return true;
    }
    
}
