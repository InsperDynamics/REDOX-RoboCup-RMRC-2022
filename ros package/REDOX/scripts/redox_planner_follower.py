#! /usr/bin/env python2
# -*- coding:utf-8 -*-

import rospy
from geometry_msgs.msg import Twist
from nav_msgs.msg import  Odometry, OccupancyGrid
from tf.transformations import euler_from_quaternion
from math import cos, sin, pi
raio_roda = 0.08
largura_robo = 0.23
x = 0
y = 0
theta = 0
F, R, L, B = 0, 0, 0, 0
map = []
mapwidth = 0
mapheight = 0
isRe = False
c1 = 1
c3 = 0.6

def recebeu_odom(dado):
    global x, y, theta
    x = dado.pose.pose.position.x
    y = dado.pose.pose.position.y
    ora_q = dado.pose.pose.orientation
    (roll,pitch,theta) = euler_from_quaternion([ora_q.x,ora_q.y,ora_q.z,ora_q.w])

def recebeu_map(dado):
    global map, mapwidth, mapheight
    mapwidth = dado.info.width
    mapheight = dado.info.height
    for i in range(mapheight):
        for j in range(mapwidth):
            map.append(dado.data[i * mapwidth + j])

def getFBRL():
    global F, B, R, L
    global isRe
    global theta
    F, B, R, L = mapwidth, mapwidth, mapwidth, mapwidth
    if not isRe:
        alphas = [0, pi, 7*pi/4, pi/4]
    else:
        alphas = [0, pi, 5*pi/4, 3*pi/4]
    for d in range(1, mapwidth):
        if F < mapwidth and R < mapwidth and L < mapwidth and B < mapwidth:
            break
        for alpha_idx in range(len(alphas)):
            xp = x + (d * cos(alphas[alpha_idx] + theta))
            yp = y + (d * sin(alphas[alpha_idx] + theta))
            if map[int(yp * mapwidth + xp)] >= 50:
                if alpha_idx == 0 and F == mapwidth:
                    F = d
                elif alpha_idx == 1 and B == mapwidth:
                    B = d
                elif alpha_idx == 2 and R == mapwidth:
                    R = d
                elif alpha_idx == 3 and L == mapwidth:
                    L = d
    
def getVel():
    global isRe, raio_roda
    global c1, c3
    erro = c1 * (R - L)
    z = erro
    x = c3 - (raio_roda * z)
    if isRe:
        x = -x
        z = -z
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
        getFBRL()
        checkBump()
        x, z = getVel()
        vel = Twist()
        vel.linear.x = x
        vel.angular.z = z
        topic_vel.publish(vel)
        rospy.sleep(0.1)