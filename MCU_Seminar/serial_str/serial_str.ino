String read_data = "";

void setup() {
  Serial.begin(9600);
}

void loop() {
  if(Serial.available() > 0){
    read_data = Serial.readString();
    Serial.print("I received = ");
    Serial.println(read_data);    
  }
}
