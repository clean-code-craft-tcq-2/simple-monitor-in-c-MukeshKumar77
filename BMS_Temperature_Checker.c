#include "BMS_module.h"

const char* temperatureMessage[2] = {"Temperature  is out of range" , "Die Temperatur liegt außerhalb des zulässigen Bereichs"};

void convertDataToStandardUnit(BatteryInfo* data, unsigned char selectedUnit)
{
	if((selectedUnit & TEMPERATURE_IN_CELSIUS) == TEMPERATURE_IN_CELSIUS)
	{
		//do nothing
	}
	else if ((selectedUnit & TEMPERATURE_IN_FAHRENHEIT) == TEMPERATURE_IN_FAHRENHEIT)
	{
		data->batteryTemperature = ((data->batteryTemperature - 32) * 5 / 9);
	}
}

void isBatteryTemperatureWithinLimit(BatteryInfo batteryData)
{
	//take a copy of temperature to print at console
	float temperature = batteryData.batteryTemperature;

	convertDataToStandardUnit(&batteryData, BatteryDataUnitSelection);

	unsigned char errorStatus;
	errorStatus = BatteryErrorStatus;
	if(batteryData.batteryTemperature < 0)
	{
		errorStatus |= LOW_BATTERY_TEMPERATURE;
		batteryData.batteryTemperature = temperature;
		printWarningToConsole(temperatureMessage, UnitofBatteryData, batteryData.batteryTemperature,
								BatteryDataUnitSelection, LanguageSelection);
	}
	else if(batteryData.batteryTemperature > 45)
	{
		errorStatus |= HIGH_BATTERY_TEMPERATURE;
		batteryData.batteryTemperature = temperature;
		printWarningToConsole(temperatureMessage, UnitofBatteryData, batteryData.batteryTemperature,
								BatteryDataUnitSelection, LanguageSelection);
	}
	BatteryErrorStatus = errorStatus;
}

