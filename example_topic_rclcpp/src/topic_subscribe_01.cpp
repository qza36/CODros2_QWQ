#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
class TopicSubscribe01 : public rclcpp::Node
{ 
public:
    TopicSubscribe01(std::string name):Node(name){
        RCLCPP_INFO(this->get_logger(),"大家好，我是%s.",name.c_str());
        //创建一个订阅者话题
        command_subscribe_ = this->create_subscription<std_msgs::msg::String>("command",10,std::bind(&TopicSubscribe01::command_callback,this,std::placeholders::_1));
    }
    private:
    //声明一个订阅者
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr command_subscribe_;
    //收到话题数据的回调函数
    void command_callback(const std_msgs::msg::String::SharedPtr msg){
        double speed = 0.0f;
        if(msg->data == "forward"){
            speed = 0.2f;
        }
        RCLCPP_INFO(this->get_logger(),"收到[%s]消息,发送速度为: %f",msg->data.c_str(),speed);
    }
};
int main(int argc,char **argv){
    rclcpp::init(argc,argv);
    auto node = std::make_shared<TopicSubscribe01>("topic_subscribe_01");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
