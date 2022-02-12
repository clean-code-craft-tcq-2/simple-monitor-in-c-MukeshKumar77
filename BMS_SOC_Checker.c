#include "BMS_module.h"

const char* SoCMessage[5][2] = {
		{"Error: SOC is below the range" , "Fehler: SOC liegt unterhalb des Bereichs"},
		{"Warning: SOC approaching discharge " , "Warnung: SOC nähert sich der Entladung"},
		{"SOC is normal" , "SOC ist normal"},
		{"Warning: SOC is approaching peak charge" , "Warnung: SOC nähert sich der Spitzenladung"},
		{"Error: SOC is above the range" , "Fehler: SOC liegt über dem Bereich"}};

void isStateOfChargeWithinLimit(BatteryInfo batteryData)
{
	// set the unit to default
	const char* UnitofSOC[] = {"%"};
	unsigned char defaultUnitIdx = 1;

	unsigned char errorStatus;
	errorStatus = BatteryErrorStatus;
	errorStatus = ((checkForLimit(SoCMessage, UnitofSOC, batteryData.batteryStateOfCharge, defaultUnitIdx, LOW_WARNING_MESSAGE, LOW_SOC_WARNING)) ||
					(checkForLimit(SoCMessage, UnitofSOC, batteryData.batteryStateOfCharge, defaultUnitIdx, NORMAL_MESSSAGE, NORMAL_SOC)) ||
					(checkForLimit(SoCMessage, UnitofSOC, batteryData.batteryStateOfCharge, defaultUnitIdx, HIGH_WARNING_MESSAGE, HIGH_SOC_WARNING)));
	if(!errorStatus)
	{
		errorStatus = ((checkForLimit(SoCMessage, UnitofSOC, batteryData.batteryStateOfCharge, defaultUnitIdx, LOW_BREACH_MESSAGE, LOW_SOC_BREACH)) ||
						(checkForLimit(SoCMessage, UnitofSOC, batteryData.batteryStateOfCharge, defaultUnitIdx, HIGH_BREACH_MESSAGE, HIGH_SOC_BREACH)));
		BatteryErrorStatus = errorStatus;
	}
}
