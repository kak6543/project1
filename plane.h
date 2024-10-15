#ifndef PLANE_H
#define PLANE_H
#include "container.h"

class Plane {
private:
    double pos;         // Position of the plane
    double vel;         // Velocity of the plane
    double distance;    // Distance to destination
    bool at_SCE;        // Status at Scheduled Controlled Event (SCE)
    FlightInfo flight;
public:
    
    Plane(const char* from, const char* to) : origin(from), destination(to), pos(0.0), vel(0.0), distance(0.0), at_SCE(false) {}

    
    ~Plane() {}

    // Operate function (no real functionality as per the instructions)
    void operate(double dt) {
        // Example: Incrementing position by velocity * dt
        pos += vel * dt;
    }
// Getters
    double getPos() const { return pos; }
    const char* getOrigin() const { return origin; }
    const char* getDestination() const { return destination; }
    bool isAtSCE() const { return at_SCE; }

    // Get/Set functions for velocity
    double getVel() const { return vel; }
    void setVel(double v) { vel = v; }
};

#endif