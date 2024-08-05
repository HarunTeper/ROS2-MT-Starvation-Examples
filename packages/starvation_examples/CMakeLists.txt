cmake_minimum_required(VERSION 3.5)
project(starvation_examples)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(ament_cmake_python REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclpy REQUIRED)

# Include Cpp "include" directory
include_directories(include)

set(starvation_dependencies "rclcpp")

# Add libraries
add_library(starvation_examples_node SHARED src/starvation_node.cpp)
ament_target_dependencies(starvation_examples_node ${starvation_dependencies})

# Create Cpp executable
add_executable(starvation_examples src/starvation_main.cpp)

# Link libraries
target_link_libraries(starvation_examples starvation_examples_node)

# Install Cpp executables
install(TARGETS
  starvation_examples
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}/
)

ament_package()
