#!/usr/bin/env python
# license removed for brevity
import rospy
from std_msgs.msg import Float32MultiArray

def rostest():
    pub = rospy.Publisher("/cmd_vel1", Float32MultiArray, queue_size=10)
    rospy.init_node('rostest', anonymous=True)
    rate = rospy.Rate(10) # 10hz
    while not rospy.is_shutdown():
        servo_values = [.75, 1, 0, 0, 0, 0]
        rospy.loginfo(servo_values)
        pub.publish(6, servo_values)
        rate.sleep()

if __name__ == '__main__':
    try:
        rostest()
    except rospy.ROSInterruptException:
        pass