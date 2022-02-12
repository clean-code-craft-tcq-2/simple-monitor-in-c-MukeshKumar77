#include "BMS_module.h"

const char* temperatureMessage[5][2] = {
		{"Error: Temperature is below the range" , "Fehler: Temperatur liegt unterhalb des Bereichs"},
		{"Warning: Temperature is too low " , "Warnung: Die Temperatur ist zu niedrig"},
		{"Temperature is normal" , "Temperatur ist normal"},
		{"Warning: Temperature is too high" , "Warnung: Die Temperatur ist zu hoch"},
		{"Error: Temperature is above the range" , "Fehler: Temperatur liegt über dem Bereich"}};

float fahrenheitTemp;

void convertDataToStandardUnit(BatteryInfo* data, unsigned char selectedUnit)
{
	if ((selectedUnit & TEMPERATURE_IN_FAHRENHEIT) == TEMPERATURE_IN_FAHRENHEIT)
	{
		data->batteryTemperature = ((data->batteryTemperature - 32) * 5 / 9);
	}
}

static bool checkForTemperatureWarningFirst(float parameter);

static bool checkForTemperatureWarningFirst(float parameter)
{
	bool retVal;
	retVal = ((checkForLimit(temperatureMessage, UnitofBatteryData, parameter, BatteryDataUnitSelection, LOW_WARNING_MESSAGE, LOW_TEMPERATURE_WARNING)) ||
						(checkForLimit(temperatureMessage, UnitofBatteryData, parameter, BatteryDataUnitSelection, NORMAL_MESSSAGE, NORMAL_TEMPERATURE)) ||
						(checkForLimit(temperatureMessage, UnitofBatteryData, parameter, BatteryDataUnitSelection, HIGH_WARNING_MESSAGE, HIGH_TEMPERATURE_WARNING)));
	return(retVal);
}

void isBatteryTemperatureWithinLimit(BatteryInfo batteryData)
{
	//take a copy of temperature to print at console
	fahrenheitTemp = batteryData.batteryTemperature;

	convertDataToStandardUnit(&batteryData, BatteryDataUnitSelection);

	unsigned char errorStatus;
	errorStatus = BatteryErrorStatus;
	errorStatus = checkForTemperatureWarningFirst(batteryData.batteryTemperature);

	if(!errorStatus)
	{
		errorStatus = ((checkForLimit(temperatureMessage, UnitofBatteryData, batteryData.batteryTemperature, BatteryDataUnitSelection, LOW_BREACH_MESSAGE, LOW_TEMPERATURE_BREACH)) ||
						(checkForLimit(temperatureMessage, UnitofBatteryData, batteryData.batteryTemperature, BatteryDataUnitSelection, HIGH_BREACH_MESSAGE, HIGH_TEMPERATURE_BREACH)));
		BatteryErrorStatus = errorStatus;
	}
}
