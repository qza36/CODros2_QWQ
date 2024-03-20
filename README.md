# ros学习代码
## 2024/3/11 完成自定义接口,阅读Qos指南ing...
## 2024/3/12 写参数,学动作
- 参数代码通过，但是执行<br><code>ros2 run example_parameters_rclcpp parameters_basic --ros-args -p rcl_log_level:=50</code><br>没有预期效果
## 2024/3/13 写动作代码
- 代码写完，编译失败
```
    Could not find a package configuration file provided by
  "robot_control_interfaces" with any of the following names:

    robot_control_interfacesConfig.cmake
    robot_control_interfaces-config.cmake

```
## 2024/3/20 安装miniconda与jupyer,实现jupyer与ros2通信