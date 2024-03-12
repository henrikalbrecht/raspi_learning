#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h> // for usleep

#define GPIO_NUMBER "1" // Change this to the GPIO pin number you're using

using namespace std;

// File paths for GPIO control
const string GPIO_PATH = "/sys/class/gpio/";
const string EXPORT_PATH = GPIO_PATH + "export";
const string UNEXPORT_PATH = GPIO_PATH + "unexport";

// Function to export a GPIO pin
void exportGPIO(const string &gpio)
{
    ofstream exportFile(EXPORT_PATH.c_str());
    if (exportFile.is_open())
    {
        exportFile << gpio;
        exportFile.close();
    }
    else
    {
        cerr << "Error exporting GPIO " << gpio << endl;
    }
}

// Function to unexport a GPIO pin
void unexportGPIO(const string &gpio)
{
    ofstream unexportFile(UNEXPORT_PATH.c_str());
    if (unexportFile.is_open())
    {
        unexportFile << gpio;
        unexportFile.close();
    }
    else
    {
        cerr << "Error unexporting GPIO " << gpio << endl;
    }
}

// Function to set direction of a GPIO pin
void setDirection(const string &gpio, const string &direction)
{
    string directionPath = GPIO_PATH + "gpio" + gpio + "/direction";
    ofstream directionFile(directionPath.c_str());
    if (directionFile.is_open())
    {
        directionFile << direction;
        directionFile.close();
    }
    else
    {
        cerr << "Error setting direction for GPIO " << gpio << endl;
    }
}

// Function to write value to a GPIO pin
void writeValue(const string &gpio, const string &value)
{
    string valuePath = GPIO_PATH + "gpio" + gpio + "/value";
    ofstream valueFile(valuePath.c_str());
    if (valueFile.is_open())
    {
        valueFile << value;
        valueFile.close();
    }
    else
    {
        cerr << "Error writing value to GPIO " << gpio << endl;
    }
}

int main()
{
    // Export GPIO pin
    exportGPIO(GPIO_NUMBER);

    // Set direction to output
    setDirection(GPIO_NUMBER, "out");

    // Blink LED 5 times
    for (int i = 0; i < 5; ++i)
    {
        // Turn LED on
        writeValue(GPIO_NUMBER, "1");
        usleep(500000); // Sleep for 0.5 seconds

        // Turn LED off
        writeValue(GPIO_NUMBER, "0");
        usleep(500000); // Sleep for 0.5 seconds
    }

    // Unexport GPIO pin
    unexportGPIO(GPIO_NUMBER);

    return 0;
}
