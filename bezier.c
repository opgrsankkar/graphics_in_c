#include<graphics.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>

void main(void)
{
	int gdriver = DETECT,gnode,errorcode;
	initgraph(&gdriver,&gnode, "");
	int x0,x1,x2,x3,y0,y1,y2,y3;
	float u=0.1;
	float x,y;
	printf("Enter x0 y0");
	scanf("%d %d",&x0,&y0);
	printf("Enter x1 y1");
	scanf("%d %d",&x1,&y1);
	printf("Enter x2 y2");
	scanf("%d %d",&x2,&y2);
	printf("Enter x3 y3");
	scanf("%d %d",&x3,&y3);
	for(u=0.1;u!=1;u=u+0.1)
	{

	       x=(x0*pow((1-u),3))+(x1*3*u*pow((1-u),2))+(x2*3*u*u*(1-u))+(x3*u*u*u);
	       y=(y0*pow((1-u),3))+(y1*3*u*pow((1-u),2))+(y2*3*u*u*(1-u))+(y3*u*u*u);
	       line(x0,y0,x,y);
	       x0=x;
	       y0=y;
	}
	getch();
	closegraph();
}