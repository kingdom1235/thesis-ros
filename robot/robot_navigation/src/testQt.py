#!/usr/bin/env python

import rospy
from geometry_msgs.msg import Pose2D, Twist
from nav_msgs.msg import Odometry

def publish_poses():
    rospy.init_node('pose_publisher', anonymous=True)
    
    # Publishers for the four topics
    raw_pose2d_pub = rospy.Publisher('raw_pose2d', Pose2D, queue_size=10)
    pose2d_pub = rospy.Publisher('pose2d', Pose2D, queue_size=10)
    hector_pose2d_pub = rospy.Publisher('hector_pose2d', Pose2D, queue_size=10)
    raw_odom_pub = rospy.Publisher('raw_odom', Odometry, queue_size=10)
    
    rate = rospy.Rate(1)  # 1 Hz

    while not rospy.is_shutdown():
        # Create a Pose2D message
        pose_msg = Pose2D()
        pose_msg.x = 1.567999  # Replace with your desired x coordinate
        pose_msg.y = 2.64646989  # Replace with your desired y coordinate
        pose_msg.theta = 65.54666464  # Replace with your desired theta angle

        # Create a Twist message for the velocity
        twist_msg = Twist()
        twist_msg.linear.x = 0.1136646  # Replace with your desired linear velocity
        twist_msg.angular.z = 0.2465699  # Replace with your desired angular velocity

        # Publish to the four topics
        raw_pose2d_pub.publish(pose_msg)
        pose2d_pub.publish(pose_msg)
        hector_pose2d_pub.publish(pose_msg)
        
        rospy.loginfo('Published Pose2D messages')

        rate.sleep()

if __name__ == '__main__':
    try:
        publish_poses()
    except rospy.ROSInterruptException:
        pass
