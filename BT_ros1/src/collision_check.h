// Made by HSM

// #include <mutex>
#include <string>
#include <vector>

#include <ros/ros.h>
#include "behaviortree_cpp_v3/condition_node.h"
#include <morai_msgs/CollisionData.h>
#include <mutex>


class CollisionCheck : public BT::ConditionNode // BT::ConditionNode 클래스를 상속하는 CollisionCheck 클래스를 선언
{
public:
    CollisionCheck(
        const std::string & condition_name,
        const BT::NodeConfiguration & conf);

    CollisionCheck() = delete;

    BT::NodeStatus tick() override;

    static BT::PortsList providedPorts()
    {
        return {};
    }

private:

    void collisionCallback(const morai_msgs::CollisionData::ConstPtr& msg);
    ros::NodeHandle node_;
    ros::Subscriber sub_;
    bool person_collision_ = false;

};