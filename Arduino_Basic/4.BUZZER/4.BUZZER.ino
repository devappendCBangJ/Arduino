int BUZZER=7;  // Digital input
void setup ()

{
  pinMode (BUZZER, OUTPUT);
}

void loop ()
{
  digitalWrite (BUZZER, HIGH);
  delay(1000);
  digitalWrite (BUZZER, LOW);
  delay(1000);
}

