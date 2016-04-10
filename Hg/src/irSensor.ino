void setup() {
  pinMode((A0), INPUT); // back left
  pinMode((A1), INPUT); // front left
  pinMode((A2), INPUT); // back right
  pinMode((A3), INPUT); // front right
  pinMode((A4), INPUT); // forward
  Serial.begin(9600);
}

void loop() {
    Serial.print("Back left ");
    Serial.println(analogRead(A0));
    Serial.print("Front left ");
    Serial.println(analogRead(A1));
    Serial.print("Back right ");
    Serial.println(analogRead(A2));
    Serial.print("Front right");
    Serial.println(analogRead(A3));
    Serial.print("Forward ");
    Serial.println(analogRead(A4));
    delay (500*4);
// put your main code here, to run repeatedly:
}


