#include "RB_tree.h"
#include <iostream>
#include <vector>

TreeNode* RB_Tree::find(int x, bool ins) {
	TreeNode* tmp = root;
	
	bool right;

	if (x > tmp->key) {
		right = true;
	}
	else {
		right = false;
	}

	while (true) {
		if (((tmp->key > x) || (tmp->right == nullptr)) && right) {
			if (tmp->left != nullptr) {
				if (tmp->left->key > x) {
					right = !right;
				}
				right = false;
			}
			else {
				break;
			}
		}
		else if (((tmp->key < x) || (tmp->left == nullptr)) && !right) {
			if (tmp->right != nullptr) {
				if (tmp->right->key < x) {
					right = !right;
				}
				right = true;
			}
			else {
				break;
			}
		}

		if (right) {
			tmp = tmp->right;
		}
		else {
			tmp = tmp->left;
		}
	}

	if (ins) {
		return tmp;
	}
	else {
		if (tmp->parent->key == x) {
			return tmp->parent;
		}
		else {
			return nullptr;
		}
	}
}

void RB_Tree::insert(int x)
{
	if (root == nullptr) {
		root = new TreeNode{ Color::BLACK, x };

		return;
	}

	TreeNode* tmp = SubInsert(x);

	TwoRedElementsCase(tmp);
}

void RB_Tree::erase(int x)
{
	if (!root) {
		return;
	}

	TreeNode* tmp = root;
	while (tmp) {
		if (x < tmp->key) {
			tmp = tmp->left;
		}
		else if (x > tmp->key) {
			tmp = tmp->right;
		}
		else {
			break;
		}
	}

	if (!tmp) {
		return;
	}

	if (!tmp->left && !tmp->right) {
		if (tmp->parent) {
			if (x < tmp->parent->key) {
				tmp->parent->left = nullptr;
			}
			else {
				tmp->parent->right = nullptr;
			}
		}
	}
	else if (tmp->left && !tmp->right) {
		tmp->parent->left = tmp->left;
		tmp->left->parent = tmp->parent;
		tmp->left->color = BLACK;
	}
	else if (!tmp->left && tmp->right) {
		tmp->parent->right = tmp->right;
		tmp->right->parent = tmp->parent;
		tmp->right->color = BLACK;
	}
	else {
		TreeNode* bufferTmp = tmp;

		tmp = tmp->left;
		while (tmp->right) {
			tmp = tmp->right;
		}

		if (tmp->left) {
			tmp->parent->right = tmp->left;
			tmp->left->parent = tmp->parent;
		}

		if (isRightSon(tmp)) {
			tmp->parent->right = nullptr;
		}
		else {
			tmp->parent->left = nullptr;
		}

		if (bufferTmp->parent) {
			tmp->parent = bufferTmp->parent;
			if (isRightSon(bufferTmp)) {
				bufferTmp->parent->right = tmp;
			}
			else {
				bufferTmp->parent->left = tmp;
			}
		}
		else {
			tmp->parent = nullptr;
		}

		tmp->left = bufferTmp->left;
		tmp->right = bufferTmp->right;
		tmp->color = BLACK;

		bufferTmp = nullptr;
	}

	tmp = nullptr;
}

std::vector<InsertedNode> RB_Tree::GetTreeNodes()
{
	std::vector<InsertedNode> tree;
	
	GetTreeNodes_(tree, root);

	return tree;
}

void RB_Tree::GetTreeNodes_(std::vector<InsertedNode> &tree, TreeNode* tree_)
{
	if (!tree_) {
		return;
	}

	InsertedNode res{tree_->color, tree_->key};

	GetTreeNodes_(tree, tree_->left);
	tree.push_back(res);
	GetTreeNodes_(tree, tree_->right);

}

void RB_Tree::RepaintUncleRedCase(TreeNode* tmp, TreeNode* uncle)
{
	tmp = tmp->parent;
	tmp->color = BLACK;

	tmp = tmp->parent;

	uncle->color = BLACK;
	
	if (tmp != root) {
		tmp->color = RED;
		if (tmp && tmp->parent && tmp->color == RED && tmp->parent->color == RED) {
			TwoRedElementsCase(tmp);
		}
	}
}

void RB_Tree::RepaintUncleBlackCase(TreeNode* tmp)
{
	if (isRightSon(tmp) && !isRightSon(tmp->parent)) {
		LeftRightRotate(tmp);
		tmp = tmp->left;
	}
	else if (!isRightSon(tmp) && isRightSon(tmp->parent)) {
		RightLeftRotate(tmp);

		tmp = tmp->right;
	}

	if (isRightSon(tmp)) {
		TreeNode* grandgrand = tmp->parent->parent->parent;
		bool rightSon;
		if (grandgrand) {
			rightSon = isRightSon(tmp->parent->parent);
		}

		tmp = tmp->parent;

		TreeNode* buffer_son = tmp->left;

		tmp->color = BLACK;
		tmp->right->color = RED;
		tmp->parent->left->color = BLACK;

		if (tmp->parent == root) {
			root = tmp;
		}

		tmp->left = tmp->parent;
		tmp->left->parent = tmp;
		tmp->left->color = RED;

		if (grandgrand) {
			if (rightSon) {
				grandgrand->right = tmp;
			}
			else {
				grandgrand->left = tmp;
			}
			tmp->parent = grandgrand;
		}
		else {
			tmp->parent = nullptr;
		}

		if (buffer_son) {
			tmp = tmp->left;

			
			tmp->right = buffer_son;
			tmp->right->parent = tmp;

			tmp->right->color = BLACK;
		}
	}
	else {
		TreeNode* grandgrand = tmp->parent->parent->parent;
		bool rightSon;
		if (grandgrand) {
			rightSon = isRightSon(tmp->parent->parent);
		}

		tmp = tmp->parent;

		TreeNode* buffer_son = tmp->right;

		tmp->color = BLACK;
		tmp->left->color = RED;
		tmp->parent->right->color = BLACK;

		if (tmp->parent == root) {
			root = tmp;
		}

		tmp->right = tmp->parent;
		tmp->right->parent = tmp;
		tmp->right->color = RED;

		if (grandgrand) {
			if (rightSon) {
				grandgrand->right = tmp;
			}
			else {
				grandgrand->left = tmp;
			}
			tmp->parent = grandgrand;
		}
		else {
			tmp->parent = nullptr;
		}

		if (buffer_son) {
			tmp = tmp->right;
			
			tmp->left = buffer_son;
			tmp->left->parent = tmp;

			tmp->left->color = BLACK;
		}
	}
}

TreeNode* RB_Tree::SubInsert(int x)
{
	TreeNode* tmp = root;

	while (tmp) {
		if (x < tmp->key) {
			if (tmp->left) {
				tmp = tmp->left;
			}
			else {
				tmp->left = new TreeNode{ Color::RED, x };
				tmp->left->parent = tmp;
				tmp = tmp->left;
				return tmp;
			}
		}
		else {
			if (tmp->right) {
				tmp = tmp->right;
			}
			else {
				tmp->right = new TreeNode{ Color::RED, x };
				tmp->right->parent = tmp;
				tmp = tmp->right;
				return tmp;
			}
		}
	}
	return tmp;
}

bool RB_Tree::isRightSon(TreeNode* tmp)
{
	return tmp && tmp->parent->right == tmp;
}

void RB_Tree::rotate(TreeNode* tmp) { // Изменить название функции
	TreeNode* grand = tmp->parent->parent;
	TreeNode* grandgrand = nullptr;
	if (grand) {
		grandgrand = grand->parent;
	}
	bool rightSon;

	if (grandgrand) { 
		rightSon = isRightSon(grand);
	}

	if (grand == root) {
		root = tmp->parent;
	}

	if (isRightSon(tmp->parent)) {
		grand->right = tmp->parent->left;
		grand->color = RED;

		tmp->parent->left = grand;

		tmp->parent->left->parent = tmp->parent;
	}
	else {
		grand->left = tmp->parent->right;
		grand->color = RED;

		tmp->parent->right = grand;

		tmp->parent->right->parent = tmp->parent;
	}

	if (grandgrand) {
		if (rightSon) {
			grandgrand->right = tmp->parent;
		}
		else {
			grandgrand->left = tmp->parent;
		}
	}

	tmp->parent->parent = grandgrand;

	tmp->parent->color = BLACK;
}

void RB_Tree::TwoRedElementsCase(TreeNode* tmp) { // Изменить название фукнции
	if (tmp->color == RED && tmp->parent->color == RED) {
		TreeNode* grand = tmp->parent->parent;
		TreeNode* uncle = nullptr;
		if (isRightSon(tmp->parent)) {
			uncle = grand->left;
		}
		else {
			uncle = grand->right;
		}

		if (uncle) {
			if (uncle->color == RED) {
				RepaintUncleRedCase(tmp, uncle);
			}
			else if (uncle->color == BLACK) {
				RepaintUncleBlackCase(tmp);
			}
		}
		else {
			if (isRightSon(tmp) && !isRightSon(tmp->parent)) { // Проверить на дубляцию кода, в большой поворот входят маленькие
				LeftRightRotate(tmp);
				tmp = tmp->left;
			}
			else if (!isRightSon(tmp) && isRightSon(tmp->parent)) {
				RightLeftRotate(tmp);
				tmp = tmp->right;
			}
			rotate(tmp);
		}
	}
}

void RB_Tree::LeftRightRotate(TreeNode* tmp)
{
	if (tmp->left) {
		tmp->parent->right = tmp->left;
		tmp->left->parent = tmp->parent;
	}
	else {
		tmp->parent->right = nullptr;
	}
	tmp->left = tmp->parent;
	tmp->parent = tmp->parent->parent;
	tmp->left->parent = tmp;
	if (tmp->key >= tmp->parent->key) {
		tmp->parent->right = tmp;
	}
	else {
		tmp->parent->left = tmp;
	}
}

void RB_Tree::RightLeftRotate(TreeNode* tmp)
{
	if (tmp->right) {
		tmp->parent->left = tmp->right;
		tmp->right->parent = tmp->parent;
	}
	else {
		tmp->parent->left = nullptr;
	}
	tmp->right = tmp->parent;
	tmp->parent = tmp->parent->parent;
	tmp->right->parent = tmp;
	if (tmp->key >= tmp->parent->key) {
		tmp->parent->right = tmp;
	}
	else {
		tmp->parent->left = tmp;
	}
}
