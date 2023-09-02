#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "turtlesim/msg/pose.hpp"
#include<cmath>


class FindDistance : public rclcpp::Node
{
public:
    FindDistance() : Node("find_distance"), targetPosx(10.0), targetPosy(10.0)      // Define target poses
    {
        RCLCPP_INFO(this->get_logger(), "Rotator Has Started!");

        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("turtle1/cmd_vel", 10);
        
        subscriber_ = this->create_subscription<turtlesim::msg::Pose>("/turtle1/pose", 10,
            std::bind(&FindDistance::CalculateDistance, this, std::placeholders::_1));


        timer_ = this->create_wall_timer(std::chrono::milliseconds(500),
                                         std::bind(&FindDistance::rotator, this));
    }

private:
    void rotator()
    {
        auto msg = geometry_msgs::msg::Twist();

        if (!startBottom)
        {
            // Start from 2 unity bottom
            msg.linear.y = -2;
            startBottom = true;
        }
        else
        {
            msg.linear.x = 1;
            msg.angular.z = 1;
        }

        publisher_->publish(msg);
    }

    void CalculateDistance(const turtlesim::msg::Pose::SharedPtr pose)
    {
        posx = pose->x;         // get x position
        posy = pose->y;         // get y position

        float r = sqrt(pow(posx - defPosx, 2) + pow(posy - defPosy, 2));        // distance to center
        float d = sqrt(pow(posx - targetPosx, 2) + pow(posy - targetPosy, 2));      // distance to target

        RCLCPP_INFO(this->get_logger(), "\n Distance to center: %f \n Distance to target: %f", r, d);

        // Pythagorean theorem (assuming angle is 90) (a2 + b2 = c2)
        float x = sqrt(pow(r, 2) + pow(d, 2));
        
        RCLCPP_INFO(get_logger(), "\nDistance between center and target is: %f", x);


        // Setting the target's position 2 unit away from turtle
        targetPosx = (posy - 5.544445) * targetDistance + posx;
        targetPosy = (posx - 5.544445) * targetDistance + posy;
        
        RCLCPP_INFO(get_logger(), "\ntarget pos x: %f || y: %f", targetPosx, targetPosy);
    }


    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr subscriber_;
    rclcpp::TimerBase::SharedPtr timer_;

    bool startBottom;

    float posx, posy, targetPosx, targetPosy;
    float defPosx = 5.544445;
    float defPosy = 5.544445;

    float targetDistance = 2;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    auto node = std::make_shared<FindDistance>();

    rclcpp::spin(node);
    
    rclcpp::shutdown();

    return 0;
}