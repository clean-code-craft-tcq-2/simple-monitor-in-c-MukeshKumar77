#include "BMS_module.h"

void printWarningToConsole(const char *warningMessage[], const char *unitInfo[],
		                        float batteryData, unsigned char unit, unsigned char language)
{
	printf("%.1f %s --> %s\n", batteryData, unitInfo[unit - 1], warningMessage[language - 1]);
}

