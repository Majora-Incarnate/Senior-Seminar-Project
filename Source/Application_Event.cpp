#include "Application_Event.h"



Application_Event * Application_Event::event = NULL;



Application_Event::Application_Event() {
}
    
Application_Event::Application_Event(Application_State new_code) {
    event_code = new_code;
}
    
Application_State Application_Event::Get_Event_Code() {
    return event_code;
}
    
void Application_Event::New_Event(Application_State new_code) {
    event = new Application_Event(new_code);
}
    
Application_Event * Application_Event::Poll_Event() {
    Application_Event * temp;
        
    if (event == NULL)
        return NULL;
            
    temp = event;
    event = NULL;
    return temp;
}