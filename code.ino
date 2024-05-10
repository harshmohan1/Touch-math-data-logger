#include <Wire.h>
#include <RTClib.h>
#include <SPI.h>
#include <SD.h>

RTC_DS3231 rtc;
#define buttonPin 0
int v = 0;
int x;
int z = 0;
const int button2[] = {1, 2};
const int button3[] = {14, 15, 16};
const int button4[] = {17, 18, 19, 20};
const int button5[] = {22, 23, 24, 25, 26};
const int button6[] = {27, 28, 29};
const int button7[] = {30, 31, 32, 33};
const int button8[] = {34, 35, 36, 37};
const int button9[] = {38, 39, 40, 41, 42};
const int ledPins[] = {13, 4, 5, 6, 7, 8, 9, 10, 11,}; // Array to store LED pins
const int maxCount = 10;  // Maximum number of LEDs you'll use
int clickCount = 0;
const int chipSelect = 53;



void setup() {
  Serial.begin(57600);
#ifndef ESP8266
  while (!Serial); // wait for serial port to connect. Needed for native USB
#endif
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }
  //rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
  pinMode(0, INPUT_PULLUP);
  Serial.println("Welcome to the Serial Monitor!");

  // Set all LED pins as outputs
  for (int i = 0; i < maxCount; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  for (int i = 0; i < 3; i++) {
    pinMode(button2[i], INPUT_PULLUP);

    // Initialize SD card communication
  }
  for (int i = 0; i < 4; i++) {
    pinMode(button3[i], INPUT_PULLUP);
    pinMode(button6[i], INPUT_PULLUP);
    // Initialize SD card communication
  }
  for (int x = 0; x < 5; x++) {
    Serial.println(x);
    pinMode(button4[x], INPUT_PULLUP);
    pinMode(button8[x], INPUT_PULLUP);
    pinMode(button7[x], INPUT_PULLUP);

    // Initialize SD card communication
  }
  for (int x = 0; x < 6; x++) {
    Serial.println(x);
    pinMode(button5[x], INPUT_PULLUP);
    pinMode(button9 [x], INPUT_PULLUP);


    // Initialize SD card communication
  }

  if (!SD.begin(chipSelect)) {
    Serial.println("Card initialization failed!");
    while (1);
  }
  Serial.println("Card initialized!");
  myFile = SD.open(filename, FILE_WRITE);
  if (myFile) {
    Serial.println("File opened for writing");
  } else {
    Serial.println("Failed to open file for writing");
  }




}

void loop() {
  // put your main code here, to run repeatedly:

  if (digitalRead(0) == LOW && clickCount == 0 ) // count 1
  { // Button is pressed
    clickCount = 1;
    timefunc();
    
  }
  else if (clickCount == 1) { // count 2
    
    x = button2[z];
    single();
    if (v == 2) {
      clickCount = 2;
      v = 0;
      z = 0;
    }
  }
  else if (clickCount == 2) { // count 3
    x = button3[z];
    single();
    if (v == 3) {
      clickCount = 3;
      v = 0;
      z = 0;
    }
  }
  else if (clickCount == 3) { // count 4
    x = button4[z];
    single();
    if (v == 4) {
      clickCount = 4;
      v = 0;
      z = 0;
    }
  }
  else if (clickCount == 4) { // count 5
    x = button5[z];
    single();
    if (v == 5) {
      clickCount = 5;
      v = 0;
      z = 0;
    }
  }
  else if (clickCount == 5) { // count 6
    x = button6[z];
    doubleclick();
    if (v == 3) {
      clickCount = 6;
      v = 0;
      z = 0;
    }
  }
  else if (digitalRead(button7[0]) == LOW && clickCount == 6) { // count 7

    z = 1;
    while (clickCount != 7) {

      x = button7[z];
      
      doubleclick();
      if (v == 3) {
        clickCount = 7;
        v = 0;
        z = 0;
      }
    }
  }
  else if (clickCount == 7) { // count 8

    x = button8[z];

    doubleclick();
    if (v == 4) {
      
      clickCount = 8;
      v = 0;
      z = 0;
    }
  }

  else if (digitalRead(button9[0]) == LOW && clickCount == 8) {
    z = 1;
    
    while (clickCount != 9) {
      x = button9[z];
      
      doubleclick();
      if (v == 4) {
        clickCount = 9;
        v = 0;
        z = 0;
      }
    }
  }
  updateLEDs();
  delay(100); // Tiny debounce delay
}

// funtional code ends here

void updateLEDs() { // to update LEDs
  // Turn off all LEDs first
  for (int i = 1; i < maxCount; i++) {
    digitalWrite(ledPins[i], LOW);
  }

  // Turn on LEDs based on clickCount
  digitalWrite(ledPins[clickCount], HIGH);
  if (clickCount != 0) {
    digitalWrite(3, LOW);
  }
}

void single() { // TO REGISTER SINGLE CLICKS
  if (digitalRead(x) == LOW) {
    timefunc();
    v++;
    z++;
  }
}

void doubleclick() { // FOR DOUBLE CLICKS
  if (digitalRead(x) == LOW) { // Button is pressed

    
    delay(400);
    while (true) {
      if (digitalRead(x) == LOW)
      {
        timefunc();
        v++;
        z++;
        break;
      }
    }
  }
}

void timefunc() { // TIME REGISTERING FUNCTION
  DateTime now = rtc.now();

  // Format the timestamp (adjust as needed)
  String timestamp = String(now.year()) + "-" + String(now.month()) + "-" + String(now.day()) + " " +
                     String(now.hour(), DEC) + ":" + String(now.minute(), DEC) + ":" + String(now.second(), DEC);

  // Print the timestamp to the serial monitor
  Serial.println(clickCount);
  Serial.println(",");
  Serial.println(v);
  Serial.println(",");
  Serial.println(timestamp);
  Serial.println(",");
  data();

  // Delay between readings (adjust as needed)

}

Void data(){
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(clickCount);
    dataFile.println(",");
    dataFile.println(v);
    dataFile.println(",");
    dataFile.println(timestamp);
    dataFile.println(",");

    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt")
}
