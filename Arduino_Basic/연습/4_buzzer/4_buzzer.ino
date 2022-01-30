int buzzer;
void setup ()

{
  buzzer=11;
  pinMode(buzzer,OUTPUT);
}

void loop ()
{
  digitalWrite(buzzer,HIGH);
  delay(300);
  digitalWrite(buzzer,LOW);
  delay(1000);
}
