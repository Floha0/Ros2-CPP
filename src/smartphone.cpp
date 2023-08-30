#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"

class SmartPhone : public rclcpp::Node
{
public:
    SmartPhone() : Node("smartphone")
    {
        subscriber_ = this->create_subscription<example_interfaces::msg::String>("radio", 10,     // create subscriber that takes data from radio named publisher
            std::bind(&SmartPhone::callbackRobotNews, this, std::placeholders::_1));         // third is func. parameter        1 is 1 parameter (if 2 then 2)
        
        RCLCPP_INFO(this->get_logger(), "Smartphone Has Started");
    }

private:
    void callbackRobotNews(const example_interfaces::msg::String::SharedPtr msg)
    {
        RCLCPP_INFO(this->get_logger(), "%s", msg->data.c_str());       // Print message that has taken from publisher
    }

    rclcpp::Subscription<example_interfaces::msg::String>::SharedPtr subscriber_;       // Declare subscriber variable
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);       // initilize ROS

    auto node = std::make_shared<SmartPhone>();

    rclcpp::spin(node);
    
    rclcpp::shutdown();

    return 0;
}