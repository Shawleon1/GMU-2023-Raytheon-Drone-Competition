#!/usr/bin/env python3

import rospy
from std_msgs.msg import Float32MultiArray

if name == 'main':
    try:
        servo_values = Float32MultiArray(data=[-1.0, 1.0, 0.0, 0.0, 0.0, 0.0])
        pub = rospy.Publisher("/cmd_vel1", Float32MultiArray, queue_size=10)
        rospy.init_node('ros__test')
        rospy.loginfo("ros_test is started")
        rate = rospy.Rate(10) # 10hz
        while not rospy.is_shutdown():
            servo_values.data[0] = servo_values.data[0] + 0.01
            servo_values.data[1] = servo_values.data[1] - 0.01
            rospy.loginfo(servo_values)
            pub.publish(servo_values)
            rate.sleep()
    except rospy.ROSInterruptException:
        pass