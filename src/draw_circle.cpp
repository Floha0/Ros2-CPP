#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"


class DrawCircle : public rclcpp::Node
{
public:
    DrawCircle() : Node("draw_circle")
    {
        RCLCPP_INFO(this->get_logger(), "Rotator Has Started!");

        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("turtle1/cmd_vel", 10);

        timer_ = this->create_wall_timer(std::chrono::milliseconds(500),
                                         std::bind(&DrawCircle::rotator, this));
  
        auto msg = geometry_msgs::msg::Twist();

        msg.linear.y = -2;
        
        publisher_->publish(msg);   
    }

private:
    void rotator()
    {
        auto msg = geometry_msgs::msg::Twist();

        msg.linear.x = 1;
        msg.angular.z = 1;

        publisher_->publish(msg);   
    }

    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    auto node = std::make_shared<DrawCircle>();

    rclcpp::spin(node);
    
    rclcpp::shutdown();

    return 0;
}