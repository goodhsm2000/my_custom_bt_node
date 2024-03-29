#pragma once

#include <behaviortree_cpp_v3/condition_node.h>
#include "std_msgs/String.h"
#include <mutex>

// 얘 때매 계속 에러 생김
// static std::string interrupt_event;

class InterruptEvent : public BT::ConditionNode
{
    public:
        InterruptEvent(const std::string& name, const BT::NodeConfiguration& config)
            : BT::ConditionNode(name, config)
        {
            sub_ = node_.subscribe("interrupt_event", 1, &InterruptEvent::interruptCallback, this);
        }
        ~InterruptEvent() override = default;


        static BT::PortsList providedPorts()
        {
            return{ BT::InputPort<std::string>("event") };
        }
        
        virtual BT::NodeStatus tick() override
        {   
            ros::spinOnce();
            
            // 얘 때매 계속 에러 생김
            // interrupt_event = "";

            std::string expect_event;

            //printf("Checking interrupt....\n");
            if (!getInput<std::string>("event", expect_event)) {
                throw BT::RuntimeError("missing required input [event]");
            }

            printf("%s\n", expect_event.c_str());

            std::lock_guard<std::mutex> lock(mutex_);
            if (interrupt_event == expect_event)
            {
                // interrupt_event = expect_event;
                return BT::NodeStatus::FAILURE;
            }
            else
                return BT::NodeStatus::SUCCESS;


        }

    private:
        ros::NodeHandle node_;
        ros::Subscriber sub_;
        std::mutex mutex_;
        std::string interrupt_event = "None";
        void interruptCallback(const std_msgs::String::ConstPtr& msg)
        {   
            std::lock_guard<std::mutex> lock(mutex_);
            printf("interrupt callback detect event: %s\n", msg->data.c_str());
            interrupt_event = msg->data;
        }
};

