#pragma once
class World;

class GameObject {
    //construction
public:
    GameObject(World *world) {this->world = world; }
    
    //operations
public:
    virtual void draw() {};
    virtual void getPos(int &x, int &y) {};
    virtual void setPos(int x,int y) {};
    virtual bool update(int timeElapsed_ms, int wt, int ht) { return false; }
    virtual bool hitCheck(clan::CollisionOutline &outline) { return false; }
protected:
    World *world;
};
