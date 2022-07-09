#! /usr/bin/env python2
# -*- coding:utf-8 -*-

from cmath import inf
import rospy
from std_msgs.msg import Float64MultiArray
from geometry_msgs.msg import Twist
from nav_msgs.msg import  Odometry, OccupancyGrid
from tf.transformations import euler_from_quaternion
from geometry_msgs.msg import PoseStamped, Point
from sensor_msgs.msg import LaserScan
from math import atan2, sqrt, degrees
raio_roda = 0.08
largura_robo = 0.23
x = 0
y = 0
F, R, L, B = inf, inf, inf, inf
map = []
isRe = False
c1 = 1
c2 = 3
c3 = 0.6

def recebeu_odom(dado):
    global x, y
    x = dado.pose.pose.position.x
    y = dado.pose.pose.position.y

def recebeu_map(dado):
    global map
    mapwidth = dado.info.width
    mapheight = dado.info.height
    for i in range(mapheight):
        for j in range(mapwidth):
            map.append(dado.data[i * mapwidth + j])

def getFRLB():
    pass
    
def getVel():
    global isRe, raio_roda
    global c1, c3
    erro = c1 * (R - L)
    z = erro
    x = c3 - (raio_roda * z)
    if isRe:
        erro = c1 * (L - R)
        x = - c3 - (raio_roda * z)
    return x, z

def checkBump():
    global largura_robo
    global F, R, L, B
    global isRe
    if ((not isRe and F < largura_robo) or (isRe and B < largura_robo)) and abs(R - L) < largura_robo:
        vel = Twist()
        vel.linear.x = c3
        vel.angular.z = 0
        if isRe:
            vel.linear.x = -vel.linear.x
        topic_vel.publish(vel)
        rospy.sleep(2)
        isRe = not isRe


if __name__=="__main__":
    rospy.init_node("redox_planner_follower")
    topic_odom = rospy.Subscriber("/camera/odom/sample", Odometry , recebeu_odom)
    topic_vel = rospy.Publisher('/cmd_vel',Twist)
    topic_map = rospy.Subscriber("/map", OccupancyGrid, recebeu_map)
    rospy.sleep(10)
    while not rospy.is_shutdown():
        checkBump()
        x, z = getVel()
        vel = Twist()
        vel.linear.x = x
        vel.angular.z = z
        topic_vel.publish(vel)
        rospy.sleep(0.1)