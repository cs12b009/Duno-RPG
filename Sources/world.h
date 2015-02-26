#pragma once

#include <list>

#define MAP_WIDTH 1024
#define MAP_HEIGHT 768

class Surface;
class Edifice;
class Persona;

class World {
    //Constructions
public:
    World(clan::DisplayWindow &display_window);
    ~World();
    
    //Attributes
public:
    clan::ResourceManager resources;
    clan::Canvas get_canvas() { return canvas; }
    
    //Operations
public:
    void initLevel();
    bool hitCheck(clan::CollisionOutline &outline, Edifice *other);
    void addEdifice(Edifice *object);
    void addPersona(Persona *person);
    void run();
    
    //Implementation
private:
    void draw();
    void update(int timeElapsed_ms);
    
    void onKeyDown(const clan::InputEvent &key);
    void onMouseDown(const clan::InputEvent &key);
    void onMouseUp(const clan::InputEvent &key);
    void onMouseMove(const clan::InputEvent &key);
    void on_window_close();
    
    clan::Slot slotMouseDown;
    clan::Slot slotMouseUp;
    clan::Slot slotMouseDblClick;
    clan::Slot slotMouseMove;
    clan::Slot slotKeyDown;
    
    clan::Image game_map;
    
    bool dragging;
    bool mouseDown;
    clan::Rect dragArea;
    float highlightValue;
    
    std::list<Edifice *> edifices;
    std::list<Persona *> persons;
    
    clan::DisplayWindow window;
    clan::Canvas canvas;
    
    bool quit;
    
public:
    clan::BlendState blendstate_cl_blend_zero_cl_blend_one_minus_src_alpha;
    clan::BlendState blendstate_cl_blend_src_alpha_cl_blend_one_minus_src_alpha;
    clan::BlendState blendstate_default;
    
};
