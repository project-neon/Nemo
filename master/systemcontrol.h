#include <Thread.h>
#include <ThreadController.h>


#ifndef SYSTEMCONTROL_H
#define SYSTEMCONTROL_H

extern ThreadController controller; 

class SystemControl {
  public:
    static int bright_read1;
    static int bright_read2;
    static int infra_distance;

    static int button_state;
    static int firstReading1;
    static int firstReading2;

    static bool white;
    static bool snek;
    
    static bool leftWhite;
    static bool rightWhite;

    static void init();
    static bool buttonStartStop(bool button_press);
    static int getColorSensors();  
};


#endif  

