cmake_minimum_required(VERSION 3.8)
#SET(Trantor_DIR "/opt/ros/humble/share/example_interfaces/cmake")
project(example_ros2_interfaces)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(rclcpp REQUIRED)
find_package(example_ros2_interfaces REQUIRED)
rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/RobotPose.msg"
  "msg/RobotStatus.msg"
  "srv/MoveRobot.srv"
  DEPENDENCIES geometry_msgs
)
 add_executable(example_interfaces_robot_01 src/example_interfaces_robot_01.cpp)
 target_include_directories(example_interfaces_robot_01 PUBLIC
   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
   $<INSTALL_INTERFACE:include>)
 ament_target_dependencies(
   example_interfaces_robot_01
   "rclcpp"
   "example_ros2_interfaces"
 )
 install(TARGETS example_interfaces_robot_01
   DESTINATION lib/${PROJECT_NAME})
 
 add_executable(example_interfaces_control_01 src/example_interfaces_control_01.cpp)
 target_include_directories(example_interfaces_control_01 PUBLIC
   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
   $<INSTALL_INTERFACE:include>)
 ament_target_dependencies(
   example_interfaces_control_01
   "rclcpp"
   "example_ros2_interfaces"
 )
 install(TARGETS example_interfaces_control_01
   DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
