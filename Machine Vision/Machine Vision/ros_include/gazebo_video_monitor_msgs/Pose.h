// Generated by gencpp from file gazebo_video_monitor_msgs/Pose.msg
// DO NOT EDIT!


#ifndef GAZEBO_VIDEO_MONITOR_MSGS_MESSAGE_POSE_H
#define GAZEBO_VIDEO_MONITOR_MSGS_MESSAGE_POSE_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace gazebo_video_monitor_msgs
{
template <class ContainerAllocator>
struct Pose_
{
  typedef Pose_<ContainerAllocator> Type;

  Pose_()
    : x(0.0)
    , y(0.0)
    , z(0.0)
    , roll(0.0)
    , pitch(0.0)
    , yaw(0.0)  {
    }
  Pose_(const ContainerAllocator& _alloc)
    : x(0.0)
    , y(0.0)
    , z(0.0)
    , roll(0.0)
    , pitch(0.0)
    , yaw(0.0)  {
  (void)_alloc;
    }



   typedef double _x_type;
  _x_type x;

   typedef double _y_type;
  _y_type y;

   typedef double _z_type;
  _z_type z;

   typedef double _roll_type;
  _roll_type roll;

   typedef double _pitch_type;
  _pitch_type pitch;

   typedef double _yaw_type;
  _yaw_type yaw;





  typedef boost::shared_ptr< ::gazebo_video_monitor_msgs::Pose_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::gazebo_video_monitor_msgs::Pose_<ContainerAllocator> const> ConstPtr;

}; // struct Pose_

typedef ::gazebo_video_monitor_msgs::Pose_<std::allocator<void> > Pose;

typedef boost::shared_ptr< ::gazebo_video_monitor_msgs::Pose > PosePtr;
typedef boost::shared_ptr< ::gazebo_video_monitor_msgs::Pose const> PoseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::gazebo_video_monitor_msgs::Pose_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::gazebo_video_monitor_msgs::Pose_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::gazebo_video_monitor_msgs::Pose_<ContainerAllocator1> & lhs, const ::gazebo_video_monitor_msgs::Pose_<ContainerAllocator2> & rhs)
{
  return lhs.x == rhs.x &&
    lhs.y == rhs.y &&
    lhs.z == rhs.z &&
    lhs.roll == rhs.roll &&
    lhs.pitch == rhs.pitch &&
    lhs.yaw == rhs.yaw;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::gazebo_video_monitor_msgs::Pose_<ContainerAllocator1> & lhs, const ::gazebo_video_monitor_msgs::Pose_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace gazebo_video_monitor_msgs

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::gazebo_video_monitor_msgs::Pose_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::gazebo_video_monitor_msgs::Pose_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::gazebo_video_monitor_msgs::Pose_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::gazebo_video_monitor_msgs::Pose_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::gazebo_video_monitor_msgs::Pose_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::gazebo_video_monitor_msgs::Pose_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::gazebo_video_monitor_msgs::Pose_<ContainerAllocator> >
{
  static const char* value()
  {
    return "1a83f0bdabe750ce0cfb45a14ec63457";
  }

  static const char* value(const ::gazebo_video_monitor_msgs::Pose_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x1a83f0bdabe750ceULL;
  static const uint64_t static_value2 = 0x0cfb45a14ec63457ULL;
};

template<class ContainerAllocator>
struct DataType< ::gazebo_video_monitor_msgs::Pose_<ContainerAllocator> >
{
  static const char* value()
  {
    return "gazebo_video_monitor_msgs/Pose";
  }

  static const char* value(const ::gazebo_video_monitor_msgs::Pose_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::gazebo_video_monitor_msgs::Pose_<ContainerAllocator> >
{
  static const char* value()
  {
    return "float64 x\n"
"float64 y\n"
"float64 z\n"
"float64 roll\n"
"float64 pitch\n"
"float64 yaw\n"
;
  }

  static const char* value(const ::gazebo_video_monitor_msgs::Pose_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::gazebo_video_monitor_msgs::Pose_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.x);
      stream.next(m.y);
      stream.next(m.z);
      stream.next(m.roll);
      stream.next(m.pitch);
      stream.next(m.yaw);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct Pose_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::gazebo_video_monitor_msgs::Pose_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::gazebo_video_monitor_msgs::Pose_<ContainerAllocator>& v)
  {
    s << indent << "x: ";
    Printer<double>::stream(s, indent + "  ", v.x);
    s << indent << "y: ";
    Printer<double>::stream(s, indent + "  ", v.y);
    s << indent << "z: ";
    Printer<double>::stream(s, indent + "  ", v.z);
    s << indent << "roll: ";
    Printer<double>::stream(s, indent + "  ", v.roll);
    s << indent << "pitch: ";
    Printer<double>::stream(s, indent + "  ", v.pitch);
    s << indent << "yaw: ";
    Printer<double>::stream(s, indent + "  ", v.yaw);
  }
};

} // namespace message_operations
} // namespace ros

#endif // GAZEBO_VIDEO_MONITOR_MSGS_MESSAGE_POSE_H
