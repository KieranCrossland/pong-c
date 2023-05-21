/********************************************************************************************************************/
//By Kieran Crossland, "finished" 20th May 2023, Licensed GPL3. Written in raylib. [https://github.com/raysan5/raylib]
//This is the first real program that I've written and finished in C! ;)
/********************************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "include/raylib.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_FPS 60.0

typedef struct
{
    bool is_won;
    int winning_score;

} GameState;
typedef struct
{
    Vector2 pos;
    float speed;
    float width;
    float height;
    int score;

} Paddle;

typedef struct
{
    Vector2 pos;
    float radius;
    Vector2 speed;

} Ball;

void DrawBall(Ball* ball)
{
    DrawCircle(ball->pos.x, ball->pos.y, ball->radius, WHITE);
}

void UpdateBall(Ball* ball)
{
    ball->pos.x += ball->speed.x;
    ball->pos.y += ball->speed.y;

    if (ball->pos.y + ball->radius >= GetScreenHeight() || ball->pos.y - ball->radius <= 0)
    {
        ball->speed.y *= -1.0;
    }
    if (ball->pos.x  - 200 + ball->radius >= GetScreenHeight() || ball->pos.x - ball->radius <= 0)
    {
        ball->speed.x *= -1.0;
    }
}

void ResetBall(Ball*  ball)
{
    ball->pos.x = WINDOW_HEIGHT /2.0;
    ball->pos.y = WINDOW_WIDTH /2.0;
}
void CheckPaddleOutOfBounds(Paddle* paddle)
{
    //Checks if a paddle's position exceeds the window bounds and stops it.
    if (paddle->pos.y < -1.0) paddle->pos.y = 1.0;
            if (paddle->pos.y >= WINDOW_HEIGHT - 80.0) paddle->pos.y = WINDOW_HEIGHT - 80.0;
            if (paddle->pos.y < -1) paddle->pos.y = 1;
}

void CheckBallTouchingPaddle(Ball* ball, Paddle* paddle)
{
    if (CheckCollisionCircleRec((Vector2){ball->pos.x, ball->pos.y}, ball->radius, (Rectangle){paddle->pos.x, paddle->pos.y, paddle->width, paddle->height}))
    {
        ball->speed.x*= -1;
    }
}

void ResetGame(Ball* ball, GameState* game_state, Paddle* paddle1, Paddle* paddle2) 
{
    ball->pos.x = WINDOW_WIDTH / 2.0;
    ball->pos.y = WINDOW_HEIGHT / 2.0;
    
    paddle1->pos.x = WINDOW_WIDTH - 25.0;
    paddle1->pos.y = WINDOW_WIDTH / 2.0 - 150.0;
    paddle1->score = 0;

    paddle2->pos.x = 5.0;
    paddle2->pos.y = WINDOW_WIDTH / 2.0 - 150.0;
    paddle2->score = 0;

    game_state->is_won = false;
}

int main(int argc, char* argv[])
{
    GameState game = {false, 5};
    if (argc >= 1)
    {
        int winscore_as_int = atoi(argv[1]);
        game.winning_score = winscore_as_int;
        printf("CLI argument %i set as game.winning_score\n",game.winning_score);
    } 
    else 
    {
        printf("CLI recieved no arguments, using default game.winning_score = 5\n");
    }
    Paddle player1 = {WINDOW_WIDTH - 25.0, WINDOW_WIDTH / 2.0 - 150.0, 8.0, 20.0, 90.0, 0};
    Paddle player2 = {5.0, WINDOW_WIDTH / 2.0 - 150.0, 8.0, 20.0, 90.0, 0};
    Ball ball1 = { /*Vector2 pos.x*/ WINDOW_WIDTH / 2.0, /*Vector2 pos.y*/ WINDOW_HEIGHT / 2.0, /*float radius*/ 20, /*int speedX*/ 4, /*int speedY*/ 4};

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Kieran's Pong in C (raylib) ");

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

            UpdateBall(&ball1);

            CheckPaddleOutOfBounds(&player1);
            CheckPaddleOutOfBounds(&player2);

            CheckBallTouchingPaddle(&ball1, &player1);
            CheckBallTouchingPaddle(&ball1, &player2);

            if (ball1.pos.x  - 200 + ball1.radius >= GetScreenHeight())
            {
                    player1.score++;
            }
            if (player1.score >= game.winning_score)
            {
                printf("Green Wins!\n");
                game.is_won = true;
                //DrawTextEx(ndsbios, "Green Wins!", (Vector2){20, WINDOW_HEIGHT - 50.f},(float)ndsbios.baseSize, 4, YELLOW);
                SetWindowTitle("Green Won the last match!");
                


            }

            if (ball1.pos.x - ball1.radius <= 0)
            {
                    player2.score++;
            }
            if (player2.score >= game.winning_score)
            {
                printf("Blue Wins!\n");
                game.is_won = true;
                //DrawTextEx(ndsbios, "Blue Wins!", (Vector2){WINDOW_WIDTH -190,WINDOW_HEIGHT - 50.f},(float)ndsbios.baseSize, 4, YELLOW);
                SetWindowTitle("Blue Won the last match!");
                
                
                
            }

            BeginDrawing();
            if (!game.is_won)
            {
                ClearBackground(BLACK);

                DrawTextEx(ndsbios, TextFormat("%i", player1.score), (Vector2){10.0f, 10.0f},(float)ndsbios.baseSize, 4, GREEN);
                DrawTextEx(ndsbios, TextFormat("%i", player2.score), (Vector2){WINDOW_WIDTH -25, 10.0f},(float)ndsbios.baseSize, 4, BLUE);

                DrawRectangle(player1.pos.x, player1.pos.y, player1.width, player1.height, DARKBLUE);
                DrawRectangle(player2.pos.x, player2.pos.y, player2.width, player2.height, DARKGREEN);

                DrawBall(&ball1);
            }
            if (game.is_won)
            {
                ResetGame(&ball1, &game, &player1, &player2);
            }   

                

            EndDrawing();
        }
    CloseWindow();
    return 0;
}
