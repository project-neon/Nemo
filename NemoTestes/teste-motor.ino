#include "_config.h"
#include "motors.h"
#include "motors.cpp" //(n sei se é necessário msm mas vai q né)

void setup {
Motors::init
 } 

void loop {
Motors::driveTank(50,50);
Motors::driveTank(-50,-50);
Motors::driveTank(50,-50);
}