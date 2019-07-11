#include "../include/tm_move_api_connector.h"
#include "tm_api_msgs/robot_status.h"
#include "ros/ros.h"
#include <thread>

class TmMoveServiceAndMsgs{
  private:
    ros::NodeHandle n;
    TmMoveApiConnector* robot;
    std::thread publishThread;
    ros::ServiceServer service[16];


    void generateService(){
      robot = new TmMoveApiConnector();
      service[0] = n.advertiseService("start_work", &TmMoveApiConnector::start_work,robot);
      service[1] = n.advertiseService("record_position_joint", &TmMoveApiConnector::record_position_joint_connector,robot);
      service[2]= n.advertiseService("record_postion_joint_degree", &TmMoveApiConnector::record_postion_joint_degree_connector,robot);
      service[3] = n.advertiseService("record_position_cartesian", &TmMoveApiConnector::record_position_cartesian_connector,robot);
      service[4] = n.advertiseService("move_recorded_poisiton", &TmMoveApiConnector::move_recorded_poisiton_connector,robot);
      service[5] = n.advertiseService("move_recorded_joint_poisiton", &TmMoveApiConnector::move_recorded_joint_poisiton_connector,robot);
      service[6] = n.advertiseService("move_recorded_cartesian_poisiton", &TmMoveApiConnector::move_recorded_cartesian_poisiton_connector,robot);
      service[7] = n.advertiseService("get_recorded_joint_position", &TmMoveApiConnector::get_recorded_joint_position_connector,robot);
      service[8] = n.advertiseService("get_recorded_cartesian_position", &TmMoveApiConnector::get_recorded_cartesian_position_connector,robot);
      service[9] = n.advertiseService("delete_recorded_poisiton", &TmMoveApiConnector::delete_recorded_poisiton_connector,robot);
      service[10] = n.advertiseService("delete_recorded_joint_poisiton", &TmMoveApiConnector::delete_recorded_joint_poisiton_connector,robot);
      service[11] = n.advertiseService("delete_recorded_cartesian_poisiton", &TmMoveApiConnector::delete_recorded_cartesian_poisiton_connector,robot);
      service[12] = n.advertiseService("delete_all_recorded_position", &TmMoveApiConnector::delete_all_recorded_position_connector,robot);
      service[13] = n.advertiseService("delete_all_recorded_joint_poisiton", &TmMoveApiConnector::delete_all_recorded_joint_poisiton_connector,robot);
      service[14] = n.advertiseService("delete_all_recorded_cartesian_poisiton", &TmMoveApiConnector::delete_all_recorded_cartesian_poisiton_connector,robot);
      service[15] = n.advertiseService("end_work", &TmMoveApiConnector::end_work,robot);    
      ROS_INFO("success generate service");
    }
    static void generatePublisher(TmMoveApiConnector* robot,ros::NodeHandle &n){
      ros::Publisher cartesianPublisher = n.advertise<tm_api_msgs::robot_status>("currentCartesianPosition", 1);
      ros::Publisher jointPublisherDeg = n.advertise<tm_api_msgs::robot_status>("currentJointPositionDeg", 1);
      ros::Publisher jointPublisherRad = n.advertise<tm_api_msgs::robot_status>("currentJointPositionRad", 1);

      tm_api_msgs::robot_status robotStatus;
      ros::Rate loop_rate(10);
      ROS_INFO("success generate publisher");
      while (ros::ok()){
        robotStatus.currentCartesianPosition = robot->get_current_cartesian();
        
        robotStatus.currentJointPositionDeg = robot->get_current_joint_deg();

        robotStatus.currentJointPositionRad = robot->get_current_joint_rad();

      
        cartesianPublisher.publish(robotStatus);
        jointPublisherDeg.publish(robotStatus);
        jointPublisherRad.publish(robotStatus);

        loop_rate.sleep();
      }
    }
  public:
    TmMoveServiceAndMsgs(){
      generateService();
      publishThread = std::thread(TmMoveServiceAndMsgs::generatePublisher, robot,std::ref(n));
    }
    ~TmMoveServiceAndMsgs(){
      delete robot;
    }
};



int main(int argc, char **argv)
{
  ros::init(argc, argv, "tm_move_service");
  
  TmMoveServiceAndMsgs send{};


  ROS_INFO("Ready to get command");
  ros::AsyncSpinner spinner(2);
  spinner.start();


  ros::waitForShutdown();

  return 0;
}
