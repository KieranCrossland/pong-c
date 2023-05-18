#include <stdio.h>
#include <stdlib.h>

#include "include/raylib.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_FPS 144

/*Type declarations*/
typedef struct
{
    Vector2 pos;
    float speed;
    float width;
    float height;

} Paddle;

typedef struct
{
    Vector2 pos;
    float radius;
    Vector2 speed;
}Ball;

/*Beginning of code*/

void DrawBall(Ball* ball)
{
    DrawCircle(ball->pos.x, ball->pos.y, ball->radius, WHITE);
}

void UpdateBall(Ball* ball)
{
    ball->pos.x += ball->speed.x;
    ball->pos.y += ball->speed.y;

    if (ball->pos.y + ball->radius >= GetScreenHeight() || ball->pos.y - ball->radius <= 0) {
        ball->speed.y *= -1;
    }
    if (ball->pos.x  - 200   + ball->radius >= GetScreenHeight() || ball->pos.x - ball->radius <= 0) {
        ball->speed.x *= -1;
    }
}

void CheckPaddleOutOfBounds(Paddle* paddle) {
    //Checks if a paddle's position exceeds the window bounds and stops it.
    if (paddle->pos.y < -1) paddle->pos.y = 1;
            if (paddle->pos.y >= WINDOW_HEIGHT - 80) paddle->pos.y = WINDOW_HEIGHT - 80;
            if (paddle->pos.y < -1) paddle->pos.y = 1;
}

int main(int argc, char* argv[])
{
    if (argc > 1)
    {
        printf("program arguemts: %s\n",argv[1]);
    }
    else
    {
        printf("program received no arguments\n");
    }

    Paddle player1 = {WINDOW_WIDTH - 25.0, WINDOW_WIDTH/2.0 - 150, 4, 20, 90};
    Paddle player2 = {5.0, WINDOW_WIDTH/2.0 - 150, 4, 20, 90};
    Ball Ball1 = { /*Vector2 pos.x*/ WINDOW_WIDTH / 2.0, /*Vector2 pos.y*/ WINDOW_HEIGHT / 2.0, /*float radius*/ 20, /*int speedX*/ 2, /*int speedY*/ 2};

    const char msg[] ="Pong in C";

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "pong-c (raylib)");
    Font ndsbios = LoadFontEx("assets/fonts/nintendo_ds_bios/Nintendo-DS-BIOS.ttf",36 ,0, 255);

    SetTargetFPS(WINDOW_FPS);
    while (!WindowShouldClose())
        {

            //Controls for player 1
            if (IsKeyDown(KEY_UP)) player1.pos.y -= player1.speed;
            if (IsKeyDown(KEY_DOWN)) player1.pos.y += player1.speed;
            //Controls for player 2
            if (IsKeyDown(KEY_W)) player2.pos.y -= player2.speed;
            if (IsKeyDown(KEY_S)) player2.pos.y += player2.speed;

            UpdateBall(&Ball1);

            CheckPaddleOutOfBounds(&player1);
            CheckPaddleOutOfBounds(&player2);
            BeginDrawing();

                ClearBackground(BLACK);
                
                DrawTextEx(ndsbios, msg, (Vector2){10.0f, 10.0f},(float)ndsbios.baseSize, 2, YELLOW);

                DrawRectangle(player1.pos.x, player1.pos.y, player1.width, player1.height, DARKBLUE);
                DrawRectangle(player2.pos.x, player2.pos.y, player2.width, player2.height, DARKGREEN);
                
                DrawBall(&Ball1);

            EndDrawing();
        }
    CloseWindow();
    printf("Goodbye\n");
    return 0;

}
