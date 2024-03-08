// Made by HSM

#include <string>
#include "collision_check.h"

CollisionCheck::CollisionCheck(
  const std::string & condition_name,
  const BT::NodeConfiguration & conf)
: BT::ConditionNode(condition_name, conf)
{
    sub_ = node_.subscribe("CollisionData", 100, &CollisionCheck::collisionCallback, this);
}

BT::NodeStatus CollisionCheck::tick()
{

    ros::spinOnce();

    if (person_collision_) 
    {
        ROS_INFO("Move again to the set goal.");
        return BT::NodeStatus::FAILURE;
    } 
    else
    {
        // ROS_INFO("No Collision");
        return BT::NodeStatus::SUCCESS;
    }
}

void CollisionCheck::collisionCallback(const morai_msgs::CollisionData::ConstPtr& msg)
{   
    for (const auto& collision_obj : msg->collision_object) { // 아무런 객체도 검출되지 않으면 이 코드조차 실행이 안됨
        if (collision_obj.type == 0) 
        {
            ROS_INFO("Collision occured with %s", collision_obj.name.c_str());
            person_collision_ = true;
        }
        else
            person_collision_ = false;
        return;
        }
    
}