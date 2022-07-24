// LiquidCrystal I2C - Version: Latest 
/*RTC_LCD_i2c
Original code obtained from:
https://gist.github.com/laurenceHR/c08cd2a0944df78d168c
*/

#include <Wire.h>
#include <DS3231.h>//https://github.com/NorthernWidget/DS3231
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#define DHTPIN 2 //Pin digital 2
#define DHTTYPE DHT11

LiquidCrystal_I2C lcd(0x3F,16,2); //0x27 is the LCD Address
DHT dht(DHTPIN, DHTTYPE);

//SCL a A5 - SDA a A4

byte Year ;
byte Month ;
byte Date ;
byte DoW ;
byte Hour ;
byte Minute ;
byte Second ;
bool Century  = false;
bool h12 ;
bool PM ;
DS3231 Clock;

void setup(){
  Wire.begin();
  lcd.backlight();  
  lcd.init();
  dht.begin();

}

void loop(){
  //Variables Temp/Hum
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float hic = dht.computeHeatIndex(t, h, false); //Sensacion Termica
 
  //Fecha
  lcd.setCursor(0,0);
  lcd.print(Clock.getDate());
  lcd.print("/");
  if (Clock.getMonth(Century) < 10) {
  lcd.print(0);
  lcd.print(Clock.getMonth(Century));} 
  else {lcd.print(Clock.getMonth(Century));}
  lcd.print("/");
  lcd.print("20");
  lcd.print(Clock.getYear());
    
  //Hora
  lcd.setCursor(0,1);
  lcd.print(Clock.getHour(h12, PM)); 
  lcd.print(":"); 
  if (Clock.getMinute() < 10) {
    lcd.print("0");
    lcd.print(Clock.getMinute());} 
    else {lcd.print(Clock.getMinute());}
  lcd.print(":"); 
  if (Clock.getSecond() < 10) {
    lcd.print("0");
    lcd.print(Clock.getSecond());} 
    else {lcd.print(Clock.getSecond());}

  //Temp
  lcd.setCursor(12,0);
  lcd.print("T:");
  if (t < 10){
    lcd.print(t,0);
    lcd.print(" ");} 
    else {lcd.print(t,0);}
  lcd.setCursor(11,1);
  lcd.print("St:");
  if (hic < 10){
    lcd.print(hic,0);
    lcd.print(" ");}
    else {lcd.print(hic,0);}
  lcd.print(hic,0);

  //reset
  delay(1000);  
  //lcd.clear();
  //lcd.setCursor(9,0);
  //lcd.print("      ");
  //lcd.setCursor(0,1);
  //lcd.print("                "); 
  
}
