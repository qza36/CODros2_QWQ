#include <chrono>

#include "rclcpp/rclcpp.hpp"

class ParametersBasicNode : public rclcpp::Node
{
  public:
  explicit ParametersBasicNode(std::string name) : Node(name){
    RCLCPP_INFO(this->get_logger(),"节点已经启动：%s",name.c_str());

  }
  private:
};
int  main(int argc,char **argv){
  rclcpp::init(argc,argv);
  auto node = std::make_shared<ParametersBasicNode>("parameters_basic");
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}