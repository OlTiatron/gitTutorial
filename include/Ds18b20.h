#ifndef Ds18b20_H
#define DS18b20_H

// #include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>






// Запустим библиотеку DS18
 

DeviceAddress tempDeviceAddress, insideThermometer, outsideThermometer;

int numberOfDevices; //здесь будем хранить количество найденных устройств на шине

void initDS18b20();
/*
// function печатает адрес найденного устройства
void printAddress(DeviceAddress deviceAddress);

// function to print считанную температуру
void printTemperature(DeviceAddress deviceAddress);

 // Ищет количество датчиков на линии
  numberOfDevices = sensors.getDeviceCount();
*/

  
# endif
