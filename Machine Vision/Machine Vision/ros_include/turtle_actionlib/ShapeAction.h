// Generated by gencpp from file turtle_actionlib/ShapeAction.msg
// DO NOT EDIT!


#ifndef TURTLE_ACTIONLIB_MESSAGE_SHAPEACTION_H
#define TURTLE_ACTIONLIB_MESSAGE_SHAPEACTION_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <turtle_actionlib/ShapeActionGoal.h>
#include <turtle_actionlib/ShapeActionResult.h>
#include <turtle_actionlib/ShapeActionFeedback.h>

namespace turtle_actionlib
{
template <class ContainerAllocator>
struct ShapeAction_
{
  typedef ShapeAction_<ContainerAllocator> Type;

  ShapeAction_()
    : action_goal()
    , action_result()
    , action_feedback()  {
    }
  ShapeAction_(const ContainerAllocator& _alloc)
    : action_goal(_alloc)
    , action_result(_alloc)
    , action_feedback(_alloc)  {
  (void)_alloc;
    }



   typedef  ::turtle_actionlib::ShapeActionGoal_<ContainerAllocator>  _action_goal_type;
  _action_goal_type action_goal;

   typedef  ::turtle_actionlib::ShapeActionResult_<ContainerAllocator>  _action_result_type;
  _action_result_type action_result;

   typedef  ::turtle_actionlib::ShapeActionFeedback_<ContainerAllocator>  _action_feedback_type;
  _action_feedback_type action_feedback;





  typedef boost::shared_ptr< ::turtle_actionlib::ShapeAction_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::turtle_actionlib::ShapeAction_<ContainerAllocator> const> ConstPtr;

}; // struct ShapeAction_

typedef ::turtle_actionlib::ShapeAction_<std::allocator<void> > ShapeAction;

typedef boost::shared_ptr< ::turtle_actionlib::ShapeAction > ShapeActionPtr;
typedef boost::shared_ptr< ::turtle_actionlib::ShapeAction const> ShapeActionConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::turtle_actionlib::ShapeAction_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::turtle_actionlib::ShapeAction_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::turtle_actionlib::ShapeAction_<ContainerAllocator1> & lhs, const ::turtle_actionlib::ShapeAction_<ContainerAllocator2> & rhs)
{
  return lhs.action_goal == rhs.action_goal &&
    lhs.action_result == rhs.action_result &&
    lhs.action_feedback == rhs.action_feedback;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::turtle_actionlib::ShapeAction_<ContainerAllocator1> & lhs, const ::turtle_actionlib::ShapeAction_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace turtle_actionlib

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::turtle_actionlib::ShapeAction_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::turtle_actionlib::ShapeAction_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::turtle_actionlib::ShapeAction_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::turtle_actionlib::ShapeAction_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::turtle_actionlib::ShapeAction_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::turtle_actionlib::ShapeAction_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::turtle_actionlib::ShapeAction_<ContainerAllocator> >
{
  static const char* value()
  {
    return "d73b17d6237a925511f5d7727a1dc903";
  }

  static const char* value(const ::turtle_actionlib::ShapeAction_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xd73b17d6237a9255ULL;
  static const uint64_t static_value2 = 0x11f5d7727a1dc903ULL;
};

template<class ContainerAllocator>
struct DataType< ::turtle_actionlib::ShapeAction_<ContainerAllocator> >
{
  static const char* value()
  {
    return "turtle_actionlib/ShapeAction";
  }

  static const char* value(const ::turtle_actionlib::ShapeAction_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::turtle_actionlib::ShapeAction_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n"
"\n"
"ShapeActionGoal action_goal\n"
"ShapeActionResult action_result\n"
"ShapeActionFeedback action_feedback\n"
"\n"
"================================================================================\n"
"MSG: turtle_actionlib/ShapeActionGoal\n"
"# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n"
"\n"
"Header header\n"
"actionlib_msgs/GoalID goal_id\n"
"ShapeGoal goal\n"
"\n"
"================================================================================\n"
"MSG: std_msgs/Header\n"
"# Standard metadata for higher-level stamped data types.\n"
"# This is generally used to communicate timestamped data \n"
"# in a particular coordinate frame.\n"
"# \n"
"# sequence ID: consecutively increasing ID \n"
"uint32 seq\n"
"#Two-integer timestamp that is expressed as:\n"
"# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n"
"# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n"
"# time-handling sugar is provided by the client library\n"
"time stamp\n"
"#Frame this data is associated with\n"
"string frame_id\n"
"\n"
"================================================================================\n"
"MSG: actionlib_msgs/GoalID\n"
"# The stamp should store the time at which this goal was requested.\n"
"# It is used by an action server when it tries to preempt all\n"
"# goals that were requested before a certain time\n"
"time stamp\n"
"\n"
"# The id provides a way to associate feedback and\n"
"# result message with specific goal requests. The id\n"
"# specified must be unique.\n"
"string id\n"
"\n"
"\n"
"================================================================================\n"
"MSG: turtle_actionlib/ShapeGoal\n"
"# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n"
"#goal definition\n"
"int32 edges\n"
"float32 radius\n"
"\n"
"================================================================================\n"
"MSG: turtle_actionlib/ShapeActionResult\n"
"# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n"
"\n"
"Header header\n"
"actionlib_msgs/GoalStatus status\n"
"ShapeResult result\n"
"\n"
"================================================================================\n"
"MSG: actionlib_msgs/GoalStatus\n"
"GoalID goal_id\n"
"uint8 status\n"
"uint8 PENDING         = 0   # The goal has yet to be processed by the action server\n"
"uint8 ACTIVE          = 1   # The goal is currently being processed by the action server\n"
"uint8 PREEMPTED       = 2   # The goal received a cancel request after it started executing\n"
"                            #   and has since completed its execution (Terminal State)\n"
"uint8 SUCCEEDED       = 3   # The goal was achieved successfully by the action server (Terminal State)\n"
"uint8 ABORTED         = 4   # The goal was aborted during execution by the action server due\n"
"                            #    to some failure (Terminal State)\n"
"uint8 REJECTED        = 5   # The goal was rejected by the action server without being processed,\n"
"                            #    because the goal was unattainable or invalid (Terminal State)\n"
"uint8 PREEMPTING      = 6   # The goal received a cancel request after it started executing\n"
"                            #    and has not yet completed execution\n"
"uint8 RECALLING       = 7   # The goal received a cancel request before it started executing,\n"
"                            #    but the action server has not yet confirmed that the goal is canceled\n"
"uint8 RECALLED        = 8   # The goal received a cancel request before it started executing\n"
"                            #    and was successfully cancelled (Terminal State)\n"
"uint8 LOST            = 9   # An action client can determine that a goal is LOST. This should not be\n"
"                            #    sent over the wire by an action server\n"
"\n"
"#Allow for the user to associate a string with GoalStatus for debugging\n"
"string text\n"
"\n"
"\n"
"================================================================================\n"
"MSG: turtle_actionlib/ShapeResult\n"
"# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n"
"#result definition\n"
"float32 interior_angle\n"
"float32 apothem\n"
"\n"
"================================================================================\n"
"MSG: turtle_actionlib/ShapeActionFeedback\n"
"# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n"
"\n"
"Header header\n"
"actionlib_msgs/GoalStatus status\n"
"ShapeFeedback feedback\n"
"\n"
"================================================================================\n"
"MSG: turtle_actionlib/ShapeFeedback\n"
"# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n"
"#feedback\n"
"\n"
"\n"
;
  }

  static const char* value(const ::turtle_actionlib::ShapeAction_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::turtle_actionlib::ShapeAction_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.action_goal);
      stream.next(m.action_result);
      stream.next(m.action_feedback);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct ShapeAction_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::turtle_actionlib::ShapeAction_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::turtle_actionlib::ShapeAction_<ContainerAllocator>& v)
  {
    s << indent << "action_goal: ";
    s << std::endl;
    Printer< ::turtle_actionlib::ShapeActionGoal_<ContainerAllocator> >::stream(s, indent + "  ", v.action_goal);
    s << indent << "action_result: ";
    s << std::endl;
    Printer< ::turtle_actionlib::ShapeActionResult_<ContainerAllocator> >::stream(s, indent + "  ", v.action_result);
    s << indent << "action_feedback: ";
    s << std::endl;
    Printer< ::turtle_actionlib::ShapeActionFeedback_<ContainerAllocator> >::stream(s, indent + "  ", v.action_feedback);
  }
};

} // namespace message_operations
} // namespace ros

#endif // TURTLE_ACTIONLIB_MESSAGE_SHAPEACTION_H
