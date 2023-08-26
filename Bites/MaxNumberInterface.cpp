#include "MaxNumberInterface.h"

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/// <summary>
/// MaxNumberInterface, IMaxNumber'dan inherite edilmiþtir.
/// Beklenilen çözüm yolu
/// </summary>
class MaxNumberInterface : public IMaxNumber {
public:
    // Inherited via IMaxNumber
    virtual vector<int> getSolution(vector<int>& nums, int k) override
    {
        /* if (k == 1)
        {
            return vec;
        }
        else {
            vector<int> yeniVec;
            int temp;

            for (int i = 0; i < vec.size() - (k - 1); i++)
            {
                temp = vec.at(i);
                for (int j = (i + 1); j < (k + i) && (j < vec.size()); j++)
                {
                    temp = temp > vec.at(j) ? temp : vec.at(j);
                }
                yeniVec.push_back(temp);
            }
            return yeniVec;
        }*/

        vector<int> newVec;
        deque<int> q;  // max queue

        for (int i = 0; i < nums.size(); ++i) {
            while (!q.empty() && q.back() < nums[i])
                q.pop_back();
            q.push_back(nums[i]);
            if (i >= k && nums[i - k] == q.front())  // out of bound
                q.pop_front();
            if (i >= k - 1)
                newVec.push_back(q.front());
        }

        return newVec;


        /*
        priority_queue<pair<int, int>>pq;
        vector<int>ans;
        int n = nums.size();

        for (int i = 0; i < n; i++) {
            if (i == k)
                ans.push_back(pq.top().first);
            pq.push({ nums[i],i });

            if (k == n && i == n - 1)
                ans.push_back(pq.top().first);
            if (i < k)
                continue;

            while (pq.top().second < i - k + 1) {
                pq.pop();
            }
            ans.push_back(pq.top().first);
        }

        return ans;
        */
    }
};


/// <summary>
/// Vector elemanlarýný console'da göster
/// </summary>
/// <typeparam name="T">Vector türü</typeparam>
/// <param name="vec">Parametre olarak gelen vector</param>
template<typename T>
void printVector(const vector<T>& vec) {
    for (auto& i : vec) {
        cout << i << ", ";
    }
    cout << endl;
}