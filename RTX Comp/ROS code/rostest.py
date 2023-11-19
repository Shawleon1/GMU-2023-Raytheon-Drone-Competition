#!/usr/bin/env python
# license removed for brevity
import rospy
from std_msgs.msg import Float32Array

def talker():
    pub = rospy.Publisher("/cmd_vel1", Float32Array, queue_size=10)
    rospy.init_node('talker', anonymous=True)
    rate = rospy.Rate(10) # 10hz
    while not rospy.is_shutdown():
        servo_values = [0, 1, 0, 0, 0, 0]
        rospy.loginfo(servo_values)
        pub.publish(servo_values)
        rate.sleep()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass