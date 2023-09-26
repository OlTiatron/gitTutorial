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


void initDS18b20()
{
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
            // установите разрешение равным биту TEMPERATURE_PRECISION 
            // (каждое устройство Dallas/Maxim поддерживает несколько различных разрешений)
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
  float Read_Temp_Ds18b20()
  {
    sensors.requestTemperatures(); // команда считать данные
      // перебрать количество дачиков, распечатайте данные о температуре
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
      }

    }
    return  sensors.getTempC(tempDeviceAddress);
  }


