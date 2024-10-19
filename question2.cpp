#include <iostream>

// g++ -std=c++11 -Wall -o question2 question2.cpp
// ./question2

// define struct function to store information about flight
struct FlightInfo {
    const char* destination;  // store and reference airport codes
    int distance;             // miles to destination
};

int main() {
    
    FlightInfo flight1;             // flight of type FlightInfo to store miles to airport code
    flight1.destination = "PHL";  
    flight1.distance = 160;      

    FlightInfo flight2;
    flight2.destination = "ORD"; 
    flight2.distance = 640;       

    FlightInfo flight3;
    flight3.destination = "EWR"; 
    flight3.distance = 220;       

    std::cout << "Flight distances from SCE:" << std::endl;
    std::cout << "To " << flight1.destination << ": " << flight1.distance << " miles" << std::endl;
    std::cout << "To " << flight2.destination << ": " << flight2.distance << " miles" << std::endl;
    std::cout << "To " << flight3.destination << ": " << flight3.distance << " miles" << std::endl;

    return 0;
}

