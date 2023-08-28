#include "rclcpp/rclcpp.hpp"

class MyNode : public rclcpp::Node
{
public:
    MyNode() : Node("cpp_test")
    {
        RCLCPP_INFO(this->get_logger(), "Welcome to Node");

        timer_ = this->create_wall_timer(std::chrono::seconds(1),
                                         std::bind(&MyNode::timerCallback, this));
    }

private:
    void timerCallback()
    {
        RCLCPP_INFO(this->get_logger(), "Welcome");
    }

    rclcpp::TimerBase::SharedPtr timer_;
}; 

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);       // initilize ROS

    auto node = std::make_shared<MyNode>();   // create node

    rclcpp::spin(node);      // spin node

    rclcpp::shutdown();     // shutdown ROS
    return 0;
}