#include<graphics.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>

void bezier (int x[4], int y[4]) {
    int i;
    double t;
    double xm,ym;

	xm = getmaxx()/2;
	ym = getmaxy()/2;

	for (i=0; i<4; i++)
		putpixel ((xm+x[i]), (ym-y[i]), YELLOW);

    for (t = 0.0; t < 1.0; t += 0.01) {
		double xt = pow (1-t, 3) * x[0] + 3 * t * pow (1-t, 2) * x[1] +
				3 * pow (t, 2) * (1-t) * x[2] + pow (t, 3) * x[3];

		double yt = pow (1-t, 3) * y[0] + 3 * t * pow (1-t, 2) * y[1] +
				3 * pow (t, 2) * (1-t) * y[2] + pow (t, 3) * y[3];

				// xt += xm;
				// yt = ym - yt;
		putpixel (xt,yt, WHITE);
    }

    return;
}

void main(void)
{
	int gdriver = DETECT,gnode,errorcode;
	int x[4], y[4];
	initgraph(&gdriver,&gnode, "");
	

	x[0] =   0; y[0] = 0;
	x[1] = -50; y[1] = 100;
	x[2] = +50; y[2] = 100;
	x[3] =   0; y[3] = 0;
	bezier(x,y);

	getch();
	closegraph();
}