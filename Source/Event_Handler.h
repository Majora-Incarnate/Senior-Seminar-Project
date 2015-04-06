#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H



#include <SDL2/SDL.h>



struct Event_Handler {
        static void OnEvent(SDL_Event *);
 
        static void OnInputFocus();
        static void OnInputBlur();
 
        static void OnKeyDown(SDL_Scancode, SDL_Keycode, Uint16);
        static void OnKeyUp(SDL_Scancode, SDL_Keycode, Uint16);
 
        static void OnMouseFocus();
        static void OnMouseBlur();
        static void OnMouseMove(int, int, int, int, bool, bool, bool);
        static void OnMouseWheel(bool, bool);
        static void OnLButtonDown(int, int);
        static void OnLButtonUp(int, int);
        static void OnRButtonDown(int, int);
        static void OnRButtonUp(int, int);
        static void OnMButtonDown(int, int);
        static void OnMButtonUp(int, int);
        
        static void OnJoyAxis(Uint8, Uint8, Sint16);
        static void OnJoyButtonDown(Uint8, Uint8);
        static void OnJoyButtonUp(Uint8, Uint8);
        static void OnJoyHat(Uint8, Uint8, Uint8);
        static void OnJoyBall(Uint8, Uint8, Sint16, Sint16);
        
        static void OnMinimize();
        static void OnRestore();
        static void OnResize(int, int);
        static void OnExpose();
        static void OnExit();
        static void OnUser(Uint8, int, void *, void *);

        static void Reset_Input();
};



struct Keyboard {
        static void Reset_Key_Events();

        static const int KEY_PRESSED_INDEX = 0;
        static const int KEY_RELEASED_INDEX = 1;
        static const int KEY_DOWN_INDEX = 2;

        static bool key_state[3][283];
};



struct Mouse {
        static void Reset_Button_Events();

        static const int BUTTON_PRESSED_INDEX = 0;
        static const int BUTTON_RELEASED_INDEX = 1;
        static const int BUTTON_DOWN_INDEX = 2;

        static const int MOUSE_WHEEL_UP = 0;
        static const int MOUSE_WHEEL_DOWN = 1;

        static const int RIGHT_BUTTON_INDEX = 0;
        static const int MIDDLE_BUTTON_INDEX = 1;
        static const int LEFT_BUTTON_INDEX = 2;
        static const int MOUSE_WHEEL_INDEX = 2;

        static bool button_state[3][4];
        static float mouse_x;
        static float mouse_y;
        static float mouse_dx;
        static float mouse_dy;
};



struct Joypad {};



#endif
