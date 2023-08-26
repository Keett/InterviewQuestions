#pragma once

#include <vector>

using namespace std;

/// <summary>
/// IMaxNumber interface class
/// </summary>
__interface IMaxNumber {
public:
    vector<int> getSolution(vector<int>& nums, int k) = 0;
};
