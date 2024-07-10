#include "map_changer2/map_changer.hpp"

namespace map_changer2
{

MapChanger::MapChanger(const rclcpp::NodeOptions& options) : rclcpp::Node("map_changer", options)
{
    initial_pose_pub_ = this->create_publisher<geometry_msgs::msg::PoseWithCovarianceStamped>("/initialpose", 10);

    this->get_parameter("map_name", map_name_);
}

bool MapChanger::change_map_callback(const std::shared_ptr<std_srvs::srv::SetBool::Request> request,
                                        std::shared_ptr<std_srvs::srv::SetBool::Response> response)
{
    change_flag_ = true;
    count = request.data;

    return true;
}

bool MapChanger::read_yaml(){
    YAML::Node yaml_pass = YAML::LoadFile(map_name_);
    YAML::Node map_yaml;

    map_yaml = yaml_pass["map_list"];

    if(count >= map_name_.size()){
        exit(0);
    }else{
        map_id = map_yaml[count]["map"]["id"].as<int>();
        map_name = map_yaml[count]["map"]["map_name"].as<std::string>();
        pose_x = map_yaml[count]["map"]["pose_x"].as<double>();
        pose_y = map_yaml[count]["map"]["pose_y"].as<double>();
        orientation_z = map_yaml[count]["map"]["orientation_z"].as<double>();
        orientation_w = map_yaml[count]["map"]["orientation_w"].as<double>();
    }
    return true;
}


MapChanger::~MapChanger()
{
}

}  // namespace map_changer2
