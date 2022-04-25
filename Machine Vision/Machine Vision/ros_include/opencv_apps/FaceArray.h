// Generated by gencpp from file opencv_apps/FaceArray.msg
// DO NOT EDIT!


#ifndef OPENCV_APPS_MESSAGE_FACEARRAY_H
#define OPENCV_APPS_MESSAGE_FACEARRAY_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <opencv_apps/Face.h>

namespace opencv_apps
{
template <class ContainerAllocator>
struct FaceArray_
{
  typedef FaceArray_<ContainerAllocator> Type;

  FaceArray_()
    : faces()  {
    }
  FaceArray_(const ContainerAllocator& _alloc)
    : faces(_alloc)  {
  (void)_alloc;
    }



   typedef std::vector< ::opencv_apps::Face_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::opencv_apps::Face_<ContainerAllocator> >::other >  _faces_type;
  _faces_type faces;





  typedef boost::shared_ptr< ::opencv_apps::FaceArray_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::opencv_apps::FaceArray_<ContainerAllocator> const> ConstPtr;

}; // struct FaceArray_

typedef ::opencv_apps::FaceArray_<std::allocator<void> > FaceArray;

typedef boost::shared_ptr< ::opencv_apps::FaceArray > FaceArrayPtr;
typedef boost::shared_ptr< ::opencv_apps::FaceArray const> FaceArrayConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::opencv_apps::FaceArray_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::opencv_apps::FaceArray_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::opencv_apps::FaceArray_<ContainerAllocator1> & lhs, const ::opencv_apps::FaceArray_<ContainerAllocator2> & rhs)
{
  return lhs.faces == rhs.faces;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::opencv_apps::FaceArray_<ContainerAllocator1> & lhs, const ::opencv_apps::FaceArray_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace opencv_apps

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::opencv_apps::FaceArray_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::opencv_apps::FaceArray_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::opencv_apps::FaceArray_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::opencv_apps::FaceArray_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::opencv_apps::FaceArray_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::opencv_apps::FaceArray_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::opencv_apps::FaceArray_<ContainerAllocator> >
{
  static const char* value()
  {
    return "3ae7a36ff47d72f5dd1d764612b2b3c8";
  }

  static const char* value(const ::opencv_apps::FaceArray_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x3ae7a36ff47d72f5ULL;
  static const uint64_t static_value2 = 0xdd1d764612b2b3c8ULL;
};

template<class ContainerAllocator>
struct DataType< ::opencv_apps::FaceArray_<ContainerAllocator> >
{
  static const char* value()
  {
    return "opencv_apps/FaceArray";
  }

  static const char* value(const ::opencv_apps::FaceArray_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::opencv_apps::FaceArray_<ContainerAllocator> >
{
  static const char* value()
  {
    return "Face[] faces\n"
"\n"
"\n"
"================================================================================\n"
"MSG: opencv_apps/Face\n"
"Rect face\n"
"Rect[] eyes\n"
"string label\n"
"float64 confidence\n"
"\n"
"================================================================================\n"
"MSG: opencv_apps/Rect\n"
"# opencv Rect data type, x-y is center point\n"
"float64 x\n"
"float64 y\n"
"float64 width\n"
"float64 height\n"
"\n"
;
  }

  static const char* value(const ::opencv_apps::FaceArray_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::opencv_apps::FaceArray_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.faces);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct FaceArray_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::opencv_apps::FaceArray_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::opencv_apps::FaceArray_<ContainerAllocator>& v)
  {
    s << indent << "faces[]" << std::endl;
    for (size_t i = 0; i < v.faces.size(); ++i)
    {
      s << indent << "  faces[" << i << "]: ";
      s << std::endl;
      s << indent;
      Printer< ::opencv_apps::Face_<ContainerAllocator> >::stream(s, indent + "    ", v.faces[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // OPENCV_APPS_MESSAGE_FACEARRAY_H
