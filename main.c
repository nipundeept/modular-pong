#include "pong.h"
#include <stdio.h> // to take input names from the user in the terminal before entering the battle

//Built-in functions of Raylib :
/*DrawCirle(myball.x, myball.y, myball.radius, white);
 *DrawRectangle(myPaddle.x, myPaddle.y, mypaddle.width, myPaddle.height, WHITE);
 *
 **/

int main(void) {

    Paddle player1;
    Paddle player2;
    // Pre-game terminal setup
    player1.score = 0;
    player2.score = 0;
    GameMode gameMode;
    Difficulty aiDifficulty;

    printf("=========================\n");
    printf("   WELCOME TO PONG BALL   \n");
    printf("=========================\n");
    printf("Select Game Mode:\n");
    printf("1: VS PLAYER\n");
    printf("2: VS CPU\n");
    printf("Choice (1 or 2): ");
    scanf("%i", &gameMode);

    if (gameMode == 1) {
        printf("\n--- VS PLAYER MODE ---\n");
        printf("Enter Player 1 Name (No spaces): ");
        scanf("%19s", player1.name);
        printf("Enter Player 2 Name (No spaces): ");
        scanf("%19s", player2.name);
    }
    else if (gameMode == 2) {
        printf("\n--- VS CPU MODE ---\n");
        printf("Enter Player Name (No spaces): ");
        scanf("%19s", player1.name);

        // Automatically set Player 2's name to "CPU"
        sprintf(player2.name, "CPU");

        printf("Select CPU Difficulty:\n");
        printf("1: Easy\n");
        printf("2: Medium\n");
        printf("3: Hard\n");
        printf("Choice (1, 2, or 3): ");
        scanf("%i", &aiDifficulty);
    }
    else {
        // Fallback just in case the user types something weird
        printf("Invalid choice! Defaulting to VS PLAYER.\n");
        gameMode = 1;
        sprintf(player1.name, "Player1");
        sprintf(player2.name, "Player2");
    }

    printf("\nStarting game engine...\n");


    //Initialising screen
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Pong Ball");
    InitAudioDevice();
    Sound hitSound = LoadSound("hit.wav");
    Sound victorySound = LoadSound("victory.wav");
    Music bgMusic = LoadMusicStream("retro_bgm.mp3");

    PlayMusicStream(bgMusic);

    SetTargetFPS(60); //loop runs 60 times in a second.

    //Struct instances here
    Ball myBall;
    myBall.x = 400;
    myBall.y = 225;
    myBall.radius = 10.0f;
    myBall.velocity_x = 6;
    myBall.velocity_y = 6;


    player1.x = 10;
    player1.y = screenHeight / 2 - 50;
    player1.width = 10;
    player1.height = 100;
    player1.velocity_y = 7;

    player2.x = 780;
    player2.y = screenHeight / 2 - 50;
    player2.width = 10;
    player2.height = 100;
    player2.velocity_y = 7;

    typedef enum {
        PLAYING,
        GAME_OVER,
        PAUSED
    } GameState;
    //setting the initial state
    GameState currentState = PLAYING;
    int winner = 0;

    while (!WindowShouldClose()) { //Detect window close button or ESC Button triggered.
        UpdateMusicStream(bgMusic);
        if (IsKeyPressed(KEY_P)) {
            if (currentState == PLAYING) currentState = PAUSED;
            else if (currentState == PAUSED) currentState = PLAYING;
        }
        if (currentState == PLAYING) {
            UpdateBall(&myBall, screenWidth, screenHeight);
            UpdatePlayer1(&player1, screenHeight);
            //check the game mode to decide who will play as Player 2
            if (gameMode == VS_PLAYER) { //Human vs. human mode
                UpdatePlayer2(&player2, screenHeight);
            }
            else if (gameMode == VS_CPU) { //Human vs. CPU
                UpdateAI(&player2, &myBall, screenHeight, aiDifficulty);
            }
            CheckCollisions(&myBall, &player1, &player2, hitSound);
            // Update logic (move ball, check keys, etc.)
            // Check if ball went past Left Wall (Player 2 scores!)
            if (myBall.x + myBall.radius < 0) {
                player2.score++;
                ResetBall(&myBall, screenWidth, screenHeight);
            }

            // Check if ball went past Right Wall (Player 1 scores!)
            if (myBall.x - myBall.radius > screenWidth) {
                player1.score++;
                ResetBall(&myBall, screenWidth, screenHeight);
            }
            //checking for victory
            if (player1.score >= WIN_SCORE) {
                winner = 1;
                currentState = GAME_OVER;
                StopMusicStream(bgMusic);
                PlaySound(victorySound);
            }
            else if (player2.score >= WIN_SCORE) {
                winner = 2;
                currentState = GAME_OVER;
                StopMusicStream(bgMusic);
                PlaySound(victorySound);
            }
        }
        else if (currentState == GAME_OVER) {
            //listen for space bar to restart the game
            if (IsKeyPressed(KEY_SPACE)) {
                player1.score = player2.score = 0; //score gets reset
                ResetBall(&myBall, screenWidth, screenHeight); //reset ball to the centre
                currentState = PLAYING;
                StopSound(victorySound);
                PlayMusicStream(bgMusic);
            }
        }
        //-----------------------------
        //Drawing here
        BeginDrawing();
         ClearBackground(BLACK); //wipe the screen clear every frame
        // Draw the dotted center line (The Net)
         if (currentState == PLAYING) {
             for (int i = 0; i < screenHeight; i += 30) {
                 DrawRectangle(screenWidth / 2 - 2, i, 4, 15, LIGHTGRAY);
             }
             DrawCircle(myBall.x, myBall.y, myBall.radius, WHITE);
             DrawRectangle(player1.x, player1.y, player1.width, player1.height, WHITE);
             DrawRectangle(player2.x, player2.y, player2.width, player2.height, WHITE);
             DrawText(TextFormat("%s: %i", player1.name, player1.score), 20, 20, 20, WHITE);
             DrawText(TextFormat("%s: %i", player2.name, player2.score), screenWidth - 200, 20, 20, WHITE);
         }
        else if (currentState == GAME_OVER) {
            if (winner == 1) {
                DrawText(TextFormat("%s WINS!", player1.name), screenWidth/2 - 150, screenHeight/2 - 50, 40, WHITE);
            } else {
                DrawText(TextFormat("%s WINS!", player2.name), screenWidth/2 - 150, screenHeight/2 - 50, 40, WHITE);
            }
            //(int)(GetTime() * 2) changes between even and odd every half-second
            if (((int)(GetTime() * 2)) % 2 == 0) {
                DrawText("Press SPACE to Restart", screenWidth/2 - 140, screenHeight/2 + 20, 20, LIGHTGRAY);
            }

        }
        else if (currentState == PAUSED) {
            DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.5f));
            DrawText("PAUSED", screenWidth/2 - 80, screenHeight/2 - 20, 40, WHITE);
        }
        EndDrawing();
    }

    UnloadSound(hitSound);
    UnloadSound(victorySound);
    UnloadMusicStream(bgMusic);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}