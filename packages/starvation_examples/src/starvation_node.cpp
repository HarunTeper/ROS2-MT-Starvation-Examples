#include "starvation_examples/starvation.hpp"

StarvationNode::StarvationNode() : rclcpp::Node("starvation_node") {
  RCLCPP_INFO(this->get_logger(), "Starvation Node Startup");

  // get the parameter example_number
  this->declare_parameter("example_number", 0);
  example_number_ = this->get_parameter("example_number").as_int();

  // create callback groups
  callback_group_one_ =
      this->create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
  callback_group_two_ =
      this->create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
  callback_group_three_ =
      this->create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);

  RCLCPP_INFO(this->get_logger(), "Example Number: %d", example_number_);

  // create timers based on example number
  if (example_number_ == 4) {
    // create three timers
    // timer one, 1000ms period, 1000ms wcet, callback group one
    // timer two, 1000ms period, 500ms wcet, callback group one
    // timer three, 1000ms period, 500ms wcet, callback group two

    RCLCPP_INFO(this->get_logger(), "Timer 2 should never be executed");

    timer_one_ = this->create_wall_timer(
        std::chrono::milliseconds(1000),
        [this]() { this->timer_callback(1, 1000); }, callback_group_one_);

    timer_two_ = this->create_wall_timer(
        std::chrono::milliseconds(1000),
        [this]() { this->timer_callback(2, 500); }, callback_group_one_);

    timer_three_ = this->create_wall_timer(
        std::chrono::milliseconds(1000),
        [this]() { this->timer_callback(3, 500); }, callback_group_two_);
  } else if (example_number_ == 5) {
    // create four timers
    // timer one, 1000ms period, 500ms wcet, callback group one
    // timer two, 1000ms period, 500ms wcet, callback group two
    // timer three, 1000ms period, 500ms wcet, callback group three
    // timer four, 1000ms period, 1ms wcet, callback group three

    RCLCPP_INFO(this->get_logger(), "Timer 4 should never be executed");

    timer_one_ = this->create_wall_timer(
        std::chrono::milliseconds(1000),
        [this]() { this->timer_callback(1, 500); }, callback_group_one_);
    timer_two_ = this->create_wall_timer(
        std::chrono::milliseconds(1000),
        [this]() { this->timer_callback(2, 500); }, callback_group_two_);
    timer_three_ = this->create_wall_timer(
        std::chrono::milliseconds(1000),
        [this]() { this->timer_callback(3, 500); }, callback_group_three_);
    timer_four_ = this->create_wall_timer(
        std::chrono::milliseconds(1000),
        [this]() { this->timer_callback(4, 1); }, callback_group_three_);
  } else if (example_number_ == 6) {
    // create four timers
    // timer one, 1000ms period, 333ms wcet, callback group one
    // timer two, 1000ms period, 333ms wcet, callback group two
    // timer three, 666ms period, 333ms wcet, callback group three
    // timer four, 5000ms period, 1ms wcet, callback group three

    RCLCPP_INFO(this->get_logger(), "Timer 4 should never be executed");

    timer_one_ = this->create_wall_timer(
        std::chrono::milliseconds(1000),
        [this]() { this->timer_callback(1, 333); }, callback_group_one_);
    timer_two_ = this->create_wall_timer(
        std::chrono::milliseconds(1000),
        [this]() { this->timer_callback(2, 333); }, callback_group_two_);
    timer_three_ = this->create_wall_timer(
        std::chrono::milliseconds(500),
        [this]() { this->timer_callback(3, 334); }, callback_group_three_);
    timer_four_ = this->create_wall_timer(
        std::chrono::milliseconds(5000),
        [this]() { this->timer_callback(4, 1); }, callback_group_three_);
  } else {
    RCLCPP_INFO(this->get_logger(), "Invalid example number");
  }

  RCLCPP_INFO(this->get_logger(), "Starvation Node Ready");
  RCLCPP_INFO(this->get_logger(), "Starting execution");
}

void StarvationNode::timer_callback(int timer_id, int wcet_ms) {
  RCLCPP_INFO(this->get_logger(), "Timer %d executes", timer_id);
  auto start_time = std::chrono::steady_clock::now();
  while (std::chrono::duration_cast<std::chrono::milliseconds>(
             std::chrono::steady_clock::now() - start_time)
             .count() < wcet_ms) {
    // busy wait
  }
}