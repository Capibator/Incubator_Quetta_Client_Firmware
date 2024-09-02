#include <Arduino.h>
#include "mMenu.h"
#include "pinouts.h"
#include "rotary.h"


void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  menu.initialize(mainMenu);
  initEncoder(); 

}

void loop()
{
  updateEncoder();
  handle_rotary_button();
  processMenuCommand(menu, dir, UP, DOWN, ENTER, BACK);
  dir = IDLE;
}
