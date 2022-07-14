#! /usr/bin/env python2
# -*- coding:utf-8 -*-

import rospy
from geometry_msgs.msg import Twist
from sensor_msgs.msg import LaserScan
from nav_msgs.msg import Odometry
from tf.transformations import euler_from_quaternion
from math import cos, sin, pi, sqrt
vel = Twist()
lasers = []
isRe = False
isIni = True
c1 = 1
c3 = 0.005
F = 0
R = 0
L = 0
isIni = True
x = 0
y = 0
x_ini = 0
y_ini = 0

def scaneou(dado):
    global lasers, F, R, L, vel
    lasers = []
    for angulo in range(360):
        lasers.append(dado.ranges[angulo])
    try:
        F = min([el for el in lasers[90:93] if el > 0])
    except:
        pass
    try:
        R = min([el for el in lasers[180:183] if el > 0])
    except:
        pass
    try:
        L = min([el for el in lasers[0:3] if el > 0])
    except:
        pass
    print F, R, L, vel.linear.x, vel.angular.z

def odom_list(data):
    global x, y, x_ini, y_ini, isIni
    x = data.pose.pose.position.x
    y = data.pose.pose.position.y
    if isIni:
        x_ini = x
        y_ini = y
        isIni = False

def checkBump():
    global R, L, isRe, x, y, x_ini, y_ini, vel
    if ((not isRe and F < 0.15) or (isRe and sqrt((x-x_ini)**2 + (y-y_ini)**2) < 0.15)) and abs(R - L) < 0.15:
        vel.linear.x = c3
        vel.angular.z = 0
        if isRe:
            vel.linear.x = -vel.linear.x
        velocidade_saida.publish(vel)
        rospy.sleep(2)
        isRe = not isRe

rospy.init_node("redox_planner_RHL")
velocidade_saida = rospy.Publisher("/cmd_vel", Twist, queue_size = 3 )
recebe_scan = rospy.Subscriber("/scan", LaserScan, scaneou)
recebe_odom = rospy.Subscriber("/camera/odom/sample",Odometry,odom_list)
while not rospy.is_shutdown():
    checkBump()
    if not isRe:
        erro = R - 0.15
    elif isRe:
        erro = 0.15 - L
    vel.linear.x = c3
    vel.angular.z = -c1 * erro
    velocidade_saida.publish(vel)
    rospy.sleep(0.01)