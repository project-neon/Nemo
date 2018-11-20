

#include <Thread.h>
#include <ThreadController.h>



#ifndef SYSTEMCONTROL.H 
#define SYSTEMCONTROL.H 


extern ThreadController controller; 

class SystemControl{
public:
  static void init();

  static bool buttonStartStop(bool button_press);

  static int getColorSensors();

  static int bright_read;

  static int infraDistance;
  
};

static int button_state;



#endif  

