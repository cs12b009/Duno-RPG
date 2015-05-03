
#include "precomp.h"

#include "missile.h"
#include "persona.h"
#include "world.h"

Missile::Missile(int type, GameObject *other, World *world) : GameObject(world) {
    clan::Canvas canvas = world->get_canvas();
    
    spriteMissile = clan::Sprite::resource(canvas, "Missile", world->resources);
    spriteExplosion = clan::Sprite::resource(canvas, "Explosion", world->resources);
    range = 100;
    exploding = false;
    switch(type) {
        case Persona::STAINER:
            spriteMissile = clan::Sprite::resource(canvas, "Missile", world->resources);
            range = 300;
            speed = 500.0f;
            damage = 100;
            break;
            
    }
    
    sprite = spriteMissile;
    collisionMissile = clan::CollisionOutline("Gfx/stainer_missile.png");
    collisionMissile.set_alignment(clan::origin_center);
    
    attackObj = other;
}

void Missile::setPos(int x,int y) {
    posX = (float)x;
    posY = (float)y;
    collisionMissile.set_translation(posX, posY);
}

void Missile::setAngle(float newAngle) {
    angle = newAngle;
    sprite.set_angle(clan::Angle(angle, clan::angle_degrees));
    collisionMissile.set_angle(clan::Angle(angle, clan::angle_degrees));
}

void Missile::setAngle(int x, int y) {
    clan::Vec2f vector(posX - x, posY - y);
    clan::Vec2f up(0.0f,1.0f);   // j unit vector in Y direction
    
    angle = up.angle(vector).to_degrees();
    if(x < posX)
        angle = 360.0f - angle;
    sprite.set_angle(clan::Angle(angle, clan::angle_degrees));
    collisionMissile.set_angle(clan::Angle(angle, clan::angle_degrees));
}

void Missile::move(float length) {
    posX += length * float(sin(angle * clan::PI / 180.0f));
    posY += length * float(-cos(angle * clan::PI / 180.0f));

    collisionMissile.set_translation(posX, posY);
}

void Missile::draw() {
    clan::Canvas canvas = world->get_canvas();
    sprite.draw(canvas, posX, posY);
}

bool Missile::update(int timeElapsed_ms, int wt, int ht) {
    sprite.update(timeElapsed_ms);
    float timeElapsed = (float) timeElapsed_ms/1000.0f;
    if(exploding) {
        if(sprite.is_finished())
            return false;
    }
    else {
        move(speed * timeElapsed);
        if(attackObj->hitCheck(collisionMissile)) {
            //sound?
            attackObj->reduceHealth(damage);
            sprite = spriteExplosion;
            sprite.set_angle(clan::Angle(0, clan::angle_degrees));
            sprite.set_alpha(0.85f);
            exploding = true;
        }
        range-=10;
    }
    return (range>0);
}