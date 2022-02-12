#include "BMS_module.h"

const char* Language[2] = {"English", "German"};
const char* UnitofBatteryData[2] = {"C", "F"};
unsigned char BatteryErrorStatus;
unsigned char LanguageSelection;
unsigned char BatteryDataUnitSelection;

void setLanguage(char* language)
{
	//reset for every call of new setting
	LanguageSelection = 0;
	if(!strcmp(language, Language[0]))
	{
		LanguageSelection |= ENGLISH;
	}
	else if (!strcmp(language, Language[1]))
	{
		LanguageSelection |= GERMAN;
	}
}

void setUnitofData(char* unit)
{
	//reset for every call of new setting
	BatteryDataUnitSelection = 0;
	if(!strcmp(unit, UnitofBatteryData[0]))
	{
		BatteryDataUnitSelection |= TEMPERATURE_IN_CELSIUS;
	}
	else if (!strcmp(unit, UnitofBatteryData[1]))
	{
		BatteryDataUnitSelection |= TEMPERATURE_IN_FAHRENHEIT;
	}
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
