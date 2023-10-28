#include "ros/ros.h"
#include "sensor_msgs/JointState.h"
#include "std_msgs/Float64.h"

void jointStateCallback(const sensor_msgs::JointState::ConstPtr& msg) {
    // Your controller logic goes here
    // Publish control commands as needed
    //ROS_INFO("Joint states: [%s]", msg->data.c_str());

    // Print the current joint positions
    ROS_INFO("\n--Joint States--\n");
    for (size_t i = 0; i < msg->name.size(); i++) {
        ROS_INFO("Joint %s: Position %.4f", msg->name[i].c_str(), msg->position[i]);
    }
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "arm_controller_node");
    ros::NodeHandle nh;

    ros::Subscriber jointStateSub = nh.subscribe("/arm/joint_states", 10, jointStateCallback);
    // Add publishers for control commands if needed

    ros::spin();

    return 0;
}
/*
#include <ros/ros.h>
#include <std_msgs/String.h>
void chatterCallback(const std_msgs::String& msg)
{
    ROS_INFO("I heard: [%s]", msg.data.c_str());
}
int main(int argc, char* argv[])
{
    ros::init(argc, argv, "listener");
    ros::NodeHandle nodeHandle;
    ros::Subscriber subscriber = nodeHandle.subscribe("
    chatter",10,chatterCallback);
    ros::spin();
    return 0;
}
*/