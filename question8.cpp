#include <iostream>
#include <string>
#include <memory>  // For std::shared_ptr and std::make_shared

// flight info
struct FlightInfo {
    const char* destination;  // store and reference airport codes
    int distance;             // miles to destination
};

// class Plane
class Plane {
private:
    double pos;               // position
    double vel;               // velocity
    double distance;          // distance to destination
    bool at_SCE;              // whether the plane is at SCE
    std::string origin;       // origin of the flight
    std::string destination;  // destination of the flight

    // function to find the distance based on the destination
    int findDistance(const std::string& dest, FlightInfo flights[], int flightCount) {
        for (int i = 0; i < flightCount; ++i) {
            if (dest == flights[i].destination) {
                return flights[i].distance;
            }
        }
        return -1;  // if destination not found
    }

public:
    // constructor
    Plane(const std::string& from, const std::string& to, FlightInfo flights[], int flightCount)
        : pos(0.0), vel(0.0), at_SCE(true), origin(from), destination(to) {
        distance = findDistance(to, flights, flightCount);
        std::cout << "Plane created at memory location: " << this << "\n";
    }

    // setter for velocity
    void setVel(double newVel) {
        vel = newVel;
    }

    // function to simulate landing at SCE
    void landAtSCE() {
        at_SCE = true;
        std::cout << "The plane " << this << " is at SCE.\n";
    }
};

// class Pilot
class Pilot {
private:
    std::string name;

public:
    std::shared_ptr<Plane> myplane;  // pointer to a plane (shared ownership)

    // constructor
    Pilot(const std::string& pilotname) : name(pilotname) {
        std::cout << "Pilot " << name << " at memory: " << this << " is at the gate, ready to board the plane.\n";
    }

    // function to switch control of the plane
    void switchControl(std::shared_ptr<Plane> newPlane) {
        myplane = newPlane;
        std::cout << name << " is now in control of the plane.\n";
        std::cout << "Pilot Memory Address: " << this << "\n";
        std::cout << "Controlling Plane Memory Address: " << myplane.get() << "\n";
    }
};

// main function
int main() {
    // Define flight information
    FlightInfo flight1 = {"PHL", 160};  // flight to PHL
    FlightInfo flight2 = {"ORD", 640};  // flight to ORD
    FlightInfo flight3 = {"EWR", 220};  // flight to EWR

    // store all flights in array
    FlightInfo flights[] = {flight1, flight2, flight3};
    int flightCount = sizeof(flights) / sizeof(flights[0]);  // Number of flights

    // flight distances from SCE
    std::cout << "Flight distances from SCE:\n";
    for (int i = 0; i < flightCount; ++i) {
        std::cout << "To " << flights[i].destination << ": " << flights[i].distance << " miles\n";
    }

    // create two pilots using shared_ptr
    auto pilot1 = std::make_shared<Pilot>("Alpha");
    auto pilot2 = std::make_shared<Pilot>("Bravo");

    // iterate over each flight 
    for (int i = 0; i < flightCount; ++i) {
        // plane object for each flight (using shared_ptr)
        auto plane = std::make_shared<Plane>("SCE", flights[i].destination, flights, flightCount);
        plane->setVel(450);  // Set velocity of the plane

        // initial control of the plane to pilot1
        pilot1->switchControl(plane);

        // land the plane at SCE
        plane->landAtSCE();

        std::cout << "Navigation from SCE to " << flights[i].destination << " has been completed.\n";
        std::cout << "Navigation from " << flights[i].destination << " to SCE has been completed.\n";

        // switch control 
        if (pilot1->myplane) {
            pilot2->switchControl(plane);
        } else {
            pilot1->switchControl(plane);
        }

        std::cout << "-----------------------------------\n";
    }

    return 0;
}
