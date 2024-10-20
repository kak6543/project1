#include <iostream>
#include <string>

struct FlightInfo {
    const char* destination;  // Airport codes
    int distance;             // Miles to destination
};

// plane class
class Plane {
private:
    double pos, vel, distance;
    bool at_SCE;
    std::string origin, destination;

    // find the distance to a destination
    int findDistance(const std::string& dest, FlightInfo flights[], int flightCount) {
        for (int i = 0; i < flightCount; ++i) {
            if (dest == flights[i].destination) {
                return flights[i].distance;
            }
        }
        return -1;
    }

public:
    Plane(const std::string& from, const std::string& to, FlightInfo flights[], int flightCount)
        : pos(0.0), vel(0.0), at_SCE(true), origin(from), destination(to) {
        distance = findDistance(to, flights, flightCount);
        std::cout << "Plane created at memory location: " << this 
                  << ". Distance to " << to << " is " << distance << " miles.\n";
    }

    void setVel(double newVel) { vel = newVel; }
    bool isAtSCE() const { return at_SCE; }

    void operate(int timestep, int maxIterations) {
        int iteration = 0;
        while (iteration < maxIterations && pos < distance) {
            pos += vel * (timestep / 3600.0);
            ++iteration;
        }
        at_SCE = (pos >= distance);
        if (at_SCE) {
            std::cout << "Plane has landed at SCE.\n";
        }
    }
};

// pilot class
class Pilot {
public:
    std::string name;
    Plane* myplane;

    Pilot(const std::string& pilotname) : name(pilotname), myplane(nullptr) {
        std::cout << "Pilot Name: " << name << " at memory: " << this << "\n";
    }
};

// Main function
int main() {
    // Define flight information
    FlightInfo flights[] = {{"PHL", 160}, {"ORD", 640}, {"EWR", 220}};
    int flightCount = sizeof(flights) / sizeof(flights[0]);

    // Create a plane for the first flight
    Plane plane("SCE", "PHL", flights, flightCount);
    plane.setVel(450);  // Set velocity to 450 mph

    // Create two pilots
    Pilot pilot1("Pilot-in-Command");
    Pilot pilot2("Co-Pilot");

    // Assign the first pilot to control the plane
    pilot1.myplane = &plane;

    // Simulate flights and pilot swaps
    for (int i = 0; i < 5; ++i) {  // Simulate 5 flight legs
        std::cout << pilot1.name << " is in control of plane: " << pilot1.myplane << "\n";
        plane.operate(10, 1500);  // Fly the plane

        // Swap pilots after each flight
        Pilot* currentPilot = (pilot1.myplane == &plane) ? &pilot2 : &pilot1;
        currentPilot->myplane = &plane;

        std::cout << "Control switched to: " << currentPilot->name << "\n";
        pilot1 = *currentPilot;  // Update the controlling pilot

        std::cout << "-----------------------------------\n";
    }

    return 0;
}
