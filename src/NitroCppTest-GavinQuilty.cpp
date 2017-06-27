#include "../include/stdafx.h"
#include "../include/NitroCPP.h"

// use json namespace to make calling from json lib easier
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
	//Set initial largest values to 0
	int largestXValue = 0;
	int largestYValue = 0;
	//Set initial smalles values to arbitrarily large value
	//may cause errors if Json vlaues are larger then this value
	int smallestXValue = 100000000;
	int smallestYValue = 100000000;

	for (int i = 0; i < rectangles.size(); i++) {
		if (rectangles.at(i).connections.size() > 1) {
			std::cout << "Between rectangle ";
			std::cout << i + 1 << ", ";
			//Format the string depending on how close we are to end of the vector
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

				//Get the largest value of X first checking our current i rectangle
				if (rectangles.at(i).x > largestXValue) {
					largestXValue = rectangles.at(i).x;
				}
				//Continue to check the largest value of X for all other j rectangles
				if (rectangles.at(rectangles.at(i).connections.at(j)).x > largestXValue) {
					largestXValue = rectangles.at(rectangles.at(i).connections.at(j)).x;
				}

				//Get the largest value of Y first checking our current i rectangle
				if (rectangles.at(i).y > largestYValue) {
					largestYValue = rectangles.at(i).y;
				}
				//Continue to check the largest Value of Y for all other j rectangles
				if (rectangles.at(rectangles.at(i).connections.at(j)).y > largestYValue) {
					largestYValue = rectangles.at(rectangles.at(i).connections.at(j)).y;
				}

				//Get the smallest value of X2 first checking our current i rectangle
				if (rectangles.at(i).x2 < smallestXValue) {
					smallestXValue = rectangles.at(i).x2;
				}
				//Continue to check the smalles Value of X2 for all other j rectangles
				if (rectangles.at(rectangles.at(i).connections.at(j)).x2 < smallestXValue) {
					smallestXValue = rectangles.at(rectangles.at(i).connections.at(j)).x2;
				}

				//Get the smallest value of Y2 first checking our current i rectangle
				if (rectangles.at(i).y2 < smallestYValue) {
					smallestYValue = rectangles.at(i).y2;
				}
				//Continue to check the smalles Value of Y2 for all other j rectangles
				if (rectangles.at(rectangles.at(i).connections.at(j)).y2 < smallestYValue) {
					smallestYValue = rectangles.at(rectangles.at(i).connections.at(j)).y2;
				}
			}

			//Output the coordinates of the found rectangle created by the multiple intersections
			std::cout << " at (" << largestXValue << "," << largestYValue << "), ";
			std::cout << " w=" << smallestXValue - largestXValue << ", h=" << smallestYValue - largestYValue << "." << std::endl;

			//Reset values
			largestXValue = 0;
			largestYValue = 0;

			smallestXValue = 10000000;
			smallestYValue = 10000000;

		}

	}


}

void NitroCPP::detectIntersection() {
	//Using a nested loop structure to iterator over the rectangles and detect
	//intersections between rectangle i and j
	for (int i = 0; i < rectangles.size(); i++) {
		for (int j = i + 1; j < rectangles.size(); j++) {
			//Ensure that the rectangle at i does indeed intersect with j
			//Ensure that the values of j all fallwithin the bound of i
			if (rectangles.at(i).x < rectangles.at(j).x2 && rectangles.at(i).x2 > rectangles.at(j).x && rectangles.at(i).y < rectangles.at(j).y2 && rectangles.at(i).y2 > rectangles.at(j).y) {
				//Add rectangle j to the vector of i's connections
				rectangles.at(i).connections.push_back(j);
				//Begin output of intersection information
				std::cout << "Between Rectangle: " << i + 1 << " and " << j + 1;
				//Check largest top left value for x
				if (rectangles.at(i).x > rectangles.at(j).x)
				{
					std::cout << " at (" << rectangles.at(i).x << ",";
				}
				else {
					std::cout << " at (" << rectangles.at(j).x << ",";
				}
				//Check largest top left value for y
				if (rectangles.at(i).y > rectangles.at(j).y)
				{
					std::cout << rectangles.at(i).y << ") ,";
				}
				else {
					std::cout << rectangles.at(j).y << ") ,";
				}

				//Get the height value for the rectangle created by the intersection
				int h2 = 0;
				//Check to see if the i rectangle resides within the bounds of rectangle j
				if (rectangles.at(i).y > rectangles.at(j).y && rectangles.at(j).y2 < rectangles.at(i).y2)
				{
					h2 = rectangles.at(j).y2 - rectangles.at(i).y;
				}
				//check too see if neither corner of the j rectangle is within the i rectangle
				//therefore the intersection as the same height as rectangle i's height
				else if (rectangles.at(i).y > rectangles.at(j).y && rectangles.at(j).y2 > rectangles.at(i).y2) {
					h2 = rectangles.at(i).y2 - rectangles.at(i).y;
				}
				else {
					h2 = rectangles.at(i).y2 - rectangles.at(j).y;
				}

				//Get the width value for the rectangle created by the intersection
				int w2 = 0;
				//Check to see if the i rectangle resides within the bounds of rectangle j
				if (rectangles.at(i).x > rectangles.at(j).x && rectangles.at(j).x2 < rectangles.at(i).x2)
				{
					w2 = rectangles.at(j).x2 - rectangles.at(i).x;
				}
				//Check too see if neither corner of the j rectangle is within the i rectangle
				//therefore the intersection as the same width as rectangle i's width
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
	//Ensure the rectangle only takes in the first 10 eleemtns of the json object
	if (jsonObj.at("rects").size() <= 10 && jsonObj.at("rects").size() > 0) {
		for (int i = 0; i < jsonObj.at("rects").size(); i++) {
			//Populate our rectangle struct and add it to our vector of rectangles
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
	//Ensure that if the json contains more then 10 rectangles we use only firstt 10
	else if (jsonObj.at("rects").size() > 10) {
		for (int i = 0; i < 10; i++) {
			//Populate our rectangle struct and add it to our vector of rectangles
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
	//for every rectangle object in the array valiadate the values
	for (int i = 0; i < jsonObj.at("rects").size(); i++) {
		int x = jsonObj.at("rects").at(i).value("x", -1);
		int y = jsonObj.at("rects").at(i).value("y", -1);
		int w = jsonObj.at("rects").at(i).value("w", -1);
		int h = jsonObj.at("rects").at(i).value("h", -1);

		//If any values of the json are missing the validation will fail
		if (x == -1 || y == -1 || w == -1 || h == -1) {
			return false;
		}

	}
	return true;

}

void NitroCPP::parseJsonFile() {
	std::cout << " Please enter path or name of file you wish to use: " << std::endl;
	std::cout << " Type 'exit' to leave program " << std::endl;
	//Take in the file name if its in the same Dir as the exe
	// else the file path must also be included
	std::string fileName;
	std::getline(std::cin, fileName);
	//exit program
	if (fileName == "exit") {
		return;
	}
	std::ifstream jsonFile(fileName);
	// read the JSON file if it exists
	if (jsonFile) {
		//Create a json object base doff the contents of the filestream
		json j;
		jsonFile >> j;
		//Ensure the Json is properly formatted
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
	//Rerun the parsing step if the json could not populate rectangles
	parseJsonFile();
}
