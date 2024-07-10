#ifndef MAP_CHANGER2__MAP_CHANGER_HPP_
#define MAP_CHANGER2__MAP_CHANGER_HPP_

#include "map_changer2/visibility_control.h"

#include "rclcpp/rclcpp.hpp"

#include <std_msgs/String.h>
#include <std_srvs/srv/set_bool.hpp>
#include <nav2_msgs/srv/load_map.hpp>
#include <geometry_msgs/msg/pose_with_covariance_stamped.hpp>
#include <yaml-cpp/yaml.h>


namespace map_changer2
{

class MapChanger : public rclcpp::Node
{
public:
  explicit MapChanger(const rclcpp::NodeOptions& options = rclcpp::NodeOptions());

  virtual ~MapChanger();

private:
  bool read_yaml();
  void initial_pose_set(float pose_x, float pose_y, float ori_z, float ori_w);
  void call_map();
  bool change_map_callback(const std::shared_ptr<std_srvs::srv::SetBool::Request> request,
                            std::shared_ptr<std_srvs::srv::SetBool::Response> response);

  std::string map_name_;
  std::string map_pass_;

  rclcpp::Publisher<geometry_msgs::msg::PoseWithCovarianceStamped>::SharedPtr initial_pose_pub_;

  rclcpp::Service<std_srvs::srv::SetBool>::SharedPtr change_call_;
  rclcpp::Client<nav2_msgs::srv::LoadMap>::SharedPtr change_map_;


  bool change_flag_;
  int map_id;
  int count;
};

}  // namespace map_changer2

#endif  // MAP_CHANGER2__MAP_CHANGER_HPP_
