#include "rclcpp/rclcpp.hpp"
#include "example_ros2_interfaces/srv/move_robot.hpp"
#include "example_ros2_interfaces/msg/robot_status.hpp"

class Robot{
  public:
  Robot()= default;
  ~Robot()= default;
  float move_distance(float distance){
    status_ = example_ros2_interfaces::msg::RobotStatus::STATUS_MOVEING;
    target_pose_ += distance;
    // 当目标距离大于0.1,则持续向目标移动
    while(fabs(target_pose_ - current_pose_) > 0.1){
      //每一步移动当前到目标距离的1/10
      float step = distance / fabs(distance) * fabs(target_pose_ - current_pose_) * 0.1;
      current_pose_ += step;
      std::cout << "移动了" << step << "当前位置：" << current_pose_ << std::endl;
      //当前线程休眠500ms
      std::this_thread::sleep_for(std::chrono::milliseconds(500));

    }
    status_ = example_ros2_interfaces::msg::RobotStatus::STATUS_STOP;
    return current_pose_;
  }

  float get_current_pose(){
    return current_pose_;}
  int get_status(){
    return status_;
    }
  private:
  //声明当前位置
  float current_pose_ = 0.0;
  //声明目标位置
  float target_pose_ = 0.0;
  int status_ = example_ros2_interfaces::msg::RobotStatus::STATUS_STOP;
};
//机器人节点逻辑
class ExampleInterfacesRobot : public rclcpp::Node{
  public:
  ExampleInterfacesRobot(std::string name) : Node(name){
    RCLCPP_INFO(this->get_logger(),"节点已经启动：%s",name.c_str());
    //创建move_robot服务
    move_robot_server_ = this->create_service<example_ros2_interfaces::srv::MoveRobot>(
      "move_robot",std::bind(&ExampleInterfacesRobot::handle_move_robot,this,std::placeholders::_1,std::placeholders::_2));
    //创建发布者
    robot_status_publisher_ = this->create_publisher<example_ros2_interfaces::msg::RobotStatus>("robot_status",10);

    //创建一个周期为500ms的定时器
    timer_ = this->create_wall_timer(std::chrono::milliseconds(500),std::bind(&ExampleInterfacesRobot::timer_callback,this));


  }
  private:
  //实例化机器人
  Robot robot;
  rclcpp::TimerBase::SharedPtr timer_;//定时器，用于发布机器人位置
  rclcpp::Service<example_ros2_interfaces::srv::MoveRobot>::SharedPtr move_robot_server_;//移动机器人服务
  rclcpp::Publisher<example_ros2_interfaces::msg::RobotStatus>::SharedPtr robot_status_publisher_;//发布机器人状态发布者
   /**
   * @brief 500ms 定时回调函数，
   * 
   */
  void timer_callback(){
     example_ros2_interfaces::msg::RobotStatus message;
    message.status = robot.get_status();
    message.pose = robot.get_current_pose();
    RCLCPP_INFO(this->get_logger(),"发布机器人状态: %d,位置: %f",robot.get_current_pose());
    robot_status_publisher_->publish(message);
  };
  /**
   * @brief 收到话题数据的回调函数
   * 
   * @param request 请求共享指针，包含移动距离
   * @param response 响应的共享指针，包含当前位置信息
   */
  void handle_move_robot(const std::shared_ptr<example_ros2_interfaces::srv::MoveRobot::Request> request,std::shared_ptr<example_ros2_interfaces::srv::MoveRobot::Response> response){
    RCLCPP_INFO(this->get_logger(),"收到请求移动距离：%f",request->distance,robot.get_current_pose());
    robot.move_distance(request->distance);
    response->pose = robot.get_current_pose();
  };

};
int main(int argc, char** argv) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<ExampleInterfacesRobot>("example_interfaces_robot_01");
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
