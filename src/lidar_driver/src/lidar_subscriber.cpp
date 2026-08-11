#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"
#include <cerrno>
#include <cstring>
#include <filesystem>
#include <fstream>

class LidarSubscriber : public rclcpp::Node
{
public:
    LidarSubscriber() : Node("lidar_subscriber_node")
    {
        this->declare_parameter<std::string>("scan_topic", "/scan");
        this->declare_parameter<std::string>("output_dir", "/tmp/lidar_driver_data");

        const std::string scan_topic = this->get_parameter("scan_topic").as_string();
        output_dir_ = this->get_parameter("output_dir").as_string();

        std::filesystem::create_directories(output_dir_);

        // Start each run with fresh files instead of appending forever across runs.
        range_file_.open(output_dir_ + "/range.txt", std::ios::trunc);
        intensity_file_.open(output_dir_ + "/intensity.txt", std::ios::trunc);
        if (!range_file_.is_open() || !intensity_file_.is_open())
        {
            RCLCPP_ERROR(this->get_logger(), "Unable to open output files under '%s': %s",
                         output_dir_.c_str(), std::strerror(errno));
        }

        lidar_subscriber_ = this->create_subscription<sensor_msgs::msg::LaserScan>(
            scan_topic, 10,
            std::bind(&LidarSubscriber::callbackLidarData, this, std::placeholders::_1));

        RCLCPP_INFO(this->get_logger(), "LidarSubscriber started: listening on '%s', writing to '%s'",
                    scan_topic.c_str(), output_dir_.c_str());
    }

    ~LidarSubscriber() override
    {
        range_file_.close();
        intensity_file_.close();
    }

private:
    static void writeRow(std::ofstream &file, const std::vector<float> &values)
    {
        if (!file.is_open())
        {
            return;
        }
        for (const float value : values)
        {
            file << value << " ";
        }
        file << "\n";
        file.flush();
    }

    void callbackLidarData(const sensor_msgs::msg::LaserScan::SharedPtr msg)
    {
        writeRow(range_file_, msg->ranges);
        writeRow(intensity_file_, msg->intensities);
    }

    rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr lidar_subscriber_;
    std::ofstream range_file_;
    std::ofstream intensity_file_;
    std::string output_dir_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<LidarSubscriber>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
