/**
 * rotating fan
 */
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double rotatex(double x, double y, double angle, double pivotx, double pivoty){
    return (x)*cos(angle) - (y)*sin(angle) + pivotx* (1-cos(angle)) + pivoty*(sin(angle));
    // return (x - pivotx)*cos(angle) - (y - pivoty)*sin(angle) + pivotx;
}
double rotatey(double x, double y, double angle, double pivotx, double pivoty){
    return (x)*sin(angle) + (y)*cos(angle) + pivoty* (1-cos(angle)) - pivotx*(sin(angle));
    // return (x - pivotx)*sin(angle) - (y - pivoty)*cos(angle) + pivoty;
}

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
    double cx, cy;
    double l1x1, l1y1, l1x2, l1y2;
    double l1angle = 120 / 180.0 * 3.14;
    double l2angle = 240 / 180.0 * 3.14;
    double rotate_angle = 2 / 180.0 * 3.14;
    int speed=1;
    int i=0;

    /* initialize graphics and local variables */
    initgraph(&gdriver, &gmode, "");

    cx = getmaxx() / 2;
    cy = getmaxy() / 2;

    l1x1 = cx;
    l1y1 = cy - 20;
    l1x2 = cx;
    l1y2 = cy - 90;

    while (!kbhit()) {
        i++;
        if(i>=60){
            l1x1 = cx;
            l1y1 = cy - 20;
            l1x2 = cx;
            l1y2 = cy - 90;
            i=0;

        }

        circle((int)cx, (int)cy, 20);
        line((int)l1x1, (int)l1y1, (int)l1x2,(int) l1y2);

        line(
            (int)rotatex(l1x1, l1y1, l1angle, cx, cy),
            (int)rotatey(l1x1, l1y1, l1angle, cx, cy),
            (int)rotatex(l1x2, l1y2, l1angle, cx, cy),
            (int)rotatey(l1x2, l1y2, l1angle, cx, cy)
        );

        line(
            (int)rotatex(l1x1, l1y1, l2angle, cx, cy),
            (int)rotatey(l1x1, l1y1, l2angle, cx, cy),
            (int)rotatex(l1x2, l1y2, l2angle, cx, cy),
            (int)rotatey(l1x2, l1y2, l2angle, cx, cy)
        );

        /* prepare for next  frame */
        delay(15);
        cleardevice();

        l1x1 = rotatex(l1x1, l1y1, rotate_angle, cx, cy);
        l1y1 = rotatey(l1x1, l1y1, rotate_angle, cx, cy);
        l1x2 = rotatex(l1x2, l1y2, rotate_angle, cx, cy);
        l1y2 = rotatey(l1x2, l1y2, rotate_angle, cx, cy);

    }

    /* clean up */
    closegraph();
    return 0;
}
