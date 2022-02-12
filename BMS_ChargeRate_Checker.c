#include "BMS_module.h"

const char* chargeRateMessage[5][2] = {
		{"Error: Charge Rate is below the range" , "Fehler: Ladestrom liegt unterhalb des Bereichs"},
		{"Warning: Charge Rate is too low " , "Warnung: Die Ladestrom ist zu niedrig"},
		{"Charge Rate is normal" , "Ladestrom ist normal"},
		{"Warning: Charge Rate is too high" , "Warnung: Die Ladestrom ist zu hoch"},
		{"Error: Charge Rate is above the range" , "Fehler: Ladestrom liegt über dem Bereich"}};

// set the unit to default
const char* UnitofChargeRate[] = {"A"};
static unsigned char defaultUnitIdx = 1;

static bool checkForChargeRateWarningFirst(float parameter);

static bool checkForChargeRateWarningFirst(float parameter)
{
	bool retVal;
	retVal = ((checkForLimit(chargeRateMessage, UnitofChargeRate, parameter, defaultUnitIdx, LOW_WARNING_MESSAGE, LOW_CHARGERATE_WARNING)) ||
				(checkForLimit(chargeRateMessage, UnitofChargeRate, parameter, defaultUnitIdx, NORMAL_MESSSAGE, NORMAL_CHARGERATE)) ||
				(checkForLimit(chargeRateMessage, UnitofChargeRate, parameter, defaultUnitIdx, HIGH_WARNING_MESSAGE, HIGH_CHARGERATE_WARNING)));
	return(retVal);
}

void isChargeRateWithinLimit(BatteryInfo batteryData)
{
	unsigned char errorStatus;
	errorStatus = BatteryErrorStatus;
	errorStatus = checkForChargeRateWarningFirst(batteryData.batteryChargeRate);

	if(!errorStatus)
	{
		errorStatus = ((checkForLimit(chargeRateMessage, UnitofChargeRate, batteryData.batteryChargeRate, defaultUnitIdx, LOW_BREACH_MESSAGE, LOW_CHARGERATE_BREACH)) ||
						(checkForLimit(chargeRateMessage, UnitofChargeRate, batteryData.batteryChargeRate, defaultUnitIdx, HIGH_BREACH_MESSAGE, HIGH_CHARGERATE_BREACH)));
		BatteryErrorStatus = errorStatus;
	}
}
