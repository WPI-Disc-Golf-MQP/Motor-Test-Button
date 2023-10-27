/**
 * Here we use the same construction as the MaxBotix, namely we create a global void (*fxn)(void) 
 * to pass to init(). Doing so allow us to avoid using externs, as well as easily add multiple 
 * sensors.
*/

#include <Arduino.h>
#include <HC-SR04.h>
#include <Chassis.h>

HC_SR04 hc_sr04(0, 4); // TODO: Choose your pins.
void ISR_HC_0(void)
{
  hc_sr04.ISR_echo();
}

Chassis chassis;

void setup() 
{
  Serial.begin(115200);
  Serial.print("Welcome!\n");

  chassis.init();
  
  hc_sr04.init(ISR_HC_0);
}

void loop()
{
  chassis.loop();
  float distance = 0;
  if(hc_sr04.getDistance(distance))
  {
    Serial.print(millis());
    Serial.print("\tHC:\t");
    Serial.print(distance);

    int16_t error = distance - 2000;
    int16_t effort = error * 0.05;
    chassis.setMotorTargetSpeeds(effort, effort);

    Serial.print("\tSP:\t");
    Serial.print(effort);
    Serial.print('\n');
  }
}
