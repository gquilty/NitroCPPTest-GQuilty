#pragma once

#include "json.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>


// use json namespace to make calling from json lib easier
using json = nlohmann::json;


class NitroCPP {

/** Rectangle structure tos tore our json vlaues **/
	struct rectangle {
		int x;
		//x2 = x + width
		int x2;
		int y;
		//y2 = y + height
		int y2;
		int width;
		int height;
		//vector of all intersecting rectangles array position
		std::vector<int> connections;
	};



public:

	/** Constructor **/
	NitroCPP();

	/** Deconstructor **/
	~NitroCPP();

	/** Vector of all the rectangles created from the Json object **/
	std::vector<rectangle> rectangles;

	/** Function to output error message and rerun the parsing stage **/
	void errorRetry();
	/** Debug function used to verify population of array **/
	void printRectanglesArray();
	/** Detect rectangles which have multiple intersections and output the values **/
	void outputMultipleIntersections();
	/** Detect rectangles which have an intersection and output the intersection values **/
	void detectIntersection();
	/** Create our rectangle structures from our json object and populate array **/
	void createRectangles(json jsonObj);
	/** Verify the json file is formatted correctly otherwise it wont accept values**/
	bool verifyJson(json jsonObj);
	/** Parse the json file and ensure the file exists **/
	void parseJsonFile();
};
