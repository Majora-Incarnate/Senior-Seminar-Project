#ifndef APPLICATION_EVENT_H
#define APPLICATION_EVENT_H



#include <cstdlib>
 
 
 
enum Application_State {
    APPLICATION_EXIT,
    APPLICATION_ERROR
};



class Application_Event {
private:
    static Application_Event * event;
    Application_State event_code;
    
public:
    Application_Event();
    Application_Event(Application_State);
    
    Application_State Get_Event_Code();
    
    static void New_Event(Application_State);
    static Application_Event * Poll_Event();
};



#endif
