#include <Arduino.h>
#include <Ds18b20.h>

//Распаянные светодиоды
#define LED1 12
#define LED2 13

void setup() 
{
  // put your setup code here, to run once:
 
  Serial.begin(115200);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  // Погнали
  delay(1000);
  initDS18b20();
  
}

void loop() 
{
  // put your main code here, to run repeatedly:
  // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
  Serial.print("Zapuskaem preobrazovanie...");

 
 
      if ( (Read_Temp_Ds18b20()) > 27.0 )
      {
        /* code */
        digitalWrite(LED1,HIGH);
        Serial.println("Rele ON");
      }
      else 
      {
        /* code */
        digitalWrite(LED1,LOW);
        Serial.println("Rele OFF");
      }
      Serial.println("DONE");
       delay(1000);
    }
        
  
   
    
      
 