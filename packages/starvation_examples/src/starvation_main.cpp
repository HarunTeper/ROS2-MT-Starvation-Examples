#include "starvation_examples/starvation.hpp"

int main(int argc, char* argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::executors::MultiThreadedExecutor executor(rclcpp::ExecutorOptions(),
                                                    2);
  auto node = std::make_shared<StarvationNode>();
  executor.add_node(node);
  executor.spin();
  rclcpp::shutdown();
  return 0;
}