#include "Event_Handler.h"
#include "Application_Event.h"



bool Keyboard::key_state[3][283];
bool Mouse::button_state[3][4];
float Mouse::mouse_x = 0.0;
float Mouse::mouse_y = 0.0;
float Mouse::mouse_dx = 0.0;
float Mouse::mouse_dy = 0.0;

 

 
void Event_Handler::OnEvent(SDL_Event * Event) {
    switch(Event->type) {
        case SDL_APP_TERMINATING:
        case SDL_APP_LOWMEMORY:
        case SDL_WINDOWEVENT:
        case SDL_SYSWMEVENT:
        case SDL_APP_WILLENTERFOREGROUND:
        case SDL_APP_WILLENTERBACKGROUND:
        case SDL_APP_DIDENTERFOREGROUND:
        case SDL_APP_DIDENTERBACKGROUND:
            break;
 
        case SDL_KEYDOWN:
            Event_Handler::OnKeyDown(Event->key.keysym.scancode, Event->key.keysym.sym, Event->key.keysym.mod);
            break;
 
        case SDL_KEYUP:
            Event_Handler::OnKeyUp(Event->key.keysym.scancode, Event->key.keysym.sym, Event->key.keysym.mod);
            break;
 
        case SDL_MOUSEMOTION:
            Event_Handler::OnMouseMove(Event->motion.x,Event->motion.y,Event->motion.xrel,Event->motion.yrel,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_LEFT))!=0,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_RIGHT))!=0,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_MIDDLE))!=0);
            break;
 
        case SDL_MOUSEBUTTONDOWN:
            switch(Event->button.button) {
                case SDL_BUTTON_LEFT:
                    Event_Handler::OnLButtonDown(Event->button.x, Event->button.y);
                    break;
                    
                case SDL_BUTTON_RIGHT:
                    Event_Handler::OnRButtonDown(Event->button.x, Event->button.y);
                    break;
                    
                case SDL_BUTTON_MIDDLE:
                    Event_Handler::OnMButtonDown(Event->button.x, Event->button.y);
                    break;
            }
            break;
 
        case SDL_MOUSEBUTTONUP:
            switch(Event->button.button) {
                case SDL_BUTTON_LEFT:
                    Event_Handler::OnLButtonUp(Event->button.x, Event->button.y);
                    break;
                    
                case SDL_BUTTON_RIGHT:
                    Event_Handler::OnRButtonUp(Event->button.x, Event->button.y);
                    break;
                    
                case SDL_BUTTON_MIDDLE:
                    Event_Handler::OnMButtonUp(Event->button.x, Event->button.y);
                    break;
            }
            break;
 
        case SDL_JOYAXISMOTION:
            Event_Handler::OnJoyAxis(Event->jaxis.which,Event->jaxis.axis,Event->jaxis.value);
            break;
 
        case SDL_JOYBALLMOTION:
            Event_Handler::OnJoyBall(Event->jball.which,Event->jball.ball,Event->jball.xrel,Event->jball.yrel);
            break;
 
        case SDL_JOYHATMOTION:
            Event_Handler::OnJoyHat(Event->jhat.which,Event->jhat.hat,Event->jhat.value);
            break;
            
        case SDL_JOYBUTTONDOWN:
            Event_Handler::OnJoyButtonDown(Event->jbutton.which,Event->jbutton.button);
            break;
 
        case SDL_JOYBUTTONUP:
            Event_Handler::OnJoyButtonUp(Event->jbutton.which,Event->jbutton.button);
            break;

        case SDL_JOYDEVICEADDED:
        case SDL_JOYDEVICEREMOVED:
            //ignore
            break;

        case SDL_CONTROLLERAXISMOTION:
        case SDL_CONTROLLERBUTTONDOWN:
        case SDL_CONTROLLERBUTTONUP:
        case SDL_CONTROLLERDEVICEADDED:
        case SDL_CONTROLLERDEVICEREMOVED:
        case SDL_CONTROLLERDEVICEREMAPPED:
            //ignore
            break;

        case SDL_DOLLARGESTURE:
        case SDL_DOLLARRECORD:
        case SDL_MULTIGESTURE:
            //ignore
            break;

        case SDL_FINGERDOWN:
        case SDL_FINGERUP:
        case SDL_FINGERMOTION:
            //ignore
            break;

        case SDL_CLIPBOARDUPDATE:
        case SDL_DROPFILE:
            //ignore
            break;
            
        case SDL_USEREVENT:
        case SDL_LASTEVENT:
            //ignore
            break;
 
        case SDL_QUIT:
            Event_Handler::OnExit();
            break;

        default:
            //ignore
            break;
    }
}


/* Input Events */
void Event_Handler::OnInputFocus() {
    //Do Stuff
}
void Event_Handler::OnInputBlur() {
    //Do Stuff
}


/* Keyboard Events */
void Event_Handler::OnKeyDown(SDL_Scancode scancode, SDL_Keycode sym, Uint16 mod) {
    Keyboard::key_state[Keyboard::KEY_DOWN_INDEX][scancode] = true;
    Keyboard::key_state[Keyboard::KEY_PRESSED_INDEX][scancode] = true;
}

void Event_Handler::OnKeyUp(SDL_Scancode scancode, SDL_Keycode sym, Uint16 mod) {
    Keyboard::key_state[Keyboard::KEY_DOWN_INDEX][scancode] = false;
    Keyboard::key_state[Keyboard::KEY_RELEASED_INDEX][scancode] = true;
}


/* Mouse Events */
void Event_Handler::OnMouseFocus() {
    //Do Stuff
}

void Event_Handler::OnMouseBlur() {
    //Do Stuff
}

void Event_Handler::OnMouseMove(int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle) {
    Mouse::mouse_x = mX;
    Mouse::mouse_y = mY;
    Mouse::mouse_dx = relX;
    Mouse::mouse_dy = relY;
}

void Event_Handler::OnMouseWheel(bool Up, bool Down) {
    Mouse::button_state[Mouse::MOUSE_WHEEL_UP][Mouse::MOUSE_WHEEL_INDEX] = Up;
    Mouse::button_state[Mouse::MOUSE_WHEEL_DOWN][Mouse::MOUSE_WHEEL_INDEX] = Down;
}

void Event_Handler::OnLButtonDown(int mX, int mY) {
    Mouse::button_state[Mouse::BUTTON_DOWN_INDEX][Mouse::LEFT_BUTTON_INDEX] = true;
    Mouse::button_state[Mouse::BUTTON_PRESSED_INDEX][Mouse::LEFT_BUTTON_INDEX] = true;
}

void Event_Handler::OnLButtonUp(int mX, int mY) {
    Mouse::button_state[Mouse::BUTTON_DOWN_INDEX][Mouse::LEFT_BUTTON_INDEX] = false;
    Mouse::button_state[Mouse::BUTTON_RELEASED_INDEX][Mouse::LEFT_BUTTON_INDEX] = true;
}

void Event_Handler::OnRButtonDown(int mX, int mY) {
    Mouse::button_state[Mouse::BUTTON_DOWN_INDEX][Mouse::RIGHT_BUTTON_INDEX] = true;
    Mouse::button_state[Mouse::BUTTON_PRESSED_INDEX][Mouse::RIGHT_BUTTON_INDEX] = true;
}

void Event_Handler::OnRButtonUp(int mX, int mY) {
    Mouse::button_state[Mouse::BUTTON_DOWN_INDEX][Mouse::RIGHT_BUTTON_INDEX] = false;
    Mouse::button_state[Mouse::BUTTON_RELEASED_INDEX][Mouse::RIGHT_BUTTON_INDEX] = true;
}

void Event_Handler::OnMButtonDown(int mX, int mY) {
    Mouse::button_state[Mouse::BUTTON_DOWN_INDEX][Mouse::MIDDLE_BUTTON_INDEX] = true;
    Mouse::button_state[Mouse::BUTTON_PRESSED_INDEX][Mouse::MIDDLE_BUTTON_INDEX] = true;
}

void Event_Handler::OnMButtonUp(int mX, int mY) {
    Mouse::button_state[Mouse::BUTTON_DOWN_INDEX][Mouse::MIDDLE_BUTTON_INDEX] = false;
    Mouse::button_state[Mouse::BUTTON_RELEASED_INDEX][Mouse::MIDDLE_BUTTON_INDEX] = true;
}


/* Joystick Events */
void Event_Handler::OnJoyAxis(Uint8 which, Uint8 axis, Sint16 value) {
    //Do Stuff
}

void Event_Handler::OnJoyButtonDown(Uint8 which, Uint8 button) {
    //Do Stuff
}

void Event_Handler::OnJoyButtonUp(Uint8 which, Uint8 button) {
    //Do Stuff
}

void Event_Handler::OnJoyHat(Uint8 which, Uint8 hat, Uint8 value) {
    //Do Stuff
}

void Event_Handler::OnJoyBall(Uint8 which, Uint8 ball, Sint16 xrel, Sint16 yrel) {
    //Do Stuff
}


/* Application Events */
void Event_Handler::OnMinimize() {
    //Do Stuff
}

void Event_Handler::OnRestore() {
    //Do Stuff
}

void Event_Handler::OnResize(int w, int h) {
    //Do Stuff
}

void Event_Handler::OnExpose() {
    //Do Stuff
}

void Event_Handler::OnExit() {
    Application_Event::New_Event(APPLICATION_EXIT);
}

void Event_Handler::OnUser(Uint8 type, int code, void * data1, void * data2) {
    //Do Stuff
}


void Event_Handler::Reset_Input() {
    Keyboard::Reset_Key_Events();
    Mouse::Reset_Button_Events();

    Mouse::mouse_dx = Mouse::mouse_dy = 0.0;
}



void Keyboard::Reset_Key_Events() {
    for (int i = 0; i < 283; i++) {
        Keyboard::key_state[Keyboard::KEY_PRESSED_INDEX][i] = false;
        Keyboard::key_state[Keyboard::KEY_RELEASED_INDEX][i] = false;
    }
}



void Mouse::Reset_Button_Events() {
    for (int i = 0; i < 4; i++) {
        Mouse::button_state[Mouse::BUTTON_PRESSED_INDEX][i] = false;
        Mouse::button_state[Mouse::BUTTON_RELEASED_INDEX][i] = false;
    }
}