#include<iostream>
#include "ros/ros.h"
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/PointCloud.h>
#include <sensor_msgs/point_cloud_conversion.h>
using namespace std;

ros::Publisher pub1,pub2,pub3;
void soa_callback(const sensor_msgs::PointCloud2::ConstPtr& input)
{
    sensor_msgs::PointCloud output;
    sensor_msgs::convertPointCloud2ToPointCloud(*input,output);
    pub1.publish(output);

}
void ransac_callback(const sensor_msgs::PointCloud2::ConstPtr& input)
{
    sensor_msgs::PointCloud output;
    sensor_msgs::convertPointCloud2ToPointCloud(*input,output);
    pub2.publish(output);
}
void original_callback(const sensor_msgs::PointCloud2::ConstPtr& input)
{
    sensor_msgs::PointCloud output;
    sensor_msgs::convertPointCloud2ToPointCloud(*input,output);
    pub3.publish(output);
}
int main(int argc, char **argv)
{
    ros::init(argc,argv,"pointcloud_conversion");
    ros::NodeHandle nh;

    ros::Subscriber sub1=nh.subscribe("/point_soa",1,soa_callback);
    ros::Subscriber sub2=nh.subscribe("/output",1,ransac_callback);
    ros::Subscriber sub3=nh.subscribe("/scan_3D",1,original_callback);
    pub1=nh.advertise<sensor_msgs::PointCloud> ("converted_soa", 1);
    pub2=nh.advertise<sensor_msgs::PointCloud> ("converted_ransac",1);
    pub3=nh.advertise<sensor_msgs::PointCloud> ("converted_original",1);
    ros::spin();


}