#!/usr/bin/env python

import cv2
import rospy
import matplotlib.pyplot as plt 
import numpy as np
from nav_msgs.msg import OccupancyGrid

### Dependencias para simulação com turtlebot
"""
 /scan já é publicado ao iniciar a simulação, não precisa ser iniciado

 rosrun gmapping slam_gmapping scan:=scan
 roslaunch explore_lite explore.launch
"""

def mapa(info):
    global map
    map = info.data
    map_pub.publish(map)

if __name__== "__main__":
    map = np.zeros((3,3))
    map_listner = rospy.Subscriber("/map",OccupancyGrid,queue_size=3,callback=mapa)
    map_pub = rospy.Publisher("/costmap",OccupancyGrid,queue_size=3)

    while not rospy.is_shutdown():
        plt.imshow(map,cmap="gray")
        plt.show()
        

    
