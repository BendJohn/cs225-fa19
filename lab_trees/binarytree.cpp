/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "TreeTraversals/InorderTraversal.h"
#include <iostream>

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + std::max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    std::cout << std::endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    std::cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
    //your code here
    mirror(root);
}

template <typename T>
// typename BinaryTree<T>::Node*
void BinaryTree<T>::mirror(Node* subRoot) {
	// Base case - null node
	if (subRoot == nullptr) {
		return;
	}

	// swap every node left and right;
	mirror(subRoot->left);
	mirror(subRoot->right);
	Node* tempptr = subRoot->left;
	subRoot->left = subRoot->right;
	subRoot->right = tempptr;
}

/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{
    // your code here
    if (!root) { return true; }

    InorderTraversal<int> itr (root);
    int prev = (*itr.begin())->elem;
    for (Node* i : itr) {
	if (i->elem < prev) { return false; }
	prev = i->elem;
    }
      
    return true;
}

/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{
    // your code here
    return isOrderedRecursive(root, INT_MIN, INT_MAX);
}

template <typename T>
bool BinaryTree<T>::isOrderedRecursive(Node* subRoot, int min, int max) const {
    // Used BST algorithm from geeksforgeeks
    if (!subRoot) {
	return true;
    }
    if (subRoot->elem < min || subRoot->elem > max) {
	return false;
    }
    return isOrderedRecursive(subRoot->left, min, subRoot->elem - 1) && isOrderedRecursive(subRoot->right, subRoot->elem + 1, max);
}

/**
 * creates vectors of all the possible paths from the root of the tree to any leaf
 * node and adds it to another vector.
 * Path is, all sequences starting at the root node and continuing
 * downwards, ending at a leaf node. Paths ending in a left node should be
 * added before paths ending in a node further to the right.
 * @param paths vector of vectors that contains path of nodes
 */
template <typename T>
void BinaryTree<T>::getPaths(std::vector<std::vector<T>>& paths) const
{
    // your code here
    paths.clear();
    std::vector<T> vect;
    getPaths(root, vect, paths);
}

template <typename T>
void BinaryTree<T>::getPaths(Node* subRoot, std::vector<T> curr_path, std::vector<std::vector<T>>& paths) const {
	if (!subRoot) {
		return;
	}
	if (!subRoot->left && !subRoot->right) {
		curr_path.push_back(subRoot->elem);
		paths.push_back(curr_path);
		return;
	}
	curr_path.push_back(subRoot->elem);
	getPaths(subRoot->left, curr_path, paths);
	getPaths(subRoot->right, curr_path, paths);
}

/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{
    // your code here
    int sum = 0;
    return sumDistances(root, 0, sum);
}

template <typename T>
int BinaryTree<T>::sumDistances(Node* subRoot, int dist, int & sumDist) const {
    if (!subRoot) {
	return sumDist;
    }
    if (subRoot->left) {
	sumDist += dist + 1;
	sumDistances(subRoot->left, dist + 1, sumDist);
    }
    if (subRoot->right) {
	sumDist += dist + 1;
	sumDistances(subRoot->right, dist + 1, sumDist);
    }
    return sumDist;
}
