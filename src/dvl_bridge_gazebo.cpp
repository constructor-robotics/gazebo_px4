#include <rclcpp/rclcpp.hpp>
#include <gz/transport/Node.hh>
#include <gz/msgs/dvl_velocity_tracking.pb.h>

// #include <geometry_msgs/msg/pose_stamped.hpp>
#include <geometry_msgs/msg/twist_stamped.hpp>

class MyBridge : public rclcpp::Node {
public:
    MyBridge() : Node("my_custom_bridge") {
        // Initialize Gazebo transport node
        gz_node_ = std::make_unique<gz::transport::Node>();

        // Start the transport thread to process messages
        // transport_thread_ = std::thread([this]() {
        //   gz_node_->();
        // });
        // transport_thread_.detach();

        // Subscribe to a Gazebo topic (e.g., /model/robot_name/pose)
        gz_node_->Subscribe("/dvl/velocity", &MyBridge::gazeboCallback, this);

        // Create a ROS publisher
        ros_pub_ = this->create_publisher<geometry_msgs::msg::TwistStamped>("/dvl/velocity", 10);
    }

private:
    void gazeboCallback(const gz::msgs::DVLVelocityTracking& msg) {
        auto ros_msg = std::make_shared<geometry_msgs::msg::TwistStamped>();
        ros_msg->header.stamp = this->get_clock()->now();

        // Convert Gazebo Pose to ROS PoseStamped
        ros_msg->twist.linear.x = msg.velocity().mean().x();
        ros_msg->twist.linear.y = msg.velocity().mean().y();
        ros_msg->twist.linear.z = msg.velocity().mean().z();

        // Publish the ROS message
        ros_pub_->publish(*ros_msg);
    }

    std::unique_ptr<gz::transport::Node> gz_node_;
    rclcpp::Publisher<geometry_msgs::msg::TwistStamped>::SharedPtr ros_pub_;
    std::thread transport_thread_;
};

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MyBridge>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
