
#ifndef PONG_H
#define PONG_H

#define WIN_SCORE 3

#include <raylib.h>

//Ball blueprint lies here
typedef struct {
    int x;
    int y;
    int velocity_x;
    int velocity_y;
    float radius;
} Ball;

typedef enum {
    VS_PLAYER = 1,
    VS_CPU = 2
} GameMode;

typedef enum {
    EASY = 1,
    MEDIUM = 2,
    HARD = 3
} Difficulty;

//Paddle Blueprint
typedef struct {
    int x;
    int y;
    int width;
    int height;
    int velocity_y; //as paddle's movement is only along y-axis
    int score; //doesn't represent a physical entity of the Paddle but each player has their own Paddle and likewise its unique too
    char name[20]; // Allows name upto 19 characters
} Paddle;

void UpdateBall(Ball *b, int screenWidth, int screenHeight);
void UpdatePlayer1(Paddle *player1, int screenHeight);
void UpdatePlayer2(Paddle *player2, int screenHeight);
void UpdateAI(Paddle *ai, Ball *b, int screenHeight, int difficulty);
void CheckCollisions(Ball *b, Paddle *player1, Paddle *player2, Sound hitSound);
void ResetBall(Ball *b, int screenWidth, int screenHeight);

#endif