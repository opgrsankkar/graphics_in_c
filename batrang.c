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

	initgraph(&gd, &gm, "");

	xm = getmaxx()/2;
	ym = getmaxy()/2;
	
	x[0]=xm-20;	y[0]=ym;
	x[1]=xm-100;	y[1]=ym;
	x[2]=xm+20;	y[2]=ym;
	x[3]=xm+100;	y[3]=ym;
	
	line(x[0],y[0],x[1],y[1]);
	line(x[2],y[2],x[3],y[3]);
	
	//Bat left top wing
	x[0]=-100;	y[0]=0;
	x[1]=-60;	y[1]=-10;
	x[2]=-60;	y[2]=-20;
	x[3]=-60;	y[3]=-30;
    bezier (x,y);

	//Bat left bottom wing
	x[0]=-60;	y[0]=-30;
	x[1]=-40;	y[1]=-32;
	x[2]=-20;	y[2]=-34;
	x[3]=0;		y[3]=-50;
    bezier (x,y);

	//Bat right top wing
	x[0]=100;	y[0]=0;
	x[1]=60;	y[1]=-10;
	x[2]=60;	y[2]=-20;
	x[3]=60;	y[3]=-30;
    bezier (x,y);

	//Bat right bottom wing
	x[0]=60;	y[0]=-30;
	x[1]=40;	y[1]=-32;
	x[2]=20;	y[2]=-34;
	x[3]=0;		y[3]=-50;
    bezier (x,y);
	
	//Bat head cave in
	x[0]=-20;	y[0]=0;
	x[1]=-10;	y[1]=-10;
	x[2]=10;	y[2]=-10;
	x[3]=20;	y[3]=0;
    bezier (x,y);
	
	getch();
	closegraph();
}