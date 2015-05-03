
#pragma once
#include "gameobject.h"

class World;
class Persona;

class Missile : public GameObject {
public:
    Missile(int type, GameObject *other, World *world);

public:
    void setPos(int x, int y);
    void setAngle(float angle);
    void setAngle(int x, int y);
    void setSpeed(float speed);
    void move(float length);

virtual void draw();
virtual bool update(int timeElapsed_ms, int wt, int ht);

private:
    clan::Sprite spriteMissile;
    clan::Sprite spriteExplosion;

    clan::Sprite sprite;
    clan::CollisionOutline collisionMissile;
    GameObject* attackObj;
    
    float angle;
    float speed;
    float posX;
    float posY;
    int range;
    int damage;
    bool exploding;
};
