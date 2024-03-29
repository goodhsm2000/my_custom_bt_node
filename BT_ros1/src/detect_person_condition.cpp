#include <string>

#include "detect_person_condition.hpp"


DetectPersonCondition::DetectPersonCondition(
  const std::string & condition_name,
  const BT::NodeConfiguration & conf)
: BT::ConditionNode(condition_name, conf)
{
  sub_ = node_.subscribe("yolov8/detect_with_dis", 1000, &DetectPersonCondition::detectionCallback, this);
}

BT::NodeStatus DetectPersonCondition::tick()
{

  ros::spinOnce();

  std::lock_guard<std::mutex> lock(mutex_);
  if (person_detected_) 
  {
    ROS_INFO("Person detected");
    return BT::NodeStatus::FAILURE;
  } 
  else
  {
    ROS_INFO( "Person didn't detected"); 
    return BT::NodeStatus::SUCCESS;
  }
}

void DetectPersonCondition::detectionCallback(const yolov8_ros_msgs::BoundingBoxes::ConstPtr& msg)
{
  std::lock_guard<std::mutex> lock(mutex_);
  // ROS_INFO("1");
  person_detected_ = false;
  if (msg->bounding_boxes.empty())
    person_detected_ = false;
    ROS_INFO("Nothing was detected");
  for (const auto& detection : msg->bounding_boxes) { // 아무런 객체도 검출되지 않으면 이 코드조차 실행이 안됨
    if (detection.Class == "person" && detection.distance > 0 && detection.distance < 0.8) 
      person_detected_ = true;
  }

  return;
  }



// #include <string>
// #include "check_change_map.h"
// #include <std_msgs/Int16.h>
// #include <mutex>


// CheckChangeMap::CheckChangeMap(
//   const std::string & condition_name,
//   const BT::NodeConfiguration & conf)
// : BT::ConditionNode(condition_name, conf),
//   move_base_("MoveBase", conf)
// {      
// }

// BT::NodeStatus CheckChangeMap::tick()
// {   
    
//     sub_ = node_.subscribe("changed_map", 1, &CheckChangeMap::changemapCallback, this);

//     ros::spinOnce();
//     std::lock_guard<std::mutex> lock(mutex_);
//     if (change_map_)
//         ROS_INFO("changed_map true");
//     else 
//         ROS_INFO("changed_map false");

//     if (change_map_ == 1) 
//     {
//         ROS_INFO("Force to change map");
//         ROS_INFO("Return Failure");
//         change_map_ = false;
//         sub_.shutdown();
//         move_base_.cancelgoal();
//         return BT::NodeStatus::FAILURE;
//     } 
//     else
//     {
//         ROS_INFO("No change map");
//         return BT::NodeStatus::SUCCESS;
//     }
// }

// void CheckChangeMap::changemapCallback(const std_msgs::Int16::ConstPtr& msg)
// {      
//     // for (const auto& covariance : msg->pose) { // 아무런 객체도 검출되지 않으면 이 코드조차 실행이 안됨
//     //     for (const auto& poses : covariance.pose) {
//     //         for (const auto& point : poses.position) {
//     // for (const auto& val: msg->data)

//     std::lock_guard<std::mutex> lock(mutex_);
//     val = msg->data;
//     ROS_INFO("val");
//     if (val == 1) {
//         change_map_ = true;
//         val = 0;
//     }
//     else
//         change_map_ = false;
//     return;
        
// }