#include <WiFiConfig.h>

RemoteData data;
const int first_enable = 4;
const int second_enable = 3;
const int lwi2 = 6;
const int lwi1 = 5; 
const int rwi1 = 10;
const int rwi2 = 8;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  wifi_setup();
  set_data_receiver(&data); 



  pinMode(first_enable, OUTPUT);
  pinMode(second_enable, OUTPUT);
  pinMode(lwi1, OUTPUT);
  pinMode(lwi2, OUTPUT);
  pinMode(rwi1, OUTPUT);
  pinMode(rwi2, OUTPUT);
  digitalWrite(first_enable, HIGH);
  digitalWrite(second_enable, HIGH);
  
  digitalWrite(lwi1, LOW);
  digitalWrite(lwi2, LOW);
  digitalWrite(rwi1, LOW);
  digitalWrite(rwi2, LOW);
}



void loop() {

  if (data.vx == 0 && (data.vy <= 126 || data.vy >= 127))
  {
    if (data.vy <= 126 && data.vy >= 1)
    {
      digitalWrite(lwi1, LOW);
      digitalWrite(lwi2, HIGH);
      digitalWrite(rwi1, HIGH);
      digitalWrite(rwi2, LOW);
    }
    if (data.vy >= 127 && data.vy<= 255)
    {
      digitalWrite(lwi1, HIGH);
      digitalWrite(lwi2, LOW);
      digitalWrite(rwi1, LOW);
      digitalWrite(rwi2, HIGH);
    }
  }
  else if (data.vy == 0 && (data.vx < 126 || data.vx > 127))
  {
      if (data.vx <= 126 && data.vx >= 1)
    {
      digitalWrite(lwi1, LOW);
      digitalWrite(lwi2, HIGH);
      digitalWrite(rwi1, LOW);
      digitalWrite(rwi2, HIGH);
    }
    if(data.vx >= 127 && data.vx <= 255)
    {
      digitalWrite(lwi1, HIGH);
      digitalWrite(lwi2, LOW);
      digitalWrite(rwi1, HIGH);
      digitalWrite(rwi2, LOW);
    }
  }
  else
  {
  digitalWrite(lwi1, LOW);
  digitalWrite(lwi2, LOW);
  digitalWrite(rwi1, LOW);
  digitalWrite(rwi2, LOW);
  }

}