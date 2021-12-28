#include <Arduino.h>

//Coloquem aqui os pinos e nomes que vocês usarem

//Motor A
#define PWMA 9
#define AIN1 5  
#define AIN2 4

//Motor B
#define PWMB 10
#define BIN1 7
#define BIN2 6

#define STBY 8

// Motors config (H-Bridge)
#define MOTOR_ABS_MAX          255

//Sensor IR
#define RECV_PIN 2

//Sensores de distância
#define XSHUT1 A0
#define XSHUT2 A1
#define XSHUT3 A2
#define XSHUT4 A3

#define SCL A5
#define SDA A4

//Sensores de borda
#define borda1 A6  
#define borda2 A7

//Seletor de estratégia
#define B1 11
#define B2 12
#define B3 13

//LED
#define LED1 3
