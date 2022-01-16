#define led 3

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

/////analogWrtie실습

void loop() {
  analogWrite(led, 0);
  delay(300);
  analogWrite(led, 100);
  delay(300);
  analogWrite(led, 255);
  delay(300);
}
