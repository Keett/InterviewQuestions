#pragma once
#include <iostream>
using namespace std;

/// <summary>
/// Sqrt class
/// Sqrt.cpp içinde fonksiyonu tekrar kullanýlmasý ve içi boþ tanýmlanmasý için virtual tanýmlandý.
/// </summary>
class SqrtH{
public:
	virtual int getSolution(int x) = 0;
};

