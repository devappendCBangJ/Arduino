#define ENA 9  //PWM
#define IN1 8  //DIR
#define IN2 7  //DIR

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
}

void loop() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  for (int i = 60; i <= 250; i = i + 10){
    analogWrite(ENA, i);
    delay(250);
  }
  for (int i = 250; i >= 60; i = i - 10){
    analogWrite(ENA, i);
    delay(250);
  }
}
