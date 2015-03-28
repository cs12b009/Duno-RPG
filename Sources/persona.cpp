
#include "precomp.h"

#include "persona.h"
#include "world.h"

Persona::Persona(PersonaType type, World *world) : GameObject(world) {
    clan::Canvas canvas = world->get_canvas();
    
    switch(type) {
        case GEN_MAX:
            spriteBodyStill = clan::Sprite::resource(canvas, "GenBodyStill", world->resources);
            spriteBodyMoving = clan::Sprite::resource(canvas, "GenBodyMoving", world->resources);
            spriteSelected = clan::Sprite::resource(canvas, "GenBodySelected", world->resources);
            
            collisionBody = clan::CollisionOutline("Gfx/ash_selected.png");
            collisionBody.set_alignment(clan::origin_center);
            
            moveSpeed = 100.0f;
            
            break;
        case STAINER:
            spriteBodyStill = clan::Sprite::resource(canvas, "StainerBodyStill", world->resources);
            spriteBodyMoving = clan::Sprite::resource(canvas, "StainerBodyMoving", world->resources);
            spriteSelected = clan::Sprite::resource(canvas, "GenBodySelected", world->resources);
            
            collisionBody = clan::CollisionOutline("Gfx/ash_selected.png");
            collisionBody.set_alignment(clan::origin_center);
            
            moveSpeed = 50.0f;
            
            break;
    }
    
    selected = false;
    spriteBody = spriteBodyStill;
}

void Persona::setPos(int x, int y) {
    posX = destPosX = (float)x;
    posY = destPosY = (float)y;
    
    collisionBody.set_translation(posX,posY);
}

void Persona::setTargetPos(int x, int y) {
    destPosX = (float)x;
    destPosY = (float)y;
    
    clan::Vec2f vector(posX - destPosX, posY - destPosY);
    
    vector.normalize();
    deltaPosX = -vector.x;
    deltaPosY = -vector.y;
    spriteBody = spriteBodyMoving;
}

bool Persona::isSelected() const {
    return selected;
}

void Persona::select() {
    selected = true;
}

void Persona::deselect() {
    selected = false;
}

bool Persona::hitCheck(clan::CollisionOutline &outline, GameObject *other) {
    return collisionBody.collide(outline);
}

bool Persona::hitCheck(int x, int y) {
    int width = spriteBody.get_width();
    int height = spriteBody.get_height();
    
    return (x >= posX - width / 2 && x <= posX + width / 2
            && y >= posY - height / 2 && y <= posY + height / 2);
}

bool Persona::update(int timeElapsed_ms) {
    spriteBody.update(timeElapsed_ms);
    
    if(destPosX != posX || destPosY != posY) {
        posX += deltaPosX * moveSpeed * timeElapsed_ms /1000;
        posY += deltaPosY * moveSpeed * timeElapsed_ms /1000;
        
        if((deltaPosX > 0 && posX >= destPosX) || (deltaPosX < 0 && posX <= destPosX)
            || (deltaPosY > 0 && posY >= destPosY) ||
            (deltaPosY < 0 && posY <= destPosY)) {
            posX = destPosX;
            posY = destPosY;
        }
        collisionBody.set_translation(posX,posY);
        if(posX == destPosX && posY == destPosY)
            spriteBody = spriteBodyStill;
    }
    return true;
}

void Persona::draw() {
    clan::Canvas canvas = world->get_canvas();
    
    if(selected)
        spriteSelected.draw(canvas, posX, posY);
    
    //shadow for body
    canvas.set_blend_state(world->blendstate_cl_blend_zero_cl_blend_one_minus_src_alpha);
    spriteBody.set_alpha(0.5f);
    spriteBody.draw(canvas, posX + 5, posY + 5);
    
    // Draw body
    canvas.set_blend_state(world->blendstate_cl_blend_src_alpha_cl_blend_one_minus_src_alpha);
    spriteBody.set_alpha(1.0f);
    spriteBody.draw(canvas, posX, posY);
}