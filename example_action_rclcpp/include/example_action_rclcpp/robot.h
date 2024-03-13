/*
copyright
*/
#ifndef EXAMPLE_ACTIONI_RCLCPP_ROBOT_H_
#define EXAMPLE_ACTIONI_RCLCPP_ROBOT_H_
#include "rclcpp/rclcpp.hpp"
#include "robot_control_interfaces/action/move_robot.hpp"

class Robot {
 public:
    using MoveRobot = robot_control_interfaces::action::MoveRobor;
    Robot() = default;
    ~Robot() = default;
    float move_step();//移动机器人
    bool set_goal(float goal);//移动一段距离
    float get_current_pose();//获得当前位置
    int get_status();//获得机器人状态
    bool close_goal();//是否接近目标
    void stop_move();//停止移动


 private:
    float current_pose_ = 0.0;//声明当前位置
    float target_pose_ = 0.0;//声明目标位置
    float move_distance = 0.0;//声明移动距离
    std::atomic<bool>= cancel_flag_{false};//取消标志
    int status_ = MoveRobot::Feedback::STATUS_STOP;//声明机器人状态
};

#endif  // EXAMPLE_ACTIONI_RCLCPP_ROBOT_H_