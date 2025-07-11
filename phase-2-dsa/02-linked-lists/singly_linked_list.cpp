/*
 * SINGLY LINKED LIST - COMPREHENSIVE IMPLEMENTATION
 * ===============================================
 * 
 * This file provides a complete implementation of singly linked lists with
 * detailed explanations, operations, and algorithms commonly used in interviews
 * and competitive programming.
 * 
 * TOPICS COVERED:
 * 1. Node structure and basic operations
 * 2. Insertion (head, tail, middle)
 * 3. Deletion (head, tail, middle, by value)
 * 4. Traversal and searching
 * 5. Reversal algorithms
 * 6. Cycle detection and removal
 * 7. Merging and sorting
 * 8. Advanced operations
 * 
 * LEARNING OBJECTIVES:
 * - Master linked list fundamentals
 * - Understand pointer manipulation
 * - Implement efficient algorithms
 * - Solve complex linked list problems
 * 
 * PREREQUISITES:
 * - Basic C++ knowledge
 * - Understanding of pointers
 * - Familiarity with dynamic memory allocation
 */

#include <iostream>
#include <vector>
#include <unordered_set>
#include <stack>
#include <algorithm>

using namespace std;

// ========================================================================
// 1. NODE STRUCTURE AND BASIC DEFINITIONS
// ========================================================================

/*
 * THEORY: Singly Linked List Node
 * 
 * A singly linked list node contains:
 * - Data: The value stored in the node
 * - Next: Pointer to the next node in the sequence
 * 
 * Advantages:
 * - Dynamic size
 * - Efficient insertion/deletion at head
 * - No memory waste (only allocates what's needed)
 * 
 * Disadvantages:
 * - No random access (must traverse from head)
 * - Extra memory for storing pointers
 * - Not cache-friendly due to non-contiguous memory
 */

struct ListNode {
    int val;
    ListNode* next;
    
    // Constructors
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

// ========================================================================
// 2. SINGLY LINKED LIST CLASS IMPLEMENTATION
// ========================================================================

class SinglyLinkedList {
private:
    ListNode* head;
    int size;
    
public:
    // Constructor
    SinglyLinkedList() : head(nullptr), size(0) {}
    
    // Destructor
    ~SinglyLinkedList() {
        clear();
    }
    
    // Copy constructor
    SinglyLinkedList(const SinglyLinkedList& other) : head(nullptr), size(0) {
        ListNode* current = other.head;
        while (current) {
            insertTail(current->val);
            current = current->next;
        }
    }
    
    // Assignment operator
    SinglyLinkedList& operator=(const SinglyLinkedList& other) {
        if (this != &other) {
            clear();
            ListNode* current = other.head;
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
        ListNode* newNode = new ListNode(val);
        newNode->next = head;
        head = newNode;
        size++;
    }
    
    // Insert at tail - O(n)
    void insertTail(int val) {
        ListNode* newNode = new ListNode(val);
        
        if (!head) {
            head = newNode;
        } else {
            ListNode* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
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
        
        ListNode* newNode = new ListNode(val);
        ListNode* current = head;
        
        for (int i = 0; i < pos - 1; i++) {
            current = current->next;
        }
        
        newNode->next = current->next;
        current->next = newNode;
        size++;
    }
    
    // Delete head - O(1)
    bool deleteHead() {
        if (!head) return false;
        
        ListNode* temp = head;
        head = head->next;
        delete temp;
        size--;
        return true;
    }
    
    // Delete tail - O(n)
    bool deleteTail() {
        if (!head) return false;
        
        if (!head->next) {
            delete head;
            head = nullptr;
            size--;
            return true;
        }
        
        ListNode* current = head;
        while (current->next->next) {
            current = current->next;
        }
        
        delete current->next;
        current->next = nullptr;
        size--;
        return true;
    }
    
    // Delete at position - O(n)
    bool deleteAt(int pos) {
        if (pos < 0 || pos >= size) return false;
        
        if (pos == 0) {
            return deleteHead();
        }
        
        ListNode* current = head;
        for (int i = 0; i < pos - 1; i++) {
            current = current->next;
        }
        
        ListNode* nodeToDelete = current->next;
        current->next = nodeToDelete->next;
        delete nodeToDelete;
        size--;
        return true;
    }
    
    // Delete by value - O(n)
    bool deleteByValue(int val) {
        if (!head) return false;
        
        if (head->val == val) {
            return deleteHead();
        }
        
        ListNode* current = head;
        while (current->next && current->next->val != val) {
            current = current->next;
        }
        
        if (current->next) {
            ListNode* nodeToDelete = current->next;
            current->next = nodeToDelete->next;
            delete nodeToDelete;
            size--;
            return true;
        }
        
        return false;
    }
    
    // Search for value - O(n)
    bool search(int val) const {
        ListNode* current = head;
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
        
        ListNode* current = head;
        for (int i = 0; i < pos; i++) {
            current = current->next;
        }
        return current->val;
    }
    
    // Get size - O(1)
    int getSize() const { return size; }
    
    // Check if empty - O(1)
    bool isEmpty() const { return head == nullptr; }
    
    // Clear all nodes - O(n)
    void clear() {
        while (head) {
            ListNode* temp = head;
            head = head->next;
            delete temp;
        }
        size = 0;
    }
    
    // Display list - O(n)
    void display() const {
        ListNode* current = head;
        cout << "List: ";
        while (current) {
            cout << current->val;
            if (current->next) cout << " -> ";
            current = current->next;
        }
        cout << " -> null" << endl;
    }
    
    // Convert to vector - O(n)
    vector<int> toVector() const {
        vector<int> result;
        ListNode* current = head;
        while (current) {
            result.push_back(current->val);
            current = current->next;
        }
        return result;
    }
    
    // Get head pointer (for advanced operations)
    ListNode* getHead() const { return head; }
    
    // Set head pointer (for advanced operations)
    void setHead(ListNode* newHead) { 
        head = newHead; 
        // Recalculate size
        size = 0;
        ListNode* current = head;
        while (current) {
            size++;
            current = current->next;
        }
    }
};

// ========================================================================
// 3. ADVANCED LINKED LIST ALGORITHMS
// ========================================================================

/*
 * THEORY: Advanced Linked List Operations
 * 
 * These algorithms demonstrate important techniques:
 * - Two-pointer approach (slow/fast pointers)
 * - Recursive vs iterative solutions
 * - In-place operations
 * - Cycle detection and handling
 */

class LinkedListAlgorithms {
public:
    // Reverse linked list - Iterative O(n) time, O(1) space
    static ListNode* reverseIterative(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* current = head;
        
        while (current) {
            ListNode* next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        
        return prev;
    }
    
    // Reverse linked list - Recursive O(n) time, O(n) space
    static ListNode* reverseRecursive(ListNode* head) {
        if (!head || !head->next) return head;
        
        ListNode* newHead = reverseRecursive(head->next);
        head->next->next = head;
        head->next = nullptr;
        
        return newHead;
    }
    
    // Find middle node - O(n) time, O(1) space
    static ListNode* findMiddle(ListNode* head) {
        if (!head) return nullptr;
        
        ListNode* slow = head;
        ListNode* fast = head;
        
        while (fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        return slow;
    }
    
    // Detect cycle - Floyd's Cycle Detection O(n) time, O(1) space
    static bool hasCycle(ListNode* head) {
        if (!head || !head->next) return false;
        
        ListNode* slow = head;
        ListNode* fast = head;
        
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            
            if (slow == fast) return true;
        }
        
        return false;
    }
    
    // Find cycle start - O(n) time, O(1) space
    static ListNode* findCycleStart(ListNode* head) {
        if (!head || !head->next) return nullptr;
        
        ListNode* slow = head;
        ListNode* fast = head;
        
        // Find meeting point
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            
            if (slow == fast) break;
        }
        
        if (!fast || !fast->next) return nullptr;
        
        // Find start of cycle
        slow = head;
        while (slow != fast) {
            slow = slow->next;
            fast = fast->next;
        }
        
        return slow;
    }
    
    // Remove cycle - O(n) time, O(1) space
    static void removeCycle(ListNode* head) {
        if (!head || !head->next) return;
        
        ListNode* slow = head;
        ListNode* fast = head;
        
        // Detect cycle
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            
            if (slow == fast) break;
        }
        
        if (!fast || !fast->next) return;
        
        // Find cycle start
        slow = head;
        while (slow->next != fast->next) {
            slow = slow->next;
            fast = fast->next;
        }
        
        // Remove cycle
        fast->next = nullptr;
    }
    
    // Merge two sorted lists - O(n+m) time, O(1) space
    static ListNode* mergeSorted(ListNode* l1, ListNode* l2) {
        ListNode dummy(0);
        ListNode* current = &dummy;
        
        while (l1 && l2) {
            if (l1->val <= l2->val) {
                current->next = l1;
                l1 = l1->next;
            } else {
                current->next = l2;
                l2 = l2->next;
            }
            current = current->next;
        }
        
        current->next = l1 ? l1 : l2;
        return dummy.next;
    }
    
    // Sort linked list - Merge Sort O(n log n) time, O(log n) space
    static ListNode* sortList(ListNode* head) {
        if (!head || !head->next) return head;
        
        // Find middle and split
        ListNode* mid = findMiddle(head);
        ListNode* left = head;
        ListNode* right = mid->next;
        mid->next = nullptr;
        
        // Recursively sort both halves
        left = sortList(left);
        right = sortList(right);
        
        // Merge sorted halves
        return mergeSorted(left, right);
    }
    
    // Remove nth node from end - O(n) time, O(1) space
    static ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode dummy(0);
        dummy.next = head;
        
        ListNode* first = &dummy;
        ListNode* second = &dummy;
        
        // Move first pointer n+1 steps ahead
        for (int i = 0; i <= n; i++) {
            first = first->next;
        }
        
        // Move both pointers until first reaches end
        while (first) {
            first = first->next;
            second = second->next;
        }
        
        // Remove nth node from end
        ListNode* nodeToDelete = second->next;
        second->next = second->next->next;
        delete nodeToDelete;
        
        return dummy.next;
    }
    
    // Check if palindrome - O(n) time, O(1) space
    static bool isPalindrome(ListNode* head) {
        if (!head || !head->next) return true;
        
        // Find middle
        ListNode* slow = head;
        ListNode* fast = head;
        
        while (fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        // Reverse second half
        ListNode* secondHalf = reverseIterative(slow->next);
        
        // Compare first and second half
        ListNode* firstHalf = head;
        bool isPalin = true;
        
        while (secondHalf) {
            if (firstHalf->val != secondHalf->val) {
                isPalin = false;
                break;
            }
            firstHalf = firstHalf->next;
            secondHalf = secondHalf->next;
        }
        
        // Restore original list (optional)
        slow->next = reverseIterative(slow->next);
        
        return isPalin;
    }
    
    // Intersection of two linked lists - O(n+m) time, O(1) space
    static ListNode* getIntersection(ListNode* headA, ListNode* headB) {
        if (!headA || !headB) return nullptr;
        
        ListNode* a = headA;
        ListNode* b = headB;
        
        while (a != b) {
            a = a ? a->next : headB;
            b = b ? b->next : headA;
        }
        
        return a;
    }
    
    // Add two numbers represented as linked lists - O(max(n,m)) time, O(max(n,m)) space
    static ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode dummy(0);
        ListNode* current = &dummy;
        int carry = 0;
        
        while (l1 || l2 || carry) {
            int sum = carry;
            
            if (l1) {
                sum += l1->val;
                l1 = l1->next;
            }
            
            if (l2) {
                sum += l2->val;
                l2 = l2->next;
            }
            
            carry = sum / 10;
            current->next = new ListNode(sum % 10);
            current = current->next;
        }
        
        return dummy.next;
    }
};

// ========================================================================
// 4. UTILITY FUNCTIONS
// ========================================================================

class LinkedListUtils {
public:
    // Create linked list from vector
    static ListNode* createFromVector(const vector<int>& values) {
        if (values.empty()) return nullptr;
        
        ListNode* head = new ListNode(values[0]);
        ListNode* current = head;
        
        for (int i = 1; i < values.size(); i++) {
            current->next = new ListNode(values[i]);
            current = current->next;
        }
        
        return head;
    }
    
    // Create cycle for testing
    static void createCycle(ListNode* head, int pos) {
        if (!head || pos < 0) return;
        
        ListNode* tail = head;
        ListNode* cycleStart = nullptr;
        int index = 0;
        
        while (tail->next) {
            if (index == pos) {
                cycleStart = tail;
            }
            tail = tail->next;
            index++;
        }
        
        if (cycleStart) {
            tail->next = cycleStart;
        }
    }
    
    // Print linked list
    static void printList(ListNode* head) {
        ListNode* current = head;
        while (current) {
            cout << current->val;
            if (current->next) cout << " -> ";
            current = current->next;
        }
        cout << " -> null" << endl;
    }
    
    // Delete entire linked list
    static void deleteList(ListNode* head) {
        while (head) {
            ListNode* temp = head;
            head = head->next;
            delete temp;
        }
    }
    
    // Get length of linked list
    static int getLength(ListNode* head) {
        int length = 0;
        while (head) {
            length++;
            head = head->next;
        }
        return length;
    }
    
    // Compare two linked lists
    static bool areEqual(ListNode* l1, ListNode* l2) {
        while (l1 && l2) {
            if (l1->val != l2->val) return false;
            l1 = l1->next;
            l2 = l2->next;
        }
        return l1 == nullptr && l2 == nullptr;
    }
};

// ========================================================================
// 5. DEMONSTRATION AND TESTING
// ========================================================================

void demonstrateBasicOperations() {
    cout << "\n=== BASIC LINKED LIST OPERATIONS ===" << endl;
    
    SinglyLinkedList list;
    
    // Test insertions
    cout << "Inserting elements: ";
    list.insertHead(10);
    list.insertHead(20);
    list.insertTail(30);
    list.insertTail(40);
    list.insertAt(2, 25);
    list.display();
    
    // Test search
    cout << "Searching for 25: " << (list.search(25) ? "Found" : "Not found") << endl;
    cout << "Searching for 100: " << (list.search(100) ? "Found" : "Not found") << endl;
    
    // Test get
    cout << "Element at position 2: " << list.get(2) << endl;
    cout << "List size: " << list.getSize() << endl;
    
    // Test deletions
    cout << "Deleting head: " << (list.deleteHead() ? "Success" : "Failed") << endl;
    list.display();
    
    cout << "Deleting tail: " << (list.deleteTail() ? "Success" : "Failed") << endl;
    list.display();
    
    cout << "Deleting by value 25: " << (list.deleteByValue(25) ? "Success" : "Failed") << endl;
    list.display();
    
    cout << "Final size: " << list.getSize() << endl;
}

void demonstrateAdvancedAlgorithms() {
    cout << "\n=== ADVANCED LINKED LIST ALGORITHMS ===" << endl;
    
    // Test reverse
    vector<int> values = {1, 2, 3, 4, 5};
    ListNode* head = LinkedListUtils::createFromVector(values);
    cout << "Original: ";
    LinkedListUtils::printList(head);
    
    head = LinkedListAlgorithms::reverseIterative(head);
    cout << "Reversed: ";
    LinkedListUtils::printList(head);
    
    // Test find middle
    head = LinkedListUtils::createFromVector({1, 2, 3, 4, 5, 6});
    ListNode* middle = LinkedListAlgorithms::findMiddle(head);
    cout << "Middle of [1,2,3,4,5,6]: " << middle->val << endl;
    
    // Test palindrome
    head = LinkedListUtils::createFromVector({1, 2, 2, 1});
    cout << "Is [1,2,2,1] palindrome: " << 
         (LinkedListAlgorithms::isPalindrome(head) ? "Yes" : "No") << endl;
    
    // Test merge sorted lists
    ListNode* l1 = LinkedListUtils::createFromVector({1, 3, 5});
    ListNode* l2 = LinkedListUtils::createFromVector({2, 4, 6});
    ListNode* merged = LinkedListAlgorithms::mergeSorted(l1, l2);
    cout << "Merged sorted lists: ";
    LinkedListUtils::printList(merged);
    
    // Test cycle detection
    head = LinkedListUtils::createFromVector({1, 2, 3, 4, 5});
    LinkedListUtils::createCycle(head, 2);
    cout << "Has cycle: " << (LinkedListAlgorithms::hasCycle(head) ? "Yes" : "No") << endl;
    
    // Clean up
    LinkedListUtils::deleteList(merged);
}

void demonstrateComplexOperations() {
    cout << "\n=== COMPLEX LINKED LIST OPERATIONS ===" << endl;
    
    // Test sorting
    ListNode* head = LinkedListUtils::createFromVector({4, 2, 1, 3, 5});
    cout << "Before sorting: ";
    LinkedListUtils::printList(head);
    
    head = LinkedListAlgorithms::sortList(head);
    cout << "After sorting: ";
    LinkedListUtils::printList(head);
    
    // Test remove nth from end
    head = LinkedListUtils::createFromVector({1, 2, 3, 4, 5});
    cout << "Before removing 2nd from end: ";
    LinkedListUtils::printList(head);
    
    head = LinkedListAlgorithms::removeNthFromEnd(head, 2);
    cout << "After removing 2nd from end: ";
    LinkedListUtils::printList(head);
    
    // Test add two numbers
    ListNode* num1 = LinkedListUtils::createFromVector({2, 4, 3}); // 342
    ListNode* num2 = LinkedListUtils::createFromVector({5, 6, 4}); // 465
    ListNode* sum = LinkedListAlgorithms::addTwoNumbers(num1, num2);
    cout << "Sum of 342 + 465: ";
    LinkedListUtils::printList(sum);
    
    // Clean up
    LinkedListUtils::deleteList(head);
    LinkedListUtils::deleteList(num1);
    LinkedListUtils::deleteList(num2);
    LinkedListUtils::deleteList(sum);
}

// ========================================================================
// MAIN FUNCTION - COMPREHENSIVE DEMONSTRATION
// ========================================================================

int main() {
    cout << "SINGLY LINKED LIST - COMPREHENSIVE IMPLEMENTATION" << endl;
    cout << "================================================" << endl;
    
    try {
        demonstrateBasicOperations();
        demonstrateAdvancedAlgorithms();
        demonstrateComplexOperations();
        
        cout << "\n=== SUMMARY ===" << endl;
        cout << "✓ Basic operations (insert, delete, search)" << endl;
        cout << "✓ Advanced algorithms (reverse, cycle detection)" << endl;
        cout << "✓ Complex operations (merge, sort, palindrome)" << endl;
        cout << "✓ Utility functions for testing and debugging" << endl;
        
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}

/*
 * COMPILATION AND EXECUTION:
 * 
 * To compile: g++ -std=c++17 -O2 -o singly_linked_list singly_linked_list.cpp
 * To run: ./singly_linked_list
 * 
 * TIME COMPLEXITY SUMMARY:
 * - Insert head: O(1)
 * - Insert tail: O(n)
 * - Insert at position: O(n)
 * - Delete head: O(1)
 * - Delete tail: O(n)
 * - Delete at position: O(n)
 * - Search: O(n)
 * - Reverse: O(n)
 * - Cycle detection: O(n)
 * - Merge sorted: O(n+m)
 * - Sort: O(n log n)
 * 
 * SPACE COMPLEXITY:
 * - Most operations: O(1) auxiliary space
 * - Recursive operations: O(n) due to recursion stack
 * - Sorting: O(log n) due to recursion
 * 
 * NEXT STEPS:
 * 1. Practice implementing from memory
 * 2. Solve linked list problems on coding platforms
 * 3. Study doubly linked lists
 * 4. Learn about circular linked lists
 * 5. Explore applications in real-world scenarios
 */
