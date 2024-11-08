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
		/*if (tmp->right != nullptr && x > tmp->key) {
			if (tmp->right->key == x) {
				return tmp->right;
			}
		}
		else if (tmp->left != nullptr && x < tmp->key) {
			if (tmp->left->key == x) {
				return tmp->left;
			}
		}*/
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



	if (tmp->color == tmp->parent->color) {
		TreeNode* grand = tmp->parent->parent;
		TreeNode* uncle = nullptr;
		if (!isRightSon(tmp->parent)) {
			uncle = grand->right;
		}
		else {
			uncle = grand->left;
		}

		if (uncle) {
			if (uncle->color == RED) {
				ifUncleRed(tmp, uncle);
			}
			else if (uncle->color == BLACK) {
				ifUncleBlack(tmp);
			}
		}
		else {
			tmp->color = BLACK;
		}
	}
}

void RB_Tree::erase(int x)
{

	if (root->key == x) { // ≈сли пользователь захотел удалить корень
		if (root->right != nullptr) {
			TreeNode* elemR = root->right; // ¬ременный указатель дл€ перемещни€ 
											// правого узла удал€емого корн€
			root = root->left;
			root->right = elemR;

			//delete elemR;
		}
		else if (root->left != nullptr){
			TreeNode* elemL = root->left; // “оже самое, но дл€ левого узла
			root = root->right;
			root->left = elemL; // nullptr exeption
			
			//delete elemL;
		}
		root->parent = nullptr;
		return;
	}

	TreeNode* deleteElement = find(x); // ¬ременна€ переменна€ дл€ удалени€
									   // желаемого узла
	TreeNode* tmp = deleteElement->parent;
	if (deleteElement->key > root->key) {
		if (deleteElement->right == nullptr && deleteElement->left == nullptr) {
			deleteElement = nullptr;
		}
		else if (deleteElement->left != nullptr && deleteElement->right == nullptr){
			deleteElement->parent->left = deleteElement->left;
			deleteElement->left->parent = tmp;
		}
		else if (deleteElement->right != nullptr) {
			deleteElement->parent->right = deleteElement->left;
			deleteElement->right->parent = tmp;
		}
		delete deleteElement;
	}
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

void RB_Tree::ifUncleRed(TreeNode* &tmp, TreeNode* &uncle)
{
	tmp = tmp->parent;
	tmp->color = BLACK;

	tmp = tmp->parent;

	if (tmp != root) {
		tmp->color = RED;
	}

	uncle->color = BLACK;
}

void RB_Tree::ifUncleBlack(TreeNode* &tmp)
{
	if (tmp == tmp->parent->right) {
		TreeNode* bufferParent = tmp->parent->parent;
		TreeNode* buffer = tmp->parent;
		TreeNode* bufferLeft = tmp->parent->left;
		TreeNode* bufferRight = tmp->parent->right;

		tmp->parent = tmp;
		tmp = tmp->parent;

		tmp->parent = bufferParent;
		tmp->left = buffer;
		tmp->left->parent = tmp;
		tmp = tmp->left;
		tmp->left = bufferLeft;
		tmp->right = nullptr;
	}
	if (tmp == tmp->parent->left) {
		tmp = tmp->parent;

		TreeNode* bufferParent = new TreeNode;
		bool parent = false;
		bool leftSon = false;
		bool root_ = false;

		if (tmp->parent->parent) {
			if (tmp->parent->key > tmp->parent->parent->key) {
				leftSon = true;
			}
			else {
				leftSon = false;
			}
			bufferParent = tmp->parent->parent;
			parent = true;
		}
		TreeNode* buffer = tmp->parent;
		TreeNode* bufferRight = tmp->parent->right;

		tmp->parent = nullptr;

		if (tmp->right) {
			while (tmp->right) {
				tmp = tmp->right;
			}
		}

		tmp->right = buffer;
		tmp->right->parent = tmp;
		tmp = tmp->right;
		tmp->left = nullptr;
		tmp->right = bufferRight;

		if (tmp == root) {
			root_ = true;
		}

		while (tmp->parent) {
			tmp = tmp->parent;
		}

		if (parent) {
			tmp->parent = bufferParent;
			if (leftSon) {
				bufferParent->left = tmp;
			}
			else {
				bufferParent->right = tmp;
			}
		}

		tmp->color = BLACK;
		tmp->left->color = RED;
		tmp->right->color = RED;
		tmp->right->right->color = BLACK;

		if (root_) {
			root = tmp;
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
}

bool RB_Tree::isRightSon(TreeNode* tmp)
{
	return tmp && tmp->parent->right == tmp;
}
