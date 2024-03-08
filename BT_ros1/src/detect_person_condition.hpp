// Copyright (c) 2020 Sarthak Mittal
// Made by HSM

#include <mutex>
#include <string>
#include <vector>
#include <ros/ros.h>
#include <yolov8_ros_msgs/BoundingBoxes.h>
#include <yolov8_ros_msgs/BoundingBox.h>
#include "behaviortree_cpp_v3/condition_node.h"

class DetectPersonCondition : public BT::ConditionNode // BT::ConditionNode 클래스를 상속하는 DetectPersonCondition 클래스를 선언
{
public:
  DetectPersonCondition(
    const std::string & condition_name,
    const BT::NodeConfiguration & conf);

  DetectPersonCondition() = delete;

  BT::NodeStatus tick() override;

  static BT::PortsList providedPorts()
  {
    return {};
  }

private:
  void detectionCallback(const yolov8_ros_msgs::BoundingBoxes::ConstPtr& msg);
  ros::NodeHandle node_;
  ros::Subscriber sub_;
  bool person_detected_ = false;
  std::mutex mutex_;

};
