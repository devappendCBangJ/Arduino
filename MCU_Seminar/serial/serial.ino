int read_data = 0;
//char read_data = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  if(Serial.available() > 0){
    Serial.println(Serial.available());    
    read_data = Serial.read();
    Serial.print("I received = ");
    Serial.println(read_data);
    Serial.println(Serial.available());    
  }
}
