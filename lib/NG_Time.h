#ifndef TIME_H
#define TIME_H

#include <string>
#include <ctime>

using namespace std;
/** 
 * Make a class for time, not make time for class.
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
#endif // Time.h