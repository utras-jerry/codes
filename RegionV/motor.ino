#include <Servo.h>

// defines pins used
const int stepPin = 3; 
const int dirPin = 4; 
const int stepPin2 = 5;
const int dirPin2 = 6;
const int sens = 49;
const int sens2 = 48;

Servo myServo;

void setup() { 
// Sets the two pins as Outputs
    pinMode(stepPin,OUTPUT);
    pinMode(dirPin,OUTPUT);
    pinMode(stepPin2,OUTPUT);
    pinMode(dirPin2,OUTPUT);
    pinMode((A0), INPUT); // back left
    pinMode((A1), INPUT); // front left
    pinMode((A2), INPUT); // back right
    pinMode((A3), INPUT); // front right
    pinMode((A4), INPUT); // forward
    Serial.begin(9600);
    Serial.begin(9600);
    myServo.attach(2);
    servoOpen(true);
    while(1){
        if(analogRead(A4)>600){break;}
        align();
        delay(250);
        straightLittle(false,.5);
    }   
/*
    straightGap();
    delay(1000);
    justStraight();
    delay(1000);
    straightWall(false,  220);
    delay(1000);
    straightWall(true,  220);
*/
}

void loop(){}

void justStraight(){
    digitalWrite(dirPin,LOW);
    digitalWrite(dirPin2,HIGH);
    while(true){
        int forward = analogRead(A4);
        straightForward(2800);
        if(forward > 570){
            Serial.println("Sensor detected");
            delay(1000);
            servoOpen(true);
            delay(1000);
            turn(120);
            break;
        } 
    }
}

//Go straight till you see a wall, bro!
void straightWall(bool door, int ang){
    digitalWrite(dirPin,LOW);
    digitalWrite(dirPin2,HIGH);
    while(true){
        int backLeft = analogRead(A0);
        int frontLeft = analogRead(A1);
        int backRight = analogRead(A2);
        int frontRight = analogRead(A3);
        int forward = analogRead(A4);   
        Serial.println("Wally");
        Serial.println(frontRight);
        Serial.println(frontLeft);
        if(frontRight > 600){
            turn(-5);
            delay(500);
            straightLittle(false, .600);
            Serial.println("Right");
        }
        else if (frontLeft > 600){
            turn(5);
            Serial.println("Left");
            delay(500);
            straightLittle(false, .600);
        }
        else{
            straightForward(2800);
            if(forward > 600){
                Serial.println("Sensor detected");
                delay(1000);
                servoOpen(door);
                delay(1000);
                turn(ang);
                break;
            } 
        }
    }
}  

void align(void){
    int frontLeft = analogRead(A1);
    int frontRight = analogRead(A3);
    if(frontLeft<frontRight){
        alignRight();
    }
    else{
        alignLeft();
    }
}

//aligns with right wall
void alignRight(void){
    int backRight = analogRead(A2);
    int frontRight = analogRead(A3);
    while (!((backRight < frontRight + 30) && (backRight > frontRight - 30))){
        backRight = analogRead(A2);
        frontRight = analogRead(A3);   
        if (backRight < frontRight){
//turn left
            turn(-5);
        }
        else if (backRight >= frontRight) {
//turn right 
            turn(5);
        }
    }
}

void alignLeft(void){
    int backLeft = analogRead(A0);
    int frontLeft = analogRead(A1);
    while (!((backLeft < frontLeft + 30) && (backLeft > frontLeft - 30))){  
        backLeft = analogRead(A0);
        frontLeft = analogRead(A1);
        if (backLeft < frontLeft){
//turn right
            turn(5);
        }
        else if (backLeft >= frontLeft) {
//turn left 
            turn(-5);
        }
    }
}  



//Hold down a little. Just move as long as we told you.
void straightLittle(bool inverted, float period){
    if(!inverted){
        digitalWrite(dirPin,LOW);
        digitalWrite(dirPin2,HIGH);
    }
    else{
        digitalWrite(dirPin,HIGH);
        digitalWrite(dirPin2,LOW);
    }
    float totalTime = 0;
    while(true){
        digitalWrite(stepPin2,HIGH); digitalWrite(stepPin,HIGH);
        delayMicroseconds(2800); 
        digitalWrite(stepPin2,LOW); digitalWrite(stepPin,LOW); 
        delayMicroseconds(2800);
        totalTime += .005;
//Just in case, if there is a wall, just stop.
        if(digitalRead(sens) == HIGH || totalTime >= period){
            break;
        }
    }  
}

void turn(int angle){
    int loops = angle;
    if(angle > 0){
        digitalWrite(dirPin,HIGH);
        digitalWrite(dirPin2,HIGH);
    }
    else{
        digitalWrite(dirPin,LOW);
        digitalWrite(dirPin2,LOW); 
        loops *=-1;
    }
    float delayTotal;
    for(int i = 0; i < loops; i++){
        straightForward(3000);
        delayTotal += .010;
    }
    delay(200);  
}

void straightForward(int del){
    digitalWrite(stepPin2,HIGH); digitalWrite(stepPin,HIGH);
    delayMicroseconds(del); 
    digitalWrite(stepPin2,LOW); digitalWrite(stepPin,LOW); 
    delayMicroseconds(del);
}
    
void straightGap(){
    digitalWrite(dirPin,LOW);
    digitalWrite(dirPin2,HIGH);
    while(true){
        int backLeft = analogRead(A0);
        int frontLeft = analogRead(A1);
        int backRight = analogRead(A2);
        int frontRight = analogRead(A3);
        int forward = analogRead(A4);
        straightForward(2800);
        if(frontLeft < 200 && backLeft < 200 ){
            turn(-110);
            break;
        }
    }  
}

void servoOpen(bool shouldOpen){
    if(shouldOpen){
        myServo.write(190);
    }
    else{
        myServo.write(80);
    }
}


