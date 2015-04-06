#include "Application.h"
#include "Application_Event.h"
#include "Event_Handler.h"
#include "Video_Engine.h"
#include "Clock.h"
#include "System.h"
#include "Quad_Tree.h"
#include "Spatial_Map.h"
#include "Config.h"



Application::Application() {
    is_running = true;

    number_of_objects = Config::NUMBER_OF_OBJECTS;

    double_for_average = 0.0;
    multiprocess_average = 0.0;
    quad_tree_average = 0.0;
    hilbert_rtree_average = 0.0;
    frame_count = 0;

    circles = new Object[number_of_objects];

    omp_set_num_threads(Config::NUMBER_OF_THREADS);
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


    frame_count++;  


    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();


    for (int i = 0; i < number_of_objects; i++)
    {
    	circles[i].Update();
    	circles[i].Render();
    }



    //====================================================//
    //====================================================//
    //------------BEGINNING OF DOUBLE FOR TEST------------//
    //====================================================//
    //====================================================//
    int collision_count = 0;
    int comparison_count = 0;

    double calc_time = omp_get_wtime();

    Collider::DRAW_COLLIDING_OBJECTS = true;

    for (int i = 0; i < number_of_objects - 1; i++)
    	for (int j = i + 1; j < number_of_objects; j++)
    		if (circles[i].Intersects(circles[j]))
				collision_count++;

    Collider::DRAW_COLLIDING_OBJECTS = false;

    calc_time = omp_get_wtime() - calc_time;
    double_for_average += calc_time;

    if (frame_count >= System::fps_limit && Config::PRINT_DOUBLE_FOR_AVERAGE)
    {
        printf("Double For Average Time: %f sec\n", double_for_average / frame_count);
        double_for_average = 0.0;
    }

    if (Config::PRINT_DOUBLE_FOR_FRAME)
    {
        printf("Collision Count: %d\t", collision_count);
        printf("Comparison Count: %d\t", (number_of_objects * (number_of_objects + 1)) / 2);
        printf("Double For Average Time: %f sec\n", calc_time);
    }
    //====================================================//
    //====================================================//
    //====================================================//



    //====================================================//
    //====================================================//
    //-----------BEGINNING OF MULTIPROCESS TEST-----------//
    //====================================================//
    //====================================================//
    collision_count = 0;
    comparison_count = 0;

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
    multiprocess_average += calc_time;

    if (frame_count >= System::fps_limit && Config::PRINT_MULTITHREAD_AVERAGE)
    {
        printf("Multithreaded Average Time: %f sec\n", multiprocess_average / frame_count);
        multiprocess_average = 0.0;
    }

    if (Config::PRINT_MULTITHREAD_FRAME)
    {
        printf("Collision Count: %d\t", collision_count);
        printf("Comparison Count: %d\t", (number_of_objects * (number_of_objects + 1)) / 2);
        printf("Multithreaded Time: %f sec\n", calc_time);
    }
    //====================================================//
    //====================================================//
    //====================================================//



    //====================================================//
    //====================================================//
    //-------------BEGINNING OF QUADTREE TEST-------------//
    //====================================================//
    //====================================================//
    collision_count = 0;
    comparison_count = 0;

    calc_time = omp_get_wtime();

    Quad_Tree blah(0, 0, System::window_width, System::window_height);

    for (int i = 0; i < number_of_objects; i++)
        blah.Insert(&circles[i]);

    if (Config::DRAW_QUADTREE)
        blah.Render();

    //calc_time = omp_get_wtime();

    for (int i = 0; i < number_of_objects; i++)
        collision_count += blah.Test(&circles[i], comparison_count);

    calc_time = omp_get_wtime() - calc_time;
    quad_tree_average += calc_time;

    if (frame_count >= System::fps_limit && Config::PRINT_QUADTREE_AVERAGE)
    {
        printf("Quad Tree Average Time: %f sec\n", quad_tree_average / frame_count);
        quad_tree_average = 0.0;
    }

    if (Config::PRINT_QUADTREE_FRAME)
    {
        printf("Collision Count: %d\t", collision_count);
        printf("Comparison Count: %d\t", comparison_count);
        printf("Quad Tree Time: %f sec\n", calc_time);
    }
    //====================================================//
    //====================================================//
    //====================================================//



    //====================================================//
    //====================================================//
    //----------BEGINNING OF HILBERT R-TREE TEST----------//
    //====================================================//
    //====================================================//
    collision_count = 0;
    comparison_count = 0;

    calc_time = omp_get_wtime();

    Spatial_Map smap;

    for (int i = 0; i < number_of_objects; i++)
        smap.insert(&circles[i]);

    for (int i = 0; i < number_of_objects; i++)
        collision_count += smap.search(&circles[i], comparison_count);

    calc_time = omp_get_wtime() - calc_time;
    hilbert_rtree_average += calc_time;

    if (frame_count >= System::fps_limit && Config::PRINT_SPATIAL_MAP_AVERAGE)
    {
        printf("Index Tree Average Time: %f sec\n", hilbert_rtree_average / frame_count);
        hilbert_rtree_average = 0.0;
    }

    if (Config::PRINT_SPATIAL_MAP_FRAME)
    {
        printf("Collision Count: %d\t", collision_count);
        printf("Comparison Count: %d\t", comparison_count);
        printf("Spatial Map Time: %f sec\n", calc_time);
    }
    //====================================================//
    //====================================================//
    //====================================================//



    if (frame_count >= System::fps_limit)
    {
        printf("\n");
        frame_count = 0;
    }



    SDL_GL_SwapWindow(System::window_surface);
}

void Application::Cleanup() {
	delete[] circles;
    Video_Engine::Cleanup();
    System::Cleanup();
}