#pragma once
#include "tm_move_api.h"
#include "../test/ros_move_stub.h"
#include "tm_api_msgs/start_work.h"
#include "tm_api_msgs/record.h"
#include "tm_api_msgs/move_to_record.h"
#include "tm_api_msgs/get_record.h"
#include "tm_api_msgs/delete_point.h"



class TmMoveApiConnector
{
private:
    robot_points_control::RobotPointControl* robotPointControl;
    robot_points_control::RobotMove* robotMove;
    bool isInitialed;
    bool check_initialize();
    bool check_vector_size_correct(std::vector<double> input,int idealInputSize,std::string errorMessage);
public:
    TmMoveApiConnector(){
        isInitialed = false;
    }
    bool start_work(tm_api_msgs::start_work::Request &req,tm_api_msgs::start_work::Response &res);

    bool record_position_joint_connector(tm_api_msgs::record::Request &req, tm_api_msgs::record::Response &res);
    bool record_postion_joint_degree_connector(tm_api_msgs::record::Request &req, tm_api_msgs::record::Response &res);
    bool record_position_cartesian_connector(tm_api_msgs::record::Request &req, tm_api_msgs::record::Response &res);

    bool move_recorded_poisiton_connector(tm_api_msgs::move_to_record::Request &req, tm_api_msgs::move_to_record::Response &res);
    bool move_recorded_joint_poisiton_connector(tm_api_msgs::move_to_record::Request &req, tm_api_msgs::move_to_record::Response &res);
    bool move_recorded_cartesian_poisiton_connector(tm_api_msgs::move_to_record::Request &req, tm_api_msgs::move_to_record::Response &res);

    bool get_recorded_joint_position_connector(tm_api_msgs::get_record::Request &req, tm_api_msgs::get_record::Response &res);
    bool get_recorded_cartesian_position_connector(tm_api_msgs::get_record::Request &req, tm_api_msgs::get_record::Response &res);

    bool delete_recorded_poisiton_connector(tm_api_msgs::delete_point::Request &req, tm_api_msgs::delete_point::Response &res);
    bool delete_recorded_joint_poisiton_connector(tm_api_msgs::delete_point::Request &req, tm_api_msgs::delete_point::Response &res);
    bool delete_recorded_cartesian_poisiton_connector(tm_api_msgs::delete_point::Request &req, tm_api_msgs::delete_point::Response &res);

    bool delete_all_recorded_position_connector(tm_api_msgs::delete_point::Request &req, tm_api_msgs::delete_point::Response &res);
    bool delete_all_recorded_joint_poisiton_connector(tm_api_msgs::delete_point::Request &req, tm_api_msgs::delete_point::Response &res);
    bool delete_all_recorded_cartesian_poisiton_connector(tm_api_msgs::delete_point::Request &req, tm_api_msgs::delete_point::Response &res);

    std::vector<double> get_current_joint_rad();
    std::vector<double> get_current_joint_deg();
    std::vector<double> get_current_cartesian();

    bool end_work(tm_api_msgs::start_work::Request &req,tm_api_msgs::start_work::Response &res);
};





  
