#ifndef ROTATE_RECOVERY_ROTATE_RECOVERY_H
#define ROTATE_RECOVERY_ROTATE_RECOVERY_H
#include <nav_core/recovery_behavior.h>
#include <costmap_2d/costmap_2d_ros.h>
#include <tf2_ros/buffer.h>
#include <base_local_planner/costmap_model.h>
#include <string>

namespace laps_redox
{
/**
 * @class RotateRecovery
 * @brief A recovery behavior that rotates the robot in-place to attempt to clear out space
 */
class LapsRedox : public nav_core::RecoveryBehavior
{
public:
  /**
   * @brief  Constructor, make sure to call initialize in addition to actually initialize the object
   */
  Laps();

  /**
   * @brief  Initialization function for the RotateRecovery recovery behavior
   * @param name Namespace used in initialization
   * @param tf (unused)
   * @param global_costmap (unused)
   * @param local_costmap A pointer to the local_costmap used by the navigation stack
   */
  void initialize(std::string name, tf2_ros::Buffer*,
                  costmap_2d::Costmap2DROS*, costmap_2d::Costmap2DROS* local_costmap);

  /**
   * @brief  Run the RotateRecovery recovery behavior.
   */
  void runBehavior();

  /**
   * @brief  Destructor for the rotate recovery behavior
   */
  ~LapsRedox();

private:
  costmap_2d::Costmap2DROS* local_costmap_;
  bool initialized_;
  bool searchDistance_;
  double xmin_, xmax_, ymin_, ymax_;
  double x_, y_;
  base_local_planner::CostmapModel* world_model_;
};
};  // namespace rotate_recovery
#endif  // ROTATE_RECOVERY_ROTATE_RECOVERY_H