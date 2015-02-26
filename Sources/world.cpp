
#include "precomp.h"

#include "world.h"

    clan::Point cursor_pt;
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
    
    // Recieve mouse clicks
    /*slotKeyDown = window.get_ic().get_keyboard().sig_key_down().connect(this, &World::onKeyDown);
    slotMouseDown = window.get_ic().get_mouse().sig_key_down().connect(this, &World::onMouseDown);
    slotMouseDblClick = window.get_ic().get_mouse().sig_key_dblclk().connect(this, &World::onMouseDown);

    slotMouseUp = window.get_ic().get_mouse().sig_key_up().connect(this, &World::onMouseUp); */
    slotMouseMove = window.get_ic().get_mouse().sig_pointer_move().connect(this, &World::onMouseMove);

    // dragging = mouseDown = false;
    
    // Initi game_map - add_edifices etc TODO
    
    // Run the main loop
    run();
}

World::~World() {
    // Class Destructor
    std::list<Edifice *>::iterator it;
    /*for(it = edifices.begin(); it != edifices.end(); ++it)
        delete(*it);*/ //TODO
}

// Change map view on window
void World::onMouseMove(const clan::InputEvent &key) {
    int i;
    
//     game_map.draw(canvas, -key.mouse_pos.x, -key.mouse_pos.y);
    if(key.mouse_pos.x>MAP_WIDTH-100) 
    for(i=0;i<10;i++){
        cursor_pt.x += -1;
        game_map.draw(canvas,cursor_pt.x,cursor_pt.y);
    }
    if(key.mouse_pos.x<100)
    for(i=0;i<10;i++){
        cursor_pt.x -= -1;
        game_map.draw(canvas,cursor_pt.x,cursor_pt.y);
    }
    if(key.mouse_pos.y<100)
    for(i=0;i<10;i++){
        cursor_pt.y -= -1;
        game_map.draw(canvas,cursor_pt.x,cursor_pt.y);
    }
    if(key.mouse_pos.y>MAP_HEIGHT-100) 
    for(i=0;i<10;i++){
        cursor_pt.y += -1;
        game_map.draw(canvas,cursor_pt.x,cursor_pt.y);
    }
}

void World::run() {
    clan::GameTime game_time;
        cursor_pt.x = 0;
        cursor_pt.y = 0;
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
    std::list<Edifice *>::iterator it;
    for(it = edifices.begin(); it != edifices.end(); ) {
        // if update = false => delete edifices
        /* if ((*it)->update(timeElapsed_ms) == false) {
            delete (*it);
            it = edifices.erase(it);
        }
        else
            ++it; */ //TODO
    }
}

void World::draw() {
    // Draw background
    clan::Rect window_rect = window.get_viewport();
    game_map.draw(canvas, cursor_pt.x,cursor_pt.y);
        
    // Draw all edifices
    std::list<Edifice *>::iterator it;
    for(it = edifices.begin(); it != edifices.end(); ++it)
        //(*it)->draw(); TODO
    
    // TODO view boxes and map dragging should be somewhere here
    
    canvas.flush();
}

void World::on_window_close() {
    quit = true;
}