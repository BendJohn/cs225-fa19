/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { 
  // @done: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @done: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @done: graded in MP3.1
  return List<T>::ListIterator(tail_->next);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @done Graded in MP3.1
  ListNode* after = NULL;
  ListNode* curr = head_;
  while (curr != NULL) {
	after = curr->next;
	delete curr;
	curr = after;
  }
  head_ = NULL;
  tail_ = NULL;
  length_ = 0;
}  

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @done Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = head_;
  newNode -> prev = NULL;
  
  if (head_ != NULL) {
    head_ -> prev = newNode;
  }
  if (tail_ == NULL) {
    head_ = newNode;
    tail_ = newNode;
  }
  
  head_ = newNode;
  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @done Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = NULL;
  newNode -> prev = tail_;
  
  if (tail_ != NULL) {
    tail_ -> next = newNode;
  }
  if (tail_ == NULL) {
    head_ = newNode;
    tail_ = newNode;
  }
  
  tail_ = newNode;
  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @TODO Graded in MP3.1
  ListNode * curr = start;

  for (int i = 0; i < splitPoint && curr; i++) {
    curr = curr->next;
  }

  if (curr) {
    if (curr->prev) {
      curr->prev->next = NULL;
    }
      curr->prev = NULL;
  }

  return curr;
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {
  /// @done Graded in MP3.1
  int counter = 0;
  ListNode* curr = head_;
  while (curr->next != NULL) {
	if (counter%2 == 1) {
		ListNode* temp = curr->prev;
		temp->next = curr->next;
		curr->next->prev = temp;
		tail_->next = curr;
		curr->prev = tail_;
		curr->next = NULL;
		tail_ = curr;
		curr = temp;
	}
	counter++;
	curr = curr->next;
  }
}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @TODO Graded in MP3.2
  ListNode* prv = endPoint->next;
  ListNode* curr = startPoint;
  ListNode* nxt = curr->next;
  ListNode* tmp = startPoint->prev;
  while (nxt != endPoint->next) {
	curr->next = prv;
	curr->prev = nxt;
	prv = curr;
	curr = nxt;
	nxt = curr->next;
  }
  curr->next = prv;
  curr->prev = tmp;
  endPoint = startPoint;
  startPoint = curr;
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @TODO Graded in MP3.2
  if (n >= length_) {
	reverse();
	return;
  }

  ListNode* end = nullptr;
  ListNode* curr = head_;
  ListNode* start = head_;
  int count = 1;

  while (curr) {
	if (count == n || !curr->next) {
		end = curr;
		curr = curr->next;

		if (start == head_) { reverse(head_, end); }
		if (end == tail_) { reverse(start, tail_); }
		else { reverse(start, end); }

		if (curr) { curr->prev = end; }
		if (start->prev) { start->prev->next = start; }

		start = curr;
		count = 1;
		continue;
	}
	curr = curr->next;
	count++;
  }
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @TODO Graded in MP3.2
  ListNode* ret;
  ListNode* fptr = first;
  ListNode* sptr = second;

  // Dealing with nulls
  if (!first) { ret = second; }
  if (!second) { ret = first; }

  // Find return head
  if (fptr->data < sptr->data) { ret = fptr; }
  else { ret = sptr; }

  while (sptr) {
	if (!fptr->next && fptr->data < sptr->data) {
		
		sptr->prev = fptr;
		fptr->next = sptr;
		break;
	}
	else if (!(fptr->data < sptr->data)) {
		ListNode* snxt = sptr->next;

		sptr->prev = fptr->prev;
		if (fptr->prev) {
			fptr->prev->next = sptr;
		}
		sptr->next = fptr;
		fptr->prev = sptr;

		// Next vals
		sptr = snxt;
	} else {
		fptr = fptr->next;
	}
  }

  first = ret;
  second = nullptr;

  return ret;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @TODO Graded in MP3.2
  // Need at least two nodes to split.
  if (start->next == nullptr) { return start; }
  ListNode* start2 = split(start, chainLength / 2);

  ListNode* ret = merge(mergesort(start, chainLength / 2), mergesort(start2, (chainLength / 2) + (chainLength % 2)));
  return ret;
}
