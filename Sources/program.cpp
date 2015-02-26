
#include "precomp.h"
#include "program.h"
#include "app.h"

int Program::main(const std::vector<std::string> &args) {
    // Initialize ClanLib base components
    clan::SetupCore setup_core;
    
    // Init ClanLib display components
    clan::SetupDisplay setup_display;
    
    // including all display targets ; remove unnecessary TODO
    clan::SetupD3D setup_d3d;
    clan::SetupGL setup_gl;
    clan::SetupSWRender setup_swrender;

    clan::SetupSound setup_sound;
    
    // Start applic
    App app;
    int retval = app.main(args);
    return retval;
}

clan::Application app(&Program::main);