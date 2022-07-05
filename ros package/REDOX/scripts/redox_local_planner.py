#! /usr/bin/env python2
# -*- coding:utf-8 -*-

import rospy
from std_msgs import Float64MultiArray
from geometry_msgs.msg import Twist
from nav_msgs.msg import  Odometry, Path
from tf.transformations import euler_from_quaternion
from geometry_msgs.msg import PoseStamped, Point
from math import atan2, sqrt, degrees
raio_robo = 0.3
x = 0
y = 0
x_min, x_max, y_min, y_max = 0.0, 0.0, 0.0, 0.0
theta = 0
alpha = 0
poses = []
goal = [0, 0]

def recebeu_odom(dado):
    global x, x_min, x_max
    global y, y_min, y_max 
    global theta
    x = dado.pose.pose.position.x
    y = dado.pose.pose.position.y
    if x < x_min:
        x_min = x
    elif x > x_max:
        x_max = x
    if y < y_min:
        y_min = y
    elif y > y_max:
        y_max = y
    ora_q = dado.pose.pose.orientation
    (roll,pitch,theta) = euler_from_quaternion([ora_q.x,ora_q.y,ora_q.z,ora_q.w])

def recebeu_path(dado):
    global poses
    poses = dado.poses

def recebeu_goal(dado):
    global goal
    goal = [dado.pose.position.x, dado.pose.position.y]


def euclidean_distance(point1, point2):
    a = abs(point1[0] - point2[0])**2
    b = abs(point1[1] - point2[1])**2
    return sqrt(a + b)

def getAlpha(alpha_curr):
    global x, y, theta, raio_robo, poses
    point1 = [x, y]
    point2 = [9999999, 9999999]
    dist_atual = 9999999
    for pose in poses:
        point_candidate = [pose.pose.position.x, pose.pose.position.y]
        dist_candidate = euclidean_distance(point1, point_candidate)
        if abs(dist_candidate - raio_robo) < abs(dist_atual - raio_robo) and dist_candidate > raio_robo:
            point2 = point_candidate
            dist_atual = euclidean_distance(point1, point2)
    beta = atan2(point2[1] - point1[1], point2[0] - point1[0])
    alpha = degrees(beta - theta)
    if alpha < 0:
        alpha += 360
    elif alpha > 360:
        alpha -= 360
    if abs(alpha - alpha_curr) < 180:
        alpha = (0.5 * alpha) + (0.5 * alpha_curr)
    return alpha
    
def getVel(alpha,k):
    vel = Twist()
    if alpha <= k or alpha >= (360 - k):
        vel.linear.x = 0.2
    elif (alpha < 90 and alpha > k) or (alpha > (180 + k) and alpha < 270):
        vel.angular.z = 0.4
    elif (alpha >= (180 - k) and alpha <= (180 + k)):
        vel.linear.x = -0.2
    else:
        vel.angular.z = -0.4
    return vel  


if __name__=="__main__":
    rospy.init_node("redox_local_planner")
    topic_odom = rospy.Subscriber("/camera/odom/sample", Odometry , recebeu_odom)
    topic_voronoi = rospy.Subscriber("/roda/VoronoiPlanner/plan", Path, recebeu_path)
    topic_goal = rospy.Subscriber("/move_base/current_goal", PoseStamped, recebeu_goal)
    topic_vel = rospy.Publisher('/cmd_vel',Twist)
    topic_pts = rospy.Publisher('/redox_local_planner/points',Float64MultiArray)
    rospy.sleep(10)
    while not rospy.is_shutdown():
        data = [x_min,x_max,y_min,y_max]
        topic_pts.publish(data)
        alpha = getAlpha(alpha)
        print(alpha, goal)
        vel = getVel(alpha, 15)
        topic_vel.publish(vel)
        rospy.sleep(0.1)