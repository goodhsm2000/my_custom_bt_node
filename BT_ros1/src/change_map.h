// Made by HSM

#include <ros/ros.h>
#include <behaviortree_cpp_v3/action_node.h>
#include <string>
#include "movebase_client.h"


class ChangeMap : public BT::SyncActionNode
{
public:

    ChangeMap(
        const std::string & name,
        const BT::NodeConfiguration & conf);

    ~ChangeMap() override = default;

    // It is mandatory to define this static method.
    static BT::PortsList providedPorts()
    {
        return{ BT::InputPort<Rbiz>("map") };
    }

    virtual BT::NodeStatus tick() override;

private:
        ros::NodeHandle node_;
        ros::ServiceClient mapclient;
        // std::string map_mode;
        std::string map_file;
};
