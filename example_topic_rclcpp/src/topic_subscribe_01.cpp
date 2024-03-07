#include "rclcpp/rclcpp.hpp"

class TopicSubscribe01 : public rclcpp::Node
{ 
public:
    TopicSubscribe01(std::string name):Node(name){
        RCLCPP_INFO(this->get_logger(),"大家好，我是%s.",name.c_str());

    }
    private:
    //声明节点
};
int main(int argc,char **argv){
    rclcpp::init(argc,argv);
    auto node = std::make_shared<TopicSubscribe01>("topic_subscribe_01");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
