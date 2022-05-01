#include <kipr/wombat.h>

int main()
{
    printf("Hello World\n");
    
    enable_servos();
    set_servo_position(1,1000); //homes elbow2
    msleep(100);
    set_servo_position(0,850); //homes elbow1
    msleep(100);
    disable_servos();
    return (0);
    
}