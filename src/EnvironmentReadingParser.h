/**
 * EnvironmentReadingParser will be used to take json data from an API call and parse it into a vector of EnvironmentReading structs.
 * Right now I have a stored test file for the class. Sadly the LLM making the file wasn't able to generate 200 records like I wanted
 * The open weather API key I signed up for isn't available right away, so I'm stuck for now.
 */

#ifndef ENVIRONMENT_READING_PARSER_H
#define ENVIRONMENT_READING_PARSER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include "json.hpp"
#include "Time.h"

using json = nlohmann::json;
using namespace std;

// Define the EnvironmentReading struct
struct EnvironmentReading
{
    string day;
    time_t time;
    double temperature;
    double uvi;
    ~EnvironmentReading() {}
};

class EnvironmentReadingParser
{
public:
    // Parses the JSON file and fills the vector of EnvironmentReading
    static bool parseWeatherData(const string &filePath, vector<EnvironmentReading> &readings)
    {
        // Open and parse the JSON file
        ifstream inFile(filePath);
        if (!inFile.is_open())
        {
            cerr << "Error: Could not open file." << endl;
            return false;
        }

        json weatherData;
        inFile >> weatherData;
        inFile.close();

        // Loop through each day's data
        for (const auto &day : weatherData)
        {
            if (day.contains("hourly"))
            {
                // Extract hourly data
                for (const auto &hour : day["hourly"])
                {
                    // Create a new EnvironmentReading instance
                    EnvironmentReading reading;

                    // Extract and assign values
                    
                    reading.temperature = hour["temp"].get<double>(); // Temperature in Kelvin
                    // store the time 
                    reading.time = hour["dt"].get<time_t>(); // Time in seconds since epoch
                    reading.uvi = hour.value("uvi", 0.0);             // UV index (use 0.0 if not available)
                    // store the day from dt a string
                    time_t tempTime = hour["dt"].get<time_t>();
                    
                    reading.day = printTime(tempTime, "%Y-%m-%d");

                    reading.day = reading.day.substr(0, 10);    

                    // that will be used as the key. Technically, we don't need it for every record. TODO: refactor this.
                    readings.push_back(reading);
                }
            }
        }

        return true;
    }
};

#endif // ENVIRONMENT_READING_PARSER_H
