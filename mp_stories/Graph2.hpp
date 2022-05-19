#include <queue>
#include <algorithm>
#include <string>
#include <list>

/**
 * Returns an std::list of vertex keys that creates any shortest path between `start` and `end`.
 *
 * This list MUST include the key of the `start` vertex as the first vertex in the list, the key of
 * the `end` vertex as the last element in the list, and an ordered list of all vertices that must
 * be traveled along the shortest path.
 * 
 * For example, the path a -> c -> e returns a list with three elements: "a", "c", "e".
 * 
 * You should use undirected edges. Hint: There are no edge weights in the Graph.
 *
 * @param start The key for the starting vertex.
 * @param end   The key for the ending vertex.
 */
template <class V, class E>
std::list<std::string> Graph<V,E>::shortestPath(const std::string start, const std::string end) {
  // TODO: Part 3
  std::list<std::string> path;

  /* BFS Algorithm */
  // Use a queue to keep track of what node to visit next
  // Use a map to keep track of visited and the parent
  std::queue<std::string> nodes;
  std::unordered_map<std::string, std::string> pars;

  // Add start to our variables
  nodes.push(start);
  pars.insert({start, ""});

  // Loop through vertices till destination is found
  while (!nodes.empty()) {
	// Get edges of current node
	std::string cur = nodes.front();
	nodes.pop();
	std::list<E_byRef> edges = incidentEdges(cur);
	// Loop through edges and add vertices to queue
	for (E_byRef e : edges) {
		/*--------------- Check out source --------------*/
		std::string adj_node = e.get().source().key();
		// If not visited...
		// Add it as visited to pars
		// Add it to queue
		if (pars.find(adj_node) == pars.end()) {
			pars.insert({adj_node, cur});
			nodes.push(adj_node);

			// If it's the end, we're done :)
			if (adj_node == end) {
				nodes = std::queue<std::string>();
				break;
			}
		}
		/*--------------- Check out dest --------------*/
		adj_node = e.get().dest().key();
		// If not visited...
		// Add it as visited to pars
		// Add it to queue
		if (pars.find(adj_node) == pars.end()) {
			pars.insert({adj_node, cur});
			nodes.push(adj_node);

			// If it's the end, we're done :)
			if (adj_node == end) {
				nodes = std::queue<std::string>();
				break;
			}
		}
	}
  }

  // Create path by backtracking
  std::string cur_end = end;
  while (cur_end != "") {
	path.push_front(cur_end);
	cur_end = pars.at(cur_end);
  }
  return path;
}
