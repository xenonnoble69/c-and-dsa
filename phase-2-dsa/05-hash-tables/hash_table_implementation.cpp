/*
 * ============================================================================
 * HASH TABLE - COMPREHENSIVE IMPLEMENTATION
 * ============================================================================
 * 
 * A hash table (hash map) is a data structure that implements an associative
 * array abstract data type, mapping keys to values using a hash function.
 * 
 * Key Properties:
 * - Average O(1) time complexity for basic operations
 * - Uses hash function to compute array index from key
 * - Handles collisions using chaining or open addressing
 * - Dynamic resizing to maintain good performance
 * 
 * Applications:
 * - Database indexing
 * - Caching systems
 * - Symbol tables in compilers
 * - Implementing sets and maps
 * - Frequency counting
 * - Fast lookups and deduplication
 * 
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <functional>
#include <stdexcept>
#include <algorithm>

using namespace std;

/*
 * ========================================================================
 * HASH TABLE WITH SEPARATE CHAINING
 * ========================================================================
 */

template<typename K, typename V>
class HashTableChaining {
private:
    struct KeyValuePair {
        K key;
        V value;
        
        KeyValuePair(const K& k, const V& v) : key(k), value(v) {}
    };
    
    vector<list<KeyValuePair>> table;
    size_t bucketCount;
    size_t elementCount;
    double maxLoadFactor;
    
    // Hash function
    size_t hash(const K& key) const {
        /*
         * Simple hash function using std::hash
         * Can be customized for different key types
         */
        return std::hash<K>{}(key) % bucketCount;
    }
    
    // Resize hash table when load factor exceeds threshold
    void resize() {
        /*
         * Double the size and rehash all elements
         * Time Complexity: O(n)
         */
        size_t oldBucketCount = bucketCount;
        vector<list<KeyValuePair>> oldTable = move(table);
        
        bucketCount *= 2;
        table = vector<list<KeyValuePair>>(bucketCount);
        elementCount = 0;
        
        // Rehash all elements
        for (const auto& bucket : oldTable) {
            for (const auto& pair : bucket) {
                insert(pair.key, pair.value);
            }
        }
    }
    
public:
    // Constructor
    explicit HashTableChaining(size_t initialSize = 16, double maxLoad = 0.75) 
        : bucketCount(initialSize), elementCount(0), maxLoadFactor(maxLoad) {
        table.resize(bucketCount);
    }
    
    /*
     * ====================================================================
     * BASIC OPERATIONS
     * ====================================================================
     */
    
    // Insert key-value pair
    void insert(const K& key, const V& value) {
        /*
         * Insert new key-value pair or update existing key
         * Time Complexity: O(1) average, O(n) worst case
         * Space Complexity: O(1)
         */
        size_t index = hash(key);
        
        // Check if key already exists
        for (auto& pair : table[index]) {
            if (pair.key == key) {
                pair.value = value;  // Update existing
                return;
            }
        }
        
        // Insert new pair
        table[index].emplace_back(key, value);
        elementCount++;
        
        // Check if resize is needed
        if (loadFactor() > maxLoadFactor) {
            resize();
        }
    }
    
    // Search for key and return value
    V* find(const K& key) {
        /*
         * Find value associated with key
         * Time Complexity: O(1) average, O(n) worst case
         * Space Complexity: O(1)
         * Returns nullptr if key not found
         */
        size_t index = hash(key);
        
        for (auto& pair : table[index]) {
            if (pair.key == key) {
                return &pair.value;
            }
        }
        
        return nullptr;
    }
    
    // Check if key exists
    bool contains(const K& key) const {
        /*
         * Check if key exists in hash table
         * Time Complexity: O(1) average, O(n) worst case
         */
        size_t index = hash(key);
        
        for (const auto& pair : table[index]) {
            if (pair.key == key) {
                return true;
            }
        }
        
        return false;
    }
    
    // Remove key-value pair
    bool remove(const K& key) {
        /*
         * Remove key-value pair from hash table
         * Time Complexity: O(1) average, O(n) worst case
         * Returns true if key was found and removed
         */
        size_t index = hash(key);
        
        auto& bucket = table[index];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->key == key) {
                bucket.erase(it);
                elementCount--;
                return true;
            }
        }
        
        return false;
    }
    
    // Get value with operator[]
    V& operator[](const K& key) {
        /*
         * Access or create element with given key
         * Time Complexity: O(1) average, O(n) worst case
         */
        size_t index = hash(key);
        
        // Check if key exists
        for (auto& pair : table[index]) {
            if (pair.key == key) {
                return pair.value;
            }
        }
        
        // Key doesn't exist, create new entry
        table[index].emplace_back(key, V{});
        elementCount++;
        
        // Check if resize is needed
        if (loadFactor() > maxLoadFactor) {
            resize();
            // Recalculate index after resize
            index = hash(key);
            for (auto& pair : table[index]) {
                if (pair.key == key) {
                    return pair.value;
                }
            }
        }
        
        return table[index].back().value;
    }
    
    /*
     * ====================================================================
     * UTILITY FUNCTIONS
     * ====================================================================
     */
    
    // Get number of elements
    size_t size() const {
        return elementCount;
    }
    
    // Check if empty
    bool empty() const {
        return elementCount == 0;
    }
    
    // Get current load factor
    double loadFactor() const {
        return static_cast<double>(elementCount) / bucketCount;
    }
    
    // Get number of buckets
    size_t buckets() const {
        return bucketCount;
    }
    
    // Clear all elements
    void clear() {
        for (auto& bucket : table) {
            bucket.clear();
        }
        elementCount = 0;
    }
    
    // Get all keys
    vector<K> keys() const {
        vector<K> result;
        for (const auto& bucket : table) {
            for (const auto& pair : bucket) {
                result.push_back(pair.key);
            }
        }
        return result;
    }
    
    // Get all values
    vector<V> values() const {
        vector<V> result;
        for (const auto& bucket : table) {
            for (const auto& pair : bucket) {
                result.push_back(pair.value);
            }
        }
        return result;
    }
    
    // Print hash table statistics
    void printStats() const {
        cout << "Hash Table Statistics:" << endl;
        cout << "  Elements: " << elementCount << endl;
        cout << "  Buckets: " << bucketCount << endl;
        cout << "  Load Factor: " << loadFactor() << endl;
        cout << "  Max Load Factor: " << maxLoadFactor << endl;
        
        // Distribution analysis
        vector<size_t> bucketSizes;
        for (const auto& bucket : table) {
            bucketSizes.push_back(bucket.size());
        }
        
        size_t maxBucketSize = *max_element(bucketSizes.begin(), bucketSizes.end());
        size_t emptyBuckets = count(bucketSizes.begin(), bucketSizes.end(), 0);
        
        cout << "  Empty Buckets: " << emptyBuckets << " (" 
             << (100.0 * emptyBuckets / bucketCount) << "%)" << endl;
        cout << "  Max Bucket Size: " << maxBucketSize << endl;
    }
    
    // Print hash table contents
    void print() const {
        cout << "Hash Table Contents:" << endl;
        for (size_t i = 0; i < table.size(); ++i) {
            if (!table[i].empty()) {
                cout << "  Bucket " << i << ": ";
                for (const auto& pair : table[i]) {
                    cout << "(" << pair.key << ", " << pair.value << ") ";
                }
                cout << endl;
            }
        }
    }
};

/*
 * ========================================================================
 * HASH TABLE WITH OPEN ADDRESSING (LINEAR PROBING)
 * ========================================================================
 */

template<typename K, typename V>
class HashTableLinearProbing {
private:
    struct Entry {
        K key;
        V value;
        bool isOccupied;
        bool isDeleted;
        
        Entry() : isOccupied(false), isDeleted(false) {}
        Entry(const K& k, const V& v) : key(k), value(v), isOccupied(true), isDeleted(false) {}
    };
    
    vector<Entry> table;
    size_t bucketCount;
    size_t elementCount;
    size_t deletedCount;
    double maxLoadFactor;
    
    // Hash function
    size_t hash(const K& key) const {
        return std::hash<K>{}(key) % bucketCount;
    }
    
    // Find slot for key (for insertion or search)
    size_t findSlot(const K& key) const {
        /*
         * Linear probing to find slot
         * Time Complexity: O(1) average, O(n) worst case
         */
        size_t index = hash(key);
        
        while (table[index].isOccupied && !table[index].isDeleted && table[index].key != key) {
            index = (index + 1) % bucketCount;
        }
        
        return index;
    }
    
    // Resize and rehash
    void resize() {
        /*
         * Double size and rehash all elements
         * Time Complexity: O(n)
         */
        size_t oldBucketCount = bucketCount;
        vector<Entry> oldTable = move(table);
        
        bucketCount *= 2;
        table = vector<Entry>(bucketCount);
        elementCount = 0;
        deletedCount = 0;
        
        // Rehash all valid elements
        for (const auto& entry : oldTable) {
            if (entry.isOccupied && !entry.isDeleted) {
                insert(entry.key, entry.value);
            }
        }
    }
    
public:
    // Constructor
    explicit HashTableLinearProbing(size_t initialSize = 16, double maxLoad = 0.5) 
        : bucketCount(initialSize), elementCount(0), deletedCount(0), maxLoadFactor(maxLoad) {
        table.resize(bucketCount);
    }
    
    /*
     * ====================================================================
     * BASIC OPERATIONS
     * ====================================================================
     */
    
    // Insert key-value pair
    void insert(const K& key, const V& value) {
        /*
         * Insert or update key-value pair
         * Time Complexity: O(1) average, O(n) worst case
         */
        // Check if resize is needed
        if (static_cast<double>(elementCount + deletedCount) / bucketCount > maxLoadFactor) {
            resize();
        }
        
        size_t index = findSlot(key);
        
        if (!table[index].isOccupied || table[index].isDeleted) {
            // New insertion
            table[index] = Entry(key, value);
            elementCount++;
            if (table[index].isDeleted) {
                deletedCount--;
            }
        } else {
            // Update existing
            table[index].value = value;
        }
    }
    
    // Find value for key
    V* find(const K& key) {
        /*
         * Find value associated with key
         * Time Complexity: O(1) average, O(n) worst case
         */
        size_t index = hash(key);
        
        while (table[index].isOccupied) {
            if (!table[index].isDeleted && table[index].key == key) {
                return &table[index].value;
            }
            index = (index + 1) % bucketCount;
        }
        
        return nullptr;
    }
    
    // Check if key exists
    bool contains(const K& key) const {
        /*
         * Check if key exists in hash table
         * Time Complexity: O(1) average, O(n) worst case
         */
        size_t index = hash(key);
        
        while (table[index].isOccupied) {
            if (!table[index].isDeleted && table[index].key == key) {
                return true;
            }
            index = (index + 1) % bucketCount;
        }
        
        return false;
    }
    
    // Remove key-value pair
    bool remove(const K& key) {
        /*
         * Remove key-value pair (lazy deletion)
         * Time Complexity: O(1) average, O(n) worst case
         */
        size_t index = hash(key);
        
        while (table[index].isOccupied) {
            if (!table[index].isDeleted && table[index].key == key) {
                table[index].isDeleted = true;
                elementCount--;
                deletedCount++;
                return true;
            }
            index = (index + 1) % bucketCount;
        }
        
        return false;
    }
    
    // Access operator
    V& operator[](const K& key) {
        /*
         * Access or create element
         * Time Complexity: O(1) average, O(n) worst case
         */
        V* found = find(key);
        if (found) {
            return *found;
        }
        
        // Insert new element with default value
        insert(key, V{});
        return *find(key);
    }
    
    /*
     * ====================================================================
     * UTILITY FUNCTIONS
     * ====================================================================
     */
    
    size_t size() const { return elementCount; }
    bool empty() const { return elementCount == 0; }
    double loadFactor() const { return static_cast<double>(elementCount) / bucketCount; }
    size_t buckets() const { return bucketCount; }
    
    void clear() {
        table = vector<Entry>(bucketCount);
        elementCount = 0;
        deletedCount = 0;
    }
    
    vector<K> keys() const {
        vector<K> result;
        for (const auto& entry : table) {
            if (entry.isOccupied && !entry.isDeleted) {
                result.push_back(entry.key);
            }
        }
        return result;
    }
    
    void printStats() const {
        cout << "Hash Table (Linear Probing) Statistics:" << endl;
        cout << "  Elements: " << elementCount << endl;
        cout << "  Deleted: " << deletedCount << endl;
        cout << "  Buckets: " << bucketCount << endl;
        cout << "  Load Factor: " << loadFactor() << endl;
        cout << "  Max Load Factor: " << maxLoadFactor << endl;
        
        size_t occupiedSlots = 0;
        for (const auto& entry : table) {
            if (entry.isOccupied) {
                occupiedSlots++;
            }
        }
        
        cout << "  Occupied Slots: " << occupiedSlots << " (" 
             << (100.0 * occupiedSlots / bucketCount) << "%)" << endl;
    }
};

/*
 * ========================================================================
 * CUSTOM HASH FUNCTIONS
 * ========================================================================
 */

// Custom hash function for strings (djb2 algorithm)
struct StringHashDJB2 {
    size_t operator()(const string& str) const {
        size_t hash = 5381;
        for (char c : str) {
            hash = ((hash << 5) + hash) + c;  // hash * 33 + c
        }
        return hash;
    }
};

// Custom hash function for pairs
template<typename T1, typename T2>
struct PairHash {
    size_t operator()(const pair<T1, T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ (h2 << 1);
    }
};

/*
 * ========================================================================
 * SPECIALIZED HASH TABLE APPLICATIONS
 * ========================================================================
 */

// Frequency Counter
template<typename T>
class FrequencyCounter {
private:
    HashTableChaining<T, int> freq;
    
public:
    void add(const T& item) {
        if (freq.contains(item)) {
            freq[item]++;
        } else {
            freq.insert(item, 1);
        }
    }
    
    int getFrequency(const T& item) const {
        auto* count = const_cast<FrequencyCounter*>(this)->freq.find(item);
        return count ? *count : 0;
    }
    
    vector<pair<T, int>> getMostFrequent(int k) const {
        auto keys = freq.keys();
        vector<pair<T, int>> items;
        
        for (const auto& key : keys) {
            auto* count = const_cast<FrequencyCounter*>(this)->freq.find(key);
            if (count) {
                items.emplace_back(key, *count);
            }
        }
        
        sort(items.begin(), items.end(), 
             [](const pair<T, int>& a, const pair<T, int>& b) {
                 return a.second > b.second;
             });
        
        if (k < items.size()) {
            items.resize(k);
        }
        
        return items;
    }
    
    void print() const {
        cout << "Frequency Counter:" << endl;
        auto keys = freq.keys();
        for (const auto& key : keys) {
            auto* count = const_cast<FrequencyCounter*>(this)->freq.find(key);
            if (count) {
                cout << "  " << key << ": " << *count << endl;
            }
        }
    }
};

// LRU Cache using hash table + doubly linked list
template<typename K, typename V>
class LRUCache {
private:
    struct Node {
        K key;
        V value;
        Node* prev;
        Node* next;
        
        Node(const K& k, const V& v) : key(k), value(v), prev(nullptr), next(nullptr) {}
    };
    
    HashTableChaining<K, Node*> cache;
    Node* head;
    Node* tail;
    size_t capacity;
    size_t currentSize;
    
    void moveToHead(Node* node) {
        removeNode(node);
        addToHead(node);
    }
    
    void removeNode(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    
    void addToHead(Node* node) {
        node->prev = head;
        node->next = head->next;
        head->next->prev = node;
        head->next = node;
    }
    
    Node* removeTail() {
        Node* last = tail->prev;
        removeNode(last);
        return last;
    }
    
public:
    explicit LRUCache(size_t cap) : capacity(cap), currentSize(0) {
        head = new Node(K{}, V{});
        tail = new Node(K{}, V{});
        head->next = tail;
        tail->prev = head;
    }
    
    ~LRUCache() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
    
    V* get(const K& key) {
        Node** node = cache.find(key);
        if (node && *node) {
            moveToHead(*node);
            return &(*node)->value;
        }
        return nullptr;
    }
    
    void put(const K& key, const V& value) {
        Node** existing = cache.find(key);
        
        if (existing && *existing) {
            // Update existing
            (*existing)->value = value;
            moveToHead(*existing);
        } else {
            // Add new node
            Node* newNode = new Node(key, value);
            
            if (currentSize >= capacity) {
                // Remove LRU
                Node* lru = removeTail();
                cache.remove(lru->key);
                delete lru;
                currentSize--;
            }
            
            addToHead(newNode);
            cache.insert(key, newNode);
            currentSize++;
        }
    }
    
    void printCache() const {
        cout << "LRU Cache (most recent first): ";
        Node* current = head->next;
        while (current != tail) {
            cout << "(" << current->key << ", " << current->value << ") ";
            current = current->next;
        }
        cout << endl;
    }
};

/*
 * ========================================================================
 * DEMONSTRATION AND TESTING
 * ========================================================================
 */

void demonstrateBasicOperations() {
    cout << "=== BASIC HASH TABLE OPERATIONS ===" << endl;
    
    HashTableChaining<string, int> hashTable(8);
    
    // Insert operations
    cout << "\nInserting key-value pairs:" << endl;
    hashTable.insert("apple", 5);
    hashTable.insert("banana", 3);
    hashTable.insert("orange", 8);
    hashTable.insert("grape", 12);
    hashTable.insert("kiwi", 7);
    
    hashTable.print();
    hashTable.printStats();
    
    // Search operations
    cout << "\nSearch operations:" << endl;
    cout << "apple: " << (hashTable.contains("apple") ? "found" : "not found") << endl;
    cout << "mango: " << (hashTable.contains("mango") ? "found" : "not found") << endl;
    
    auto* value = hashTable.find("banana");
    if (value) {
        cout << "banana value: " << *value << endl;
    }
    
    // Update and access
    cout << "\nUpdate and access:" << endl;
    hashTable["apple"] = 10;  // Update
    hashTable["mango"] = 6;   // Insert new
    
    cout << "Updated apple: " << hashTable["apple"] << endl;
    cout << "New mango: " << hashTable["mango"] << endl;
    
    // Remove operation
    cout << "\nRemoving 'banana':" << endl;
    hashTable.remove("banana");
    cout << "banana after removal: " << (hashTable.contains("banana") ? "found" : "not found") << endl;
    
    hashTable.printStats();
}

void demonstrateLinearProbing() {
    cout << "\n=== LINEAR PROBING HASH TABLE ===" << endl;
    
    HashTableLinearProbing<int, string> hashTable(8);
    
    // Insert with potential collisions
    hashTable.insert(1, "one");
    hashTable.insert(9, "nine");   // Will collide with 1 (9 % 8 = 1)
    hashTable.insert(17, "seventeen"); // Will collide again
    hashTable.insert(2, "two");
    hashTable.insert(10, "ten");
    
    cout << "Inserted values with collisions:" << endl;
    hashTable.printStats();
    
    // Test retrieval
    cout << "\nRetrieval test:" << endl;
    cout << "Key 1: " << (hashTable.find(1) ? *hashTable.find(1) : "not found") << endl;
    cout << "Key 9: " << (hashTable.find(9) ? *hashTable.find(9) : "not found") << endl;
    cout << "Key 17: " << (hashTable.find(17) ? *hashTable.find(17) : "not found") << endl;
    
    // Test removal
    cout << "\nRemoving key 9:" << endl;
    hashTable.remove(9);
    cout << "Key 9 after removal: " << (hashTable.find(9) ? *hashTable.find(9) : "not found") << endl;
    cout << "Key 17 after removing 9: " << (hashTable.find(17) ? *hashTable.find(17) : "not found") << endl;
    
    hashTable.printStats();
}

void demonstrateFrequencyCounter() {
    cout << "\n=== FREQUENCY COUNTER ===" << endl;
    
    FrequencyCounter<string> counter;
    
    vector<string> words = {"apple", "banana", "apple", "orange", "banana", 
                           "apple", "grape", "banana", "apple"};
    
    cout << "Processing words: ";
    for (const string& word : words) {
        cout << word << " ";
        counter.add(word);
    }
    cout << endl;
    
    counter.print();
    
    cout << "\nTop 3 most frequent:" << endl;
    auto top3 = counter.getMostFrequent(3);
    for (const auto& item : top3) {
        cout << "  " << item.first << ": " << item.second << endl;
    }
}

void demonstrateLRUCache() {
    cout << "\n=== LRU CACHE ===" << endl;
    
    LRUCache<int, string> cache(3);
    
    cout << "Cache operations:" << endl;
    cache.put(1, "one");
    cache.printCache();
    
    cache.put(2, "two");
    cache.printCache();
    
    cache.put(3, "three");
    cache.printCache();
    
    // Access key 1 (moves to front)
    auto* value = cache.get(1);
    cout << "Accessed key 1: " << (value ? *value : "not found") << endl;
    cache.printCache();
    
    // Add key 4 (should evict key 2)
    cache.put(4, "four");
    cout << "Added key 4:" << endl;
    cache.printCache();
    
    // Try to access evicted key 2
    value = cache.get(2);
    cout << "Try to access key 2: " << (value ? *value : "not found") << endl;
}

void demonstrateCustomHashFunctions() {
    cout << "\n=== CUSTOM HASH FUNCTIONS ===" << endl;
    
    // Using custom string hash
    HashTableChaining<string, int> stringTable;
    
    vector<string> testStrings = {"hello", "world", "hash", "table", "custom"};
    
    cout << "String hash values (custom djb2):" << endl;
    StringHashDJB2 customHash;
    for (const string& str : testStrings) {
        cout << "  " << str << ": " << customHash(str) << endl;
        stringTable.insert(str, str.length());
    }
    
    // Using pair hash
    HashTableChaining<pair<int, int>, string> pairTable;
    
    cout << "\nPair hash values:" << endl;
    PairHash<int, int> pairHash;
    vector<pair<int, int>> testPairs = {{1, 2}, {3, 4}, {5, 6}};
    
    for (const auto& p : testPairs) {
        cout << "  (" << p.first << ", " << p.second << "): " << pairHash(p) << endl;
        pairTable.insert(p, "pair_" + to_string(p.first) + "_" + to_string(p.second));
    }
}

/*
 * ========================================================================
 * MAIN FUNCTION
 * ========================================================================
 */

int main() {
    cout << "=== HASH TABLE COMPREHENSIVE GUIDE ===" << endl;
    
    demonstrateBasicOperations();
    demonstrateLinearProbing();
    demonstrateFrequencyCounter();
    demonstrateLRUCache();
    demonstrateCustomHashFunctions();
    
    cout << "\n=== All Hash Table Operations Demonstrated! ===" << endl;
    
    return 0;
}

/*
 * ============================================================================
 * HASH TABLE COMPLEXITY ANALYSIS:
 * ============================================================================
 * 
 * BASIC OPERATIONS (Average Case):
 * - Insert: O(1) time, O(1) space
 * - Search: O(1) time, O(1) space
 * - Delete: O(1) time, O(1) space
 * - Access: O(1) time, O(1) space
 * 
 * WORST CASE (All keys hash to same bucket):
 * - Insert: O(n) time
 * - Search: O(n) time
 * - Delete: O(n) time
 * 
 * SPACE COMPLEXITY:
 * - Overall: O(n) for storing n key-value pairs
 * - Additional: O(m) where m is number of buckets
 * 
 * LOAD FACTOR IMPACT:
 * - Low load factor: Fast operations, more memory usage
 * - High load factor: Slower operations, less memory usage
 * - Optimal load factor: Usually 0.5-0.75
 * 
 * COLLISION RESOLUTION COMPARISON:
 * 
 * SEPARATE CHAINING:
 * - Pros: Simple, handles high load factors well
 * - Cons: Extra memory for pointers, cache misses
 * - Best for: General purpose, unknown load patterns
 * 
 * OPEN ADDRESSING (Linear Probing):
 * - Pros: Cache friendly, no pointer overhead
 * - Cons: Clustering, requires lower load factor
 * - Best for: High performance, known load patterns
 * 
 * HASH FUNCTION QUALITY:
 * - Good distribution reduces collisions
 * - Fast computation is important
 * - Should minimize clustering
 * - Examples: djb2, FNV, CityHash, MurmurHash
 * 
 * APPLICATIONS:
 * - Database indexing: O(1) lookups
 * - Caching systems: Fast data retrieval
 * - Compiler symbol tables: Variable/function lookup
 * - Deduplication: Fast duplicate detection
 * - Frequency counting: Efficient counting
 * - Set operations: Union, intersection, difference
 * 
 * ============================================================================
 */
