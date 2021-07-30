#include"ros/ros.h"
#include<iostream>
#include<pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include<pcl/filters/statistical_outlier_removal.h>
#include "pcl_conversions/pcl_conversions.h"
#include "pcl/point_cloud.h"
#include "pcl/point_types.h"
#include<sensor_msgs/PointCloud2.h>
#include<pcl/conversions.h>

ros::Publisher pub;
void cloud_cb(const sensor_msgs::PointCloud2::ConstPtr& cloud_msg)
{
    pcl::PCLPointCloud2 * cloud=new pcl::PCLPointCloud2;
    pcl::PCLPointCloud2ConstPtr cloudPtr(cloud);
    pcl_conversions::toPCL(*cloud_msg, *cloud);
    pcl::PointCloud<pcl::PointXYZ> cloud_filtered;
    pcl::PointCloud<pcl::PointXYZ>::Ptr point_cloud(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::fromPCLPointCloud2(*cloud,*point_cloud);

    std::cout << "Input : " << cloud->data.size () << std::endl;
    pcl::StatisticalOutlierRemoval<pcl::PointXYZ> sor;
    sor.setInputCloud (point_cloud);            //입력 
    sor.setMeanK (50);                    //분석시 고려한 이웃 점 수(50개)
    sor.setStddevMulThresh (1.0);         //Outlier로 처리할 거리 정보 
    sor.filter (cloud_filtered);         // 필터 적용 
    pcl::PCLPointCloud2 cloud_filtered_2;
    pcl::toPCLPointCloud2(cloud_filtered,cloud_filtered_2);
    sensor_msgs::PointCloud2 output;
    pcl_conversions::fromPCL(cloud_filtered_2,output);
    std::cout << "Output : " << cloud_filtered_2.data.size () << std::endl;

    pub.publish(output);

}


int main(int argc,char** argv)
{
    ros::init(argc,argv,"outlier_removal");
    ros::NodeHandle nh;

    ros::Subscriber sub=nh.subscribe("/voxel_output",1,cloud_cb);
    pub=nh.advertise<sensor_msgs::PointCloud2>("/point_soa",1);
    ros::spin();
}