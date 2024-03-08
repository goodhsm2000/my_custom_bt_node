// Made by HSM

// #include <mutex>
#include <string>
#include <vector>

#include <ros/ros.h>
#include "behaviortree_cpp_v3/condition_node.h"
#include <nav_msgs/Odometry.h>
#include "movebase_client.h"
// #include <geometry_msgs/Point.h>


class DistanceToGoal : public BT::ConditionNode // BT::ConditionNode 클래스를 상속하는 CollisionCheck 클래스를 선언
{
public:
    DistanceToGoal(
        const std::string & condition_name,
        const BT::NodeConfiguration & conf);

    DistanceToGoal() = delete;

    static BT::PortsList providedPorts()
    {
        return{ BT::InputPort<Rbiz>("goal") };
    }

    BT::NodeStatus tick() override;

private:

    void distanceCallback(const nav_msgs::Odometry::ConstPtr& msg);
    ros::NodeHandle node_;
    ros::Subscriber sub_;
    bool change_map_ = false;
    float goal_x, goal_y, dis_to_goal;
    geometry_msgs::Point point; 
};