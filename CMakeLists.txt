cmake_minimum_required(VERSION 3.3)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CATKIN_ENABLE_TESTING OFF)
project(gazebo_px4)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)d

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
#find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs roscpp message_generation cv_bridge ping360_sonar_msgs bluerov2commonmsgs dynamic_reconfigure waterlinked_dvl)
#find_package(PCL 1.10 REQUIRED COMPONENTS common io visualization)
#find_package (Eigen3 3.3 REQUIRED NO_MODULE)
find_package(eigen3_cmake_module REQUIRED)
find_package(Eigen3)
find_package(tf2 REQUIRED)

find_package(ament_cmake REQUIRED)
find_package(ament_cmake_python REQUIRED)

find_package(rclcpp REQUIRED)
find_package(rclpy REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(gz-transport13 REQUIRED)
find_package(gz-msgs10 REQUIRED)
#add_executable(controllerpx4bluerov2 src/px4_controller/mode.hpp src/px4_controller/main.cpp src/px4_controller/controllerOfBluerov2.cpp src/px4_controller/controllerOfBluerov2.h)
#ament_target_dependencies(controllerpx4bluerov2 px4_ros2_cpp rclcpp std_msgs sensor_msgs bluerov2commonmsgs tf2 Eigen3 px4_msgs visualization_msgs)

add_executable(my_custom_bridge src/dvl_bridge_gazebo.cpp)
ament_target_dependencies(my_custom_bridge rclcpp gz-transport13 gz-msgs10 geometry_msgs)


#target_link_libraries(my_custom_bridge
#
#        gz-transport13::gz-transport13
#)


install(TARGETS
        my_custom_bridge
        DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY launch DESTINATION share/${PROJECT_NAME}/)


ament_package()


