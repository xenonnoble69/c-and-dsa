/*
 * ============================================================================
 * STL CONTAINERS - COMPREHENSIVE GUIDE
 * ============================================================================
 * 
 * THEORY:
 * The Standard Template Library (STL) is a powerful collection of template
 * classes and functions that provide common data structures and algorithms.
 * STL containers are template classes that store collections of objects.
 * 
 * TYPES OF STL CONTAINERS:
 * 1. Sequence Containers - Store elements in linear sequence
 *    - vector, deque, list, forward_list, array
 * 2. Associative Containers - Store sorted elements
 *    - set, multiset, map, multimap
 * 3. Unordered Associative Containers - Hash-based storage
 *    - unordered_set, unordered_multiset, unordered_map, unordered_multimap
 * 4. Container Adapters - Provide specific interfaces
 *    - stack, queue, priority_queue
 * 
 * KEY CONCEPTS:
 * - Iterators: Objects that point to elements in containers
 * - Algorithms: Functions that work with containers via iterators
 * - Function Objects: Objects that can be called like functions
 * - Memory Management: Automatic allocation and deallocation
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <array>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <queue>
#include <string>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <iomanip>

using namespace std;

/*
 * ========================================================================
 * 1. SEQUENCE CONTAINERS
 * ========================================================================
 */

void demonstrateVector() {
    cout << "1. VECTOR - Dynamic Array" << endl;
    cout << "==========================" << endl;
    
    // Vector initialization
    vector<int> vec1;                           // Empty vector
    vector<int> vec2(5, 10);                    // 5 elements, all 10
    vector<int> vec3 = {1, 2, 3, 4, 5};         // Initializer list
    vector<int> vec4(vec3);                     // Copy constructor
    
    cout << "Vector initialization:" << endl;
    cout << "vec2 (5 elements of 10): ";
    for (int val : vec2) cout << val << " ";
    cout << endl;
    
    cout << "vec3 (initializer list): ";
    for (int val : vec3) cout << val << " ";
    cout << endl;
    
    // Adding elements
    vec1.push_back(100);
    vec1.push_back(200);
    vec1.push_back(300);
    vec1.emplace_back(400);  // Construct in-place (C++11)
    
    cout << "\nAfter adding elements to vec1: ";
    for (int val : vec1) cout << val << " ";
    cout << endl;
    
    // Accessing elements
    cout << "\nAccessing elements:" << endl;
    cout << "vec1[0] = " << vec1[0] << endl;
    cout << "vec1.at(1) = " << vec1.at(1) << endl;  // Bounds checking
    cout << "vec1.front() = " << vec1.front() << endl;
    cout << "vec1.back() = " << vec1.back() << endl;
    
    // Vector properties
    cout << "\nVector properties:" << endl;
    cout << "Size: " << vec1.size() << endl;
    cout << "Capacity: " << vec1.capacity() << endl;
    cout << "Empty: " << (vec1.empty() ? "Yes" : "No") << endl;
    
    // Modifying vector
    vec1.insert(vec1.begin() + 2, 250);  // Insert at position 2
    cout << "\nAfter inserting 250 at position 2: ";
    for (int val : vec1) cout << val << " ";
    cout << endl;
    
    vec1.erase(vec1.begin() + 1);  // Remove element at position 1
    cout << "After erasing element at position 1: ";
    for (int val : vec1) cout << val << " ";
    cout << endl;
    
    // Resize and reserve
    vec1.resize(7, 999);  // Resize to 7 elements, fill new with 999
    cout << "After resize(7, 999): ";
    for (int val : vec1) cout << val << " ";
    cout << endl;
    
    vec1.reserve(20);  // Reserve capacity for 20 elements
    cout << "After reserve(20), capacity: " << vec1.capacity() << endl;
    
    cout << endl;
}

void demonstrateDeque() {
    cout << "2. DEQUE - Double-ended Queue" << endl;
    cout << "=============================" << endl;
    
    deque<int> dq;
    
    // Adding elements at both ends
    dq.push_back(3);
    dq.push_back(4);
    dq.push_front(2);
    dq.push_front(1);
    
    cout << "After adding elements: ";
    for (int val : dq) cout << val << " ";
    cout << endl;
    
    // Accessing elements (similar to vector)
    cout << "Front: " << dq.front() << ", Back: " << dq.back() << endl;
    cout << "Element at index 2: " << dq[2] << endl;
    
    // Removing elements from both ends
    dq.pop_front();
    dq.pop_back();
    
    cout << "After removing front and back: ";
    for (int val : dq) cout << val << " ";
    cout << endl;
    
    // Insert and erase (similar to vector)
    dq.insert(dq.begin() + 1, 25);
    cout << "After inserting 25 at position 1: ";
    for (int val : dq) cout << val << " ";
    cout << endl;
    
    cout << endl;
}

void demonstrateList() {
    cout << "3. LIST - Doubly Linked List" << endl;
    cout << "=============================" << endl;
    
    list<string> lst = {"apple", "banana", "cherry"};
    
    cout << "Initial list: ";
    for (const string& item : lst) cout << item << " ";
    cout << endl;
    
    // Adding elements
    lst.push_front("orange");
    lst.push_back("grape");
    
    cout << "After adding elements: ";
    for (const string& item : lst) cout << item << " ";
    cout << endl;
    
    // List-specific operations
    lst.sort();  // Sort the list
    cout << "After sorting: ";
    for (const string& item : lst) cout << item << " ";
    cout << endl;
    
    lst.reverse();  // Reverse the list
    cout << "After reversing: ";
    for (const string& item : lst) cout << item << " ";
    cout << endl;
    
    lst.unique();  // Remove consecutive duplicates
    cout << "After removing duplicates: ";
    for (const string& item : lst) cout << item << " ";
    cout << endl;
    
    // Remove specific elements
    lst.remove("banana");
    cout << "After removing 'banana': ";
    for (const string& item : lst) cout << item << " ";
    cout << endl;
    
    cout << endl;
}

void demonstrateArray() {
    cout << "4. ARRAY - Fixed Size Array (C++11)" << endl;
    cout << "====================================" << endl;
    
    array<int, 5> arr = {10, 20, 30, 40, 50};
    
    cout << "Array elements: ";
    for (int val : arr) cout << val << " ";
    cout << endl;
    
    // Array properties
    cout << "Size: " << arr.size() << endl;
    cout << "Max size: " << arr.max_size() << endl;
    cout << "Empty: " << (arr.empty() ? "Yes" : "No") << endl;
    
    // Accessing elements
    cout << "First element: " << arr.front() << endl;
    cout << "Last element: " << arr.back() << endl;
    cout << "Element at index 2: " << arr[2] << endl;
    
    // Modifying elements
    arr[1] = 25;
    arr.at(3) = 45;
    
    cout << "After modification: ";
    for (int val : arr) cout << val << " ";
    cout << endl;
    
    // Fill array with single value
    array<int, 5> arr2;
    arr2.fill(100);
    
    cout << "Array filled with 100: ";
    for (int val : arr2) cout << val << " ";
    cout << endl;
    
    cout << endl;
}

/*
 * ========================================================================
 * 2. ASSOCIATIVE CONTAINERS
 * ========================================================================
 */

void demonstrateSet() {
    cout << "5. SET - Ordered Unique Elements" << endl;
    cout << "=================================" << endl;
    
    set<int> s;
    
    // Inserting elements
    s.insert(30);
    s.insert(10);
    s.insert(20);
    s.insert(30);  // Duplicate - won't be inserted
    s.insert(40);
    
    cout << "Set elements (automatically sorted): ";
    for (int val : s) cout << val << " ";
    cout << endl;
    
    // Set operations
    cout << "Size: " << s.size() << endl;
    cout << "Contains 20: " << (s.find(20) != s.end() ? "Yes" : "No") << endl;
    cout << "Contains 25: " << (s.find(25) != s.end() ? "Yes" : "No") << endl;
    
    // Using count (returns 0 or 1 for set)
    cout << "Count of 30: " << s.count(30) << endl;
    
    // Erasing elements
    s.erase(20);
    cout << "After erasing 20: ";
    for (int val : s) cout << val << " ";
    cout << endl;
    
    // Multiset - allows duplicates
    multiset<int> ms = {5, 3, 5, 7, 3, 9, 5};
    cout << "Multiset with duplicates: ";
    for (int val : ms) cout << val << " ";
    cout << endl;
    cout << "Count of 5 in multiset: " << ms.count(5) << endl;
    
    cout << endl;
}

void demonstrateMap() {
    cout << "6. MAP - Key-Value Pairs (Ordered)" << endl;
    cout << "===================================" << endl;
    
    map<string, int> ages;
    
    // Inserting key-value pairs
    ages["Alice"] = 25;
    ages["Bob"] = 30;
    ages["Charlie"] = 22;
    ages.insert({"David", 28});
    ages.insert(make_pair("Eve", 26));
    
    cout << "Map contents:" << endl;
    for (const auto& pair : ages) {
        cout << pair.first << ": " << pair.second << " years old" << endl;
    }
    
    // Accessing elements
    cout << "\nAlice's age: " << ages["Alice"] << endl;
    cout << "Bob's age: " << ages.at("Bob") << endl;
    
    // Checking if key exists
    if (ages.find("Charlie") != ages.end()) {
        cout << "Charlie found with age: " << ages["Charlie"] << endl;
    }
    
    // Modifying values
    ages["Alice"] = 26;  // Update age
    cout << "Alice's updated age: " << ages["Alice"] << endl;
    
    // Map properties
    cout << "\nMap size: " << ages.size() << endl;
    cout << "Empty: " << (ages.empty() ? "Yes" : "No") << endl;
    
    // Erasing elements
    ages.erase("Bob");
    cout << "After erasing Bob:" << endl;
    for (const auto& pair : ages) {
        cout << pair.first << ": " << pair.second << endl;
    }
    
    // Multimap - allows duplicate keys
    multimap<string, string> phone_book;
    phone_book.insert({"John", "123-456-7890"});
    phone_book.insert({"John", "987-654-3210"});
    phone_book.insert({"Jane", "555-123-4567"});
    
    cout << "\nMultimap (phone book):" << endl;
    for (const auto& pair : phone_book) {
        cout << pair.first << ": " << pair.second << endl;
    }
    
    cout << endl;
}

/*
 * ========================================================================
 * 3. UNORDERED ASSOCIATIVE CONTAINERS
 * ========================================================================
 */

void demonstrateUnorderedContainers() {
    cout << "7. UNORDERED CONTAINERS - Hash-based" << endl;
    cout << "=====================================" << endl;
    
    // Unordered set
    unordered_set<string> words = {"apple", "banana", "cherry", "apple"};
    
    cout << "Unordered set (no specific order): ";
    for (const string& word : words) cout << word << " ";
    cout << endl;
    
    // Fast lookup
    cout << "Contains 'banana': " << (words.find("banana") != words.end() ? "Yes" : "No") << endl;
    
    // Unordered map
    unordered_map<string, int> word_count;
    word_count["hello"] = 5;
    word_count["world"] = 3;
    word_count["programming"] = 7;
    
    cout << "\nUnordered map (word counts):" << endl;
    for (const auto& pair : word_count) {
        cout << pair.first << ": " << pair.second << endl;
    }
    
    // Hash table properties
    cout << "\nHash table properties:" << endl;
    cout << "Bucket count: " << word_count.bucket_count() << endl;
    cout << "Load factor: " << word_count.load_factor() << endl;
    cout << "Max load factor: " << word_count.max_load_factor() << endl;
    
    cout << endl;
}

/*
 * ========================================================================
 * 4. CONTAINER ADAPTERS
 * ========================================================================
 */

void demonstrateAdapters() {
    cout << "8. CONTAINER ADAPTERS" << endl;
    cout << "=====================" << endl;
    
    // Stack (LIFO - Last In, First Out)
    cout << "Stack (LIFO):" << endl;
    stack<int> stk;
    stk.push(10);
    stk.push(20);
    stk.push(30);
    
    cout << "Stack contents (top to bottom): ";
    while (!stk.empty()) {
        cout << stk.top() << " ";
        stk.pop();
    }
    cout << endl;
    
    // Queue (FIFO - First In, First Out)
    cout << "\nQueue (FIFO):" << endl;
    queue<string> q;
    q.push("First");
    q.push("Second");
    q.push("Third");
    
    cout << "Queue contents (front to back): ";
    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;
    
    // Priority Queue (Max heap by default)
    cout << "\nPriority Queue (Max heap):" << endl;
    priority_queue<int> pq;
    pq.push(30);
    pq.push(10);
    pq.push(50);
    pq.push(20);
    
    cout << "Priority queue contents (highest to lowest): ";
    while (!pq.empty()) {
        cout << pq.top() << " ";
        pq.pop();
    }
    cout << endl;
    
    // Min heap priority queue
    cout << "\nPriority Queue (Min heap):" << endl;
    priority_queue<int, vector<int>, greater<int>> min_pq;
    min_pq.push(30);
    min_pq.push(10);
    min_pq.push(50);
    min_pq.push(20);
    
    cout << "Min priority queue contents (lowest to highest): ";
    while (!min_pq.empty()) {
        cout << min_pq.top() << " ";
        min_pq.pop();
    }
    cout << endl;
    
    cout << endl;
}

/*
 * ========================================================================
 * 5. ITERATORS
 * ========================================================================
 */

void demonstrateIterators() {
    cout << "9. ITERATORS" << endl;
    cout << "============" << endl;
    
    vector<int> vec = {1, 2, 3, 4, 5};
    
    // Different types of iterators
    cout << "Forward iteration: ";
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    cout << "Reverse iteration: ";
    for (auto it = vec.rbegin(); it != vec.rend(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    // Const iterators
    cout << "Const iteration: ";
    for (auto it = vec.cbegin(); it != vec.cend(); ++it) {
        cout << *it << " ";
        // *it = 10;  // Error: cannot modify through const iterator
    }
    cout << endl;
    
    // Iterator arithmetic (for random access iterators)
    cout << "Iterator arithmetic:" << endl;
    auto it = vec.begin();
    cout << "First element: " << *it << endl;
    cout << "Third element: " << *(it + 2) << endl;
    cout << "Distance from begin to end: " << distance(vec.begin(), vec.end()) << endl;
    
    // Advance iterator
    advance(it, 3);
    cout << "After advance(it, 3): " << *it << endl;
    
    cout << endl;
}

/*
 * ========================================================================
 * 6. PRACTICAL EXAMPLES
 * ========================================================================
 */

void demonstratePracticalExamples() {
    cout << "10. PRACTICAL EXAMPLES" << endl;
    cout << "======================" << endl;
    
    // Example 1: Word frequency counter
    cout << "Example 1: Word Frequency Counter" << endl;
    vector<string> words = {"apple", "banana", "apple", "cherry", "banana", "apple"};
    map<string, int> word_freq;
    
    for (const string& word : words) {
        word_freq[word]++;
    }
    
    cout << "Word frequencies:" << endl;
    for (const auto& pair : word_freq) {
        cout << pair.first << ": " << pair.second << endl;
    }
    
    // Example 2: Finding unique elements
    cout << "\nExample 2: Finding Unique Elements" << endl;
    vector<int> numbers = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4};
    set<int> unique_numbers(numbers.begin(), numbers.end());
    
    cout << "Original: ";
    for (int num : numbers) cout << num << " ";
    cout << endl;
    
    cout << "Unique: ";
    for (int num : unique_numbers) cout << num << " ";
    cout << endl;
    
    // Example 3: Top K elements
    cout << "\nExample 3: Top 3 Elements" << endl;
    vector<int> data = {64, 34, 25, 12, 22, 11, 90, 88, 76, 50};
    priority_queue<int> pq(data.begin(), data.end());
    
    cout << "Original data: ";
    for (int val : data) cout << val << " ";
    cout << endl;
    
    cout << "Top 3 elements: ";
    for (int i = 0; i < 3 && !pq.empty(); i++) {
        cout << pq.top() << " ";
        pq.pop();
    }
    cout << endl;
    
    // Example 4: LRU Cache simulation using deque
    cout << "\nExample 4: LRU Cache Simulation" << endl;
    deque<int> cache;
    const int CACHE_SIZE = 3;
    vector<int> access_pattern = {1, 2, 3, 1, 4, 2, 5};
    
    for (int page : access_pattern) {
        cout << "Accessing page " << page << ": ";
        
        // Remove if already exists
        auto it = find(cache.begin(), cache.end(), page);
        if (it != cache.end()) {
            cache.erase(it);
        }
        
        // Add to front
        cache.push_front(page);
        
        // Maintain cache size
        if (cache.size() > CACHE_SIZE) {
            cache.pop_back();
        }
        
        // Print current cache state
        cout << "Cache: ";
        for (int cached : cache) cout << cached << " ";
        cout << endl;
    }
    
    cout << endl;
}

/*
 * ========================================================================
 * MAIN FUNCTION
 * ========================================================================
 */

int main() {
    cout << "=== STL CONTAINERS COMPREHENSIVE GUIDE ===" << endl << endl;
    
    demonstrateVector();
    demonstrateDeque();
    demonstrateList();
    demonstrateArray();
    demonstrateSet();
    demonstrateMap();
    demonstrateUnorderedContainers();
    demonstrateAdapters();
    demonstrateIterators();
    demonstratePracticalExamples();
    
    cout << "=== STL Containers Mastery Complete! ===" << endl;
    
    return 0;
}

/*
 * ============================================================================
 * PRACTICE EXERCISES:
 * ============================================================================
 * 
 * 1. Implement a phone book using map that supports add, remove, and search operations.
 * 
 * 2. Create a program that finds the intersection of two sets.
 * 
 * 3. Implement a task scheduler using priority_queue where tasks have priorities.
 * 
 * 4. Write a program that removes duplicates from a vector while preserving order.
 * 
 * 5. Create a simple text editor that maintains undo/redo functionality using stacks.
 * 
 * 6. Implement a graph adjacency list representation using map<int, vector<int>>.
 * 
 * 7. Write a program that groups anagrams together using unordered_map.
 * 
 * 8. Create a sliding window maximum finder using deque.
 * 
 * 9. Implement a simple database using map<string, map<string, string>>.
 * 
 * 10. Write a program that simulates a browser's back/forward functionality.
 * 
 * ============================================================================
 * CONTAINER SELECTION GUIDE:
 * ============================================================================
 * 
 * Use vector when:
 * - You need random access to elements
 * - You frequently append elements to the end
 * - Memory locality is important
 * - You need to pass data to C APIs
 * 
 * Use deque when:
 * - You need to insert/remove at both ends
 * - You need random access but also frequent front operations
 * - You want to avoid iterator invalidation on insertions
 * 
 * Use list when:
 * - You frequently insert/remove in the middle
 * - You don't need random access
 * - You want stable iterators
 * 
 * Use set/map when:
 * - You need sorted, unique elements
 * - You need fast search, insert, and remove operations
 * - You want to maintain order
 * 
 * Use unordered_set/unordered_map when:
 * - You need very fast search, insert, and remove operations
 * - You don't need sorted order
 * - You have a good hash function
 * 
 * Use stack when:
 * - You need LIFO (Last In, First Out) behavior
 * - Function call management, undo operations
 * 
 * Use queue when:
 * - You need FIFO (First In, First Out) behavior
 * - Task scheduling, breadth-first search
 * 
 * Use priority_queue when:
 * - You need to process elements by priority
 * - Dijkstra's algorithm, heap operations
 * 
 * ============================================================================
 * PERFORMANCE CHARACTERISTICS:
 * ============================================================================
 * 
 * Time Complexities:
 * - vector: access O(1), insert/remove end O(1), insert/remove middle O(n)
 * - deque: access O(1), insert/remove ends O(1), insert/remove middle O(n)
 * - list: access O(n), insert/remove anywhere O(1)
 * - set/map: search/insert/remove O(log n)
 * - unordered_set/map: search/insert/remove O(1) average, O(n) worst case
 * - stack/queue: push/pop O(1)
 * - priority_queue: push/pop O(log n)
 * 
 * Space Complexities:
 * - All containers: O(n) where n is number of elements
 * - Additional overhead varies by container type
 * 
 * ============================================================================
 * BEST PRACTICES:
 * ============================================================================
 * 
 * 1. Use range-based for loops when possible (C++11)
 * 2. Prefer emplace over insert/push for better performance
 * 3. Use const iterators when you don't modify elements
 * 4. Reserve space for vectors when you know the size
 * 5. Use unordered containers for better average performance
 * 6. Be careful with iterator invalidation
 * 7. Use appropriate container for your use case
 * 8. Consider cache locality for performance-critical code
 * 9. Use auto for iterator types to avoid complexity
 * 10. Prefer STL algorithms over hand-written loops
 * 
 * ============================================================================
 */
