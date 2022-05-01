#include <kipr/wombat.h>

int main()
{
    printf("Hello World\n");
    open_claw(500);
    return 0;
}

void open_claw(int time)
{
    mav(2, 1500);
    msleep(time);
}
