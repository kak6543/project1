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
        return -1; // if desination not found
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
    ~Plane() {
    }

    // getter for position
    double getPos() const {
        return pos;
    }

    // getter for velocity
    double getVel() const {
        return vel;
    }

    // setter for velocity
    void setVel(double newVel) {
        vel = newVel;
    }

    // getter for origin
    std::string getOrigin() const {
        return origin;
    }

    // getter for destination
    std::string getDestination() const {
        return destination;
    }

    // getter for distance
    double getDistance() const {
        return distance;
    }

    // setter for distance
    void setDistance(double newDistance) {
        distance = newDistance;
    }

    // getter for at_SCE
    bool isAtSCE() const {
        return at_SCE;
    }

    // function to simulate flight
    void operate(int timestep, int maxIterations, const std::string& pilotName) {
        int iteration = 0;
        std::cout << "Flying from " << origin << " to " << destination << std::endl;
        
        while (iteration < maxIterations && pos < distance) {
            std::cout << "Pilot Name: " << pilotName << std::endl;
            std::cout << "Pilot Memory Address: " << &pilotName << std::endl;
            std::cout << "Plane Memory Address: " << this << std::endl;
            pos += vel * (timestep / 3600.0); 
            std::cout << "Iteration " << (iteration + 1) << ": Time = " << (iteration + 1) * timestep << " seconds, Plane position: " << pos << " miles" << std::endl;
            iteration++;
        }

        if (pos >= distance) {
            std::cout << "Plane has reached its destination: " << destination << std::endl;
            std::cout << "Plane Memory Address: " << this << " - Plane is now at SCE." << std::endl;
        } else {
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
        std::cout << "Pilot Memory Address: " << this << std::endl;
        
        std::cout << name << " is at the gate, ready to board the plane." << std::endl;
    }
    ~Pilot() {
        std::cout << "Pilot Name: " << name << std::endl;
        std::cout << name << " pilot is out of the gate." << std::endl;
    }

    std::string getname() const {
        return name; 
    }
    void switchControl(Plane* newPlane){
        std::cout << name << " is now in control of the plane." << std::endl;
        std::cout << "Pilot Memory Address: " << this << std::endl;
        std::cout << "Controlling Plane Memory Address: " << newPlane << std::endl;
    }
};

int main() {
    // Define flight information
    FlightInfo flight1 = {"PHL", 160};  // flight to PHL 
    FlightInfo flight2 = {"ORD", 640};  // flight to ORD 
    FlightInfo flight3 = {"EWR", 220};  // flight to EWR 

    // store all flights in array
    FlightInfo flights[] = {flight1, flight2, flight3};
    int flightCount = sizeof(flights) / sizeof(flights[0]);  // Number of flights

    // flight distances from SCE
    std::cout << "Flight distances from SCE:" << std::endl;
    for (int i = 0; i < flightCount; ++i) {
        std::cout << "To " << flights[i].destination << ": " << flights[i].distance << " miles" << std::endl;
    }

    // iterate over each flight
    for (int i = 0; i < flightCount; ++i) {
        // Instantiate a Plane object for each flight
        Plane plane("SCE", flights[i].destination, flights, flightCount);
        Pilot pilot("Pilot " + std::to_string(i + 1));
        // set the velocity of the plane
        plane.setVel(450);
        
        std::cout << "Starting simulation for destination: " << flights[i].destination << std::endl;
        plane.operate(50, 1500, pilot.getname());  // 50 s timestep, 1500 max iterations

        Pilot newPilot("Pilot " + std::to_string(i + 2));  // Create a new pilot
        newPilot.switchControl(&plane);
        std::cout << "-----------------------------------" << std::endl;
    }

    return 0;
}
