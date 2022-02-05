#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#define	BATTERY_TEMPERATURE_NOT_OK	0x01
#define STATE_OF_CHARGE_NOT_OK		0x02
#define CHARGE_RATE_NOT_OK		    0x04

static unsigned char BatteryErrorStatus;
/* BatteryErrorStatus
   7 6 5 4 3 2 1 0
   x x x x x x x x
   | | | | | | | |
   | | | | | | | \___ Set if battery temperature is out of range
   | | | | | | \_____ Set if State of Charge is out of range
   | | | | | \_______ Set if charge rate is beyond limit
   \_\_\_\_\_________ Reserved for future use
*/

typedef struct
{
	float batteryTemperature;
	float batteryStateOfCharge;
	float batteryChargeRate;
} BatteryInfo;

void printWarningToConsole(BatteryInfo batteryinfo)
{
	if((BatteryErrorStatus & BATTERY_TEMPERATURE_NOT_OK) == BATTERY_TEMPERATURE_NOT_OK){
		printf("Temperature (%.1f celcius) is out of range!\n", batteryinfo.batteryTemperature);
	}
	if((BatteryErrorStatus & STATE_OF_CHARGE_NOT_OK) == STATE_OF_CHARGE_NOT_OK){
		printf("State of Charge (%.1f) is out of range!\n,", batteryinfo.batteryStateOfCharge);
	}
	if((BatteryErrorStatus & CHARGE_RATE_NOT_OK) == CHARGE_RATE_NOT_OK){
		printf("Charge Rate (%.1f) is out of range!\n", batteryinfo.batteryChargeRate);
	}
}

bool isBatteryTemperatureWithinLimit(BatteryInfo batteryData)
{
	if(batteryData.batteryTemperature < 0 || batteryData.batteryTemperature > 45)
	{
		BatteryErrorStatus |= BATTERY_TEMPERATURE_NOT_OK;
		return false;
	}
	else
	{
		return true;
	}
}

bool isStateOfChargeWithinLimit(BatteryInfo batteryData)
{
	if(batteryData.batteryStateOfCharge < 20 || batteryData.batteryStateOfCharge > 80)
	{
		BatteryErrorStatus |= STATE_OF_CHARGE_NOT_OK;
		return false;
	}
	else
	{
		return true;
	}
}

bool isChargeRateWithinLimit(BatteryInfo batteryData )
{
	if(batteryData.batteryChargeRate > 0.8)
	{
		BatteryErrorStatus |= CHARGE_RATE_NOT_OK;
		return false;
	}
	else
	{
		return true;
	}
}

bool batteryIsOk(BatteryInfo BatteryData)
{
	isBatteryTemperatureWithinLimit(BatteryData);
	isStateOfChargeWithinLimit(BatteryData);
	isChargeRateWithinLimit(BatteryData);

	if(BatteryErrorStatus)
	{
		printWarningToConsole(BatteryData);
		return false;
	}
	else
	{
		return true;
	}
}

void testWorkingOfBMS()
{
	BatteryInfo batteryCheckDataSet[5];
	//dataset 1
	batteryCheckDataSet[0].batteryTemperature = 25;
	batteryCheckDataSet[0].batteryStateOfCharge = 70;
	batteryCheckDataSet[0].batteryChargeRate = 0.7;
	assert(batteryIsOk(batteryCheckDataSet[0]));

	//dataset 2
	batteryCheckDataSet[1].batteryTemperature = 50;
	batteryCheckDataSet[1].batteryStateOfCharge = 85;
	batteryCheckDataSet[1].batteryChargeRate = 0;
	assert(batteryIsOk(batteryCheckDataSet[1]));
}

int main()
{
	testWorkingOfBMS();
    return 0;
}
