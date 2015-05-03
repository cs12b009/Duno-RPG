
#include "precomp.h"

#include "creep.h"
#include "persona.h"
#include "world.h"

Creep::Creep(PersonaType type, World *world) : Persona(type, world) {
    clan::Canvas canvas = world->get_canvas();
    
    selected = false;
    sentinal = false;
    scourge = false;
    
    HealthBar = clan::Image::resource(canvas, "Health", world->resources);
    Health = clan::Image::resource(canvas, "health", world->resources);
    ManaBar = clan::Image::resource(canvas, "Health", world->resources);
    Mana = clan::Image::resource(canvas, "mana", world->resources);
    
    switch(type) {
        case TYPE1:
            spriteBodyStill = clan::Sprite::resource(canvas, "Neutral1Still", world->resources);
            spriteBodyMovingLeft = spriteBodyMovingUp = spriteBodyMovingDown = 
                spriteBodyMoving = clan::Sprite::resource(canvas, "Neutral1Moving", world->resources);
            spriteSelected = clan::Sprite::resource(canvas, "GenBodySelected", world->resources);
            spriteAttack = clan::Sprite::resource(canvas, "Neutral1Attacking", world->resources);
            spriteDeath = clan::Sprite::resource(canvas, "Neutral1Death", world->resources);
            
            collisionBody = clan::CollisionOutline("Gfx/neutral/neutral1_still.png");
            collisionBody.set_alignment(clan::origin_center);
            
            break;
    }
    
    spriteBody = spriteBodyStill;
}