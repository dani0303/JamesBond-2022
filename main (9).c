#include <kipr/wombat.h>

int main()
{
    //starts robot using light sensor
    //light_sensor();
    
    //grabs rings and drags it in place (out of the way of Dan's bot)
    close_claw(1800);
    ao();
    msleep(250);
    create_right(800);
    msleep(250);
    
    //gets into position to start putting rings on
    create_forward(3200);
    msleep(250);
    create_right(820);
    msleep(1000);
    create_forward(1500);
    msleep(500);

    //starts putting rings on
    open_claw(1850);
    ao();
    msleep(250);
    create_backward(400);
    msleep(250);
    servo_speed(1000, 800, 1, 30);
    msleep(250);
    create_forward(100);
    msleep(250);
    close_claw(2300);
    ao();
    msleep(250);
    servo_speed(800, 400, 1, 30);
    msleep(250);
    servo_speed(850, 950, 0, 30);
    msleep(250);
    
    //puts orange and red rings on horizontal bar
    create_right(1100);
    servo_speed(400, 880, 1, 30);
    msleep(250);
    claw_rotate_counterclockwise(125);
    ao();
    servo_speed(950, 1050, 0, 30);
    create_right(1300);
    ao();
    
    //goes back for yellow and green rings 
    open_claw(2100);
    ao();
    create_left(1500);
    msleep(250);
    claw_rotate_clockwise(175);
    ao();
    msleep(250);
    servo_speed(920, 400, 1, 30);
    msleep(250);
    create_left(750);
    ao();
    
    //gets yellow and green rings
    msleep(250);
    create_backward(500);
    msleep(250);
    servo_speed(400, 420, 1, 30);
    msleep(250);
    servo_speed(1050, 430, 0, 30);
    msleep(250);
    create_forward(300);
    close_claw(1900);
    ao();
    msleep(250);
    
    //puts yellow and green rings on horizontal bar
    servo_speed(430, 1050, 0, 30);
    msleep(250);
    servo_speed(420, 400, 1, 30);
    msleep(250);
    create_forward(200);
    msleep(250);
    create_right(700);
    servo_speed(400, 880, 1, 30);
    msleep(250);
    claw_rotate_clockwise(200);
    ao();
    msleep(250);
    create_right(1500);
    msleep(250);
    open_claw(2000);
    ao();
    msleep(250);
    
    //goes back for blue
    create_left(1600);
    msleep(250);
    claw_rotate_counterclockwise(200);
    ao();
    msleep(250);
    servo_speed(880, 400, 1, 30);
    msleep(250);
    create_left(500);
    msleep(250);
    create_backward(400);
    msleep(250);
    servo_speed(400, 350, 1, 30);
    msleep(250);
    servo_speed(1050, 350, 0, 30);
    msleep(250);
    create_forward(300);
    msleep(250);
    close_claw(1900);
    ao();
    msleep(250);
    create_forward(100);
    msleep(250);
    
    //puts blue ring on horizontal bar
    servo_speed(350, 1050, 0, 30);
    msleep(250);
    servo_speed(350, 400, 1, 30);
    msleep(250);
    create_right(700);
    msleep(250);
    servo_speed(400, 880, 1, 30);
    msleep(250);
    claw_rotate_clockwise(200);
    ao();
    msleep(250);
    create_right(1500);
    msleep(250);
    open_claw(2000);
    ao();
    msleep(250);
    create_left(3000);
    msleep(250);
    claw_rotate_counterclockwise(180);
    ao();
    msleep(250);
    
    //gets botguy
    create_forward(5000);
    msleep(250);
    servo_speed(1050, 1400, 0, 30);
    msleep(250);
    servo_speed(880, 450, 1, 30);
    msleep(250);
    create_forward(1500);
    msleep(250);
    create_left(1300);
    msleep(250);
    create_forward(1000);
    msleep(250);
    close_claw(2500);
    ao();
    msleep(250);
    create_right(700);
    msleep(250);
    
    
    
    
    
    
    
    
    
    return 0;
}





//FUNCTIONS

//moves create forward

void create_forward(int time)
{
    create_connect();
    create_drive_direct(75, 75);
    msleep(time);
    create_stop();
    create_disconnect(); 
}


//moves create backwards

void create_backward(int time)
{
    create_connect();
    create_drive_direct(-75, -75);
    msleep(time);
    create_stop();
    create_disconnect(); 
}


//moves create right

void create_right(int time)
{
    create_connect();
    create_drive_direct(75, -75);
    msleep(time);
    create_stop();
    create_disconnect(); 
}


//moves create left

void create_left(int time)
{
    create_connect();
    create_drive_direct(-75, 75);
    msleep(time);
    create_stop();
    create_disconnect(); 
}


//rotates claw clockwise

void claw_rotate_clockwise(int time)
{
    mav(0, 1500);
    msleep(time);
}


//rotates claw counterclockwise

void claw_rotate_counterclockwise(int time)
{
    mav(0, -1500);
    msleep(time);
}


//opens claw

void open_claw(int time)
{
    mav(2, 1500);
    msleep(time);
}


// starts robot using light sensor

void light_sensor()
{
    while(analog(0) > 3000)
    {
        if(analog(0) <= 3200)
        {
            break;
        }
    }
}


//close claw

void close_claw(int time)
{
    mav(2, -1500);
    msleep(time);
}


//moves servos to a specific position with a position speed

//moves a servo from one given position to another at a certain speed
//op- the starting position of the servo
//wp- the ending positon of the servo
//servoport- the port of the servo 
//speed- the increment by which the servo position is repeatedly moved
void servo_speed(int op, int wp, int servoport, int speed) {   
    //allows for the servo to change in any direction
	if(op > wp){
		while(op > wp){
			if(op - wp < speed){
				//just set the claw to the end position
				set_servo_position(servoport, wp);
				op = wp;
			}else{
				//increments the position
				op -= speed;  

				//sets the servo position to the incremented position
                enable_servos();
				set_servo_position(servoport, op);
				msleep(100);
                disable_servos();
			}
		}
	}else{
		while(wp > op){
			 //if the position is less than one increment away from the wanted position
			if(wp - op < speed){
				//just set the claw to the end position
                enable_servos();
				set_servo_position(servoport, op); 
                msleep(100);
                disable_servos();
				op = wp;
			}else{
				
				//increments the position
				op += speed;
				//sets the servo position to the incremented position
                enable_servos();
				set_servo_position(servoport, op);
				msleep(100);
                disable_servos();
			}
		}
	}
}