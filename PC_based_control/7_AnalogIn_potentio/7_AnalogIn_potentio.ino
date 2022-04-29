int led[4]={8,9,10,11}, apin=0;

void setup()
{
  for(int i=0; i<4; i++)
    pinMode(led[i], OUTPUT); // 디폴트는 입력
}

void loop()
{
  int aval = analogRead(apin);
  int brightness = aval / 4; // 10bit->8bit
  for(int i=0; i<4; i++)
    analogWrite(led[i], brightness); // 밝기 출력
}
