#!/usr/bin/env python

import rospy
from nav_msgs.msg import OccupancyGrid

def mapa(info):
    mapa = info[3]
    map_pub.publish(mapa)

if __name__== "__main__":
    #rospy.init_node("le_scan.py")
    #rospy.init_node("slam_gmapping")
    #rospy.init_node("explore_lite")
    #rospy.init_node("move_base")

    while not rospy.is_shutdown():
        map_listner = rospy.Subscriber("/map",OccupancyGrid,queue_size=3,callback=mapa)
        map_pub = rospy.Publisher("/costmap",OccupancyGrid,queue_size=3)
        

    
