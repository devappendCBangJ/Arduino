#define dir 4
#define pwm 3

void setup() {
  pinMode(dir, OUTPUT);
  pinMode(pwm, OUTPUT);
}

void loop() {
  digitalWrite(dir, HIGH);
  analogWrite(pwm, 100);
}
