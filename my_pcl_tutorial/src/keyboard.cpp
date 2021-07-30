#include<iostream>
#include<fstream>
#include"ros/ros.h"
#include<sensor_msgs/PointCloud.h>
#include<std_msgs/String.h>
using namespace std;

int main(int argc, char **argv)
{
    ros::init(argc,argv,"keyboard");
    ros::NodeHandle nh;
    ROS_INFO("keyboard node init...");
    ros::Publisher keyboard_pub=nh.advertise<std_msgs::String>("keyboard_input",1);
    while(ros::ok())
    {
        ROS_INFO("Insert keys");
        std_msgs::String msg;
        getline(cin,msg.data);
        if(msg.data[0]=='\x03')
            ros::spinOnce();
        keyboard_pub.publish(msg);
        ROS_INFO("key well published");

    }
    return 0;
}