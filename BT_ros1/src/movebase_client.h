#pragma once

#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <behaviortree_cpp_v3/action_node.h>
#include <tf/transform_datatypes.h>
#include <string>
#include <actionlib/client/client_goal_handle_imp.h>

// Custom type
struct Rbiz
{
    double x, y, quaternion_z, quaternion_w;
    std::string move_mode;
    int obj_num;
    std::string map_mode;
};


namespace BT
{
template <> inline
Rbiz convertFromString(StringView key)
{
    // three real numbers separated by semicolons
    auto parts = BT::splitString(key, ';');
    if (parts.size() != 4)
    {
        throw BT::RuntimeError("invalid input)");
    }
    else
    {
        Rbiz output;

        output.x     = convertFromString<double>(parts[0]);
        output.y     = convertFromString<double>(parts[1]);
        output.quaternion_z = convertFromString<double>(parts[2]);
        output.quaternion_w = convertFromString<double>(parts[3]);
        // output.move_mode = convertFromString<std::string>(parts[4]);
        // output.obj_num = convertFromString<int>(parts[5]);
        // output.map_mode = convertFromString<std::string>(parts[6]);
        return output;
    }
}
} // end namespace BT

//----------------------------------------------------------------

class MoveBase : public BT::AsyncActionNode
{
public:

    MoveBase(const std::string& name, const BT::NodeConfiguration& config)
        : BT::AsyncActionNode(name, config),
          _client("move_base", true)
    {
    }

    // It is mandatory to define this static method.
    static BT::PortsList providedPorts()
    {
        return{ BT::InputPort<Rbiz>("goal") };
    }

    void cancelgoal();

    virtual BT::NodeStatus tick() override;

    // _absorted 변수를 이용하여 이동 작업 중지 여부 결정
    virtual void halt() override
    {
        _aborted = true;
    }

private:
    typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
    // _clinet 객체는 ROS의 move_base 서비스와 통신하여 로봇의 이동 작업을 관리
    MoveBaseClient _client;

    typedef actionlib::ClientGoalHandle<move_base_msgs::MoveBaseAction> ClientGoal;
    ClientGoal _goalhandle;
    bool _aborted;
};


