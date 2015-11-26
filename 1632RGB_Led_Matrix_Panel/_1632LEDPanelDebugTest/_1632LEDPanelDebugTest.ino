/*******************************************************************************/
/* 1632LEDPanelDebugTest - Sketch zum Debuggen der Funktionsweise des 
 * 16*32 Adafruit RGB LED Panels
 * Obere Hälfte des Panels in Cyan, untere in Gelb
 * Die Framerate ist derzeit noch ohne sinnvolle Funktion
 *
 * Getestet mit:         Arduino Uno
 *                       Arduino IDE 1.63 / 1.64
 *
 * Referenz:             -
 *
 * Original Autor:       https://electronicfreakblog.wordpress.com/
 *                       
 * Autor:                Olaf Meier
 *                      
 *
 * Modifiziert von:
 * Autor:
 *
 * Hardware Verbindung:  Ardu  -  Gerät
 *                       +5V   -  -
 *                       GND   -  GND 4 mal
 *                       -     -  +5V / 2,5A Stromversorgung
 *                       -     -  GND        Stromversorgung
 *
 * Ergänzungen:          -
 *
 */
/*******************************************************************************/
/*******************************************************************************/
/***   Deklaration globaler Konstanten, Variablen, Import von Bibliotheken   ***/
/*******************************************************************************/
/***  Software Version und Datum  ***/
const char* sketchname            =  "1632LEDPanelDebugTest";
const char* revision              =  "R.0.1";
const char* author                =  "Olaf Meier";
const char* date                  =  "2015/11/17";

/*******************************************************************************/
/***  Deklariere Konstanten und Variablen für diesen Sketch  ***/
const unsigned int BAUDRATE       =  9600;         // Serieller Monitor Baud Rate
const byte DATA_R0                =  2;            // Obere Panelhälfte Daten Rot
const byte DATA_G0                =  3;            // Obere Panelhälfte Daten Grün
const byte DATA_B0                =  4;            // Obere Panelhälfte Daten Blau
const byte DATA_R1                =  5;            // Untere Panelhälfte Daten Rot
const byte DATA_G1                =  6;            // Untere Panelhälfte Daten Grün
const byte DATA_B1                =  7;            // Untere Panelhälfte Daten Blau

/***  Control pins  ***/
const byte CLK                    =  8;            // Clock
const byte OE                     =  9;            // Output Enable / Active LOW
const byte STB                    =  10;           // LAT Latch / Active LOW

/***  Addresss pins  ***/
const byte A                      =  A0;           // D14 Adresse A
const byte B                      =  A1;           // D15 Adresse B
const byte C                      =  A2;           // D16 Adresse C


uint32_t frameRate                =  50;           // Bildwiederholrate in Hz
/*******************************************************************************/
/*******************************************************************************/
void setup() {
  /***  Starte den seriellen Monitor und warte jetzt auf Daten zur Ausgabe  ***/
  Serial.begin(9600);                              // Starte seriellen Monitor

  /***  Initialisiere alle Datenpins  ***/
  for (int i = 2; i <= 7; i++)                     // Arduino Pin 2 bis 7
    pinMode(i, OUTPUT);                            // Alle Datenpins als Ausgang
  for (int i = 2; i <= 7; i++)                     // RGB Port 0 und 1 aus
    digitalWrite(i, LOW);                          // Datenpins sind Active HIGH

  /***  Initialisiere alle Kontrollpins  ***/
  for (int i = 8; i <= 10; i++)                    // Arduino Pin 8, 9, 10
    pinMode(i, OUTPUT);                            // Alle Kontrollpins Ausgang
  digitalWrite(CLK, LOW);                          // Takt ist Active HIGH
  digitalWrite(OE, HIGH);                          // Display aus /Active LOW
  digitalWrite(STB, HIGH);                         // Datenübernahme aus /Active LOW

  /***  Initialisiere alle Adresspins  ***/
  for (int i = 14; i <= 16; i++)                   // Arduino Pin A0 bis A2
    pinMode(i, OUTPUT);
  for (int i = 14; i <= 16; i++)
    digitalWrite(i, LOW);                          // Alle LOW=0, 9 / HIGH=8, 16

  /***  Panel für Testzwecke für 1 Sekunde einschalten  ***/
  digitalWrite(OE, LOW);                           // Output Enable. Active LOW
  delay(1000);
  digitalWrite(OE, HIGH);                          // LED Matrix Zeile ausschalten


  /***  Berechne die Verzögerung je Zeile  ***/
  frameRate = 1000000 / frameRate / 16;            // Für 16 darstellbare Zeilen

}                                                  // Ende Setup (Einmalig)
/*******************************************************************************/
/*******************************************************************************/
void loop() {

  digitalWrite(OE, HIGH);                          // LED Panel ausschalten
  digitalWrite(STB, HIGH);                         // Datenübernahme aus /Active LOW

  /***  Farbwerte der oberen Hälfte der Matrix  ***/
  digitalWrite(DATA_R0, LOW);
  digitalWrite(DATA_G0, HIGH);
  digitalWrite(DATA_B0, HIGH);

  /***  Farbwerte der unteren Hälfte der Matrix  ***/
  digitalWrite(DATA_R1, HIGH);
  digitalWrite(DATA_G1, HIGH);
  digitalWrite(DATA_B1, LOW);

  /***  Generiere den Takt des CLK-Pin für alle 32 LEDs mit 3 Farben  ***/
  for (int cycles = 0; cycles <= 191;  cycles ++)
  {
    digitalWrite(CLK, LOW);                        // Positive Flanke ist entscheidend
    digitalWrite(CLK, HIGH);                       // Positive Flanke ist entscheidend
  }
  digitalWrite(CLK, LOW);                          // Taktleitung wieder zurücksetzen
  digitalWrite(STB, LOW);                          // Übernahme der Daten ins Latch


  /***  Adressiere alle Zeilen mit den im Latch gespeicherten Daten  ***/
  for (int i = 0; i <= 7; i++)                     // Zeile 1 bis 8, 9 bis 16
    addressRow(i, frameRate);                      // Zeile, Verzögerung
}                                                  // Ende Loop (Endlos)
/*******************************************************************************/
/*******************************************************************************/
/***  Funktion adressiere Zeilen   ***/
void addressRow(byte _address, uint16_t _delay) {
  digitalWrite(OE, HIGH);                          // LED Matrix Zeile ausschalten
  if (_address > 7) _address = 7;                  // Fehlerabfrage Adressraum
  // delayMicroseconds(10000);                     // Debugging

  digitalWrite(A, bitRead(_address, 0));           // LSB
  digitalWrite(B, bitRead(_address, 1));
  digitalWrite(C, bitRead(_address, 2));           // MSB
  /***  RGB LED Matrix Panel Zeile einschalten  ***/
  digitalWrite(OE, LOW);                           // LED Matrix Zeile einschalten
  delayMicroseconds(_delay);
}                                                  // Ende der Funktion
/*******************************************************************************/
/*******************************************************************************/




