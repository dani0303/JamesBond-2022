#include <kipr/wombat.h>
//wires will get tangles if rotated in one direction too long
int main()
{
    printf("Hello World\n");
    claw_rotate_clockwise(500);
    return 0;
}

void claw_rotate_clockwise(int time)
{
    mav(0, 1500);
    msleep(time);
}
