/**********************************************************************************************************/
/**********************************************************************************************************/
/***  Display dedicated time values in words  ***/
void timeRange(byte minutes, byte hours){
  byte index = 0;                                  // Show string "Meine Wortuhr: " 
  printStringWithShift(stringTimeText[index], shiftSpeed);
  Serial.print(stringTimeText[index]);
  index = 16;                                      // Show string "Es ist "
  printStringWithShift(stringTimeText[index], shiftSpeed);
  Serial.print(stringTimeText[index]);
  // ....
  /**********************************************************************************************************/
  /**********************************************************************************************************/
  /***  Test weather it is exactly a full hour  ***/
  if (minutes == 00){
    index = 17;                                    // Show string "genau "
    printStringWithShift(stringTimeText[index], shiftSpeed);  
    Serial.print(stringTimeText[index]);
    fullHour(hours);                               // Show value of hours
    index = 25;                                    // Show string "Uhr "
    printStringWithShift(stringTimeText[index], shiftSpeed);
    Serial.println(stringTimeText[index]);
  }                                                // Select full hour cycle
  /**********************************************************************************************************/
  /***  Test weather it is close to a full hour  ***/
  if (minutes >= 55 && minutes <= 59){
    index = 19;                                    // Show string "kurz "
    printStringWithShift(stringTimeText[index], shiftSpeed);
    Serial.print(stringTimeText[index]);
    index = 20;                                    // Show string "vor "
    printStringWithShift(stringTimeText[index], shiftSpeed);
    Serial.print(stringTimeText[index]);
    if (hours <=11){
      fullHour(hours+1);
      Serial.println();
    }
    if (hours == 12){
      printStringWithShift("eins ", shiftSpeed);
      Serial.println("eins ");                     // Show "Eins " instead of "Zwoelf "
    }
  }                                                // Select close to full hour cycle  
  /**********************************************************************************************************/
  /***  Test weather it is short after a full hour  ***/
  if (minutes >= 1 && minutes <= 5){
    index = 19;                                    // Show string "kurz "
    printStringWithShift(stringTimeText[index], shiftSpeed);  
    Serial.print(stringTimeText[index]);
    index = 21;                                    // Show string "nach "
    printStringWithShift(stringTimeText[index], shiftSpeed);
    Serial.print(stringTimeText[index]);
    if (hours == 1){
      printStringWithShift("eins ", shiftSpeed);    
      Serial.println("eins ");
    }
    else {
      fullHour(hours);                             // Show value of hours
      Serial.println();
    }
  }                                                // Select short after full hour cycle  
  /**********************************************************************************************************/
  /**********************************************************************************************************/
  /***  Test weather we have exactly 30 minutes  ***/
  if (minutes == 30){
    index = 24;                                    // Show "halb "
    printStringWithShift(stringTimeText[index], shiftSpeed);
    Serial.print(stringTimeText[index]);
    if (hours <=11){
      fullHour(hours+1);
      Serial.println();
    }
    if (hours == 12){
      printStringWithShift("eins ", shiftSpeed);
      Serial.println("eins ");                      // Show "Eins " instead of "Zwoelf "
    }
  }                                                // Select half hour cycle
  /**********************************************************************************************************/
  /***  Test weather we have short before half  ***/
  if (minutes >= 25 && minutes <= 29) {
    index = 19;                                    // Show string "kurz "
    printStringWithShift(stringTimeText[index], shiftSpeed);
    Serial.print(stringTimeText[index]);
    index = 20;                                    // Show string "vor "
    printStringWithShift(stringTimeText[index], shiftSpeed);
    Serial.print(stringTimeText[index]);
    index = 24;                                    // Show "halb "
    printStringWithShift(stringTimeText[index], shiftSpeed);
    Serial.print(stringTimeText[index]);
    if (hours <=11){
      fullHour(hours+1);
      Serial.println();
    }
    if (hours == 12){
      printStringWithShift("eins ", shiftSpeed);    
      Serial.println("eins ");
    }
  }                                                // Select short before half  
  /**********************************************************************************************************/
  /***  Test weather we have short after half  ***/
  if (minutes >= 31 && minutes <= 35){
    index = 19;                                    // Show string "kurz "
    printStringWithShift(stringTimeText[index], shiftSpeed);
    Serial.print(stringTimeText[index]);
    index = 21;                                    // Show string "nach "
    printStringWithShift(stringTimeText[index], shiftSpeed);
    Serial.print(stringTimeText[index]);  
    index = 24;                                    // Show "halb "
    printStringWithShift(stringTimeText[index], shiftSpeed);
    Serial.print(stringTimeText[index]);
    if (hours <=11){
      fullHour(hours+1);
      Serial.println();
    }
    if (hours == 12){
      printStringWithShift("eins ", shiftSpeed);
      Serial.println("eins ");
    }
  }                                                // Select short before half  
  /**********************************************************************************************************/
  /**********************************************************************************************************/
  /***  Test weather we have a quarter past full hour  ***/
  if (minutes == 15){
    index = 17;                                    // Show string "genau "
    printStringWithShift(stringTimeText[index], shiftSpeed);
    Serial.print(stringTimeText[index]);
    index = 23;                                    // "viertel nach " will be shown at array postion 23
    printStringWithShift(stringTimeText[index], shiftSpeed);
    Serial.print(stringTimeText[index]); 
    if (hours == 1) {
      printStringWithShift("eins ", shiftSpeed);
      Serial.println("eins ");                     // Show "Eins" instead of "Zwoelf"
    }
    else {
      fullHour(hours);
      Serial.println();
    }
  }                                                // Select a quarter past full hour
  /**********************************************************************************************************/
  /***  Test weather we have short after a quarter past full hour  ***/
  if (minutes >= 11 && minutes <= 14){
    index = 18;                                    // Show string "gleich "
    printStringWithShift(stringTimeText[index], shiftSpeed);
    Serial.print(stringTimeText[index]);
    index = 23;                                    // "viertel nach " will be shown at array postion 23
    printStringWithShift(stringTimeText[index], shiftSpeed);
    Serial.print(stringTimeText[index]); 
    if (hours == 1) {
      printStringWithShift("eins ", shiftSpeed);
      Serial.println("eins ");                     // Show "Eins" instead of "Zwoelf"
    }
    else {
      fullHour(hours);
      Serial.println();
    }  
  }                                                // Select a quarter past full hour
  /**********************************************************************************************************/
  /**********************************************************************************************************/
  /***  Test weather we have a quarter to full hour  ***/
  if (minutes == 45){
    index = 17;                                    // Show string "genau "
    printStringWithShift(stringTimeText[index], shiftSpeed);
    Serial.print(stringTimeText[index]);
    index = 22;                                    // "viertel vor " will be shown at array postion 22
    printStringWithShift(stringTimeText[index], shiftSpeed);
    Serial.print(stringTimeText[index]);
    if (hours <=11){
      fullHour(hours+1);
      Serial.println();
    }
    if (hours == 12){
      printStringWithShift("eins ", shiftSpeed);
      Serial.println("eins ");                     // Show "Eins " instead of "Zwoelf "
    }
  }                                                // Select a quarter to full hour
  /**********************************************************************************************************/
  /***  Test weather we have close to a quarter to full hour  ***/
  if (minutes >= 41 && minutes <=44){
    index = 18;                                    // Show string "gleich "
    printStringWithShift(stringTimeText[index], shiftSpeed);
    Serial.print(stringTimeText[index]);
    index = 22;                                    // "viertel vor " will be shown at array postion 22
    printStringWithShift(stringTimeText[index], shiftSpeed);
    Serial.print(stringTimeText[index]);
    if (hours <=11){
      fullHour(hours+1);
      Serial.println();
    }
    if (hours == 12){
      printStringWithShift("eins ", shiftSpeed);
      Serial.println("eins ");                     // Show "Eins " instead of "Zwoelf "
    }
  }                                                // Select close to a quarter to full hour
  /**********************************************************************************************************/
  /**********************************************************************************************************/
  /***  Test weather we have exactly 10 or 20 or 40 or 50 minutes  ***/
  if (minutes == 10 || minutes == 20 || minutes == 40 || minutes == 50){
    byte arrayDeviation = 0;                       // Index 10 will show correctly "Zehn"
    if (minutes < 30){
      if (minutes == 20)
        arrayDeviation = 7;                        // "Zwanzig " will be shown at array postion 13  
      index = 17;                                  // Show string "genau "
      printStringWithShift(stringTimeText[index], shiftSpeed);
      Serial.print(stringTimeText[index]);
      fullTenMinutes(minutes, arrayDeviation);
      index = 21;                                  // Show "nach"
      printStringWithShift(stringTimeText[index], shiftSpeed);
      Serial.print(stringTimeText[index]);
    if (hours == 1) {
      printStringWithShift("eins ", shiftSpeed);
      Serial.println("eins ");                     // Show "Eins" instead of "Zwoelf"
    }
    else {
      fullHour(hours);
      Serial.println();
    }
    }                                              // 1st half hour
    if (minutes > 30){
      if (minutes == 40)
        arrayDeviation = 27;                       // "Vierzig " will be shown at array postion 14  
      if (minutes == 50)
        arrayDeviation = 40;                       // "Fuenfzig " will be shown at array postion 15     
      index = 17;                                  // Show string "genau "
      printStringWithShift(stringTimeText[index], shiftSpeed);
      Serial.print(stringTimeText[index]);
      fullTenMinutes(minutes, arrayDeviation);
      index = 20;                                  // Show "vor "
      printStringWithShift(stringTimeText[index], shiftSpeed);
      Serial.print(stringTimeText[index]);
      if (hours <=11){
        fullHour(hours+1);
        Serial.println();
      }
      if (hours == 12){
        printStringWithShift("eins ", shiftSpeed);
        Serial.println("eins ");                   // Show "Eins" instead of "Zwoelf"
      }
    }                                              // 2nd half hour
  }                                                // Select exactly 10 or 20 or 40 or 50 minutes
  /**********************************************************************************************************/
  /***  Test weather we have close to 10 or 20 or 40 or 50 minutes  ***/
  if (minutes >= 6 && minutes <= 9){
    index = 18;                                    // Show string "gleich "
    printStringWithShift(stringTimeText[index], shiftSpeed);
    Serial.print(stringTimeText[index]);
    index = 10;                                    // Show "Zehn "
    printStringWithShift(stringTimeText[index], shiftSpeed);
    Serial.print(stringTimeText[index]);
    index = 21;                                    // Show "nach "
    printStringWithShift(stringTimeText[index], shiftSpeed);
    Serial.print(stringTimeText[index]);
    if (hours == 1) {
      printStringWithShift("eins ", shiftSpeed);
      Serial.println("eins ");                     // Show "Eins" instead of "Zwoelf"
    }
    else {
      fullHour(hours);
      Serial.println();
    }
  }
  if (minutes >= 16 && minutes <= 19){
    index = 18;                                    // Show string "gleich "
    printStringWithShift(stringTimeText[index], shiftSpeed);
    Serial.print(stringTimeText[index]);
    index = 13;                                    // Show "Zwanzig "
    printStringWithShift(stringTimeText[index], shiftSpeed);
    Serial.print(stringTimeText[index]);
    index = 21;                                    // Show "nach "
    printStringWithShift(stringTimeText[index], shiftSpeed);
    Serial.print(stringTimeText[index]);
    if (hours == 1) {
      printStringWithShift("eins ", shiftSpeed);
      Serial.println("eins ");                     // Show "Eins" instead of "Zwoelf"
    }
    else {
      fullHour(hours);
      Serial.println();
    }
  }
  if (minutes >= 36 && minutes <= 39){
    index = 18;                                    // Show string "gleich "
    printStringWithShift(stringTimeText[index], shiftSpeed);
    Serial.print(stringTimeText[index]);
    index = 13;                                    // Show "Zwanzig "
    printStringWithShift(stringTimeText[index], shiftSpeed);
    Serial.print(stringTimeText[index]);
    index = 20;                                    // Show "vor "
    printStringWithShift(stringTimeText[index], shiftSpeed);
    Serial.print(stringTimeText[index]);
    if (hours <=11){
      fullHour(hours+1);
      Serial.println();
    }
    if (hours == 12){
      printStringWithShift("eins ", shiftSpeed);
      Serial.println("eins ");                     // Show "Eins " instead of "Zwoelf "
    }
  }
  if (minutes >= 46 && minutes <= 49){
    index = 18;                                    // Show string "gleich "
    printStringWithShift(stringTimeText[index], shiftSpeed);
    Serial.print(stringTimeText[index]);
    index = 10;                                    // Show "Zehn "
    printStringWithShift(stringTimeText[index], shiftSpeed);
    Serial.print(stringTimeText[index]);
    index = 20;                                    // Show "vor "
    printStringWithShift(stringTimeText[index], shiftSpeed);
    Serial.print(stringTimeText[index]);
    if (hours <=11){
      fullHour(hours+1);
      Serial.println();
    }
    if (hours == 12){
      printStringWithShift("eins ", shiftSpeed);
      Serial.println("eins ");                     // Show "Eins " instead of "Zwoelf "
    }
  }                                                // Select close to 10 or 20 or 40 or 50 minutes
  /**********************************************************************************************************/
  /**********************************************************************************************************/
  /***  Test weather we have close to 5 minutes before half hour  ***/
  if (minutes >= 21 && minutes <= 24){
    index = 18;                                    // Show string "gleich "
    printStringWithShift(stringTimeText[index], shiftSpeed);
    Serial.print(stringTimeText[index]);
    index = 5;                                     // Show "Fuenf "
    printStringWithShift(stringTimeText[index], shiftSpeed);
    Serial.print(stringTimeText[index]);
    index = 20;                                    // Show "vor "
    printStringWithShift(stringTimeText[index], shiftSpeed);
    Serial.print(stringTimeText[index]);
    index = 24;                                    // Show "Halb "
    printStringWithShift(stringTimeText[index], shiftSpeed);
    Serial.print(stringTimeText[index]);
    if (hours <=11){
      fullHour(hours+1);
      Serial.println();
    }
    if (hours == 12){
      printStringWithShift("eins ", shiftSpeed);
      Serial.println("eins ");                     // Show "Eins " instead of "Zwoelf "
    }
  }                                                // Select close to 5 minutes to half hour
  /**********************************************************************************************************/
  /***  Test weather we have close to 5 minutes before full hour  ***/
  if (minutes >= 51 && minutes <= 54){
    index = 18;                                    // Show string "gleich "
    printStringWithShift(stringTimeText[index], shiftSpeed);
    Serial.print(stringTimeText[index]);
    index = 5;                                     // Show "Fuenf "
    printStringWithShift(stringTimeText[index], shiftSpeed);
    Serial.print(stringTimeText[index]);
    index = 20;                                    // Show "vor "
    printStringWithShift(stringTimeText[index], shiftSpeed);
    Serial.print(stringTimeText[index]);
    if (hours <=11){
      fullHour(hours+1);
      Serial.println();
    }
    if (hours == 12){
      printStringWithShift("eins ", shiftSpeed);
      Serial.println("eins ");                     // Show "Eins " instead of "Zwoelf "
    }
  }                                                // Select close to 5 minutes to half hour
  /**********************************************************************************************************/
}                                                  // End of function timeRange
/**********************************************************************************************************/
/**********************************************************************************************************/
/***  Show full hours only  ***/
void fullHour(byte hours){
  byte index = hours;
  printStringWithShift(stringTimeText[index], shiftSpeed);
  Serial.print (stringTimeText[index]);
}
/**********************************************************************************************************/
/***  Show exactly 10 or 20 or 40 or 50 minutes  ***/
void fullTenMinutes(byte minutes, byte arrayDeviation){
  byte index = minutes - arrayDeviation;
  printStringWithShift(stringTimeText[index], shiftSpeed);
  Serial.print (stringTimeText[index]);
}
/**********************************************************************************************************/
/**********************************************************************************************************/















