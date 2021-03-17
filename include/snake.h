#ifndef SNAKE_H
#define SNAKE_H
#include "../include/raylib.h"
#include <vector>

class SnakePiece {
public:
    int xVel;
    int yVel;
    float xPos;
    float yPos;
    float width;
    float height;

    bool hasChosenDir;
    SnakePiece(){}
    SnakePiece(float _xPos, float _yPos, float _width, float _height);
    

    void DrawPiece();
    void MovePiece();
};

class SnakeHead : public SnakePiece {
public:
    SnakeHead(){};
    using SnakePiece::SnakePiece;
    void Inputs();
};

class SnakeManager{
public:
    SnakeManager();

    std::vector<int> headMovements;
    std::vector<SnakePiece> snakePieces;
    SnakeHead snakeHead;

    void DrawPieces();

    void CreateSnakePiece();

    void CheckCollision();
};
#endif
