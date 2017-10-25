#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <graphics.h>

#define LEFT_BOUND      150
#define RIGHT_BOUND     450
#define TOP_BOUND       100
#define BOTTOM_BOUND    350

typedef struct coordinate {
    int x, y;
    char code[4];
} PT;

void drawwindow();
void drawline(PT p1, PT p2);
PT setcode(PT p);
int visibility(PT p1, PT p2);
PT resetendpt(PT p1, PT p2);

void main() {
    int gd = DETECT, v, gm;
    PT p1, p2, p3, p4, ptemp;

    initgraph(&gd, &gm, "");

    // Line To Be Clipped
    p1.x = 50;
    p1.y = 100;
    p2.x = 500;
    p2.y = 250;

    drawwindow();
    drawline(p1, p2);

    getch();
    cleardevice();

    p1 = setcode(p1);
    p2 = setcode(p2);
    v = visibility(p1, p2);

    switch (v) {
    case 0:
        drawwindow();
        drawline(p1, p2);
        break;
    case 1:
        drawwindow();
        break;
    case 2:
        p3 = resetendpt(p1, p2);
        p4 = resetendpt(p2, p1);
        drawwindow();
        drawline(p3, p4);
        break;
    }

    getch();
    closegraph();
}

void drawwindow() {
    rectangle(LEFT_BOUND, TOP_BOUND, RIGHT_BOUND, BOTTOM_BOUND);
}

void drawline(PT p1, PT p2) {
    line(p1.x, p1.y, p2.x, p2.y);
}

PT setcode(PT p) { //for setting the 4 bit code
    PT ptemp;

    if (p.y < TOP_BOUND)
        ptemp.code[0] = '1'; //Top
    else
        ptemp.code[0] = '0';

    if (p.y > BOTTOM_BOUND)
        ptemp.code[1] = '1'; //Bottom
    else
        ptemp.code[1] = '0';

    if (p.x > RIGHT_BOUND)
        ptemp.code[2] = '1'; //Right
    else
        ptemp.code[2] = '0';

    if (p.x < LEFT_BOUND)
        ptemp.code[3] = '1'; //Left
    else
        ptemp.code[3] = '0';

    ptemp.x = p.x;
    ptemp.y = p.y;

    return (ptemp);
}

int visibility(PT p1, PT p2) {
    int i, flag = 0;

    for (i = 0; i < 4; i++) {
        if ((p1.code[i] != '0') || (p2.code[i] != '0'))
            flag = 1;
    }

    if (flag == 0)
        return (0);

    for (i = 0; i < 4; i++) {
        if ((p1.code[i] == p2.code[i]) && (p1.code[i] == '1'))
            flag = '0';
    }

    if (flag == 0)
        return (1);

    return (2);
}

PT resetendpt(PT p1, PT p2) {
    PT temp;
    int x, y, i;
    float m, k;

    if (p1.code[3] == '1')
        x = LEFT_BOUND;

    if (p1.code[2] == '1')
        x = RIGHT_BOUND;

    if ((p1.code[3] == '1') || (p1.code[2] == '1')) {
        m = (float)(p2.y - p1.y) / (p2.x - p1.x);
        k = (p1.y + (m * (x - p1.x)));
        temp.y = k;
        temp.x = x;

        for (i = 0; i < 4; i++)
            temp.code[i] = p1.code[i];

        if (temp.y <= BOTTOM_BOUND && temp.y >= TOP_BOUND)
            return (temp);
    }

    if (p1.code[0] == '1')
        y = TOP_BOUND;

    if (p1.code[1] == '1')
        y = BOTTOM_BOUND;

    if ((p1.code[0] == '1') || (p1.code[1] == '1')) {
        m = (float)(p2.y - p1.y) / (p2.x - p1.x);
        k = (float)p1.x + (float)(y - p1.y) / m;
        temp.x = k;
        temp.y = y;

        for (i = 0; i < 4; i++)
            temp.code[i] = p1.code[i];

        return (temp);
    }
    else
        return (p1);
}