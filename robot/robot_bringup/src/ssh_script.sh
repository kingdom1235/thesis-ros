#!/usr/bin/expect

# Set the SSH command and arguments
set ssh_command "ssh"
set ssh_arguments "ubuntu@192.168.172.76"

# Set the ROS launch command
set ros_launch_command "roslaunch robot_bringup robot.launch"

# Function to run SSH and ROS launch
proc run_ssh_and_launch {} {
    global ssh_command
    global ssh_arguments
    global ros_launch_command

    # Open a new terminal window and execute the SSH command
    spawn gnome-terminal -- bash -c "$ssh_command $ssh_arguments ; echo 'Press Enter to exit...'; read"

    # Wait for the terminal to open and SSH to complete
    expect {
        "Press Enter to exit..." {
            # Send the ROS launch command and keep the terminal open
            send "$ros_launch_command\r"
            interact
        }
    }
}

# Run SSH and ROS launch
run_ssh_and_launch
