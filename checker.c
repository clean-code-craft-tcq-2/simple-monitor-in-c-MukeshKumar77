#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#define	HIGH_BATTERY_TEMPERATURE	0x01
#define	LOW_BATTERY_TEMPERATURE		0x02
#define HIGH_STATE_OF_CHARGE		0x04
#define LOW_STATE_OF_CHARGE		0x08
#define CHARGE_RATE_NOT_OK		0x10

unsigned char BatteryErrorStatus = 0;
/* BatteryErrorStatus
   7 6 5 4 3 2 1 0
   x x x x x x x x
   | | | | | | | |
   | | | | | | | \___ Set if battery temperature is above 45
   | | | | | | \_____ Set if battery temperature is below 0
   | | | | | \_______ Set if State of Charge is above 80
   | | | | \_________ Set if State of Charge is below 20
   | | | \___________ Set if charge rate is beyond limit of 0.8
   \_\_\_____________ Reserved for future use
*/

typedef struct
{
	float batteryTemperature;
	float batteryStateOfCharge;
	float batteryChargeRate;
} BatteryInfo;

void printTemperatureWarningToConsole(BatteryInfo batteryinfo, unsigned char errorStatus)
{
	if((errorStatus & HIGH_BATTERY_TEMPERATURE) == HIGH_BATTERY_TEMPERATURE){
		printf("Temperature = %.1f celcius, is above 45 celcius!\n", batteryinfo.batteryTemperature);
	}
	else if((errorStatus & LOW_BATTERY_TEMPERATURE) == LOW_BATTERY_TEMPERATURE){
		printf("Temperature = %.1f celcius, is below 0 celcius!\n", batteryinfo.batteryTemperature);
	}
}

void printSOCWarningToConsole(BatteryInfo batteryinfo, unsigned char errorStatus)
{
	if((errorStatus & HIGH_STATE_OF_CHARGE) == HIGH_STATE_OF_CHARGE){
		printf("State of Charge = %.1f, is above 80 percent!\n", batteryinfo.batteryStateOfCharge);
	}
	else if((errorStatus & LOW_STATE_OF_CHARGE) == LOW_STATE_OF_CHARGE){
		printf("State of Charge = %.1f, is below 20 percent!\n", batteryinfo.batteryStateOfCharge);
	}
}

void printChargeRateWarningToConsole(BatteryInfo batteryinfo, unsigned char errorStatus)
{
	if((errorStatus & CHARGE_RATE_NOT_OK) == CHARGE_RATE_NOT_OK){
	printf("Charge Rate = %.1f, is above 0.8\n", batteryinfo.batteryChargeRate);
	}
}

void isBatteryTemperatureWithinLimit(BatteryInfo batteryData)
{
	if(batteryData.batteryTemperature < 0)
	{
		BatteryErrorStatus |= LOW_BATTERY_TEMPERATURE;
	}
	else if(batteryData.batteryTemperature > 45)
	{
		BatteryErrorStatus |= HIGH_BATTERY_TEMPERATURE;
	}
	printTemperatureWarningToConsole(batteryData, BatteryErrorStatus);
}

void isStateOfChargeWithinLimit(BatteryInfo batteryData)
{
	if(batteryData.batteryStateOfCharge < 20)
	{
		BatteryErrorStatus |= LOW_STATE_OF_CHARGE;
	}
	else if(batteryData.batteryStateOfCharge > 80)
	{
		BatteryErrorStatus |= HIGH_STATE_OF_CHARGE;
	}
	printSOCWarningToConsole(batteryData, BatteryErrorStatus);
}

void isChargeRateWithinLimit(BatteryInfo batteryData)
{
	if(batteryData.batteryChargeRate > 0.8)
	{
		BatteryErrorStatus |= CHARGE_RATE_NOT_OK;
	}
	printChargeRateWarningToConsole(batteryData, BatteryErrorStatus);
}

bool batteryIsOk(BatteryInfo BatteryData)
{
	isBatteryTemperatureWithinLimit(BatteryData);
	isStateOfChargeWithinLimit(BatteryData);
	isChargeRateWithinLimit(BatteryData);

	if(BatteryErrorStatus)
	{
		// clear error status for next call of this API
		BatteryErrorStatus = 0;
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

int main()
{
    testWorkingOfBMS();
    return 0;
}
