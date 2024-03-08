// Made by HSM

#include <string>
#include "distance_to_goal.h"
#include <nav_msgs/Odometry.h>
#include <cmath>

DistanceToGoal::DistanceToGoal(
  const std::string & condition_name,
  const BT::NodeConfiguration & conf)
: BT::ConditionNode(condition_name, conf)
{
    sub_ = node_.subscribe("odom", 100, &DistanceToGoal::distanceCallback, this);
}

BT::NodeStatus DistanceToGoal::tick()
{
    Rbiz goal;
    // 입력 포트에 있는 것을 읽어 goal에 저장
    if (!getInput<Rbiz>("goal", goal)) {
        // if I can't get this, there is something wrong with your BT.
        // For this reason throw an exception instead of returning FAILURE
        throw BT::RuntimeError("missing required input [goal]");
    }   

    goal_x = goal.x;
    goal_y = goal.y;

    ros::spinOnce();

    if (change_map_) 
    {
        ROS_INFO("Force to change map");
        return BT::NodeStatus::FAILURE;
    } 
    else
    {
        // ROS_INFO("No Collision");
        return BT::NodeStatus::SUCCESS;
    }
}

void DistanceToGoal::distanceCallback(const nav_msgs::Odometry::ConstPtr& msg)
{   
    // for (const auto& covariance : msg->pose) { // 아무런 객체도 검출되지 않으면 이 코드조차 실행이 안됨
    //     for (const auto& poses : covariance.pose) {
    //         for (const auto& point : poses.position) {
    point = msg->pose.pose.position;
    dis_to_goal = pow(point.x - goal_x, 2) + pow(point.y - goal_y, 2);
    ROS_INFO("Distance to goal:  %f", dis_to_goal);
    if (dis_to_goal <= 0.25)
    {
        // ROS_INFO("Distance to goal:  %f", dis_to_goal);
        change_map_ = true;
    }
    else
        change_map_ = false;
    return;
            
}