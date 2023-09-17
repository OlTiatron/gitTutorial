#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define TEMPERATURE_PRECISION 9 // Lower resolution
// Настроим порт  ESP куда подключен DS18B20
#define ONER_WIRE_BUS 6

DeviceAddress tempDeviceAddress, insideThermometer, outsideThermometer;

int numberOfDevices; //здесь будем хранить количество найденных устройств на шине

// function печатает адрес найденного устройства
void printAddress(DeviceAddress deviceAddress)

// function to print считанную температуру
void printTemperature(DeviceAddress deviceAddress)
