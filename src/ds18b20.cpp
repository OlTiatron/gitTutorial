#include <OneWire.h>
#include <DallasTemperature.h>
 #include <Ds18b20.h>
// #include <Arduino.h>

#define TEMPERATURE_PRECISION 9 // Lower resolution
#define ONER_WIRE_BUS 6 // Настроим порт  ESP куда подключен DS18B20

//Создадим массивы для хранения адресов нескольких датчиков
DeviceAddress tempDeviceAddress, insideThermometer, outsideThermometer;

int numberOfDevices; //здесь будем хранить количество найденных устройств на шине

// Создаем экземпляр класса от OneWire 
OneWire oneWire(ONER_WIRE_BUS);

//Подключим библиотеку в наш проект
DallasTemperature sensors(&oneWire);
void initDS18b20(){
sensors.begin();
}
/*

  // sensors.begin();

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

*/