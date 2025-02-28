#include "RB_tree.h"
#include <iostream>
#include <vector>

TreeNode* RB_Tree::find(int x, bool ins=false) {
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

	if (!tmp->left && !tmp->right && tmp->color == RED && tmp->parent) { // Совместить условие с условием ниже
		if (x < tmp->parent->key) {
			tmp->parent->left = nullptr;
		}
		else {
			tmp->parent->right = nullptr;
		}
	}
	else if (!tmp->left && !tmp->right && tmp->color == BLACK && tmp->parent) {
		if (isRightSon(tmp)) {

		}
		else {
			if (tmp->parent->right->color == BLACK) {
				TreeNode* brother = tmp->parent->right;
				if (brother->right->color == RED || brother->left->color == RED);
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
		TreeNode* replaceElement = tmp; // tmp в этой фунции был удаляемым элементом, в этом моменте он стал шагаемым.
		// Изменить переменные tmp и buffertmp в этом случае.
		// Переименовать tmp и bufferTmp

		replaceElement = replaceElement->left;
		while (replaceElement->right) {
			replaceElement = replaceElement->right;
		}

		if (replaceElement->left) {
			replaceElement->parent->right = replaceElement->left;
			replaceElement->left->parent = replaceElement->parent;
		}

		if (isRightSon(replaceElement)) { // Лишнее дейтвие, логично что это правый сын
			replaceElement->parent->right = nullptr;
		}
		else {
			replaceElement->parent->left = nullptr;
		}

		if (tmp->parent) {
			replaceElement->parent = tmp->parent;
			if (isRightSon(tmp)) {
				tmp->parent->right = replaceElement;
			}
			else {
				tmp->parent->left = replaceElement;
			}
		}
		else {
			replaceElement->parent = nullptr;
		}

		replaceElement->left = tmp->left;
		replaceElement->right = tmp->right;
		replaceElement->color = BLACK;
	}

	delete tmp;
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
