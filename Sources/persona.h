
#pragma once
#include "gameobject.h"

class World;

class Persona : public GameObject {
    //Each type
public:
    enum PersonaType {
        GEN_MAX,
        STAINER,
        GANYMEDE
    };
    
    //init
public:
    Persona(PersonaType type, World *world);
    
    //Attributes
public:
    bool isSelected() const;
    bool sentinal;
    
    //Operations
public:
    void getPos(int &x, int &y);
    void setPos(int x,int y);
    void currentPos(int x, int y);
    void setTargetPos(int x,int y);
    void setTargetPos(GameObject *other);
    void hitTarget(GameObject *other);
    bool enemyCheck(GameObject *other);
    void select();
    void deselect();
    void clearFollow();
    bool hitCheck(clan::CollisionOutline &outline, GameObject *other);
    bool hitCheck(int x,int y);
    
    virtual void draw();
    virtual bool update(int timeElapsed_ms, int wt, int ht);
    
    //Attributes visible
private:
    int experience;
    int gold;

    float baseHealthRegen;
    float baseManaRegen;
    int maxHealth;
    int maxMana;
    int health;
    int mana;
    
    short agility;
    short strength;
    short intelligence;
    short armor;
    short damage;
    
    int attackRange;
    int attackSpeed;
    float moveSpeed;

    //Attributes hidden
private:
    clan::Sprite spriteBody;
    clan::Sprite spriteBodyStill;
    clan::Sprite spriteBodyMoving;
    clan::Sprite spriteSelected;
    clan::Sprite spriteAttack;
    
    clan::CollisionOutline collisionBody;
    GameObject *followObj;

    float posX, posY;
    float destPosX, destPosY;
    float deltaPosX, deltaPosY;
    float currentX, currentY;
    
    bool selected;
    bool followStance;
    bool hitStance;
};
