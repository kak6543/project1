#include <iostream>
#include <string>

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
        return -1; // if destination not found
    }

public:
    // constructor
    Plane(const std::string& from, const std::string& to, FlightInfo flights[], int flightCount)
        : pos(0.0), vel(0.0), at_SCE(true), origin(from), destination(to) {
        distance = findDistance(to, flights, flightCount);
        if (distance == -1) {
            std::cout << "Destination " << to << " not found." << std::endl;
        } else {
            std::cout << "Plane Created at memory location " << this << ". Distance to " << to << " is " << distance << " miles." << std::endl;
        }
    }

    // destructor
    ~Plane() {}

    // getter for position
    double getPos() const { return pos; }

    // getter for velocity
    double getVel() const { return vel; }

    // setter for velocity
    void setVel(double newVel) { vel = newVel; }

    // getter for origin
    std::string getOrigin() const { return origin; }

    // getter for destination
    std::string getDestination() const { return destination; }

    // getter for distance
    double getDistance() const { return distance; }

    // setter for distance
    void setDistance(double newDistance) { distance = newDistance; }

    // getter for at_SCE
    bool isAtSCE() const { return at_SCE; }

    // function to simulate flight
    void operate(int timestep, int maxIterations) {
        int iteration = 0;
        std::cout << "Flying from " << origin << " to " << destination << std::endl;

        while (iteration < maxIterations && pos < distance) {
            pos += vel * (timestep / 3600.0);
            std::cout << "Iteration " << (iteration + 1) << ": Time = " << (iteration + 1) * timestep << " seconds, Plane position: " << pos << " miles" << std::endl;
            iteration++;
        }

        if (pos >= distance) {
            at_SCE = true;
            std::cout << "Plane has landed at SCE." << std::endl;
        } else {
            at_SCE = false;
            std::cout << "Plane did not reach the destination after " << maxIterations << " iterations." << std::endl;
        }
    }
};

class Pilot {
private:
    std::string name;

public:
    Pilot(const std::string& pilotname) : name(pilotname) {
        std::cout << "Pilot Name: " << name << std::endl;
        std::cout << "Memory Address: " << this << std::endl;
        std::cout << name << " is at the gate, ready to board the plane." << std::endl;
    }

    ~Pilot() {
        std::cout << "Pilot Name: " << name << std::endl;
        std::cout << name << " pilot is out of the gate." << std::endl;
    }

    std::string getname() const { return name; }
    Plane* myplane;
};

int main() {
    // define flight information
    FlightInfo flight1 = {"PHL", 160};  // flight to PHL 
    FlightInfo flight2 = {"ORD", 640};  // flight to ORD 
    FlightInfo flight3 = {"EWR", 220};  // flight to EWR 

    // store all flights in array
    FlightInfo flights[] = {flight1, flight2, flight3};
    int flightCount = sizeof(flights) / sizeof(flights[0]);  // number of flights

    // create two pilots
    Pilot pilot1("Pilot-in-Command");
    Pilot pilot2("Co-Pilot");

    // create a plane for the first flight and assign pilot1 control
    Plane plane("SCE", "PHL", flights, flightCount);
    plane.setVel(450);  // set velocity
    pilot1.myplane = &plane;

    // iterate over each flight and swap pilots
    for (int i = 0; i < 5; ++i) {  // simulate 5 flights
        std::cout << pilot1.getname() << " is in control of the plane: " << pilot1.myplane << std::endl;
        
        plane.operate(10, 1500);  // fly the plane

        // swap pilots
        Pilot* currentPilot = (pilot1.myplane == &plane) ? &pilot2 : &pilot1;
        currentPilot->myplane = &plane;

        std::cout << "Control switched to: " << currentPilot->getname() << std::endl;

        // update pilot1 to the new controlling pilot
        pilot1 = *currentPilot;

        std::cout << "-----------------------------------" << std::endl;
    }

    return 0;
}
