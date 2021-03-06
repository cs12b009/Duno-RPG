
#include "precomp.h"

#include "persona.h"
#include "world.h"
#include "missile.h"

Persona::Persona(PersonaType type, World *world) : GameObject(world) {
    clan::Canvas canvas = world->get_canvas();
    
    selected = false;
    followStance = false;
    hitStance = false;
    isRange = false;
    thepointer = 0;
    currentPos(0,0);
    attackRange = 100;
    heroType = type;
    maxHealth = health = 1000;
    maxMana = mana = 500;
    damage = 100;
    
    HealthBar = clan::Image::resource(canvas, "Health", world->resources);
    Health = clan::Image::resource(canvas, "health", world->resources);
    ManaBar = clan::Image::resource(canvas, "Health", world->resources);
    Mana = clan::Image::resource(canvas, "mana", world->resources);
    
    switch(type) {
        case GEN_MAX:
            spriteBodyStill = clan::Sprite::resource(canvas, "GenBodyStill", world->resources);
            spriteBodyMovingLeft = spriteBodyMovingUp = spriteBodyMovingDown = 
                spriteBodyMoving = clan::Sprite::resource(canvas, "GenBodyMoving", world->resources);
            spriteSelected = clan::Sprite::resource(canvas, "GenBodySelected", world->resources);
            
            collisionBody = clan::CollisionOutline("Gfx/ash_selected.png");
            collisionBody.set_alignment(clan::origin_center);
            
            moveSpeed = 100.0f;
            
            break;
        case STAINER:
            spriteBodyStill = clan::Sprite::resource(canvas, "StainerBodyStill", world->resources);
            spriteBodyMovingLeft = spriteBodyMoving = clan::Sprite::resource(canvas, "StainerBodyMoving", world->resources);
            spriteSelected = clan::Sprite::resource(canvas, "GenBodySelected", world->resources);
            spriteAttack = clan::Sprite::resource(canvas, "StainerBodyAttacking", world->resources);
            spriteBodyMovingLeft = clan::Sprite::resource(canvas, "StainerBodyMovingLeft", world->resources);
            spriteBodyMovingUp = clan::Sprite::resource(canvas, "StainerBodyMovingUp", world->resources);
            spriteBodyMovingDown = clan::Sprite::resource(canvas, "StainerBodyMovingDown", world->resources);
            
            collisionBody = clan::CollisionOutline("Gfx/stainer/stainer_still.png");
            collisionBody.set_alignment(clan::origin_center);
            isRange = true;
            
            moveSpeed = 50.0f;
            attackRange = 200;
            
            break;
        case GANYMEDE:
            spriteBodyStill = clan::Sprite::resource(canvas, "GanymedeBodyStill", world->resources);
            spriteBodyMovingLeft = spriteBodyMovingUp = spriteBodyMovingDown = 
                spriteBodyMoving = clan::Sprite::resource(canvas, "GanymedeBodyMoving", world->resources);
            spriteSelected = clan::Sprite::resource(canvas, "GenBodySelected", world->resources);
            spriteAttack = clan::Sprite::resource(canvas, "GanymedeBodyAttacking", world->resources);
            
            collisionBody = clan::CollisionOutline("Gfx/gany/gany_still1.png");
            collisionBody.set_alignment(clan::origin_center);
            isRange = false;
            
            moveSpeed = 80.0f;
            attackRange = 50;
    }
    
    spriteBody = spriteBodyStill;
}

void Persona::setPos(int x, int y) {
    posX = destPosX = (float)x;
    posY = destPosY = (float)y;
    
    collisionBody.set_translation(posX,posY);
}

void Persona::getPos(int &x, int &y) {
    x = posX;
    y = posY;
}

void Persona::currentPos(int x, int y) {
    currentX = (float)x;
    currentY = (float)y;
    
    // collisionBody.set_translation(posX,posY);
}

void Persona::setTargetPos(int x, int y) {
    destPosX = (float)x;
    destPosY = (float)y;
    
    clan::Vec2f vector(posX - destPosX, posY - destPosY);
    
    vector.normalize();
    deltaPosX = -vector.x;
    deltaPosY = -vector.y;
    if(deltaPosX <0.4 && deltaPosX >-0.4) {
        if(deltaPosY >0)
            spriteBody = spriteBodyMovingDown;
        else
            spriteBody = spriteBodyMovingUp;
    }
    else if(deltaPosX<0)
        spriteBody = spriteBodyMovingLeft;
    else
        spriteBody = spriteBodyMoving;
}

void Persona::setTargetPos(GameObject *other) {
    followStance = true;
    followObj = other;
}

void Persona::reduceHealth(int x) {
    health -= x;
}

void Persona::hitTarget(GameObject *other) {
    int x,y;
    other->getPos(x,y);
    
    hitStance = true;
    if(!isRange)        // meele attacks
        spriteBody = spriteAttack;
    else {
        Missile *missile = new Missile(heroType,followObj,world);
        missile->setPos(posX,posY);
        missile->setAngle(x,y);
        world->addGameObject(missile);
    }
}

bool Persona::isSelected() const {
    return selected;
}

bool Persona::enemyCheck(GameObject *other) {
    Persona *p1 = (Persona*) other;
    if((p1->sentinal && sentinal) || (p1->scourge  && scourge))
        return false;
    return true;
}

void Persona::clearFollow() {
    followStance = false;
}

void Persona::select() {
    selected = true;
}

void Persona::deselect() {
    selected = false;
}

bool Persona::hitCheck(clan::CollisionOutline &outline) {
    return collisionBody.collide(outline);
}

bool Persona::hitCheck(int x, int y) {
    int width = spriteBody.get_width();
    int height = spriteBody.get_height();
    
    return (x >= posX - width / 2 && x <= posX + width / 2
            && y >= posY - height / 2 && y <= posY + height / 2);
}

bool Persona::update(int timeElapsed_ms, int wt, int ht) {
    spriteBody.update(timeElapsed_ms);
    int x,y;
    int tempx,tempy,temp2x,temp2y;
    int flag=0,flag1=0;
    std::list<GameObject *>::iterator it;
    for(it = world->gameobjects.begin(); it != world->gameobjects.end(); ++it)
    {
      
      if((*it)->hitCheck(this->collisionBody) && (*it)!=this  && thepointer==0 )
        {       
          thepointer=1;
          collisionBody.set_translation(posX,posY);
          //this->setTargetPos(key.mouse_pos.x, key.mouse_pos.y);
          destPosY=posY;
          destPosX=posX;
          spriteBody = spriteBodyStill;

          return true;
        }
    }
    tempx=posX;
    tempy=posY;
    temp2x=destPosX;
    temp2y=destPosY;
 
    if(ht!=currentY) {
       posY -= (ht-currentY);
       destPosY -= (ht-currentY);
        currentY=ht;
    }

    if(wt!=currentX) {
       posX -= (wt-currentX);
       destPosX -= (wt-currentX);
        currentX=wt;
    }

    if(hitStance && spriteAttack.is_looping()) {
        hitStance = false;      //end hit stance start follow stance
        followStance = true;
        followObj->reduceHealth(damage);
        if(isRange) {

        }
    }
    
    if(followStance) {
        followObj->getPos(x,y);
        clan::Vec2f vector(posX-x,posY-y);
        if(vector.length() < attackRange+1) {
            if(!enemyCheck(followObj))
                followStance = false;
            else {
                hitTarget(followObj);
                destPosX = posX; destPosY = posY;
                followStance = false;
            }
        }
        else {
            vector.normalize();
            setTargetPos( x + (attackRange*vector.x),
                          y + (attackRange*vector.y));
        }
    }
    
    if(destPosX != posX || destPosY != posY) {
        posX += deltaPosX * moveSpeed * timeElapsed_ms /1000;
        posY += deltaPosY * moveSpeed * timeElapsed_ms /1000;
        
        if((deltaPosX > 0 && posX >= destPosX) || (deltaPosX < 0 && posX <= destPosX)
            || (deltaPosY > 0 && posY >= destPosY) ||
            (deltaPosY < 0 && posY <= destPosY)) {
            posX = destPosX;
            posY = destPosY;
        }
        
        if(posX == destPosX && posY == destPosY)
            spriteBody = spriteBodyStill;
    }
    collisionBody.set_translation(posX,posY);
    for(it = world->gameobjects.begin(); it != world->gameobjects.end(); ++it)
    {
      
      if((*it)->hitCheck(this->collisionBody) && (*it)!=this)flag=1;
    }
    if(flag==1 && (destPosX != posX || destPosY != posY))
    {
      posX=tempx;
      posY=tempy;
      destPosX=tempx;
      destPosY=tempy;
      collisionBody.set_translation(posX,posY);
      spriteBody = spriteBodyStill;
    }
    else if(flag==0)
      thepointer=0;
    return true;
}

void Persona::draw() {
    clan::Canvas canvas = world->get_canvas();
    
    if(selected)
        spriteSelected.draw(canvas, posX, posY);
        
    //Health Bar
    HealthBar.draw(canvas, posX-HealthBar.get_width()/2, posY - 30);
    ManaBar.draw(canvas, posX-ManaBar.get_width()/2, posY - 40);
    float len = ((float)health/maxHealth)*HealthBar.get_width();
    for(int i = 0; i < (int)len; i++){
    	Health.draw(canvas, posX-HealthBar.get_width()/2 + i, posY - 31);
    }
    len = ((float)mana/maxMana)*ManaBar.get_width();
    for(int i = 0; i < len; i++){
    	Mana.draw(canvas, posX - ManaBar.get_width()/2 + i, posY - 41);
    }
    
    //shadow for body
    canvas.set_blend_state(world->blendstate_cl_blend_zero_cl_blend_one_minus_src_alpha);
    spriteBody.set_alpha(0.5f);
    spriteBody.draw(canvas, posX + 5, posY + 5);
    
    // Draw body
    canvas.set_blend_state(world->blendstate_cl_blend_src_alpha_cl_blend_one_minus_src_alpha);
    spriteBody.set_alpha(1.0f);
    spriteBody.draw(canvas, posX, posY);
}
