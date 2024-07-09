#ifndef MAP_CHANGER2__MAP_CHANGER_HPP_
#define MAP_CHANGER2__MAP_CHANGER_HPP_

#include "map_changer2/visibility_control.h"

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/bool.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/float32.hpp"
#include "std_msgs/msg/int8.hpp"
#include "nav_msgs/srv/load_map.hpp"


namespace map_changer2
{

class MapChanger : public rclcpp::Node
{
public:
  MapChanger();

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
  rclcpp::Client<nav_msgs::srv::LoadMap>::SharedPtr change_map_;


  bool change_flag_;
  int map_id;
};

}  // namespace map_changer2

#endif  // MAP_CHANGER2__MAP_CHANGER_HPP_
