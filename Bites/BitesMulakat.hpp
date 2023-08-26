#pragma once
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/// <summary>
/// IMaxNumber interface class
/// </summary>
__interface IMaxNumber {
public:
    vector<int> getSolution(vector<int>& nums, int k) = 0;
};

/// <summary>
/// MaxNumberInterface, IMaxNumber'dan inherite edilmiþtir.
/// Beklenilen çözüm yolu (Soru 1)
/// </summary>
class MaxNumberInterface : public IMaxNumber {
public:
    // Inherited via IMaxNumber
    virtual vector<int> getSolution(vector<int>& nums, int k) override
    {
        vector<int> newVec;
        deque<int> newDeque;

        for (int i = 0; i < nums.size(); ++i) {
            while (!newDeque.empty() && newDeque.back() < nums[i])
                newDeque.pop_back();
            newDeque.push_back(nums[i]);
            if (i >= k && nums[i - k] == newDeque.front())
                newDeque.pop_front();
            if (i >= k - 1)
                newVec.push_back(newDeque.front());
        }
        return newVec;
    }
};

/// <summary>
/// Soru 2 için verilen Node tanýmlamasý
/// </summary>
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

/// <summary>
/// IBinaryTree interface class
/// </summary>
__interface IBinaryTree {
public:
    Node* connect(Node* root) { };
};

/// <summary>
/// BinaryTreeExample, IBinaryTree'den inherite edilmiþtir.
/// Beklenilen çözüm yolu (Soru 2)
/// </summary>
class BinaryTreeExample : public IBinaryTree {
public:
    // Inherited via IBinaryTree
    virtual Node* connect(Node* root) override
    {
        if (root == NULL)
            return NULL;
        if (root->left)
        {
            root->left->next = root->right;
            if (root->next)
            {
                root->right->next = root->next->left;
            }
            connect(root->left);
            connect(root->right);
        }
        return root;     
    }
};

/// <summary>
/// SqrtH class, içinde virtual tanýmlý override edilecek fonksiyon ismini barýndýrmaktadýr.
/// </summary>
class SqrtH {
public:
    virtual int getSolution(int x) = 0;
};

/// <summary>
/// Sqrt, SqrtH class'ýndan inherite edilmiþtir.
/// Beklenilen çözüm yolu (Soru 3)
/// </summary>
class Sqrt : public SqrtH {
public:
    // Inherited via SqrtH
    virtual int getSolution(int x) override
    {
        int front = 2, rear = x, middle;

        if (x <= 1)
            return x;
        while (front <= rear) {
            middle = front + (rear - front) / 2;
            if (middle == x / middle)
                return middle;
            else if (middle < x / middle)
                front = middle + 1;
            else
                rear = middle - 1;
        }
        if (front > x / front)
            return front - 1;

        return front;
    }

};