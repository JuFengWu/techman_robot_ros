from tm_move_api_python import TmMoveApiPython
import rospy
if __name__ == "__main__":
    tmMove = TmMoveApiPython(False)
    with tmMove:
        j1 = [0,0,90,0,90,0]
        tmMove.record_postion_joint_degree("j1",j1)
        j2 = [0,0,90,0,90,90]
        tmMove.record_postion_joint_degree("j2",j2)
        tmMove.move_recorded_joint_poisiton("j1",False)
        tmMove.move_recorded_joint_poisiton("j2",False)

        currentCartesianPosition = tmMove.get_current_cartesian_position()
        print(len(currentCartesianPosition))
        print("tmMove.currentCartesianPosition is")
        print(currentCartesianPosition)
        currentJointPositionRad = tmMove.get_current_joint_position_rad()
        print(len(currentCartesianPosition))
        print("tmMove.currentJointPositionRad")
        print(currentJointPositionRad)
        print("tmMove.currentJointPositionDeg")
        print(tmMove.get_current_joint_position_deg())
    #rospy.spin()