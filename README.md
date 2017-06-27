## Third Party Libraries

Libraries used in this project are as follows :

Json parser : https://github.com/nlohmann/json

Unit Tests  : https://github.com/philsquared/Catch

Build Tools : https://cmake.org/

## Installation

The code for the project can be found the src and include directories in this project.

To Build this project it is required that Cmake is installed. (Projected tested with V 3.4.3)

Build instructions as follows: (as tested on Visual Studio 14 2015)

Go to ../utils/ folder

Generate a "build" folder (mkdir build)

Go to this "build" fodler (cd build)

Generate project:

       cmake .. -G " {YOUR_PLATFORM_GENERATOR}


Platform Generator Windows:

     For 32 bit Libraries:

     	cmake .. -G "Visual Studio 14 2015 Win"

     For 64 bit libraries:

     	cmake .. -G "Visual Studio 14 2015 Win64"


To then build two .exe for the project and its tests run the following in /build dir :

    cmake --build . --target ALL_BUILD --config Release

You should now find two .exe inside build\bin\Release, if so copy and paste the sample .json files into this directory to ensure the tests can run.

To run the project you can simply run the NitroCPPTest-GavinQuilty.exe and when prompted paste the absolute path of your .json file you wish to calculate the intersections of.


## Tests

Test Library used for this Project is Catch C++

Code can be found here https://github.com/philsquared/Catch .

Decided to use a header only library as it reduces complexity of build instructions for small projects.

The Project contains 6 test scenarios.

As states in the installation section a test.exe is created upon building the project with Cmake.
