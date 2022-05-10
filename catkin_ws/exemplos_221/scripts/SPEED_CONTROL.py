#! /usr/bin/env python3
# -*- coding:utf-8 -*-

import rospy
from geometry_msgs.msg import Twist
from nav_msgs.msg import  Odometry
from tf.transformations import euler_from_quaternion
from geometry_msgs.msg import Point
from math import atan2

x=0
y=0
theta=0

msg=Odometry()


def position(msg):
    global x
    global y
    global theta

    x=msg.pose.pose.position.x
    y=msg.pose.pose.position.y
    ora_q=msg.pose.pose.orientation
    (roll,pitch,theta)=euler_from_quaternion([ora_q.x,ora_q.y,ora_q.z,ora_q.w])


rospy.init_node('Speed_Controller')
sub=rospy.Subscriber('/odom',Odometry,callback=position)
pub=rospy.Publisher('/cmd_vel',Twist,queue_size=10)
rospy.sleep(1)
r=rospy.Rate(4)

#to set a goal
goal=Point()

goal.x=4
goal.y=4
speed=Twist()

while not rospy.is_shutdown():
    x_diff=goal.x-x
    y_diff=goal.y-y
    t1=time.time()
    angle_to_go=atan2(y_diff,x_diff)
    if abs(angle_to_go-theta)>0.1: 
        speed.linear.x =0
        speed.angular.z=0.3
    else:
        speed.linear.x =0.3
        speed.angular.z=0.0

    pub.publish(speed)
    r.sleep()
    t2=time.time()
