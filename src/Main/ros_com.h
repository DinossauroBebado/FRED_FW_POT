#include <ros.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Float32.h>
#include <geometry_msgs/Twist.h>

#include <Main/power.h>
#include <Main/led_strip.h>

// Subscribers ------------
#define cmd_wheels_topic "cmd_wheels"
#define cmd_right_wheel_topic "cmd_right_wheel"
#define cmd_vel_topic "cmd_vel"
#define cmd_led_strip_topic "cmd/led_strip/color"

//Publisher 
#define pwm_right_topic "power/status/pwm/right"
#define pwm_left_topic "power/status/pwm/left"

#define angular_speed_right_topic "power/status/speed/angular/right"
#define angular_speed_left_topic "power/status/speed/angular/left"

#define rpm_speed_right_topic "power/status/speed/rpm/right"
#define rpm_speed_left_topic "power/status/speed/rpm/left"

ros::NodeHandle  nh;

//------------------SUBS--------------------
//locomotion 
ros::Subscriber<geometry_msgs::Twist> subCmdVel(cmd_vel_topic, cmdVelCB);
//lights 
ros::Subscriber<std_msgs::Float32> subLedStrip(cmd_led_strip_topic, led_strip_controler_ros );

//-----------------PUBS-------------------------

std_msgs::Int16 pwmRightMsg ;
ros::Publisher subPwmRight(pwm_right_topic, &pwmRightMsg);

std_msgs::Int16 pwmLeftMsg ;
ros::Publisher subPwmLeft(pwm_left_topic, &pwmLeftMsg);

std_msgs::Float32 angularSpeedRightMsg ;
ros::Publisher subAngularSpeedRight(angular_speed_right_topic, &angularSpeedRightMsg);

std_msgs::Float32 angularSpeedLeftMsg ;
ros::Publisher subAngularSpeedLeft(angular_speed_left_topic, &angularSpeedLeftMsg);

std_msgs::Float32 rpmSpeedLeftMsg ;
ros::Publisher subRpmSpeedLeft(rpm_speed_left_topic, &rpmSpeedLeftMsg);
std_msgs::Float32 rpmSpeedRightMsg ;
ros::Publisher subRpmSpeedRight(rpm_speed_right_topic, &rpmSpeedRightMsg);

bool rosConnected(ros::NodeHandle  nh,bool _connect){
    bool connected = nh.connected();
    if(_connect != connected){
        _connect = connected;
        digitalWrite(LED_BUILD_IN,!connected);
        led_strip_controler(!connected);
    }
    
    return connected;
}


void ros_init(){

  nh.initNode();

  nh.subscribe(subCmdVel);
  nh.subscribe(subLedStrip);

  nh.advertise(subPwmRight);
  nh.advertise(subPwmLeft);

  nh.advertise(subAngularSpeedRight);
  nh.advertise(subAngularSpeedLeft);
  
  nh.advertise(subRpmSpeedLeft);
  nh.advertise(subRpmSpeedRight);
}

void ros_loop(float speed_right, float speed_left){
    pwmRightMsg.data = pwm_right;
    subPwmRight.publish(&pwmRightMsg);

    pwmLeftMsg.data = pwm_left;
    subPwmLeft.publish(&pwmLeftMsg);

    angularSpeedLeftMsg.data = speed_left;
    subAngularSpeedLeft.publish(&angularSpeedLeftMsg);


    angularSpeedRightMsg.data = speed_right;
    subAngularSpeedRight.publish(&angularSpeedRightMsg);

    rpmSpeedLeftMsg.data = rpm_left;
    subRpmSpeedLeft.publish(&rpmSpeedLeftMsg);

    rpmSpeedRightMsg.data = rpm_right;
    subRpmSpeedRight.publish(&rpmSpeedRightMsg);


}