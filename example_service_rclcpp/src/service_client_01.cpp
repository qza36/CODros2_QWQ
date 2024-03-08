#include "rclcpp/rclcpp.hpp"

class ServiceClient01 : public rclcpp::Node
{
    public:
    ServiceClient01(std::string name):Node(name){
        RCLCPP_INFO(this->get_logger(),"节点已经启动：%s",name.c_str());

    }
    private:
};
int main(int argc,char **argv){
    rclcpp::init(argc,argv);
    auto node = std::make_shared<ServiceClient01>("service_client_01");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}