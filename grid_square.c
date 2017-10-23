#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <math.h>

#define GRID 5
int maxx, maxy;
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
void setpixel(int x, int y) {
    int xp, yp;
    if(x>0) {
        xp = (x*GRID) + 2 + (maxx/2);
    } else {
        xp = (maxx/2) + (x*GRID) - 2 + GRID;
    }
    if(y>0) {
        yp = maxy - ((y*GRID) + 2 + (maxy/2));
    } else {
        yp = maxy - ((maxy/2) + (y*GRID) - 2 + GRID);
    }
    
    // setfillstyle(SOLID_FILL, c);
    floodfill(xp, yp, YELLOW);
    // setfillstyle(SOLID_FILL, WHITE);
}
void drawlineBLD(int x1,int y1, int x2, int y2){
    int dx, dy, p, x, y;

    dx = x2 - x1;
    dy = y2 - y1;

    x = x1;
    y = y1;

    p=2*dy-dx;

    while(x<x2)
    {
        setpixel(x,y);
        if(p>=0) {
            y=y+1;
            p=p+2*dy-2*dx;
        } else {
            p=p+2*dy;
        }
        x=x+1;
    }
}
void drawgrid() {
    int i, j;
    setcolor(GREEN);
    line(maxx/2, 0, maxx/2, maxy);
    line(0, maxy/2, maxx, maxy/2);
    setcolor(YELLOW);
    for (i=maxx/2; i<maxx; i+=GRID) {
        line(i, 0, i, maxy);
        line(maxx-i, 0, maxx-i, maxy);
    }
    for (j=maxy/2; j < maxy; j+=GRID) {
        line(0, j, maxx, j);
        line(0, maxy-j, maxx, maxy-j);
    }
    setcolor(WHITE);
}
void drawcar(int xc, int yc) {
    drawlineBLD(xc,yc,xc+5,yc);
}
int main() {
    int gd = DETECT, gm;
    int x, y;
    initgraph(&gd, &gm, "");
    maxx = getmaxx();
    maxy = getmaxy();
    x = -5;
    y = 5;
    while(!kbhit()) {
        if(x < 5) {
            x++;
        } else {
            break;
        }
        drawgrid();
        drawcar(x,y);

        delay(1000);
        cleardevice();
    }
    
    
    getch();
    return 0;
}