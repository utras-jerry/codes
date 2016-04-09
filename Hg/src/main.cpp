/*UT IEEE RAS Mercury 2016*/
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"



void updateMotorDirection();
void updateLeftMotorSpeed();
void updateRightMotorSpeed();
void makeLeftTurn();
void makeRightTurn();


Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *right_front_motor = AFMS.getMotor(1);
Adafruit_DCMotor *left_front_motor = AFMS.getMotor(2);
Adafruit_DCMotor *left_back_motor = AFMS.getMotor(3);
Adafruit_DCMotor *right_back_motor = AFMS.getMotor(4);


/*Motor Variables*/
int left_motor_speed;
int right_motor_speed;
/*Tracks first byte and byte before that*/
char last_read_byte = 0;
char current_byte = 0;
/*Motor Variables*/

enum MOTOR_DIRECTION {forward, backward};
int motor_direction;

void setup() {
        Serial.begin(9600);
        Serial.println("Adafruit Motorshield v2 - DC Motor test!");
        AFMS.begin();

        left_front_motor->run(RELEASE);
        right_front_motor->run(RELEASE);
        left_back_motor->run(RELEASE);
        right_back_motor->run(RELEASE);
}

void loop() {

        if(Serial.available() > 0) {
                last_read_byte = current_byte;
                current_byte = Serial.read();
                /* gets a byte off of the serial buffer*/
                Serial.println(current_byte);
                if(current_byte == 'w') {
                        motor_direction = forward;
                        updateMotorDirection();
                }
                else if(current_byte == 's') {
                        motor_direction = backward;
                        updateMotorDirection();
                }
                else if( (0x30 <= current_byte) && (current_byte <=0x39))
                {
                        current_byte = (current_byte - 0x30);
                        if(last_read_byte == 'l')
                        {
                                left_motor_speed = map (current_byte,0,9,0,255);
                                Serial.println(left_motor_speed);
                        }
                        if (last_read_byte == 'r')
                        {
                                right_motor_speed = map (current_byte,0,9,0,255);
                                Serial.println(right_motor_speed);
                        }
                }
                else if(current_byte == 'd'){
                  makeLeftTurn();
                }
                else if(current_byte == 'a'){
                  makeRightTurn();
                }
                else if(current_byte == 'b'){
                  makeLeftTurn();                  
                }

        }
        delay(100);
}
void updateMotorDirection(){
        if(motor_direction == FORWARD)
        {
                left_front_motor->run(FORWARD);
                right_front_motor->run(FORWARD);
                left_back_motor->run(FORWARD);
                right_back_motor->run(FORWARD);
        }else
        {
                left_front_motor->run(BACKWARD);
                right_front_motor->run(BACKWARD);
                left_back_motor->run(BACKWARD);
                right_back_motor->run(BACKWARD);
        }
}
void updateLeftMotorSpeed(){
  left_front_motor->setSpeed(left_motor_speed);
  left_back_motor->setSpeed(left_motor_speed);
}
void updateRightMotorSpeed(){
  right_front_motor->setSpeed(right_motor_speed);
  left_back_motor->setSpeed(left_motor_speed);
}
void makeRightTurn(){
  right_front_motor->setSpeed(-right_motor_speed);
  left_back_motor->setSpeed(left_motor_speed);
}
void makeLeftTurn(){
  right_front_motor->setSpeed(right_morot_speed);
  left_back_motor->setSpeed(-left_motor_speed);
}
