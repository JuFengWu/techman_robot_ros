## Techman Robot Ros Simulator for TM-5
 
This is the [Techman Robot ](https://tm-robot.com/) TM-5 simulator for both the Ros Melodic version and the Kinetic version.
It also has a simpler robot points recorder which can help you to record joint base positions and cartesian positions.
I also use the Google test (Gtest) to make sure this code is stable.

> __NOTE__:  
This project is developing. Currently, only TM5_700 is available. In the future, I hope it is not only a simulator but also can control real robot.

#### Use docker-compose to build and run it (Linux, Recommend)
1. Download source this code and open terminal to go to "docker" folder
2. Type ```docker-compose build``` and it will start to build the environment.
3. Type ```docker-compose up -d ros_melodic_vnc_techman``` and open browser and navigate to ```localhost:6080```
4. This source code will be at ```/root/ws_techman_robot```


#### The packages or and environment
- Ros Melodic  or Ros Kinetic
- [Google test](https://github.com/google/googletest)
- RVIZ
- Moveit

#### How to use it
1. Download it into *your_ros_working_space*/src folder.
2. Go to *your_ros_working_space* and open terminal.
3. Type ```catkin_make``` and build project
4. Go to *your_ros_working_space*/devel and type ```source setup.bash```
5. Type ```roslaunch *your_ros_working_space*/src/tm700_moveit_config/launch/demo.launch```
you will see the TM-Robot on RVIZ
6. Open a new terminal and follow step 2 to step 4 and type ```rosrun tm_move_api tm_move_api``` 
you will see the TM-Robot start to move
7. If you want to modify the robot path, you can just modify  *your_ros_working_space*/src/tm_move_api/src/move.cpp to change the path
8. In RobotPointControl.h there are two ways to record points, the first is the joint recorder, the other is the cartesian recorder. Record joint and move it, end effector won't move straightly, but when it near singular point, it won't move too fast.
Record cartesian and move it, end effector will move straightly, but when it near singular point, it will move very fast.
#### How to test it
1. Open terminal and type ```roscore```
2. Open another terminal and type ``` catkin_make tm_move_api test_move_api```
3. Type ```rosrun tm_move_api test_move_api ``` you can see the test results.

#### How to use tm move python api
1. Open a terminal and Type ```roslaunch *your_ros_working_space*/src/tm700_moveit_config/launch/demo.launch``` to open rviz
2. Open another terminal and type ```rosrun tm_move_api tm_move_serverice```
3. Open the other terminal, and type ```python2  *your_ros_working_space*/src/tm_move_python/scrips/tm_move.py```, you will see the TM-Robot start to move
4. If you want to modify robot path, you can just modify *your_ros_working_space*/src/tm_move_python/scrips/tm_move.py to change the path
5. In *tm_move_api_python* , there are also two ways to record points, the first is the joint recorder, the other is the cartesian recorder. Record joint and move it, end effector won't move straightly, but when it near singular point, it won't move too fast. Record cartesian and move it, end effector will move straightly, but when it near singular point, it will move very fast.

#### How to test tm move python api
1. Open a terminal and type ```roscore```, and wait for ros run 
2. Open another terminal and type ```rosrun tm_move_api tm_move_service```
3. Open the other terminal, and type ```python2  *your_ros_working_space*/src/tm_move_python/test_client_scrip.py```, the test will start, it will show all test process and result.

##### Enjoy it!
