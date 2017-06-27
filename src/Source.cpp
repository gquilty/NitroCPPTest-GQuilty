#include "../include/stdafx.h"
#include "../include/NitroCPP.h"

int main()
{
	NitroCPP *nitro = new NitroCPP();
	nitro->parseJsonFile();
	nitro->detectIntersection();
	nitro->outputMultipleIntersections();
}