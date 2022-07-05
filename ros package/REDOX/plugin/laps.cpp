#include <rotate_recovery/rotate_recovery.h>
#include <pluginlib/class_list_macros.h>
#include <nav_core/parameter_magic.h>
#include <tf2/utils.h>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Point.h>
#include <angles/angles.h>
#include <algorithm>
#include <string>


// register this planner as a RecoveryBehavior plugin
PLUGINLIB_EXPORT_CLASS(laps_redox::LapsRedox, nav_core::RecoveryBehavior)

namespace laps_redox
{
LapsRedox::Laps(): local_costmap_(NULL), initialized_(false), world_model_(NULL), searchDistance_(true), xmin_(NULL), xmax_(NULL), ymin_(NULL), ymax_(NULL), x_(NULL), y_(NULL)
{
}

void LapsRedox::initialize(std::string name, tf2_ros::Buffer*,
                                costmap_2d::Costmap2DROS*, costmap_2d::Costmap2DROS* local_costmap)
{
  if (!initialized_)
  {
    local_costmap_ = local_costmap;

    world_model_ = new base_local_planner::CostmapModel(*local_costmap_->getCostmap());

    initialized_ = true;
  }
  else
  {
    ROS_ERROR("You should not call initialize twice on this object, doing nothing");
  }
}

LapsRedox::~RotateRecovery()
{
  delete world_model_;
}

void ptCallback(const geometry_msgs::Float64MultiArray& data)
{
  xmin_ = data.data[0];
  xmax_ = data.data[1];
  ymin_ = data.data[2];
  ymax_ = data.data[3];
}

void odomCallback(const nav_msgs::Odometry& data)
{
  x_ = data.pose.pose.position.x;
  y_ = data.pose.pose.position.y;
}

void LapsRedox::runBehavior()
{
  if (!initialized_)
  {
    ROS_ERROR("This object must be initialized before runBehavior is called");
    return;
  }

  if (local_costmap_ == NULL)
  {
    ROS_ERROR("The costmap passed to the RotateRecovery object cannot be NULL. Doing nothing.");
    return;
  }
  ROS_WARN("Rotate recovery behavior started.");

  ros::Rate r(frequency_);
  ros::NodeHandle n;
  ros::Publisher pos_pub = n.advertise<geometry_msgs::PoseStamped>("roda/move_base_simple/goal", 1000);
  ros::Subscriber points = n.subscribe("redox_local_planner/points", 1000, &ptCallback);
  ros::Subscriber odom_sub = n.subscribe("/camera/odom/sample", 1000, &odomCallback);

  if(searchDistance_){
    geometry_msgs::PoseStamped goal;
    goal.header.frame_id = "map";
    goal.pose.position.z = 0;
    goal.pose.orientation.x = 0;
    goal.pose.orientation.y = 0;
    goal.pose.orientation.z = 0;
    goal.pose.orientation.w = 1;
    if(xmax_ - xmin_ > ymax_ - ymin_){
      goal.pose.position.x = xmin_;
      goal.pose.position.y = ymin_;
    }
    pos_pub.publish(goal);
    ros::Duration(1).sleep();

  }
}
  
  
};  // namespace rotate_recovery