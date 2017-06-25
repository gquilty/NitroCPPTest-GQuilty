// NitroCppTest-GavinQuilty.cpp : Defines the entry point for the console application.
//

#include "../include/stdafx.h"
#include "../include/json.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

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

std::vector<rectangle> rectangles;

//This is a debug function to ensure we have correct data from Json File
void printRectanglesArray(){
	for (int i = 0; i < rectangles.size(); i++) {
		std::cout << rectangles.at(i).x <<  "," << rectangles.at(i).y << "," << rectangles.at(i).height << "," << rectangles.at(i).width << "," << rectangles.at(i).x2 << "," << rectangles.at(i).y2 << std::endl;
		for (int j = 0; j < rectangles.at(i).connections.size(); j++) {
			std::cout << i << " connected to: " << rectangles.at(i).connections.at(j) << std::endl;
		}
	}
}

void outputMultipleIntersections() {
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
				else if(j == rectangles.at(i).connections.size() - 1){
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

void detectIntersection() {
	for (int i = 0; i < rectangles.size(); i++) {
		for (int j = i +1 ; j < rectangles.size(); j++) {
			if (rectangles.at(i).x < rectangles.at(j).x2 && rectangles.at(i).x2 > rectangles.at(j).x && rectangles.at(i).y < rectangles.at(j).y2 && rectangles.at(i).y2 > rectangles.at(j).y) {
				rectangles.at(i).connections.push_back(j);
				std::cout << "Between Rectangle: " << i +1 << " and " << j +1 ;
				if (rectangles.at(i).x > rectangles.at(j).x)
				{
					std::cout << " at (" << rectangles.at(i).x << ",";
				}
				else {
					std::cout << " at (" << rectangles.at(j).x << ",";
				}
				
				if (rectangles.at(i).y > rectangles.at(j).y)
				{
					std::cout << rectangles.at(i).y << ") ," ;
				}
				else {
					std::cout << rectangles.at(j).y << ") ," ;
				}

				int h2 = 0;
				if (rectangles.at(i).y > rectangles.at(j).y && rectangles.at(j).y2 < rectangles.at(i).y2 )
				{
					h2 = rectangles.at(j).y2 - rectangles.at(i).y;
				}
				else if(rectangles.at(i).y > rectangles.at(j).y && rectangles.at(j).y2 > rectangles.at(i).y2) {
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

void createRectangles(json jsonObj) {
	if (jsonObj.at("rects").size() <= 10) {
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
}

void parseJsonFile() {
	std::cout << " Please enter path or name of file you wish to use: " << std::endl;
	std::cout << " Type 'exit' to leave the program " << std::endl;
	std::string fileName;
	std::getline(std::cin, fileName);
	if (fileName == "exit") {
		return;
	}
	else {
		std::ifstream jsonFile(fileName);
		// read a JSON file
		if (jsonFile) {
			json j;
			jsonFile >> j;
			createRectangles(j);
		}
		else {
			std::cout << " Error getting File" << std::endl;
			parseJsonFile();
		}
	}
	
	
	
}

int main()
{	
	parseJsonFile();	
	detectIntersection();
	outputMultipleIntersections();
    return 0;
}

