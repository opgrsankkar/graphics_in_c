/**
 * bouncing ball
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
    int up = 0;
    int left = 0;

    /* initialize graphics and local variables */
    initgraph(&gdriver, &gmode, "");

    /* get mid positions in x and y-axis */
    x = getmaxx() / 2;
    y = getmaxy() / 2;

    while (!kbhit()) {
        if (y >= getmaxy() - 30)
            up = 1;
        if (y <= 30)
            up = 0;

        if (x >= getmaxx() - 30)
            left = 1;
        if (x <= 30)
            left = 0;

        setcolor(RED);
        circle(x, y, 30);
        floodfill(x, y, RED);

        /* prepare for next  frame */
        delay(15);
        cleardevice();

        if (up)
            y = y - 5;
        else
            y = y + 5;

        if (left)
            x = x - 5;
        else
            x = x + 5;
    }

    /* clean up */
    closegraph();
    return 0;
}
