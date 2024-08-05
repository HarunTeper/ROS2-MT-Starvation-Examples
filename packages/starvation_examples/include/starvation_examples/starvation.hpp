#include <rclcpp/rclcpp.hpp>

class StarvationNode : public rclcpp::Node {
 public:
  StarvationNode();
  ~StarvationNode() = default;

 private:
  rclcpp::TimerBase::SharedPtr timer_one_;
  rclcpp::TimerBase::SharedPtr timer_two_;
  rclcpp::TimerBase::SharedPtr timer_three_;
  rclcpp::TimerBase::SharedPtr timer_four_;

  rclcpp::CallbackGroup::SharedPtr callback_group_one_;
  rclcpp::CallbackGroup::SharedPtr callback_group_two_;
  rclcpp::CallbackGroup::SharedPtr callback_group_three_;

  int example_number_;
  void timer_callback(int timer_id, int wcet_ms);
};