#pragma once
#include <iostream>
using namespace std;

/// <summary>
/// Sqrt class
/// Sqrt.cpp i�inde fonksiyonu tekrar kullan�lmas� ve i�i bo� tan�mlanmas� i�in virtual tan�mland�.
/// </summary>
class SqrtH{
public:
	virtual int getSolution(int x) = 0;
};

