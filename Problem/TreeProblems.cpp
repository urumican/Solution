#include <iostream>
#include <algorithm>
#include "my_tree.h"

using namespace std;

/* data structure for maximum BST subtree.  */
struct MaxBSTRes {
	bool isBST;
	int maxVal, minVal, numOfNode, globalMax;
	MaxBSTRes(bool x = false) {
		isBST = x;
		maxVal = INT_MIN;
		minVal = INT_MAX;
		numOfNode = 0;
		globalMax = 0;
	}
};

/* Data structure for Lowest common accestor */
struct LCARes {
	int numOfNodeFound;
	TreeNode* res;
	LCARes(int numOfNodeFound, TreeNode* res) {
		this->numOfNodeFound = numOfNodeFound;
		this->res = res;
	}
};

class TreeProblem {
public:
	int largestSubBST(TreeNode* root) {
		if (root == NULL) {
			return 0;
		}

		int start = 0;
		MaxBSTRes res = dfsLargestBST(root, &start);

		return res.numOfNode;
	}

	TreeNode* findLCAinBT(TreeNode* root, TreeNode* p, TreeNode* q) {
		return findLCA(root, p, q).res;
	}

private:
	
	/* Postorder traversal */
	LCARes findLCA(TreeNode* root, TreeNode* p, TreeNode* q) {
		if (root == NULL) {
			LCARes res(NULL, 0);
			return res;
		}

		LCARes left = findLCA(root->left, p, q);
		if (left.numOfNodeFound == 2) {
			return left;
		}

		LCARes right = findLCA(root->right, p, q);
		if (right.numOfNodeFound == 2) {
			return right;
		}

		int numOfNodesFound = left.numOfNodeFound + right.numOfNodeFound + ((root == p || root == q) ? 1 : 0);
		LCARes res(numOfNodesFound, (left.numOfNodeFound == 1 && right.numOfNodeFound == 1 ? root : NULL));

		return res;
	}

	MaxBSTRes dfsLargestBST(TreeNode* root, int* curMax) {
		if (root != NULL) {
			MaxBSTRes res(true);
			return res;
		}

		MaxBSTRes left = dfsLargestBST(root->left, curMax); 
		MaxBSTRes right = dfsLargestBST(root->right, curMax); 

		MaxBSTRes res;
		if (left.isBST && right.isBST && left.maxVal < root->val && right.minVal >= root->val) {
			res.isBST = true;
			res.numOfNode = left.numOfNode + right.numOfNode + 1;
			res.maxVal = right.maxVal;
			res.minVal = left.minVal;
			*curMax = max(*curMax, res.numOfNode);
		}

		return res;
	}
};
