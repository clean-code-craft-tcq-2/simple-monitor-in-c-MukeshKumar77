#include "BMS_module.h"

void testSettingofLanguage()
{
	BatteryInfo batteryCheckDataSet[5];
	setLanguage("German");
	setUnitofData("C");

	batteryCheckDataSet[0].batteryTemperature = 105;
	batteryCheckDataSet[0].batteryStateOfCharge = 70;
	batteryCheckDataSet[0].batteryChargeRate = 0.5;
	assert(batteryIsOk(batteryCheckDataSet[0]) == false);
	assert((LanguageSelection & GERMAN) == GERMAN);


	setLanguage("English");
	assert((LanguageSelection & ENGLISH) == ENGLISH);
}

void testSettingofUnit()
{
	BatteryInfo batteryCheckDataSet[5];
	setUnitofData("F");

	batteryCheckDataSet[0].batteryTemperature = 700;
	batteryCheckDataSet[0].batteryStateOfCharge = 70;
	batteryCheckDataSet[0].batteryChargeRate = 0.7;
	assert(batteryIsOk(batteryCheckDataSet[0]) == false);
	assert((BatteryDataUnitSelection & TEMPERATURE_IN_FAHRENHEIT) == TEMPERATURE_IN_FAHRENHEIT);

	setUnitofData("F");
	batteryCheckDataSet[1].batteryTemperature = 100;
	batteryCheckDataSet[1].batteryStateOfCharge = 70;
	batteryCheckDataSet[1].batteryChargeRate = 0.7;
	assert(batteryIsOk(batteryCheckDataSet[1]) == true);
	assert((BatteryDataUnitSelection & TEMPERATURE_IN_FAHRENHEIT) == TEMPERATURE_IN_FAHRENHEIT);

	setUnitofData("C");
	assert((BatteryDataUnitSelection & TEMPERATURE_IN_CELSIUS) == TEMPERATURE_IN_CELSIUS);
}

void testWorkingOfBMS()
{
	BatteryInfo batteryCheckDataSet[5];

	// EC - all okay
	batteryCheckDataSet[0].batteryTemperature = 25;
	batteryCheckDataSet[0].batteryStateOfCharge = 70;
	batteryCheckDataSet[0].batteryChargeRate = 0.7;
    assert(batteryIsOk(batteryCheckDataSet[0]) == true);

	// EC + BVA - low values
	batteryCheckDataSet[1].batteryTemperature = -1;
	batteryCheckDataSet[1].batteryStateOfCharge = 19;
	batteryCheckDataSet[1].batteryChargeRate = 0;
	assert(batteryIsOk(batteryCheckDataSet[1]) == false);

	// EC + BVA - all okay
	batteryCheckDataSet[2].batteryTemperature = 0;
	batteryCheckDataSet[2].batteryStateOfCharge = 20;
	batteryCheckDataSet[2].batteryChargeRate = 0.1;
	assert(batteryIsOk(batteryCheckDataSet[2]) == true);

	// EC + BVA - all okay
	batteryCheckDataSet[3].batteryTemperature = 45;
	batteryCheckDataSet[3].batteryStateOfCharge = 80;
	batteryCheckDataSet[3].batteryChargeRate = 0.7;
	assert(batteryIsOk(batteryCheckDataSet[3]) == true);

	// EC + BVA - high values
	batteryCheckDataSet[4].batteryTemperature = 46;
	batteryCheckDataSet[4].batteryStateOfCharge = 81;
	batteryCheckDataSet[4].batteryChargeRate = 0.9;
	assert(batteryIsOk(batteryCheckDataSet[4]) == false);
}
