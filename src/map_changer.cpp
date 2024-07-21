#include "map_changer2/map_changer.hpp"

namespace map_changer2
{

MapChanger::MapChanger(const rclcpp::NodeOptions& options) : rclcpp::Node("map_changer", options)
{
    change_call_ = this->create_service<std_srvs::srv::SetBool>(
        "change_call", std::bind(&MapChanger::change_map_callback, this, std::placeholders::_1, std::placeholders::_2));
    change_map_ = this->create_client<nav2_msgs::srv::LoadMap>("change_map");

    initial_pose_pub_ = this->create_publisher<geometry_msgs::msg::PoseWithCovarianceStamped>("/initialpose", 10);

    this->get_parameter("map_name", map_name_);
}

bool MapChanger::change_map_callback(const std::shared_ptr<std_srvs::srv::SetBool::Request> request,
                                        std::shared_ptr<std_srvs::srv::SetBool::Response> response)
{
    change_flag_ = true;
    count = request->data;

    return true;
}

bool MapChanger::read_yaml(){
    YAML::Node yaml_pass = YAML::LoadFile(map_name_.data());
    YAML::Node map_yaml;

    map_yaml = yaml_pass["map_list"];

    if(count >= map_name_.size()){
        exit(0);
    }else{
        map_id = map_yaml[count]["map"]["id"].as<int>();
        map_name_ = map_yaml[count]["map"]["map_name_"].as<std::string>();
        pose_x = map_yaml[count]["map"]["pose_x"].as<double>();
        pose_y = map_yaml[count]["map"]["pose_y"].as<double>();
        orientation_z = map_yaml[count]["map"]["orientation_z"].as<double>();
        orientation_w = map_yaml[count]["map"]["orientation_w"].as<double>();
    }
    return true;
}

void MapChanger::initial_pose_set(double x, double y, double z, double w){
    geometry_msgs::msg::PoseWithCovarianceStamped pose_msg;
    pose_msg.header.stamp = this->get_clock()->now();
    pose_msg.header.frame_id = "map";
    pose_msg.pose.pose.position.x = x;
    pose_msg.pose.pose.position.y = y;
    pose_msg.pose.covariance[0] = 0.25;
    pose_msg.pose.covariance[6 * 1 + 1] = 0.25;
    pose_msg.pose.covariance[6 * 5 + 5] = 0.0685;
    pose_msg.pose.pose.orientation.z = z;
    pose_msg.pose.pose.orientation.z = w;

    initial_pose_pub_->publish(pose_msg);
}

void MapChanger::call_map(){
    if(change_flag_){
        read_yaml();
        initial_pose_set(pose_x, pose_y, orientation_z, orientation_w);

        change_flag_ = false;
        count++;
    }
}

}  // namespace map_changer2

int main(int argc, char** argv){
    rclcpp::init(argc, argv);
    rclcpp::NodeOptions options;

    auto node = std::make_shared<map_changer2::MapChanger>(options);
    bool read_result = node->read_yaml();

    if(!read_result){
        std::cerr << "read_yaml error" << std::endl;
        return 1;
    }else {
        rclcpp::spin(node);
        rclcpp::shutdown();
        return 0;
    }
}
