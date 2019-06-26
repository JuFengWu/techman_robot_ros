##Techman Robot Ros Simulator for TM-5
 
This is [Techman Robot ](https://tm-robot.com/) TM-5 simulator for both Ros Melodic version and Kinetic version.
It also have a simpler robot points recorder which can help you to record joint base positions and cartesian positions.
I also use google test (Gtest) to make sure this code is stable.



> __NOTE__:  
This project is developing. Currently, only TM5_700 is available. In future, I hope it is not only a simulator but also can control real robot.

#### The packages or and environment
- Ros Melodic  or Ros Kinetic
- [google test](https://github.com/google/googletest)
- RVIZ
- moveit

#### How to use it
1. Download it into *your_ros_working_space*/src folder.
2. Go to *your_ros_working_space* and open terminal.
3. Type ```catkin_make``` and build project
4. Go to *your_ros_working_space*/devel and type ```source setup.bash```
5. Type ```roslaunch *your_ros_working_space*/src/tm700_moveit_config/launch/demo.launch```
you will see the TM-Robot on RVIZ
6. Open new terminal and follow step 2 to setp 4 and type```rosrun tm_move_api tm_move_api``` 
you will see the TM-Robot start to move
7. If you want to modify the robot path, you can just modify  *your_ros_working_space*/src/tm_move_api/src/move.cpp to change the path
8. In RobotPointControl.h there are two ways to record point, the first is joint recorder, the other is cartesian recorder. Record joint and move it, end effector won't move straightly, but when it near singular point, it won't move too fast.
Record cartesian and move it, end effector will move straightly, but when it near singular point, it will move very fast.
#### How to test it
1. Open terminal and type ```roscore```
2. Open another terminal and type ``` catkin_make tm_move_api test_move_api```
3. Type ```rosrun tm_move_api test_move_api ``` you can see the test results.
#####Enjoy it!
