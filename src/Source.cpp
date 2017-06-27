#include "../include/stdafx.h"
#include "../include/NitroCPP.h"

int main()
{
	NitroCPP *nitro = new NitroCPP();
	nitro->parseJsonFile();
	nitro->detectIntersection();
	nitro->outputMultipleIntersections();
	std::cout << "Press any key to leave program " << std::endl;
	std::string exit;
	std::getline(std::cin, exit);

}