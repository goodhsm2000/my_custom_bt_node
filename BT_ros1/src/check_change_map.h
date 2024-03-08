// Made by HSM

// #include <mutex>
#include <string>
#include <vector>

#include <ros/ros.h>
#include "behaviortree_cpp_v3/condition_node.h"
#include <std_msgs/Int16.h>
#include <mutex>
#include "movebase_client.h"


// #include <geometry_msgs/Point.h>


class CheckChangeMap : public BT::ConditionNode // BT::ConditionNode 클래스를 상속하는 CollisionCheck 클래스를 선언
{
public:
    CheckChangeMap(
        const std::string & condition_name,
        const BT::NodeConfiguration & conf);

    CheckChangeMap() = delete;

    static BT::PortsList providedPorts()
    {
        return {};
    }

    BT::NodeStatus tick() override;

private:

    void changemapCallback(const std_msgs::Int16::ConstPtr& msg);
    ros::NodeHandle node_;
    ros::Subscriber sub_;
    bool change_map_ = false;
    std::mutex mutex_;
    int val = 0;
    MoveBase move_base_;
};

// // Made by HSM

// // #include <mutex>
// #include <string>
// #include <vector>

// #include <ros/ros.h>
// #include "behaviortree_cpp_v3/condition_node.h"
// #include <std_msgs/Int16.h>
// #include <mutex>


// // #include <geometry_msgs/Point.h>


// class CheckChangeMap2 : public BT::ConditionNode // BT::ConditionNode 클래스를 상속하는 CollisionCheck 클래스를 선언
// {
// public:
//     CheckChangeMap2(
//         const std::string & condition_name,
//         const BT::NodeConfiguration & conf);

//     CheckChangeMap2() = delete;

//     static BT::PortsList providedPorts()
//     {
//         return {};
//     }

//     BT::NodeStatus tick() override;

// private:

//     void changemapCallback2(const std_msgs::Int16::ConstPtr& msg);
//     ros::NodeHandle node_;
//     ros::Subscriber sub_;
//     bool change_map_ = false;
//     std::mutex mutex_;
//     int val = 0;
// };