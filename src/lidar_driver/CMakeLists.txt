cmake_minimum_required(VERSION 3.8)
project(lidar_driver)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)

add_executable(lidar_subscriber_node src/lidar_subscriber.cpp)

ament_target_dependencies(lidar_subscriber_node rclcpp sensor_msgs)


install(TARGETS
  lidar_subscriber_node
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
