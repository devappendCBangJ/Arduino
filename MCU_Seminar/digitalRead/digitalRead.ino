#define sw 4
int state = 0;

void setup() {
  pinMode(sw, INPUT);
  Serial.begin(9600);
}

void loop() {
  state = digitalRead(sw);
  Serial.println(state);
}
