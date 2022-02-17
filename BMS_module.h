#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

#ifndef BMS_MODULE_H_
#define BMS_MODULE_H_

#define	ENGLISH				0x01
#define	GERMAN				0x02

#define	TEMPERATURE_IN_CELSIUS		0x01
#define	TEMPERATURE_IN_FAHRENHEIT	0x02
#define STATE_OF_CHARGE_IN_PERCENT	0x03
#define CHARGE_RATE_IN_AMPERE		0x04

#define LOW_BREACH_MESSAGE		0x00
#define LOW_WARNING_MESSAGE		0x01
#define NORMAL_MESSSAGE			0x02
#define HIGH_WARNING_MESSAGE		0x03
#define HIGH_BREACH_MESSAGE		0x04

#define LOW_SOC_BREACH 			0, 19
#define LOW_SOC_WARNING			20, 24
#define NORMAL_SOC			25, 75
#define HIGH_SOC_WARNING		76, 80
#define HIGH_SOC_BREACH			81, 100

#define LOW_TEMPERATURE_BREACH 		-10, -0
#define LOW_TEMPERATURE_WARNING		0, 2.25
#define NORMAL_TEMPERATURE		2.26, 42.74
#define HIGH_TEMPERATURE_WARNING	42.75, 45
#define HIGH_TEMPERATURE_BREACH		46, 100

#define LOW_CHARGERATE_BREACH 		-0.5, -0.1
#define LOW_CHARGERATE_WARNING		0, 0.04
#define NORMAL_CHARGERATE		0.05, 0.75
#define HIGH_CHARGERATE_WARNING		0.76, 0.8
#define HIGH_CHARGERATE_BREACH		0.9, 1


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
extern float fahrenheitTemp;

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
void printWarningToConsole(const char *warningMessage[5][2],
							const char *unitInfo[],
							float batteryData,
							unsigned char UnitIndex,
							unsigned char MessageIndex,
							unsigned char Language);

bool checkForLimit(const char *messageToConsole[5][2],
					const char *unit[],
					float batteryInfo,
					unsigned char unitIdx,
					unsigned char messageIdx,
					float lowerLimit,
					float upperLimit);

void setLanguage(unsigned char language);
void setUnitofData(unsigned char unit);

void testWorkingOfBMS();
void testSettingofLanguage();
void testSettingofUnit();

#endif /* BMS_MODULE_H_ */
