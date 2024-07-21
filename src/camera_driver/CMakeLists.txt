cmake_minimum_required(VERSION 3.8)
project(camera_driver)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(image_transport REQUIRED)

find_package(cv_bridge REQUIRED)
find_package(OpenCV REQUIRED)

add_executable(camera_subscriber src/camera_subscriber.cpp)

# Specify include directories
include_directories(${OpenCV_INCLUDE_DIRS})

# Specify libraries to link against
target_link_libraries(camera_subscriber ${OpenCV_LIBS})

# Specify ament dependencies
ament_target_dependencies(camera_subscriber rclcpp sensor_msgs cv_bridge)

ament_target_dependencies(camera_subscriber rclcpp sensor_msgs image_transport cv_bridge)


install(TARGETS
  camera_subscriber
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
