/**
 * Title: Lab 32: Carz
 * Description: Make a deque
 * Author: Nick Galvez
 * Class: COMSC-210
 *
 */

#include <iostream>
#include <deque>
#include <string>
#include <EnvironmentReadingParser.h>
#include "NG_Time.h"
#include "Car.h"
using namespace std;

const int INITIAL_CARS = 2;

/**
 * Just print a space
 */
ostream& s(ostream& os) {
    os << " ";
    return os;
}

int main()
{
    deque<Car> cars;

cout << "Initial Queue:" << endl;
    for (size_t i = 0; i < INITIAL_CARS; i++)
    {
        cars.push_back(Car());
        cout << "[" << cars[i].getYear() << s << cars[i].getMake() << s << cars[i].getTransponder() << "] " << "🏎" << endl;
    }
    



    
}