#include <DHT.h>
#include <Adafruit_Sensor.h>
#include <U8g2lib.h>
#include <Wire.h>

#ifdef U8X8_HAVE_HW_I2C
#define DHTPIN 4
#define DHTTYPE DHT11
#endif
U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
DHT dht(DHTPIN, DHTTYPE);

void setup(void) {
  Serial.begin(9600);
  u8g2.begin();
  dht.begin();
}



void loop(void) {
  int t=dht.readTemperature();
  int h=dht.readHumidity();
  u8g2.firstPage();
  do {  
  u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_6x10_mf); 
    u8g2.drawStr(0, 10, "Temp:");  
    u8g2.setCursor(37, 10);
    u8g2.print(t);   
    u8g2.drawStr(62, 10, "C");
    u8g2.setFont(u8g2_font_6x10_mf);
    u8g2.drawStr(00, 20, "hum:");  
    u8g2.setCursor(37, 20);
    u8g2.print(h);
    u8g2.drawStr(62, 20, "%"); 
    u8g2.sendBuffer();
     } while( u8g2.nextPage() );

   Serial.print("temperature:");
   Serial.print(t);
   Serial.println("C");
   Serial.print("Humidity:");
   Serial.print(h);
   Serial.println("%");
  delay(500);  

}

