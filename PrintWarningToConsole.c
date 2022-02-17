#include "BMS_module.h"

void printWarningToConsole(const char *warningMessage[5][2],
							const char *unitInfo[],
							float batteryData,
							unsigned char UnitIndex,
							unsigned char MessageIndex,
							unsigned char Language)
{
	printf("%.1f %s --> %s\n", batteryData, unitInfo[UnitIndex - 1], warningMessage[MessageIndex][Language - 1]);
}
