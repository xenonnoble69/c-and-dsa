/*
 * ============================================================================
 * PRIORITY QUEUE - COMPREHENSIVE IMPLEMENTATION AND APPLICATIONS
 * ============================================================================
 * 
 * Priority Queue is an abstract data type where each element has a priority.
 * Elements are served based on priority rather than insertion order.
 * 
 * Key Properties:
 * - Higher priority elements are served first
 * - Can be implemented using heaps (most efficient)
 * - Supports dynamic priority updates
 * - Essential for many graph algorithms and scheduling
 * 
 * Types:
 * - Min Priority Queue: Lower values have higher priority
 * - Max Priority Queue: Higher values have higher priority
 * - Custom Priority Queue: User-defined priority function
 * 
 * Applications:
 * - Task scheduling in operating systems
 * - Dijkstra's shortest path algorithm
 * - Huffman coding for data compression
 * - A* search algorithm
 * - Event simulation systems
 * 
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <map>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <chrono>

using namespace std;

/*
 * ========================================================================
 * CUSTOM PRIORITY QUEUE IMPLEMENTATION
 * ========================================================================
 */

template<typename T, typename Priority = int>
class PriorityQueue {
private:
    struct PQElement {
        T data;
        Priority priority;
        size_t insertionOrder;  // For stable ordering
        
        PQElement(const T& d, const Priority& p, size_t order) 
            : data(d), priority(p), insertionOrder(order) {}
        
        // Comparator for priority queue (max heap by default)
        bool operator<(const PQElement& other) const {
            if (priority != other.priority) {
                return priority < other.priority;  // Higher priority first
            }
            return insertionOrder > other.insertionOrder;  // FIFO for same priority
        }
    };
    
    priority_queue<PQElement> pq;
    size_t insertionCounter;
    
public:
    PriorityQueue() : insertionCounter(0) {}
    
    /*
     * ====================================================================
     * BASIC OPERATIONS
     * ====================================================================
     */
    
    // Insert element with priority
    void push(const T& data, const Priority& priority) {
        pq.emplace(data, priority, insertionCounter++);
    }
    
    // Remove and return highest priority element
    T pop() {
        if (empty()) {
            throw runtime_error("Priority queue is empty");
        }
        
        T result = pq.top().data;
        pq.pop();
        return result;
    }
    
    // Get highest priority element without removing
    const T& top() const {
        if (empty()) {
            throw runtime_error("Priority queue is empty");
        }
        return pq.top().data;
    }
    
    // Get priority of top element
    Priority topPriority() const {
        if (empty()) {
            throw runtime_error("Priority queue is empty");
        }
        return pq.top().priority;
    }
    
    // Check if queue is empty
    bool empty() const {
        return pq.empty();
    }
    
    // Get number of elements
    size_t size() const {
        return pq.size();
    }
    
    /*
     * ====================================================================
     * UTILITY FUNCTIONS
     * ====================================================================
     */
    
    // Print all elements (destructive - empties the queue)
    void printAndClear() {
        cout << "Priority Queue contents (priority, data): ";
        while (!empty()) {
            auto elem = pq.top();
            pq.pop();
            cout << "(" << elem.priority << ", " << elem.data << ") ";
        }
        cout << endl;
    }
    
    // Get copy of all elements as vector
    vector<pair<T, Priority>> getAllElements() const {
        vector<pair<T, Priority>> result;
        priority_queue<PQElement> tempPQ = pq;
        
        while (!tempPQ.empty()) {
            auto elem = tempPQ.top();
            tempPQ.pop();
            result.emplace_back(elem.data, elem.priority);
        }
        
        return result;
    }
};

/*
 * ========================================================================
 * STL PRIORITY QUEUE EXAMPLES
 * ========================================================================
 */

void demonstrateSTLPriorityQueue() {
    cout << "=== STL PRIORITY QUEUE EXAMPLES ===" << endl;
    
    // Default max heap
    priority_queue<int> maxPQ;
    vector<int> values = {3, 1, 4, 1, 5, 9, 2, 6};
    
    cout << "Inserting into max priority queue: ";
    for (int val : values) {
        cout << val << " ";
        maxPQ.push(val);
    }
    cout << endl;
    
    cout << "Extracting from max priority queue: ";
    while (!maxPQ.empty()) {
        cout << maxPQ.top() << " ";
        maxPQ.pop();
    }
    cout << endl;
    
    // Min heap using greater comparator
    priority_queue<int, vector<int>, greater<int>> minPQ;
    
    cout << "\nInserting into min priority queue: ";
    for (int val : values) {
        cout << val << " ";
        minPQ.push(val);
    }
    cout << endl;
    
    cout << "Extracting from min priority queue: ";
    while (!minPQ.empty()) {
        cout << minPQ.top() << " ";
        minPQ.pop();
    }
    cout << endl;
}

/*
 * ========================================================================
 * ADVANCED PRIORITY QUEUE APPLICATIONS
 * ========================================================================
 */

// Task scheduling system
struct Task {
    string name;
    int priority;
    int duration;
    chrono::time_point<chrono::steady_clock> deadline;
    
    Task(const string& n, int p, int d) 
        : name(n), priority(p), duration(d) {
        deadline = chrono::steady_clock::now() + chrono::seconds(d * 2);
    }
    
    // Custom comparator for task scheduling
    struct Compare {
        bool operator()(const Task& a, const Task& b) const {
            // Higher priority first, then earlier deadline
            if (a.priority != b.priority) {
                return a.priority < b.priority;
            }
            return a.deadline > b.deadline;
        }
    };
};

class TaskScheduler {
private:
    priority_queue<Task, vector<Task>, Task::Compare> taskQueue;
    
public:
    void addTask(const string& name, int priority, int duration) {
        taskQueue.emplace(name, priority, duration);
        cout << "Added task: " << name << " (Priority: " << priority 
             << ", Duration: " << duration << ")" << endl;
    }
    
    void executeTasks() {
        cout << "\nExecuting tasks in priority order:" << endl;
        
        while (!taskQueue.empty()) {
            Task task = taskQueue.top();
            taskQueue.pop();
            
            cout << "Executing: " << task.name 
                 << " (Priority: " << task.priority 
                 << ", Duration: " << task.duration << ")" << endl;
        }
    }
    
    void showTaskQueue() const {
        priority_queue<Task, vector<Task>, Task::Compare> tempQueue = taskQueue;
        cout << "\nCurrent task queue:" << endl;
        
        while (!tempQueue.empty()) {
            Task task = tempQueue.top();
            tempQueue.pop();
            cout << "  " << task.name << " (Priority: " << task.priority << ")" << endl;
        }
    }
};

/*
 * ========================================================================
 * DIJKSTRA'S ALGORITHM USING PRIORITY QUEUE
 * ========================================================================
 */

class DijkstraGraph {
private:
    struct Edge {
        int destination;
        int weight;
        
        Edge(int dest, int w) : destination(dest), weight(w) {}
    };
    
    struct DijkstraNode {
        int vertex;
        int distance;
        
        DijkstraNode(int v, int d) : vertex(v), distance(d) {}
        
        // Min heap comparator (smaller distance has higher priority)
        bool operator>(const DijkstraNode& other) const {
            return distance > other.distance;
        }
    };
    
    vector<vector<Edge>> adjacencyList;
    int numVertices;
    
public:
    DijkstraGraph(int vertices) : numVertices(vertices) {
        adjacencyList.resize(vertices);
    }
    
    void addEdge(int source, int destination, int weight) {
        adjacencyList[source].emplace_back(destination, weight);
        // For undirected graph, uncomment the line below:
        // adjacencyList[destination].emplace_back(source, weight);
    }
    
    vector<int> shortestPath(int source) {
        vector<int> distances(numVertices, INT_MAX);
        vector<bool> visited(numVertices, false);
        
        // Min priority queue for Dijkstra's algorithm
        priority_queue<DijkstraNode, vector<DijkstraNode>, greater<DijkstraNode>> pq;
        
        distances[source] = 0;
        pq.emplace(source, 0);
        
        cout << "Running Dijkstra's algorithm from vertex " << source << ":" << endl;
        
        while (!pq.empty()) {
            DijkstraNode current = pq.top();
            pq.pop();
            
            if (visited[current.vertex]) continue;
            
            visited[current.vertex] = true;
            cout << "Processing vertex " << current.vertex 
                 << " with distance " << current.distance << endl;
            
            // Check all neighbors
            for (const Edge& edge : adjacencyList[current.vertex]) {
                int neighbor = edge.destination;
                int newDistance = distances[current.vertex] + edge.weight;
                
                if (newDistance < distances[neighbor]) {
                    distances[neighbor] = newDistance;
                    pq.emplace(neighbor, newDistance);
                    cout << "  Updated distance to vertex " << neighbor 
                         << ": " << newDistance << endl;
                }
            }
        }
        
        return distances;
    }
    
    void printGraph() const {
        cout << "Graph adjacency list:" << endl;
        for (int i = 0; i < numVertices; ++i) {
            cout << "Vertex " << i << ": ";
            for (const Edge& edge : adjacencyList[i]) {
                cout << "(" << edge.destination << ", " << edge.weight << ") ";
            }
            cout << endl;
        }
    }
};

/*
 * ========================================================================
 * K-WAY MERGE USING PRIORITY QUEUE
 * ========================================================================
 */

struct ListNode {
    int val;
    ListNode* next;
    
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* n) : val(x), next(n) {}
};

class KWayMerge {
private:
    struct ListNodeComparator {
        bool operator()(ListNode* a, ListNode* b) const {
            return a->val > b->val;  // Min heap
        }
    };
    
public:
    // Merge k sorted linked lists
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode*, vector<ListNode*>, ListNodeComparator> pq;
        
        // Add first node of each list to priority queue
        for (ListNode* head : lists) {
            if (head) {
                pq.push(head);
            }
        }
        
        ListNode dummy(0);
        ListNode* current = &dummy;
        
        while (!pq.empty()) {
            ListNode* node = pq.top();
            pq.pop();
            
            current->next = node;
            current = current->next;
            
            // Add next node from the same list
            if (node->next) {
                pq.push(node->next);
            }
        }
        
        return dummy.next;
    }
    
    // Merge k sorted arrays
    vector<int> mergeKArrays(vector<vector<int>>& arrays) {
        struct ArrayElement {
            int value;
            int arrayIndex;
            int elementIndex;
            
            ArrayElement(int v, int ai, int ei) 
                : value(v), arrayIndex(ai), elementIndex(ei) {}
            
            bool operator>(const ArrayElement& other) const {
                return value > other.value;  // Min heap
            }
        };
        
        priority_queue<ArrayElement, vector<ArrayElement>, greater<ArrayElement>> pq;
        
        // Add first element of each array
        for (int i = 0; i < arrays.size(); ++i) {
            if (!arrays[i].empty()) {
                pq.emplace(arrays[i][0], i, 0);
            }
        }
        
        vector<int> result;
        
        while (!pq.empty()) {
            ArrayElement elem = pq.top();
            pq.pop();
            
            result.push_back(elem.value);
            
            // Add next element from the same array
            if (elem.elementIndex + 1 < arrays[elem.arrayIndex].size()) {
                pq.emplace(arrays[elem.arrayIndex][elem.elementIndex + 1], 
                          elem.arrayIndex, elem.elementIndex + 1);
            }
        }
        
        return result;
    }
};

/*
 * ========================================================================
 * MEDIAN MAINTENANCE USING TWO HEAPS
 * ========================================================================
 */

class MedianFinder {
private:
    priority_queue<int> maxHeap;  // For smaller half
    priority_queue<int, vector<int>, greater<int>> minHeap;  // For larger half
    
public:
    void addNumber(int num) {
        // Add to appropriate heap
        if (maxHeap.empty() || num <= maxHeap.top()) {
            maxHeap.push(num);
        } else {
            minHeap.push(num);
        }
        
        // Balance heaps
        if (maxHeap.size() > minHeap.size() + 1) {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        } else if (minHeap.size() > maxHeap.size() + 1) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }
    
    double findMedian() const {
        if (maxHeap.size() == minHeap.size()) {
            return (maxHeap.top() + minHeap.top()) / 2.0;
        } else if (maxHeap.size() > minHeap.size()) {
            return maxHeap.top();
        } else {
            return minHeap.top();
        }
    }
    
    void printHeaps() const {
        cout << "Max heap (smaller half): ";
        priority_queue<int> tempMax = maxHeap;
        while (!tempMax.empty()) {
            cout << tempMax.top() << " ";
            tempMax.pop();
        }
        cout << endl;
        
        cout << "Min heap (larger half): ";
        priority_queue<int, vector<int>, greater<int>> tempMin = minHeap;
        while (!tempMin.empty()) {
            cout << tempMin.top() << " ";
            tempMin.pop();
        }
        cout << endl;
    }
};

/*
 * ========================================================================
 * DEMONSTRATION FUNCTIONS
 * ========================================================================
 */

void demonstrateCustomPriorityQueue() {
    cout << "\n=== CUSTOM PRIORITY QUEUE ===" << endl;
    
    PriorityQueue<string, int> pq;
    
    pq.push("Low priority task", 1);
    pq.push("High priority task", 10);
    pq.push("Medium priority task", 5);
    pq.push("Critical task", 15);
    pq.push("Another high priority", 10);
    
    cout << "Processing tasks by priority:" << endl;
    while (!pq.empty()) {
        cout << "Task: " << pq.top() 
             << " (Priority: " << pq.topPriority() << ")" << endl;
        pq.pop();
    }
}

void demonstrateTaskScheduler() {
    cout << "\n=== TASK SCHEDULER ===" << endl;
    
    TaskScheduler scheduler;
    
    scheduler.addTask("Database backup", 5, 30);
    scheduler.addTask("Security scan", 8, 15);
    scheduler.addTask("Log cleanup", 2, 5);
    scheduler.addTask("System update", 9, 45);
    scheduler.addTask("Data analysis", 6, 20);
    
    scheduler.showTaskQueue();
    scheduler.executeTasks();
}

void demonstrateDijkstra() {
    cout << "\n=== DIJKSTRA'S ALGORITHM ===" << endl;
    
    DijkstraGraph graph(6);
    
    // Add edges (source, destination, weight)
    graph.addEdge(0, 1, 4);
    graph.addEdge(0, 2, 2);
    graph.addEdge(1, 2, 1);
    graph.addEdge(1, 3, 5);
    graph.addEdge(2, 3, 8);
    graph.addEdge(2, 4, 10);
    graph.addEdge(3, 4, 2);
    graph.addEdge(3, 5, 6);
    graph.addEdge(4, 5, 3);
    
    graph.printGraph();
    
    vector<int> distances = graph.shortestPath(0);
    
    cout << "\nShortest distances from vertex 0:" << endl;
    for (int i = 0; i < distances.size(); ++i) {
        cout << "To vertex " << i << ": " << distances[i] << endl;
    }
}

void demonstrateKWayMerge() {
    cout << "\n=== K-WAY MERGE ===" << endl;
    
    KWayMerge merger;
    
    // Test with arrays
    vector<vector<int>> arrays = {
        {1, 4, 7},
        {2, 5, 8},
        {3, 6, 9}
    };
    
    cout << "Input arrays:" << endl;
    for (int i = 0; i < arrays.size(); ++i) {
        cout << "Array " << i << ": ";
        for (int val : arrays[i]) {
            cout << val << " ";
        }
        cout << endl;
    }
    
    vector<int> merged = merger.mergeKArrays(arrays);
    cout << "Merged result: ";
    for (int val : merged) {
        cout << val << " ";
    }
    cout << endl;
}

void demonstrateMedianFinder() {
    cout << "\n=== MEDIAN MAINTENANCE ===" << endl;
    
    MedianFinder medianFinder;
    vector<int> numbers = {5, 15, 1, 3, 8, 7, 9, 2, 6};
    
    for (int num : numbers) {
        medianFinder.addNumber(num);
        cout << "Added " << num << ", median: " << medianFinder.findMedian() << endl;
    }
    
    cout << "\nFinal heap state:" << endl;
    medianFinder.printHeaps();
}

/*
 * ========================================================================
 * MAIN FUNCTION
 * ========================================================================
 */

int main() {
    cout << "=== PRIORITY QUEUE COMPREHENSIVE GUIDE ===" << endl;
    
    demonstrateSTLPriorityQueue();
    demonstrateCustomPriorityQueue();
    demonstrateTaskScheduler();
    demonstrateDijkstra();
    demonstrateKWayMerge();
    demonstrateMedianFinder();
    
    cout << "\n=== All Priority Queue Applications Demonstrated! ===" << endl;
    
    return 0;
}

/*
 * ============================================================================
 * PRIORITY QUEUE COMPLEXITY ANALYSIS:
 * ============================================================================
 * 
 * BASIC OPERATIONS (Heap-based implementation):
 * - Push: O(log n) time, O(1) space
 * - Pop: O(log n) time, O(1) space
 * - Top: O(1) time, O(1) space
 * - Size/Empty: O(1) time, O(1) space
 * 
 * APPLICATIONS COMPLEXITY:
 * 
 * TASK SCHEDULING:
 * - Add task: O(log n)
 * - Get next task: O(log n)
 * - Overall: O(n log n) for n tasks
 * 
 * DIJKSTRA'S ALGORITHM:
 * - Time: O((V + E) log V) where V = vertices, E = edges
 * - Space: O(V) for distance array and priority queue
 * 
 * K-WAY MERGE:
 * - Time: O(N log k) where N = total elements, k = number of arrays
 * - Space: O(k) for priority queue
 * 
 * MEDIAN MAINTENANCE:
 * - Add number: O(log n)
 * - Find median: O(1)
 * - Space: O(n) for storing all numbers
 * 
 * COMPARISON WITH OTHER DATA STRUCTURES:
 * 
 * vs. Sorted Array:
 * - Priority Queue: O(log n) insert, O(log n) extract
 * - Sorted Array: O(n) insert, O(1) extract
 * 
 * vs. Unsorted Array:
 * - Priority Queue: O(log n) insert, O(log n) extract
 * - Unsorted Array: O(1) insert, O(n) extract
 * 
 * vs. Binary Search Tree:
 * - Priority Queue: Specialized for min/max operations
 * - BST: More general but similar complexity
 * 
 * WHEN TO USE PRIORITY QUEUE:
 * - Need frequent access to min/max element
 * - Processing elements in priority order
 * - Implementing algorithms like Dijkstra's, Prim's
 * - Task scheduling and event simulation
 * - Finding k largest/smallest elements
 * 
 * ============================================================================
 */
