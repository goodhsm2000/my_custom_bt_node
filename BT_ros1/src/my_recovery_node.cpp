#include <string>
#include "my_recovery_node.hpp"

MyRecoveryNode::MyRecoveryNode(
  const std::string & name,
  const BT::NodeConfiguration & conf)
: BT::ControlNode::ControlNode(name, conf),
  current_child_idx_(0)
{
}

BT::NodeStatus MyRecoveryNode::tick()
{
  const unsigned children_count = children_nodes_.size();

  if (children_count != 2) {
    throw BT::BehaviorTreeException("Recovery Node '" + name() + "' must only have 2 children.");
  }

  setStatus(BT::NodeStatus::RUNNING);

  while (current_child_idx_ < children_count) {
    TreeNode * child_node = children_nodes_[current_child_idx_];
    const BT::NodeStatus child_status = child_node->executeTick();

    if (current_child_idx_ == 0) {
      switch (child_status) {
        case BT::NodeStatus::SUCCESS:
          {
            halt();
            return BT::NodeStatus::SUCCESS;
          }

        case BT::NodeStatus::FAILURE:
          {
            // tick second child
            current_child_idx_++;
            break;
          }

        case BT::NodeStatus::RUNNING:
          {
            return BT::NodeStatus::RUNNING;
          }

        default:
          {
            halt();
            return BT::NodeStatus::FAILURE;
          }
      }  // end switch

    } else if (current_child_idx_ == 1) {
      switch (child_status) {
        case BT::NodeStatus::SUCCESS:
          {
            current_child_idx_--;
            ControlNode::haltChildren();
          }
          break;

        case BT::NodeStatus::FAILURE:
          {
            current_child_idx_--;
            halt();
            return BT::NodeStatus::FAILURE;
          }

        case BT::NodeStatus::RUNNING:
          {
            return BT::NodeStatus::RUNNING;
          }

        default:
          {
            halt();
            return BT::NodeStatus::FAILURE;
          }
      }  // end switch
    }
  }  // end while loop

  halt();
  return BT::NodeStatus::FAILURE;
}

void MyRecoveryNode::halt()
{
  ControlNode::halt();
  current_child_idx_ = 0;
}

