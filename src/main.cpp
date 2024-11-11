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
#include "Time.h"
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


bool testPrintTime()
{
    // https://www.epochconverter.com/
    time_t time = 0;
    string expected = "1969-12-31 16:00:00"; // Pacific time
    string result = printTime(time, "%Y-%m-%d %H:%M:%S");
    cout << "Expected: " << expected << " Got: " << result << endl;
    return expected == result;
}

bool testEnvironmentReadingParserOpens()
{
    vector<EnvironmentReading> historicalData;
    int success = EnvironmentReadingParser::parseWeatherData("../all_weather_data.json", historicalData);
    return success;
}

bool testEnvironmentReadingParserReads()
{
    vector<EnvironmentReading> historicalData;
    int success = EnvironmentReadingParser::parseWeatherData("../all_weather_data.json", historicalData);
    // echo the first 5 readings
    for (int i = 0; i < 5; i++)
    {
        cout << "Reading " << i << ": " << historicalData[i].temperature << "°K, " << historicalData[i].uvi << " UVI" << historicalData[i].time << " time "<< endl;
    }

    return historicalData.size() > 0;
}

/**
 * 
 */
double simulateBatteryCharge(const double &uvi, const time_t &time)
{
    // Simulate the battery charge
    // Battery charge is proportional to UVI and time of day
    // Battery charge is 100% at noon, and 0% at midnight
    // Battery charge is also inversely proportional to UVI
    // I admit, I got help with this. Math is not my strong suit.
    return 100 - (abs(12 - localtime(&time)->tm_hour) + uvi) / 2;
}
/**
 * Simulates the soil moisture based on the UVI and temperature.
 *
 * @param double uvi
 * @param double temperature
 * @return double
 */
double simulateSoilMoisture(const double &uvi, const double &temperature) {
    // Simulate the soil moisture
    // Soil moisture is inversely proportional to UVI and temperature. I admit, I got help with this. Math is not my strong suit.
    return 100 - (uvi + temperature) / 2;
}

double testSimulateSoilMoisture() {
    double uvi = 5.0;
    double temperature = 90.0;
    double expected = 97.5;
    double result = simulateSoilMoisture(uvi, temperature);
    return expected == result;
}

int main()
{

    // Test the printTime function
    cout << "Test printTime: " << (testPrintTime() ? "PASSED" : "FAILED") << endl;
    cout << "Test EnvironmentReadingParser Opens: " << (testEnvironmentReadingParserOpens() ? "PASSED" : "FAILED") << endl;
    cout << "Test EnvironmentReadingParser Reads: " << endl << (testEnvironmentReadingParserReads() ? "PASSED" : "FAILED") << endl;
    cout << endl;
    cout << endl;
    cout << "Running Simulation..." << endl;
    // Get a new array of EnvironmentReading structs
    // Test file should be in the repo under the src directory.
    vector<EnvironmentReading> historicalData;

    // I will use a `std::map` of `std::array` to store the 3 datapoints, as well as the timestamp:
    // This should look like:
    /*
     day [
     time [
        soilMoisture,
        battery
        temperature
    ],
*/
    map<string, map<time_t, array<double, 3>>> readings;

    // Read the file. The API is not working, my key hasn't been activated yet so I tried generating some test data with chatgpt.
    int success = EnvironmentReadingParser::parseWeatherData("../all_weather_data.json", historicalData);
    
    // If the file was read successfully, add the data to the map
    // For each record:
    // Call the simulate soil moisture function based on the UVI and temperature
    // Call the simulate battery charge function based on the UVI and time of day
    // Call the simulate temperature function (should be simple)
    // Push the data to the map
    if (success)
    {
        for (const auto &reading : historicalData)
        {
            // Create a new array for the data
            array<double, 3> data;
            // Simulate the battery charge
            data[0] = simulateBatteryCharge(reading.uvi, reading.time);
            // Simulate the soil moisture
            data[1] = simulateSoilMoisture(reading.uvi, reading.temperature);
            // Add the temperature
            data[2] = reading.temperature;
            // Add the data to the map
            readings[reading.day][reading.time] = data;
        }
    }
    // Print the data
    for (const auto &reading : readings)
    {
        cout << "Day: " << reading.first << endl;
        for (const auto &time : reading.second)
        {
            cout << "Time: " << printTime(time.first) << endl;
            cout << "Soil Moisture: " << time.second[0] << "%" << endl;
            cout << "Battery: " << time.second[1] << "%" << endl;
            cout << "Temperature: " << time.second[2] << "°K" << endl;
            cout << endl;
        }
        cout << endl;
    }
}