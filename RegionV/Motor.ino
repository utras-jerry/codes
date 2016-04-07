// defines pins numbers

    const int stepPin = 3; 
    const int dirPin = 4; 
    const int stepPin2 = 5;
    const int dirPin2 = 6;

    void setup() { 

// Sets the two pins as Outputs
        
        pinMode(stepPin,OUTPUT);
        pinMode(dirPin,OUTPUT);
        pinMode(stepPin2,OUTPUT);
        pinMode(dirPin2,OUTPUT);
    }
    void loop() {
        digitalWrite(dirPin,HIGH);
        digitalWrite(dirPin2,LOW);

// Enables the motor to move in a particular direction
// Makes 200 pulses for making one full cycle rotation 
        
        for(int x = 0; x < 200; x++ ) {
            digitalWrite(stepPin2,HIGH); digitalWrite(stepPin,HIGH);
            delayMicroseconds(500); 
            digitalWrite(stepPin2,LOW); digitalWrite(stepPin,LOW); 
            delayMicroseconds(500);  
        }
        delay(1000);

// One second delay
        
        digitalWrite(dirPin,LOW); 
        digitalWrite(dirPin2,HIGH); 

//Changes the rotations direction 
// Makes 400 pulses for making two full cycle rotation 

        for(int x = 0; x < 400; x++) { 
            digitalWrite(stepPin2,HIGH); digitalWrite(stepPin,HIGH);
            delayMicroseconds(500); 
            digitalWrite(stepPin2,LOW); digitalWrite(stepPin,LOW);
            delayMicroseconds(500); 
        } 
        delay(1000);
    }
