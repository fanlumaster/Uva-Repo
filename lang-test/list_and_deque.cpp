#include <algorithm>
#include <iostream>
#include <list>
#include <deque>

int main()
{
    // Create a list containing integers
    std::list<int> l = {7, 5, 16, 8};

    // Add an integer to the front of the list
    l.push_front(13);
    // Add an integer to the back of the list
    l.push_back(25);

    // Print out the list
    std::cout << "l = { ";
    for (int n : l)
        std::cout << n << ", ";
    std::cout << "};\n";

    // ======================================================= //

    // Create a deque containing integers
    std::deque<int> d = {7, 5, 16, 8};

    // Add an integer to the beginning and end of the deque
    d.push_front(13);
    d.push_back(25);

    std::cout << "d = { ";
    // Iterate and print values of deque
    for (int n : d)
        std::cout << n << ", ";
    std::cout << "};\n";
}
