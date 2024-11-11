/**
 * Title: Lab 29: Beta Release
 * Description: Add more actual code, refactor, optimize, test
 * Author: Nick Galvez
 * Class: COMSC-210
 *
 */

#include <iostream>
#include <algorithm> // for sort(), find()
#include <numeric>   // for accumulate()
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <array>
#include "EnvironmentReadingParser.h"

using namespace std;

/**
 * EnvironmentReading struct
 *
 * @param time_t time
 * @param double temperature
 * @param double soilMoisture
 * @param double battery
 */



/**
 My project will simulate a weather sensor for a garden, by allowing input of weather data for a given day, and simulating sensor reading for 3 sensors:

1. Battery charge
2. Soil moisture
3. Temperature

*/


/**
 * Prints the time in a human-readable format.
 *
 * @param time_t time
 * @param string format
 * @return string
 */
string printTime(const time_t &time, const string &format = "%Y-%m-%d %H:%M:%S")
{
    char buffer[80];
    strftime(buffer, 80, format.c_str(), localtime(&time));
    return buffer;
}


int main()
{
    // Get a new array of EnvironmentReading structs
    // Test file should be in the repo under the src directory.
    vector<EnvironmentReading> historicalData;

    // I will use a `std::map` of `std::array` to store the 3 datapoints, as well as the timestamp:
    map<time_t, array<double, 3>> readings;

    // Read the file. The API is not working, my key hasn't been activated yet so I tried generating some test data with chatgpt.
    int success = EnvironmentReadingParser::parseWeatherData("../all_weather_data.json", historicalData);
    
    // If the file was read successfully, add the data to the map
    if (success)
    {
        for (auto &reading : historicalData)
        {
            array<double, 3> data = {reading.time, reading.temperature, reading.uvi};
            readings[reading.time] = data;
        }
    }
    else
    {
        // error and exit
        cout << "Error reading file." << endl;
        return 1;
    }
}