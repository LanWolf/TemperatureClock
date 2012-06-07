/* Klok, temperatuur
    by Rick   
    
   Klokchip :
     Pin 6 naar pin 5 op arduino 
     Pin 5 naar pin 4 op arduino
     
   Led:
     Pin 13
     
   LCD:
     PIN 12,11 6,5,4,3
     
   DHT11:
     Pin 2

*/

// Import needed libraries
#include <LiquidCrystal.h>

#include <dht11.h>
#include <Wire.h>
// Timer Lib
#include "RTClib.h"
// DS18B20 Libs

#include <OneWire.h>
#include <DallasTemperature.h>

// Declare objects
RTC_DS1307 RTC;
dht11 DHT11;
LiquidCrystal lcd(12, 11, 6, 5, 4, 3);

//  Declare Constants, Pin Numbers 
#define DHT11PIN 2
#define LEDPIN 13
#define ONE_WIRE_BUS 10

// DS18S20 Temperature chip i/o
OneWire oneWire(ONE_WIRE_BUS); 
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

// SETUP: RUNS ONCE 
void setup()   
{
  // start de clock 
    Wire.begin();
    RTC.begin();
     // following line sets the RTC to the date & time this sketch was compiled
    //RTC.adjust(DateTime(__DATE__, __TIME__));
    
   // Start up the library
   sensors.begin(); // IC Default 9 bit. If you have troubles consider upping it 12. Ups the delay giving the IC more time to process the temperature measurement 
   sensors.setResolution(12);
   // initialize the lcd
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("");
  pinMode(LEDPIN, OUTPUT);
  
 

} // end setup 


// LOOP: RUNS CONSTANTLY
void loop()   
{
  DateTime now = RTC.now();

  int chk = DHT11.read(DHT11PIN);

  //lcd.print("Read sensor: ");
  switch (chk)
  //{
    lcd.cursor() ;
    lcd.home();
    
  if(now.day() < 10){
    lcd.print("0");
   }
    lcd.print(now.day(), DEC);
  lcd.print('/');
  
  if(now.month() < 10){
    lcd.print("0");
   }
    lcd.print(now.month(), DEC);
    lcd.print('/');

    lcd.print(now.year(), DEC);
    
    lcd.print(' ');
    
    lcd.print(now.hour(), DEC);
    lcd.print(':');
   if(now.minute() < 10){
    lcd.print("0");
   }
    lcd.print(now.minute(), DEC);
    lcd.print(':');
   if(now.second() < 10){
    lcd.print("0");
   }
    lcd.print(now.second(), DEC);
    //Serial.println();
    
    //case 0: lcd.println("OK"); break;
    //case -1: lcd.clear() ;lcd.println("Checksum error"); break;
    //case -2: lcd.clear() ; lcd.println("Time out error"); break;
    //default: lcd.clear() ;lcd.println("Unknown error"); break;
  //}
  lcd.setCursor(0,1);
  lcd.print((float)DHT11.temperature, 0);
  lcd.print("\337C");
  
if ((float)DHT11.temperature >24 )
{
  // action A
  digitalWrite(LEDPIN, HIGH);
}
else
{
  // action B
  digitalWrite(LEDPIN, LOW);
}


  lcd.setCursor(5,1);
  lcd.print((float)DHT11.humidity, 0);
  lcd.print("% ");

 // call sensors.requestTemperatures() to issue a global temperature
// request to all devices on the bus
  sensors.requestTemperatures(); // Send the command to get temperatures

  lcd.print(sensors.getTempCByIndex(0)); // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire
  lcd.print("\337C");

  //lcd.clear();
}// End main loop

// Declare User-written Functions 


// ( THE END )
