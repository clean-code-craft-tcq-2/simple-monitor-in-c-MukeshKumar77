#include "BMS_module.h"

const char* SoCMessage[2] = {"State of Charge is out of range" , "Der Ladezustand ist außerhalb des Bereichs"};

void isStateOfChargeWithinLimit(BatteryInfo batteryData)
{
	// set the unit to default
	const char* UnitofSOC[] = {"%"};
	unsigned char defaultUnitIdx = 1;

	unsigned char errorStatus;
	errorStatus = BatteryErrorStatus;
	if(batteryData.batteryStateOfCharge < 20)
	{
		errorStatus |= LOW_STATE_OF_CHARGE;
		printWarningToConsole(SoCMessage, UnitofSOC, batteryData.batteryStateOfCharge,
								defaultUnitIdx, LanguageSelection);
	}
	else if(batteryData.batteryStateOfCharge > 80)
	{
		errorStatus |= HIGH_STATE_OF_CHARGE;
		printWarningToConsole(SoCMessage, UnitofSOC, batteryData.batteryStateOfCharge,
								defaultUnitIdx, LanguageSelection);
	}
	BatteryErrorStatus = errorStatus;
}

