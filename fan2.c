/**
 * rotating fan
 */
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>

int kbhit()
{
    struct timeval tv;
    fd_set fds;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds); //STDIN_FILENO is 0
    select(STDIN_FILENO+1, &fds, NULL, NULL, &tv);
    return FD_ISSET(STDIN_FILENO, &fds);
}

int main()
{

    /* request autodetection */
    int gdriver = DETECT, gmode, errorcode;

    /* Local Variables */
    int x, y;
    int i;

    initgraph(&gdriver, &gmode, "");

    x = getmaxx() / 2;
    y = getmaxy() / 2;
    i = 0;
    while (!kbhit()) {

        pieslice(x, y, i, i+30, 100);

        pieslice(x, y, i+120, i+150, 100);

        pieslice(x, y, i+240, i+270, 100);

        delay(15);
        cleardevice();

        i++;
    }

    /* clean up */
    closegraph();
    return 0;
}