#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

//Распаянные светодиоды
#define LED1 12
#define LED2 13
#define TEMPERATURE_PRECISION 9 // Lower resolution
// Настроим порт  ESP куда подключен DS18B20
#define ONER_WIRE_BUS 6
// Создаем экземпляр класса от OneWire 
OneWire oneWire(ONER_WIRE_BUS);
//Подключим библиотеку в наш проект
DallasTemperature sensors(&oneWire);
//Создадим массивы для хранения адресов нескольких датчиков
DeviceAddress tempDeviceAddress, insideThermometer, outsideThermometer;

int numberOfDevices; //здесь будем хранить количество найденных устройств на шине
// Переменная для хранения адресов найденных устройств
// DeviceAddress tempDeviceAddress; // Мы будем использовать эту переменную для хранения адреса найденного устройства

// function распечатаем адрес найденного устройства
void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}


// function to print the temperature for a device
void printTemperature(DeviceAddress deviceAddress)
{
  // method 1 - slower
  //Serial.print("Temp C: ");
  //Serial.print(sensors.getTempC(deviceAddress));
  //Serial.print(" Temp F: ");
  //Serial.print(sensors.getTempF(deviceAddress)); // Makes a second call to getTempC and then converts to Fahrenheit

  // method 2 - faster
  float tempC = sensors.getTempC(deviceAddress);
  if (tempC == DEVICE_DISCONNECTED_C)
  {
    Serial.println("Error: Could not read temperature data");
    return;
  }
  Serial.print("Temp C: ");
  Serial.print(tempC);
  Serial.print(" Temp F: ");
  Serial.println(DallasTemperature::toFahrenheit(tempC)); // Converts tempC to Fahrenheit
}

void setup() 
{
  // put your setup code here, to run once:
 
  Serial.begin(115200);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  // Погнали
  delay(1000);
  // Запустим библиотеку DS18
  sensors.begin();
  // Ищем количество датчиков на линии
  numberOfDevices = sensors.getDeviceCount();
  Serial.print("Found ");
  Serial.print(numberOfDevices, DEC);
  Serial.println(" datchik.");
  // выясним как запитан датчик
  Serial.print("Parasite power is: ");
  if (sensors.isParasitePowerMode()) Serial.println("ON");
  else Serial.println("OFF");


  // распечатаем адреса всех найденных устройств
  for (int i = 0; i < numberOfDevices; i++)
  {
    // Search the wire for address
    if (sensors.getAddress(tempDeviceAddress, i))
    {
      Serial.print("Found device ");
      Serial.print(i, DEC);
      Serial.print(" with address: ");
      printAddress(tempDeviceAddress);
      Serial.println();

      Serial.print("Setting tochnost preobrazovania ");
      Serial.println(TEMPERATURE_PRECISION, DEC);

      // set the resolution to TEMPERATURE_PRECISION bit (Each Dallas/Maxim device is capable of several different resolutions)
      sensors.setResolution(tempDeviceAddress, TEMPERATURE_PRECISION);

      Serial.print("Tochnost preobrazovania sostavliaet: ");
      Serial.print(sensors.getResolution(tempDeviceAddress), DEC);
      Serial.println();
    } else {
      Serial.print("Found gost device at ");
      Serial.print(i, DEC);
      Serial.print(" but could not detect address. Check power and cabling");
    }

  }

}

void loop() {
  // put your main code here, to run repeatedly:
  // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
  Serial.print("Zapuskaem preobrazovanie...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");
 // Loop through each device, print out temperature data
  for (int i = 0; i < numberOfDevices; i++)
  {
    // Search the wire for address
    if (sensors.getAddress(tempDeviceAddress, i))
    {
      // Output the device ID
      Serial.print("Temperature for device: ");
      Serial.println(i, DEC);

      // It responds almost immediately. Let's print out the data
      printTemperature(tempDeviceAddress); // Распечатаем температуру с датчика
      if ( (sensors.getTempC(tempDeviceAddress)) > 27.0 )
      {
        /* code */
        digitalWrite(LED1,HIGH);
        Serial.println("Rele ON");
      }
      
    }
        //else ghost device! Check your power requirements and cabling
        // Serial.print("ERROR");

  }
      /*
      digitalWrite(LED1,HIGH);
      Serial.print("Led1 On");
      delay(1000);
      digitalWrite(LED1, LOW);
      Serial.println("OFF");
      delay(1000); // для гит хаба
      */
     delay(1000);
}
