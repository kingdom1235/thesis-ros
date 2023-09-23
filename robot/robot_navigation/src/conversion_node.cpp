#include <tf/tf.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Pose2D.h>
#include <geometry_msgs/PoseStamped.h>
#include <move_base_msgs/MoveBaseAction.h>

ros::Publisher pub_pose_, pub_raw_pose_, pub_hector_pose_, pub_goal_, pub_localization_;

void odometryCallback_(const nav_msgs::Odometry::ConstPtr &msg);
void rawOdometryCallback_(const nav_msgs::Odometry::ConstPtr &msg);
void hectorOdometryCallback_(const geometry_msgs::PoseStamped::ConstPtr &msg);
void goalCallback_(const geometry_msgs::PoseStamped::ConstPtr &msg);
void localizationCallback_(const geometry_msgs::PoseStamped::ConstPtr &msg);

int main(int argc, char **argv)
{
    ros::init(argc, argv, "conversion_node");
    
    ros::NodeHandle nh_;
    ros::NodeHandle simple_nh("move_base_simple");
    
    ros::Subscriber sub_raw_odom_ = nh_.subscribe("raw_odom", 1, rawOdometryCallback_);
    ros::Subscriber sub_odom_ = nh_.subscribe("odom", 1, odometryCallback_);
    ros::Subscriber sub_hector_odom_ = nh_.subscribe("slam_out_pose", 1, hectorOdometryCallback_);
    ros::Subscriber sub_goal_ = simple_nh.subscribe("goal", 1, goalCallback_);
    ros::Subscriber sub_localization_ = nh_.subscribe("mcl_pose", 1, localizationCallback_);

    ROS_INFO("Conversion node!");

    pub_pose_ = nh_.advertise<geometry_msgs::Pose2D>("pose2d", 1);
    pub_raw_pose_ = nh_.advertise<geometry_msgs::Pose2D>("raw_pose2d", 1);
    pub_hector_pose_ = nh_.advertise<geometry_msgs::Pose2D>("hector_pose2d", 1);
    pub_goal_ = nh_.advertise<geometry_msgs::Pose2D>("goal_pose2d", 1);
    pub_localization_ = nh_.advertise<geometry_msgs::Pose2D>("localization_pose2d", 1);
    
    ros::spin();
    
    return 0;
}

void odometryCallback_(const nav_msgs::Odometry::ConstPtr &msg) {
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

void rawOdometryCallback_(const nav_msgs::Odometry::ConstPtr &msg) {
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
    pub_raw_pose_.publish(raw_pose2d);
}

void hectorOdometryCallback_(const geometry_msgs::PoseStamped::ConstPtr &msg) {
    geometry_msgs::Pose2D hector_pose2d;
    hector_pose2d.x = msg->pose.position.x;
    hector_pose2d.y = msg->pose.position.y;
    
    tf::Quaternion q(
        msg->pose.orientation.x,
        msg->pose.orientation.y,
        msg->pose.orientation.z,
        msg->pose.orientation.w);
    tf::Matrix3x3 m(q);
    double roll, pitch, yaw;
    m.getRPY(roll, pitch, yaw);
    
    hector_pose2d.theta = (yaw*180)/M_PI;
    pub_hector_pose_.publish(hector_pose2d);
}

void goalCallback_(const geometry_msgs::PoseStamped::ConstPtr &msg) {
    geometry_msgs::Pose2D goal_pose2d;
    goal_pose2d.x = msg->pose.position.x;
    goal_pose2d.y = msg->pose.position.y;
    
    tf::Quaternion q(
        msg->pose.orientation.x,
        msg->pose.orientation.y,
        msg->pose.orientation.z,
        msg->pose.orientation.w);
    tf::Matrix3x3 m(q);
    double roll, pitch, yaw;
    m.getRPY(roll, pitch, yaw);
    
    goal_pose2d.theta = (yaw * 180) / M_PI;
    pub_goal_.publish(goal_pose2d);
}

void localizationCallback_(const geometry_msgs::PoseStamped::ConstPtr &msg){
    geometry_msgs::Pose2D localization_pose2d;
    localization_pose2d.x = msg->pose.position.x;
    localization_pose2d.y = msg->pose.position.y;

    tf::Quaternion q(
        msg->pose.orientation.x,
        msg->pose.orientation.y,
        msg->pose.orientation.z,
        msg->pose.orientation.w);
    tf::Matrix3x3 m(q);
    double roll, pitch, yaw;
    m.getRPY(roll, pitch, yaw);

    localization_pose2d.theta = (yaw * 180) / M_PI;
    pub_localization_.publish(localization_pose2d);
}