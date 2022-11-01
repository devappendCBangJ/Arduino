char PSD = A0;
int PSD_volt;
float PSD_cm;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  PSD_volt = map(analogRead(PSD), 0, 1023, 0, 5000);
  PSD_cm = (24.61/(PSD_volt-0.1696))*1000;
  Serial.print("PSD_volt : ");
  Serial.print(PSD_volt / 1000.0);
  Serial.print("/ PSD_cm : ");
  Serial.println(PSD_cm);
  delay(50);
}
