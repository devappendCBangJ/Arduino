// PSD 예제 : https://www.devicemart.co.kr/goods/view?no=1280438

//#include// LCD I2C 헤더파일 호출
//LiquidCrystal_I2C lcd(0x27,16,2); // set the LCD address to 0x27 for a 16 chars and 2 line display
char Sensor = A0; //A0에 센서연결
int Sensor_val; //센서 ADC값 저장 변수
//int lcd_pos;
//byte i;
#define VOLTS_PER_UNIT .0049F // (.0049 for 10 bit A-D) 
float volts;
//float inches;
float cm;

void setup() // 초기화
{
//  lcd.init(); // LCD 출력준비
//  lcd.backlight(); //LCD 백라이트 ON
//  lcd.setCursor(4, 0); //쓰기 좌표 1번줄에 4번칸
//  lcd.print("PSD"); // LCD에 LM35DZ 출력
//  lcd.setCursor(0, 1); //쓰기 좌표 2번줄에 0번칸
//  lcd.print("VALUE"); //LCD에 TEMP: 출력
  Serial.begin(9600);//시리얼통신 속도설정 
}

void loop() // 무한루프
{
  Sensor_val = analogRead(Sensor); // 센서저장변수에 아날로그값을 저장
  volts = (float)Sensor_val * VOLTS_PER_UNIT; // 아날로그값을 volt 단위로 변환
//  inches = 23.897 * pow(volts,-1.1907); // 측정전압에 따른 inch단위 거리 계산
  cm = 60.495 * pow(volts,-1.1904); // 측정전압에 따른 cm단위 거리 계산
//  if (volts < .2) inches = -1.0; // 측정범위 미만일때
//  if(cm>=99){
//    lcd.setCursor(6, 1); //쓰기 좌표 1번줄에 4번칸
//    lcd.print((int)cm, DEC); // LCD에 거리값 출력
//  }
//
//  else{
//    lcd.setCursor(6, 1); //쓰기 좌표 1번줄에 4번칸
//    lcd.print(" ");
//    lcd.print((int)cm, DEC); // LCD에 거리값 출력
//  }
  Serial.println(cm);
//  lcd.setCursor(9, 1); //쓰기 좌표 1번줄에 4번칸
//  lcd.print("cm ");
  delay(100); //2초간 지연
}
