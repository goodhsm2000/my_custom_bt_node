#include <ros/ros.h>
#include <behaviortree_cpp_v3/action_node.h>
#include <string>
#include "movebase_client.h"
#include <actionlib/client/simple_action_client.h>
#include <move_base_msgs/MoveBaseAction.h>


class WaitAction : public BT::SyncActionNode
{
public:
  WaitAction(
        const std::string & name,
        const BT::NodeConfiguration & conf);

  virtual BT::NodeStatus tick() override;

  // Any BT node that accepts parameters must provide a requiredNodeParameters method
  static BT::PortsList providedPorts()
  {
    return{BT::InputPort<int>("wait_duration", 1, "Wait time")};

  }

private:
  // typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
  // _clinet 객체는 ROS의 move_base 서비스와 통신하여 로봇의 이동 작업을 관리
  // MoveBaseClient _client;
  ros::NodeHandle node_;
  ros::Publisher pub_;
  float x, y, z, th;
  MoveBase _movebase;
  bool cancel_goal = true;

};
