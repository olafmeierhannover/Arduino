/*******************************************************************************/
/* 1632LEDPanelBasic - Simpler Sketch zum Debuggen der Funktionsweise des
 * 16*32 Adafruit RGB LED Panels auch ohne Library.
 * Die Verkabelung erfolgt allerdings entsprechend der Adafruit Library.
 * Der Dateneingang mit Blick auf die LEDs befindet sich rechts.
 * Der Bildaufbau ist von rechts nach links und von oben nach unten.
 * Panel ist in 2 Sektionen unterteilt mit den Zeilen 0 bis 7 über R0, G0, B0
 * sowie den Zeilen 8 bis 15 über den Port RGB1 mit R1, G1, B1 erreichbar.
 *
 * Getestet mit:         Arduino Uno
 *                       Arduino IDE 1.6.3 / 1.6.4 / 1.6.6
 *
 * Referenz:             https://learn.adafruit.com/32x16-32x32-rgb-led-matrix/
 *
 * Original Autor:       https://electronicfreakblog.wordpress.com/
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
const char* sketchname            =  "1632LEDPanelBasic";
const char* revision              =  "R.1.0";
const char* author                =  "Olaf Meier";
const char* date                  =  "2015/11/29";

/*******************************************************************************/
/***  Deklariere Konstanten für die Datenpins der RGB Farbenports  ***/
const unsigned int BAUDRATE       =  9600;         // Serieller Monitor Baud Rate
const byte DATA_R0                =  2;            // Obere Panelhälfte Daten Rot
const byte DATA_G0                =  3;            // Obere Panelhälfte Daten Grün
const byte DATA_B0                =  4;            // Obere Panelhälfte Daten Blau
const byte DATA_R1                =  5;            // Untere Panelhälfte Daten Rot
const byte DATA_G1                =  6;            // Untere Panelhälfte Daten Grün
const byte DATA_B1                =  7;            // Untere Panelhälfte Daten Blau
/***  Deklariere Konstanten für die Steuerpins  ***/
const byte CLK                    =  8;            // Clock, pos. Flanke
const byte OE                     =  9;            // Output Enable, neg. Flanke
const byte STB                    =  10;           // LAT Latch (Strobe), neg. Flanke
/***  Deklariere Konstanten für die Adressspins  ***/
/*  msb   lsb
    C  B  A  Zeile von oben
    0  0  0    0
    0  0  1    1
    0  1  0    2
    0  1  1    3
    1  0  0    4
    1  0  1    5
    1  1  0    6
    1  1  1    7  */
const byte A                      =  A0;           // D14 Adresse A (LSB)
const byte B                      =  A1;           // D15 Adresse B
const byte C                      =  A2;           // D16 Adresse C (MSB)
/*******************************************************************************/
/*******************************************************************************/
void setup() {
  /***  Starte den seriellen Monitor und warte jetzt auf Daten zur Ausgabe  ***/
  Serial.begin(9600);                              // Starte seriellen Monitor
  /*****************************************************************************/
  /***  Initialisiere die 6 Datenpins des RGB Port 0 und RGB Port 1  ***/
  for (int i = 2; i <= 7; i++)                     // RGB0=Pin 2-4 und RGB1=5-7
    pinMode(i, OUTPUT);                            // Alle Datenpins als Ausgang
  for (int i = 2; i <= 7; i++)                     // RGB Port 0 und 1 auf aus
    digitalWrite(i, LOW);                          // Datenpins sind Active HIGH

  /***  Initialisiere alle 3 Adresspins  ***/
  for (int i = 14; i <= 16; i++)                   // Arduino Pin A0 bis A2
    pinMode(i, OUTPUT);
  for (int i = 14; i <= 16; i++)
    digitalWrite(i, LOW);                          // Alle LOW=0, 8 / HIGH=7, 15

  /***  Initialisiere alle 3 Steuerpins  ***/
  for (int i = 8; i <= 10; i++)                    // Arduino Pin 8, 9, 10
    pinMode(i, OUTPUT);                            // Alle Steuerpins Ausgang
  digitalWrite(CLK, LOW);                          // Taktleitung zurücksetzen
  digitalWrite(OE, HIGH);                          // Panel aus. Ein mit negativer Flanke
  digitalWrite(STB, LOW);                          // Gespeicherte Daten aus Latch 
  /*****************************************************************************/
  /***  Schieberegister / Latch mit RGB-Daten, hier alles mit LOW vorbelegen  ***/
  for (int p = 0; p < 32;  p++)                    // 32 Pixel je Zeile
  {
    digitalWrite(CLK, LOW);                        // Taktleitung zurücksetzen
    digitalWrite(CLK, HIGH);                       // Datenübernahme mit positiver Flanke
  }
  digitalWrite(CLK, LOW);                          // Taktleitung zurücksetzen
  /***  Strobe-Pulse RGB Port0/1 Schieberegister fix ins Latch speichern  ***/
  digitalWrite(STB, HIGH);                         // Datendurchgang HIGH
  digitalWrite(STB, LOW);                          // Daten ins Latch gespeichert LOW
  /*****************************************************************************/
  /***  Pixelaufbau einer Zeile                                              ***/
  /***  Ausgabe der Farbwerte der obersten Zeilen 0 und 8 (bzw. 1 und 9)  
  /***  Im oberen Segment wird die Farbe Cyan und im unteren Gelb angezeigt  
  /***  Das Panel wird an dieser Stelle bereits eingeschaltet, um den 
  /***  Pixelaufbau der Zeile sichtbar zu machen.                            ***/
  /*****************************************************************************/
  digitalWrite(OE, LOW);                           // Panel ein, mit negativer Flanke
  /***  Farbwerte der oberen Hälfte der Matrix  ***/
  digitalWrite(DATA_R0, LOW);
  digitalWrite(DATA_G0, HIGH);
  digitalWrite(DATA_B0, HIGH);
  /***  Farbwerte der unteren Hälfte der Matrix  ***/
  digitalWrite(DATA_R1, HIGH);
  digitalWrite(DATA_G1, HIGH);
  digitalWrite(DATA_B1, LOW);

  for (int p = 0; p < 32;  p++)                    // 32 Pixel je Zeile
  {
    digitalWrite(CLK, LOW);                        // Taktleitung zurücksetzen
    digitalWrite(CLK, HIGH);                       // Datenübernahme mit positiver Flanke
    /***  Strobe-Pulse RGB Port0/1 Schieberegister fix ins Latch speichern  ***/
    digitalWrite(STB, HIGH);                       // Datendurchgang HIGH
    digitalWrite(STB, LOW);                        // Daten ins Latch gespeichert LOW
 //   delay(100);                                    // Optional Delay for debugging!
  }
  digitalWrite(CLK, LOW);                          // Taktleitung zurücksetzen

  digitalWrite(OE, HIGH);                          // Panel ausschalten.
}                                                  // Ende Setup (Einmalig)
/*******************************************************************************/
/*******************************************************************************/
void loop() {
  digitalWrite(OE, LOW);                           // Optional Panel einschalten
  /***  Adressiere alle Zeilen mit den im Latch gespeicherten Daten  ***/
  for (int i = 0; i <= 7; i++)  {                  // Zeile 1 bis 8, 9 bis 16
    addressRow(i);                                 // Zeile, Verzögerung
//    delay(100);                                    // Optional Delay for debugging!
  }
}                                                  // Ende Loop (Endlos)
/*******************************************************************************/
/*******************************************************************************/
/***  Funktion zum Zeilenaufbau. Jede Zeile des Panels ansprechen   ***/
void addressRow(byte _address) {
  digitalWrite(A, bitRead(_address, 0));           // LSB
  digitalWrite(B, bitRead(_address, 1));
  digitalWrite(C, bitRead(_address, 2));           // MSB
}                                                  // Ende der Funktion addressRow
/*******************************************************************************/
/*******************************************************************************/




