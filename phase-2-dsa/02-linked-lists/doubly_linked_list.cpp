/*
 * DOUBLY LINKED LIST - COMPREHENSIVE IMPLEMENTATION
 * ===============================================
 * 
 * This file provides a complete implementation of doubly linked lists with
 * detailed explanations, operations, and algorithms. Doubly linked lists
 * offer bidirectional traversal and more efficient operations compared to
 * singly linked lists.
 * 
 * TOPICS COVERED:
 * 1. Node structure with prev and next pointers
 * 2. Bidirectional insertion and deletion
 * 3. Forward and backward traversal
 * 4. Advanced operations (reverse, merge, sort)
 * 5. Circular doubly linked lists
 * 6. LRU Cache implementation using doubly linked list
 * 7. Deque implementation
 * 8. Memory management and optimization
 * 
 * LEARNING OBJECTIVES:
 * - Master doubly linked list fundamentals
 * - Understand bidirectional pointer manipulation
 * - Implement efficient O(1) operations
 * - Apply doubly linked lists to real-world problems
 * 
 * ADVANTAGES OVER SINGLY LINKED LISTS:
 * - Bidirectional traversal
 * - O(1) deletion when node pointer is given
 * - Easier implementation of certain algorithms
 * - Better for implementing deques and LRU caches
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stdexcept>

using namespace std;

// ========================================================================
// 1. NODE STRUCTURE AND BASIC DEFINITIONS
// ========================================================================

/*
 * THEORY: Doubly Linked List Node
 * 
 * A doubly linked list node contains:
 * - Data: The value stored in the node
 * - Next: Pointer to the next node
 * - Prev: Pointer to the previous node
 * 
 * This bidirectional linking allows:
 * - Traversal in both directions
 * - O(1) deletion when node pointer is known
 * - Easier implementation of certain algorithms
 */

struct DLLNode {
    int val;
    DLLNode* next;
    DLLNode* prev;
    
    // Constructors
    DLLNode() : val(0), next(nullptr), prev(nullptr) {}
    DLLNode(int x) : val(x), next(nullptr), prev(nullptr) {}
    DLLNode(int x, DLLNode* prev, DLLNode* next) 
        : val(x), next(next), prev(prev) {}
};

// ========================================================================
// 2. DOUBLY LINKED LIST CLASS IMPLEMENTATION
// ========================================================================

class DoublyLinkedList {
private:
    DLLNode* head;
    DLLNode* tail;
    int size;
    
public:
    // Constructor
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}
    
    // Destructor
    ~DoublyLinkedList() {
        clear();
    }
    
    // Copy constructor
    DoublyLinkedList(const DoublyLinkedList& other) 
        : head(nullptr), tail(nullptr), size(0) {
        DLLNode* current = other.head;
        while (current) {
            insertTail(current->val);
            current = current->next;
        }
    }
    
    // Assignment operator
    DoublyLinkedList& operator=(const DoublyLinkedList& other) {
        if (this != &other) {
            clear();
            DLLNode* current = other.head;
            while (current) {
                insertTail(current->val);
                current = current->next;
            }
        }
        return *this;
    }
    
    // ====================================================================
    // BASIC OPERATIONS
    // ====================================================================
    
    // Insert at head - O(1)
    void insertHead(int val) {
        DLLNode* newNode = new DLLNode(val);
        
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        size++;
    }
    
    // Insert at tail - O(1)
    void insertTail(int val) {
        DLLNode* newNode = new DLLNode(val);
        
        if (!tail) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
    }
    
    // Insert at position - O(n)
    void insertAt(int pos, int val) {
        if (pos < 0 || pos > size) {
            throw out_of_range("Position out of bounds");
        }
        
        if (pos == 0) {
            insertHead(val);
            return;
        }
        
        if (pos == size) {
            insertTail(val);
            return;
        }
        
        DLLNode* newNode = new DLLNode(val);
        DLLNode* current = getNodeAt(pos);
        
        newNode->next = current;
        newNode->prev = current->prev;
        current->prev->next = newNode;
        current->prev = newNode;
        size++;
    }
    
    // Delete head - O(1)
    bool deleteHead() {
        if (!head) return false;
        
        DLLNode* temp = head;
        
        if (head == tail) {
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }
        
        delete temp;
        size--;
        return true;
    }
    
    // Delete tail - O(1)
    bool deleteTail() {
        if (!tail) return false;
        
        DLLNode* temp = tail;
        
        if (head == tail) {
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        
        delete temp;
        size--;
        return true;
    }
    
    // Delete at position - O(n)
    bool deleteAt(int pos) {
        if (pos < 0 || pos >= size) return false;
        
        if (pos == 0) return deleteHead();
        if (pos == size - 1) return deleteTail();
        
        DLLNode* nodeToDelete = getNodeAt(pos);
        nodeToDelete->prev->next = nodeToDelete->next;
        nodeToDelete->next->prev = nodeToDelete->prev;
        
        delete nodeToDelete;
        size--;
        return true;
    }
    
    // Delete node directly - O(1)
    bool deleteNode(DLLNode* node) {
        if (!node) return false;
        
        if (node == head) return deleteHead();
        if (node == tail) return deleteTail();
        
        node->prev->next = node->next;
        node->next->prev = node->prev;
        
        delete node;
        size--;
        return true;
    }
    
    // Delete by value - O(n)
    bool deleteByValue(int val) {
        DLLNode* current = head;
        
        while (current) {
            if (current->val == val) {
                return deleteNode(current);
            }
            current = current->next;
        }
        
        return false;
    }
    
    // Search for value - O(n)
    bool search(int val) const {
        DLLNode* current = head;
        while (current) {
            if (current->val == val) return true;
            current = current->next;
        }
        return false;
    }
    
    // Get value at position - O(n)
    int get(int pos) const {
        if (pos < 0 || pos >= size) {
            throw out_of_range("Position out of bounds");
        }
        
        DLLNode* node = getNodeAt(pos);
        return node->val;
    }
    
    // Get size - O(1)
    int getSize() const { return size; }
    
    // Check if empty - O(1)
    bool isEmpty() const { return head == nullptr; }
    
    // Clear all nodes - O(n)
    void clear() {
        while (head) {
            DLLNode* temp = head;
            head = head->next;
            delete temp;
        }
        head = tail = nullptr;
        size = 0;
    }
    
    // Display list forward - O(n)
    void displayForward() const {
        DLLNode* current = head;
        cout << "Forward: ";
        while (current) {
            cout << current->val;
            if (current->next) cout << " <-> ";
            current = current->next;
        }
        cout << " <-> null" << endl;
    }
    
    // Display list backward - O(n)
    void displayBackward() const {
        DLLNode* current = tail;
        cout << "Backward: ";
        while (current) {
            cout << current->val;
            if (current->prev) cout << " <-> ";
            current = current->prev;
        }
        cout << " <-> null" << endl;
    }
    
    // Get head pointer
    DLLNode* getHead() const { return head; }
    
    // Get tail pointer
    DLLNode* getTail() const { return tail; }
    
private:
    // Helper function to get node at position - O(n)
    DLLNode* getNodeAt(int pos) const {
        if (pos < 0 || pos >= size) return nullptr;
        
        DLLNode* current;
        
        // Choose direction based on position
        if (pos < size / 2) {
            // Start from head
            current = head;
            for (int i = 0; i < pos; i++) {
                current = current->next;
            }
        } else {
            // Start from tail
            current = tail;
            for (int i = size - 1; i > pos; i--) {
                current = current->prev;
            }
        }
        
        return current;
    }
};

// ========================================================================
// 3. ADVANCED DOUBLY LINKED LIST ALGORITHMS
// ========================================================================

class DoublyLinkedListAlgorithms {
public:
    // Reverse doubly linked list - O(n) time, O(1) space
    static DLLNode* reverse(DLLNode* head) {
        if (!head) return nullptr;
        
        DLLNode* current = head;
        DLLNode* temp = nullptr;
        
        while (current) {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev;
        }
        
        return temp ? temp->prev : head;
    }
    
    // Find middle node - O(n) time, O(1) space
    static DLLNode* findMiddle(DLLNode* head) {
        if (!head) return nullptr;
        
        DLLNode* slow = head;
        DLLNode* fast = head;
        
        while (fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        return slow;
    }
    
    // Merge two sorted doubly linked lists - O(n+m) time, O(1) space
    static DLLNode* mergeSorted(DLLNode* l1, DLLNode* l2) {
        if (!l1) return l2;
        if (!l2) return l1;
        
        DLLNode* result = nullptr;
        
        if (l1->val <= l2->val) {
            result = l1;
            result->next = mergeSorted(l1->next, l2);
            if (result->next) result->next->prev = result;
        } else {
            result = l2;
            result->next = mergeSorted(l1, l2->next);
            if (result->next) result->next->prev = result;
        }
        
        return result;
    }
    
    // Sort doubly linked list - Merge Sort O(n log n) time, O(log n) space
    static DLLNode* sortList(DLLNode* head) {
        if (!head || !head->next) return head;
        
        // Find middle and split
        DLLNode* mid = findMiddle(head);
        DLLNode* right = mid->next;
        
        // Break the link
        mid->next = nullptr;
        if (right) right->prev = nullptr;
        
        // Recursively sort both halves
        DLLNode* left = sortList(head);
        right = sortList(right);
        
        // Merge sorted halves
        return mergeSorted(left, right);
    }
    
    // Convert binary tree to doubly linked list - In-order traversal
    static DLLNode* treeToDoublyList(DLLNode* root) {
        if (!root) return nullptr;
        
        DLLNode* head = nullptr;
        DLLNode* prev = nullptr;
        
        inorderTraversal(root, head, prev);
        
        return head;
    }
    
    // Quick sort for doubly linked list - O(n log n) average, O(n²) worst
    static DLLNode* quickSort(DLLNode* head) {
        if (!head || !head->next) return head;
        
        DLLNode* tail = getTail(head);
        quickSortUtil(head, tail);
        
        return head;
    }
    
    // Remove duplicates from sorted doubly linked list - O(n) time, O(1) space
    static DLLNode* removeDuplicates(DLLNode* head) {
        if (!head) return nullptr;
        
        DLLNode* current = head;
        
        while (current && current->next) {
            if (current->val == current->next->val) {
                DLLNode* nodeToDelete = current->next;
                current->next = nodeToDelete->next;
                if (nodeToDelete->next) {
                    nodeToDelete->next->prev = current;
                }
                delete nodeToDelete;
            } else {
                current = current->next;
            }
        }
        
        return head;
    }
    
    // Rotate doubly linked list - O(n) time, O(1) space
    static DLLNode* rotate(DLLNode* head, int k) {
        if (!head || k == 0) return head;
        
        // Find length and tail
        int length = 1;
        DLLNode* tail = head;
        while (tail->next) {
            tail = tail->next;
            length++;
        }
        
        k = k % length;
        if (k == 0) return head;
        
        // Find new head
        DLLNode* newTail = head;
        for (int i = 0; i < length - k - 1; i++) {
            newTail = newTail->next;
        }
        
        DLLNode* newHead = newTail->next;
        
        // Break and reconnect
        newTail->next = nullptr;
        newHead->prev = nullptr;
        tail->next = head;
        head->prev = tail;
        
        return newHead;
    }
    
private:
    // Helper function for tree to doubly list conversion
    static void inorderTraversal(DLLNode* root, DLLNode*& head, DLLNode*& prev) {
        if (!root) return;
        
        inorderTraversal(root->prev, head, prev);
        
        if (!head) {
            head = root;
        } else {
            prev->next = root;
            root->prev = prev;
        }
        prev = root;
        
        inorderTraversal(root->next, head, prev);
    }
    
    // Helper function to get tail
    static DLLNode* getTail(DLLNode* head) {
        while (head && head->next) {
            head = head->next;
        }
        return head;
    }
    
    // Helper function for quick sort
    static void quickSortUtil(DLLNode* low, DLLNode* high) {
        if (high && low != high && low != high->next) {
            DLLNode* pi = partition(low, high);
            quickSortUtil(low, pi->prev);
            quickSortUtil(pi->next, high);
        }
    }
    
    // Partition function for quick sort
    static DLLNode* partition(DLLNode* low, DLLNode* high) {
        int pivot = high->val;
        DLLNode* i = low->prev;
        
        for (DLLNode* j = low; j != high; j = j->next) {
            if (j->val <= pivot) {
                i = (i == nullptr) ? low : i->next;
                swap(i->val, j->val);
            }
        }
        
        i = (i == nullptr) ? low : i->next;
        swap(i->val, high->val);
        
        return i;
    }
};

// ========================================================================
// 4. LRU CACHE IMPLEMENTATION USING DOUBLY LINKED LIST
// ========================================================================

/*
 * THEORY: LRU (Least Recently Used) Cache
 * 
 * LRU Cache is a cache replacement policy that removes the least recently
 * used items first. Doubly linked list is perfect for this because:
 * - O(1) insertion and deletion at both ends
 * - O(1) removal of any node (when pointer is available)
 * - Easy to move nodes to front/back
 */

class LRUCache {
private:
    struct CacheNode {
        int key, value;
        CacheNode* prev;
        CacheNode* next;
        
        CacheNode(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
    };
    
    unordered_map<int, CacheNode*> cache;
    CacheNode* head;
    CacheNode* tail;
    int capacity;
    
public:
    LRUCache(int cap) : capacity(cap) {
        head = new CacheNode(0, 0);
        tail = new CacheNode(0, 0);
        head->next = tail;
        tail->prev = head;
    }
    
    ~LRUCache() {
        while (head) {
            CacheNode* temp = head;
            head = head->next;
            delete temp;
        }
    }
    
    int get(int key) {
        if (cache.find(key) != cache.end()) {
            CacheNode* node = cache[key];
            moveToHead(node);
            return node->value;
        }
        return -1;
    }
    
    void put(int key, int value) {
        if (cache.find(key) != cache.end()) {
            CacheNode* node = cache[key];
            node->value = value;
            moveToHead(node);
        } else {
            CacheNode* newNode = new CacheNode(key, value);
            
            if (cache.size() >= capacity) {
                CacheNode* tail_node = removeTail();
                cache.erase(tail_node->key);
                delete tail_node;
            }
            
            cache[key] = newNode;
            addToHead(newNode);
        }
    }
    
    void display() {
        cout << "LRU Cache (most recent -> least recent): ";
        CacheNode* current = head->next;
        while (current != tail) {
            cout << "(" << current->key << "," << current->value << ") ";
            current = current->next;
        }
        cout << endl;
    }
    
private:
    void addToHead(CacheNode* node) {
        node->prev = head;
        node->next = head->next;
        head->next->prev = node;
        head->next = node;
    }
    
    void removeNode(CacheNode* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    
    void moveToHead(CacheNode* node) {
        removeNode(node);
        addToHead(node);
    }
    
    CacheNode* removeTail() {
        CacheNode* lastNode = tail->prev;
        removeNode(lastNode);
        return lastNode;
    }
};

// ========================================================================
// 5. DEQUE IMPLEMENTATION USING DOUBLY LINKED LIST
// ========================================================================

/*
 * THEORY: Deque (Double-ended queue)
 * 
 * A deque allows insertion and deletion at both ends in O(1) time.
 * Doubly linked list is ideal for this implementation.
 */

class Deque {
private:
    DoublyLinkedList dll;
    
public:
    // Add element to front - O(1)
    void pushFront(int val) {
        dll.insertHead(val);
    }
    
    // Add element to back - O(1)
    void pushBack(int val) {
        dll.insertTail(val);
    }
    
    // Remove element from front - O(1)
    bool popFront() {
        return dll.deleteHead();
    }
    
    // Remove element from back - O(1)
    bool popBack() {
        return dll.deleteTail();
    }
    
    // Get front element - O(1)
    int front() {
        if (dll.isEmpty()) throw runtime_error("Deque is empty");
        return dll.getHead()->val;
    }
    
    // Get back element - O(1)
    int back() {
        if (dll.isEmpty()) throw runtime_error("Deque is empty");
        return dll.getTail()->val;
    }
    
    // Check if empty - O(1)
    bool empty() {
        return dll.isEmpty();
    }
    
    // Get size - O(1)
    int size() {
        return dll.getSize();
    }
    
    // Display deque
    void display() {
        dll.displayForward();
    }
};

// ========================================================================
// 6. UTILITY FUNCTIONS
// ========================================================================

class DoublyLinkedListUtils {
public:
    // Create doubly linked list from vector
    static DLLNode* createFromVector(const vector<int>& values) {
        if (values.empty()) return nullptr;
        
        DLLNode* head = new DLLNode(values[0]);
        DLLNode* current = head;
        
        for (int i = 1; i < values.size(); i++) {
            DLLNode* newNode = new DLLNode(values[i]);
            current->next = newNode;
            newNode->prev = current;
            current = newNode;
        }
        
        return head;
    }
    
    // Print doubly linked list
    static void printList(DLLNode* head) {
        DLLNode* current = head;
        cout << "Forward: ";
        while (current) {
            cout << current->val;
            if (current->next) cout << " <-> ";
            current = current->next;
        }
        cout << " <-> null" << endl;
    }
    
    // Delete entire doubly linked list
    static void deleteList(DLLNode* head) {
        while (head) {
            DLLNode* temp = head;
            head = head->next;
            delete temp;
        }
    }
    
    // Get length of doubly linked list
    static int getLength(DLLNode* head) {
        int length = 0;
        while (head) {
            length++;
            head = head->next;
        }
        return length;
    }
    
    // Convert to vector
    static vector<int> toVector(DLLNode* head) {
        vector<int> result;
        while (head) {
            result.push_back(head->val);
            head = head->next;
        }
        return result;
    }
};

// ========================================================================
// 7. DEMONSTRATION AND TESTING
// ========================================================================

void demonstrateBasicOperations() {
    cout << "\n=== BASIC DOUBLY LINKED LIST OPERATIONS ===" << endl;
    
    DoublyLinkedList dll;
    
    // Test insertions
    cout << "Inserting elements: ";
    dll.insertHead(10);
    dll.insertHead(20);
    dll.insertTail(30);
    dll.insertTail(40);
    dll.insertAt(2, 25);
    dll.displayForward();
    dll.displayBackward();
    
    // Test deletions
    cout << "Deleting head: " << (dll.deleteHead() ? "Success" : "Failed") << endl;
    dll.displayForward();
    
    cout << "Deleting tail: " << (dll.deleteTail() ? "Success" : "Failed") << endl;
    dll.displayForward();
    
    cout << "Size: " << dll.getSize() << endl;
}

void demonstrateAdvancedAlgorithms() {
    cout << "\n=== ADVANCED DOUBLY LINKED LIST ALGORITHMS ===" << endl;
    
    // Test reverse
    vector<int> values = {1, 2, 3, 4, 5};
    DLLNode* head = DoublyLinkedListUtils::createFromVector(values);
    cout << "Original: ";
    DoublyLinkedListUtils::printList(head);
    
    head = DoublyLinkedListAlgorithms::reverse(head);
    cout << "Reversed: ";
    DoublyLinkedListUtils::printList(head);
    
    // Test sorting
    head = DoublyLinkedListUtils::createFromVector({4, 2, 1, 3, 5});
    cout << "Before sorting: ";
    DoublyLinkedListUtils::printList(head);
    
    head = DoublyLinkedListAlgorithms::sortList(head);
    cout << "After sorting: ";
    DoublyLinkedListUtils::printList(head);
    
    // Clean up
    DoublyLinkedListUtils::deleteList(head);
}

void demonstrateLRUCache() {
    cout << "\n=== LRU CACHE DEMONSTRATION ===" << endl;
    
    LRUCache cache(3);
    
    cache.put(1, 10);
    cache.put(2, 20);
    cache.put(3, 30);
    cache.display();
    
    cout << "Get key 2: " << cache.get(2) << endl;
    cache.display();
    
    cache.put(4, 40);  // Should evict key 1
    cache.display();
    
    cout << "Get key 1: " << cache.get(1) << endl;  // Should return -1
    cout << "Get key 3: " << cache.get(3) << endl;
    cache.display();
}

void demonstrateDeque() {
    cout << "\n=== DEQUE DEMONSTRATION ===" << endl;
    
    Deque dq;
    
    dq.pushBack(10);
    dq.pushBack(20);
    dq.pushFront(5);
    dq.pushFront(1);
    
    cout << "After pushes: ";
    dq.display();
    
    cout << "Front: " << dq.front() << ", Back: " << dq.back() << endl;
    
    dq.popFront();
    dq.popBack();
    
    cout << "After pops: ";
    dq.display();
    
    cout << "Size: " << dq.size() << endl;
}

// ========================================================================
// MAIN FUNCTION - COMPREHENSIVE DEMONSTRATION
// ========================================================================

int main() {
    cout << "DOUBLY LINKED LIST - COMPREHENSIVE IMPLEMENTATION" << endl;
    cout << "================================================" << endl;
    
    try {
        demonstrateBasicOperations();
        demonstrateAdvancedAlgorithms();
        demonstrateLRUCache();
        demonstrateDeque();
        
        cout << "\n=== SUMMARY ===" << endl;
        cout << "✓ Basic operations with O(1) head/tail operations" << endl;
        cout << "✓ Bidirectional traversal capabilities" << endl;
        cout << "✓ Advanced algorithms (reverse, sort, merge)" << endl;
        cout << "✓ LRU Cache implementation" << endl;
        cout << "✓ Deque implementation" << endl;
        cout << "✓ Efficient memory management" << endl;
        
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}

/*
 * COMPILATION AND EXECUTION:
 * 
 * To compile: g++ -std=c++17 -O2 -o doubly_linked_list doubly_linked_list.cpp
 * To run: ./doubly_linked_list
 * 
 * TIME COMPLEXITY COMPARISON:
 * 
 * Operation           | Singly LL | Doubly LL
 * --------------------|-----------|----------
 * Insert head         | O(1)      | O(1)
 * Insert tail         | O(n)      | O(1)
 * Delete head         | O(1)      | O(1)
 * Delete tail         | O(n)      | O(1)
 * Delete given node   | O(n)      | O(1)
 * Search              | O(n)      | O(n)
 * Reverse             | O(n)      | O(n)
 * 
 * SPACE COMPLEXITY:
 * - Each node: 12 bytes (4 for data + 8 for two pointers on 64-bit)
 * - vs Singly LL: 8 bytes (4 for data + 4 for one pointer on 64-bit)
 * - Trade-off: 50% more memory for better time complexity
 * 
 * APPLICATIONS:
 * - LRU Cache implementation
 * - Deque (double-ended queue)
 * - Undo/Redo operations
 * - Navigation systems (back/forward)
 * - Music players (previous/next)
 * - Browser history
 * 
 * NEXT STEPS:
 * 1. Practice implementing from memory
 * 2. Solve doubly linked list problems
 * 3. Study circular doubly linked lists
 * 4. Implement more advanced data structures
 * 5. Optimize for specific use cases
 */
