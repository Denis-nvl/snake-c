#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include "../include/snake.h"

struct Snake snake;
struct Point food;

int gameOver = 0;
char direction = 'd';
int score = 0;

void init() {
    snake.length = 3;
    snake.body[0] = (struct Point){10, 10};
    snake.body[1] = (struct Point){9, 10};
    snake.body[2] = (struct Point){8, 10};

    srand(time(NULL));
    food.x = rand() % WIDTH;
    food.y = rand() % HEIGHT;
}

void draw() {
    system("cls");

    for (int i = 0; i < WIDTH + 2; i++) printf("#");
    printf("\n");

    for (int y = 0; y < HEIGHT; y++) {
        printf("#");
        for (int x = 0; x < WIDTH; x++) {
            int printed = 0;

            if (x == food.x && y == food.y) {
                printf("*");
                continue;
            }

            for (int k = 0; k < snake.length; k++) {
                if (snake.body[k].x == x && snake.body[k].y == y) {
                    printf(k == 0 ? "O" : "o");
                    printed = 1;
                }
            }

            if (!printed) printf(" ");
        }
        printf("#\n");
    }

    for (int i = 0; i < WIDTH + 2; i++) printf("#");
    printf("\nScore: %d\n", score);
}

void input() {
    if (_kbhit()) {
        char c = _getch();
        if (c == 'w') direction = 'w';
        if (c == 's') direction = 's';
        if (c == 'a') direction = 'a';
        if (c == 'd') direction = 'd';
    }
}

void logic() {
    struct Point head = snake.body[0];

    if (direction == 'w') head.y--;
    if (direction == 's') head.y++;
    if (direction == 'a') head.x--;
    if (direction == 'd') head.x++;

    if (head.x < 0 || head.x >= WIDTH || head.y < 0 || head.y >= HEIGHT)
        gameOver = 1;

    for (int i = 1; i < snake.length; i++) {
        if (head.x == snake.body[i].x && head.y == snake.body[i].y)
            gameOver = 1;
    }

    for (int i = snake.length; i > 0; i--) {
        snake.body[i] = snake.body[i - 1];
    }

    snake.body[0] = head;

    if (head.x == food.x && head.y == food.y) {
        snake.length++;
        score += 10;
        food.x = rand() % WIDTH;
        food.y = rand() % HEIGHT;
    }
}

int main() {
    init();

    while (!gameOver) {
        draw();
        input();
        logic();
        Sleep(200);
    }

    printf("Game Over! Scor final: %d\n", score);
    return 0;
}
