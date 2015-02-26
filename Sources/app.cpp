#include "precomp.h"

#include "app.h"
#include "world.h"

int App::main(const std::vector<std::string> &args) {
    
    // Create a window
    clan::DisplayWindowDescription desc;
    desc.set_title("Change this title");
    desc.set_size(clan::Size(MAP_WIDTH,MAP_HEIGHT),true);
    clan::DisplayWindow window(desc);
    
    clan::SoundOutput output(44100);
    
    // Create world
    World world(window);
    
    // Run the main loop
    world.run();
    
    return 0;
}