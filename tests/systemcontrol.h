
#include <Thread.h>
#include <ThreadController.h>



#ifndef SYSTEMCONTROL.H 
#define SYSTEMCONTROL.H 


extern ThreadController controller; 

class SystemControl{
public:
  static void init();

  static void buttonStartStop(int button_state);

  static int bright_read;

  static int button_state;

  static bool begun;

};



#endif 