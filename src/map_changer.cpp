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
                                        }


MapChanger::~MapChanger()
{
}

}  // namespace map_changer2
