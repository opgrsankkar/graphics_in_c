/**
 * line drawing algorithms
 * BLD - Bresenham Line Drawing algorithm (for |m| < 1)
 * DDA - Digital Differential Analyser algorithm
 */
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#define WHITE 15

/**
 * function to return max of two float values
   max(a, b);
 * @param float
 * @param float
 */
float max(float a, float b){
    return (a>b)
            ? a
            : b;
}

/**
 * function to draw line given two end points in Cartesian co-ordinate system
 * with Basic Bresenham Line Drawing algorithm supporting lines with |m| < 1
   drawlineBLD(x1, y1, x2, y2);
 * @param int abscissa of starting point
 * @param int ordinate of starting point
 * @param int abscissa of ending point
 * @param int oridante of ending point
 */
void drawlineBLD(int x1,int y1, int x2, int y2){
    int dx, dy, p, x, y;

    dx = x2 - x1;
    dy = y2 - y1;

    x = x1;
    y = y1;

    p=2*dy-dx;

    while(x<x2)
    {
        putpixel(x,y,WHITE);
        if(p>=0) {
            y=y+1;
            p=p+2*dy-2*dx;
        } else {
            p=p+2*dy;
        }
        x=x+1;
    }
}

/**
 * function to draw line given two end points in Cartesian co-ordinate system
 * with Digital Differential Analyser algorithm
   drawlineDDA(x1, y1, x2, y2);
 * @param float abscissa of starting point
 * @param float ordinate of starting point
 * @param float abscissa of ending point
 * @param float oridante of ending point
 */
void drawlineDDA(float x1, float y1, float x2, float y2){
    float x, y, dx, dy, step, xinc, yinc;
    int k;

    dx = x2 - x1;
    dy = y2 - y1;

    x = x1;
    y = y1;

    step = max(abs(dx),abs(dy));
    xinc = dx / step;
    yinc = dy / step;
    for (k=0; k<step; ++k) {
        putpixel(x, y, WHITE);
        x += xinc;
        y += yinc;
    }
}

int main()
{

   /* request autodetection */
   int gdriver = DETECT, gmode, errorcode;
   /* Local Variables */
   int xmax, ymax;

   /* initialize graphics and local variables */
   initgraph(&gdriver, &gmode, "");

   xmax = getmaxx();
   ymax = getmaxy();

   /* draw line BLD*/
   drawlineBLD(0,0,xmax,ymax);

   /* draw line DDA*/
   drawlineDDA(0,ymax,xmax,0);

   /* clean up */
   getchar();
   closegraph();
   return 0;
}
