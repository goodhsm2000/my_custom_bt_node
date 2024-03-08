// Made by HSM

#include <string>
#include "obs_collision_check.h"

ObsCollisionCheck::ObsCollisionCheck(
  const std::string & condition_name,
  const BT::NodeConfiguration & conf)
: BT::ConditionNode(condition_name, conf)
{
    sub_ = node_.subscribe("CollisionData", 100, &CollisionCheck::collisionCallback, this);
}

BT::NodeStatus ObsCollisionCheck::tick()
{

    ros::spinOnce();

    if (obstacle_collision_) 
    {
        ROS_INFO("Move back to avoid obstacle");
        return BT::NodeStatus::FAILURE;
    } 
    else
    {
        // ROS_INFO("No Collision");
        return BT::NodeStatus::SUCCESS;
    }
}

void ObsCollisionCheck::obscollisionCallback(const morai_msgs::CollisionData::ConstPtr& msg)
{   
    for (const auto& collision_obj : msg->collision_object) { // 아무런 객체도 검출되지 않으면 이 코드조차 실행이 안됨
        if (collision_obj.type == 2) 
        {
            ROS_INFO("Collision occured with %s", collision_obj.name.c_str());
            obstacle_collision_ = true;
        }
        else
            obstacle_collision_ = false;
        return;
        }
    
}