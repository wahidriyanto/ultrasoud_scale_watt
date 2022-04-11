// Digital Scale using Arduino By Engr. Wahid riyanto
//FOLLOW INSTAGRAM SMBD.TECH
// SMBD VLOG YouTube Channel

#include <HX711_ADC.h> // link downlod https://github.com/olkal/HX711_ADC
#include <Wire.h>
#include <LiquidCrystal_I2C.h> // LiquidCrystal_I2C library
HX711_ADC LoadCell(5, 6);     // parameters: dt pin, sck pin
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27,20,4);
int led = 1;      //pin led 
int taree = 2;    // pin push on zero
int buzzer = 10; 
int a = 0;
float b = 0;

void setup() {
  Serial.begin(57600);
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode (taree, INPUT_PULLUP);
  LoadCell.begin(); // start connection to HX711
  LoadCell.start(2000); // load cells gets 2000ms of time to stabilize
  LoadCell.setCalFactor(410.2); // calibration factor for load cell => strongly dependent on your individual setup
  lcd.init();  // begins connection to the LCD module
  lcd.backlight(); // turns on the backlight

  tone(buzzer, 1200);
  delay(100);
  noTone(buzzer);
  
  lcd.setCursor(1, 0); // set cursor to first row
  lcd.print("Digital Scale "); // print out to LCD
  lcd.setCursor(0, 1); // set cursor to first row
  lcd.print("By: Egr fitri"); // print out to LCD
  delay(3000);
  lcd.clear();
  tone(buzzer, 1200);
  delay(300);
  noTone(buzzer);
  
}
void loop() { 

  lcd.setCursor(1, 0); // set cursor to first row
  lcd.print(" Digital Scale "); // print out to LCD
  LoadCell.update(); // retrieves data from the load cell
  float i = LoadCell.getData(); // get output value
  Serial.println(i);
 if (i<0)
 {
  i = i * (-1);
  lcd.setCursor(0, 1);
  lcd.print("-");
  lcd.setCursor(9, 1);
  lcd.print("-");
 }
 else
 {
   lcd.setCursor(0, 1);
  lcd.print(" ");
   lcd.setCursor(9, 1);
  lcd.print(" ");
 }
  
  lcd.setCursor(1, 1); // set cursor to secon row
  lcd.print(i, 2); // print out the retrieved value to the second row
  lcd.print("g ");
  float w = i/14.68;  //berat di kalikan dengan rumus watt
  lcd.setCursor(10, 1);
  lcd.print(w, 2);
  lcd.print("W ");

  if (i>=5000)  // jika nilai 1 lebih besar dri 5kg maka buzzer akan bunyi
  {
    i=0;
   tone(buzzer, 1600);
  delay(200);
  noTone(buzzer);
    digitalWrite(led, HIGH);
   lcd.setCursor(0, 0); // set cursor to secon row
  lcd.print("  Over Loaded   "); 
  delay(200);
  }
  digitalWrite(led, LOW);
  if (digitalRead (taree) == LOW)
  {
  tone(buzzer, 5000);
  delay(100);
  noTone(buzzer);
    digitalWrite(led, HIGH);
    lcd.setCursor(0, 1); // set cursor to secon row
    lcd.print("    STORED...    ");
    LoadCell.start(5000);
     tone(buzzer, 5000);
  delay(300);
  noTone(buzzer);
  lcd.setCursor(0, 1);
   lcd.print("                ");
  }
}
