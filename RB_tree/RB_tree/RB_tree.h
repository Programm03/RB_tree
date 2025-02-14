#pragma once
#include <vector>

enum Color {
	RED,
	BLACK
};

struct TreeNode {
	Color color = Color::RED;
	int key = 0;
	TreeNode* left = nullptr;
	TreeNode* right = nullptr;
	TreeNode* parent = nullptr;
};

struct InsertedNode {
	Color color = Color::RED;
	int key = 0;

	bool operator== (const InsertedNode &node)const {
		return node.color == color && node.key == key;
	}
};


class RB_Tree {
public:
	TreeNode* find(int x, bool ins=false);
	void insert(int x);
	void erase(int x);
	std::vector<InsertedNode> GetTreeNodes();
private:
	TreeNode* root = nullptr;
	void GetTreeNodes_(std::vector<InsertedNode> &tree, TreeNode* tree_);
	void RepaintUncleRedCase(TreeNode* tmp, TreeNode* uncle);
	void RepaintUncleBlackCase(TreeNode* tmp);
	TreeNode* SubInsert(int x);
	bool isRightSon(TreeNode* tmp);
	void rotate(TreeNode* tmp);
	void TwoRedElementsCase(TreeNode* tree);
	void LeftRightRotate(TreeNode* tmp);
	void RightLeftRotate(TreeNode* tmp);
};