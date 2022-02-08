char Sensor = A0;
int Sensor_val;

void setup() {
  pinMode(Sensor, INPUT);
  Serial.begin(9600);
}

void loop() {
  Sensor_val = analogRead(Sensor);
  Serial.println(Sensor_val);
}
