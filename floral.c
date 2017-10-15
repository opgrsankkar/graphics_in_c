#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <math.h>

void bezier (int x[4], int y[4])
{

    int i;
    double t;
    double xm,ym;

    xm = getmaxx()/2;
	ym = getmaxy()/2;

	for (i=0; i<4; i++)
		putpixel ((xm+x[i]), (ym-y[i]), YELLOW);

    for (t = 0.0; t < 1.0; t += 0.0001)
    {
		double xt = pow (1-t, 3) * x[0] + 3 * t * pow (1-t, 2) * x[1] +
				3 * pow (t, 2) * (1-t) * x[2] + pow (t, 3) * x[3];

		double yt = pow (1-t, 3) * y[0] + 3 * t * pow (1-t, 2) * y[1] +
				3 * pow (t, 2) * (1-t) * y[2] + pow (t, 3) * y[3];

				xt += xm;
				yt = ym - yt;
		putpixel (xt,yt, WHITE);
    }

    return;
}

void main()
{
	int x[4], y[4];
	int xm,ym;
	int gd = DETECT, gm;

	initgraph(&gd, &gm, "\\TURBOC3\\BGI");

	xm = getmaxx()/2;
	ym = getmaxy()/2;
	
	//left-top
	x[0]=-30;	y[0]=0;
	x[1]=-40;	y[1]=100;
	x[2]=-100;	y[2]=40;
	x[3]=0;		y[3]=30;
    bezier (x,y);

	//left-bottom
	x[0]=-30;	y[0]=0;
	x[1]=-40;	y[1]=-100;
	x[2]=-100;	y[2]=-40;
	x[3]=0;		y[3]=-30;
    bezier (x,y);
	
	//top-right
	x[0]=0;		y[0]=30;
	x[1]=100;	y[1]=40;
	x[2]=40;	y[2]=100;
	x[3]=30;	y[3]=0;
    bezier (x,y);
	
	//bottom-right
	x[0]=30;	y[0]=0;
	x[1]=40;	y[1]=-100;
	x[2]=100;	y[2]=-40;
	x[3]=0;		y[3]=-30;
    bezier (x,y);
	
	//top
	x[0]=-30;	y[0]=30;
	x[1]=60;	y[1]=100;
	x[2]=-60;	y[2]=100;
	x[3]=30;	y[3]=30;
    bezier (x,y);

	//right
	x[0]=30;	y[0]=30;
	x[1]=100;	y[1]=-60;
	x[2]=100;	y[2]=60;
	x[3]=30;	y[3]=-30;
    bezier (x,y);
	
	//bottom
	x[0]=-30;	y[0]=-30;
	x[1]=60;	y[1]=-100;
	x[2]=-60;	y[2]=-100;
	x[3]=30;	y[3]=-30;
    bezier (x,y);
	
	//left
	x[0]=-30;	y[0]=30;
	x[1]=-100;	y[1]=-60;
	x[2]=-100;	y[2]=60;
	x[3]=-30;	y[3]=-30;
    bezier (x,y);
	
	circle(xm,ym,2);
	getch();
}