#include "BMS_module.h"

const char* Language[2] = {"English", "German"};
const char* UnitofBatteryData[2] = {"C", "F"};
unsigned char BatteryErrorStatus;
unsigned char LanguageSelection;
unsigned char BatteryDataUnitSelection;

void setLanguage(unsigned char language)
{
	//reset for every call of new setting
	LanguageSelection = 0;
	//set new language
	LanguageSelection = language;
}

void setUnitofData(unsigned char unit)
{
	//reset for every call of new setting
	BatteryDataUnitSelection = 0;
	//set new unit
	BatteryDataUnitSelection = unit;
}

bool checkForLimit(const char *messageToConsole[5][2],
					const char *unit[],
					float batteryInfo,
					unsigned char unitIdx,
					unsigned char messageIdx,
					float lowerLimit,
					float upperLimit)
{
	if ((batteryInfo >= lowerLimit) && (batteryInfo <= upperLimit))
	{
		printWarningToConsole(messageToConsole, unit, batteryInfo, unitIdx, messageIdx, LanguageSelection);
		return true;
	}
	return false;
}

bool batteryIsOk(BatteryInfo BatteryData)
{
	bool retVal = true;

	// clear error status for each call of this API
	BatteryErrorStatus = 0;

	isBatteryTemperatureWithinLimit(BatteryData);
	isStateOfChargeWithinLimit(BatteryData);
	isChargeRateWithinLimit(BatteryData);

	if(BatteryErrorStatus)
	{
		retVal =  false;
	}
	return retVal;
}

int main()
{
	testSettingofLanguage();
	testSettingofUnit();
	testWorkingOfBMS();

    return 0;
}
