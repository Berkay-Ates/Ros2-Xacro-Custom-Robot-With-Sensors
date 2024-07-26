#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"
#include <fstream>
#include <iostream>

class LidarSubscriber : public rclcpp ::Node // MODIFY NAME
{
public:
    LidarSubscriber() : Node("lidar_subscriber_node") // MODIFY NAME
    {
        lidar_subscriber_ = this->create_subscription<sensor_msgs::msg::LaserScan>("/scan/out",
                                                                                   10, std ::bind(&LidarSubscriber ::callbackLidarData, this, std ::placeholders ::_1));
        RCLCPP_INFO(this->get_logger(),
                    "LidarSubscriber has been started ");
    }

private:
    void callbackLidarData(const sensor_msgs::msg::LaserScan::SharedPtr msg)
    {
        int i = 0;
        std::vector<float> intensity = msg->intensities;
        std::vector<float> ranges = msg->ranges;

        std::ofstream file;

        // Write ranges to file
        file.open("range.txt", std::ios_base::app);
        if (file.is_open())
        {
            for (i=0;i< (int) ranges.size();i++)
            {
                file << ranges.at(i) << " ";
            }
            file << std::endl<<"\n";
            file.close();
        }
        else
        {
            RCLCPP_WARN(this->get_logger(), "Unable to open /data/range.txt file, error: %s", std::strerror(errno));
        }

        // Write intensities to file
        file.open("intensity.txt", std::ios_base::app);
        if (file.is_open())
        {
            for (i=0;i< (int) intensity.size();i++)
            {
                file << intensity.at(i) << " ";
            }
    
            file << std::endl<<"\n";
            file.close();
        }
        else
        {
            RCLCPP_WARN(this->get_logger(), "Unable to open /data/intensity.txt file, error: %s", std::strerror(errno));
        }
    }

    rclcpp ::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr lidar_subscriber_;
};
int main(int argc, char **argv)
{
    rclcpp ::init(argc, argv);
    auto node = std ::make_shared<LidarSubscriber>(); // MODIFY NAME
    rclcpp ::spin(node);
    rclcpp ::shutdown();
    return 0;
}