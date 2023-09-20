#ifndef __Ds18b20_H
#define __DS18b20_H

#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define TEMPERATURE_PRECISION 9 // Lower resolution

#define ONER_WIRE_BUS 6 // Настроим порт  ESP куда подключен DS18B20

// Создаем экземпляр класса от OneWire 
 OneWire oneWire(ONER_WIRE_BUS);
//Подключим библиотеку в наш проект
 DallasTemperature sensors(&oneWire);


// Запустим библиотеку DS18
 

DeviceAddress tempDeviceAddress, insideThermometer, outsideThermometer;

int numberOfDevices; //здесь будем хранить количество найденных устройств на шине
/*
// function печатает адрес найденного устройства
void printAddress(DeviceAddress deviceAddress);

// function to print считанную температуру
void printTemperature(DeviceAddress deviceAddress);

 // Ищет количество датчиков на линии
  numberOfDevices = sensors.getDeviceCount();
*/
# endif
