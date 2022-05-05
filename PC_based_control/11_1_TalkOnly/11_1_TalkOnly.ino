int btn[4]={2,3,4,5}, led[4]={8,9,10,11}, apin=0;
const char cSTX=2, cETX=3, cCR=13, cLF=10;

void setup()
{
  for(int i=0; i<4; i++)
  {
    pinMode(led[i], OUTPUT);
    pinMode(btn[i], INPUT_PULLUP); // pull-up
  }
  Serial.begin(9600);
}

void loop()
{
  // LED 켜기
  for(int i=0; i<4; i++)
    digitalWrite(led[i], !digitalRead(btn[i]));
    // A접(normally high) : 사고에 대해 안전
      // 고장났을 때 파악 쉬움
    // B접(normally low) : 사고에 대해 불안전
      // 고장났을 때 파악 어려움
    // 활용 : emergency switch, 모터 limit sensor
    
  // 상태수집
  String leds = "";
  leds += digitalRead(btn[0]) ? "0" : "1";
  leds += digitalRead(btn[1]) ? "0" : "1";
  leds += digitalRead(btn[2]) ? "0" : "1";
  leds += digitalRead(btn[3]) ? "0" : "1";  
  String poten = strPadLeft(String(analogRead(apin)), 4); // string 변환 + 왼쪽에 0000 끼워넣음
  
  // 정보 내용만들기
  String st = "01," + leds + "," + poten;
  
  // BCC 만들기
  char BCC = 0;
  int len = st.length();
  for(int i=0; i<len; i++)
  {
    char c = st[i];
    BCC = BCC ^ c; // 이건 뭐지??? ♣
  }
  
  // 앞뒤 붙여 송신
  st = String(cSTX) + st + String(cETX) + String(BCC) + String(cCR) + String(cLF);
  Serial.print(st);
  
  delay(200);
}

//------------------ user function --------------------------
String strPadLeft(String st, int len)
{
  // string 앞의 len개수 데이터만 추출
  while(st.length() < len) {
    st = "0" + st;
  }
  return st;
}
