#ifndef SNAKE_H
#define SNAKE_H

#define WIDTH 20
#define HEIGHT 20

struct Point {
    int x, y;
};

struct Snake {
    struct Point body[100];
    int length;
};

#endif
