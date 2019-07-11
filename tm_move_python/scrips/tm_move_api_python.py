import sys
import rospy
from tm_api_msgs.srv import record,move_to_record,delete_point,start_work,get_record
from tm_api_msgs.msg import robot_status
from threading import Thread
import time
import os
sys.path.insert (0,os.path.dirname(os.path.abspath(__file__)))

from utilites import Utilites

class SendRecieveFromService:
    @staticmethod
    def ros_pytho_client(aqqestName,srvMsgName):
        rospy.wait_for_service(aqqestName)
        returnFunction = rospy.ServiceProxy(aqqestName,srvMsgName)
        return returnFunction
    @staticmethod
    def send_record_service(aqqestName,positionName,jointPositionRad,jointPositionDeg,cartesianPosition):
        py_fun = SendRecieveFromService.ros_pytho_client(aqqestName,record)
        res = py_fun(positionName,jointPositionRad,jointPositionDeg,cartesianPosition)
        return res.success
    @staticmethod
    def send_move_to_record_service(aqqestName,positionName, isPlan):
        py_fun = SendRecieveFromService.ros_pytho_client(aqqestName,move_to_record)
        res = py_fun(positionName,isPlan)
        return res.success

    @staticmethod
    def send_delete_to_record_service(positionName,aqqestName):
        py_fun = SendRecieveFromService.ros_pytho_client(aqqestName,delete_point)
        res = py_fun(positionName)
        return res.success
        
    

class TmMoveApiPython:
    def __init__(self,isTest):
        self.isTest = isTest

    def __enter__(self):
        self.currentCartesianPosition = None
        self.currentJointPositionRad = None
        self.currentJointPositionDeg = None
        
        start_work_py_function = SendRecieveFromService.ros_pytho_client("start_work",start_work)
        rospy.wait_for_service("start_work")
        if(self.isTest):
            start_work_py_function(True)
        else:
            start_work_py_function(False)

        self.create_listener()
        
    
    def __exit__(self, exc_type, exc_val, exc_tb):
        print("TmMoveApiPython __exit__ is called ")
        self.cartesianSub.unregister()
        self.jointDegSub.unregister()
        self.jointRadSub.unregister()
        end_work_py_function = SendRecieveFromService.ros_pytho_client("end_work",start_work)
        end_work_py_function()

    def check_data_correct(self,data):  
        if(len(set(data))==1 and data[0] == -999):
            print("it seems not initial before!")
            return None
        return data

    def get_current_cartesian_position(self):
        while(self.currentCartesianPosition == None):
            time.sleep(0.1)
        return self.check_data_correct(self.currentCartesianPosition)

    def get_current_joint_position_rad(self):
        while(self.currentCartesianPosition == None):
            time.sleep(0.1)
        return self.check_data_correct(self.currentJointPositionRad)

    def get_current_joint_position_deg(self):
        while(self.currentCartesianPosition == None):
            time.sleep(0.1)
        return self.check_data_correct(self.currentJointPositionDeg)

    def cartesian_position_callback(self,data):
        self.currentCartesianPosition = data.currentCartesianPosition

    def joint_position_deg_callback(self,data):
        
        self.currentJointPositionDeg = data.currentJointPositionDeg

    def joint_position_rad_callback(self,data):
        self.currentJointPositionRad = data.currentJointPositionRad

    def create_listener(self):
        rospy.init_node('tm_move_python', anonymous=True)
        self.cartesianSub = rospy.Subscriber("currentCartesianPosition", robot_status, self.cartesian_position_callback)
        self.jointDegSub = rospy.Subscriber("currentJointPositionDeg", robot_status, self.joint_position_deg_callback)
        self.jointRadSub = rospy.Subscriber("currentJointPositionRad", robot_status, self.joint_position_rad_callback)
        #print("before spin")
        #rospy.spin()
        #print("after spin")
    
    def except_reaction(self,e):
        print("Service call failed: %s",e)
        return False

    def record_position_joint(self,positionName,jointPosition):
        try:
            print("send record_position_joint to service")
            return SendRecieveFromService.send_record_service("record_position_joint",positionName,jointPosition,None,None)
        except rospy.ServiceException as e:
            return self.except_reaction(e)

    def record_postion_joint_degree(self,positionName,jointPosition):
        try:
            print("send record_postion_joint_degree to service")
            return SendRecieveFromService.send_record_service("record_postion_joint_degree",positionName,None,jointPosition,None)
        except rospy.ServiceException as e:
            return self.except_reaction(e)

    def record_position_cartesian(self,positionName,cartesianPosition):
        try:
            print("send record_position_cartesian to service")
            return SendRecieveFromService.send_record_service("record_position_cartesian",positionName,None,None,cartesianPosition)
        except rospy.ServiceException as e:
            return self.except_reaction(e)

    def move_recorded_poisiton(self,positionName,isPlan):
        try:
            print("send move_recorded_poisiton to service")
            return SendRecieveFromService.send_move_to_record_service("move_recorded_poisiton",positionName,isPlan)
        except rospy.ServiceException as e:
            return self.except_reaction(e)

    def move_recorded_joint_poisiton(self,positionName,isPlan):
        try:
            print("send move_recorded_joint_poisiton to service")
            return SendRecieveFromService.send_move_to_record_service("move_recorded_joint_poisiton",positionName,isPlan)
        except rospy.ServiceException as e:
            return self.except_reaction(e)

    def move_recorded_cartesian_poisiton(self,positionName,isPlan):
        try:
            print("send move_recorded_cartesian_poisiton to service")
            return SendRecieveFromService.send_move_to_record_service("move_recorded_cartesian_poisiton",positionName,isPlan)
        except rospy.ServiceException as e:
            return self.except_reaction(e)
    def checkAllLengthIsCorrect(self,compareVariable,*args):
        length = len(compareVariable)
        for var in args:
            if(length == len(var)):
                continue
            else:
                return False
        return True


    def get_all_recorded_position(self):
        isSuccess,allJointPosition = self.get_recorded_joint_position_deg()
        if(isSuccess):
            isSuccess,allCartesianPosition = self.get_recorded_cartesian_position()
            return isSuccess,allJointPosition,allCartesianPosition
        else:
            return False,None,None

    def get_recorded_joint_position_deg(self):
        try:
            print("send get_recorded_joint_position_deg to service")
            py_fun = SendRecieveFromService.ros_pytho_client("get_recorded_joint_position",get_record)
            res = py_fun()
            allJointPosition = {}
            if(self.checkAllLengthIsCorrect(res.recorded_joint_positions_name,res.j1,res.j2,res.j3,res.j4,res.j5,res.j6)):
                for i in range(len(res.recorded_joint_positions_name)):
                    joints = [res.j1[i],res.j2[i],res.j3[i],res.j4[i],res.j5[i],res.j6[i]]
                    jointsDeg = [ Utilites.rad_to_deg(rad) for rad in joints]
                    allJointPosition[res.recorded_joint_positions_name[i]] = jointsDeg
                return True,allJointPosition
            else:
                print("the lenghth of all joint and joint name is not the same")
                return False,allJointPosition
        except rospy.ServiceException as e:
            return self.except_reaction(e)

    def get_recorded_cartesian_position(self):
        try:
            print("send get_recorded_cartesian_position to service")
            py_fun = SendRecieveFromService.ros_pytho_client("get_recorded_cartesian_position",get_record)
            res = py_fun()
            allCartesianPosition = {}
            if(self.checkAllLengthIsCorrect(res.recorded_cartesian_positions_name,res.c1,res.c2,res.c3,res.c4,res.c5,res.c6,res.c7)):
                for i in range(len(res.recorded_cartesian_positions_name)):
                    cartesianPoint = [res.c1[i],res.c2[i],res.c3[i],res.c4[i],res.c5[i],res.c6[i],res.c7[i]]
                    allCartesianPosition[res.recorded_cartesian_positions_name[i]] = cartesianPoint
                return True,allCartesianPosition
            else:
                print("the lenghth of all joint and joint name is not the same")
                return False,allCartesianPosition
        except rospy.ServiceException as e:
            return self.except_reaction(e)

    

    def delete_recorded_poisiton(self,positionName):
        try:
            print("send delete_recorded_poisiton to service")
            return SendRecieveFromService.send_delete_to_record_service(positionName,"delete_recorded_poisiton")
        except rospy.ServiceException as e:
            return self.except_reaction(e)

    def delete_recorded_joint_poisiton(self,positionName):
        try:
            print("send delete_recorded_joint_poisiton to service")
            return SendRecieveFromService.send_delete_to_record_service(positionName,"delete_recorded_joint_poisiton")
        except rospy.ServiceException as e:
            return self.except_reaction(e)

    def delete_recorded_cartesian_poisiton(self,positionName):
        try:
            print("send delete_recorded_cartesian_poisiton to service")
            return SendRecieveFromService.send_delete_to_record_service(positionName,"delete_recorded_cartesian_poisiton")
        except rospy.ServiceException as e:
            return self.except_reaction(e)

    def delete_all_recorded_position(self):
        try:
            print("send delete_all_recorded_position to service")
            SendRecieveFromService.send_delete_to_record_service(None,"delete_all_recorded_position")
            return True
        except rospy.ServiceException as e:
            return self.except_reaction(e)

    def delete_all_recorded_joint_poisiton(self):
        try:
            print("send delete_all_recorded_joint_poisiton to service")
            SendRecieveFromService.send_delete_to_record_service(None,"delete_all_recorded_joint_poisiton")
            return True
        except rospy.ServiceException as e:
            return self.except_reaction(e)

    def delete_all_recorded_cartesian_poisiton(self):
        try:
            print("send delete_all_recorded_cartesian_poisiton to service")
            SendRecieveFromService.send_delete_to_record_service(None,"delete_all_recorded_cartesian_poisiton")
        except rospy.ServiceException as e:
            return self.except_reaction(e)
