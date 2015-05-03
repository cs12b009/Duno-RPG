
#include "precomp.h"

#include "building.h"
#include "world.h"
#include "string.h"
//make another class building with size parameter. size(height,width); put size.h in precomp.
//collisionBuilding = clan::CollisionOutline("Gfx/helipad.png",size,clan::OutlineAccuracy::accuracy_high);
Building::Building(BuildingType buiding_type, World *world)
: GameObject(world)
{
	clan::Canvas canvas = world->get_canvas();

	switch(buiding_type)
	{
	case WALL:

		//world->bkg = clan::XMLResourceManager::create(clan::XMLResourceDocument("resources.xml"));
		//collisionBuilding = clan::CollisionOutline("Gfx/wall.png");
                //collisionBuilding = clan::CollisionOutline("Gfx/wall.png",size,clan::OutlineAccuracy::accuracy_high);
                //const std::vector< Contour > contours;
                //collisionBuilding = clan::CollisionOutline(contours,size,clan::OutlineAccuracy::accuracy_high);
                sprite = clan::Sprite::resource(canvas,"wall", world->resources);
                collisionBuilding = clan::CollisionOutline("Gfx/wall.png",128,clan::accuracy_raw);
		collisionBuilding.set_alignment(clan::origin_center);
		break;
	}
	
	exploding = false;
}

Building::~Building()
{

}

void Building::setPos(int x, int y)
{
	posX = (float)x;
	posY = (float)y;
	collisionBuilding.set_translation(posX, posY);
}

void Building::setAngle(float newAngle)
{
	angle = newAngle;
	sprite.set_angle(clan::Angle(angle, clan::angle_degrees));
	collisionBuilding.set_angle(clan::Angle(angle, clan::angle_degrees));
}

void Building::draw()
{
	
	clan::Canvas canvas = world->get_canvas();
     
	sprite.draw(canvas, posX  , posY );
        collisionBuilding.set_translation(posX, posY);
        //setPos(posX + cursor_pt.x, posY + cursor_pt.y);

}

bool Building::update(int timeElapsed_ms, int wt, int ht)
{

	sprite.update(timeElapsed_ms);
        if(ht!=currentY) {
        posY -= (ht-currentY);
            currentY=ht;
        }

        if(wt!=currentX) {
        posX -= (wt-currentX);
            currentX=wt;
        }
	return true;
}

bool Building::hitCheck(clan::CollisionOutline &outline)
{
	return collisionBuilding.collide(outline);
}
