#include "App.h"

App::App(int width = 640, int height = 480, int max_iter = 100)
{
	surf_display = NULL;
	width_display = width;
	height_display = height;
	
	running = true;
	
	//TODO: add argument to App:App to specify fractal type (mandelbrot, julia, ...)
	fractal = new FractalMandelbrot(width_display, height_display, max_iter);

	//complex<double> orbit(0.72, 0.11);
	//fractal = new FractalJulia(width_display, height_display, max_iter, orbit);
	
	//TODO: add argument to App::App to specify the first view
	complex<double> z_top_left(-2.1, 1.2);
	complex<double> z_bottom_right(0.6, -1.2);
	//complex<double> z_top_left(-1.5, 0.33);
	//complex<double> z_bottom_right(-0.5, -0.33);
	fractal->UpdateIter(z_top_left, z_bottom_right);
	fractal->UpdateColor();
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
	App app(800, 710, 50);
    return app.Execute();
}
