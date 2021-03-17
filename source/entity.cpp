#include "entity.h"

std::vector<Entity> entities = std::vector<Entity>();

Entity::Entity(float _xPos, float _yPos, float _width, float _height, Color _color){
    xPos = _xPos;
    yPos = _yPos;
    width = _width;
    height = _height;
    color = _color;
}

void Entity::Draw(){
    Rectangle rec = {xPos, yPos, width, height};
    DrawRectangleRounded(rec, .15, 10, RED);
}


void CreateEntity(){
    int randX = ((int)(rand() % GetScreenWidth()) / 30) * 30;
    int randY = ((int)(rand() % GetScreenHeight()) / 30) * 30;
    Entity e = Entity(randX, randY, 30, 30, MAROON);
    entities.push_back(e);
}

void DrawEntites(){
    for(int i = 0; i < static_cast<int>(entities.size()); i++){
        entities[i].Draw();
    }
}

bool CheckEntityCollisions(int _xPos, int _yPos){
    for(int i = 0; i < static_cast<int>(entities.size()); i++){
        if(entities[i].xPos == _xPos && entities[i].yPos == _yPos){
            entities.erase(entities.begin() + i);
            CreateEntity();
            return true;
        }
        
    }
    return false;
}