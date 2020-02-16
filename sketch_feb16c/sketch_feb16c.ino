#include <LiquidCrystal.h>
#include <DHT11.h>    //라이브러리 불러옴
#define dataPin 8
#include <Servo.h>                           // Include servo library
 
Servo servoLeft;                             // Declare left and right servos
Servo servoRight;

int note[] = {1047, 1147, 1319, 1397, 1568, 1760, 1976, 2093};
LiquidCrystal lcd(1, 2, 4, 5, 6, 7); // Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)            //Signal 이 연결된 아두이노의 핀번호
DHT11 dht11(dataPin);        

int inputPin = 10;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status
 

void setup()
{
   Serial.begin(9600); //통신속도 설정
   
  pinMode(inputPin, INPUT);     // declare sensor as input
   lcd.begin(16,2);
}
 
void loop()
{
  int err;
  float temp, humi;
  
   servoLeft.attach(13);                      // Attach left signal to P13 
  servoRight.attach(12);                     // Attach right signal to P12

  // Full speed forward
 servoLeft.writeMicroseconds(1700);         // Left wheel counterclockwise
  servoRight.writeMicroseconds(1300);        // Right wheel clockwise
     delay(10000);     // ...for 10 seconds
      
 
 if((err=dht11.read(humi, temp))==0) //온도, 습도 읽어와서 표시
  {
     servoLeft.detach();                        // Stop sending servo signals
 servoRight.detach();  
   delay(2000);
    lcd.setCursor(0,0);
    lcd.print("temperature:");
    lcd.print(temp);
    Serial.print("temperature:");
    Serial.print(temp);
    lcd.setCursor(0,1);
    lcd.println();

   if(temp <= 20){
    tone(4, note[0], 500);               
    delay(750); 
     lcd.setCursor(0,0);
    lcd.print("temperature:");
    lcd.print(temp);
    lcd.print("Go to Section A:");
    Serial.print("temperature:");
    Serial.print(temp);
    lcd.setCursor(0,1);
    lcd.println();
    }
    
    else if((temp >= 38)&&(temp < 40)){
    tone(4, note[5], 500);    
    lcd.print("Go to Section B");           
    delay(750);     
      }
    else if((temp >= 40)&&(temp < 42)){
    tone(4, note[6], 500);               
    delay(750); 
      }
    else if((temp >= 42)&&(temp < 44)){
    tone(4, note[7], 500);               
    delay(750); 
    }
  }
 /* else                                //에러일 경우 처리
  {
    Serial.println();
    Serial.print("Error No :");
    Serial.print(err);
    Serial.println();    
  }*/
  
   val = digitalRead(inputPin);  // read input value
  if (val == HIGH) {            // check if the input is HIGH
     if (pirState == LOW) {
      // we have just turned on
    Serial.println("Motion detected!");
      
      // We only want to print on the output change, not state
      pirState = HIGH;
    }
  }
  else {
    if (pirState == HIGH){
      // we have just turned of
      Serial.println("Motion ended!");
        servoLeft.writeMicroseconds(1700);         // Left wheel counterclockwise
  servoRight.writeMicroseconds(1300); 
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }
}


 
