#pragma once

#include <list>

class GameObject;
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
    bool hitCheck(clan::CollisionOutline &outline, GameObject *other);
    void addGameObject(GameObject *object);
    void run();
    
    //Implementation
private:
    void draw();
    void update(int timeElapsed_ms);
    
    void onKeyDown(const clan::InputEvent &key);
    void onMouseClick(const clan::InputEvent &key);
    void onMouseUp(const clan::InputEvent &key);
    void onMouseMove(const clan::InputEvent &key);
    void on_window_close();
    
    clan::Slot slotMouseDown;
    clan::Slot slotMouseUp;
    clan::Slot slotMouseDblClick;
    clan::Slot slotMouseMove;
    clan::Slot slotKeyDown;
    
    clan::Image game_map;
    clan::Image mini_map;
    clan::Image ability1;
    clan::Image ability2;
    clan::Image ability3;
    clan::Image ability4;
    clan::Sprite mini_map_select;
    clan::Sprite mini_dot;
    clan::Point map_zoom_pt;
    
    int xPos;
    int yPos;

    bool dragging;
    bool mouseDown;
    clan::Rect dragArea;
    float highlightValue;
    
    //Sounds
    clan::SoundBuffer_Session *music_session_;

    std::list<Persona *> persons;
    std::list<Persona *> sentinal;
    std::list<Persona *> scourge;
    
    clan::DisplayWindow window;
    clan::Canvas canvas;
    
    bool quit;
    
public:
    std::list<GameObject *> gameobjects;
    clan::BlendState blendstate_cl_blend_zero_cl_blend_one_minus_src_alpha;
    clan::BlendState blendstate_cl_blend_src_alpha_cl_blend_one_minus_src_alpha;
    clan::BlendState blendstate_default;
    
};
