#include <iostream>
#include <string>

// Struct to store flight information
struct FlightInfo {
    const char* destination;  // Store and reference airport codes
    int distance;             // Miles to destination
};

// Class Plane
class Plane {
private:
    double pos;               // Position of the plane
    double vel;               // Velocity of the plane
    double distance;          // Distance to the destination
    bool at_SCE;              // Whether the plane is at SCE (specific control event)
    std::string origin;       // Origin of the flight
    std::string destination;  // Destination of the flight

    // Helper function to find the distance based on the destination
    int findDistance(const std::string& dest, FlightInfo flights[], int flightCount) {
        for (int i = 0; i < flightCount; ++i) {
            if (dest == flights[i].destination) {
                return flights[i].distance;
            }
        }
        return -1; // Return -1 if destination is not found
    }

public:
    // Constructor
    Plane(const std::string& from, const std::string& to, FlightInfo flights[], int flightCount)
        : pos(0.0), vel(0.0), at_SCE(true), origin(from), destination(to) {
        distance = findDistance(to, flights, flightCount);
        if (distance == -1) {
            std::cout << "Destination " << to << " not found." << std::endl;
        } else {
            std::cout << "Plane Created at memory location " << this << ". Distance to " << to << " is " << distance << " miles." << std::endl;
        }
    }

    // Destructor
    ~Plane() {
    }

    // Getter for position
    double getPos() const {
        return pos;
    }

    // Getter for velocity
    double getVel() const {
        return vel;
    }

    // Setter for velocity
    void setVel(double newVel) {
        vel = newVel;
    }

    // Getter for origin
    std::string getOrigin() const {
        return origin;
    }

    // Getter for destination
    std::string getDestination() const {
        return destination;
    }

    // Getter for distance
    double getDistance() const {
        return distance;
    }

    // Setter for distance (if needed)
    void setDistance(double newDistance) {
        distance = newDistance;
    }

    // Getter for at_SCE
    bool isAtSCE() const {
        return at_SCE;
    }

    // Operate function to simulate flight
    void operate(int timestep, int maxIterations) {
        int iteration = 0;
        std::cout << "Flying from " << origin << " to " << destination << std::endl;
        
        while (iteration < maxIterations && pos < distance) {
            pos += vel * (timestep / 3600.0);  // Convert time from seconds to hours and calculate new position
            std::cout << "Iteration " << (iteration + 1) << ": Time = " << (iteration + 1) * timestep << " seconds, Plane position: " << pos << " miles" << std::endl;
            iteration++;
        }

        if (pos >= distance) {
            std::cout << "Plane has reached its destination: " << destination << std::endl;
        } else {
            std::cout << "Plane did not reach the destination after " << maxIterations << " iterations." << std::endl;
        }
    }
};

// Main function for testing
int main() {
    // Define flight information
    FlightInfo flight1 = {"PHL", 160};  // Flight to PHL (Philadelphia)
    FlightInfo flight2 = {"ORD", 640};  // Flight to ORD (Chicago O'Hare)
    FlightInfo flight3 = {"EWR", 220};  // Flight to EWR (Newark)

    // Store all flights in an array
    FlightInfo flights[] = {flight1, flight2, flight3};
    int flightCount = sizeof(flights) / sizeof(flights[0]);  // Number of flights

    // Print out flight distances from SCE
    std::cout << "Flight distances from SCE:" << std::endl;
    for (int i = 0; i < flightCount; ++i) {
        std::cout << "To " << flights[i].destination << ": " << flights[i].distance << " miles" << std::endl;
    }

    // Iterate over each flight and simulate the journey
    for (int i = 0; i < flightCount; ++i) {
        // Instantiate a Plane object for each flight
        Plane plane("SCE", flights[i].destination, flights, flightCount);

        // Set the velocity of the plane (for example, 450 mph)
        plane.setVel(450);

        // Call the operate function with a timestep of 50 seconds and a maximum of 1500 iterations
        std::cout << "Starting simulation for destination: " << flights[i].destination << std::endl;
        plane.operate(10, 1500);  // 50-second timestep, 1500 max iterations
        std::cout << "-----------------------------------" << std::endl;
    }

    return 0;
}
