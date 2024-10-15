/* @todo
implement rotary core logic
implement menu system basic
implement internet connectivity with firebase.
https://capibator-default-rtdb.firebaseio.com/
AIzaSyBmV9YETTAMU748zFiko8EOO5yvOV-K684
*/
#include <Arduino.h>
#include "mMenu.h"
#include "pinouts.h"
#include "rotary.h"
#include "firebaseHandler.h"

#define root 1
bool toggleMenu; 
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  menu.initialize(mainMenu);
  initEncoder();
  connectWifi();
  connectFirebase();
  menu.hide();
}

void loop()
{
  updateEncoder();
  handle_rotary_button();
  if (on_button_long_click())
  {
    if (toggleMenu)
      toggleMenu = false;
    toggleMenu = true;
  }

  if (toggleMenu)
  {
    processMenuCommand(menu, dir, UP, DOWN, ENTER, BACK);
    dir = IDLE;
  }
  else
  {
    // show temperature settings. 
  }
}
