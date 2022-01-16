#define led 13

String read_data = "";

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if(Serial.available() > 0){
    read_data = Serial.readString();
    Serial.print("I received = ");
    Serial.println(read_data);
  }
  if(read_data == "on"){
    digitalWrite(led, HIGH);
  }
  else if(read_data == "off"){
    digitalWrite(led, LOW);
  }
}
