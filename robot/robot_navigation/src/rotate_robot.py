#!/usr/bin/env python

import rospy
from geometry_msgs.msg import Twist

def rotate_robot(duration):
    # Initialize the ROS node
    rospy.init_node('rotate_robot', anonymous=True)
    
    # Create a publisher for the twist messages
    cmd_vel_pub = rospy.Publisher('/cmd_vel', Twist, queue_size=10)
    
    # Create a Twist message to command the robot
    twist = Twist()
    
    # Set the angular velocity to rotate the robot
    twist.angular.z = 1.0  # Adjust the value as per your requirement
    
    # Set the linear velocity to zero to prevent unintended motion
    twist.linear.x = 0.0
    twist.linear.y = 0.0
    twist.linear.z = 0.0
    
    # Publish the twist message repeatedly to rotate the robot
    rate = rospy.Rate(10)  # Publish at 10 Hz
    duration = rospy.Duration(duration)  # Rotate for the specified duration
    
    start_time = rospy.Time.now()
    while (rospy.Time.now() - start_time) < duration:
        cmd_vel_pub.publish(twist)
        rate.sleep()
    
    # Stop the robot after rotating
    twist.linear.x = 0.0
    twist.angular.z = 0.0
    cmd_vel_pub.publish(twist)

if __name__ == '__main__':
    try:
        # Read the rotation duration from a parameter
        rotation_duration = rospy.get_param('~rotation_duration', 10)  # Default: 10 seconds
        
        rotate_robot(rotation_duration)
    except rospy.ROSInterruptException:
        pass
