#include "System.h"
#include "Application_Event.h"



const double System::DEFAULT_FPS_LIMIT = 30.0;
const char * System::WINDOW_ICON_FILEPATH = "./Art/Icon.bmp";
const char * System::APPLICATION_TITLE = "Collision Detection Project";
const char * System::APPLICATION_VERSION = "0.0.0.0";

const int System::DEFAULT_WINDOW_HEIGHT = 800;
const int System::DEFAULT_WINDOW_WIDTH = 800;

SDL_Window * System::window_surface = NULL;
SDL_GLContext System::opengl_context = NULL;
double System::fps_limit = System::DEFAULT_FPS_LIMIT;
int System::window_height = DEFAULT_WINDOW_HEIGHT;
int System::window_width = DEFAULT_WINDOW_WIDTH;
unsigned int System::debug_flag = 0xFFFFFFFF;



int System::Get_Memory_Usage() { //Note: this value is in KB!
    FILE * file = fopen("/proc/self/status", "r");
    int result = -1;
    /*char line[128];

    while (fgets(line, 128, file) != NULL) {
        if (strncmp(line, "VmSize:", 7) == 0) {
    		int i = strlen(line);

		    while (*line < '0' || *line > '9')
		        line++;

		    line[i-3] = '\0';
		    i = atoi(line);

		    result = i;
            break;
        }
    }*/

    fclose(file);
    return result;
}



bool System::Setup()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		printf("Unable to initialize SDL: %s\n", SDL_GetError());
		Application_Event::New_Event(APPLICATION_ERROR);
		return false;
	}

	window_surface = SDL_CreateWindow(APPLICATION_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	if (window_surface == NULL) 
	{
		printf("Unable to set %dx%d video: %s\n", System::window_width, System::window_height, SDL_GetError());
		Application_Event::New_Event(APPLICATION_ERROR);
		return false;
	}

	opengl_context = SDL_GL_CreateContext(window_surface);

	if (opengl_context == NULL) 
	{
		printf("Unable to setup openGL\n");
		Application_Event::New_Event(APPLICATION_ERROR);
		return false;
	}

	return true;
}

void System::Cleanup() {
	if (opengl_context)
		SDL_GL_DeleteContext(opengl_context); 

	if (window_surface)
		SDL_DestroyWindow(window_surface); 
	
	SDL_Quit();
}