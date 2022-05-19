/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */

    // Tasty looking ternary structures:
    return first[curDim] == second[curDim] ? first < second : first[curDim] < second[curDim];
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    double sum_best = 0;
    double sum_potential = 0;

    for (int i = 0; i < Dim; i++) {
	sum_best += (currentBest[i] - target[i]) * (currentBest[i] - target[i]);
	sum_potential += (potential[i] - target[i]) * (potential[i] - target[i]);
    }

    return sum_potential < sum_best;
}

template <int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>>& points, int start, int end, int dim) {
    // Set pivot randomly to the last value
    Point<Dim> pivot = points[end];

    // Iterate from start to end and place the
    // point at the start index if its smaller
    for (int i = start; i < end; i++) {
	if (smallerDimVal(points[i], pivot, dim)) {
		std::swap(points[start], points[i]);
		start++;
	}
    }

    // Swap the pivot to the correct i+1 spot
    // and return that value
    std::swap(points[start], points[end]);
    return start;
}

template <int Dim>
Point<Dim> KDTree<Dim>::kthSmallest(vector<Point<Dim>>& points, int start, int end, int dim, int k) {
    while (start <= end) {
	// Partition around pivot
	int pivot = partition(points, start, end, dim);

	// If pivot is kth smallest element, return!
	if (pivot == k) { return points[k]; }

	// If pivot index is greater than k,
	// the k must be on the left side
	if (pivot > k) { end = pivot - 1; }

	// If pivot index is less than k,
	// the k must be on the right side
	else { start = pivot + 1; }
    }
    // To please the c++ gods
    return points[0];
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::createTree(vector<Point<Dim>>& points, int start, int end, int dim) {
    // Base Case
    if (end < start || (unsigned) end >= points.size() || start < 0) {
	return nullptr;
    }

    // Find the median along the dimension
    // Place median at midpoint
    int midIndex = (end + start) / 2;
    Point<Dim> median = kthSmallest(points, start, end, dim, midIndex);

    // Add middle node as return Node
    // Increment corresponding variables
    KDTreeNode* retNode = new KDTreeNode(median);
    size++;
    dim = (dim + 1) % Dim;

    // Create left and right child
    // Recurse on start to (m-1) and (m+1) to end
    retNode->left = createTree(points, start, midIndex - 1, dim);
    retNode->right = createTree(points, midIndex + 1, end, dim);

    // Finally return the node
    return retNode;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */

    // Set variables
    size = 0;
    root = nullptr;

    // If newPoints is empty, you're done!
    if (newPoints.empty()) { return; };

    // Otherwise call createTree, copy newPoints (since its const)
    vector<Point<Dim>> points = newPoints;
    root = createTree(points, 0, points.size()-1, 0);
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::treeCreate(const KDTreeNode& other) const {
  KDTreeNode* newNode = new KDTreeNode(other.point);
  if (other.left) {
    newNode->left = treeCreate(other.left);
  }
  if (other.right) {
    newNode->right = treeCreate(other.right);
  }
  return newNode;
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  if (!other.root) {
     size = other.size;
     return;
   }
   root = new KDTreeNode(other.root.point);
   if (other.root.left) {
     root->left = treeCreate(other.root.left);
   }
   if (other.root.right) {
     root->right = treeCreate(other.root.right);
   }
   size = other.size;
}

template <int Dim>
void KDTree<Dim>::clear(KDTreeNode* subroot) {
   if (subroot) {
	clear(subroot->left);
	clear(subroot->right);
	delete subroot;
   }
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  // Check if the other is the same
  if (&rhs == this) {
	return;
  }
  clear(root);

  if (!rhs.root) {
     size = rhs.size;
     return;
  }
  root = new KDTreeNode(rhs.root.point);
  if (rhs.root.left) {
    root->left = treeCreate(rhs.root.left);
  }
  if (rhs.root.right) {
    root->right = treeCreate(rhs.root.right);
  }
  size = rhs.size;
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  clear(root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(KDTreeNode* subroot, Point<Dim> query, int dim) const {
   // goLeft is true when the recurse step should go left
   // (aka it goes right the first time)
   Point<Dim> currentBest;
   bool goLeft = false;

   // Base Case -- if you're at a leaf node its the current best
   // Don't return it just yet, we have to backtrack
   if (!subroot->left && !subroot->right) {
	return subroot->point;
   // If left doesn't exist go right
   } else if (!subroot->left || smallerDimVal(subroot->point, query, dim)) {
	goLeft = true;
	currentBest = findNearestNeighbor(subroot->right, query, (dim+1)%Dim);
   // Otherwise go left
   } else {
	currentBest = findNearestNeighbor(subroot->left, query, (dim+1)%Dim);
   }

   /** ============ Time for backtracking ============ */
   Point<Dim> possibleBest;
   // The current root is better so update best
   if (shouldReplace(query, currentBest, subroot->point)) {
	currentBest = subroot->point;
   }

   // Recurse down subtree iff distance to (split pane)**2 < (current radius)**2
   // splitPane is a point on the splitPane of the current subroot
   Point<Dim> splitPane = query;
   splitPane[dim] = subroot->point[dim];
   if (shouldReplace(query, currentBest, splitPane) || !shouldReplace(query, splitPane, currentBest)) {
	possibleBest = goLeft ?
		(subroot->left ?
			findNearestNeighbor(subroot->left, query, (dim+1)%Dim)
			: currentBest)
		:  (subroot->right ?
			findNearestNeighbor(subroot->right, query, (dim+1)%Dim)
			: currentBest);

	// Update current best based on possible best
	if (shouldReplace(query, currentBest, possibleBest) == shouldReplace(query, possibleBest, currentBest)) {
		currentBest = possibleBest < currentBest ? possibleBest : currentBest;
	}
	currentBest = shouldReplace(query, currentBest, possibleBest) ? possibleBest : currentBest;
   }
   return currentBest;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
	if (!root) {
		std::cout << "Wait a minute... root doesn't exit!?" << std::endl;
	}
    return root ? findNearestNeighbor(root, query, 0) : Point<Dim>();
}

