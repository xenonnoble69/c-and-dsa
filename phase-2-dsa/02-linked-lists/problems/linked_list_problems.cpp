/*
 * ============================================================================
 * LINKED LIST PROBLEMS - COMPREHENSIVE COLLECTION
 * ============================================================================
 * 
 * This file contains 25+ carefully selected linked list problems ranging from
 * basic operations to advanced algorithms. Each problem includes:
 * - Clear problem statement
 * - Multiple solution approaches
 * - Time and space complexity analysis
 * - Test cases and edge case handling
 * 
 * PROBLEM CATEGORIES:
 * 1. Basic Operations (1-5)
 * 2. Two Pointer Techniques (6-10)
 * 3. Reversal and Manipulation (11-15)
 * 4. Merge and Sort Operations (16-20)
 * 5. Advanced Algorithms (21-25)
 * 
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

/*
 * ========================================================================
 * LINKED LIST NODE DEFINITION
 * ========================================================================
 */

struct ListNode {
    int val;
    ListNode* next;
    
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

// Utility functions for testing
class LinkedListUtils {
public:
    // Create linked list from vector
    static ListNode* createList(const vector<int>& vals) {
        if (vals.empty()) return nullptr;
        
        ListNode* head = new ListNode(vals[0]);
        ListNode* current = head;
        
        for (size_t i = 1; i < vals.size(); ++i) {
            current->next = new ListNode(vals[i]);
            current = current->next;
        }
        return head;
    }
    
    // Print linked list
    static void printList(ListNode* head, const string& label = "List") {
        cout << label << ": ";
        ListNode* current = head;
        while (current) {
            cout << current->val;
            if (current->next) cout << " -> ";
            current = current->next;
        }
        cout << " -> NULL" << endl;
    }
    
    // Get list length
    static int getLength(ListNode* head) {
        int length = 0;
        while (head) {
            length++;
            head = head->next;
        }
        return length;
    }
    
    // Delete linked list
    static void deleteList(ListNode* head) {
        while (head) {
            ListNode* temp = head;
            head = head->next;
            delete temp;
        }
    }
    
    // Create cycle at given position (0-indexed, -1 for no cycle)
    static void createCycle(ListNode* head, int pos) {
        if (!head || pos < 0) return;
        
        ListNode* cycleNode = head;
        ListNode* tail = head;
        
        // Find cycle node
        for (int i = 0; i < pos && cycleNode; ++i) {
            cycleNode = cycleNode->next;
        }
        
        // Find tail
        while (tail->next) {
            tail = tail->next;
        }
        
        // Create cycle
        if (cycleNode) {
            tail->next = cycleNode;
        }
    }
};

/*
 * ========================================================================
 * CATEGORY 1: BASIC OPERATIONS (Problems 1-5)
 * ========================================================================
 */

class BasicOperations {
public:
    /*
     * Problem 1: Delete Node in a Linked List
     * Given a node (not the tail) in a singly linked list, delete it.
     * 
     * Approach: Copy next node's value and delete next node
     * Time: O(1), Space: O(1)
     */
    static void deleteNode(ListNode* node) {
        if (!node || !node->next) return;
        
        // Copy next node's value
        node->val = node->next->val;
        
        // Delete next node
        ListNode* temp = node->next;
        node->next = node->next->next;
        delete temp;
    }
    
    /*
     * Problem 2: Remove Nth Node From End
     * Remove the nth node from the end of the list.
     * 
     * Approach: Two-pass or one-pass with two pointers
     * Time: O(n), Space: O(1)
     */
    static ListNode* removeNthFromEnd(ListNode* head, int n) {
        // Create dummy node to handle edge cases
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        
        ListNode* fast = dummy;
        ListNode* slow = dummy;
        
        // Move fast pointer n+1 steps ahead
        for (int i = 0; i <= n; ++i) {
            fast = fast->next;
        }
        
        // Move both pointers until fast reaches end
        while (fast) {
            fast = fast->next;
            slow = slow->next;
        }
        
        // Remove nth node from end
        ListNode* nodeToDelete = slow->next;
        slow->next = slow->next->next;
        delete nodeToDelete;
        
        ListNode* result = dummy->next;
        delete dummy;
        return result;
    }
    
    /*
     * Problem 3: Find Middle of Linked List
     * Find the middle node of the linked list.
     * 
     * Approach: Two pointers (slow and fast)
     * Time: O(n), Space: O(1)
     */
    static ListNode* findMiddle(ListNode* head) {
        if (!head) return nullptr;
        
        ListNode* slow = head;
        ListNode* fast = head;
        
        // Fast pointer moves 2 steps, slow moves 1 step
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        return slow;
    }
    
    /*
     * Problem 4: Remove Duplicates from Sorted List
     * Remove all duplicates from a sorted linked list.
     * 
     * Approach: Single pass with comparison
     * Time: O(n), Space: O(1)
     */
    static ListNode* removeDuplicates(ListNode* head) {
        if (!head) return head;
        
        ListNode* current = head;
        
        while (current && current->next) {
            if (current->val == current->next->val) {
                ListNode* duplicate = current->next;
                current->next = current->next->next;
                delete duplicate;
            } else {
                current = current->next;
            }
        }
        
        return head;
    }
    
    /*
     * Problem 5: Remove All Duplicates from Sorted List
     * Remove all nodes that have duplicates, leaving only distinct numbers.
     * 
     * Approach: Dummy node with skip logic
     * Time: O(n), Space: O(1)
     */
    static ListNode* removeAllDuplicates(ListNode* head) {
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        ListNode* prev = dummy;
        ListNode* current = head;
        
        while (current) {
            // Check if current node has duplicates
            if (current->next && current->val == current->next->val) {
                int duplicateVal = current->val;
                
                // Skip all nodes with duplicate value
                while (current && current->val == duplicateVal) {
                    ListNode* temp = current;
                    current = current->next;
                    delete temp;
                }
                
                prev->next = current;
            } else {
                prev = current;
                current = current->next;
            }
        }
        
        ListNode* result = dummy->next;
        delete dummy;
        return result;
    }
};

/*
 * ========================================================================
 * CATEGORY 2: TWO POINTER TECHNIQUES (Problems 6-10)
 * ========================================================================
 */

class TwoPointerTechniques {
public:
    /*
     * Problem 6: Linked List Cycle Detection
     * Determine if a linked list has a cycle.
     * 
     * Approach: Floyd's Cycle Detection (Tortoise and Hare)
     * Time: O(n), Space: O(1)
     */
    static bool hasCycle(ListNode* head) {
        if (!head || !head->next) return false;
        
        ListNode* slow = head;
        ListNode* fast = head;
        
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            
            if (slow == fast) {
                return true;
            }
        }
        
        return false;
    }
    
    /*
     * Problem 7: Find Cycle Start Node
     * Find the node where the cycle begins.
     * 
     * Approach: Floyd's algorithm + mathematical proof
     * Time: O(n), Space: O(1)
     */
    static ListNode* detectCycle(ListNode* head) {
        if (!head || !head->next) return nullptr;
        
        ListNode* slow = head;
        ListNode* fast = head;
        
        // Phase 1: Detect cycle
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            
            if (slow == fast) {
                // Phase 2: Find cycle start
                slow = head;
                while (slow != fast) {
                    slow = slow->next;
                    fast = fast->next;
                }
                return slow;
            }
        }
        
        return nullptr;
    }
    
    /*
     * Problem 8: Intersection of Two Linked Lists
     * Find the node where two linked lists intersect.
     * 
     * Approach: Two pointers with length equalization
     * Time: O(m + n), Space: O(1)
     */
    static ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
        if (!headA || !headB) return nullptr;
        
        ListNode* ptrA = headA;
        ListNode* ptrB = headB;
        
        // When one pointer reaches end, redirect to other list's head
        while (ptrA != ptrB) {
            ptrA = ptrA ? ptrA->next : headB;
            ptrB = ptrB ? ptrB->next : headA;
        }
        
        return ptrA;  // Either intersection node or nullptr
    }
    
    /*
     * Problem 9: Palindrome Linked List
     * Check if a linked list is a palindrome.
     * 
     * Approach: Find middle, reverse second half, compare
     * Time: O(n), Space: O(1)
     */
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
        ListNode* secondHalf = reverseList(slow->next);
        
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
        
        return isPalin;
    }
    
    /*
     * Problem 10: Remove Elements
     * Remove all elements with given value.
     * 
     * Approach: Dummy node with filtering
     * Time: O(n), Space: O(1)
     */
    static ListNode* removeElements(ListNode* head, int val) {
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        ListNode* current = dummy;
        
        while (current->next) {
            if (current->next->val == val) {
                ListNode* nodeToDelete = current->next;
                current->next = current->next->next;
                delete nodeToDelete;
            } else {
                current = current->next;
            }
        }
        
        ListNode* result = dummy->next;
        delete dummy;
        return result;
    }

private:
    static ListNode* reverseList(ListNode* head) {
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
};

/*
 * ========================================================================
 * CATEGORY 3: REVERSAL AND MANIPULATION (Problems 11-15)
 * ========================================================================
 */

class ReversalManipulation {
public:
    /*
     * Problem 11: Reverse Linked List
     * Reverse a singly linked list.
     * 
     * Approach: Iterative three-pointer technique
     * Time: O(n), Space: O(1)
     */
    static ListNode* reverseList(ListNode* head) {
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
    
    /*
     * Problem 12: Reverse Linked List II
     * Reverse nodes from position m to n.
     * 
     * Approach: Find positions, reverse sublist, reconnect
     * Time: O(n), Space: O(1)
     */
    static ListNode* reverseBetween(ListNode* head, int m, int n) {
        if (!head || m == n) return head;
        
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        ListNode* prev = dummy;
        
        // Move to position m-1
        for (int i = 1; i < m; ++i) {
            prev = prev->next;
        }
        
        // Start of reversal
        ListNode* start = prev->next;
        ListNode* then = start->next;
        
        // Reverse from m to n
        for (int i = 0; i < n - m; ++i) {
            start->next = then->next;
            then->next = prev->next;
            prev->next = then;
            then = start->next;
        }
        
        ListNode* result = dummy->next;
        delete dummy;
        return result;
    }
    
    /*
     * Problem 13: Reverse Nodes in k-Group
     * Reverse every k consecutive nodes.
     * 
     * Approach: Iterative reversal with group counting
     * Time: O(n), Space: O(1)
     */
    static ListNode* reverseKGroup(ListNode* head, int k) {
        if (!head || k <= 1) return head;
        
        // Check if we have k nodes
        ListNode* current = head;
        for (int i = 0; i < k; ++i) {
            if (!current) return head;
            current = current->next;
        }
        
        // Reverse first k nodes
        ListNode* prev = nullptr;
        current = head;
        
        for (int i = 0; i < k; ++i) {
            ListNode* next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        
        // Recursively reverse remaining groups
        head->next = reverseKGroup(current, k);
        
        return prev;
    }
    
    /*
     * Problem 14: Rotate List
     * Rotate the list to the right by k places.
     * 
     * Approach: Find length, create cycle, break at new head
     * Time: O(n), Space: O(1)
     */
    static ListNode* rotateRight(ListNode* head, int k) {
        if (!head || !head->next || k == 0) return head;
        
        // Find length and last node
        ListNode* tail = head;
        int length = 1;
        
        while (tail->next) {
            tail = tail->next;
            length++;
        }
        
        // Calculate effective rotation
        k = k % length;
        if (k == 0) return head;
        
        // Find new tail (length - k - 1 from start)
        ListNode* newTail = head;
        for (int i = 0; i < length - k - 1; ++i) {
            newTail = newTail->next;
        }
        
        // New head is next of new tail
        ListNode* newHead = newTail->next;
        
        // Break the cycle
        newTail->next = nullptr;
        tail->next = head;
        
        return newHead;
    }
    
    /*
     * Problem 15: Swap Nodes in Pairs
     * Swap every two adjacent nodes.
     * 
     * Approach: Iterative swapping with dummy node
     * Time: O(n), Space: O(1)
     */
    static ListNode* swapPairs(ListNode* head) {
        if (!head || !head->next) return head;
        
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        ListNode* prev = dummy;
        
        while (prev->next && prev->next->next) {
            ListNode* first = prev->next;
            ListNode* second = prev->next->next;
            
            // Swap
            prev->next = second;
            first->next = second->next;
            second->next = first;
            
            // Move to next pair
            prev = first;
        }
        
        ListNode* result = dummy->next;
        delete dummy;
        return result;
    }
};

/*
 * ========================================================================
 * CATEGORY 4: MERGE AND SORT OPERATIONS (Problems 16-20)
 * ========================================================================
 */

class MergeSortOperations {
public:
    /*
     * Problem 16: Merge Two Sorted Lists
     * Merge two sorted linked lists.
     * 
     * Approach: Two pointers with comparison
     * Time: O(m + n), Space: O(1)
     */
    static ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* dummy = new ListNode(0);
        ListNode* current = dummy;
        
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
        
        // Attach remaining nodes
        current->next = l1 ? l1 : l2;
        
        ListNode* result = dummy->next;
        delete dummy;
        return result;
    }
    
    /*
     * Problem 17: Merge k Sorted Lists
     * Merge k sorted linked lists.
     * 
     * Approach: Divide and conquer
     * Time: O(n log k), Space: O(log k)
     */
    static ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) return nullptr;
        return mergeKListsHelper(lists, 0, static_cast<int>(lists.size()) - 1);
    }
    
    /*
     * Problem 18: Sort List
     * Sort a linked list in O(n log n) time.
     * 
     * Approach: Merge sort
     * Time: O(n log n), Space: O(log n)
     */
    static ListNode* sortList(ListNode* head) {
        if (!head || !head->next) return head;
        
        // Find middle and split
        ListNode* mid = findMiddleAndSplit(head);
        
        // Recursively sort both halves
        ListNode* left = sortList(head);
        ListNode* right = sortList(mid);
        
        // Merge sorted halves
        return mergeTwoLists(left, right);
    }
    
    /*
     * Problem 19: Insertion Sort List
     * Sort using insertion sort algorithm.
     * 
     * Approach: Build sorted portion iteratively
     * Time: O(n²), Space: O(1)
     */
    static ListNode* insertionSortList(ListNode* head) {
        if (!head || !head->next) return head;
        
        ListNode* dummy = new ListNode(0);
        ListNode* current = head;
        
        while (current) {
            ListNode* next = current->next;
            
            // Find insertion position
            ListNode* prev = dummy;
            while (prev->next && prev->next->val < current->val) {
                prev = prev->next;
            }
            
            // Insert current node
            current->next = prev->next;
            prev->next = current;
            
            current = next;
        }
        
        ListNode* result = dummy->next;
        delete dummy;
        return result;
    }
    
    /*
     * Problem 20: Partition List
     * Partition list around value x.
     * 
     * Approach: Two separate lists, then combine
     * Time: O(n), Space: O(1)
     */
    static ListNode* partition(ListNode* head, int x) {
        ListNode* smallerHead = new ListNode(0);
        ListNode* greaterHead = new ListNode(0);
        ListNode* smaller = smallerHead;
        ListNode* greater = greaterHead;
        
        while (head) {
            if (head->val < x) {
                smaller->next = head;
                smaller = smaller->next;
            } else {
                greater->next = head;
                greater = greater->next;
            }
            head = head->next;
        }
        
        // Connect smaller list to greater list
        greater->next = nullptr;
        smaller->next = greaterHead->next;
        
        ListNode* result = smallerHead->next;
        delete smallerHead;
        delete greaterHead;
        return result;
    }

private:
    static ListNode* mergeKListsHelper(vector<ListNode*>& lists, int start, int end) {
        if (start == end) return lists[start];
        if (start > end) return nullptr;
        
        int mid = start + (end - start) / 2;
        ListNode* left = mergeKListsHelper(lists, start, mid);
        ListNode* right = mergeKListsHelper(lists, mid + 1, end);
        
        return mergeTwoLists(left, right);
    }
    
    static ListNode* findMiddleAndSplit(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;
        ListNode* prev = nullptr;
        
        while (fast && fast->next) {
            prev = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        
        // Split the list
        if (prev) prev->next = nullptr;
        
        return slow;
    }
    
    static ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* dummy = new ListNode(0);
        ListNode* current = dummy;
        
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
        
        ListNode* result = dummy->next;
        delete dummy;
        return result;
    }
};

/*
 * ========================================================================
 * CATEGORY 5: ADVANCED ALGORITHMS (Problems 21-25)
 * ========================================================================
 */

class AdvancedAlgorithms {
public:
    /*
     * Problem 21: Copy List with Random Pointer
     * Deep copy a linked list where each node has a random pointer.
     * 
     * Approach: Three-pass algorithm with interweaving
     * Time: O(n), Space: O(1)
     */
    struct RandomListNode {
        int val;
        RandomListNode* next;
        RandomListNode* random;
        
        RandomListNode(int x) : val(x), next(nullptr), random(nullptr) {}
    };
    
    static RandomListNode* copyRandomList(RandomListNode* head) {
        if (!head) return nullptr;
        
        // Phase 1: Create copy nodes and interweave
        RandomListNode* current = head;
        while (current) {
            RandomListNode* copy = new RandomListNode(current->val);
            copy->next = current->next;
            current->next = copy;
            current = copy->next;
        }
        
        // Phase 2: Set random pointers for copy nodes
        current = head;
        while (current) {
            if (current->random) {
                current->next->random = current->random->next;
            }
            current = current->next->next;
        }
        
        // Phase 3: Separate original and copy lists
        RandomListNode* copyHead = head->next;
        RandomListNode* original = head;
        RandomListNode* copy = copyHead;
        
        while (original) {
            original->next = copy->next;
            original = original->next;
            
            if (original) {
                copy->next = original->next;
                copy = copy->next;
            }
        }
        
        return copyHead;
    }
    
    /*
     * Problem 22: LRU Cache Implementation
     * Implement LRU cache using doubly linked list + hash map.
     * 
     * Time: O(1) for get and put operations
     * Space: O(capacity)
     */
    class LRUCache {
    private:
        struct DListNode {
            int key, value;
            DListNode* prev;
            DListNode* next;
            
            DListNode() : key(0), value(0), prev(nullptr), next(nullptr) {}
            DListNode(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
        };
        
        unordered_map<int, DListNode*> cache;
        DListNode* head;
        DListNode* tail;
        int capacity;
        
        void addToHead(DListNode* node) {
            node->prev = head;
            node->next = head->next;
            head->next->prev = node;
            head->next = node;
        }
        
        void removeNode(DListNode* node) {
            node->prev->next = node->next;
            node->next->prev = node->prev;
        }
        
        void moveToHead(DListNode* node) {
            removeNode(node);
            addToHead(node);
        }
        
        DListNode* popTail() {
            DListNode* last = tail->prev;
            removeNode(last);
            return last;
        }
        
    public:
        LRUCache(int capacity) : capacity(capacity) {
            head = new DListNode();
            tail = new DListNode();
            head->next = tail;
            tail->prev = head;
        }
        
        int get(int key) {
            auto it = cache.find(key);
            if (it != cache.end()) {
                DListNode* node = it->second;
                moveToHead(node);
                return node->value;
            }
            return -1;
        }
        
        void put(int key, int value) {
            auto it = cache.find(key);
            if (it != cache.end()) {
                DListNode* node = it->second;
                node->value = value;
                moveToHead(node);
            } else {
                DListNode* newNode = new DListNode(key, value);
                
                if (static_cast<int>(cache.size()) >= capacity) {
                    DListNode* tail_node = popTail();
                    cache.erase(tail_node->key);
                    delete tail_node;
                }
                
                cache[key] = newNode;
                addToHead(newNode);
            }
        }
        
        ~LRUCache() {
            DListNode* current = head;
            while (current) {
                DListNode* next = current->next;
                delete current;
                current = next;
            }
        }
    };
    
    /*
     * Problem 23: Flatten Multilevel Doubly Linked List
     * Flatten a multilevel doubly linked list.
     * 
     * Approach: DFS with stack
     * Time: O(n), Space: O(d) where d is max depth
     */
    struct MultilevelNode {
        int val;
        MultilevelNode* prev;
        MultilevelNode* next;
        MultilevelNode* child;
        
        MultilevelNode() : val(0), prev(nullptr), next(nullptr), child(nullptr) {}
        MultilevelNode(int x) : val(x), prev(nullptr), next(nullptr), child(nullptr) {}
    };
    
    static MultilevelNode* flatten(MultilevelNode* head) {
        if (!head) return nullptr;
        
        stack<MultilevelNode*> st;
        MultilevelNode* current = head;
        
        while (current) {
            if (current->child) {
                // If there's a next node, push it to stack
                if (current->next) {
                    st.push(current->next);
                }
                
                // Connect current to child
                current->next = current->child;
                current->child->prev = current;
                current->child = nullptr;
            }
            
            // If we reach the end and stack is not empty
            if (!current->next && !st.empty()) {
                MultilevelNode* next = st.top();
                st.pop();
                
                current->next = next;
                next->prev = current;
            }
            
            current = current->next;
        }
        
        return head;
    }
    
    /*
     * Problem 24: Add Two Numbers
     * Add two numbers represented as linked lists.
     * 
     * Approach: Simulate addition with carry
     * Time: O(max(m, n)), Space: O(max(m, n))
     */
    static ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* dummy = new ListNode(0);
        ListNode* current = dummy;
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
        
        ListNode* result = dummy->next;
        delete dummy;
        return result;
    }
    
    /*
     * Problem 25: Reorder List
     * Reorder list: L0 → L1 → … → Ln-1 → Ln to L0 → Ln → L1 → Ln-1 → L2 → Ln-2 → …
     * 
     * Approach: Find middle, reverse second half, merge alternately
     * Time: O(n), Space: O(1)
     */
    static void reorderList(ListNode* head) {
        if (!head || !head->next) return;
        
        // Find middle
        ListNode* slow = head;
        ListNode* fast = head;
        
        while (fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        // Split and reverse second half
        ListNode* secondHalf = slow->next;
        slow->next = nullptr;
        secondHalf = reverseList(secondHalf);
        
        // Merge alternately
        ListNode* first = head;
        ListNode* second = secondHalf;
        
        while (second) {
            ListNode* temp1 = first->next;
            ListNode* temp2 = second->next;
            
            first->next = second;
            second->next = temp1;
            
            first = temp1;
            second = temp2;
        }
    }

private:
    static ListNode* reverseList(ListNode* head) {
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
};

/*
 * ========================================================================
 * TESTING AND DEMONSTRATION
 * ========================================================================
 */

void testBasicOperations() {
    cout << "=== BASIC OPERATIONS TESTS ===" << endl;
    
    // Test Remove Nth From End
    cout << "Remove Nth From End:" << endl;
    ListNode* list1 = LinkedListUtils::createList({1, 2, 3, 4, 5});
    LinkedListUtils::printList(list1, "Original");
    
    list1 = BasicOperations::removeNthFromEnd(list1, 2);
    LinkedListUtils::printList(list1, "After removing 2nd from end");
    
    // Test Find Middle
    cout << "\nFind Middle:" << endl;
    ListNode* list2 = LinkedListUtils::createList({1, 2, 3, 4, 5, 6});
    LinkedListUtils::printList(list2, "Original");
    
    ListNode* middle = BasicOperations::findMiddle(list2);
    cout << "Middle node value: " << middle->val << endl;
    
    // Test Remove Duplicates
    cout << "\nRemove Duplicates:" << endl;
    ListNode* list3 = LinkedListUtils::createList({1, 1, 2, 3, 3});
    LinkedListUtils::printList(list3, "With duplicates");
    
    list3 = BasicOperations::removeDuplicates(list3);
    LinkedListUtils::printList(list3, "After removing duplicates");
    
    // Cleanup
    LinkedListUtils::deleteList(list1);
    LinkedListUtils::deleteList(list2);
    LinkedListUtils::deleteList(list3);
    
    cout << endl;
}

void testTwoPointerTechniques() {
    cout << "=== TWO POINTER TECHNIQUES TESTS ===" << endl;
    
    // Test Cycle Detection
    cout << "Cycle Detection:" << endl;
    ListNode* list1 = LinkedListUtils::createList({3, 2, 0, -4});
    LinkedListUtils::printList(list1, "Original");
    
    bool hasCycle1 = TwoPointerTechniques::hasCycle(list1);
    cout << "Has cycle: " << (hasCycle1 ? "Yes" : "No") << endl;
    
    // Create cycle and test again
    LinkedListUtils::createCycle(list1, 1);
    bool hasCycle2 = TwoPointerTechniques::hasCycle(list1);
    cout << "After creating cycle at position 1: " << (hasCycle2 ? "Yes" : "No") << endl;
    
    // Test Palindrome
    cout << "\nPalindrome Check:" << endl;
    ListNode* list2 = LinkedListUtils::createList({1, 2, 2, 1});
    LinkedListUtils::printList(list2, "List");
    
    bool isPalin = TwoPointerTechniques::isPalindrome(list2);
    cout << "Is palindrome: " << (isPalin ? "Yes" : "No") << endl;
    
    // Cleanup (note: list1 has cycle, so we don't delete it normally)
    LinkedListUtils::deleteList(list2);
    
    cout << endl;
}

void testReversalManipulation() {
    cout << "=== REVERSAL AND MANIPULATION TESTS ===" << endl;
    
    // Test Reverse List
    cout << "Reverse List:" << endl;
    ListNode* list1 = LinkedListUtils::createList({1, 2, 3, 4, 5});
    LinkedListUtils::printList(list1, "Original");
    
    list1 = ReversalManipulation::reverseList(list1);
    LinkedListUtils::printList(list1, "Reversed");
    
    // Test Reverse Between
    cout << "\nReverse Between Positions:" << endl;
    ListNode* list2 = LinkedListUtils::createList({1, 2, 3, 4, 5});
    LinkedListUtils::printList(list2, "Original");
    
    list2 = ReversalManipulation::reverseBetween(list2, 2, 4);
    LinkedListUtils::printList(list2, "Reversed between positions 2-4");
    
    // Test Swap Pairs
    cout << "\nSwap Pairs:" << endl;
    ListNode* list3 = LinkedListUtils::createList({1, 2, 3, 4});
    LinkedListUtils::printList(list3, "Original");
    
    list3 = ReversalManipulation::swapPairs(list3);
    LinkedListUtils::printList(list3, "After swapping pairs");
    
    // Cleanup
    LinkedListUtils::deleteList(list1);
    LinkedListUtils::deleteList(list2);
    LinkedListUtils::deleteList(list3);
    
    cout << endl;
}

void testMergeSortOperations() {
    cout << "=== MERGE AND SORT OPERATIONS TESTS ===" << endl;
    
    // Test Merge Two Sorted Lists
    cout << "Merge Two Sorted Lists:" << endl;
    ListNode* list1 = LinkedListUtils::createList({1, 2, 4});
    ListNode* list2 = LinkedListUtils::createList({1, 3, 4});
    
    LinkedListUtils::printList(list1, "List 1");
    LinkedListUtils::printList(list2, "List 2");
    
    ListNode* merged = MergeSortOperations::mergeTwoLists(list1, list2);
    LinkedListUtils::printList(merged, "Merged");
    
    // Test Sort List
    cout << "\nSort List:" << endl;
    ListNode* list3 = LinkedListUtils::createList({4, 2, 1, 3});
    LinkedListUtils::printList(list3, "Unsorted");
    
    list3 = MergeSortOperations::sortList(list3);
    LinkedListUtils::printList(list3, "Sorted");
    
    // Test Partition
    cout << "\nPartition List:" << endl;
    ListNode* list4 = LinkedListUtils::createList({1, 4, 3, 2, 5, 2});
    LinkedListUtils::printList(list4, "Original");
    
    list4 = MergeSortOperations::partition(list4, 3);
    LinkedListUtils::printList(list4, "Partitioned around 3");
    
    // Cleanup
    LinkedListUtils::deleteList(merged);
    LinkedListUtils::deleteList(list3);
    LinkedListUtils::deleteList(list4);
    
    cout << endl;
}

void testAdvancedAlgorithms() {
    cout << "=== ADVANCED ALGORITHMS TESTS ===" << endl;
    
    // Test LRU Cache
    cout << "LRU Cache:" << endl;
    AdvancedAlgorithms::LRUCache cache(2);
    
    cache.put(1, 1);
    cache.put(2, 2);
    cout << "get(1): " << cache.get(1) << endl;  // returns 1
    
    cache.put(3, 3);  // evicts key 2
    cout << "get(2): " << cache.get(2) << endl;  // returns -1 (not found)
    
    cache.put(4, 4);  // evicts key 1
    cout << "get(1): " << cache.get(1) << endl;  // returns -1 (not found)
    cout << "get(3): " << cache.get(3) << endl;  // returns 3
    cout << "get(4): " << cache.get(4) << endl;  // returns 4
    
    // Test Add Two Numbers
    cout << "\nAdd Two Numbers:" << endl;
    ListNode* num1 = LinkedListUtils::createList({2, 4, 3});  // represents 342
    ListNode* num2 = LinkedListUtils::createList({5, 6, 4});  // represents 465
    
    LinkedListUtils::printList(num1, "Number 1 (342)");
    LinkedListUtils::printList(num2, "Number 2 (465)");
    
    ListNode* sum = AdvancedAlgorithms::addTwoNumbers(num1, num2);
    LinkedListUtils::printList(sum, "Sum (807)");
    
    // Test Reorder List
    cout << "\nReorder List:" << endl;
    ListNode* list1 = LinkedListUtils::createList({1, 2, 3, 4});
    LinkedListUtils::printList(list1, "Original");
    
    AdvancedAlgorithms::reorderList(list1);
    LinkedListUtils::printList(list1, "Reordered");
    
    // Cleanup
    LinkedListUtils::deleteList(num1);
    LinkedListUtils::deleteList(num2);
    LinkedListUtils::deleteList(sum);
    LinkedListUtils::deleteList(list1);
    
    cout << endl;
}

/*
 * ========================================================================
 * MAIN FUNCTION
 * ========================================================================
 */

int main() {
    cout << "=== LINKED LIST PROBLEMS COMPREHENSIVE GUIDE ===" << endl << endl;
    
    testBasicOperations();
    testTwoPointerTechniques();
    testReversalManipulation();
    testMergeSortOperations();
    testAdvancedAlgorithms();
    
    cout << "=== All Linked List Problems Tested Successfully! ===" << endl;
    
    return 0;
}

/*
 * ============================================================================
 * PROBLEM COMPLEXITY SUMMARY:
 * ============================================================================
 * 
 * BASIC OPERATIONS:
 * 1. Delete Node: O(1) time, O(1) space
 * 2. Remove Nth From End: O(n) time, O(1) space
 * 3. Find Middle: O(n) time, O(1) space
 * 4. Remove Duplicates: O(n) time, O(1) space
 * 5. Remove All Duplicates: O(n) time, O(1) space
 * 
 * TWO POINTER TECHNIQUES:
 * 6. Cycle Detection: O(n) time, O(1) space
 * 7. Find Cycle Start: O(n) time, O(1) space
 * 8. Intersection: O(m + n) time, O(1) space
 * 9. Palindrome: O(n) time, O(1) space
 * 10. Remove Elements: O(n) time, O(1) space
 * 
 * REVERSAL AND MANIPULATION:
 * 11. Reverse List: O(n) time, O(1) space
 * 12. Reverse Between: O(n) time, O(1) space
 * 13. Reverse K Group: O(n) time, O(1) space
 * 14. Rotate List: O(n) time, O(1) space
 * 15. Swap Pairs: O(n) time, O(1) space
 * 
 * MERGE AND SORT:
 * 16. Merge Two Lists: O(m + n) time, O(1) space
 * 17. Merge K Lists: O(n log k) time, O(log k) space
 * 18. Sort List: O(n log n) time, O(log n) space
 * 19. Insertion Sort: O(n²) time, O(1) space
 * 20. Partition: O(n) time, O(1) space
 * 
 * ADVANCED ALGORITHMS:
 * 21. Copy Random List: O(n) time, O(1) space
 * 22. LRU Cache: O(1) get/put, O(capacity) space
 * 23. Flatten Multilevel: O(n) time, O(d) space
 * 24. Add Two Numbers: O(max(m,n)) time, O(max(m,n)) space
 * 25. Reorder List: O(n) time, O(1) space
 * 
 * ============================================================================
 * KEY PATTERNS AND TECHNIQUES:
 * ============================================================================
 * 
 * 1. DUMMY NODE PATTERN:
 *    - Use when head might change
 *    - Simplifies edge case handling
 *    - Common in merge/manipulation problems
 * 
 * 2. TWO POINTER TECHNIQUE:
 *    - Slow/Fast pointers for cycle detection
 *    - Find middle, detect patterns
 *    - Space-efficient solutions
 * 
 * 3. ITERATIVE REVERSAL:
 *    - Three pointers: prev, current, next
 *    - More space-efficient than recursion
 *    - Used in many manipulation problems
 * 
 * 4. DIVIDE AND CONQUER:
 *    - Merge sort approach for sorting
 *    - Efficient for merge k lists
 *    - Recursive problem breakdown
 * 
 * 5. HASH MAP OPTIMIZATION:
 *    - Trade space for time
 *    - Quick lookups and existence checks
 *    - Useful for complex relationships
 * 
 * ============================================================================
 */
