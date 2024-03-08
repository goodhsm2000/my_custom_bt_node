// Made by HSM

#include <string>
#include "check_change_map.h"
#include <std_msgs/Int16.h>
#include <mutex>


CheckChangeMap::CheckChangeMap(
  const std::string & condition_name,
  const BT::NodeConfiguration & conf)
: BT::ConditionNode(condition_name, conf),
  move_base_("MoveBase", conf)
{      
}

BT::NodeStatus CheckChangeMap::tick()
{   
    
    sub_ = node_.subscribe("changed_map", 1, &CheckChangeMap::changemapCallback, this);

    ros::spinOnce();
    std::lock_guard<std::mutex> lock(mutex_);
    if (change_map_)
        ROS_INFO("changed_map true");
    else 
        ROS_INFO("changed_map false");

    if (change_map_ == 1) 
    {
        ROS_INFO("Force to change map");
        ROS_INFO("Return Failure");
        change_map_ = false;
        sub_.shutdown();
        move_base_.cancelgoal();
        return BT::NodeStatus::FAILURE;
    } 
    else
    {
        ROS_INFO("No change map");
        return BT::NodeStatus::SUCCESS;
    }
}

void CheckChangeMap::changemapCallback(const std_msgs::Int16::ConstPtr& msg)
{      
    // for (const auto& covariance : msg->pose) { // 아무런 객체도 검출되지 않으면 이 코드조차 실행이 안됨
    //     for (const auto& poses : covariance.pose) {
    //         for (const auto& point : poses.position) {
    // for (const auto& val: msg->data)

    std::lock_guard<std::mutex> lock(mutex_);
    val = msg->data;
    ROS_INFO("val");
    if (val == 1) {
        change_map_ = true;
        val = 0;
    }
    else
        change_map_ = false;
    return;
        
}

// // Made by HSM

// #include <string>
// #include "check_change_map2.h"
// #include <std_msgs/Int16.h>


// CheckChangeMap2::CheckChangeMap2(
//   const std::string & condition_name,
//   const BT::NodeConfiguration & conf)
// : BT::ConditionNode(condition_name, conf)
// {       
// }

// BT::NodeStatus CheckChangeMap2::tick()
// {   
    
//     sub_ = node_.subscribe("changed_map", 1, &CheckChangeMap2::changemapCallback2, this);

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
//         return BT::NodeStatus::FAILURE;
//     } 
//     else
//     {
//         ROS_INFO("No change map");
//         return BT::NodeStatus::SUCCESS;
//     }
// }

// void CheckChangeMap2::changemapCallback2(const std_msgs::Int16::ConstPtr& msg)
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