#include "BMS_module.h"

const char* chargeRateMessage[2] = {"Charge Rate is out of range" , "Die Laderate liegt außerhalb des Bereichs"};

void isChargeRateWithinLimit(BatteryInfo batteryData)
{
	// set the unit to default
	const char* UnitofChargeRate[] = {"A"};
	unsigned char defaultUnit = 1;

	unsigned char errorStatus;
	errorStatus = BatteryErrorStatus;
	if(batteryData.batteryChargeRate > 0.8)
	{
		errorStatus |= CHARGE_RATE_NOT_OK;
		printWarningToConsole(chargeRateMessage, UnitofChargeRate, batteryData.batteryChargeRate,
								defaultUnit, LanguageSelection);
	}
	BatteryErrorStatus = errorStatus;
}
