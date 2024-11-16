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
#include <locale>
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

void printCar(Car &car)
{
    cout << "[" << car.getYear() << s << car.getMake() << s << car.getTransponder() << "] " << endl;
}
/**
 * Print the queue of cars
 * TODO: fix emojis, they are going beyond the end of the cars.
 */
void printQueue(deque<Car> &cars)
{
    // Set the locale to enable UTF-8 output. I guess this is why the vscode terminal doesn't display emojis.
    locale::global(locale("en_US.UTF-8"));
    wcout.imbue(locale());
    // Not sure if this works on all terminal emulators.

    int iconOffset = 0x0;
    int iconStart = 0x1F695;
    for (size_t i = 0; i < cars.size(); i++)
    {
        printCar(cars[i]);
    }
    // for each car, print a car emoji starting from 0x1F695 and incrementing by 1
    for (size_t i = 0; i < cars.size(); i++) {
        wchar_t emoji = static_cast<wchar_t>(iconStart + iconOffset); // Calculate the Unicode emoji. Thanks to https://unicode.org/emoji/charts/full-emoji-list.html
        wcout << emoji << L" "; 
        iconOffset++; 
        if (iconOffset > 0x1F6C0 - 0x1F695) { 
            iconOffset = 0; // Reset the offset
        }
    }
    cout << endl;
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
        if (arc4random() % 100 < 55)
        {
            cout << "Car at the head of the line paid its toll and left the toll booth." << endl;
            cars.pop_front();
            movement = true;
        }
        if (arc4random() % 100 < 45)
        { // 45% probability that another car joins the line for the toll booth
            
            cars.push_back(Car());
            cout << "A " << cars.back().getMake() << " joined the line for the toll booth." << endl;

            movement = true;
        }
        if (!movement)
        {
            cout << "It's a traffic jam! No cars moved." << endl;
        }


        // Print the queue
        cout << "Queue:" << endl;
        if (cars.size() > 0)
        {
            
            printQueue(cars);
        }
        else
        {
            cout << "EMPTY" << endl;
        }

        cout << endl;
    }

    cout << "All cars have left the toll booth." << endl;

    return 0;
}