void setup() {
  //enable
  pinMode(27,OUTPUT);
  pinMode(29,OUTPUT);
  pinMode(46,OUTPUT);
  pinMode(48,OUTPUT);
  //PWM
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  //Directionals
  pinMode(30,OUTPUT);
  pinMode(32,OUTPUT);
  pinMode(34,OUTPUT);
  pinMode(36,OUTPUT);
  pinMode(38,OUTPUT);
  pinMode(40,OUTPUT);
  pinMode(42,OUTPUT);
  pinMode(44,OUTPUT);
  //Drive
  digitalWrite(27, HIGH);
  digitalWrite(29, HIGH);
  digitalWrite(46, HIGH);
  digitalWrite(48, HIGH);
  analogWrite(10, 150);
  analogWrite(11, 150);
  analogWrite(8, 150);
  analogWrite(9, 150);
  //forward
  digitalWrite(30, LOW);
  digitalWrite(34, HIGH);
  digitalWrite(36, LOW);
  digitalWrite(32, HIGH);
  digitalWrite(42, LOW);
  digitalWrite(40, HIGH);
  digitalWrite(38, LOW);
  digitalWrite(44, HIGH);
  //Await
  delay(500);
  //backwards
  digitalWrite(30, HIGH);
  digitalWrite(34, LOW);
  digitalWrite(36, HIGH);
  digitalWrite(32, LOW);
  digitalWrite(42, HIGH);
  digitalWrite(40, LOW);
  digitalWrite(38, HIGH);
  digitalWrite(44, LOW);
  //Await
  delay(500);
  //turn right
  digitalWrite(30, LOW);
  digitalWrite(34, HIGH);
  digitalWrite(36, HIGH);
  digitalWrite(32, LOW);
  digitalWrite(42, LOW);
  digitalWrite(40, HIGH);
  digitalWrite(38, HIGH);
  digitalWrite(44, LOW);
  //Await
  delay(500);
  //turn left
  digitalWrite(30, HIGH);
  digitalWrite(34, LOW);
  digitalWrite(36, LOW);
  digitalWrite(32, HIGH);
  digitalWrite(42, HIGH);
  digitalWrite(40, LOW);
  digitalWrite(38, LOW);
  digitalWrite(44, HIGH);
  //Await
  delay(500);
  //Unload pwm
  analogWrite(10, 0);
  analogWrite(11, 0);
  analogWrite(8, 0);
  analogWrite(9, 0);
}

void loop() {
  
}
