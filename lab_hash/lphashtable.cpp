/**
 * @file lphashtable.cpp
 * Implementation of the LPHashTable class.
 */
#include "lphashtable.h"

template <class K, class V>
LPHashTable<K, V>::LPHashTable(size_t tsize)
{
    if (tsize <= 0)
        tsize = 17;
    size = findPrime(tsize);
    table = new std::pair<K, V>*[size];
    should_probe = new bool[size];
    for (size_t i = 0; i < size; i++) {
        table[i] = NULL;
        should_probe[i] = false;
    }
    elems = 0;
}

template <class K, class V>
LPHashTable<K, V>::~LPHashTable()
{
    for (size_t i = 0; i < size; i++)
        delete table[i];
    delete[] table;
    delete[] should_probe;
}

template <class K, class V>
LPHashTable<K, V> const& LPHashTable<K, V>::operator=(LPHashTable const& rhs)
{
    if (this != &rhs) {
        for (size_t i = 0; i < size; i++)
            delete table[i];
        delete[] table;
        delete[] should_probe;

        table = new std::pair<K, V>*[rhs.size];
        should_probe = new bool[rhs.size];
        for (size_t i = 0; i < rhs.size; i++) {
            should_probe[i] = rhs.should_probe[i];
            if (rhs.table[i] == NULL)
                table[i] = NULL;
            else
                table[i] = new std::pair<K, V>(*(rhs.table[i]));
        }
        size = rhs.size;
        elems = rhs.elems;
    }
    return *this;
}

template <class K, class V>
LPHashTable<K, V>::LPHashTable(LPHashTable<K, V> const& other)
{
    table = new std::pair<K, V>*[other.size];
    should_probe = new bool[other.size];
    for (size_t i = 0; i < other.size; i++) {
        should_probe[i] = other.should_probe[i];
        if (other.table[i] == NULL)
            table[i] = NULL;
        else
            table[i] = new std::pair<K, V>(*(other.table[i]));
    }
    size = other.size;
    elems = other.elems;
}

template <class K, class V>
void LPHashTable<K, V>::insert(K const& key, V const& value)
{

    /**
     * @todo Implement this function.
     *
     * @note Remember to resize the table when necessary (load factor >= 0.7).
     * **Do this check *after* increasing elems (but before inserting)!!**
     * Also, don't forget to mark the cell for probing with should_probe!
     */
    size_t hash = hashes::hash(key, size);
    elems++;

    // Check if we need to resize
    if ((float) elems / size >= 0.7) {
	resizeTable();
    }

    // insert hash into table
    while (table[hash]) {
	hash = (hash + 1) % size;
    }
    table[hash] = new std::pair<K, V>(key, value);

    // After insert it should be probed
    should_probe[hash] = true;
}

template <class K, class V>
void LPHashTable<K, V>::remove(K const& key)
{
    /**
     * @todo: implement this function
     */
    // Find the index of the key
    size_t index = findIndex(key);
    delete table[index];
    table[index] = nullptr;
    should_probe[index] = false;
    elems--;
}

template <class K, class V>
int LPHashTable<K, V>::findIndex(const K& key) const
{

    /**
     * @todo Implement this function
     *
     * Be careful in determining when the key is not in the table!
     */
    size_t hash = hashes::hash(key, size);
    size_t start_hash = hash;

    // Iterate through table to find whether the probe is true and
    // the hash is the same, starting at hash
    while (!(should_probe[hash] && table[hash] && table[hash]->first == key)) {
	hash = (hash + 1) % size;
	if (start_hash == hash) {
		return -1;
	}
    }

    return hash;
}

template <class K, class V>
V LPHashTable<K, V>::find(K const& key) const
{
    int idx = findIndex(key);
    if (idx != -1)
        return table[idx]->second;
    return V();
}

template <class K, class V>
V& LPHashTable<K, V>::operator[](K const& key)
{
    // First, attempt to find the key and return its value by reference
    int idx = findIndex(key);
    if (idx == -1) {
        // otherwise, insert the default value and return it
        insert(key, V());
        idx = findIndex(key);
    }
    return table[idx]->second;
}

template <class K, class V>
bool LPHashTable<K, V>::keyExists(K const& key) const
{
    return findIndex(key) != -1;
}

template <class K, class V>
void LPHashTable<K, V>::clear()
{
    for (size_t i = 0; i < size; i++)
        delete table[i];
    delete[] table;
    delete[] should_probe;
    table = new std::pair<K, V>*[17];
    should_probe = new bool[17];
    for (size_t i = 0; i < 17; i++)
        should_probe[i] = false;
    size = 17;
    elems = 0;
}

template <class K, class V>
void LPHashTable<K, V>::resizeTable()
{

    /**
     * @todo Implement this function
     *
     * The size of the table should be the closest prime to size * 2.
     *
     * @hint Use findPrime()!
     */
    // Make new table
    size_t new_size = findPrime(2*size);
    std::pair<K, V>** new_table = new std::pair<K, V>*[new_size]();
    bool* new_should_probe = new bool[new_size]();

    for (auto it = begin(); it != end(); it++) {
	K key = it->first;
	V value = it->second;
/* ====================     Insert    ============================== **/
	size_t hash = hashes::hash(key, new_size);

	// insert hash into table
	while (new_table[hash]) {
		hash = (hash + 1) % new_size;
	}
	new_table[hash] = new std::pair<K, V>(key, value);

	// After insert it should be probed
	new_should_probe[hash] = true;
/* ====================     Insert    ============================== **/
    }
    for (size_t i = 0; i < size; i++)
        delete table[i];
    delete[] table;
    size = new_size;
    delete[] should_probe;
    should_probe = new_should_probe;
    table = new_table;
}
