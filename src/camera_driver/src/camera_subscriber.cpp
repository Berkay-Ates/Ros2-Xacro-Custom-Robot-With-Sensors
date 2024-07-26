#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>

class ImageSubscriber : public rclcpp::Node
{
public:
    ImageSubscriber()
        : Node("camera_subscriber_node")
    {
        image_subscriber = this->create_subscription<sensor_msgs::msg::Image>("/camera_sensor/image_raw", 10,
                                                                              std::bind(&ImageSubscriber::imageCallback, this, std::placeholders::_1));
    }

private:
    void imageCallback(const sensor_msgs::msg::Image::ConstSharedPtr &msg)
    {
        try
        {

            cv::Mat image = cv_bridge::toCvCopy(msg, "bgr8")->image;
            // Görüntü işleme kodu buraya
            int height = msg->height;
            int width = msg->width;
            std::vector<unsigned char> data = msg->data;

            RCLCPP_ERROR(this->get_logger(), " %zu ", sizeof(data[0]));
            RCLCPP_INFO(this->get_logger(), " %zu ", data.size());
            RCLCPP_INFO(this->get_logger(), " %zu ", data.size() * sizeof(data[0]));

            RCLCPP_WARN(this->get_logger(), "height_of_image: %d, width_of_image:%d", height, width);
            cv::imshow("Camera Image", image);
            cv::waitKey(1);
        }
        catch (cv_bridge::Exception &e)
        {
            RCLCPP_ERROR(this->get_logger(), "cv_bridge exception: %s", e.what());
            return;
        }
    }

    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr image_subscriber;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ImageSubscriber>());
    rclcpp::shutdown();
    return 0;
}
