#include "ros/ros.h"
#include "sensor_msgs/JointState.h"
#include "std_msgs/Float64.h"

ros::Publisher joint0CommandPub;
ros::Publisher joint1CommandPub;
ros::Publisher joint2CommandPub;
ros::Publisher joint3CommandPub;

void jointStateCallback(const sensor_msgs::JointState::ConstPtr& msg) {
    // Your controller logic goes here
    // Publish control commands as needed
    //ROS_INFO("Joint states: [%s]", msg->data.c_str());

    // Print the current joint positions
    ROS_INFO("\n--Joint States--");
    for (size_t i = 0; i < msg->name.size(); i++) {
        ROS_INFO("Joint %s: Position %.4f", msg->name[i].c_str(), msg->position[i]);
    }
    float increments[4] = {0.2, 0.00, 0.00, 0.00};
    std_msgs::Float64 commandMsg[4];
    for (size_t i = 0; i < msg->name.size(); i++) {
        commandMsg[i].data = msg->position[i]+increments[i]; // Set the command value as needed
    }
    joint0CommandPub.publish(commandMsg[0]); // Publish the command
    joint1CommandPub.publish(commandMsg[1]); // Publish the command
    joint2CommandPub.publish(commandMsg[2]); // Publish the command
    joint3CommandPub.publish(commandMsg[3]); // Publish the command
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "arm_controller_node");
    ros::NodeHandle nh;

    ros::Subscriber jointStateSub = nh.subscribe("/arm/joint_states", 10, jointStateCallback);
    // Add publishers for control commands if needed
    // Define a publisher for the command topic of a joint controller
    joint0CommandPub = nh.advertise<std_msgs::Float64>("arm/PositionJointInterface_J0_controller/command", 10);
    joint1CommandPub = nh.advertise<std_msgs::Float64>("arm/PositionJointInterface_J1_controller/command", 10);
    joint2CommandPub = nh.advertise<std_msgs::Float64>("arm/PositionJointInterface_J2_controller/command", 10);
    joint3CommandPub = nh.advertise<std_msgs::Float64>("arm/PositionJointInterface_J3_controller/command", 10);


    ros::spin();

    return 0;
}