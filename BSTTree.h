#ifndef BSTT
#define BSTT

#include <iostream>
#include <fstream>
#include "Record.h"
#include "Item.h"

using namespace std;

struct TreeNode {
	Item value;

	TreeNode* head;
	TreeNode* left;
	TreeNode* right;

	TreeNode(Item _val) {
		value = _val;
		head = nullptr;
		left = nullptr;
		right = nullptr;
	}

	TreeNode(Item _val, TreeNode* h) {
		value = _val;
		this->head = h;
		left = nullptr;
		right = nullptr;
	}

	bool hasNoChildren() {
		if (this->left == nullptr && this->right == nullptr) return true;
		return false;
	}
};

struct BSTTree {
	TreeNode* root = nullptr;
	Item dflt;

	BSTTree(TreeNode* root = nullptr) {
		this->root = nullptr;
	}

	bool is_empty() {
		return root->hasNoChildren();
	}

	void push(Item _val) {
		if (root == nullptr) {
			TreeNode* firstNode = new TreeNode(_val);
			firstNode->value = _val;
			root = firstNode;
			return;
		}

		TreeNode* currentNode = root;
		while (true)
		{
			if (_val.getKey() >= currentNode->value.getKey()) {
				if (currentNode->right == nullptr) {
					TreeNode* tmp1 = new TreeNode(_val, currentNode);

					currentNode->right = tmp1;
					break;
				}
				else {
					currentNode = currentNode->right;
				}
			}
			else {
				if (currentNode->left == nullptr) {
					TreeNode* tmp2 = new TreeNode(_val, currentNode);

					currentNode->left = tmp2;
					break;
				}
				else {
					currentNode = currentNode->left;
				}
			}
		}
	}

	void print(TreeNode* currentNode, int level) {
		if (currentNode) {
			print(currentNode->right, level + 1);
			for (int i = 0; i < level; i++) cout << "   ";
			cout << currentNode->value.getKey() << endl;
			print(currentNode->left, level + 1);
		}
	}

	// Convert to delete by key
	void deleteByKey(int key) {
		if (!root) return;
		root = deleteNode(root, key);
	}

	TreeNode* deleteNode(TreeNode* currentNode, int key) {
		if (currentNode->value.key == key) {
			if (!currentNode->left && !currentNode->right)
				return nullptr;
			
			if (!currentNode->left)
				return currentNode->right;

			if (!currentNode->right)
				return currentNode->left;

			TreeNode* minNodeInRightSubtree = findMinElement(currentNode->right);
			currentNode->value = minNodeInRightSubtree->value;
			
			currentNode->right = this->deleteNode(currentNode->right, minNodeInRightSubtree->value.key);
			return currentNode;
		}

		if (key < currentNode->value.key) {
			if (!currentNode->left) {
				cout << "No such elem" << endl;
				return currentNode;
			}

			currentNode->left = deleteNode(currentNode->left, key);
			return currentNode;
		}

		if (key > currentNode->value.key) {
			if (!currentNode->right) {
				cout << "No such elem" << endl;
				return currentNode;
			}

			currentNode->right = deleteNode(currentNode->right, key);
			return currentNode;
		}
	}

	TreeNode* findMinElement(TreeNode* node) {
		if (!node->left) return node;
		return findMinElement(node->left);
	}

	TreeNode* getNodeByKey(int key, TreeNode* currentNode) {
		if (!currentNode) return nullptr;
		if (currentNode->value.key == key) return currentNode;
		if (currentNode->value.key > key) getNodeByKey(key, currentNode->left);
		else getNodeByKey(key, currentNode->right);
	}

	Item getItemByKey(int key, TreeNode* currentNode) {
		if (!currentNode) return dflt;
		if (currentNode->value.key == key) return currentNode->value;
		if (currentNode->value.key > key) getItemByKey(key, currentNode->left);
		else getItemByKey(key, currentNode->right);
	}

	void buildTreeFromFile(ifstream& fb) {
		int counter = 0;
		Record x;

		fb.read((char*)&x, sizeof(Record));
		while (!fb.eof())
		{
			Item item(x.numOfTST, counter);
			counter++;

			this->push(item);

			fb.read((char*)&x, sizeof(Record));
		}

		cout << "done" << endl;
	}
};

#endif

