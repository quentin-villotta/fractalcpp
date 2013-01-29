#include "App.h"

App::App(int width = 640, int height = 480)
{
	surf_display = NULL;
	width_display = width;
	height_display = height;
	
	running = true;
}

int App::Execute()
{
    if(Init() == false)
		return -1;

    SDL_Event event;

    while(running)
	{
        while(SDL_PollEvent(&event))
            Event(&event);

        Loop();
        Render();
    }

    Cleanup();

    return 0;
}

int main(int argc, char* argv[])
{
	//parse conf file
	App app(1024, 768);
    return app.Execute();
}
