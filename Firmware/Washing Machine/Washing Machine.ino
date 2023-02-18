#include <LiquidCrystal.h>
const int next = A1;
const int motorPin = 13;
const int select = A0;
const int drainPin = 2; // input pin for drain switch
const int emptyWaterSwitch = 3; // input pin for empty water tank switch
const int relayPin = 7; // output pin for relay
const int buzzerPin = 8; // output pin for buzzer
const int lcdRsPin = 12; // LCD RS pin
const int lcdEnPin = 11; // LCD EN pin
const int lcdD4Pin = 5; // LCD D4 pin
const int lcdD5Pin = 4; // LCD D5 pin
const int lcdD6Pin = 9; // LCD D6 pin
const int lcdD7Pin = 10; // LCD D7 pin
LiquidCrystal lcd(lcdRsPin, lcdEnPin, lcdD4Pin, lcdD5Pin, lcdD6Pin, lcdD7Pin);

void setup() {
  pinMode(drainPin, INPUT);
  pinMode(emptyWaterSwitch, INPUT);
  pinMode(relayPin, OUTPUT);
  pinMode(motorPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);

  lcd.begin(20, 4); // Initialize 20x4 LCD
  lcd.clear(); // Clear the LCD display
  lcd.print("Washing Machine"); // Display message on LCD
  delay(2000);
}

void loop() {
  // Check if drain switch is closed
  while (digitalRead(drainPin) == LOW) 
  {
    // Wait for water to drain out
    lcd.clear();
    lcd.print("Waiting to Drain...");
    delay(500);
  }
  digitalWrite(relayPin, HIGH);

  // Check empty water tank switch
  if (digitalRead(emptyWaterSwitch) == HIGH) 
  {
    // Turn on relay to close drain valve
    lcd.setCursor(0, 1);
    lcd.print("Empty switch is Pressed");   
    digitalWrite(relayPin, HIGH);
    lcd.setCursor(0, 2);
    lcd.print("Relay Turned ON...");
    lcd.setCursor(0, 3);
    lcd.print("Drain Closed...");
  

  // Ask user to set washing timer value
  lcd.clear();
  lcd.print("Set washing time:");
  lcd.setCursor(3,1);
  lcd.print("30 Min");
  lcd.setCursor(3,2);
  lcd.print("45 Min");
  lcd.setCursor(3,3);
  lcd.print("60 Min");
  int washingTime = 0;
  int count = 0;
  // Code to get input from user and set washingTime variable
  while(!digitalRead(select))
  {
    if(digitalRead(next))
    {
      count = count + 1;
      delay(500);
    }
    else
    {
      if(count==1)
      {
        lcd.clear();
        lcd.setCursor(0,1);
        lcd.print("-->");
        lcd.setCursor(3,1);
        lcd.print("30 Min");
        lcd.setCursor(3,2);
        lcd.print("45 Min");
        lcd.setCursor(3,3);
        lcd.print("60 Min");
        washingTime = 2000;        
      }
      else if(count==2)
      {
        lcd.clear();
        lcd.setCursor(0,2);
        lcd.print("-->");
        lcd.setCursor(3,1);
        lcd.print("30 Min");
        lcd.setCursor(3,2);
        lcd.print("45 Min");
        lcd.setCursor(3,3);
        lcd.print("60 Min");
        washingTime = 4000; 
      }
      else if(count==3)
      {
        lcd.clear();
        lcd.setCursor(0,3);
        lcd.print("-->") ;
        lcd.setCursor(3,1);
        lcd.print("30 Min");
        lcd.setCursor(3,2);
        lcd.print("45 Min");
        lcd.setCursor(3,3);
        lcd.print("60 Min");
        washingTime = 6000;
      }    
      
      else if(count>=4)
      {
        count = 1;
      }
      else
      {
        count = 0;
      }  
    }
    delay(500);
  } 
   

  // Run washing motor till timer time elapses
  lcd.clear();
  lcd.print("Washing.....");
  
  int elapsed = 0;
  digitalWrite(motorPin, HIGH);
      
  while (elapsed < washingTime) {
    // Code to control washing motor based on washingTime variable
    delay(1000); // Delay 1 second
    elapsed += 1000; // Increment elapsed time by 1 second
  }
  digitalWrite(motorPin, LOW);

  // Open drain valve to drain water
  lcd.clear();
  lcd.print("Draining water");
  digitalWrite(relayPin, LOW);
  while (!digitalRead(drainPin)) {
    // Code to sound buzzer to indicate water is draining
    digitalWrite(buzzerPin, HIGH);
    delay(500);
    digitalWrite(buzzerPin, LOW);
    delay(500);
  }

  // Close drain valve
  lcd.clear();
  lcd.setCursor(3,2);
  lcd.print("Washing COMPLETED");
  digitalWrite(relayPin, HIGH);
  delay(3000); // Delay 5 minutes
  // Code to sound buzzer to indicate washing is complete
  digitalWrite(buzzerPin, HIGH);
  delay(2000);
  digitalWrite(buzzerPin, LOW);
  digitalWrite(relayPin, LOW);  
}

else
{
   lcd.clear();
  lcd.print("Waiting for Tank to Empty"); 
  delay(200)  ;
}
}
