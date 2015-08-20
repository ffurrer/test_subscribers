cmake_minimum_required(VERSION 2.8.3)
project(test_subscribers)

find_package(catkin REQUIRED COMPONENTS roscpp std_msgs)

find_package(gazebo REQUIRED)
link_directories(${GAZEBO_LIBRARY_DIRS})
include_directories(include ${GAZEBO_INCLUDE_DIRS} ${catkin_INCLUDE_DIRS})

catkin_package(
 INCLUDE_DIRS include
 LIBRARIES
 CATKIN_DEPENDS std_msgs
 DEPENDS gazebo
)

add_executable(test_msg_publisher src/test_msg_publisher.cpp)
target_link_libraries(test_msg_publisher ${catkin_LIBRARIES})
add_dependencies(test_msg_publisher ${catkin_EXPORTED_TARGETS})

add_library(test_gazebo_plugin src/test_gazebo_plugin.cpp)
target_link_libraries(test_gazebo_plugin ${catkin_LIBRARIES} ${GAZEBO_LIBRARIES})
add_dependencies(test_gazebo_plugin ${catkin_EXPORTED_TARGETS})
