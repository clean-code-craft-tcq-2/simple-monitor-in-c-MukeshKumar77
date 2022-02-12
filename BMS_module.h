#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

#ifndef BMS_MODULE_H_
#define BMS_MODULE_H_

#define	ENGLISH						0x01
#define	GERMAN						0x02

#define	TEMPERATURE_IN_CELSIUS		0x01
#define	TEMPERATURE_IN_FAHRENHEIT	0x02
#define STATE_OF_CHARGE_IN_PERCENT	0x03
#define CHARGE_RATE_IN_AMPERE		0x04

#define	HIGH_BATTERY_TEMPERATURE	0x01
#define	LOW_BATTERY_TEMPERATURE		0x02
#define HIGH_STATE_OF_CHARGE		0x04
#define LOW_STATE_OF_CHARGE		    0x08
#define CHARGE_RATE_NOT_OK		    0x10


extern unsigned char LanguageSelection;
/* LanguageSelection
   0x01 --> English is selected language
   0x02 --> German is selected language
   Rest number reserved for future
*/

extern unsigned char BatteryDataUnitSelection;
/* BatteryDataUnitSelection
   0x01 --> Battery temperature is in celcius
   0x02 --> Battery temperature is in fahrenheit
   Rest number reserved for future
*/

extern unsigned char BatteryErrorStatus;
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

extern const char* UnitofBatteryData[2];

bool batteryIsOk(BatteryInfo BatteryData);
void isBatteryTemperatureWithinLimit(BatteryInfo batteryData);
void isStateOfChargeWithinLimit(BatteryInfo batteryData);
void isChargeRateWithinLimit(BatteryInfo batteryData);
void printWarningToConsole(const char *warningMessage[], const char *unitInfo[],
							float batteryData, unsigned char unit, unsigned char language);

void setLanguage(char* language);
void setUnitofData(char* unit);

void testWorkingOfBMS();
void testSettingofLanguage();
void testSettingofUnit();

#endif /* BMS_MODULE_H_ */
