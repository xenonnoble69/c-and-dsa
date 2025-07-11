/*
 * ============================================================================
 * HEAP DATA STRUCTURE - COMPREHENSIVE IMPLEMENTATION
 * ============================================================================
 * 
 * A heap is a complete binary tree that satisfies the heap property:
 * - Max Heap: Parent >= Children (root has maximum element)
 * - Min Heap: Parent <= Children (root has minimum element)
 * 
 * Key Properties:
 * - Complete binary tree (filled level by level, left to right)
 * - Can be efficiently implemented using arrays
 * - Provides O(log n) insertion and deletion of min/max element
 * - Provides O(1) access to min/max element
 * 
 * Applications:
 * - Priority Queues
 * - Heap Sort algorithm
 * - Graph algorithms (Dijkstra's, Prim's)
 * - Finding k largest/smallest elements
 * - Median maintenance
 * 
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <functional>

using namespace std;

/*
 * ========================================================================
 * BINARY HEAP IMPLEMENTATION
 * ========================================================================
 */

template<typename T>
class BinaryHeap {
private:
    vector<T> heap;
    bool isMaxHeap;  // true for max heap, false for min heap
    
    // Helper functions for array-based representation
    int parent(int i) const { return (i - 1) / 2; }
    int leftChild(int i) const { return 2 * i + 1; }
    int rightChild(int i) const { return 2 * i + 2; }
    
    // Compare function based on heap type
    bool compare(const T& a, const T& b) const {
        return isMaxHeap ? (a > b) : (a < b);
    }
    
    // Restore heap property by moving element up
    void heapifyUp(int index) {
        /*
         * Move the element at index up the tree until heap property is satisfied
         * Used after insertion to maintain heap property
         * Time Complexity: O(log n)
         */
        while (index > 0) {
            int parentIndex = parent(index);
            
            // If heap property is satisfied, stop
            if (!compare(heap[index], heap[parentIndex])) {
                break;
            }
            
            // Swap with parent and continue
            swap(heap[index], heap[parentIndex]);
            index = parentIndex;
        }
    }
    
    // Restore heap property by moving element down
    void heapifyDown(int index) {
        /*
         * Move the element at index down the tree until heap property is satisfied
         * Used after deletion to maintain heap property
         * Time Complexity: O(log n)
         */
        int size = heap.size();
        
        while (true) {
            int largest = index;
            int left = leftChild(index);
            int right = rightChild(index);
            
            // Find the element that should be at the top among parent and children
            if (left < size && compare(heap[left], heap[largest])) {
                largest = left;
            }
            
            if (right < size && compare(heap[right], heap[largest])) {
                largest = right;
            }
            
            // If current element is in correct position, stop
            if (largest == index) {
                break;
            }
            
            // Swap and continue
            swap(heap[index], heap[largest]);
            index = largest;
        }
    }

public:
    // Constructor
    explicit BinaryHeap(bool maxHeap = true) : isMaxHeap(maxHeap) {}
    
    // Constructor with initial vector (heapify)
    BinaryHeap(const vector<T>& data, bool maxHeap = true) 
        : heap(data), isMaxHeap(maxHeap) {
        buildHeap();
    }
    
    /*
     * ====================================================================
     * BASIC OPERATIONS
     * ====================================================================
     */
    
    // Insert element into heap
    void insert(const T& value) {
        /*
         * 1. Add element to the end of heap (maintains complete tree property)
         * 2. Restore heap property by moving element up
         * Time Complexity: O(log n)
         * Space Complexity: O(1)
         */
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }
    
    // Remove and return top element (min for min heap, max for max heap)
    T extractTop() {
        /*
         * 1. Save the top element (to return)
         * 2. Move last element to top
         * 3. Remove last element
         * 4. Restore heap property by moving top element down
         * Time Complexity: O(log n)
         * Space Complexity: O(1)
         */
        if (empty()) {
            throw runtime_error("Heap is empty");
        }
        
        T result = heap[0];
        
        // Move last element to top and remove last element
        heap[0] = heap.back();
        heap.pop_back();
        
        // Restore heap property
        if (!empty()) {
            heapifyDown(0);
        }
        
        return result;
    }
    
    // Get top element without removing it
    const T& top() const {
        /*
         * Return the min/max element without removing it
         * Time Complexity: O(1)
         * Space Complexity: O(1)
         */
        if (empty()) {
            throw runtime_error("Heap is empty");
        }
        return heap[0];
    }
    
    // Check if heap is empty
    bool empty() const {
        return heap.empty();
    }
    
    // Get number of elements in heap
    size_t size() const {
        return heap.size();
    }
    
    /*
     * ====================================================================
     * ADVANCED OPERATIONS
     * ====================================================================
     */
    
    // Build heap from existing array (Floyd's algorithm)
    void buildHeap() {
        /*
         * Convert arbitrary array into heap
         * Start from last non-leaf node and heapify down each node
         * Time Complexity: O(n) - better than n insertions O(n log n)
         * Space Complexity: O(1)
         */
        int n = heap.size();
        
        // Start from last non-leaf node
        for (int i = (n / 2) - 1; i >= 0; --i) {
            heapifyDown(i);
        }
    }
    
    // Remove element at specific index
    void remove(int index) {
        /*
         * Remove element at given index
         * Time Complexity: O(log n)
         */
        if (index < 0 || index >= heap.size()) {
            throw out_of_range("Index out of bounds");
        }
        
        // Replace with last element
        heap[index] = heap.back();
        heap.pop_back();
        
        if (index < heap.size()) {
            // Try both heapify operations
            int parentIdx = parent(index);
            if (index > 0 && compare(heap[index], heap[parentIdx])) {
                heapifyUp(index);
            } else {
                heapifyDown(index);
            }
        }
    }
    
    // Update element at specific index
    void update(int index, const T& newValue) {
        /*
         * Update element at given index with new value
         * Time Complexity: O(log n)
         */
        if (index < 0 || index >= heap.size()) {
            throw out_of_range("Index out of bounds");
        }
        
        T oldValue = heap[index];
        heap[index] = newValue;
        
        // Determine direction to restore heap property
        if (compare(newValue, oldValue)) {
            heapifyUp(index);
        } else {
            heapifyDown(index);
        }
    }
    
    // Merge with another heap
    void merge(const BinaryHeap<T>& other) {
        /*
         * Merge current heap with another heap
         * Time Complexity: O((n + m) log(n + m)) where n, m are sizes
         */
        if (isMaxHeap != other.isMaxHeap) {
            throw invalid_argument("Cannot merge heaps of different types");
        }
        
        // Add all elements from other heap
        for (const T& element : other.heap) {
            insert(element);
        }
    }
    
    /*
     * ====================================================================
     * UTILITY FUNCTIONS
     * ====================================================================
     */
    
    // Check if array satisfies heap property
    bool isValidHeap() const {
        /*
         * Verify that the current array satisfies heap property
         * Time Complexity: O(n)
         */
        for (int i = 0; i < heap.size(); ++i) {
            int left = leftChild(i);
            int right = rightChild(i);
            
            if (left < heap.size() && compare(heap[left], heap[i])) {
                return false;
            }
            
            if (right < heap.size() && compare(heap[right], heap[i])) {
                return false;
            }
        }
        return true;
    }
    
    // Get k largest/smallest elements
    vector<T> getTopK(int k) const {
        /*
         * Get k largest elements (for max heap) or k smallest elements (for min heap)
         * Time Complexity: O(k log k)
         */
        vector<T> result;
        if (k <= 0 || empty()) return result;
        
        // Create a copy for extraction
        BinaryHeap<T> tempHeap(*this);
        
        for (int i = 0; i < k && !tempHeap.empty(); ++i) {
            result.push_back(tempHeap.extractTop());
        }
        
        return result;
    }
    
    // Convert heap to sorted array
    vector<T> heapSort() const {
        /*
         * Extract all elements to get sorted order
         * Time Complexity: O(n log n)
         * For max heap: descending order
         * For min heap: ascending order
         */
        vector<T> result;
        BinaryHeap<T> tempHeap(*this);
        
        while (!tempHeap.empty()) {
            result.push_back(tempHeap.extractTop());
        }
        
        return result;
    }
    
    // Print heap level by level
    void printHeap() const {
        cout << "Heap (" << (isMaxHeap ? "Max" : "Min") << "): ";
        for (const T& element : heap) {
            cout << element << " ";
        }
        cout << endl;
        
        // Print tree structure
        printTreeStructure();
    }
    
    void printTreeStructure() const {
        if (empty()) {
            cout << "Empty heap" << endl;
            return;
        }
        
        cout << "Tree structure:" << endl;
        int level = 0;
        int levelSize = 1;
        int index = 0;
        
        while (index < heap.size()) {
            cout << "Level " << level << ": ";
            
            for (int i = 0; i < levelSize && index < heap.size(); ++i) {
                cout << heap[index++] << " ";
            }
            
            cout << endl;
            level++;
            levelSize *= 2;
        }
    }
    
    // Get underlying vector (for testing)
    const vector<T>& getHeapArray() const {
        return heap;
    }
};

/*
 * ========================================================================
 * SPECIALIZED HEAP IMPLEMENTATIONS
 * ========================================================================
 */

// Min Heap specialization
template<typename T>
class MinHeap : public BinaryHeap<T> {
public:
    MinHeap() : BinaryHeap<T>(false) {}
    MinHeap(const vector<T>& data) : BinaryHeap<T>(data, false) {}
    
    T extractMin() { return this->extractTop(); }
    const T& getMin() const { return this->top(); }
};

// Max Heap specialization
template<typename T>
class MaxHeap : public BinaryHeap<T> {
public:
    MaxHeap() : BinaryHeap<T>(true) {}
    MaxHeap(const vector<T>& data) : BinaryHeap<T>(data, true) {}
    
    T extractMax() { return this->extractTop(); }
    const T& getMax() const { return this->top(); }
};

/*
 * ========================================================================
 * HEAP-BASED ALGORITHMS
 * ========================================================================
 */

// Heap Sort implementation
template<typename T>
vector<T> heapSort(vector<T> arr, bool ascending = true) {
    /*
     * Sort array using heap sort algorithm
     * Time Complexity: O(n log n)
     * Space Complexity: O(1) in-place sorting
     */
    if (arr.empty()) return arr;
    
    // Build heap (use max heap for ascending sort)
    BinaryHeap<T> heap(arr, !ascending);
    
    // Extract elements in sorted order
    vector<T> result;
    while (!heap.empty()) {
        result.push_back(heap.extractTop());
    }
    
    return result;
}

// Find k largest elements
template<typename T>
vector<T> findKLargest(const vector<T>& arr, int k) {
    /*
     * Find k largest elements using min heap
     * Time Complexity: O(n log k)
     * Space Complexity: O(k)
     */
    if (k <= 0 || arr.empty()) return {};
    
    MinHeap<T> minHeap;
    
    for (const T& element : arr) {
        if (minHeap.size() < k) {
            minHeap.insert(element);
        } else if (element > minHeap.getMin()) {
            minHeap.extractMin();
            minHeap.insert(element);
        }
    }
    
    // Extract all elements
    vector<T> result;
    while (!minHeap.empty()) {
        result.push_back(minHeap.extractMin());
    }
    
    // Reverse to get largest first
    reverse(result.begin(), result.end());
    return result;
}

// Find k smallest elements
template<typename T>
vector<T> findKSmallest(const vector<T>& arr, int k) {
    /*
     * Find k smallest elements using max heap
     * Time Complexity: O(n log k)
     * Space Complexity: O(k)
     */
    if (k <= 0 || arr.empty()) return {};
    
    MaxHeap<T> maxHeap;
    
    for (const T& element : arr) {
        if (maxHeap.size() < k) {
            maxHeap.insert(element);
        } else if (element < maxHeap.getMax()) {
            maxHeap.extractMax();
            maxHeap.insert(element);
        }
    }
    
    // Extract all elements
    vector<T> result;
    while (!maxHeap.empty()) {
        result.push_back(maxHeap.extractMax());
    }
    
    // Reverse to get smallest first
    reverse(result.begin(), result.end());
    return result;
}

/*
 * ========================================================================
 * DEMONSTRATION AND TESTING
 * ========================================================================
 */

void demonstrateBasicOperations() {
    cout << "=== BASIC HEAP OPERATIONS ===" << endl;
    
    // Max Heap demonstration
    cout << "\n--- Max Heap ---" << endl;
    MaxHeap<int> maxHeap;
    
    vector<int> values = {4, 10, 3, 5, 1, 15, 20, 17};
    cout << "Inserting: ";
    for (int val : values) {
        cout << val << " ";
        maxHeap.insert(val);
    }
    cout << endl;
    
    maxHeap.printHeap();
    
    cout << "Extracting elements: ";
    while (!maxHeap.empty()) {
        cout << maxHeap.extractMax() << " ";
    }
    cout << endl;
    
    // Min Heap demonstration
    cout << "\n--- Min Heap ---" << endl;
    MinHeap<int> minHeap(values);
    minHeap.printHeap();
    
    cout << "Extracting elements: ";
    while (!minHeap.empty()) {
        cout << minHeap.extractMin() << " ";
    }
    cout << endl;
}

void demonstrateHeapSort() {
    cout << "\n=== HEAP SORT DEMONSTRATION ===" << endl;
    
    vector<int> arr = {64, 34, 25, 12, 22, 11, 90};
    cout << "Original array: ";
    for (int x : arr) cout << x << " ";
    cout << endl;
    
    vector<int> sortedAsc = heapSort(arr, true);
    cout << "Sorted ascending: ";
    for (int x : sortedAsc) cout << x << " ";
    cout << endl;
    
    vector<int> sortedDesc = heapSort(arr, false);
    cout << "Sorted descending: ";
    for (int x : sortedDesc) cout << x << " ";
    cout << endl;
}

void demonstrateTopKElements() {
    cout << "\n=== TOP K ELEMENTS DEMONSTRATION ===" << endl;
    
    vector<int> arr = {7, 10, 4, 3, 20, 15, 8, 5};
    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << endl;
    
    int k = 3;
    
    vector<int> kLargest = findKLargest(arr, k);
    cout << k << " largest elements: ";
    for (int x : kLargest) cout << x << " ";
    cout << endl;
    
    vector<int> kSmallest = findKSmallest(arr, k);
    cout << k << " smallest elements: ";
    for (int x : kSmallest) cout << x << " ";
    cout << endl;
}

void demonstrateAdvancedOperations() {
    cout << "\n=== ADVANCED HEAP OPERATIONS ===" << endl;
    
    vector<int> data = {4, 10, 3, 5, 1};
    MaxHeap<int> heap(data);
    
    cout << "Initial heap: ";
    heap.printHeap();
    
    // Update operation
    cout << "\nUpdating index 2 from " << heap.getHeapArray()[2] << " to 15" << endl;
    heap.update(2, 15);
    heap.printHeap();
    
    // Remove operation
    cout << "\nRemoving element at index 1" << endl;
    heap.remove(1);
    heap.printHeap();
    
    // Get top k elements
    vector<int> top3 = heap.getTopK(3);
    cout << "\nTop 3 elements: ";
    for (int x : top3) cout << x << " ";
    cout << endl;
    
    // Validation
    cout << "Is valid heap: " << (heap.isValidHeap() ? "Yes" : "No") << endl;
}

/*
 * ========================================================================
 * MAIN FUNCTION
 * ========================================================================
 */

int main() {
    cout << "=== BINARY HEAP COMPREHENSIVE GUIDE ===" << endl;
    
    demonstrateBasicOperations();
    demonstrateHeapSort();
    demonstrateTopKElements();
    demonstrateAdvancedOperations();
    
    cout << "\n=== All Heap Operations Demonstrated! ===" << endl;
    
    return 0;
}

/*
 * ============================================================================
 * HEAP COMPLEXITY ANALYSIS:
 * ============================================================================
 * 
 * BASIC OPERATIONS:
 * - Insert: O(log n) time, O(1) space
 * - Extract top: O(log n) time, O(1) space
 * - Peek top: O(1) time, O(1) space
 * - Build heap: O(n) time, O(1) space
 * 
 * ADVANCED OPERATIONS:
 * - Remove arbitrary element: O(log n) time
 * - Update element: O(log n) time
 * - Merge heaps: O((n + m) log(n + m)) time
 * 
 * ALGORITHMS:
 * - Heap Sort: O(n log n) time, O(1) space
 * - Find k largest/smallest: O(n log k) time, O(k) space
 * 
 * SPACE COMPLEXITY:
 * - Overall: O(n) for storing n elements
 * - Array representation is very space efficient
 * 
 * HEAP PROPERTIES:
 * - Complete binary tree structure
 * - Efficient array representation
 * - Parent-child relationships via array indices
 * - Logarithmic height guarantees
 * 
 * ============================================================================
 */
