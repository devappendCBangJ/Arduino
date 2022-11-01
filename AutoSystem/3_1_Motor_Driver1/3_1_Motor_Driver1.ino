const int motorPWMPin = 6; // L298 Input ENA
const int motorDirPin1 = 8; // L298 Input 1
const int motorDirPin2 = 9; // L298 Input 2

void setup() {
  // put your setup code here, to run once:
  pinMode(motorDirPin1, OUTPUT);
  pinMode(motorDirPin2, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(motorDirPin1, HIGH);
  digitalWrite(motorDirPin2, LOW);
  analogWrite(motorPWMPin, 128);
  delay(300);
  digitalWrite(motorDirPin2, HIGH);
  digitalWrite(motorDirPin1, LOW);
  analogWrite(motorPWMPin, 128);
  delay(300);
}
