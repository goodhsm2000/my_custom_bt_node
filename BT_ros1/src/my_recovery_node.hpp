// Made by HSM

#ifndef NAV2_BEHAVIOR_TREE__PLUGINS__CONTROL__MY_RECOVERY_NODE_HPP_
#define NAV2_BEHAVIOR_TREE__PLUGINS__CONTROL__MY_RECOVERY_NODE_HPP_

#include <string>
#include "behaviortree_cpp_v3/control_node.h"

class MyRecoveryNode : public BT::ControlNode
{
public:
  MyRecoveryNode(
    const std::string & name,
    const BT::NodeConfiguration & conf);

  ~MyRecoveryNode() override = default;

  // retry 횟수를 없애는 recovery node => 무조건 success로 
  static BT::PortsList providedPorts()
  {
    return {};
  }

private:
  unsigned int current_child_idx_;

  BT::NodeStatus tick() override;
  void halt() override;
};

#endif  // NAV2_BEHAVIOR_TREE__PLUGINS__CONTROL__MY_RECOVERY_NODE_HPP_
