#include <gtest/gtest.h>
#include "ros_move_stub.h"
#include"../include/tm_move_api.h"

class TestMoveApi : public testing::Test
{
protected:
    test_move_api::RosMoveStub *rosMoveStub;
    robot_move_api::RobotPointControl *testRobot;
    virtual void SetUp(){
        rosMoveStub = new test_move_api::RosMoveStub("test_robot");
        testRobot = new robot_move_api::RobotPointControl(rosMoveStub);
    }
    virtual void TearDown(){
        delete this->testRobot;
        delete this->rosMoveStub;
    }
};

TEST_F(TestMoveApi, positionJoint){
    std::vector<double> joint1 = {1,2,3,4,5,6};
    std::vector<double> joint2 = {3,4,5,6,7,8};
    testRobot->record_position_joint("joint1",joint1);
    testRobot->record_position_joint("joint2",joint2);
    testRobot->move_recorded_joint_poisiton("joint1",true);
    EXPECT_EQ(joint1,rosMoveStub->get_current_joint_position());
    ASSERT_TRUE(rosMoveStub->get_is_plan());
    
    testRobot->move_recorded_poisiton("joint2",false);
    EXPECT_EQ(joint2,rosMoveStub->get_current_joint_position());
    ASSERT_FALSE(rosMoveStub->get_is_plan());

    std::map<std::string,std::vector<double> > jointPosition;
    jointPosition.insert(std::pair<std::string, std::vector<double> >("joint1",joint1));
    jointPosition.insert(std::pair<std::string, std::vector<double> >("joint2",joint2));
    EXPECT_EQ(jointPosition,testRobot->get_recorded_joint_position());

    testRobot->delete_recorded_joint_poisiton("joint1");
    std::map<std::string,std::vector<double> > jointPosition2;
    jointPosition2.insert(std::pair<std::string, std::vector<double> >("joint2",joint2));
    EXPECT_EQ(jointPosition2,testRobot->get_recorded_joint_position());

    testRobot->delete_all_recorded_joint_poisiton();
    std::map<std::string,std::vector<double> > jointPositionNull;
    EXPECT_EQ(jointPositionNull,testRobot->get_recorded_joint_position());
}

TEST_F(TestMoveApi,cartesianPosition){
    std::vector<double> position1 = {1,2,3,4,5,6,7};
    std::vector<double> position2 = {2,3,4,5,6,7,8};
    testRobot->record_position_cartesian("position1",position1);
    testRobot->record_position_cartesian("position2",position2);
    testRobot->move_recorded_poisiton("position1",true);
    EXPECT_EQ(position1,rosMoveStub->get_current_end_effector_position());
    ASSERT_TRUE(rosMoveStub->get_is_plan());

    testRobot->move_recorded_cartesian_poisiton("position2",false);
    EXPECT_EQ(position2,rosMoveStub->get_current_end_effector_position());
    ASSERT_FALSE(rosMoveStub->get_is_plan());

    std::map<std::string,std::vector<double> > positions;
    positions.insert(std::pair<std::string, std::vector<double> >("position1",position1));
    positions.insert(std::pair<std::string, std::vector<double> >("position2",position2));
    EXPECT_EQ(positions,testRobot->get_recorded_cartesian_position());

    testRobot->delete_recorded_cartesian_poisiton("position1");
    std::map<std::string,std::vector<double> > onePosition;
    onePosition.insert(std::pair<std::string, std::vector<double> >("position2",position2));
    EXPECT_EQ(onePosition,testRobot->get_recorded_cartesian_position());

    testRobot->delete_all_recorded_cartesian_poisiton();
    std::map<std::string,std::vector<double> > positionNull;
    EXPECT_EQ(positionNull,testRobot->get_recorded_cartesian_position());
}

TEST_F(TestMoveApi,cartesianAndJointTest){
    
    std::vector<double> jointPosition = {1,2,3,4,5,6};
    std::vector<double> cartesianosition = {1,2,3,4,5,6,7};
    testRobot->record_position_joint("jointPosition",jointPosition);
    testRobot->record_position_cartesian("cartesianosition",cartesianosition);
    testRobot->move_recorded_poisiton("jointPosition",true);
    EXPECT_EQ(jointPosition,rosMoveStub->get_current_joint_position());
    
    testRobot->move_recorded_poisiton("cartesianosition",true);
    EXPECT_EQ(cartesianosition,rosMoveStub->get_current_end_effector_position());

    std::map<std::string,std::vector<double> > allPositions;
    allPositions.insert(std::pair<std::string, std::vector<double> >("cartesianosition",cartesianosition));
    allPositions.insert(std::pair<std::string, std::vector<double> >("jointPosition",jointPosition));
    EXPECT_EQ(allPositions,testRobot->get_all_recorded_position(false));

    testRobot->delete_recorded_poisiton("cartesianosition");
    std::map<std::string,std::vector<double> > onePosition;
    onePosition.insert(std::pair<std::string, std::vector<double> >("jointPosition",jointPosition));
    EXPECT_EQ(onePosition,testRobot->get_all_recorded_position(true));

    testRobot->delete_all_recorded_position();
    std::map<std::string,std::vector<double> > positionNull;
    EXPECT_EQ(positionNull,testRobot->get_recorded_cartesian_position());
    
    
}

int main(int argc, char **argv){
   testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}