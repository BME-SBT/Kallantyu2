#include <Arduino.h>
#include <Servo.h>

Servo servo;
int ema = 0;
void setup()
{
  pinMode(A0, INPUT);
  servo.attach(9);
  Serial.begin(115200);
}


int clamp(int value, int min, int max)
{
  if (value < min)
  {
    return min;
  }
  if (value > max)
  {
    return max;
  }
  return value;
}

void loop()
{
  int value = analogRead(A0);
  int rev = 1024 - value;
  int mapped = map(rev, 459, 958, 1280, 1830);
  mapped = clamp(mapped, 1280, 1830); // clamp to 1280-1830 (servo limits)
  int micros = mapped;
  ema = (ema * 0.9) + (micros * 0.1);
/*   Serial.print(rev);
  Serial.print(" ");
  Serial.print((int)micros);
  Serial.print(" ");
  Serial.print(ema);
  Serial.println(); */

  servo.writeMicroseconds(ema);
}