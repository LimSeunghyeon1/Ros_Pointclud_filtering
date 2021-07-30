#include<ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include<pcl/point_types.h>

#include<pcl/sample_consensus/model_types.h>
#include<pcl/sample_consensus/method_types.h>
#include <pcl/segmentation/sac_segmentation.h>

ros::Publisher pub;

void
cloud_cb (const sensor_msgs::PointCloud2ConstPtr& input)
{
    // Convert the sensor_msgs/PointCloud2 data to pcl/PointCloud
    pcl::PCLPointCloud2 temp;
    pcl::PointCloud<pcl::PointXYZ> cloud;
    pcl_conversions::toPCL (*input, temp);
    pcl::fromPCLPointCloud2(temp,cloud);
    pcl::PointCloud<pcl::PointXYZ> inlierPoints;
    pcl::PointCloud<pcl::PointXYZ> inlierPoints_neg;
    pcl::ModelCoefficients coefficients;
    pcl::PointIndices inliers;
    // Create the segmentation object
    pcl::SACSegmentation<pcl::PointXYZ> seg;
    // Optional
    seg.setOptimizeCoefficients (true);
    // Mandatory
    seg.setModelType (pcl::SACMODEL_PLANE);
    seg.setMethodType (pcl::SAC_RANSAC);
    seg.setDistanceThreshold (0.01);

    seg.setInputCloud (cloud.makeShared ());
    seg.segment (inliers, coefficients);

    // Publish the model coefficients
    //pcl_msgs::ModelCoefficients ros_coefficients;
    pcl::PCLPointCloud2 inlierPoints_2;
    pcl::copyPointCloud<pcl::PointXYZ>(cloud,inliers,inlierPoints); 
    pcl::toPCLPointCloud2(inlierPoints, inlierPoints_2);
    sensor_msgs::PointCloud2 output;
    pcl_conversions::fromPCL(inlierPoints_2,output);
    //pcl_conversions::fromPCL(coefficients, ros_coefficients);

    pub.publish (output);
}

int
main (int argc, char** argv)
{
    ROS_INFO("initializing,..");
    // Initialize ROS
    ros::init (argc, argv, "ransac");
    ros::NodeHandle nh;

    // Create a ROS subscriber for the input point cloud
    ros::Subscriber sub = nh.subscribe ("point_soa", 1, cloud_cb);

    // Create a ROS publisher for the output point cloud
    pub = nh.advertise<sensor_msgs::PointCloud2> ("output", 1);
    //pub = nh.advertise<pcl_msgs::ModelCoefficients> ("ransac_output", 1);

    // Spin
    ros::spin ();
    ROS_INFO("dd");
}