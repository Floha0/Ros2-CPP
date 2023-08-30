#include "rclcpp/rclcpp.hpp"

class MyNode : public rclcpp::Node
{
public:
    MyNode() : Node("cpp_test"), counter_(0)        // initialize
    {
        RCLCPP_INFO(this->get_logger(), "Welcome to Node");

        timer_ = this->create_wall_timer(std::chrono::seconds(1),
                                         std::bind(&MyNode::timerCallback, this));
    }
    
private:
    void timerCallback()
    {
        counter_++;
        RCLCPP_INFO(this->get_logger(), "Welcome %d", counter_);
    }

    rclcpp::TimerBase::SharedPtr timer_;
    int counter_;       // declare
}; 

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);       // initilize ROS

    auto node = std::make_shared<MyNode>();   // create node

    rclcpp::spin(node);      // spin node

    rclcpp::shutdown();     // shutdown ROS
    return 0;
}