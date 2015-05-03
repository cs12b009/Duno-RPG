#pragma once
#include "persona.h"

class Creep : public Persona {
    
    // init
public:
    Creep(PersonaType type, World *world);
    
private:
    int habitatRange;
    float habitatX, habitatY;
};
