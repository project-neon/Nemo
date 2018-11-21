
#ifndef MOTORS_H 
#define MOTORS_H 


class Motors{ 

public: 

	static void init();

	static void move(int motor, int speed, int direction);

	static void stop();


};

#endif 