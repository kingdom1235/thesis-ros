#include <tf/tf.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Pose2D.h>

ros::Publisher pub_pose_, pub_raw_pose_, pub_hector_pose_;

void odometryCallback_(const nav_msgs::Odometry::ConstPtr msg) {
    geometry_msgs::Pose2D pose2d;
    pose2d.x = msg->pose.pose.position.x;
    pose2d.y = msg->pose.pose.position.y;
    
    tf::Quaternion q(
        msg->pose.pose.orientation.x,
        msg->pose.pose.orientation.y,
        msg->pose.pose.orientation.z,
        msg->pose.pose.orientation.w);
    tf::Matrix3x3 m(q);
    double roll, pitch, yaw;
    m.getRPY(roll, pitch, yaw);
    
    pose2d.theta = (yaw*180)/M_PI;
    pub_pose_.publish(pose2d);
}

void rawOdometryCallback_(const nav_msgs::Odometry::ConstPtr msg) {
    geometry_msgs::Pose2D raw_pose2d;
    raw_pose2d.x = msg->pose.pose.position.x;
    raw_pose2d.y = msg->pose.pose.position.y;
    
    tf::Quaternion q(
        msg->pose.pose.orientation.x,
        msg->pose.pose.orientation.y,
        msg->pose.pose.orientation.z,
        msg->pose.pose.orientation.w);
    tf::Matrix3x3 m(q);
    double roll, pitch, yaw;
    m.getRPY(roll, pitch, yaw);
    
    raw_pose2d.theta = (yaw*180)/M_PI;
    pub_pose_.publish(raw_pose2d);
}

void hectorOdometryCallback_(const geometry_msgs::PoseStamped::ConstPtr msg) {
    geometry_msgs::Pose2D hector_pose2d;
    hector_pose2d.x = msg->pose.pose.position.x;
    hector_pose2d.y = msg->pose.pose.position.y;
    
    tf::Quaternion q(
        msg->pose.pose.orientation.x,
        msg->pose.pose.orientation.y,
        msg->pose.pose.orientation.z,
        msg->pose.pose.orientation.w);
    tf::Matrix3x3 m(q);
    double roll, pitch, yaw;
    m.getRPY(roll, pitch, yaw);
    
    hector_pose2d.theta = (yaw*180)/M_PI;
    pub_pose_.publish(hector_pose2d);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "conversion_node");
    
    ros::NodeHandle nh_;
    
    ros::Subscriber sub_odom_ = nh_.subscribe("raw_odom", 1, rawOdometryCallback_);
    ros::Subscriber sub_odom_ = nh_.subscribe("odom", 1, odometryCallback_);
    ros::Subscriber sub_odom_ = nh_.subscribe("slam_out_pose", 1, hectorOdometryCallback_);


    pub_pose_ = nh_.advertise<geometry_msgs::Pose2D>("pose2d", 1);
    pub_pose_ = nh_.advertise<geometry_msgs::Pose2D>("raw_pose2d", 1);
    pub_pose_ = nh_.advertise<geometry_msgs::Pose2D>("hector_pose2d", 1);
    
    ros::spin();
    
    return 0;
}