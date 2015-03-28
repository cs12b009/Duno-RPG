
#include "precomp.h"

#include "world.h"
#include "persona.h"

#define MAP_WIDTH 1366
#define MAP_HEIGHT 768

int max_ht=0;
int max_wt = 0;
    
World::World(clan::DisplayWindow &display_window) : window(display_window), quit(false) {
    
    clan::Slot slot_quit = window.sig_window_close().connect(this, &World::on_window_close);
    
    canvas = clan::Canvas(window);
    
    clan::BlendStateDescription blend_desc;
    blendstate_default = clan::BlendState(canvas, blend_desc);
    blend_desc.set_blend_function( clan::blend_zero, clan::blend_one_minus_src_alpha, clan::blend_zero, clan::blend_one_minus_src_alpha);
    blendstate_cl_blend_zero_cl_blend_one_minus_src_alpha = clan::BlendState(canvas, blend_desc);

    blend_desc.set_blend_function(clan::blend_src_alpha, clan::blend_one_minus_src_alpha, clan::blend_src_alpha, clan::blend_one_minus_src_alpha);
    blendstate_cl_blend_src_alpha_cl_blend_one_minus_src_alpha = clan::BlendState(canvas, blend_desc);

    // Setting up resources - needs XML file
    resources = clan::XMLResourceManager::create(clan::XMLResourceDocument("resources.xml"));
    game_map = clan::Image::resource(canvas, "background", resources);
    
    //Mini-map Initialization
    mini_map = clan::Image::resource(canvas, "minimap", resources);

    //Mini-map Select
    mini_map_select = clan::Sprite::resource(canvas, "MiniMapSelect", resources);

    map_zoom_pt.x = 0;
    map_zoom_pt.y = 0;
    // Recieve mouse clicks
    /*slotKeyDown = window.get_ic().get_keyboard().sig_key_down().connect(this, &World::onKeyDown);
    slotMouseDown = window.get_ic().get_mouse().sig_key_down().connect(this, &World::onMouseDown);
    slotMouseDblClick = window.get_ic().get_mouse().sig_key_dblclk().connect(this, &World::onMouseDown); */

    slotMouseUp = window.get_ic().get_mouse().sig_key_up().connect(this, &World::onMouseClick);
    slotMouseMove = window.get_ic().get_mouse().sig_pointer_move().connect(this, &World::onMouseMove);
    
    // Initi game_map - add_gameobjects etc 
    initLevel();
    
    // Run the main loop
    run();
}

World::~World() {
    // Class Destructor
    std::list<GameObject *>::iterator it;
    for(it = gameobjects.begin(); it != gameobjects.end(); ++it)
        delete(*it);
}

void World::initLevel() {
    Persona *person1 = new Persona(Persona::STAINER, this);
    person1->setPos(100,100);
    
    gameobjects.push_back(person1);
    persons.push_back(person1);
}

// Clicking on units
void World::onMouseClick(const clan::InputEvent &key) {
    // Right click = move or attack
    if(key.id == clan::mouse_right) {
        std::list<Persona *>::iterator it;
        for(it = persons.begin(); it != persons.end(); ++it) {
            Persona *person1 = (*it);
            
            // Change destination for selected persons
            if(person1->isSelected())
                person1->setTargetPos(key.mouse_pos.x, key.mouse_pos.y);
        }
    }
    
    // Left click = select
    if(key.id == clan::mouse_left) {
        std::list<Persona *>::iterator it;
        for(it = persons.begin(); it != persons.end(); ++it) {
            Persona *person1 = (*it);
            
            // Just left click on map deselects
            if(person1->isSelected())
                person1->deselect();
            // Select person
            if(person1->hitCheck(key.mouse_pos.x, key.mouse_pos.y))
                person1->select();
        }

        //Select Mini-map-select ,when clicked on Mini-map 
        // if(mini_map.hitCheck(key.mouse_pos.x, key.mouse_pos.y)){
        // 	mini_map_select->select();
        // }

    }
}

// Change map view on window
void World::onMouseMove(const clan::InputEvent &key) {
    int i;
    
    if(key.mouse_pos.x>MAP_WIDTH-100) 
    for(i=0;i<10;i++){
        max_wt += 1;
        if(max_wt>3200-(MAP_WIDTH)){
            max_wt = 3200-(MAP_WIDTH);
            break;
        }
        map_zoom_pt.x += -1;
    }
    if(key.mouse_pos.x<100)
    for(i=0;i<10;i++){
        max_wt -= 1;
        if(max_wt<0){
            max_wt =0;
            break;
        }
        map_zoom_pt.x -= -1;
    }
    if(key.mouse_pos.y<100)
    for(i=0;i<10;i++){
        max_ht -= 1;
        if(max_ht<0){
            max_ht = 0;
            break;
        }
        map_zoom_pt.y -= -1;
    }
    if(key.mouse_pos.y>MAP_HEIGHT-100) 
    for(i=0;i<10;i++){
        max_ht += 1;
        if(max_ht>2400-(MAP_HEIGHT)){
            max_ht = 2400-(MAP_HEIGHT);
            break;
        }
        map_zoom_pt.y += -1;
    }
}

void World::run() {
    clan::GameTime game_time;
    // ----  Music
    clan::SoundBuffer music = clan::SoundBuffer::resource("Music1",resources);
    music.set_volume(0.3f);
    
    clan::SoundBuffer_Session music_session = music.prepare();
    
    music_session.set_looping(true);
    music_session.play();
    // ----  Music done
    
    while(!window.get_ic().get_keyboard().get_keycode(clan::keycode_escape)) {
        game_time.update();
        if (quit)
            break;
        
        update(game_time.get_time_elapsed_ms());
        draw();
        
        window.flip(1);
        clan::KeepAlive::process();
    };
}

void World::update(int timeElapsed_ms) {
    // update all stuff
    std::list<GameObject *>::iterator it;
    for(it = gameobjects.begin(); it != gameobjects.end(); ) {
        // if update = false => delete gameobjects
        if ((*it)->update(timeElapsed_ms) == false) {
            delete (*it);
            it = gameobjects.erase(it);
        }
        else
            ++it; //TODO
    }
}

void World::draw() {
    // Draw background
    clan::Rect window_rect = window.get_viewport();
    game_map.draw(canvas, map_zoom_pt.x,map_zoom_pt.y);
    
    // mini_map.set_scale(0.2f, 0.2f);
    mini_map.draw(canvas, 1366-mini_map.get_width(),768-mini_map.get_height());

    // mini_map_select.set_scale(0.05f,0.05f);
    mini_map_select.draw(canvas,1366 - mini_map.get_width() + mini_map_select.get_width()/2 + max_wt/13 , 768 - mini_map.get_height() + mini_map_select.get_height()/2 + max_ht/12);

    // Draw all gameobjects
    std::list<GameObject *>::iterator it;
    for(it = gameobjects.begin(); it != gameobjects.end(); ++it)
        (*it)->draw();
    
    // TODO view boxes and map dragging should be somewhere here
    
    canvas.flush();
}

void World::on_window_close() {
    quit = true;
}