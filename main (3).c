#include <kipr/wombat.h>

//SENSORS
int r_sen = 0;//RIGHT SENSOR
int l_sen = 1;//LEFT SENSOR

//SERVO PORTS
int ARM = 0;
int CLAW = 1;

//SERVO POSITIONS
int arm_low = 1030;
int close_claw = 1451;
int arm_lift = 450;
int open_claw = 0;

/*
comes out of starting box and turns right to face black line and follow it
uses line follower code to follow the line while plowing the pom poms
once it gets to the middle it must drive forward for a few seconds to compensate
for the black line in the midlle of the board
*/
int main()
{
    //DRIVE TIME: 3000 TURN: 1000
    GetOutOfStartBox(5, 2250);
    stop(3000);
    //DRIVE FORWARD TO COMPENSATE FOR THE SAMPLE ISOLATION UNIT BEFORE LINE FOLLOW
    printf("Drive forward to clear small box\n");
    drive(500, 6500);
    stop(50);
    //AFTER CLEARING THE BOX BEGIN LINE FOLLOW
    printf("Start first line follower\n");
    line_follow(30);
    //DRIVE FORWARD PASS THE BLACK LINE IN THE MIDDLE
    printf("Drive pass the the middle black tape\n");
    //WHILE THE RIGHT SENSOR DETECTS A VALUE GREATER THAN BLACK
    stop(500);
    while(analog(l_sen) > 2000)
    {
        printf("while loop started\n");
        drive(500, 50);
    }
    //BEGIN THE LINE FOLLOWER
    printf("Start second line follower\n");
    line_follow(45);
    stop(50);
	
    /*
	SECOND HALF
	*/
	
    //DRIVE BACK TO MAKE ROOM FOR HOOK
    drive(-500, 5000);
    stop(50);
    turn_right(1000, 500);
    drive(1000, 500);
    turn_left(1000, 150);
    //LOWER THE ARM
    ArmControl(arm_low);
    stop(50);
    //DRIVE IN WITH HOOK DOWN TO GET THE TRANSPORTER
    drive(500, 2000);
    stop(50);
    //LIFT THE TRANSPORTER UP
    servo_change(arm_low, arm_lift, ARM, 50);
    stop(50);
    //DRIVE BACK TO COLLECT THE POM POMS
    drive(-500, 4000);
    stop(50);
    //LOWER THE TRANSPORTER ONTOP OF THE POM POMS
    servo_change(arm_lift, arm_low, ARM, 50);
    stop(50);
    //DRIVE BACK TO PULL OUT THE HOOK
    drive(-500, 2000);
    stop(50);
    //LIFT THE HOOK
    servo_change(arm_low, arm_lift, ARM, 50);
    stop(50);
    //DRIVE FORWARD AGAIN TO GET HOOK IN THE MIDDLE
    //THIS IS DONE TO GET THE TRANSPORTER IN A GRIP TO CARRY ALONG THE BOARD
    drive(500, 1500);
    //LOWER THE ARM
    servo_change(arm_lift, arm_low, ARM, 50);
    //PULL BACK TO ADJUST THE GRIP
    drive(500, 2500);
    //TURN RIGHT AND GO HOME
    turn_right(1000, 2500);
    line_follow(20);
    ArmControl(arm_lift);
    drive(1000, 500);
    line_follow(20);
    printf("End\n");
    return 0;
}

void drive(int power, int time)
{
    mav(0, power);
    mav(1, power);
    msleep(time);
}

void turn_left(int power, int time)
{
    mav(0, power);
    mav(1, -power);
    msleep(time);
}

void turn_right(int power, int time)
{
    mav(0, -power);
    mav(1, power);
    msleep(time);
}

void stop(int time)
{
    mav(0, 0);
    mav(1, 0);
    msleep(time);
}

/*
*LINE_FOLLOW
*time represents the total amount of time the robot
*will be running line follow
*while the the both sensors don't detect any tape drive foward for 500
*add one to the counter first so that it won't do another loop before time runs outs
*if r_sen detects black turn right
*if l_sen detects black turn left
*if counter equals the time then break out of the loop
*/
void line_follow(int time)
{
    int count = 0;
    while (count < time)
    {
        count ++;
        if(count == time)
        {
            break;
        }
        else if (analog(r_sen) >= 2000)
        {
            stop(50);
            turn_right(1500, 85);
        }
        else if(analog(l_sen) >= 2000)
        {
            stop(50);
            turn_left(1500, 85);
        }
        else
        {
            drive(500, 350);
        }
    }
}

void reverse_line_follow()
{
    //if right sensor detects black
    if (analog(r_sen) >= 3100)
    {
        //turn right to make left sensor
        turn_right(1500, 85);
        while(analog(l_sen) <= 3100)
        {
            drive(500, 85);
        }
        turn_left(500, 500);
    }
}

void GetOutOfStartBox(int drive_time, int turn_time)
{
    //START AT ANGLE AND DRIVE FORWARD TO REACH BLACK LINE
    while(analog(r_sen) <= 2000)
    {
        drive(500, drive_time);
    }
    drive(500, 1500);
    stop(50);
    //TURN RIGHT TO FACE BLACK LINE
    turn_right(500, turn_time);
    stop(50);
}

void ArmControl(int position)
{
    enable_servos();
    set_servo_position(ARM, position);
    msleep(500);
    disable_servos();
}

void ClawControl(int position)
{
    enable_servos();
    set_servo_position(CLAW, position);
    msleep(500);
    disable_servos();
}

void servo_change(int op, int wp, int servoport, int speed) 
{   
    //allows for the servo to change in any direction
    enable_servos();
    if (op > wp) 
    { 
        while(op > wp)  
        {   
            //if the position is less than one increment away from the wanted position
            if(op - wp < speed)
            {
                //just set the claw to the end position
                set_servo_position(servoport, wp);
                op = wp;
            }
            else
            {
                //increments the position
                op -= speed;  
                //sets the servo position to the incremented position
                set_servo_position(servoport, op);   
                msleep(100); 
            }
        }   
    }
    else 
    { 
        while(wp > op)  
        {   
            //if the position is less than one increment away from the wanted position
            if(wp - op < speed)
            {
                //just set the claw to the end position
                set_servo_position(servoport, op); 
                op = wp;
            }
            else
            {
                //increments the position
                op += speed; 
                //sets the servo position to the incremented position
                set_servo_position(servoport, op);   
                msleep(100); 
            }
        }   
    } 
    disable_servos();
} 