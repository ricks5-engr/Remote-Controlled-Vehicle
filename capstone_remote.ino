#include <WiFiConfig.h>
const int g_led = 8;
const int r_led = 10;
const int x = 1;
const int y = 0;

uint8_t receiverAddress[] = {0x34, 0xB7, 0xDA, 0xF6, 0x3A, 0xCC};
RemoteData data;
int og_x = 0;
int og_y = 0;
const int max_value = 3500; //max and min values that detect the cotnroller to be resting
const int min_value = 3000;

void setup() {
  Serial.begin(115200);
  pinMode(x, INPUT);
  pinMode(y, INPUT);
  wifi_setup();
  peer_setup(receiverAddress); 
  pinMode(r_led, OUTPUT);
  pinMode(g_led, OUTPUT);
}
void loop() {
  og_y = analogRead(y);
  og_x = analogRead(x);

  //DEFAULT CASE: CAR IS RESTING/CONTROLLER IS DIAGONAL OR RESTING I chose to make this simple and remove diagonal inputs because regardless of diagonal inputs the car is still aboe to go any direction
  data.vx = 0;
  data.vy = 0;
  data.sw = 0;
  digitalWrite(r_led, HIGH);
  digitalWrite(g_led, LOW);

//if one direction is resting and the other is moving send data to car to move
if ( ( (og_x < max_value && og_x > min_value) && (og_y < min_value || og_y > max_value) ) || ( (og_y < max_value && og_y > min_value) && (og_x < min_value || og_x > max_value) ) )  
{
  digitalWrite(r_led, LOW);
  digitalWrite(g_led, HIGH);
  if (og_x < max_value && og_x > min_value) //if the x direction is in rest
  {
    if (og_y < min_value) //y direction(right - left) is negative
    {
      data.vy = map(og_y, 0, min_value-1, 126, 1);
    }
    else //y direction is positive
    {
      data.vy = map(og_y, max_value+1, 4095, 127, 255);
    }
  }
  else //x direction is not in rest
  {
    if (og_x < min_value) //x is negative(backwards)
    {
      data.vx = map(og_x, 0, min_value-1, 126, 1);
    }
    else
    {
      data.vx = map(og_x, max_value+1, 4095, 127, 255);
    }
  }
}
}

