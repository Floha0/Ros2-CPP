#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"

class Radio : public rclcpp::Node
{
public:
    Radio() : Node("radio"), name_("Turtle")
    {
        publisher_ = this->create_publisher<example_interfaces::msg::String>("radio", 10);        // create publisher with radio name
        
        timer_ = this->create_wall_timer(std::chrono::milliseconds(500),
                                         std::bind(&Radio::publishMsg, this));         // create timer for callback

        RCLCPP_INFO(this->get_logger(), "Radio has started");
    }

private:
    void publishMsg()
    {
        auto msg = example_interfaces::msg::String();           // msg type
        msg.data = std::string("I'm controlling" + name_);          // message 
        publisher_->publish(msg);           // publish msg
    }

    std::string name_;
    rclcpp::Publisher<example_interfaces::msg::String>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;

};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);       // initilize ROS

    auto node = std::make_shared<Radio>();

    rclcpp::spin(node);
    
    rclcpp::shutdown();

    return 0;
}