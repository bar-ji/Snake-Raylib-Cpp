#include "snake.h"
#include <iostream>

bool hasChosenDir = false;

SnakePiece::SnakePiece(float _xPos, float _yPos, float _width, float _height){
    xPos = _xPos;
    yPos = _yPos;
    width = _width;
    height = _height;
}

void SnakePiece::DrawPiece(){
    Rectangle rec = {xPos, yPos, width, height};
    DrawRectangleRounded(rec, .15, 10, BEIGE);
}

//1
void SnakePiece::MovePiece(){
    switch(xVel)
    {
        case 1:
            xPos += 30;
            break;
        case -1:
            xPos -= 30;
            break;
        default:
            break;
    }
    switch(yVel)
    {
        case 1:
            yPos -= 30;
            break;
        case -1:
            yPos += 30;
            break;
        default:
            break;

    }
    hasChosenDir = false;
}

void SnakeHead::Inputs(){
    if(hasChosenDir) return;
    switch(xVel){
        case 0:
            if(IsKeyDown(KEY_D)){
                xVel = 1;
                yVel = 0;
                hasChosenDir = true;
                break;
            }
            else if(IsKeyDown(KEY_A)){
                xVel = -1;
                yVel = 0;
                hasChosenDir = true;
                break;
            }
        default:
            break;
    }
    switch(yVel)
    {
        case 0:
            if(IsKeyDown(KEY_W)){
                xVel = 0;
                yVel = 1;
                hasChosenDir = true;
                break;
            }
            else if(IsKeyDown(KEY_S)){
                xVel = 0;
                yVel = -1;
                hasChosenDir = true;
                break;
            }
        default:
            break;
    }
}

SnakeManager::SnakeManager(){
    SnakeManager::snakeHead = SnakeHead(GetScreenWidth() / 2, GetScreenHeight() / 2, 30, 30);
    snakeHead.xVel = 1;
}


void SnakeManager::DrawPieces(){
    snakeHead.DrawPiece();
    for(int i = 0; i < static_cast<int>(snakePieces.size()); i++){
        snakePieces[i].DrawPiece();
    }
}

void SnakeManager::CreateSnakePiece(){
    int xPos = 0;
    int yPos = 0;
    SnakePiece previousSnake = snakeHead;
    

    if(static_cast<int>(snakePieces.size() != 0)){
        previousSnake = snakePieces[static_cast<int>(snakePieces.size())-1];
    }

    switch(previousSnake.yVel)
    {
        case 0:
            if(previousSnake.xVel == 1){
                xPos = previousSnake.xPos - 30;
                yPos = previousSnake.yPos;
                break;
            }
            else if(previousSnake.xVel == -1){
                xPos = previousSnake.xPos + 30;
                yPos = previousSnake.yPos;
                break;
            }
        default:
            break;
    }
    switch(previousSnake.xVel)
    {
        case 0:
            if(previousSnake.yVel == 1){
                yPos = previousSnake.yPos + 30;
                xPos = previousSnake.xPos;
                break;
            }
            else if(previousSnake.yVel == -1){
                yPos = previousSnake.yPos - 30;
                xPos = previousSnake.xPos;
                break;
            }
        default:
            break;
    }

    SnakePiece s = SnakePiece(xPos, yPos, 30, 30);
    s.xVel = previousSnake.xVel;
    s.yVel = previousSnake.yVel;
    snakePieces.push_back(s);
}

void SnakeManager::CheckCollision(){
    for(int i = 0; i < static_cast<int>(snakePieces.size()); i++){
        if(snakePieces[i].xPos == snakeHead.xPos && snakePieces[i].yPos == snakeHead.yPos){
            CloseWindow();
        }
    }
    if(snakeHead.xPos >= GetScreenWidth() || snakeHead.xPos <= -30){
        CloseWindow();
    }
    if(snakeHead.yPos >= GetScreenHeight() || snakeHead.yPos <= -30){
        CloseWindow();
    }
}