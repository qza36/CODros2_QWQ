#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp" //导入消息接口

class TopicPublisher01 : public rclcpp::Node
{
public:
    // 构造函数,有一个参数为节点名称
    TopicPublisher01(std::string name) : Node(name)
    {
        RCLCPP_INFO(this->get_logger(), "%s节点已经启动.", name.c_str());
        //创建发布者
        command_publisher_ = this->create_publisher<std_msgs::msg::String>("command", 10);
    }

private:
    void timer_callback(){
        // 创建一个消息
        std_msgs::msg::String message;
        message.data =  "Hello World!";
        //日志打印
        RCLCPP_INFO(this->get_logger(), "发布消息: '%s'", message.data.c_str());
        //发布消息
        command_publisher_->publish(message);
    }
    //声明定时器指针
    rclcpp::TimerBase::SharedPtr timer_;
    // 声明话题发布者
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr command_publisher_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    /*创建对应节点的共享指针对象*/
    auto node = std::make_shared<TopicPublisher01>("topic_publisher_01");
    /* 运行节点，并检测退出信号*/
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}