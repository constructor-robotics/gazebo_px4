#include <rclcpp/rclcpp.hpp>
#include <gz/transport/Node.hh>
#include <gz/msgs/Pose.hh>
#include <geometry_msgs/msg/pose_stamped.hpp>

class MyBridge : public rclcpp::Node {
public:
    MyBridge() : Node("my_custom_bridge") {
        // Initialize Gazebo transport node
        gz_node_ = std::make_unique<gz::transport::Node>();

        // Start the transport thread to process messages
        transport_thread_ = std::thread([this]() {
          gz_node_->Run();
        });
        transport_thread_.detach();

        // Subscribe to a Gazebo topic (e.g., /model/robot_name/pose)
        gz_node_->Subscribe("/model/robot_name/pose", &MyBridge::gazeboCallback, this);

        // Create a ROS publisher
        ros_pub_ = this->create_publisher<geometry_msgs::msg::PoseStamped>("my_pose_topic", 10);
    }

private:
    void gazeboCallback(const gz::msgs::Pose& msg) {
        auto ros_msg = std::make_shared<geometry_msgs::msg::PoseStamped>();
        ros_msg->header.stamp = this->get_clock()->now();

        // Convert Gazebo Pose to ROS PoseStamped
        ros_msg->pose.position.x = msg.position().x();
        ros_msg->pose.position.y = msg.position().y();
        ros_msg->pose.position.z = msg.position().z();

        ros_msg->pose.orientation.w = msg.orientation().w();
        ros_msg->pose.orientation.x = msg.orientation().x();
        ros_msg->pose.orientation.y = msg.orientation().y();
        ros_msg->pose.orientation.z = msg.orientation().z();

        // Publish the ROS message
        ros_pub_->publish(*ros_msg);
    }

    std::unique_ptr<gz::transport::Node> gz_node_;
    rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr ros_pub_;
    std::thread transport_thread_;
};

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MyBridge>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
