#include "pong.h"

void UpdateBall(Ball *b, int screenWidth, int screenHeight) {
    //Move the ball by adding velocity to its components
    b->x += b->velocity_x; //dereferencing variable x from the struct b and adding the ball velocity in its own direction
    b->y += b->velocity_y;

    //check collision with top wall
    if (b->y - b->radius <= 0) {
        b->y = b->radius; //make it back to the edge so that it doesn't get stuck
        b->velocity_y *= -1; //reverse the velocity
    }
    //check collision with bottom wall
    if (b->y + b->radius >= screenHeight) {
        b->y = screenHeight - b->radius;
        b->velocity_y *= -1;
    }
}

void UpdatePlayer1(Paddle *player1, int screenHeight) {
    //check input and move
    if (IsKeyDown(KEY_W)) {
        player1->y -= player1->velocity_y;
    }
    if (IsKeyDown(KEY_S)) {
        player1->y += player1->velocity_y;
    }
    //check bounds of the paddle(if it goes beyond the screen, make it upto that level)
    if (player1->y <= 0) {
        player1->y = 0; //snaps to the top of the screen
    }
    if (player1-> y + player1->height >= screenHeight) {
        player1->y = screenHeight - player1->height;
    }
}

void UpdatePlayer2(Paddle *player2, int screenHeight) {
    //same as the update section of player1, here we use arrow keys to trigger the movement
    if (IsKeyDown(KEY_UP)) {
        player2->y -= player2->velocity_y;
    }
    if (IsKeyDown(KEY_DOWN)) {
        player2->y += player2->velocity_y;
    }
    //checking the boundary conditions of the paddle
    if (player2->y <= 0) {
        player2->y = 0; //snaps to the top of the screen
    }
    if (player2-> y + player2->height >= screenHeight) {
        player2->y = screenHeight - player2->height;

    }
}

void UpdateAI(Paddle *ai, Ball *b, int screenHeight, int difficulty) {
    int aiSpeed = 0;
    if (difficulty == EASY) {
        aiSpeed = 3;
    }
    else if (difficulty == MEDIUM) {
        aiSpeed = 5;
    }
    else if (difficulty == HARD) {
        aiSpeed = 8;
    }
    if (b->y < ai->y + (ai->height / 2)) {
        ai->y -= aiSpeed; //Ball is above, move up
    }
    if (b->y > ai->y + (ai->height / 2)) {
        ai->y += aiSpeed; //Ball is below, move down
    }
    if (ai->y <= 0) ai->y = 0;
    if (ai->y + ai->height >= screenHeight) ai->y = screenHeight - ai->height;
}

void CheckCollisions(Ball *b, Paddle *p1, Paddle *p2, Sound hitSound) {
    /*for collision detection of ball with either of the paddles, we can use Raylib's inbuilt collision detection function of Circle and Rectangle
     *but for that the function expects user to input ball Vector and Rectangle, so we convert our data into those instances
     */
    Vector2 ballCenter = {(float) b -> x, (float) b -> y};
    Rectangle recP1 = {
        (float) p1 -> x,
        (float) p1 -> y,
        (float) p1 -> width,
        (float) p1 -> height
    };
    Rectangle recP2 = {
        (float) p2 -> x,
        (float) p2 -> y,
        (float) p2 -> width,
        (float) p2 -> height
    };
    if (CheckCollisionCircleRec(ballCenter, b->radius, recP2)) {
        b->velocity_x *= -1; // Bounce!
        b->x = p2->x - (int)b->radius;
        PlaySound(hitSound);
    }
    //check collision with Paddle1. (left player)
    if (CheckCollisionCircleRec(ballCenter, b->radius, recP1)) {
        b->velocity_x *= -1; //invert the velocity in x direction, so that the position now decreases towards the left
        b->x = p1->x + p1->width + (int) b->radius;
        PlaySound(hitSound);
    }
}

void ResetBall(Ball *b, int screenWidth, int screenHeight) {
    b->x = screenWidth / 2;
    b->y = screenHeight / 2;
    b->velocity_x *= -1;
    b->velocity_y = (GetRandomValue(0, 1) == 0) ? -5 : 5; // randomizing the y-direction, so that it becomes unpredictable

}

