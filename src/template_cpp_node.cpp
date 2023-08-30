#include "rclcpp/rclcpp.hpp"

class MyCustomNode : public rclcpp::Node
{
public:
    MyCustomNode() : Node("node_name")
    {

        RCLCPP_INFO(this->get_logger(), "Node Has Started");
    }

private:
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);       // initilize ROS

    auto node = std::make_shared<MyCustomNode>();

    rclcpp::spin(node);
    
    rclcpp::shutdown();

    return 0;
}