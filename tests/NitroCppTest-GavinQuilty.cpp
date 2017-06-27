// NitroCppTest-GavinQuilty.cpp : Defines the entry point for the console application.
//

#include "NitroCPP.h"

// for convenience
using json = nlohmann::json;


struct rectangle {
	int x;
	int x2;
	int y;
	int y2;
	int width;
	int height;
	std::vector<int> connections;
};



NitroCPP::NitroCPP() {
}

NitroCPP::~NitroCPP() {
}

//This is a debug function to ensure we have correct data from Json File
void NitroCPP::printRectanglesArray() {
	for (int i = 0; i < rectangles.size(); i++) {
		std::cout << rectangles.at(i).x << "," << rectangles.at(i).y << "," << rectangles.at(i).height << "," << rectangles.at(i).width << "," << rectangles.at(i).x2 << "," << rectangles.at(i).y2 << std::endl;
		for (int j = 0; j < rectangles.at(i).connections.size(); j++) {
			std::cout << i << " connected to: " << rectangles.at(i).connections.at(j) << std::endl;
		}
	}
}

void NitroCPP::outputMultipleIntersections() {
	int largestXValue = 0;
	int largestYValue = 0;

	int smallestXValue = 100000000;
	int smallestYValue = 100000000;

	for (int i = 0; i < rectangles.size(); i++) {
		if (rectangles.at(i).connections.size() > 1) {
			std::cout << "Between rectangle ";
			std::cout << i + 1 << ", ";
			for (int j = 0; j < rectangles.at(i).connections.size(); j++) {
				if (j == rectangles.at(i).connections.size() - 2) {
					std::cout << rectangles.at(i).connections.at(j) + 1 << " and ";
				}
				else if (j == rectangles.at(i).connections.size() - 1) {
					std::cout << rectangles.at(i).connections.at(j) + 1;
				}
				else {
					std::cout << rectangles.at(i).connections.at(j) + 1 << ", ";
				}

				//get largest X value
				if (rectangles.at(i).x > largestXValue) {
					largestXValue = rectangles.at(i).x;
				}

				if (rectangles.at(rectangles.at(i).connections.at(j)).x > largestXValue) {
					largestXValue = rectangles.at(rectangles.at(i).connections.at(j)).x;
				}

				//get largest Y value
				if (rectangles.at(i).y > largestYValue) {
					largestYValue = rectangles.at(i).y;
				}

				if (rectangles.at(rectangles.at(i).connections.at(j)).y > largestYValue) {
					largestYValue = rectangles.at(rectangles.at(i).connections.at(j)).y;
				}

				//get smalles X2 value
				if (rectangles.at(i).x2 < smallestXValue) {
					smallestXValue = rectangles.at(i).x2;
				}

				if (rectangles.at(rectangles.at(i).connections.at(j)).x2 < smallestXValue) {
					smallestXValue = rectangles.at(rectangles.at(i).connections.at(j)).x2;
				}

				//get smallest Y value
				if (rectangles.at(i).y2 < smallestYValue) {
					smallestYValue = rectangles.at(i).y2;
				}

				if (rectangles.at(rectangles.at(i).connections.at(j)).y2 < smallestYValue) {
					smallestYValue = rectangles.at(rectangles.at(i).connections.at(j)).y2;
				}
			}

			std::cout << " at (" << largestXValue << "," << largestYValue << "), ";
			std::cout << " w=" << smallestXValue - largestXValue << ", h=" << smallestYValue - largestYValue << "." << std::endl;

			largestXValue = 0;
			largestYValue = 0;

			smallestXValue = 10000000;
			smallestYValue = 10000000;

		}

	}


}

void NitroCPP::detectIntersection() {
	for (int i = 0; i < rectangles.size(); i++) {
		for (int j = i + 1; j < rectangles.size(); j++) {
			if (rectangles.at(i).x < rectangles.at(j).x2 && rectangles.at(i).x2 > rectangles.at(j).x && rectangles.at(i).y < rectangles.at(j).y2 && rectangles.at(i).y2 > rectangles.at(j).y) {
				rectangles.at(i).connections.push_back(j);
				std::cout << "Between Rectangle: " << i + 1 << " and " << j + 1;
				if (rectangles.at(i).x > rectangles.at(j).x)
				{
					std::cout << " at (" << rectangles.at(i).x << ",";
				}
				else {
					std::cout << " at (" << rectangles.at(j).x << ",";
				}

				if (rectangles.at(i).y > rectangles.at(j).y)
				{
					std::cout << rectangles.at(i).y << ") ,";
				}
				else {
					std::cout << rectangles.at(j).y << ") ,";
				}

				int h2 = 0;
				if (rectangles.at(i).y > rectangles.at(j).y && rectangles.at(j).y2 < rectangles.at(i).y2)
				{
					h2 = rectangles.at(j).y2 - rectangles.at(i).y;
				}
				else if (rectangles.at(i).y > rectangles.at(j).y && rectangles.at(j).y2 > rectangles.at(i).y2) {
					h2 = rectangles.at(i).y2 - rectangles.at(i).y;
				}
				else {
					h2 = rectangles.at(i).y2 - rectangles.at(j).y;
				}

				int w2 = 0;
				if (rectangles.at(i).x > rectangles.at(j).x && rectangles.at(j).x2 < rectangles.at(i).x2)
				{
					w2 = rectangles.at(j).x2 - rectangles.at(i).x;
				}
				else if (rectangles.at(i).x > rectangles.at(j).x && rectangles.at(j).x2 > rectangles.at(i).x2) {
					w2 = rectangles.at(i).x2 - rectangles.at(i).x;
				}
				else {
					w2 = rectangles.at(i).x2 - rectangles.at(j).x;
				}

				std::cout << " w=" << w2 << ", h=" << h2 << "." << std::endl;

			}
		}
	}
}



void NitroCPP::createRectangles(json jsonObj) {
	if (jsonObj.at("rects").size() <= 10 && jsonObj.at("rects").size() > 0) {
		for (int i = 0; i < jsonObj.at("rects").size(); i++) {
			rectangle newRectangle;
			newRectangle.x = jsonObj.at("rects").at(i).at("x");
			newRectangle.y = jsonObj.at("rects").at(i).at("y");
			newRectangle.width = jsonObj.at("rects").at(i).at("w");
			newRectangle.height = jsonObj.at("rects").at(i).at("h");
			newRectangle.x2 = newRectangle.x + newRectangle.width;
			newRectangle.y2 = newRectangle.y + newRectangle.height;
			rectangles.push_back(newRectangle);
		}
	}
	else if (jsonObj.at("rects").size() > 10) {
		for (int i = 0; i < 10; i++) {
			rectangle newRectangle;
			newRectangle.x = jsonObj.at("rects").at(i).at("x");
			newRectangle.y = jsonObj.at("rects").at(i).at("y");
			newRectangle.width = jsonObj.at("rects").at(i).at("w");
			newRectangle.height = jsonObj.at("rects").at(i).at("h");
			newRectangle.x2 = newRectangle.x + newRectangle.width;
			newRectangle.y2 = newRectangle.y + newRectangle.height;
			rectangles.push_back(newRectangle);
		}
	}
	else {
		std::cout << " Error reading JSON Object please retry " << std::endl;
		errorRetry();
	}
}

bool NitroCPP::verifyJson(json jsonObj) {
	for (int i = 0; i < jsonObj.at("rects").size(); i++) {
		int x = jsonObj.at("rects").at(i).value("x", -1);
		int y = jsonObj.at("rects").at(i).value("y", -1);
		int w = jsonObj.at("rects").at(i).value("w", -1);
		int h = jsonObj.at("rects").at(i).value("h", -1);

		if (x == -1 || y == -1 || w == -1 || h == -1) {
			return false;
		}
	}

	return true;

}

void NitroCPP::parseJsonFile() {
	std::cout << " Please enter path or name of file you wish to use: " << std::endl;
	std::cout << " Type 'exit' to leave program " << std::endl;
	std::string fileName;
	std::getline(std::cin, fileName);
	if (fileName == "exit") {
		return;
	}
	std::ifstream jsonFile(fileName);
	// read a JSON file
	if (jsonFile) {
		json j;
		jsonFile >> j;
		if (verifyJson(j)) {
			createRectangles(j);
		}
		else {
			std::cout << " Error reading JSON Object values please retry " << std::endl;
			errorRetry();
		}

	}
	else {
		errorRetry();
	}

}

void NitroCPP::errorRetry() {
	std::cout << " Error getting File - please retry" << std::endl;
	parseJsonFile();
}

