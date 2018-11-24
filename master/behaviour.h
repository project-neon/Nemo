#include "_config.h"
#include <Thread.h>


#ifndef BEHAVIOUR_H 
#define BEHAVIOUR_H 

class Behaviour{
	
public:

	static void verifyData(int irdist, int brightr1, int brightr2);

	static void searchMode();

	static void attackMode();

	static void retreatMode();

};

#endif