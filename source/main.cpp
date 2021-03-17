#include "../include/raylib.h"
#include <iostream>
#include "../include/snake.h"
#include "../include/entity.h"
#include "string"

void DrawBorder(){
    DrawRectangle(0, 0, GetScreenWidth(), 15, BLACK);
    DrawRectangle(GetScreenWidth()-15, 0, 15, GetScreenHeight() , BLACK);
    DrawRectangle(0, 0, 15, GetScreenHeight(), BLACK);
    DrawRectangle(0, GetScreenHeight()-15, GetScreenWidth(), 15, BLACK);
}

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 600;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Snake");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    SnakeManager snakeManager = SnakeManager();

    int desiredEntityCount = 1;
    for(int i = 0; i < desiredEntityCount; i++){
        CreateEntity();
    }

    float dt = 0;
    float timeElapsed = 0;


    //--------------------------------------------------------------------------------------

    // Main game loop

    SnakeHead& snakeHead = snakeManager.snakeHead;
    int score = 0;
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        dt = GetFrameTime();
        timeElapsed += dt;
        int numBodyPieces = static_cast<int>(snakeManager.snakePieces.size());

        snakeHead.Inputs();

        if(timeElapsed > 0.2){
            switch(snakeHead.yVel){
                case 0:
                    if(snakeHead.xVel == 1){
                        snakeManager.headMovements.push_back(0);
                    }
                    else if(snakeHead.xVel == -1){
                        snakeManager.headMovements.push_back(2);
                    }
                    break;
                default:
                    break;
            }
            switch(snakeHead.xVel)
            {
                case 0:
                    if(snakeHead.yVel == 1){
                        snakeManager.headMovements.push_back(3);
                    }
                    else if(snakeHead.yVel == -1){
                        snakeManager.headMovements.push_back(1);
                    }
                    break;
                default:
                    break;
            }

            snakeHead.MovePiece();
            for(int i = 0; i < numBodyPieces; i++){
                float movement = static_cast<int>(snakeManager.headMovements.size())-i-2;

                switch(snakeManager.headMovements[movement])
                {
                    case 0:
                        snakeManager.snakePieces[i].xVel = 1;
                        snakeManager.snakePieces[i].yVel = 0;
                        break;
                    case 1:
                        snakeManager.snakePieces[i].xVel = 0;
                        snakeManager.snakePieces[i].yVel = -1;
                        break;
                    case 2:
                        snakeManager.snakePieces[i].xVel = -1;
                        snakeManager.snakePieces[i].yVel = 0;
                        break;
                    case 3:
                        snakeManager.snakePieces[i].xVel = 0;
                        snakeManager.snakePieces[i].yVel = 1;
                        break;
                    default:
                        break;
                }
                
                snakeManager.snakePieces[i].MovePiece();
            }

            snakeManager.CheckCollision();
            if(CheckEntityCollisions(snakeHead.xPos, snakeHead.yPos)){
                snakeManager.CreateSnakePiece();
                score++;
            }
            timeElapsed = 0;
        }
        BeginDrawing();
        ClearBackground(WHITE);
        std::string scoreChar = std::to_string(score);
        char const* pchar = scoreChar.c_str();
        DrawText(pchar, 230, 170, 300, RAYWHITE);
        
        DrawEntites();
        snakeManager.snakeHead.DrawPiece();
        for(int i = 0; i < numBodyPieces; i++){
            snakeManager.snakePieces[i].DrawPiece();
        }
        EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context

    return 0;
}