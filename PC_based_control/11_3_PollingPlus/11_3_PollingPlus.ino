int btn[4]={2,3,4,5}, led[4]={8,9,10,11}, apin=0;
const char cSTX=2, cETX=3, cACK=6, sNAK=15, cCR=13, cLF=10;
String gBuff;

void setup() {
  // 초기 설정
  for(int i=0; i<4; i++)
  {
    pinMode(led[i], OUTPUT);
    pinMode(btn[i], INPUT_PULLUP); // pull-up
  }
  Serial.begin(9600);
  Serial.setTimeout(0); // 지연시간 없이 바로 읽음
}

void loop() {
  // 데이터 없으면 리턴
  if(Serial.available() <= 0) return;
  
  // 수신내용 버퍼에 추가
  gBuff += Serial.readString();
  
  // STX ~ ETX 찾기
  int ipos0 = gBuff.indexOf(cSTX);
  if(ipos0 < 0) return;
  int ipos1 = gBuff.indexOf(cETX, ipos0);
  if(ipos1 < 0) return;
  
  // STX ~ ETX 빼고 내부만 얻기
  String st = gBuff.substring(ipos0+1, ipos1);

  // gBuff 업데이트
  gBuff = gBuff.substring(ipos1 + 1);
  
  //=================================
  //  1. Set DO
  //=================================
  if (st.substring(0, 2) == "DO")
  {
    String hex = st.substring(2, 4);
    int dd = HexToDec(hex);
    digitalWrite(led[0], dd & 0x1 ? HIGH : LOW);
    digitalWrite(led[1], dd & 0x2 ? HIGH : LOW);
    digitalWrite(led[2], dd & 0x4 ? HIGH : LOW);
    digitalWrite(led[3], dd & 0x8 ? HIGH : LOW);
    Serial.print(String(cACK) + "DO" + String(cETX));
  }
  
  //=================================
  //  2. Set AO
  //=================================
  else if (st.substring(0, 2) == "AO")
  {
    String hex[4];
    hex[0] = st.substring(2, 4);   
    hex[1] = st.substring(5, 7);
    hex[2] = st.substring(8, 10);
    hex[3] = st.substring(11, 13);
    int dec;
    dec = HexToDec(hex[0]); analogWrite(led[0], dec);
    dec = HexToDec(hex[1]); analogWrite(led[1], dec);
    dec = HexToDec(hex[2]); analogWrite(led[2], dec);
    dec = HexToDec(hex[3]); analogWrite(led[3], dec);
    Serial.print(String(cACK) + "AO" + String(cETX));
  }
  
  //=================================
  //  3. Ask RB
  //=================================
  else if (st.substring(0, 2) == "RB")
  {
    int dec = 0;
    if(!digitalRead(btn[0])) dec = dec | 0x1;
    if(!digitalRead(btn[1])) dec = dec | 0x2;
    if(!digitalRead(btn[2])) dec = dec | 0x4;
    if(!digitalRead(btn[3])) dec = dec | 0x8;
    String hex1 = String(dec, HEX);
    if(hex1.length() == 1) hex1 = "0" + hex1;
    
    int poten = analogRead(apin);
    String hex2 = String(poten, HEX);
    hex2 = strPadLeft(hex2, 3);   // 16진수니까 3글자면 표현가능
    
    Serial.print(String(cACK) + "RB" + hex1 + "," + hex2 + String(cETX));
  }

  //=================================
  //  5. NAK
  //=================================
  else
  {
    Serial.print(String(sNAK));
  }
}
   
//--------------------- user function -----------------------------
//=================================
// 16진수 변환
//=================================
int HexToDec(String hex)
{
  char buf[10];
  hex.toCharArray(buf, 10);
  int dec = strtoul(buf, NULL, 16);
  return dec;
}

//=================================
// 왼쪽 문자열만 반환
//=================================
String strPadLeft(String st, int len)
{
  while(st.length() < len) {
    st = "0" + st;
  }
  return st;
}
