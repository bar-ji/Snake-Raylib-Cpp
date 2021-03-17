#ifndef ENTITY_H
#define ENTITY_H
#include<vector>
#include<stdlib.h>
#include"../include/raylib.h"

class Entity{
public:
    float xPos;
    float yPos;
    float width;
    float height;
    Color color;

    Entity(float _xPos, float _yPos, float _width, float _height, Color _color);

    void Draw();
};

extern std::vector<Entity> entities;

void CreateEntity();

void DrawEntites();

bool CheckEntityCollisions(int _xPos, int _yPos);

#endif