# Custom Robot Simulation Project

## Overview

> This project involves a custom robot simulation in Gazebo, utilizing ROS 2. The robot model is defined using URDF and Xacro files, and the project includes a camera sensor for image processing.

![Project Structure Image](/images/rviz.png)

## Project Structure

The project is structured as follows:

- **Launch File**: `custom_robot_gazebo.launch.xml` - Main launch file to start the Gazebo simulation and RViz visualization.

- **Camera Subscriber**: `camera_subscriber.cpp` - C++ code to subscribe to the camera topic and process the images.
  ![Camera Structure Image](/images/camera.png)
  TODO

- **LiDAR Subscriber**: `lidar_subscriber.cpp `- C++ code to subscribe to the LiDAR topic and process the scanned data.

![gazebo.png](/images/gazebo.png)

## How to Run

### Prerequisites

- ROS 2 installed.
- Gazebo installed.
- Custom robot packages (`custom_robot_description`, `custom_robot_bringup`) correctly set up.

### Steps

1. **Build the Workspace**:

   ```sh
   colcon build
   ```

2. **Source the Setup Files:**:
   ```sh
   source install/setup.bash
   ```
3. **Launch the Simulation:**:
   ```sh
   ros2 launch custom_robot_gazebo.launch.xml
   ```
4. **Run the Camera Subscriber Node:**:
   ```sh
   ros2 run custom_package camera_subscriber
   ```

## Purpose

> The primary goal of this project is to simulate a custom robot in Gazebo, visualize it in RViz, and process camera images for various applications. This setup can be extended to include more sensors and advanced functionalities.

## Future Works

>

1.  Add more sensors to the robot model.
2.  Implement advanced image processing algorithms.
3.  Integrate with other ROS 2 packages for extended functionality.
4.  Implement Lidar Sensor Subscriber Node

## Notes

Ensure the paths in the launch file are correctly set according to your workspace setup.
Modify the camera_subscriber.cpp file to include your image processing code.

This README provides an overview and instructions to get started with the custom robot simulation project in ROS 2.
