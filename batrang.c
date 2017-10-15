#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <math.h>

#define LEFT 0
#define TOP 1
#define RIGHT 2
#define BOTTOM 3
#define BOUND 30
double ANG(double x) { return x*3.1415/180; }

double xm,ym;
double ang = 0;
int flag[] = {0,0,0,0};
int kbhit() {
    struct timeval tv;
    fd_set fds;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds); //STDIN_FILENO is 0
    select(STDIN_FILENO+1, &fds, NULL, NULL, &tv);
    return FD_ISSET(STDIN_FILENO, &fds);
}
double rotatex(double x, double y, double angle, double pivotx, double pivoty){
    return (x)*cos(angle) - (y)*sin(angle) + pivotx* (1-cos(angle)) + pivoty*(sin(angle));
    // return (x - pivotx)*cos(angle) - (y - pivoty)*sin(angle) + pivotx;
}
double rotatey(double x, double y, double angle, double pivotx, double pivoty){
    return (x)*sin(angle) + (y)*cos(angle) + pivoty* (1-cos(angle)) - pivotx*(sin(angle));
    // return (x - pivotx)*sin(angle) - (y - pivoty)*cos(angle) + pivoty;
}
void bezier (int x[4], int y[4]) {

    int i;
    double u;

	// for (i=0; i<4; i++)
	// 	putpixel ((xm+x[i]), (ym-y[i]), YELLOW);

    for (u = 0.0; u < 1.0; u += 0.01)
    {
		double xt = pow (1-u, 3) * x[0] + 3 * u * pow (1-u, 2) * x[1] +
				3 * pow (u, 2) * (1-u) * x[2] + pow (u, 3) * x[3];

		double yt = pow (1-u, 3) * y[0] + 3 * u * pow (1-u, 2) * y[1] +
				3 * pow (u, 2) * (1-u) * y[2] + pow (u, 3) * y[3];

		xt += xm;
		yt = ym - yt;

		if (rotatex(xt, yt, ANG(ang), xm, ym) <= BOUND)
			flag[LEFT]		= 1;
		if (rotatex(xt, yt, ANG(ang), xm, ym) >= getmaxx()-BOUND)
			flag[RIGHT]		= 1;
		if (rotatey(xt, yt, ANG(ang), xm, ym) <= BOUND)
			flag[TOP]		= 1;
		if (rotatey(xt, yt, ANG(ang), xm, ym) >= getmaxy()-BOUND)
			flag[BOTTOM]	= 1;

		if(!(flag[LEFT]==1||flag[RIGHT]==1||flag[TOP]==1||flag[BOTTOM]==1)){
			putpixel ((int)rotatex(xt, yt, ANG(ang), xm, ym),
					(int)rotatey(xt, yt, ANG(ang), xm, ym),
					WHITE);
		}
    }

    return;
}

void main() {
	int x[4], y[4];
	int x_step=5, y_step=5, ang_step = 5;
	int gd = DETECT, gm;
	int i = 0;

	initgraph(&gd, &gm, "");

	xm = getmaxx()/2;
	ym = getmaxy()/2;

	while(!kbhit()) {

		if (flag[LEFT] == 1) {
			x_step = 5;
			if ((ang > 180 && ang < 270) || (ang > 0 && ang < 90)) {
				ang_step = -ang_step;
			}
		}
		if (flag[RIGHT] == 1) {
			x_step = -5;
			if ((ang > 180 && ang < 270) || (ang > 0 && ang < 90)) {
				ang_step = -ang_step;
			}
		}
		if (flag[TOP] == 1) {
			y_step = 5;
			if (!((ang > 180 && ang < 270) || (ang > 0 && ang < 90))) {
				ang_step = -ang_step;
			}
		}
		if (flag[BOTTOM] == 1) {
			y_step = -5;
			if ((ang > 90 && ang < 180) || (ang > 0 && ang < 90)) {
				ang_step = -ang_step;
			}
		}

		ang = (double)(((int)(ang+ang_step))%359);
		xm += x_step;
		ym += y_step;

		for(int loop = 0; loop < 4; loop++) flag[loop]=0;

		x[0]=xm-20;		y[0]=ym;
		x[1]=xm-100;	y[1]=ym;
		x[2]=xm+20;		y[2]=ym;
		x[3]=xm+100;	y[3]=ym;
		
		rectangle (BOUND,BOUND,getmaxx()-BOUND,getmaxy()-BOUND);
		if ((int)rotatex(x[0],y[0],ANG(ang),xm,ym) < BOUND ||
			(int)rotatey(x[0],y[0],ANG(ang),xm,ym) < BOUND ||
			(int)rotatex(x[1],y[1],ANG(ang),xm,ym) < BOUND ||
			(int)rotatey(x[1],y[1],ANG(ang),xm,ym) < BOUND ||
			(int)rotatex(x[2],y[2],ANG(ang),xm,ym) < BOUND ||
			(int)rotatey(x[2],y[2],ANG(ang),xm,ym) < BOUND ||
			(int)rotatex(x[3],y[3],ANG(ang),xm,ym) < BOUND ||
			(int)rotatey(x[3],y[3],ANG(ang),xm,ym) < BOUND ||
			(int)rotatex(x[0],y[0],ANG(ang),xm,ym) > getmaxx() - BOUND ||
			(int)rotatey(x[0],y[0],ANG(ang),xm,ym) > getmaxy() - BOUND ||
			(int)rotatex(x[1],y[1],ANG(ang),xm,ym) > getmaxx() - BOUND ||
			(int)rotatey(x[1],y[1],ANG(ang),xm,ym) > getmaxy() - BOUND ||
			(int)rotatex(x[2],y[2],ANG(ang),xm,ym) > getmaxx() - BOUND ||
			(int)rotatey(x[2],y[2],ANG(ang),xm,ym) > getmaxy() - BOUND ||
			(int)rotatex(x[3],y[3],ANG(ang),xm,ym) > getmaxx() - BOUND ||
			(int)rotatey(x[3],y[3],ANG(ang),xm,ym) > getmaxy() - BOUND) {
			//pass
		} else {
			line(
				(int)rotatex(x[0],y[0],ANG(ang),xm,ym),
				(int)rotatey(x[0],y[0],ANG(ang),xm,ym),
				(int)rotatex(x[1],y[1],ANG(ang),xm,ym),
				(int)rotatey(x[1],y[1],ANG(ang),xm,ym)
			);
			line(
				(int)rotatex(x[2],y[2],ANG(ang),xm,ym),
				(int)rotatey(x[2],y[2],ANG(ang),xm,ym),
				(int)rotatex(x[3],y[3],ANG(ang),xm,ym),
				(int)rotatey(x[3],y[3],ANG(ang),xm,ym)
			);
		}
		//left top wing
		x[0]=-100;	y[0]=0;
		x[1]=-60;	y[1]=-10;
		x[2]=-60;	y[2]=-20;
		x[3]=-60;	y[3]=-30;
		bezier (x,y);

		//left bottom wing
		x[0]=-60;	y[0]=-30;
		x[1]=-40;	y[1]=-32;
		x[2]=-20;	y[2]=-34;
		x[3]=0;		y[3]=-50;
		bezier (x,y);

		//right top wing
		x[0]=100;	y[0]=0;
		x[1]=60;	y[1]=-10;
		x[2]=60;	y[2]=-20;
		x[3]=60;	y[3]=-30;
		bezier (x,y);

		//right bottom wing
		x[0]=60;	y[0]=-30;
		x[1]=40;	y[1]=-32;
		x[2]=20;	y[2]=-34;
		x[3]=0;		y[3]=-50;
		bezier (x,y);
		
		//head
		x[0]=-20;	y[0]=0;
		x[1]=-10;	y[1]=-10;
		x[2]=10;	y[2]=-10;
		x[3]=20;	y[3]=0;
		bezier (x,y);

		delay(15);
		cleardevice();
	}
	closegraph();
}