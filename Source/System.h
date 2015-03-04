#ifndef SYSTEM_H
#define SYSTEM_H



#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <omp.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_net.h>
#include <SDL2/SDL_ttf.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>



class System {
public:
	static bool Setup();
	static void Cleanup();

	static int Get_Memory_Usage();

	/*DEFAULT VARIABLES*/
	static const double DEFAULT_FPS_LIMIT;
	static const char * WINDOW_ICON_FILEPATH;
	static const char * APPLICATION_TITLE;
	static const char * APPLICATION_VERSION;

	static const int DEFAULT_WINDOW_HEIGHT;
	static const int DEFAULT_WINDOW_WIDTH;

	/*System Variables*/
	static SDL_Window * window_surface;
	static SDL_GLContext opengl_context;
	static double fps_limit;
	static int window_height;
	static int window_width;

	/*Math Variables*/

private:
};



#endif