// BitesMulakat.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#include "MaxNumberInterface.cpp"
#include "Sqrt.cpp"
#include "BinaryTreeInterface.cpp"

using namespace std;

int count(10);
class A {
public:
    static int count;
    class B {
    public:
        static int count;
    };
};

int A::count(42);
int A::B::count(453284);

int main()
{
    vector<int> vec1 = { 1, 3, -1, -3, 5, 3, 6, 7 };
    MaxNumberInterface maxNumber;
    printVector(maxNumber.getSolution(vec1, 3));


    Sqrt sqrt;
    cout << sqrt.getSolution(8) << endl;

    cout << ::count << endl;
    cout << A::count << endl;
    cout << A::B::count << endl;
    return EXIT_SUCCESS;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu



