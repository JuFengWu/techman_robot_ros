from  scrips import tm_move_api_python
import unittest
import time

#TODO: let it delete!!!!


class TestTmMovePython(unittest.TestCase):
    def setUp(self):
        
        self.tmMove = tm_move_api_python.TmMoveApiPython(True)

        
    def test_position_joint(self):

        with self.tmMove:
            joint1 = [1,2,3,4,5,6]
            joint2 = [3,4,5,6,7,8]
            self.tmMove.record_postion_joint_degree("j1",joint1)
            self.tmMove.record_postion_joint_degree("j2",joint2)
            self.tmMove.move_recorded_poisiton("j1",True)
            time.sleep(0.5)
            self.assertEqual(joint1,list( self.tmMove.get_current_joint_position_deg()))
                
            self.tmMove.move_recorded_poisiton("j2",False)
            time.sleep(0.5)
            self.assertEqual(joint2,list(self.tmMove.get_current_joint_position_deg()))

            jointPositions = {}
            jointPositions["j1"] = joint1
            jointPositions["j2"] = joint2
            isSuccess,allJointPosition = self.tmMove.get_recorded_joint_position_deg()
            self.assertTrue(isSuccess)
            self.assertEqual(jointPositions,(allJointPosition))

            self.tmMove.delete_recorded_joint_poisiton("j1")
            jointPosition2 = {}
            jointPosition2["j2"] = joint2
            isSuccess,allJointPosition = self.tmMove.get_recorded_joint_position_deg()
            self.assertTrue(isSuccess)
            self.assertEqual(jointPosition2,allJointPosition)

            jointPositionNull = {}
            self.tmMove.delete_all_recorded_joint_poisiton()
            isSuccess,allJointPosition = self.tmMove.get_recorded_joint_position_deg()
            self.assertTrue(isSuccess)
            self.assertEqual(jointPositionNull,allJointPosition)
        
    def test_cartesian_move(self):

        with self.tmMove:
            position1 = [1,2,3,4,5,6,7]
            position2 = [2,3,4,5,6,7,8]
            self.tmMove.record_position_cartesian("p1",position1)
            self.tmMove.record_position_cartesian("p2",position2)
            self.tmMove.move_recorded_poisiton("p1",True)
            time.sleep(1)
            self.assertEqual(position1,list( self.tmMove.get_current_cartesian_position()))

            self.tmMove.move_recorded_poisiton("p2",False)
            time.sleep(1)
            self.assertEqual(position2,list( self.tmMove.get_current_cartesian_position()))

            positions = {}
            positions["p1"] = position1
            positions["p2"] = position2
            isSuccess,allPositions = self.tmMove.get_recorded_cartesian_position()
            self.assertTrue(isSuccess)
            self.assertEqual(positions,allPositions)
                
            self.tmMove.delete_recorded_cartesian_poisiton("p1")
            positions1 = {}
            positions1["p2"] = position2
            isSuccess,allPositions = self.tmMove.get_recorded_cartesian_position()
            self.assertTrue(isSuccess)
            self.assertEqual(positions1,allPositions)

            positionNull = {}
            self.tmMove.delete_all_recorded_cartesian_poisiton()
            isSuccess,allPositions = self.tmMove.get_recorded_cartesian_position()
            self.assertTrue(isSuccess)
            self.assertEqual(positionNull,allPositions)

    def test_cartesian_joint(self):

        with self.tmMove:
            jointPosition = [1,2,3,4,5,6]
            cartesianosition = [1,2,3,4,5,6,7]
            self.tmMove.record_postion_joint_degree("j1",jointPosition)
            self.tmMove.record_position_cartesian("p1",cartesianosition)
            self.tmMove.move_recorded_poisiton("j1",False)
            time.sleep(1)
            self.assertEqual(jointPosition,list( self.tmMove.get_current_joint_position_deg()))

            self.tmMove.move_recorded_poisiton("p1",False)
            time.sleep(1)
            self.assertEqual(cartesianosition,list( self.tmMove.get_current_cartesian_position()))

            ansJointPosition={}
            ansJointPosition["j1"] = jointPosition
            ansCartesianPosition = {}
            ansCartesianPosition["p1"] = cartesianosition
            isSuccess,allJointPosition,allCartesianPosition = self.tmMove.get_all_recorded_position()
            self.assertTrue(isSuccess)
            self.assertEqual(ansJointPosition,allJointPosition)
            self.assertEqual(ansCartesianPosition,allCartesianPosition)

            self.tmMove.delete_recorded_poisiton("p1")
            ansJointPosition1={}
            ansJointPosition1["j1"] = jointPosition
            ansCartesianPosition1 = {}
            isSuccess,allJointPosition,allCartesianPosition = self.tmMove.get_all_recorded_position()
            self.assertTrue(isSuccess)
            self.assertEqual(ansJointPosition1,allJointPosition)
            self.assertEqual(ansCartesianPosition1,allCartesianPosition)

            self.tmMove.delete_all_recorded_position()
            nullPosition={}
            isSuccess,allJointPosition,allCartesianPosition = self.tmMove.get_all_recorded_position()
            self.assertTrue(isSuccess)
            self.assertEqual(nullPosition,allJointPosition)
            self.assertEqual(nullPosition,allCartesianPosition)


if __name__ == "__main__":
    unittest.main()
 
