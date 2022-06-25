#! /usr/bin/env python3
# -*- coding:utf-8 -*-

import rospy
from nav_msgs.msg import OccupancyGrid

def escutou(info):
    pub.publish(info)

sub = rospy.Subscriber("/map",OccupancyGrid, escutou)
pub = rospy.Publisher('/costmap',OccupancyGrid)

while not rospy.is_shutdown():
    pass