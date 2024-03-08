// Made by HSM

#include "change_map.h"
#include <ros/ros.h>
#include <string>
#include <nav_msgs/LoadMap.h>
#include <behaviortree_cpp_v3/action_node.h>


ChangeMap::ChangeMap(
  const std::string & name,
  const BT::NodeConfiguration & conf)
: BT::SyncActionNode(name, conf)
{
}

BT::NodeStatus ChangeMap::tick()
{   
    Rbiz map;
    // 입력 포트에 있는 것을 읽어 map에 저장
    if (!getInput<Rbiz>("map", map)) {
        // if I can't get this, there is something wrong with your BT.
        // For this reason throw an exception instead of returning FAILURE
        throw BT::RuntimeError("missing required input [map]");
    }

    // auto parts = BT::splitString(map, ';');
    // if (parts.size() != 5)
    // {
    //     throw BT::RuntimeError("invalid input)");
    // }
    // else
    // {
    //     map_mode = BT::convertFromString<std::string>(parts[4]);
    // }

    if (map.map_mode == "OutdoorMap")
    {
        map_file = "/home/hsm/neuronbot2_ros1_ws/src/neuronbot2/neuronbot2_nav/maps/phenix.yaml";

    }
    else if (map.map_mode == "IndoorMap")
    {
        map_file = "/home/hsm/neuronbot2_ros1_ws/src/neuronbot2/neuronbot2_nav/maps/mememan.yaml";
    }
    else
    {
        throw BT::RuntimeError("An incorrect notation of [map]");
    }

    // ROS_INFO("\rmap_file is %s", map_file.c_str());
    mapclient = node_.serviceClient<nav_msgs::LoadMap>("change_map");

    nav_msgs::LoadMap::Request req;
    nav_msgs::LoadMap::Response resp;

    req.map_url = map_file;

    // 서비스를 요청하고 요청이 받아졌을 때 true를 반환하고, 실패하면 false를 반환
    // 요청에 대한 결과는 resp에 저장됨
    bool srv_result = mapclient.call(req, resp);

    ROS_INFO("result %u", resp.result);

    // Call the change_map service
    if (srv_result == 1 && resp.result == 0)
    {   
        //change map success
        ROS_INFO("Change map Successed");
        ros::WallDuration duration(0.5);
        duration.sleep();
        return BT::NodeStatus::SUCCESS;

    }
    else
    {   
        //change_map fail
        ROS_INFO("Change map Failed");
        return BT::NodeStatus::FAILURE;
    }
    
};






