/* Your code here! */
#include "dsets.h"

void DisjointSets::addelements(int num) {
	// Pushing back num uptrees
	for (int i = 0; i < num; i++) {
		nodes.push_back(-1);
	}
}

int DisjointSets::find(int elem) {
	// If nodes[elem] < 0, we've found the root!
	if (nodes[elem] < 0) {
		return elem;
	}
	// Otherwise recursively call
	nodes[elem] = find(nodes[elem]);
	return nodes[elem];
}

void DisjointSets::setunion(int a, int b) {
	// Find roots of a and b
	int root_a = find(a);
	int root_b = find(b);

	// If roots are the same, don't do nuthin'
	if (root_a == root_b) {
		return;
	}

	// If the two sets are the same size,
	// make the tree containing the second argument
	// point to the tree containing the first.
	if (nodes[root_a] <= nodes[root_b]) {
		nodes[root_a] += nodes[root_b];
		nodes[root_b] = root_a;
	} else {
		nodes[root_b] += nodes[root_a];
		nodes[root_a] = root_b;
	}
}

int DisjointSets::size(int elem) {
	return -1 * nodes[find(elem)];
}
