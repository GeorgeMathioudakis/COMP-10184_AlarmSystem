// COMP-10184 – Mohawk College
// COMP-10184_AlarmSystem
// Stage 5 submission 
// This program is used to imitate a home alarm that detects movement.
// which casues a countdown to start  that will trigger the alarm  if the button is not pressed disabling  the sensor 
//
// @author  George Mathioudakis
// @id   001211882
//
// I created this work and I have not shared it with anyone else.
//

#include <Arduino.h>

// digital input pin definitions
#define PIN_PIR D5
#define PIN_BUTTON D6
#define BUTTON_DELAY 200
#define BLINK_DELAY 125 
#define BUTTON_PUSHED  0
#define BUTTON_NOT_PUSHED 1
#define EXIT_LOOP 10
#define lOOP_ITERATOR 0.25
#define  LIGHT_OFF true
#define  LIGHT_ON false
#define ALARM_DISABLED  0
#define ALARM_ENABLE    1
#define ALARM_COUNTDOWN 2
#define ALARM_ACTIVE    3

int iButton;
int iAlarmState;
bool bPIR;


// *************************************************************
void setup() {
  // configure the USB serial monitor
  Serial.begin(115200);

  // configure the LED output
  pinMode(LED_BUILTIN, OUTPUT);

  // PIR sensor is an INPUT
  pinMode(PIN_PIR, INPUT);

  // Button is an INPUT
  pinMode(PIN_BUTTON, INPUT_PULLUP);

   iAlarmState = ALARM_ENABLE;
   bPIR = false;
   iButton = BUTTON_NOT_PUSHED;
}

// *************************************************************



// *************************************************************
//  function used to detect movement from motion sensor
void detectingMovement()
{
  digitalWrite(LED_BUILTIN, LIGHT_OFF);
  bPIR = digitalRead(PIN_PIR);
  //delay(BUTTON_DELAY);
  if(bPIR == true)
  {
    iAlarmState = ALARM_COUNTDOWN;
   }
}
// *************************************************************


// *************************************************************
// function is used to start a count down  causing the light to blink  for 10 seconds,
// Causing the light to go solid if the button is not pressed during the  10 seconds of blinking 
void alarmCountDown() {
  double dLoopCount = 0;
  iButton = BUTTON_NOT_PUSHED;
  while (dLoopCount != EXIT_LOOP && iButton == BUTTON_NOT_PUSHED)
    {
      iButton = digitalRead(PIN_BUTTON);
      digitalWrite(LED_BUILTIN, LIGHT_OFF);
      iButton = digitalRead(PIN_BUTTON);
      delay(BLINK_DELAY);
      iButton = digitalRead(PIN_BUTTON);
      digitalWrite(LED_BUILTIN, LIGHT_ON);
      iButton = digitalRead(PIN_BUTTON);
      delay(BLINK_DELAY);
      iButton = digitalRead(PIN_BUTTON);
      dLoopCount += lOOP_ITERATOR;
    }
    delay(BUTTON_DELAY);

  if(dLoopCount == EXIT_LOOP){
    iAlarmState = ALARM_ACTIVE;
  }
  else{
    digitalWrite(LED_BUILTIN, true);
    iAlarmState = ALARM_DISABLED;
  }
}
// *************************************************************


// *************************************************************
//function is used to wait for the button to be pressed to re-enable sensor
void re_EnableSensor(){
  iButton = digitalRead(PIN_BUTTON);
  delay(200);
  if(iButton == 0)
  {
    iAlarmState = ALARM_ENABLE;
  }
}
// *************************************************************
// function is used to when the alarm is active causing  the light to stay on
void alarmActive(){

  digitalWrite(LED_BUILTIN, false);
}
// *************************************************************
// loop is used to switch between states of the  alarm
void loop() {
  
  switch(iAlarmState) 
  {
  case ALARM_DISABLED:
  re_EnableSensor();
  break;

  case ALARM_ENABLE:
    detectingMovement();
    break;
    
  case ALARM_COUNTDOWN:
    alarmCountDown();
    break;
    
  case ALARM_ACTIVE:
    alarmActive();
    break;
  }
}
// *************************************************************