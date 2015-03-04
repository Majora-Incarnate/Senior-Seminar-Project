#include "Application.h"
#include "Application_Event.h"
#include "Event_Handler.h"
#include "Video_Engine.h"
#include "Clock.h"
#include "System.h"
#include "Quad_Tree.h"



#define num_threads 4



Application::Application() {
    is_running = true;

    number_of_objects = 500;

    circles = new Object[number_of_objects];

    omp_set_num_threads(num_threads);
}



bool Application::Execute() {
    if (!Setup())
        return 1;
        
    while (is_running) {
        Events();
        Loop();
    }
    
    Cleanup();

    return 0;
}



bool Application::Setup() {
    if (!System::Setup())
        return false;
    if (!Video_Engine::Setup())
        return false;

    return true;
}

void Application::Events() {
    SDL_Event Event;

    Event_Handler::Reset_Input();

    while (SDL_PollEvent(&Event))
        Event_Handler::OnEvent(&Event);

    Application_Event * appFlag = Application_Event::Poll_Event();

    if (appFlag == NULL)
        return;

    is_running = false;

    switch(appFlag->Get_Event_Code()) {
    case APPLICATION_EXIT:
        break;

    default:
        printf("Error: %s\n", "Unknown Critical Error");
        break;
    }
}

void Application::Loop() {
    Clock::Frame_Control.Update();   


    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();


    for (int i = 0; i < number_of_objects; i++)
    {
    	circles[i].Update();
    	circles[i].Render();
    }


    int collision_count = 0;

    double calc_time = omp_get_wtime();

    for (int i = 0; i < number_of_objects - 1; i++)
    	for (int j = i + 1; j < number_of_objects; j++)
    		if (circles[i].Intersects(circles[j]))
				collision_count++;

    calc_time = omp_get_wtime() - calc_time;

    printf("Collision Count: %d\t", collision_count);
    printf("Control Time: %f sec\n", calc_time);


    /*collision_count = 0;

    calc_time = omp_get_wtime();

	#pragma omp parallel
	{
		int ID = omp_get_thread_num();
		int thread_count = omp_get_num_threads();
		int temp = 0;

	    for (int i = ID; i < number_of_objects - 1; i += thread_count)
	    	for (int j = i + 1; j < number_of_objects; j++)
                if (circles[i].Intersects(circles[j]))
                    temp++;

		#pragma omp atomic update
		collision_count += temp;
	}

    calc_time = omp_get_wtime() - calc_time;

    printf("Collision Count: %d\t", collision_count);
    printf("Multithreaded Time: %f sec\n", calc_time);*/


    collision_count = 0;

    Quad_Tree blah(0, 0, System::window_width, System::window_height);

    blah.Render();

    for (int i = 0; i < number_of_objects; i++)
        blah.Insert(&circles[i]);

    calc_time = omp_get_wtime();

    for (int i = 0; i < number_of_objects; i++)
    {
        std::list<Object *> temp = blah.Test(&circles[i]);
        for (std::list<Object *>::iterator it = temp.begin(); it != temp.end(); it++)
            if (*it != &circles[i])
                if (circles[i].Intersects(**it))
                    collision_count++;

    }

    calc_time = omp_get_wtime() - calc_time;

    printf("Collision Count: %d\t", collision_count);
    printf("Quad Tree Time: %f sec\n", calc_time);


    printf("\n");


    SDL_GL_SwapWindow(System::window_surface);
}

void Application::Cleanup() {
	delete[] circles;
    Video_Engine::Cleanup();
    System::Cleanup();
}