
#pragma once
#include "gameobject.h"

class World;

class Persona : public GameObject {
    //Each type
public:
    enum PersonaType {
        GEN_MAX
    };
    
    //init
public:
    Persona(PersonaType type, World *world);
    
    //Attributes
public:
    bool isSelected() const;
    
    //Operations
public:
    void getPos(int &x, int &y);
    void setPos(int x,int y);
    void setTargetPos(int x,int y);
    void select();
    void deselect();
    bool hitCheck(clan::CollisionOutline &outline, GameObject *other);
    bool hitCheck(int x,int y);
    
    virtual void draw();
    virtual bool update(int timeElapsed_ms);
    
private:
    clan::Sprite spriteBody;
    clan::Sprite spriteBodyStill;
    clan::Sprite spriteBodyMoving;
    clan::Sprite spriteSelected;
    
    clan::CollisionOutline collisionBody;
    
    float posX, posY;
    float destPosX, destPosY;
    float deltaPosX, deltaPosY;
    float bodyTurnSpeed;
    float moveSpeed;
    
    bool selected;
};
