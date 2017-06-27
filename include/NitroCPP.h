#pragma once

#include "json.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>


// for convenience
using json = nlohmann::json;

class NitroCPP {

	struct rectangle {
		int x;
		int x2;
		int y;
		int y2;
		int width;
		int height;
		std::vector<int> connections;
	};



public:

	NitroCPP();

	~NitroCPP();
	std::vector<rectangle> rectangles;


	void errorRetry();
	void printRectanglesArray();
	void outputMultipleIntersections();
	void detectIntersection();
	void createRectangles(json jsonObj);
	bool verifyJson(json jsonObj);
	void parseJsonFile();
};