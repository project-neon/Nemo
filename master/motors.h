
#ifndef MOTORS.H 
#define MOTORS.H 


class Motors{ 

public: 

	static void init();

	static void move(int motor, int speed, int direction);

	static void stop();


};

#endif 