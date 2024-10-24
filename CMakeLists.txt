cmake_minimum_required(VERSION 3.17)
project(ProjectName)  

set(CMAKE_CXX_STANDARD 14)

# Define the executable and its source files.
add_executable(ProjectName  
    main.cpp
    Factory.cpp Factory.h
    Car.cpp Car.h
    Vehicle.cpp Vehicle.h
    MotorVehicle.cpp MotorVehicle.h
    Bike.cpp Bike.h
    Motorcycle.cpp Motorcycle.h
    Sprayer.cpp Sprayer.h
    Commission.cpp Commission.h
    ErrorVehicles.h
)

# Copy input file to the binary directory.
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/stdin.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
