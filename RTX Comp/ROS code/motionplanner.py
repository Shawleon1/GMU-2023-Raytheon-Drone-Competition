#!/usr/bin/env python3

#to do: actually recieve gps input
#       add dampening to steering

import rospy
import math
from std_msgs.msg import Float32MultiArray
from sensor_msgs.msg import Joy

#current pose, to be fed by gps_callback in the future. x, y, degrees.
currPose = [0, 0, 0]
emergency_stop = 0

#stage and lane for the competition
stage = 0
lane = 0

def joy_callback(msg):
    global currPose, emergency_stop
    currPose = [0, 0, 0]
    emergency_stop = msg.buttons[9]

if __name__ == '__main__':
    try:
        servo_values = Float32MultiArray(data=[-1.0, 1.0, 0.0, 0.0, 0.0, 0.0])

        #accessing joystick (in the future will be motion planner) and publishing to arduino
        pub = rospy.Publisher("/cmd_vel1", Float32MultiArray, queue_size=10)
        sub = rospy.Subscriber("/joy", Joy, joy_callback)
        
        #we would have a case switch/ if statements for the series of targets to hit and the speeds to drive at
        targets = [[5, 0], [5, 3], [10, 3], [0, 0]]
        speed = 1
        currTarget = 0
        steering = 0

        rospy.init_node('motionplanner__test')
        rospy.loginfo("motionplanner_test is started")
        rate = rospy.Rate(10) # 10hz
        while not rospy.is_shutdown():
            #if we are close to the current target, move to the next target
            #if(abs(currPose[0] - targets[currTarget][0]) < 1 and abs(currPose[1] - targets[currTarget][1]) < 1):
            #    currTarget = currTarget + 1
                #end case
            #    if(targets[currTarget] == [0, 0]):
            #        break

            #calculate theta between robot and target
            deltaX = targets[currTarget][0] - currPose[0]
            deltaY = targets[currTarget][1] - currPose[1]
            angle = currPose[2] - math.atan(deltaX/deltaY)

            #pick steering
            if(angle < -5):
                steering = -1
            elif(angle > 5):
                steering = 1
            else:
                steering = 0

            servo_values.data[0] = steering
            servo_values.data[1] = speed
            servo_values.data[2] = emergency_stop
            rospy.loginfo(servo_values)
            pub.publish(servo_values)
            rate.sleep()
    except rospy.ROSInterruptException:
        pass