/*UT IEEE RAS Mercury 2016
Authors:Hasun Amaraskeara,Jerry Wang
*/

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"


Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *right_front_motor = AFMS.getMotor(1);
Adafruit_DCMotor *left_front_motor = AFMS.getMotor(2);
Adafruit_DCMotor *left_back_motor = AFMS.getMotor(3);
Adafruit_DCMotor *right_back_motor = AFMS.getMotor(4);


/*Tracks first byte and byte before that*/
char last_read_byte = 0;
char current_byte = 0;

/*Motor Variables*/
int left_motor_speed;
int right_motor_speed;
enum MOTOR_DIRECTION {forward, backward};
int motor_direction;
void updateMotorDirection();
void updateLeftMotors();
void updateRightMotors();
void makeLeftTurn();
void makeRightTurn();
void startMotors();
/*Motor Varialbes*/

void setup() {
        Serial.begin(9600); // set up Serial library at 9600 bps
        Serial.println("UT IEEE RAS MERCURY 2016");
        AFMS.begin(); // create with the default frequency 1.6KHz
        /* turn on the motors */
        right_back_motor->run(RELEASE);
        right_front_motor->run(RELEASE);
        left_back_motor->run(RELEASE);
        left_front_motor->run(RELEASE);
        /*turn on the motors*/
        startMotors();
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
                if(current_byte == 'b') {
                        motor_direction = backward;
                        updateMotorDirection();
                }
                if( (0x30 <= current_byte) && (current_byte <=0x39))
                {
                        current_byte = (current_byte - 0x30);
                        if(last_read_byte == 'l')
                        {
                                left_motor_speed = map (current_byte,0,9,0,255);
                                Serial.println(left_motor_speed);
                                updateLeftMotors();
                        }
                        if (last_read_byte == 'r')
                        {
                                right_motor_speed = map (current_byte,0,9,0,255);
                                Serial.println(right_motor_speed);
                                updateRightMotors();
                        }

                }
                else if(current_byte == 'd'){
                  makeLeftTurn();
                }
                else if(current_byte == 'a'){
                  makeRightTurn();
                }
                else if(current_byte == 'f'){
                  left_back_motor->setSpeed(0);
                  left_front_motor->setSpeed(0);
                  right_back_motor->setSpeed(0);
                  right_front_motor->setSpeed(0);
                }

        }
        delay(50);
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


void makeRightTurn(){
  right_front_motor->setSpeed(-right_motor_speed);
  left_back_motor->setSpeed(left_motor_speed);
}
void makeLeftTurn(){
  right_front_motor->setSpeed(right_motor_speed);
  left_back_motor->setSpeed(-left_motor_speed);

 }


void updateLeftMotors(){
        left_back_motor->setSpeed(left_motor_speed);
        left_front_motor->setSpeed(left_motor_speed);
        updateMotorDirection();
        //delay(50);
}
void updateRightMotors(){
        right_back_motor->setSpeed(right_motor_speed);
        right_front_motor->setSpeed(right_motor_speed);
        updateMotorDirection();

}

void startMotors(){
        right_back_motor->run(FORWARD);
        right_front_motor->run(FORWARD);
        left_back_motor->run(FORWARD);
        left_front_motor->run(FORWARD);
        /*LOL JERRY LOL*/
        left_back_motor->setSpeed(4);
        left_front_motor->setSpeed(4);
        right_back_motor->setSpeed(4);
        right_front_motor->setSpeed(4);
}
