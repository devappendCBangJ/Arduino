#include <DHT.h>
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
 
void setup(){
  Serial.begin(9600);
  dht.begin();
}
 
void loop(){
    float t = dht.readTemperature();   
    int h = dht.readHumidity();
    
    Serial.print("temperature:");      
    Serial.println(t,1);   
    Serial.print("humidity:");         
    Serial.println(h);    
    delay(1000);
}
