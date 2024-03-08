// Made by HSM

#include "event_check.h"
#include <ros/ros.h>
#include <string>
#include <morai_msgs/WoowaDillyEventCmdSrv.h>
#include "behaviortree_cpp_v3/condition_node.h"
#include <morai_msgs/DillyCmd.h>
#include <morai_msgs/DillyCmdResponse.h>




EventCheck::EventCheck(
  const std::string & name,
  const BT::NodeConfiguration & conf)
: BT::ConditionNode(name, conf)
{
}

BT::NodeStatus EventCheck::tick()
{   
    Rbiz event;

    if (!getInput("mode", event)) {
        // if I can't get this, there is something wrong with your BT.
        // For this reason throw an exception instead of returning FAILURE
        throw BT::RuntimeError("missing required input [mode] and [onj_num]");
    }

    if (event.move_mode == "Receive")
    {
        Pickup = true;

    }
    else if (event.move_mode == "Deliver")
    {
        Pickup = false;
    }
    else
    {
        throw BT::RuntimeError("An incorrect notation of [mode]");
    }

    ItemIndex = event.obj_num;

    // ROS_INFO("\rmap_file is %s", map_file.c_str());
    eventclient = node_.serviceClient<morai_msgs::WoowaDillyEventCmdSrv>("WoowaDillyEventCmd");

    morai_msgs::WoowaDillyEventCmdSrv::Request req;
    morai_msgs::WoowaDillyEventCmdSrv::Response resp;

    morai_msgs::DillyCmd msg;
    msg.isPickup = Pickup;
    msg.deliveryItemIndex = ItemIndex;

    req.request = msg;

    // 일반적으로 call 메서드의 반환 값은 bool
    // morai_msgs::DillyCmdResponse response.result = eventclient.call(req, resp);
    bool srv_result = eventclient.call(req, resp);

    ROS_INFO("result %u", resp.response.result);
    

    // Call the change_map service
    if (srv_result == 1 && resp.response.result == 1)
    {   
        // success
        ROS_INFO("num %d obj %s completed", event.obj_num, event.move_mode.c_str() );
        return BT::NodeStatus::SUCCESS;
    }
    else if (srv_result == 0)
    {   
        // fail
        ROS_INFO("service call failed");
        return BT::NodeStatus::FAILURE;
    }
    else
    {   
        // fail
        ROS_INFO("num %d obj %s failed", event.obj_num, event.move_mode.c_str() );
        return BT::NodeStatus::FAILURE;
    }
    
};