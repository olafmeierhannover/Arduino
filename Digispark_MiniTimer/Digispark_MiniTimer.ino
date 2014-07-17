/******************************************************************************************/
/* Digispark_MiniTimer. On/Off-Timer with Digispark and with small changes for Uno.
 * Please refer also comments below. Pins connected to the LED and the relay must be changed!
 * 
 * Origin Author:        Olaf Meier  
 *
 * Modified by:          
 * Last Update:          2014/07_14                      
 * 
 * Hardware connection:  Refer within the sketch please!
 *  
 * Pin out of the Digispark:
 * All pins can be used as Digital I/O. Pins 0, 1, 4 as PWM. 4 Analog In as pins 2, 3, 4, 5
 * Pin 0 → MOSI I2C SDA, PWM (LED on Model B)
 * Pin 1 → MISO PWM (LED on Model A)
 * Pin 2 → I2C SCK, Analog In 1
 * Pin 3 → Analog In 3 (also used for USB+ when USB is in use) has a 1.5 kΩ pull-up resistor
 * Pin 4 → PWM, Analog In 2 (also used for USB- when USB is in use)
 * Pin 5 → PB5(NRES), Analog In 0
 * Example:
 * pinMode(5, INPUT); where 5 is the physical pin number, here Analog Input 0!
 *
 * While using USB, reconnect the digital pin 3 + 4 as far as used!!!
 *
 * 
 * 
 * ToDo:                
 * 
 */
/******************************************************************************************/
/*
 * Example of output:
 *
 */
/******************************************************************************************/
/******************************************************************************************/
/***  Declaration of global constants and initialization of variables. Add includes.  ***/
/******************************************************************************************/
/***  Software release and date  ***/
const char* sketchname            =  "Digispark_MiniTimer";
const char* revision              =  "R.1.0";
const char* author                =  "Olaf Meier";
const char* date                  =  "2014/07/14";

const unsigned int INTERVAL       = (1000 - 0);    // Create 1 second, considering sketch delays
long previousMillis               =  0;            // Store old millis

/***  Declare and initialize time variables for the 24h clock here  ***/
unsigned long seconds             =  0;            // Seconds
unsigned long minutes             =  0;            // Minutes
unsigned long hours               =  0;            // Hours
boolean toggleLed                 =  false;        // Switch off the LED to dislay 1s cycle
/******************************************************************************************/
/***  For continuous on/off cycles at same time remember the 24h cycle of the time base  ***/
/***  Enter the relay off period here  ***/
const byte RELOFFSECONDS          =  50;           // 50 seconds
const byte RELOFFMINUTES          =  59;           // 59 minutes
const byte RELOFFHOURS            =  11;           // 11 hours
/***  Enter the relay on period here  ***/
const byte RELONSECONDS           =  10;           // 10 seconds
const byte RELONMINUTES           =  0;
const byte RELONHOURS             =  0;
/******************************************************************************************/
unsigned long relOffTimeSeconds   =  0;            // Calculate the off period in seconds
unsigned long relOnTimeSeconds    =  0;            // Calculate the on period in seconds
unsigned long actualTimeSeconds   =  0;            // Store actual time in seconds here
/******************************************************************************************/
boolean relayFlag                 =  false;        // Relay is on or off; only for debug
unsigned long timeStamp           =  0;            // Store last relay off action
/******************************************************************************************/
/***  Declare constants and variables for the Digispark_MiniTimer  ***/
# define LEDPIN                      1             // LED pin 0 = Model B; pin 1 = Model A
# define RELAISPIN                   0             // Connect relay via 1k + BC547 to pin 0
/***  For Arduino Uno and during debugging use other pins to connect hardware  ***/
/*
# define LEDPIN                      3             // 
# define RELAISPIN                   13            // Connect relay via 1k + BC547 to pin 12
*/
/******************************************************************************************/
/******************************************************************************************/
void setup() {
  Serial.begin(38400);                             // Baud rate for Uno debug monitor 

  /***  Configure pins as output and set to low  ***/
  pinMode(LEDPIN, OUTPUT); 
  pinMode(RELAISPIN, OUTPUT); 
  digitalWrite(LEDPIN, LOW);
  digitalWrite(RELAISPIN, LOW);

  /***  Calculate the given on/off switching times of the relay in seconds  ***/
  relOffTimeSeconds = RELOFFSECONDS + (RELOFFMINUTES*60) + (RELOFFHOURS*60*60);
  relOnTimeSeconds = RELONSECONDS + (RELONMINUTES*60) + (RELONHOURS*60*60);

}                                                  // End of void setup() 
/******************************************************************************************/
/******************************************************************************************/
void loop() {
  /******************************************************************************************/
  /***  Debug some values over the Arduino Uno serial monitor  ***/
  Serial.print(hours);
  Serial.print(":");
  Serial.print(minutes);
  Serial.print(":");
  Serial.println(seconds);

  Serial.print("Actual time in seconds: ");
  Serial.println(actualTimeSeconds);
  
  Serial.print("Flag Relaisstatus: ");
  Serial.println(relayFlag);

  Serial.print("Switch on period in seconds: ");
  Serial.println(relOffTimeSeconds);

  Serial.print("Switch off period in seconds: ");
  Serial.println(relOnTimeSeconds);
  /***  End of debug  ***/
  /******************************************************************************************/

  clockCycle(INTERVAL);                            // Generates 1 second cycle + 24h time base
  digitalWrite(LEDPIN, toggleLed);                 // Toggle LED each second

  actualTimeSeconds = 0;                           // Reset old time stamp before saving new         
  actualTimeSeconds = seconds + (minutes*60)+(hours*60*60);

  /***  Switch on relay  ***/
  if(actualTimeSeconds > (relOffTimeSeconds+timeStamp)) {
    relayFlag = true;                              // Relay is switched on yet
    digitalWrite(RELAISPIN, HIGH);
  }
  /***  Switch off relay  ***/
 if(hours == 0 && minutes == 0 && seconds == 0)  
    timeStamp = 0;                                 // Reset time stamp
  if(actualTimeSeconds > (relOffTimeSeconds+relOnTimeSeconds+timeStamp)) {
    relayFlag = false;                             // Relay is switched off now
    timeStamp = seconds + (minutes*60)+(hours*60*60);// Store latest off time stamp now
    digitalWrite(RELAISPIN, LOW);
  }
 }                                                  // End of void loop()
/******************************************************************************************/
/******************************************************************************************/





