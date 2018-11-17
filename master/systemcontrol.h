

#include <Thread.h>
#include <ThreadController.h>



#ifndef SYSTEMCONTROL.H 
#define SYSTEMCONTROL.H 


extern ThreadController controller; 

class SystemControl{
public:
  static void init();

  static void buttonStartStop(bool tipo);

};



#endif  