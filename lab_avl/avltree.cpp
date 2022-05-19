/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include <iostream>

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node* rootRight = t->right;
    t->right = rootRight->left;
    rootRight->left = t;
    t = rootRight;
    // update heights
    rootRight = t->left;
    rootRight->height = std::max(heightOrNeg1(rootRight->left), heightOrNeg1(rootRight->right)) + 1;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node* rootLeft = t->left;
    t->left = rootLeft->right;
    rootLeft->right = t;
    t = rootLeft;
    // update heights
    rootLeft = t->right;
    rootLeft->height = std::max(heightOrNeg1(rootLeft->left), heightOrNeg1(rootLeft->right)) + 1;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    // Find the balance of the subtree and the subtree->left and subtree->right
    int heightLeft = heightOrNeg1(subtree->left);
    int heightRight = heightOrNeg1(subtree->right);

    int subtreeBalance = heightRight - heightLeft;
    int leftBalance = 0;
    int rightBalance = 0;

    if (subtree->left) {
	heightLeft = heightOrNeg1(subtree->left->left);
	heightRight = heightOrNeg1(subtree->left->right);
	leftBalance = heightRight - heightLeft;
    }
    if (subtree->right) {
	heightLeft = heightOrNeg1(subtree->right->left);
	heightRight = heightOrNeg1(subtree->right->right);
	rightBalance = heightRight - heightLeft;
    }
    // check right elbow, left elbow, left stick and right stick
    if (subtreeBalance == 2 && rightBalance < 0) {
	rotateRightLeft(subtree);
    } else if (subtreeBalance == -2 && leftBalance > 0) {
	rotateLeftRight(subtree);
    } else if (subtreeBalance == 2) {
	rotateLeft(subtree);
    } else if (subtreeBalance == -2) {
	rotateRight(subtree);
    }

    // Update height
    subtree->height = std::max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right)) + 1;
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if (!subtree) {
	subtree = new Node (key, value);
    } else if (subtree->key > key) {
	insert(subtree->left, key, value);
    } else if (subtree->key < key) {
	insert(subtree->right, key, value);
    } else {
	subtree->value = value;
	return;
    }

    rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
	    subtree = nullptr;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node* toSwap = subtree->left;
	    while (toSwap->right) {
		toSwap = toSwap->right;
	    }
	    swap(toSwap, subtree);
	    remove(subtree->left, key);
        } else {
            /* one-child remove */
            // your code here
            Node* temp;
            if (subtree->left) {
		temp = subtree->left;
	    } else {
		temp = subtree->right;
	    }
	    delete subtree;
	    subtree = temp;
        }
    }

    // your code here
    if (subtree) {
    	rebalance(subtree);
    }
}
