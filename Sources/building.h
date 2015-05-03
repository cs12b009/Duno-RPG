#pragma once

#include "gameobject.h"

class Building : public GameObject
{
// Enums
public:
	enum BuildingType
	{
		WALL
	};

// Construction
public:
	Building(BuildingType building_type, World *world);
	~Building();
	
// Attributes
public:
	
// Operations
public:
	void setPos(int x, int y);
	void setAngle(float angle);
	virtual void draw();
	//virtual void draw2(clan::Point cursor_pt);
	virtual bool update(int timeElapsed_ms, int wt, int ht);
	virtual bool hitCheck(clan::CollisionOutline &outline);

// Implementation:
private:
	clan::Sprite sprite;
        clan::CollisionOutline collisionBuilding;
	
	float angle;	
	float posX;
	float posY;
	float currentX;
	float currentY;

	bool exploding;
};

