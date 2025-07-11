/*
 * ============================================================================
 * CIRCULAR LINKED LIST IMPLEMENTATION
 * ============================================================================
 * 
 * A comprehensive implementation of circular linked lists with both singly
 * and doubly linked variants. Circular linked lists are useful for:
 * - Round-robin scheduling
 * - Music playlists
 * - Game turn management
 * - Buffer implementations
 * - Continuous data processing
 * 
 * KEY CHARACTERISTICS:
 * - Last node points back to first node (no NULL termination)
 * - Continuous traversal possible
 * - Special handling for empty and single-node cases
 * - Careful insertion/deletion to maintain circularity
 * 
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>

using namespace std;

/*
 * ========================================================================
 * CIRCULAR SINGLY LINKED LIST
 * ========================================================================
 */

template<typename T>
class CircularSinglyLinkedList {
private:
    struct Node {
        T data;
        Node* next;
        
        Node(const T& value) : data(value), next(nullptr) {}
    };
    
    Node* tail;  // Points to last node (which points to first)
    size_t list_size;

public:
    /*
     * Constructor & Destructor
     */
    CircularSinglyLinkedList() : tail(nullptr), list_size(0) {}
    
    ~CircularSinglyLinkedList() {
        clear();
    }
    
    // Copy constructor
    CircularSinglyLinkedList(const CircularSinglyLinkedList& other) 
        : tail(nullptr), list_size(0) {
        if (!other.empty()) {
            Node* current = other.tail->next;  // Start from head
            do {
                push_back(current->data);
                current = current->next;
            } while (current != other.tail->next);
        }
    }
    
    // Assignment operator
    CircularSinglyLinkedList& operator=(const CircularSinglyLinkedList& other) {
        if (this != &other) {
            clear();
            if (!other.empty()) {
                Node* current = other.tail->next;
                do {
                    push_back(current->data);
                    current = current->next;
                } while (current != other.tail->next);
            }
        }
        return *this;
    }
    
    /*
     * Basic Properties
     */
    bool empty() const {
        return tail == nullptr;
    }
    
    size_t size() const {
        return list_size;
    }
    
    /*
     * Element Access
     */
    T& front() {
        if (empty()) throw std::runtime_error("List is empty");
        return tail->next->data;  // Head is tail->next
    }
    
    const T& front() const {
        if (empty()) throw std::runtime_error("List is empty");
        return tail->next->data;
    }
    
    T& back() {
        if (empty()) throw std::runtime_error("List is empty");
        return tail->data;
    }
    
    const T& back() const {
        if (empty()) throw std::runtime_error("List is empty");
        return tail->data;
    }
    
    /*
     * Insertion Operations
     */
    
    // Insert at the beginning (before current head)
    void push_front(const T& value) {
        Node* new_node = new Node(value);
        
        if (empty()) {
            // First node - points to itself
            tail = new_node;
            tail->next = tail;
        } else {
            // Insert between tail and head
            new_node->next = tail->next;  // Point to current head
            tail->next = new_node;        // Tail points to new head
        }
        
        list_size++;
    }
    
    // Insert at the end (after current tail)
    void push_back(const T& value) {
        Node* new_node = new Node(value);
        
        if (empty()) {
            // First node - points to itself
            tail = new_node;
            tail->next = tail;
        } else {
            // Insert after current tail
            new_node->next = tail->next;  // Point to head
            tail->next = new_node;        // Current tail points to new node
            tail = new_node;              // Update tail
        }
        
        list_size++;
    }
    
    // Insert at specific position (0-indexed)
    void insert(size_t position, const T& value) {
        if (position > list_size) {
            throw std::out_of_range("Position out of range");
        }
        
        if (position == 0) {
            push_front(value);
            return;
        }
        
        if (position == list_size) {
            push_back(value);
            return;
        }
        
        Node* new_node = new Node(value);
        Node* current = tail->next;  // Start from head
        
        // Move to position-1
        for (size_t i = 0; i < position - 1; ++i) {
            current = current->next;
        }
        
        new_node->next = current->next;
        current->next = new_node;
        list_size++;
    }
    
    /*
     * Deletion Operations
     */
    
    // Remove from the beginning
    void pop_front() {
        if (empty()) throw std::runtime_error("List is empty");
        
        if (list_size == 1) {
            // Only one node
            delete tail;
            tail = nullptr;
        } else {
            Node* head = tail->next;
            tail->next = head->next;  // Skip head
            delete head;
        }
        
        list_size--;
    }
    
    // Remove from the end
    void pop_back() {
        if (empty()) throw std::runtime_error("List is empty");
        
        if (list_size == 1) {
            // Only one node
            delete tail;
            tail = nullptr;
        } else {
            // Find second-to-last node
            Node* current = tail->next;  // Start from head
            while (current->next != tail) {
                current = current->next;
            }
            
            current->next = tail->next;  // Point to head
            delete tail;
            tail = current;  // Update tail
        }
        
        list_size--;
    }
    
    // Remove at specific position
    void erase(size_t position) {
        if (position >= list_size) {
            throw std::out_of_range("Position out of range");
        }
        
        if (position == 0) {
            pop_front();
            return;
        }
        
        if (position == list_size - 1) {
            pop_back();
            return;
        }
        
        Node* current = tail->next;  // Start from head
        
        // Move to position-1
        for (size_t i = 0; i < position - 1; ++i) {
            current = current->next;
        }
        
        Node* node_to_delete = current->next;
        current->next = node_to_delete->next;
        delete node_to_delete;
        list_size--;
    }
    
    // Remove first occurrence of value
    bool remove(const T& value) {
        if (empty()) return false;
        
        if (list_size == 1) {
            if (tail->data == value) {
                delete tail;
                tail = nullptr;
                list_size = 0;
                return true;
            }
            return false;
        }
        
        // Check if head needs to be removed
        if (tail->next->data == value) {
            pop_front();
            return true;
        }
        
        Node* current = tail->next;  // Start from head
        do {
            if (current->next->data == value) {
                Node* node_to_delete = current->next;
                
                if (node_to_delete == tail) {
                    // Removing tail
                    tail = current;
                }
                
                current->next = node_to_delete->next;
                delete node_to_delete;
                list_size--;
                return true;
            }
            current = current->next;
        } while (current != tail);
        
        return false;
    }
    
    // Clear all elements
    void clear() {
        if (empty()) return;
        
        Node* current = tail->next;  // Start from head
        Node* head = current;
        
        do {
            Node* next = current->next;
            delete current;
            current = next;
        } while (current != head);
        
        tail = nullptr;
        list_size = 0;
    }
    
    /*
     * Search Operations
     */
    
    // Find first occurrence of value
    int find(const T& value) const {
        if (empty()) return -1;
        
        Node* current = tail->next;  // Start from head
        int position = 0;
        
        do {
            if (current->data == value) {
                return position;
            }
            current = current->next;
            position++;
        } while (current != tail->next);
        
        return -1;
    }
    
    // Check if value exists
    bool contains(const T& value) const {
        return find(value) != -1;
    }
    
    /*
     * Utility Operations
     */
    
    // Display the list
    void display() const {
        if (empty()) {
            cout << "List is empty" << endl;
            return;
        }
        
        Node* current = tail->next;  // Start from head
        cout << "Circular List: ";
        
        do {
            cout << current->data;
            current = current->next;
            if (current != tail->next) cout << " -> ";
        } while (current != tail->next);
        
        cout << " -> (back to " << tail->next->data << ")" << endl;
    }
    
    // Convert to vector for easier testing
    vector<T> to_vector() const {
        vector<T> result;
        if (empty()) return result;
        
        Node* current = tail->next;  // Start from head
        do {
            result.push_back(current->data);
            current = current->next;
        } while (current != tail->next);
        
        return result;
    }
    
    // Rotate the list (move elements forward by k positions)
    void rotate(int k) {
        if (empty() || list_size <= 1) return;
        
        k = k % static_cast<int>(list_size);
        if (k == 0) return;
        
        if (k < 0) k += list_size;  // Handle negative rotation
        
        // Find new tail (k positions from current tail)
        Node* new_tail = tail;
        for (int i = 0; i < k; ++i) {
            new_tail = new_tail->next;
        }
        
        tail = new_tail;
    }
    
    // Split list at position (creates two circular lists)
    CircularSinglyLinkedList<T> split_at(size_t position) {
        if (position >= list_size) {
            throw std::out_of_range("Position out of range");
        }
        
        CircularSinglyLinkedList<T> second_list;
        
        if (position == 0) {
            // Return empty list, keep original
            return second_list;
        }
        
        if (position == list_size) {
            // Return empty list, keep original
            return second_list;
        }
        
        // Find split point
        Node* current = tail->next;  // Start from head
        for (size_t i = 0; i < position - 1; ++i) {
            current = current->next;
        }
        
        // Split the list
        Node* second_head = current->next;
        current->next = tail->next;  // First list: current -> head
        
        // Update first list
        Node* first_tail = current;
        
        // Create second list
        second_list.tail = tail;
        second_list.tail->next = second_head;  // Second list: tail -> second_head
        
        // Update sizes
        second_list.list_size = list_size - position;
        list_size = position;
        
        // Update first list's tail
        tail = first_tail;
        
        return second_list;
    }
};

/*
 * ========================================================================
 * CIRCULAR DOUBLY LINKED LIST
 * ========================================================================
 */

template<typename T>
class CircularDoublyLinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        
        Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
    };
    
    Node* head;  // Points to first node
    size_t list_size;

public:
    /*
     * Constructor & Destructor
     */
    CircularDoublyLinkedList() : head(nullptr), list_size(0) {}
    
    ~CircularDoublyLinkedList() {
        clear();
    }
    
    // Copy constructor
    CircularDoublyLinkedList(const CircularDoublyLinkedList& other) 
        : head(nullptr), list_size(0) {
        if (!other.empty()) {
            Node* current = other.head;
            do {
                push_back(current->data);
                current = current->next;
            } while (current != other.head);
        }
    }
    
    // Assignment operator
    CircularDoublyLinkedList& operator=(const CircularDoublyLinkedList& other) {
        if (this != &other) {
            clear();
            if (!other.empty()) {
                Node* current = other.head;
                do {
                    push_back(current->data);
                    current = current->next;
                } while (current != other.head);
            }
        }
        return *this;
    }
    
    /*
     * Basic Properties
     */
    bool empty() const {
        return head == nullptr;
    }
    
    size_t size() const {
        return list_size;
    }
    
    /*
     * Element Access
     */
    T& front() {
        if (empty()) throw std::runtime_error("List is empty");
        return head->data;
    }
    
    const T& front() const {
        if (empty()) throw std::runtime_error("List is empty");
        return head->data;
    }
    
    T& back() {
        if (empty()) throw std::runtime_error("List is empty");
        return head->prev->data;  // Tail is head->prev
    }
    
    const T& back() const {
        if (empty()) throw std::runtime_error("List is empty");
        return head->prev->data;
    }
    
    /*
     * Insertion Operations
     */
    
    // Insert at the beginning
    void push_front(const T& value) {
        Node* new_node = new Node(value);
        
        if (empty()) {
            // First node - points to itself
            head = new_node;
            head->next = head->prev = head;
        } else {
            Node* tail = head->prev;
            
            // Insert between tail and head
            new_node->next = head;
            new_node->prev = tail;
            tail->next = new_node;
            head->prev = new_node;
            head = new_node;  // Update head
        }
        
        list_size++;
    }
    
    // Insert at the end
    void push_back(const T& value) {
        Node* new_node = new Node(value);
        
        if (empty()) {
            // First node - points to itself
            head = new_node;
            head->next = head->prev = head;
        } else {
            Node* tail = head->prev;
            
            // Insert after tail
            new_node->next = head;
            new_node->prev = tail;
            tail->next = new_node;
            head->prev = new_node;
            // head remains the same
        }
        
        list_size++;
    }
    
    // Insert at specific position
    void insert(size_t position, const T& value) {
        if (position > list_size) {
            throw std::out_of_range("Position out of range");
        }
        
        if (position == 0) {
            push_front(value);
            return;
        }
        
        if (position == list_size) {
            push_back(value);
            return;
        }
        
        Node* new_node = new Node(value);
        Node* current = head;
        
        // Move to position
        for (size_t i = 0; i < position; ++i) {
            current = current->next;
        }
        
        // Insert before current
        Node* prev_node = current->prev;
        
        new_node->next = current;
        new_node->prev = prev_node;
        prev_node->next = new_node;
        current->prev = new_node;
        
        list_size++;
    }
    
    /*
     * Deletion Operations
     */
    
    // Remove from the beginning
    void pop_front() {
        if (empty()) throw std::runtime_error("List is empty");
        
        if (list_size == 1) {
            // Only one node
            delete head;
            head = nullptr;
        } else {
            Node* tail = head->prev;
            Node* new_head = head->next;
            
            tail->next = new_head;
            new_head->prev = tail;
            
            delete head;
            head = new_head;
        }
        
        list_size--;
    }
    
    // Remove from the end
    void pop_back() {
        if (empty()) throw std::runtime_error("List is empty");
        
        if (list_size == 1) {
            // Only one node
            delete head;
            head = nullptr;
        } else {
            Node* tail = head->prev;
            Node* new_tail = tail->prev;
            
            new_tail->next = head;
            head->prev = new_tail;
            
            delete tail;
        }
        
        list_size--;
    }
    
    // Remove at specific position
    void erase(size_t position) {
        if (position >= list_size) {
            throw std::out_of_range("Position out of range");
        }
        
        if (position == 0) {
            pop_front();
            return;
        }
        
        if (position == list_size - 1) {
            pop_back();
            return;
        }
        
        Node* current = head;
        
        // Move to position
        for (size_t i = 0; i < position; ++i) {
            current = current->next;
        }
        
        // Remove current
        current->prev->next = current->next;
        current->next->prev = current->prev;
        
        delete current;
        list_size--;
    }
    
    // Remove first occurrence of value
    bool remove(const T& value) {
        if (empty()) return false;
        
        Node* current = head;
        do {
            if (current->data == value) {
                if (list_size == 1) {
                    delete head;
                    head = nullptr;
                    list_size = 0;
                } else {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                    
                    if (current == head) {
                        head = current->next;
                    }
                    
                    delete current;
                    list_size--;
                }
                return true;
            }
            current = current->next;
        } while (current != head);
        
        return false;
    }
    
    // Clear all elements
    void clear() {
        if (empty()) return;
        
        Node* current = head;
        do {
            Node* next = current->next;
            delete current;
            current = next;
        } while (current != head);
        
        head = nullptr;
        list_size = 0;
    }
    
    /*
     * Utility Operations
     */
    
    // Display forward
    void display_forward() const {
        if (empty()) {
            cout << "List is empty" << endl;
            return;
        }
        
        Node* current = head;
        cout << "Forward: ";
        
        do {
            cout << current->data;
            current = current->next;
            if (current != head) cout << " <-> ";
        } while (current != head);
        
        cout << " <-> (back to " << head->data << ")" << endl;
    }
    
    // Display backward
    void display_backward() const {
        if (empty()) {
            cout << "List is empty" << endl;
            return;
        }
        
        Node* current = head->prev;  // Start from tail
        cout << "Backward: ";
        
        do {
            cout << current->data;
            current = current->prev;
            if (current != head->prev) cout << " <-> ";
        } while (current != head->prev);
        
        cout << " <-> (back to " << head->prev->data << ")" << endl;
    }
    
    // Convert to vector
    vector<T> to_vector() const {
        vector<T> result;
        if (empty()) return result;
        
        Node* current = head;
        do {
            result.push_back(current->data);
            current = current->next;
        } while (current != head);
        
        return result;
    }
};

/*
 * ========================================================================
 * CIRCULAR LINKED LIST APPLICATIONS
 * ========================================================================
 */

/*
 * Application 1: Josephus Problem
 * Classic problem where people stand in circle and every k-th person is eliminated
 */
class JosephusProblem {
public:
    static int solve(int n, int k) {
        CircularSinglyLinkedList<int> circle;
        
        // Create circle of people (1 to n)
        for (int i = 1; i <= n; ++i) {
            circle.push_back(i);
        }
        
        cout << "Initial circle: ";
        circle.display();
        
        // Eliminate every k-th person
        while (circle.size() > 1) {
            // Rotate to position k-1, then eliminate
            circle.rotate(k - 1);
            int eliminated = circle.front();
            circle.pop_front();
            
            cout << "Eliminated: " << eliminated << ", ";
            circle.display();
        }
        
        return circle.front();  // Last survivor
    }
};

/*
 * Application 2: Round Robin Scheduler
 * Simple round-robin process scheduling simulation
 */
class RoundRobinScheduler {
private:
    struct Process {
        int id;
        int burst_time;
        int remaining_time;
        
        Process(int pid, int bt) : id(pid), burst_time(bt), remaining_time(bt) {}
        
        bool operator==(const Process& other) const {
            return id == other.id;
        }
    };
    
    CircularSinglyLinkedList<Process> ready_queue;
    int time_quantum;
    int current_time;

public:
    RoundRobinScheduler(int quantum) : time_quantum(quantum), current_time(0) {}
    
    void add_process(int id, int burst_time) {
        ready_queue.push_back(Process(id, burst_time));
    }
    
    void run_scheduler() {
        cout << "=== Round Robin Scheduling (Quantum = " << time_quantum << ") ===" << endl;
        
        while (!ready_queue.empty()) {
            Process current = ready_queue.front();
            ready_queue.pop_front();
            
            int execution_time = min(current.remaining_time, time_quantum);
            current.remaining_time -= execution_time;
            current_time += execution_time;
            
            cout << "Time " << current_time - execution_time << "-" << current_time
                 << ": Process P" << current.id << " executed" << endl;
            
            if (current.remaining_time > 0) {
                // Process not finished, add back to queue
                ready_queue.push_back(current);
            } else {
                cout << "Process P" << current.id << " completed at time " << current_time << endl;
            }
        }
        
        cout << "All processes completed!" << endl;
    }
};

/*
 * ========================================================================
 * TESTING AND DEMONSTRATION
 * ========================================================================
 */

void test_circular_singly_linked_list() {
    cout << "=== CIRCULAR SINGLY LINKED LIST TESTS ===" << endl;
    
    CircularSinglyLinkedList<int> list;
    
    // Test insertions
    cout << "Testing insertions:" << endl;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_front(0);
    list.display();  // Should show: 0 -> 1 -> 2 -> 3 -> (back to 0)
    
    // Test access
    cout << "Front: " << list.front() << ", Back: " << list.back() << endl;
    cout << "Size: " << list.size() << endl;
    
    // Test rotations
    cout << "\nTesting rotation:" << endl;
    list.rotate(2);
    list.display();  // Should be rotated
    
    // Test deletions
    cout << "\nTesting deletions:" << endl;
    list.pop_front();
    list.display();
    
    list.pop_back();
    list.display();
    
    // Test search
    cout << "\nTesting search:" << endl;
    cout << "Position of 1: " << list.find(1) << endl;
    cout << "Contains 5: " << (list.contains(5) ? "Yes" : "No") << endl;
    
    cout << endl;
}

void test_circular_doubly_linked_list() {
    cout << "=== CIRCULAR DOUBLY LINKED LIST TESTS ===" << endl;
    
    CircularDoublyLinkedList<char> list;
    
    // Test insertions
    cout << "Testing insertions:" << endl;
    list.push_back('A');
    list.push_back('B');
    list.push_back('C');
    list.push_front('Z');
    
    list.display_forward();
    list.display_backward();
    
    // Test access
    cout << "Front: " << list.front() << ", Back: " << list.back() << endl;
    cout << "Size: " << list.size() << endl;
    
    // Test insertions at position
    cout << "\nTesting insertion at position 2:" << endl;
    list.insert(2, 'X');
    list.display_forward();
    
    // Test deletions
    cout << "\nTesting deletions:" << endl;
    list.pop_front();
    list.display_forward();
    
    list.erase(1);
    list.display_forward();
    
    cout << endl;
}

void test_josephus_problem() {
    cout << "=== JOSEPHUS PROBLEM TEST ===" << endl;
    
    int n = 7;  // 7 people
    int k = 3;  // Every 3rd person is eliminated
    
    cout << "Josephus Problem: " << n << " people, eliminate every " << k << "rd person" << endl;
    int survivor = JosephusProblem::solve(n, k);
    cout << "Last survivor: " << survivor << endl;
    
    cout << endl;
}

void test_round_robin_scheduler() {
    cout << "=== ROUND ROBIN SCHEDULER TEST ===" << endl;
    
    RoundRobinScheduler scheduler(3);  // Time quantum = 3
    
    // Add processes
    scheduler.add_process(1, 10);  // P1 needs 10 time units
    scheduler.add_process(2, 4);   // P2 needs 4 time units
    scheduler.add_process(3, 5);   // P3 needs 5 time units
    
    scheduler.run_scheduler();
    
    cout << endl;
}

/*
 * ========================================================================
 * MAIN FUNCTION
 * ========================================================================
 */

int main() {
    cout << "=== CIRCULAR LINKED LISTS COMPREHENSIVE GUIDE ===" << endl << endl;
    
    test_circular_singly_linked_list();
    test_circular_doubly_linked_list();
    test_josephus_problem();
    test_round_robin_scheduler();
    
    cout << "=== All Circular Linked List Tests Completed! ===" << endl;
    
    return 0;
}

/*
 * ============================================================================
 * CIRCULAR LINKED LIST SUMMARY:
 * ============================================================================
 * 
 * ADVANTAGES:
 * - Continuous traversal possible
 * - No NULL pointers to check
 * - Useful for round-robin applications
 * - Can traverse entire list from any node
 * - Memory efficient for cyclic data
 * 
 * DISADVANTAGES:
 * - More complex insertion/deletion
 * - Risk of infinite loops if not careful
 * - Harder to detect end of list
 * - More complex boundary conditions
 * 
 * COMMON APPLICATIONS:
 * - Round-robin scheduling
 * - Music playlists (continuous play)
 * - Game turn management
 * - Josephus problem
 * - Buffer implementations
 * - Undo operations in circular buffer
 * 
 * TIME COMPLEXITIES:
 * - Access: O(n)
 * - Search: O(n)
 * - Insertion: O(1) at head/tail, O(n) at arbitrary position
 * - Deletion: O(1) at head/tail, O(n) at arbitrary position
 * - Rotation: O(k) where k is rotation amount
 * 
 * SPACE COMPLEXITY: O(n) where n is number of elements
 * 
 * KEY IMPLEMENTATION NOTES:
 * - Always maintain circularity in operations
 * - Handle single-node case specially
 * - Use tail pointer for singly linked version
 * - Use head pointer for doubly linked version
 * - Be careful with termination conditions in loops
 * 
 * ============================================================================
 */
