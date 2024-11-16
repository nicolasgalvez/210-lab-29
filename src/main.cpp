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
ostream &s(ostream &os)
{
    os << " ";
    return os;
}

void printCar(Car &car) {
    cout << "[" << car.getYear() << s << car.getMake() << s << car.getTransponder() << "] " << "🏎" << endl;
}

int main()
{
    deque<Car> cars;

    cout << "Initial Queue:" << endl;
    for (size_t i = 0; i < INITIAL_CARS; i++)
    {
        cars.push_front(Car());
        printCar(cars.front());
    }
    int time = 0;
    while (cars.size() > 0)
    {
        bool movement = false;
        time++;
        cout << "Time: " << time << endl;

        // 55% probability that the car at the head of the line pays its toll and leaves the toll booth
        if (rand() % 100 < 55)
        {
            cout << "Car at the head of the line paid its toll and left the toll booth." << endl;
            cars.pop_front();
            movement = true;
        }
        if (rand() % 100 < 45)
        { // 45% probability that another car joins the line for the toll booth
            cout << "Another car joined the line for the toll booth." << endl;
            cars.push_back(Car());
            movement = true;
        }
        if (!movement)
        {
            cout << "It's a traffic jam! No cars moved." << endl;
        }
        cout << endl
             << endl;
    } 

    cout << "All cars have left the toll booth." << endl;

    return 0;
}