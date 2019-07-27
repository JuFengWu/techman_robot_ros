FROM dorowu/ubuntu-desktop-lxde-vnc:bionic
LABEL maintainer "leowu102000@gmail.com"

RUN add-apt-repository main
RUN add-apt-repository universe
RUN add-apt-repository restricted
RUN add-apt-repository multiverse

#install git
RUN apt-get update
RUN echo "y" | apt-get install git 

#install vim
RUN echo "y" | apt-get install vim

#install ros melodic
ENV ENV APT_KEY_DONT_WARN_ON_DANGEROUS_USAGE=1
RUN apt-get update
RUN echo "y" | apt-get install gpg-agent
RUN apt-get install dirmngr

RUN sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
RUN apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654
RUN apt-get update
RUN echo "y" | apt-get install ros-melodic-desktop
RUN rosdep init && rosdep update
RUN /bin/bash -c "echo 'source /opt/ros/melodic/setup.bash' >> /root/.bashrc"

#install moveit
RUN echo "y" |apt-get install ros-melodic-moveit

#install gazebo
RUN apt-get install wget
RUN sh -c 'echo "deb http://packages.osrfoundation.org/gazebo/ubuntu-stable `lsb_release -cs` main" > /etc/apt/sources.list.d/gazebo-stable.list'
RUN wget http://packages.osrfoundation.org/gazebo.key -O - | sudo apt-key add -
RUN apt-get update
RUN echo "y" |apt-get install gazebo9
RUN echo "y" |apt-get install libgazebo9-dev
RUN echo "y" | apt-get install ros-melodic-gazebo-ros-pkgs ros-melodic-gazebo-ros-control

#install ros-industrial
RUN echo "y" |apt-get install ros-melodic-industrial-core



