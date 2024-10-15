#include <iostream>
#include <vector>

// g++ -std=c++11 -Wall -o question1 question1.cpp
// ./question1

#define ENABLE_USER_INPUT 0                 // if 0 -> 1, user input enabled

int main() {
    double empty_weight;                    // lbs
    double empty_moment;                    // lbs-in
    int num_front_seats; 
    std::vector<double> front_seat_weights; // lbs
    double front_seat_arm;                  // moment arm (in.)
    int num_rear_seats; 
    std::vector<double> rear_seat_weights;  // lbs
    double rear_seat_arm; 
    double fuel_gal;                        // gallons
    double fuel_weight_per_gal;
    double fuel_tank_arm;                   // moment arm (in.)
    double baggage_weight;
    double baggage_arm;                     // moment arm (in.)

#if ENABLE_USER_INPUT

    std::cout << "Enter the aircraft empty weight (lbs): ";
    std::cin >> empty_weight;
    std::cout << "Enter the aircraft empty-weight moment (pounds-inches): ";
    std::cin >> empty_moment;

    std::cout << "Enter the number of front seat occupants: ";
    std::cin >> num_front_seats;
    front_seat_weights.resize(num_front_seats); // front seat weight vector resized to match # of front seats
    for (int i = 0; i < num_front_seats; ++i) {
        std::cout << "Enter the weight of front seat occupant " << i+1 << " (lbs): ";
        std::cin >> front_seat_weights[i];
    }
    std::cout << "Enter the front seat moment arm (inches): ";
    std::cin >> front_seat_arm;

    std::cout << "Enter the number of rear seat occupants: ";
    std::cin >> num_rear_seats;
    rear_seat_weights.resize(num_rear_seats); // rear seat weight vector resized to match # of rear seats
    for (int i = 0; i < num_rear_seats; ++i) {
        std::cout << "Enter the weight of rear seat occupant " << i+1 << " (lbs): ";
        std::cin >> rear_seat_weights[i];
    }
    std::cout << "Enter the rear seat moment arm (inches): ";
    std::cin >> rear_seat_arm;

    std::cout << "Enter the number of gallons of usable fuel (gallons): ";
    std::cin >> fuel_gal;
    std::cout << "Enter the usable fuel weight per gallon (lbs): ";
    std::cin >> fuel_weight_per_gal;
    std::cout << "Enter the fuel tank moment arm (inches): ";
    std::cin >> fuel_tank_arm;

    std::cout << "Enter the baggage weight (lbs): ";
    std::cin >> baggage_weight;
    std::cout << "Enter the baggage moment arm (inches): ";
    std::cin >> baggage_arm;

#else
    // hardcoded values
    empty_weight = 2050;
    empty_moment = 155400;
    num_front_seats = 2;
    front_seat_weights = {180, 150};
    front_seat_arm = 85;
    num_rear_seats = 2;
    rear_seat_weights = {160, 170};
    rear_seat_arm = 121;
    fuel_gal = 44;
    fuel_weight_per_gal = 6;
    fuel_tank_arm = 75;
    baggage_weight = 10;
    baggage_arm = 140;
#endif

    // front seat moment (uses total occupant weight of front seats)
    double front_seat_total_weight = 0;
    for (double weight:front_seat_weights) {  // weight var. holds current occupant's weight during each iter
        front_seat_total_weight += weight;
    }
    double front_seat_moment = front_seat_total_weight * front_seat_arm;

    // rear seat moment (uses total occupant weight of rear seats)
    double rear_seat_total_weight = 0;
    for (double weight:rear_seat_weights) {
        rear_seat_total_weight += weight;
    }
    double rear_seat_moment = rear_seat_total_weight*rear_seat_arm;

    // fuel moment
    double fuel_weight = fuel_gal*fuel_weight_per_gal;
    double fuel_moment = fuel_weight*fuel_tank_arm;

    // baggage moment
    double baggage_moment = baggage_weight*baggage_arm;

    // total moment
    double total_weight = empty_weight+front_seat_total_weight+rear_seat_total_weight+fuel_weight+baggage_weight;
    double total_moment = empty_moment+front_seat_moment+rear_seat_moment+fuel_moment+baggage_moment;
    double cg_location = total_moment/total_weight;

    // design limits
    const double max_gross_weight = 2950;
    const double forward_cg_limit = 82.1;
    const double aft_cg_limit = 84.7;

    // check limits
    bool weight_within_limit = total_weight <= max_gross_weight;
    bool cg_within_limit = (cg_location >= forward_cg_limit) && (cg_location <= aft_cg_limit);

    if (weight_within_limit && cg_within_limit) {
        std::cout << "The aircraft is within weight and CG limits.\n";
        std::cout << "Gross Weight: " << total_weight << " lbs\n";
        std::cout << "CG Location: " << cg_location << " inches\n";
    } else {
        std::cout << "The aircraft is NOT within weight and CG limits.\n";
        // adjust fuel weight
        double initial_fuel_weight = fuel_weight;
        double adjusted_fuel_weight = fuel_weight;
        bool found_solution = false;

        // reduce fuel weight
        for (adjusted_fuel_weight = initial_fuel_weight; adjusted_fuel_weight >= 0; adjusted_fuel_weight -= 0.01) {
            fuel_moment = adjusted_fuel_weight*fuel_tank_arm;
            total_weight = empty_weight+front_seat_total_weight+rear_seat_total_weight+adjusted_fuel_weight+baggage_weight;
            total_moment = empty_moment+front_seat_moment+rear_seat_moment+fuel_moment+baggage_moment;
            cg_location = total_moment/total_weight;
            weight_within_limit = total_weight <= max_gross_weight;
            cg_within_limit = (cg_location >= forward_cg_limit) && (cg_location <= aft_cg_limit);
            if (weight_within_limit && cg_within_limit) {
                found_solution = true;
                break;
            }
        }

        if (found_solution) {
            double fuel_difference = adjusted_fuel_weight - initial_fuel_weight;
            if (fuel_difference > 0) {
                std::cout << "Add " << fuel_difference << " lbs (" << fuel_difference / fuel_weight_per_gal << " gallons) of fuel to meet the limits.\n";
            } else {
                std::cout << "Drain " << -fuel_difference << " lbs (" << -fuel_difference / fuel_weight_per_gal << " gallons) of fuel to meet the limits.\n";
            }
            std::cout << "New Gross Weight: " << total_weight << " lbs\n";
            std::cout << "New CG Location: " << cg_location << " inches\n";
        } else {
            std::cout << "Unable to adjust fuel to meet weight and balance limits.\n";
        }
    }

    return 0;
}