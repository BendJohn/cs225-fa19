

/**
 * @file heap.cpp
 * Implementation of a heap class.
 */


template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    // @TODO Update to return the index you are choosing to be your root.
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the left child.
    return currentIdx*2;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the right child.
    return currentIdx*2 + 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    // @TODO Update to return the index of the parent.
    return currentIdx / 2;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    // @TODO Update to return whether the given node has a child
    return currentIdx*2 < _elems.size();
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the child with highest priority
    ///   as defined by higherPriority()

    if (rightChild(currentIdx) < _elems.size()) {
	return higherPriority(_elems[leftChild(currentIdx)],_elems[rightChild(currentIdx)]) ? leftChild(currentIdx)
		: rightChild(currentIdx);
    }
    return leftChild(currentIdx);
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    // @TODO Implement the heapifyDown algorithm.
    size_t highest = currentIdx;
    size_t left = leftChild(currentIdx);
    size_t right = rightChild(currentIdx);

    if (left < _elems.size()) {
	highest = higherPriority(_elems[left], _elems[highest]) ? left : highest;
    }
    if (right < _elems.size()) {
	highest = higherPriority(_elems[right], _elems[highest]) ? right : highest;
    }
    if (highest != currentIdx) {
	std::swap(_elems[highest], _elems[currentIdx]);
	heapifyDown(highest);
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    size_t parent = currentIdx / 2;
    if (currentIdx != root() && higherPriority(_elems[currentIdx], _elems[parent])) {
	std::swap(_elems[currentIdx], _elems[parent]);
	heapifyUp(parent);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    // @TODO Depending on your implementation, this function may or may
    ///   not need modifying
    _elems.push_back(T());
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems) 
{
    // @TODO Construct a heap using the buildHeap algorithm
    _elems.push_back(T());
    for (unsigned i = 0; i < elems.size(); i++) {
      _elems.push_back(elems[i]);
    }
    for (unsigned j = parent(_elems.size()-1); j > 0; j--) {
      heapifyDown(j);
    }
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    // @TODO Remove, and return, the element with highest priority
    T toReturn = _elems[1];
    _elems[1] = _elems[_elems.size()-1];
    _elems.pop_back();
    heapifyDown(1);
    return toReturn;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    // @TODO Return, but do not remove, the element with highest priority
    return _elems[1];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    // @TODO Add elem to the heap
    _elems.push_back(elem);
    heapifyUp(_elems.size()-1);
}

template <class T, class Compare>
void heap<T, Compare>::updateElem(const size_t & idx, const T& elem)
{
    // @TODO In-place updates the value stored in the heap array at idx
    // Corrects the heap to remain as a valid heap even after update
    _elems[idx] = elem;
    heapifyUp(idx);
    heapifyDown(idx);
}


template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    // @TODO Determine if the heap is empty
    return _elems.size() < 2;
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}
