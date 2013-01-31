#include "App.h"

App::App(int width, int height, int max_iter, 
	complex<double> z_top_left, complex<double> z_bottom_right)
{
	surf_display = NULL;
	width_display = width;
	height_display = height;
	
	running = true;
	
	//TODO: add argument to App:App to specify fractal type (mandelbrot, julia, ...)
	fractal = new FractalJulia(width_display, height_display, max_iter,
		z_top_left, z_bottom_right);	
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
	
	//Mandelbrot centered
	//complex<double> z_top_left(-2.1, 1.2);
	//complex<double> z_bottom_right(0.6, -1.2);
	
	complex<double> z_top_left(-2.0, 2.0);
	complex<double> z_bottom_right(2.0, -2.0);
	App app(800, 710, 50, z_top_left, z_bottom_right);
	
    return app.Execute();
}
