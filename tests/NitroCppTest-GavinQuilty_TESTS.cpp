#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "NitroCPP.h"
#include "catch.hpp"


TEST_CASE("Test NitroCPP class constructor") {

	NitroCPP *nitro = new NitroCPP();
	REQUIRE(nitro != 0);
	
}

TEST_CASE("Test verify Json correct") {

	std::ifstream i("rect1.json");
	json j;
	i >> j;

	NitroCPP *nitro = new NitroCPP();
	REQUIRE(nitro->verifyJson(j));

}

TEST_CASE("Test verify Json malformed") {

	std::ifstream i("rectError.json");
	json j;
	i >> j;

	NitroCPP *nitro = new NitroCPP();	
	REQUIRE_FALSE(nitro->verifyJson(j));

}

TEST_CASE("Test createRectangles with < 10 vlaues") {

	std::ifstream i("rect1.json");
	json j;
	i >> j;

	NitroCPP *nitro = new NitroCPP();
	nitro->createRectangles(j);
	REQUIRE(nitro->rectangles.size() <= 10);

}

TEST_CASE("Test createRectangles with 10 vlaues") {

	std::ifstream i("rect10.json");
	json j;
	i >> j;

	NitroCPP *nitro = new NitroCPP();
	nitro->createRectangles(j);
	REQUIRE(nitro->rectangles.size() == 10);

}

TEST_CASE("Test createRectangles with 0 vlaues") {

	json j = {
		{ "rects", {} }
	};
	std::cout << "*** TESTCASE : Please type exit *** " << std::endl;
	NitroCPP *nitro = new NitroCPP();
	nitro->createRectangles(j);
	
	REQUIRE(nitro->rectangles.size() == 0);

}