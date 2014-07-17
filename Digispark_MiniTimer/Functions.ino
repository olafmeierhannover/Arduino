/******************************************************************************************/
/******************************************************************************************/
/***  Create a second cycle and generate a 24 hours clock as the time base  ***/
void clockCycle(unsigned int INTERVAL){            // Use same constant INTERVAL
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > INTERVAL) {
    previousMillis = currentMillis;                // Save the last time status
    toggleLed = !toggleLed;                        // Toggle LED to display all is alive
    seconds +=1;
    if(seconds == 60) {
      seconds = 0;
      minutes +=1;
      if(minutes == 60) {
        minutes = 0;
        hours +=1;
        if(hours == 24)                            // Reset at 24:00:00 (midnight)
           hours = 0;        
      }
    }
  }                                                // End of if currentMillis loop
}                                                  // End of void loop
/***  End of functions  ***/
/******************************************************************************************/
/******************************************************************************************/


