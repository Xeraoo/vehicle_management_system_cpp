#include "Factory.h"
#include "Commission.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

ifstream appArg; // Declaration for input file stream
bool file = false; // Flag to check if file input is used

// Template function to get user input or read from a file
template <typename T>
T getValue(bool files, ifstream& appArgs);

// Template function to check if a value is within a specified range
template <typename T>
bool rangeNumValue(T min, T max, T arg);

// Function to create a Factory object
Factory* createFactory(string brand, int capacity, bool quality);

// Function to determine the selected factory
int inWhichFactory(Factory *_factory, int _nrOfFactories);

// Menu function to create a vehicle
void createVehicleMenu(Factory *_factory, int _nrOfFactories);

// Function to list vehicles from a specific factory or all factories
int* listVehicleMenu(Factory *_factory, int _nrOfFactories);

// Menu function for vehicle sales
void saleVehicleMenu(Factory *_factory, int _nrOfFactories, vector<Vehicle*> *soldVehicles);

// Menu function to drive a motor vehicle
void driveMotorVehicleMenu(Factory *_factory, int _nrOfFactories, vector<Vehicle*> *soldVehicles);

// Menu function for commissions
void commissionMenu(Commission* commission, vector<Vehicle*> soldVehicles);

// Menu function for changing vehicle color (sprayer)
void sprayerMenu(Factory *_factory, int _nrOfFactories);

int main(int argc, char* argv[]) {
    // Check if a file argument is provided
    if (argc > 1) {
        appArg.open(argv[1]); // Open the specified file
        if (appArg.is_open()) {
            cout << "\nFile stdin.txt has been opened properly!\n" << endl;
        }
        file = true; // Set file flag to true
    }

    cout << "///////////////////////////////////////////////////////////////" << endl;
    cout << "<<<<<<<<<<<<<<<<<<<<<<WELCOME TO FACTORY>>>>>>>>>>>>>>>>>>>>>>" << endl;
    cout << "Type the number of factories that you would like to have (maximum 20):" << endl;
    
    int nrOfFactories = -1; // Initialize number of factories
    // Loop to get valid input for number of factories
    while (rangeNumValue(1, 10, nrOfFactories)) {
        nrOfFactories = getValue<int>(file, appArg); // Get user input or read from file
    }

    // Dynamically allocate an array of Factory objects
    auto* factory = new Factory[nrOfFactories];
    vector<Vehicle*> soldVehicles; // Vector to hold sold vehicles
    auto *commission = new Commission(0); // Create a commission object

    // Loop to add factories
    for (int i = 0; i < nrOfFactories; i++) {
        cout << "\nFactory " << i + 1 << " of " << nrOfFactories << endl;
        cout << "Type brand of each factory:" << endl;
        string brand = getValue<string>(file, appArg); // Get brand input

        cout << "Type main capacity for this factory: \n(main capacity = car capacity, 2 times larger than motorcycle capacity and 50 larger than basket capacity)" << endl;
        int capacity = -1;
        // Loop to get valid capacity input
        while (rangeNumValue(100, 500, capacity)) {
            capacity = getValue<int>(file, appArg);
        }

        cout << "Is it luxury or budget? Type 1 for luxury, and 0 for budget" << endl;
        bool quality = getValue<bool>(file, appArg); // Get quality input

        // Create a Factory object and assign it to the array
        factory[i] = *createFactory(brand, capacity, quality);
    }

    int step = 0; // Variable to track menu option selection

    // Main menu loop
    do {
        cout << "\n/////////////////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
        cout << "\n<<<<<<<<<<<<<<<<<<<<<<MENU>>>>>>>>>>>>>>>>>>>>>>" << endl;
        cout << "Choose one option by typing number next to it:" << endl;
        cout << "<1> Create new vehicle" << endl;
        cout << "<2> List vehicles from one factory or from all" << endl;
        cout << "<3> Sale vehicle" << endl;
        cout << "<4> Drive motor vehicle" << endl;
        cout << "<5> Go to commission (sale or buy motor vehicle)" << endl;
        cout << "<6> Go to sprayer (to change color of vehicle)" << endl;
        cout << "<7> End" << endl;

        // Read user input or read from file
        if (file) {
            appArg >> step;
            cout << "    INPUT: " << step << endl;
        } else {
            cout << "    INPUT: ";
            cin >> step;
        }

        // Switch-case to handle menu options
        switch (step) {
            case 1:
                createVehicleMenu(factory, nrOfFactories); // Create vehicle
                break;
            case 2:
                try {
                    listVehicleMenu(factory, nrOfFactories); // List vehicles
                } catch (NoVehicleError &noVehicleError) { // Catch exception if no vehicles available
                    cout << "\nERROR: " << noVehicleError.warning << endl; // Print error message
                }
                break;
            case 3:
                saleVehicleMenu(factory, nrOfFactories, &soldVehicles); // Sale vehicle
                break;
            case 4:
                driveMotorVehicleMenu(factory, nrOfFactories, &soldVehicles); // Drive vehicle
                break;
            case 5:
                commissionMenu(commission, soldVehicles); // Go to commission menu
                break;
            case 6:
                sprayerMenu(factory, nrOfFactories); // Go to sprayer menu
                break;
            case 7:
                cout << "\n<<<<<<<<<<<<<<<<<<<<<<GOODBYE!>>>>>>>>>>>>>>>>>>>>>>" << endl;
                break;
            default:
                cout << "Type one of the numbers above!" << endl; // Invalid option
        }
    } while (step != 7); // Exit loop when option 7 is chosen

    delete[] factory; // Free allocated memory for factories
    delete commission; // Free allocated memory for commission

    return 0; // Exit program
}

// Template function to get user input or read from a file
template <typename T>
T getValue(bool files, ifstream& appArgs) {
    T arg;
    if (files) {
        appArgs >> arg; // Read from file
        cout << "    INPUT: " << arg << endl;
    } else {
        cout << "    INPUT: ";
        cin >> arg; // Read from console

        // Validate input type
        while (cin.fail()) {
            cout << "You typed a value of the wrong type, try again." << endl;
            cin.clear(); // Clear the error state
            cin.ignore(1000, '\n'); // Discard invalid input
            cout << "    INPUT: ";
            cin >> arg; // Retry input
        }
    }
    return arg; // Return the input value
}

// Template function to check if a value is within a specified range
template <typename T>
bool rangeNumValue(T min, T max, T arg) {
    if (arg < min || arg > max) {
        cout << "Type value from " << min << " to " << max; // Specify valid range
        if (arg == static_cast<int>(arg)) // Check if the value is an integer
            cout << " that is an integer!" << endl; // For integer type
        else
            cout << " that is a floating-point number!" << endl; // For floating-point type
        return true; // Indicate invalid range
    }
    return false; // Indicate valid range
}

// Function to create a Factory object
Factory* createFactory(string brand, int capacity, bool quality) {
    auto* factory = new Factory(brand, capacity, quality); // Allocate a new Factory object
    return factory; // Return pointer to the Factory
}

// Function to determine the selected factory
int inWhichFactory(Factory *_factory, int _nrOfFactories) {
    cout << "<<<<<<<<<<<<<<<<<<<<<<CHOOSE FACTORY>>>>>>>>>>>>>>>>>>>>>>" << endl;
    cout << "You've got " << _nrOfFactories << " factories to choose:" << endl;
    for (int i = 0; i < _nrOfFactories; i++) {
        cout << i << ".";
        _factory[i].printFactory(); // Print available factories
        cout << endl;
    }

    cout << "Type the number of the factory that you are interested in: " << endl;
    int selected = -1; // Initialize selected factory index
    // Loop to get valid factory selection
    while (rangeNumValue(0, _nrOfFactories - 1, selected)) {
        selected = getValue<int>(file, appArg); // Get user input
    }

    return selected; // Return the selected factory index
}

void createVehicleMenu(Factory *_factory, int _nrOfFactories) // Creates and adds a vehicle to the selected factory by the user
{
    cout << "\n<<<<<<<<<<<<<<<<<<<<<<CREATE VEHICLE>>>>>>>>>>>>>>>>>>>>>>" << endl;

    cout << "\nIn which factory would you like to put your vehicle?" << endl;
    int fNr = inWhichFactory(_factory, _nrOfFactories); // Get the selected factory number

    cout << "\nType number next to the vehicle you choose: \n <0> Car\n <1> Motorcycle\n <2> Bike" << endl;
    int kindOfVehicle = -1;
    while (rangeNumValue(0, 2, kindOfVehicle)) // Loop until a valid vehicle type is chosen
    {
        kindOfVehicle = getValue<int>(file, appArg); // Get user input for vehicle type
    }

    // Prompt for RGB color values
    cout << "\nType RGB colour values (press enter between them):" << endl;
    cout << "\nSAMPLE VALUES: \nBlack[0,0,0], White[255,255,255], Red[255,0,0], Green[0,255,0], Blue[0,0,255]" << endl;

    int rgb[3] = { -1, -1, -1 }; // Array to hold RGB values

    // Loop to get RGB values from the user
    for (int i = 0; i < 3; i++)
    {
        cout << "\nRGB[" << i << "]:" << endl;
        while (rangeNumValue(0, 255, rgb[i])) // Validate RGB input
        {
            rgb[i] = getValue<int>(file, appArg); // Get user input for RGB value
        }
    }

    int doors = -1; // Variable to hold number of doors for cars
    bool basket = -1; // Variable to determine if the vehicle is a basket (for bikes)

    if (kindOfVehicle == 0) // If the vehicle is a car
    {
        cout << "\nType number of doors:" << endl;
        while (rangeNumValue(1, 5, doors)) // Validate door count input
        {
            doors = getValue<int>(file, appArg); // Get user input for number of doors
        }
    }

    if (kindOfVehicle == 2) // If the vehicle is a bike
    {
        cout << "\nIf you like to have a basket type 1, otherwise type 0:" << endl;
        basket = getValue<bool>(file, appArg); // Get user input for basket option
    }

    // Create the vehicle in the selected factory with specified parameters
    _factory[fNr].createVehicle(kindOfVehicle, doors, rgb[0], rgb[1], rgb[2], basket);
}

int* listVehicleMenu(Factory *_factory, int _nrOfFactories) // Lists and counts vehicles in factories
{
    int* tabNrOfVehicles = new int[_nrOfFactories]{0}; // Array to monitor vehicle count in each factory

    cout << "\n<<<<<<<<<<<<<<<<<<<<<<LIST VEHICLES>>>>>>>>>>>>>>>>>>>>>>" << endl;

    cout << "Here is the list of all vehicles (number next to vehicle refers to the one in factory):" << endl;
    for (int i = 0; i < _nrOfFactories; i++)
    {
        cout << "\nFACTORY: ";
        _factory[i].printFactory(); // Print factory name
        cout << endl;
        tabNrOfVehicles[i] = _factory[i].listVehicles(); // List vehicles from each factory and store the count
    }

    // If no vehicles exist in any factory, throw NoVehicleError
    int sum = 0;
    for (int i = 0; i < _nrOfFactories; i++)
    {
        sum += tabNrOfVehicles[i]; // Calculate total number of vehicles
    }

    if (sum == 0)
        throw NoVehicleError(); // Throw error if no vehicles are found

    return tabNrOfVehicles; // Return array of vehicle counts for each factory
}

void saleVehicleMenu(Factory *_factory, int _nrOfFactories, vector<Vehicle*> *soldVehicles) // Moves vehicle to sold vehicles vector and changes its owner
{
    cout << "\n<<<<<<<<<<<<<<<<<<<<<<SALE VEHICLE>>>>>>>>>>>>>>>>>>>>>>" << endl;

    cout << "Let's see the offer!" << endl;

    try
    {
        int* check = listVehicleMenu(_factory, _nrOfFactories); // Check and list vehicles, ensuring at least one vehicle exists

        cout << "\nIn which factory would you like to buy the vehicle?" << endl;
        int fNr = inWhichFactory(_factory, _nrOfFactories); // Get selected factory for purchase

        int size = check[fNr]; // Check number of vehicles in selected factory
        if (size != 0)
        {
            cout << "\nChoose the vehicle that you want to buy by typing the number next to it in LIST VEHICLES:" << endl;
            int nr = -1;

            while (rangeNumValue(0, size - 1, nr)) // Loop until a valid vehicle index is chosen
            {
                nr = getValue<int>(file, appArg); // Get user input for vehicle index
            }

            cout << "Type new owner:" << endl;
            string newOwner = getValue<string>(file, appArg); // Get user input for new owner's name

            soldVehicles->push_back(_factory[fNr].saleVehicle(nr, newOwner)); // Add sold vehicle to the soldVehicles vector
        }
        else
        {
            cout << "You chose a factory with no vehicles!" << endl; // Notify if selected factory has no vehicles
        }
    }
    catch (NoVehicleError &noVehicleError) // Catch NoVehicleError if no vehicles are present
    {
        cout << "\nERROR: " << noVehicleError.warning << endl; // Display error message
    }
}

void driveMotorVehicleMenu(Factory *_factory, int _nrOfFactories, vector<Vehicle*> *soldVehicles) // Increases vehicle mileage, decreases fuel amount, allows vehicle to be sold while driving
{
    cout << "\n<<<<<<<<<<<<<<<<<<<<<<DRIVE VEHICLE>>>>>>>>>>>>>>>>>>>>>>" << endl;
    cout << "Let's see the offer!" << endl;

    try // Error handling in case there are no vehicles in factories
    {
        int* check = listVehicleMenu(_factory, _nrOfFactories);

        cout << "\nIn which factory would you like to drive a motor vehicle?" << endl;
        int fNr = inWhichFactory(_factory, _nrOfFactories); // Get selected factory for driving

        int size = check[fNr]; // Get the number of vehicles in the selected factory
        if (size != 0)
        {
            cout << "\nChoose the motor vehicle (not bike!) that you want to drive by typing the number next to it in LIST VEHICLES:" << endl;

            int nr = -1;
            while (rangeNumValue(0, size - 1, nr)) // Loop until a valid vehicle index is chosen
            {
                nr = getValue<int>(file, appArg); // Get user input for vehicle index
            }

            try // Check for bike selection
            {
                _factory[fNr].getVehicle(nr)->bikeKind(); // Ensure selected vehicle is not a bike

                auto* ptrToVehicle = dynamic_cast<MotorVehicle*>(_factory[fNr].getVehicle(nr)); // Cast to MotorVehicle

                cout << "\nWhat is the distance that you want to drive?" << endl;
                float distance = -1.01; // Initialize distance variable
                while (rangeNumValue<float>(0.0, 1000.0, distance)) // Validate distance input
                {
                    distance = getValue<float>(file, appArg); // Get user input for distance
                }

                try // Check for sufficient fuel
                {
                    ptrToVehicle->driveMotorVehicle(distance); // Drive the vehicle, update mileage and fuel
                }
                catch (NoFuelError &noFuelError) // Catch NoFuelError if fuel is insufficient
                {
                    cout << "\nERROR: " << noFuelError.warning << endl; // Display error message
                }
                catch (LowFuelError &lowFuelError) // Catch LowFuelError for low fuel conditions
                {
                    cout << "\nERROR: " << lowFuelError.warning << endl; // Display error message
                    cout << "You stop after: " << lowFuelError.maxDistance << endl; // Display maximum distance traveled
                }

                cout << "\nIf you liked the ride and you want to buy this vehicle, type 0; otherwise, type 1:" << endl;
                bool decision = getValue<bool>(file, appArg); // Get user decision on purchasing

                if (decision == 0) // If the user wants to buy the vehicle
                {
                    cout << "Type new owner:" << endl;
                    string newOwner = getValue<string>(file, appArg); // Get user input for new owner's name

                    soldVehicles->push_back(_factory[fNr].saleVehicle(nr, newOwner)); // Add sold vehicle to the soldVehicles vector
                }
                else if (decision == 1) // If the user does not want to buy the vehicle
                {
                    cout << "Consider trying a different vehicle!" << endl; // Suggest trying another vehicle
                }
            }
            catch (BikeError &bikeError) // Catch BikeError if a bike is selected
            {
                cout << "\nERROR: " << bikeError.warning << endl; // Display error message
            }
        }
        else
        {
            cout << "You chose a factory with no vehicles!" << endl; // Notify if selected factory has no vehicles
        }
    }
    catch (NoVehicleError &noVehicleError) // Catch NoVehicleError if no vehicles are present
    {
        cout << "\nERROR: " << noVehicleError.warning << endl; // Display error message
    }
}

void listSoldVehiclesMenu(vector<Vehicle*> *soldVehicles) // Lists all sold vehicles
{
    cout << "\n<<<<<<<<<<<<<<<<<<<<<<LIST SOLD VEHICLES>>>>>>>>>>>>>>>>>>>>>>" << endl;

    if (!soldVehicles->empty()) // Check if sold vehicles exist
    {
        for (size_t i = 0; i < soldVehicles->size(); i++)
        {
            cout << "\nSold Vehicle #" << i + 1 << ":" << endl;
            soldVehicles->at(i)->printInfo(); // Print information for each sold vehicle
        }
    }
    else
    {
        cout << "No vehicles have been sold yet." << endl; // Notify if no vehicles have been sold
    }
}

void commissionMenu(Commission* commission, vector<Vehicle*> soldVehicles)
// Moves a vehicle from the sold vehicles list to the commission or allows the sale of a vehicle from the commission, while updating the vehicle owner.
{
    cout << "\n<<<<<<<<<<<<<<<<<<<<<<COMMISSION>>>>>>>>>>>>>>>>>>>>>>" << endl;
    cout << "\nIf you'd like to sell a vehicle to the commission, type 0. If you'd like to buy a vehicle from the commission, type 1:" << endl;
    bool decision = getValue<bool>(file, appArg);

    if (decision == 0) // Moving a vehicle from the sold list to the commission
    {
        if (!soldVehicles.empty()) // Checks if the sold vehicles vector is not empty
        {
            cout << "\nHere is the list of available vehicles:" << endl;

            int size = static_cast<int>(soldVehicles.size());
            for (int i = 0; i < size; i++) // Displays vehicles from soldVehicles vector with their prices
            {
                cout << i << ". ";
                soldVehicles[i]->printVehicle(); // Print vehicle details
                cout << endl;

                if (soldVehicles[i]->bikeInList()) // Check if it's a bike and print purchase price if applicable
                {
                    cout << "Purchase price: " << Commission::purchasePrice(dynamic_cast<MotorVehicle*>(soldVehicles[i])) << endl;
                }
                else
                {
                    cout << "NOT FOR PURCHASE!" << endl;
                }

                cout << endl;
            }

            cout << "\nChoose the vehicle you want to sell by typing the number next to it:" << endl;
            cout << "Note: You cannot choose a bike!" << endl;
            int vehicleNumber = -1;

            while (rangeNumValue(0, size - 1, vehicleNumber))
            {
                vehicleNumber = getValue<int>(file, appArg); // Ensure valid vehicle number
            }

            try // Prevent selecting a bike by mistake
            {
                soldVehicles[vehicleNumber]->bikeKind(); // Throws an error if a bike is chosen
                commission->sellToCommission(dynamic_cast<MotorVehicle*>(soldVehicles[vehicleNumber]));
            }
            catch (BikeError &bikeError) // Catching and handling the error if a bike is selected
            {
                cout << "\nERROR: " << bikeError.warning << endl;
            }
        }
        else
        {
            cout << "There is no vehicle to sell!" << endl;
        }
    }
    else if (decision == 1) // Buying a vehicle from the commission
    {
        if (commission->printCommission()) // Checks if there are vehicles in the commission and prints them
        {
            cout << "\nChoose the vehicle you want to buy by typing the number next to it:" << endl;
            int vehicleNumber = -1;

            int size = commission->square.size(); // Get the number of vehicles in the commission

            while (rangeNumValue(0, size - 1, vehicleNumber))
            {
                vehicleNumber = getValue<int>(file, appArg); // Ensure valid vehicle number
            }

            cout << "Type the new owner's name:" << endl;
            string newOwner = getValue<string>(file, appArg); // Input for the new owner

            commission->buyFromCommission(vehicleNumber, newOwner); // Process the purchase
        }
    }
}

void sprayerMenu(Factory* _factory, int _nrOfFactories) // Changes the color of a selected vehicle from the factory
{
    cout << "\n<<<<<<<<<<<<<<<<<<<<<<SPRAYER>>>>>>>>>>>>>>>>>>>>>>" << endl;
    cout << "List of vehicles in factories:" << endl;

    try
    {
        int* check = listVehicleMenu(_factory, _nrOfFactories); // List vehicles from factories

        cout << "\nIn which factory would you like to choose the vehicle?" << endl;
        int fNr = inWhichFactory(_factory, _nrOfFactories); // Select factory

        int size = check[fNr]; // Check if there are vehicles in the selected factory
        if (size != 0)
        {
            cout << "\nChoose the vehicle that you want to repaint by typing the number next to it:" << endl;
            int nr = -1;

            while (rangeNumValue(0, size - 1, nr))
            {
                nr = getValue<int>(file, appArg); // Ensure valid vehicle number
            }

            Vehicle* ptrToVehicle = _factory[fNr].getVehicle(nr); // Pointer to the selected vehicle

            cout << "Type RGB color values (press Enter after each):" << endl;
            cout << "Values must be from 0 to 255!\n\nSAMPLE VALUES: \nBlack[0,0,0], White[255,255,255], Red[255,0,0], Green[0,255,0], Blue[0,0,255]" << endl;

            int rgbNew[3] = { -1, -1, -1 }; // Array to hold RGB values

            for (int i = 0; i < 3; i++) // Input RGB values
            {
                cout << "\nRGB[" << i << "]:" << endl;
                while (rangeNumValue(0, 255, rgbNew[i]))
                {
                    rgbNew[i] = getValue<int>(file, appArg); // Ensure valid RGB value
                }
            }

            Sprayer::paintOver(ptrToVehicle, rgbNew); // Change the color of the vehicle

            cout << "\nThe vehicle has been painted!" << endl;
        }
        else
        {
            cout << "You selected a factory with no vehicles!" << endl;
        }
    }
    catch (NoVehicleError &noVehicleError) // Catch and handle the error if no vehicles are present
    {
        cout << "\nERROR: " << noVehicleError.warning << endl;
    }
}