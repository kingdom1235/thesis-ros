#!/bin/bash
rostopic pub /reset std_msgs/Empty
rostopic pub /syscommand std_msgs/String "reset"
