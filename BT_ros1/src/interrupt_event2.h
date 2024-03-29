#pragma once

#include <behaviortree_cpp_v3/action_node.h>
#include "std_msgs/String.h"

// static std::string interrupt_event2;

class InterruptEvent2 : public BT::SyncActionNode
{
    public:
        InterruptEvent2(const std::string& name, const BT::NodeConfiguration& config)
            : BT::SyncActionNode(name, config)
        {
            sub_ = node_.subscribe("interrupt_event2", 1, &InterruptEvent2::interruptCallback2, this);
        }
        ~InterruptEvent2() override = default; 

        static BT::PortsList providedPorts()
        {
            return{ BT::InputPort<std::string>("event") };
        }

        virtual BT::NodeStatus tick() override
        {   
            ros::spinOnce();

            std::string expect_event;

            //printf("Checking interrupt....\n");
            if (!getInput<std::string>("event", expect_event)) {
                throw BT::RuntimeError("missing required input [event]");
            }

            printf("%s\n", expect_event.c_str());

            if (interrupt_event2 == expect_event) {
                interrupt_event2 = expect_event;
                return BT::NodeStatus::SUCCESS;
            }
            else
                return BT::NodeStatus::FAILURE;

        }

    private:
        ros::NodeHandle node_;
        ros::Subscriber sub_;
        std::string interrupt_event2;
        void interruptCallback2(const std_msgs::String::ConstPtr& msg)
        {
            printf("interrupt callback detect event2: %s\n", msg->data.c_str());
            interrupt_event2 = msg->data;
        }
};
