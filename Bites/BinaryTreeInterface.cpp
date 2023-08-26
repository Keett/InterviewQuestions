#include "BinaryTreeInterface.h"
#include <queue>

using namespace std;

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



