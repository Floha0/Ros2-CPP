cmake_minimum_required(VERSION 3.8)
project(my_cpp_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(example_interfaces REQUIRED)
find_package(turtlesim REQUIRED)
find_package(geometry_msgs REQUIRED)

add_executable(cpp_node src/my_first_node.cpp)    
ament_target_dependencies(cpp_node rclcpp)       

add_executable(radio src/radio.cpp)
ament_target_dependencies(radio rclcpp example_interfaces)

add_executable(smartphone src/smartphone.cpp)
ament_target_dependencies(smartphone rclcpp example_interfaces)

add_executable(find_distance src/find_distance.cpp)
ament_target_dependencies(find_distance rclcpp geometry_msgs turtlesim)

install (TARGETS
  cpp_node
  radio
  smartphone
  find_distance
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
