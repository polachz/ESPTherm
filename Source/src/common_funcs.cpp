#include <Arduino.h>
#include "definitions.h"
#include "debug.h"
#include "common_funcs.h"

//Ticker ticker;

/*
void tick_led()
{
  //toggle state
  int state = digitalRead(BOARD_LED);  // get the current state of GPIO1 pin
  digitalWrite(BOARD_LED, !state);     // set pin to the opposite state
}

void BlinkLed(double intervalInSecs)
{
    ticker.attach(intervalInSecs, tick_led);
}
void BlinkLedStop(bool ledOn)
{
    ticker.detach();
    if(ledOn){
        //keep LED on
        digitalWrite(BOARD_LED, HIGH);
   }else{
        digitalWrite(BOARD_LED, LOW);
   }
}
*/
String formatBytes(size_t bytes) {
	if (bytes < 1024) {
		return String(bytes) + "B";
	} else if (bytes < (1024 * 1024)) {
		return String(bytes / 1024.0) + "KB";
	} else if (bytes < (1024 * 1024 * 1024)) {
		return String(bytes / 1024.0 / 1024.0) + "MB";
	} else {
		return String(bytes / 1024.0 / 1024.0 / 1024.0) + "GB";
	}
}

void signal_hard_error()
{
    printlnE("Hard Error Occurs!"); 
    delay(1000);
    printlnE("HARD Error Occurs!"); 
    delay(1000);
    printlnE("HARD ERROR Occurs!"); 
    delay(2000);
    printlnE("Going to reboot sytem in 1 sec...."); 
    //ESP.restart();
}
