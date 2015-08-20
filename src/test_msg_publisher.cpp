#include "ros/ros.h"
#include "std_msgs/String.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "test_");

  ros::NodeHandle nh;

  ros::Publisher test_pub = nh.advertise<std_msgs::String>("test_msg", 1);

  ros::Rate loop_rate(100);

  while (ros::ok()) {
    std_msgs::String msg;

    std::string test_string = "|";
    msg.data = test_string;

    test_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
  }

  return 0;
}
