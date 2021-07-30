#include "ros/ros.h"
#include <sensor_msgs/PointCloud.h>
#include<iostream>
#include<fstream>
#include<std_msgs/String.h>
#include<geometry_msgs/Point32.h>
#include<vector>
#include<sstream>
using namespace std;
vector<geometry_msgs::Point32> lidar_point_voxel;
vector<geometry_msgs::Point32> lidar_point_ransac;
vector<geometry_msgs::Point32> lidar_point;
static int cnt=0;
void callback(const std_msgs::String::ConstPtr& msg)
{
    ROS_INFO("subscribe callback initialized...");
    istringstream iss(msg->data);
    string token;
    vector<string> param;
    while(getline(iss,token,' '))
    {
        param.emplace_back(token);
    }
    ROS_INFO("param is... %s",param[0].c_str());
    if(param[0]=="p") //for soa
    {
        string dir("/home/sam/logging_file/soa_lidar_test");
        dir+=to_string(cnt);
        dir+=".txt";
        ofstream fout;
       
        ROS_INFO("dir is %s",dir.c_str());
        if(access(dir.c_str(),F_OK)<0)
        {
            fout.open(dir);
            ROS_INFO("lidar_point size is %d",lidar_point_voxel.size());
            for(int i=0;i<lidar_point_voxel.size();i++)
            {
                fout<<lidar_point_voxel[i].x<<" "<<lidar_point_voxel[i].y<<" "<<lidar_point_voxel[i].z<<endl;

            }
            ROS_INFO("logged successfully!");
        }
        else
        {
            ROS_ERROR("Try again.. File name already exists");
            cnt++;
            return;
        }
        fout.close();
        cnt++;


    }
    if(param[0]=="r") //for ransac
    {
        string dir("/home/sam/logging_file/ransac_lidar_test");
        dir+=to_string(cnt);
        dir+=".txt";
        ofstream fout;

        ROS_INFO("dir is %s",dir.c_str());
        if(access(dir.c_str(),F_OK)<0)
        {
            fout.open(dir);
            ROS_INFO("lidar_point size is %d",lidar_point_ransac.size());
            for(int i=0;i<lidar_point_ransac.size();i++)
            {
                fout<<lidar_point_ransac[i].x<<" "<<lidar_point_ransac[i].y<<" "<<lidar_point_ransac[i].z<<endl;
                
            }
            ROS_INFO("logged successfully!");
        }
        else
        {
            ROS_ERROR("Try again.. File name already exists");
            cnt++;
            return;
        }
        fout.close();
        cnt++;
    }
    if(param[0]=="o")// for original data (unfiltered ones)
    {
        string dir("/home/sam/logging_file/original_lidar_test");
        dir+=to_string(cnt);
        dir+=".txt";
        ofstream fout;
        ROS_INFO("dir is %s",dir.c_str());
        if(access(dir.c_str(),F_OK)<0)
        {
            fout.open(dir);
            ROS_INFO("lidar_point size is %d",lidar_point.size());
            for(int i=0;i<lidar_point.size();i++)
            {
                fout<<lidar_point[i].x<<" "<<lidar_point[i].y<<" "<<lidar_point[i].z<<endl;
                
            }
            ROS_INFO("logged successfully!");
        }
        else
        {
            ROS_ERROR("Try again.. File name already exists");
            cnt++;
            return;
        }
        fout.close();
        cnt++;
    }
}
void voxel_cb(const sensor_msgs::PointCloud::ConstPtr& scan)
{
    lidar_point_voxel.clear();
    for(int i=0;i<scan->points.size();i++)
    {
        lidar_point_voxel.push_back(scan->points[i]);
    }

}
void ransac_cb(const sensor_msgs::PointCloud::ConstPtr& scan )
{
    lidar_point_ransac.clear();
    for(int i=0;i<scan->points.size();i++)
    {
        lidar_point_ransac.push_back(scan->points[i]);
    }

}
void original_cb(const sensor_msgs::PointCloud::ConstPtr& scan )
{
    lidar_point.clear();
    for(int i=0;i<scan->points.size();i++)
    {
        lidar_point.push_back(scan->points[i]);
    }

}
int main(int argc,char** argv)
{
    ros::init(argc,argv,"lidar_logging");
    ros::NodeHandle nh;
    ros::Subscriber sub=nh.subscribe("keyboard_input",1,callback);
    ros::Subscriber voxel_sub=nh.subscribe("converted_soa",1,voxel_cb);
    ros::Subscriber ransac_sub=nh.subscribe("converted_ransac",1,ransac_cb);
    ros::Subscriber original_sub=nh.subscribe("converted_original",1,original_cb);
    ros::spin();


}