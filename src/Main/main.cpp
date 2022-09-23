
#include <Main/config.h>
#include <Main/ros_com.h>

bool _connect = false ;

void setup() { 
  ros_init();

  pinMode(LED_BUILD_IN,OUTPUT);
  digitalWrite(LED_BUILD_IN,HIGH);
  
}

void loop() 
{   
    if(!rosConnected(nh,_connect))
        stop();
  
    nh.spinOnce();

}
