/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 * stacks and queues portion of the lab.
 */

namespace QuackFun {

/**
 * Sums items in a stack.
 *
 * **Hint**: think recursively!
 *
 * @note You may modify the stack as long as you restore it to its original
 * values.
 *
 * @note You may use only two local variables of type T in your function.
 * Note that this function is templatized on the stack's type, so stacks of
 * objects overloading the + operator can be summed.
 *
 * @note We are using the Standard Template Library (STL) stack in this
 * problem. Its pop function works a bit differently from the stack we
 * built. Try searching for "stl stack" to learn how to use it.
 *
 * @param s A stack holding values to sum.
 * @return  The sum of all the elements in the stack, leaving the original
 *          stack in the same state (unchanged).
 */
template <typename T>
T sum(stack<T>& s)
{

    // Your code here
    T agg = T();
    if (s.size() == 0) {
	return agg;
    }

    T top = s.top();
    s.pop();
    agg = top + sum(s);
    s.push(top);
    return agg; // stub return value (0 for primitive types). Change this!
                // Note: T() is the default value for objects, and 0 for
                // primitive types
}

/**
 * Checks whether the given string (stored in a queue) has balanced brackets.
 * A string will consist of square bracket characters, [, ], and other
 * characters. This function will return true if and only if the square bracket
 * characters in the given string are balanced. For this to be true, all
 * brackets must be matched up correctly, with no extra, hanging, or unmatched
 * brackets. For example, the string "[hello][]" is balanced, "[[][[]a]]" is
 * balanced, "[]]" is unbalanced, "][" is unbalanced, and "))))[cs225]" is
 * balanced.
 *
 * For this function, you may only create a single local variable of type
 * `stack<char>`! No other stack or queue local objects may be declared. Note
 * that you may still declare and use other local variables of primitive types.
 *
 * @param input The queue representation of a string to check for balanced brackets in
 * @return      Whether the input string had balanced brackets
 */
bool isBalanced(queue<char> input)
{

    // @TODO: Make less optimistic
    stack<char> s;
    for (unsigned long i = 0; i < input.size(); i++) {
	char curr = input.front();
	if (curr == '[') {
		s.push(curr);
	}
	if (curr == ']' && s.empty()) {
		return false;
	}
	if (curr == ']') {
		s.pop();
	}
	input.pop();
	input.push(curr);
    }
    return s.empty();
}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 *
 * **Hint**: You'll want to make a local stack variable.
 *
 * @note Any "leftover" numbers should be handled as if their block was
 * complete.
 *
 * @note We are using the Standard Template Library (STL) queue in this
 * problem. Its pop function works a bit differently from the stack we
 * built. Try searching for "stl stack" to learn how to use it.
 *
 * @param q A queue of items to be scrambled
 */
template <typename T>
void scramble(queue<T>& q)
{
    stack<T> s;
    // optional: queue<T> q2;
    queue<T> q2;
    queue<T> ret;

    int n = 1;

    while (!q.empty()) {
	for (int i = 0; i < n && !q.empty(); i++) {
		T curr = q.front();
		s.push(curr);
		q2.push(curr);
		q.pop();
	}
	if (n % 2 == 0) {
		while (!s.empty()) {
			ret.push(s.top());
			s.pop();
			q2.pop();
		}
	} else {
		while (!q2.empty()) {
			ret.push(q2.front());
			q2.pop();
			s.pop();
		}
	}
	n++;
    }
    q = ret;
    // Your code here
}

/**
 * Checks if the parameter stack and queue are the same. A stack and a queue
 * are considered to the "the same" if they contain only elements of exactly
 * the same values in exactly the same order.
 *
 * @note You may assume the stack and queue contain the same number of items!
 *
 * @note The back of the queue corresponds to the top of the stack!
 *
 * @note There are restrictions for writing this function.
 * - Your function may not use any loops
 * - In your function you may only declare ONE local boolean variable to use in
 *   your return statement, and you may only declare TWO local variables of
 *   parametrized type T to use however you wish.
 * - No other local variables can be used.
 * - After execution of verifySame, the stack and queue must be unchanged. Be
 *   sure to comment your code VERY well.
 *
 * @param s The stack to compare
 * @param q The queue to compare
 * @return  true if the stack and the queue are the same; false otherwise
 */
template <typename T>
bool verifySame(stack<T>& s, queue<T>& q)
{
    bool retval = true; // optional
    T q_val; // rename me
    T s_val; // rename :)

    // You have to call recursively on the stack,
    // b/c a queue can pop and push to get the next value,
    // but a stack can't.
    
    // Base Case
    if (s.empty()) {
	return true;
    }

    // Start from last value in stack (should be first value in queue)
    // Then keep going up
    s_val = s.top();
    s.pop();

    // Make sure to AND all of the retvals calculated
    // This makes sure every value is true
    retval = retval && verifySame(s, q);

    // Revert stack in the same place as the outside function
    // So as to not change the stack
    s.push(s_val);

    // Check if value in queue is equal to value in stack.
    // Return false making every future case false
    q_val = q.front();
    if (q_val != s_val) {
	retval = false;
    }

    // Move to next value in queue
    // Sicne stack is same size as queue,
    // the queue will have full rotated by the end
    q.pop();
    q.push(q_val);
    return retval;
}

}
