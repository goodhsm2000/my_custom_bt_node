// Made by HSM

#include <ros/ros.h>
#include "behaviortree_cpp_v3/condition_node.h"
#include <string>
#include "movebase_client.h"


class EventCheck : public BT::ConditionNode
{
public:

    EventCheck(
        const std::string & name,
        const BT::NodeConfiguration & conf);

    ~EventCheck() override = default;

    // It is mandatory to define this static method.
    static BT::PortsList providedPorts()
    {
        return{ BT::InputPort<Rbiz>("mode"), BT::InputPort<Rbiz>("obj_num") };
    }

    virtual BT::NodeStatus tick() override;

private:
        ros::NodeHandle node_;
        ros::ServiceClient eventclient;
        bool Pickup;
        int32_t ItemIndex;
};
