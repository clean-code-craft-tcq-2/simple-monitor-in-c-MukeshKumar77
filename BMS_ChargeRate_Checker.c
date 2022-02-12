#include "BMS_module.h"

const char* chargeRateMessage[5][2] = {
		{"Error: Charge Rate is below the range" , "Fehler: Ladestrom liegt unterhalb des Bereichs"},
		{"Warning: Charge Rate is too low " , "Warnung: Die Ladestrom ist zu niedrig"},
		{"Charge Rate is normal" , "Ladestrom ist normal"},
		{"Warning: Charge Rate is too high" , "Warnung: Die Ladestrom ist zu hoch"},
		{"Error: Charge Rate is above the range" , "Fehler: Ladestrom liegt über dem Bereich"}};

void isChargeRateWithinLimit(BatteryInfo batteryData)
{
	// set the unit to default
	const char* UnitofChargeRate[] = {"A"};
	unsigned char defaultUnitIdx = 1;

	unsigned char errorStatus;
	errorStatus = BatteryErrorStatus;
	errorStatus = ((checkForLimit(chargeRateMessage, UnitofChargeRate, batteryData.batteryChargeRate, defaultUnitIdx, LOW_WARNING_MESSAGE, LOW_CHARGERATE_WARNING)) ||
					(checkForLimit(chargeRateMessage, UnitofChargeRate, batteryData.batteryChargeRate, defaultUnitIdx, NORMAL_MESSSAGE, NORMAL_CHARGERATE)) ||
					(checkForLimit(chargeRateMessage, UnitofChargeRate, batteryData.batteryChargeRate, defaultUnitIdx, HIGH_WARNING_MESSAGE, HIGH_CHARGERATE_WARNING)));
	if(!errorStatus)
	{
		errorStatus = ((checkForLimit(chargeRateMessage, UnitofChargeRate, batteryData.batteryChargeRate, defaultUnitIdx, LOW_BREACH_MESSAGE, LOW_CHARGERATE_BREACH)) ||
						(checkForLimit(chargeRateMessage, UnitofChargeRate, batteryData.batteryChargeRate, defaultUnitIdx, HIGH_BREACH_MESSAGE, HIGH_CHARGERATE_BREACH)));
		BatteryErrorStatus = errorStatus;
	}
}
