

    // Set velocity
    myPlane.setVel(500.0);  // Example velocity in miles per hour

    // Call the operate function
    myPlane.operate(0.5);  // Operate for 0.5 hours

    // Print plane information
    std::cout << "Plane from " << myPlane.getOrigin() << " to " << myPlane.getDestination() << std::endl;
    std::cout << "Current position: " << myPlane.getPos() << " miles" << std::endl;
    std::cout << "Current velocity: " << myPlane.getVel() << " miles per hour" << std::endl;

    return 0;
}
//hello


