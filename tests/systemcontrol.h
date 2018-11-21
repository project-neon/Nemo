#include <Thread.h>
#include <ThreadController.h>


#ifndef SYSTEMCONTROL_H
#define SYSTEMCONTROL_H

extern ThreadController controller; 

class SystemControl {
  public:
    static int bright_read;
    static int button_state;
    static int infra_distance;


    static void init();
    static bool buttonStartStop(bool button_press);
    static int getColorSensors();  
};


#endif  

