/*
 * ============================================================================
 * ADVANCED STL FEATURES - COMPREHENSIVE GUIDE
 * ============================================================================
 * 
 * THEORY:
 * This module covers advanced STL features that optimize performance and
 * provide sophisticated functionality:
 * 
 * 1. MOVE SEMANTICS (C++11):
 *    - Rvalue references and perfect forwarding
 *    - Move constructors and move assignment operators
 *    - std::move and std::forward
 *    - Impact on STL containers and algorithms
 * 
 * 2. EMPLACE OPERATIONS (C++11):
 *    - In-place construction to avoid unnecessary copies
 *    - emplace, emplace_back, emplace_front
 *    - Comparison with insert/push operations
 * 
 * 3. ALLOCATORS:
 *    - Custom memory management for containers
 *    - Standard allocators and custom allocators
 *    - Allocator-aware containers
 * 
 * 4. ADVANCED CONTAINER FEATURES:
 *    - Container adaptors and their underlying containers
 *    - Exception safety guarantees
 *    - Iterator invalidation rules
 *    - Container selection guidelines
 * 
 * 5. ADVANCED ALGORITHM FEATURES:
 *    - Execution policies (C++17)
 *    - Ranges library preview (C++20)
 *    - Algorithm complexity guarantees
 *    - Custom algorithm design
 * 
 * PERFORMANCE IMPLICATIONS:
 * Understanding these features is crucial for writing high-performance code,
 * especially in systems programming, game development, and real-time applications.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <utility>
#include <algorithm>
#include <numeric>
#include <chrono>
#include <deque>
#include <list>
#include <set>
#include <map>
#include <unordered_map>
#include <queue>
#include <stack>
#include <array>
#include <forward_list>
#include <thread>
#include <future>
#include <random>

// C++17 features (if available)
#if __cplusplus >= 201703L
#include <execution>
#endif

using namespace std;
using namespace std::chrono;

/*
 * ========================================================================
 * 1. MOVE SEMANTICS AND PERFECT FORWARDING
 * ========================================================================
 */

// A class to demonstrate move semantics
class MoveableResource {
private:
    int* data;
    size_t size;
    string name;
    
public:
    // Constructor
    MoveableResource(const string& n, size_t s) : name(n), size(s) {
        data = new int[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = static_cast<int>(i);
        }
        cout << "Constructed " << name << " with " << size << " elements" << endl;
    }
    
    // Copy constructor
    MoveableResource(const MoveableResource& other) : name(other.name + "_copy"), size(other.size) {
        data = new int[size];
        copy(other.data, other.data + size, data);
        cout << "Copied " << other.name << " -> " << name << endl;
    }
    
    // Move constructor
    MoveableResource(MoveableResource&& other) noexcept 
        : data(other.data), size(other.size), name(move(other.name) + "_moved") {
        other.data = nullptr;
        other.size = 0;
        cout << "Moved " << name << endl;
    }
    
    // Copy assignment
    MoveableResource& operator=(const MoveableResource& other) {
        if (this != &other) {
            delete[] data;
            name = other.name + "_assigned";
            size = other.size;
            data = new int[size];
            copy(other.data, other.data + size, data);
            cout << "Copy assigned " << name << endl;
        }
        return *this;
    }
    
    // Move assignment
    MoveableResource& operator=(MoveableResource&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            name = move(other.name) + "_move_assigned";
            other.data = nullptr;
            other.size = 0;
            cout << "Move assigned " << name << endl;
        }
        return *this;
    }
    
    // Destructor
    ~MoveableResource() {
        delete[] data;
        if (!name.empty()) {
            cout << "Destroyed " << name << endl;
        }
    }
    
    // Utility functions
    const string& getName() const { return name; }
    size_t getSize() const { return size; }
    bool isValid() const { return data != nullptr; }
};

// Perfect forwarding example
template<typename T>
void processResource(T&& resource) {
    cout << "Processing resource: " << resource.getName() << endl;
    // Forward the resource to another function
    vector<MoveableResource> storage;
    storage.emplace_back(forward<T>(resource));
}

void demonstrateMoveSemantics() {
    cout << "1. MOVE SEMANTICS AND PERFECT FORWARDING" << endl;
    cout << "=========================================" << endl;
    
    cout << "Creating original resource:" << endl;
    MoveableResource original("original", 1000);
    
    cout << "\nCopy construction:" << endl;
    MoveableResource copied = original;
    
    cout << "\nMove construction:" << endl;
    MoveableResource moved = move(original);
    cout << "Original after move - valid: " << boolalpha << original.isValid() << endl;
    
    cout << "\nVector operations with move semantics:" << endl;
    vector<MoveableResource> resources;
    
    // Push back with copy
    cout << "push_back with copy:" << endl;
    resources.push_back(copied);
    
    // Push back with move
    cout << "push_back with move:" << endl;
    resources.push_back(move(moved));
    
    // Emplace back (construct in place)
    cout << "emplace_back (construct in place):" << endl;
    resources.emplace_back("emplaced", 500);
    
    cout << "\nUsing perfect forwarding:" << endl;
    MoveableResource temp("temp", 100);
    processResource(temp);                    // lvalue reference
    processResource(MoveableResource("rvalue", 200));  // rvalue reference
    
    cout << "\nContainer contents:" << endl;
    for (size_t i = 0; i < resources.size(); ++i) {
        cout << "Resource " << i << ": " << resources[i].getName() 
             << " (size: " << resources[i].getSize() << ")" << endl;
    }
    
    cout << endl;
}

/*
 * ========================================================================
 * 2. EMPLACE OPERATIONS
 * ========================================================================
 */

struct Point3D {
    double x, y, z;
    string label;
    
    Point3D(double x_val, double y_val, double z_val, const string& l = "") 
        : x(x_val), y(y_val), z(z_val), label(l) {
        cout << "Point3D constructed: (" << x << ", " << y << ", " << z << ") " << label << endl;
    }
    
    Point3D(const Point3D& other) : x(other.x), y(other.y), z(other.z), label(other.label + "_copy") {
        cout << "Point3D copied: " << label << endl;
    }
    
    Point3D(Point3D&& other) noexcept 
        : x(other.x), y(other.y), z(other.z), label(move(other.label) + "_moved") {
        cout << "Point3D moved: " << label << endl;
    }
    
    ~Point3D() {
        if (!label.empty()) {
            cout << "Point3D destroyed: " << label << endl;
        }
    }
};

void demonstrateEmplaceOperations() {
    cout << "2. EMPLACE OPERATIONS" << endl;
    cout << "=====================" << endl;
    
    // Vector emplace operations
    cout << "Vector emplace vs push_back:" << endl;
    vector<Point3D> points;
    
    cout << "\nUsing push_back (creates temporary, then moves):" << endl;
    points.push_back(Point3D(1.0, 2.0, 3.0, "pushed"));
    
    cout << "\nUsing emplace_back (constructs in place):" << endl;
    points.emplace_back(4.0, 5.0, 6.0, "emplaced");
    
    cout << "\nUsing emplace (insert at position):" << endl;
    points.emplace(points.begin(), 0.0, 0.0, 0.0, "emplaced_at_begin");
    
    // Map emplace operations
    cout << "\nMap emplace operations:" << endl;
    map<string, Point3D> point_map;
    
    cout << "Using emplace with piecewise construction:" << endl;
    point_map.emplace(piecewise_construct,
                     forward_as_tuple("origin"),
                     forward_as_tuple(0.0, 0.0, 0.0, "map_origin"));
    
    cout << "Using try_emplace (C++17):" << endl;
    #if __cplusplus >= 201703L
    point_map.try_emplace("center", 5.0, 5.0, 5.0, "map_center");
    #endif
    
    // Set emplace operations
    cout << "\nSet emplace operations:" << endl;
    set<pair<int, string>> coord_set;
    
    cout << "Using emplace:" << endl;
    auto result = coord_set.emplace(10, "ten");
    cout << "Emplace successful: " << boolalpha << result.second << endl;
    
    cout << "Using emplace_hint:" << endl;
    coord_set.emplace_hint(result.first, 20, "twenty");
    
    // Queue emplace operations
    cout << "\nQueue/Stack emplace operations:" << endl;
    queue<Point3D> point_queue;
    stack<Point3D> point_stack;
    
    cout << "Queue emplace:" << endl;
    point_queue.emplace(7.0, 8.0, 9.0, "queued");
    
    cout << "Stack emplace:" << endl;
    point_stack.emplace(10.0, 11.0, 12.0, "stacked");
    
    cout << "\nFinal container sizes:" << endl;
    cout << "Vector: " << points.size() << " elements" << endl;
    cout << "Map: " << point_map.size() << " elements" << endl;
    cout << "Set: " << coord_set.size() << " elements" << endl;
    cout << "Queue: " << point_queue.size() << " elements" << endl;
    cout << "Stack: " << point_stack.size() << " elements" << endl;
    
    cout << endl;
}

/*
 * ========================================================================
 * 3. CUSTOM ALLOCATORS
 * ========================================================================
 */

// Simple pool allocator for demonstration
template<typename T>
class PoolAllocator {
private:
    static constexpr size_t POOL_SIZE = 1024;
    alignas(T) char pool[POOL_SIZE * sizeof(T)];
    bool used[POOL_SIZE];
    size_t next_free;
    
public:
    using value_type = T;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using pointer = T*;
    using const_pointer = const T*;
    
    PoolAllocator() : next_free(0) {
        fill(used, used + POOL_SIZE, false);
        cout << "PoolAllocator created with " << POOL_SIZE << " slots" << endl;
    }
    
    template<typename U>
    PoolAllocator(const PoolAllocator<U>&) : PoolAllocator() {}
    
    pointer allocate(size_type n) {
        if (n != 1) {
            throw bad_alloc();  // This simple allocator only handles single objects
        }
        
        // Find free slot
        for (size_t i = next_free; i < POOL_SIZE; ++i) {
            if (!used[i]) {
                used[i] = true;
                next_free = i + 1;
                cout << "Allocated slot " << i << endl;
                return reinterpret_cast<pointer>(pool + i * sizeof(T));
            }
        }
        
        // Wrap around
        for (size_t i = 0; i < next_free; ++i) {
            if (!used[i]) {
                used[i] = true;
                next_free = i + 1;
                cout << "Allocated slot " << i << " (wrapped)" << endl;
                return reinterpret_cast<pointer>(pool + i * sizeof(T));
            }
        }
        
        throw bad_alloc();
    }
    
    void deallocate(pointer p, size_type n) {
        if (n != 1) return;
        
        size_t index = (reinterpret_cast<char*>(p) - pool) / sizeof(T);
        if (index < POOL_SIZE) {
            used[index] = false;
            if (index < next_free) {
                next_free = index;
            }
            cout << "Deallocated slot " << index << endl;
        }
    }
    
    template<typename U>
    bool operator==(const PoolAllocator<U>&) const { return true; }
    
    template<typename U>
    bool operator!=(const PoolAllocator<U>&) const { return false; }
};

// Tracking allocator to monitor allocations
template<typename T>
class TrackingAllocator {
private:
    static size_t allocation_count;
    static size_t deallocation_count;
    static size_t bytes_allocated;
    
public:
    using value_type = T;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using pointer = T*;
    using const_pointer = const T*;
    
    TrackingAllocator() = default;
    
    template<typename U>
    TrackingAllocator(const TrackingAllocator<U>&) {}
    
    pointer allocate(size_type n) {
        allocation_count++;
        bytes_allocated += n * sizeof(T);
        cout << "TrackingAllocator: Allocated " << n * sizeof(T) << " bytes" << endl;
        return static_cast<pointer>(::operator new(n * sizeof(T)));
    }
    
    void deallocate(pointer p, size_type n) {
        deallocation_count++;
        cout << "TrackingAllocator: Deallocated " << n * sizeof(T) << " bytes" << endl;
        ::operator delete(p);
    }
    
    static void printStats() {
        cout << "Allocation Statistics:" << endl;
        cout << "  Allocations: " << allocation_count << endl;
        cout << "  Deallocations: " << deallocation_count << endl;
        cout << "  Bytes allocated: " << bytes_allocated << endl;
        cout << "  Leaked allocations: " << (allocation_count - deallocation_count) << endl;
    }
    
    static void resetStats() {
        allocation_count = 0;
        deallocation_count = 0;
        bytes_allocated = 0;
    }
    
    template<typename U>
    bool operator==(const TrackingAllocator<U>&) const { return true; }
    
    template<typename U>
    bool operator!=(const TrackingAllocator<U>&) const { return false; }
};

// Static member definitions
template<typename T>
size_t TrackingAllocator<T>::allocation_count = 0;

template<typename T>
size_t TrackingAllocator<T>::deallocation_count = 0;

template<typename T>
size_t TrackingAllocator<T>::bytes_allocated = 0;

void demonstrateCustomAllocators() {
    cout << "3. CUSTOM ALLOCATORS" << endl;
    cout << "====================" << endl;
    
    // Pool allocator demonstration
    cout << "Pool Allocator demonstration:" << endl;
    {
        vector<int, PoolAllocator<int>> pool_vector;
        cout << "Adding elements to pool-allocated vector:" << endl;
        
        for (int i = 0; i < 5; ++i) {
            pool_vector.push_back(i * 10);
        }
        
        cout << "Vector contents: ";
        for (int val : pool_vector) {
            cout << val << " ";
        }
        cout << endl;
    }
    cout << "Pool allocator scope ended" << endl;
    
    // Tracking allocator demonstration
    cout << "\nTracking Allocator demonstration:" << endl;
    TrackingAllocator<int>::resetStats();
    
    {
        vector<int, TrackingAllocator<int>> tracked_vector;
        map<string, int, less<string>, TrackingAllocator<pair<const string, int>>> tracked_map;
        
        cout << "Operations with tracked containers:" << endl;
        
        // Vector operations
        for (int i = 0; i < 10; ++i) {
            tracked_vector.push_back(i);
        }
        
        // Map operations
        tracked_map["one"] = 1;
        tracked_map["two"] = 2;
        tracked_map["three"] = 3;
        
        cout << "Intermediate statistics:" << endl;
        TrackingAllocator<int>::printStats();
        
        // Force reallocation
        tracked_vector.reserve(1000);
        
        cout << "After reserve(1000):" << endl;
        TrackingAllocator<int>::printStats();
    }
    
    cout << "Final statistics after containers destroyed:" << endl;
    TrackingAllocator<int>::printStats();
    
    // Standard allocator usage
    cout << "\nStandard allocator direct usage:" << endl;
    allocator<int> std_alloc;
    int* arr = std_alloc.allocate(5);
    
    for (int i = 0; i < 5; ++i) {
        std_alloc.construct(arr + i, i * i);
    }
    
    cout << "Allocated array: ";
    for (int i = 0; i < 5; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    for (int i = 0; i < 5; ++i) {
        std_alloc.destroy(arr + i);
    }
    std_alloc.deallocate(arr, 5);
    
    cout << endl;
}

/*
 * ========================================================================
 * 4. ADVANCED CONTAINER FEATURES
 * ========================================================================
 */

void demonstrateContainerFeatures() {
    cout << "4. ADVANCED CONTAINER FEATURES" << endl;
    cout << "===============================" << endl;
    
    // Container adaptors with different underlying containers
    cout << "Container adaptors with different underlying containers:" << endl;
    
    // Stack with different underlying containers
    stack<int> default_stack;                    // deque by default
    stack<int, vector<int>> vector_stack;        // vector underlying
    stack<int, list<int>> list_stack;            // list underlying
    
    for (int i = 1; i <= 3; ++i) {
        default_stack.push(i);
        vector_stack.push(i * 10);
        list_stack.push(i * 100);
    }
    
    cout << "Stack tops - default: " << default_stack.top() 
         << ", vector: " << vector_stack.top() 
         << ", list: " << list_stack.top() << endl;
    
    // Priority queue with custom comparator and container
    cout << "\nPriority queues with custom configurations:" << endl;
    priority_queue<int> max_heap;                                    // max heap (default)
    priority_queue<int, vector<int>, greater<int>> min_heap;        // min heap
    priority_queue<int, deque<int>, greater<int>> deque_min_heap;   // deque-based min heap
    
    vector<int> values = {30, 10, 50, 20, 40};
    for (int val : values) {
        max_heap.push(val);
        min_heap.push(val);
        deque_min_heap.push(val);
    }
    
    cout << "Max heap top: " << max_heap.top() << endl;
    cout << "Min heap top: " << min_heap.top() << endl;
    cout << "Deque min heap top: " << deque_min_heap.top() << endl;
    
    // Exception safety demonstration
    cout << "\nException safety guarantees:" << endl;
    vector<string> safe_vector;
    safe_vector.reserve(10);  // Strong exception safety for push_back
    
    try {
        safe_vector.push_back("safe");
        safe_vector.push_back("operation");
        cout << "Vector size after safe operations: " << safe_vector.size() << endl;
    } catch (...) {
        cout << "Exception caught, but vector state is consistent" << endl;
    }
    
    // Iterator invalidation awareness
    cout << "\nIterator invalidation awareness:" << endl;
    vector<int> iter_test = {1, 2, 3, 4, 5};
    auto it = iter_test.begin() + 2;  // Points to element 3
    cout << "Iterator points to: " << *it << endl;
    
    iter_test.insert(iter_test.begin(), 0);  // This invalidates 'it'
    cout << "After insert at beginning, vector size: " << iter_test.size() << endl;
    // Note: 'it' is now invalid and shouldn't be used
    
    // Refresh iterator
    it = find(iter_test.begin(), iter_test.end(), 3);
    if (it != iter_test.end()) {
        cout << "Found element 3 at new position" << endl;
    }
    
    // Container selection guidelines demonstration
    cout << "\nContainer selection performance comparison:" << endl;
    const int N = 10000;
    
    // Vector vs List for different operations
    vector<int> perf_vector;
    list<int> perf_list;
    
    auto start_time = high_resolution_clock::now();
    
    // Sequential insertion (vector advantage)
    for (int i = 0; i < N; ++i) {
        perf_vector.push_back(i);
    }
    auto vector_insert_time = high_resolution_clock::now() - start_time;
    
    start_time = high_resolution_clock::now();
    for (int i = 0; i < N; ++i) {
        perf_list.push_back(i);
    }
    auto list_insert_time = high_resolution_clock::now() - start_time;
    
    cout << "Sequential insertion (microseconds):" << endl;
    cout << "  Vector: " << duration_cast<microseconds>(vector_insert_time).count() << endl;
    cout << "  List: " << duration_cast<microseconds>(list_insert_time).count() << endl;
    
    // Random access (vector advantage)
    start_time = high_resolution_clock::now();
    volatile int sum1 = 0;
    for (int i = 0; i < 1000; ++i) {
        sum1 += perf_vector[i * (N/1000)];
    }
    auto vector_access_time = high_resolution_clock::now() - start_time;
    
    start_time = high_resolution_clock::now();
    volatile int sum2 = 0;
    auto list_it = perf_list.begin();
    for (int i = 0; i < 1000; ++i) {
        advance(list_it, N/1000);
        sum2 += *list_it;
        list_it = perf_list.begin();  // Reset for next iteration
    }
    auto list_access_time = high_resolution_clock::now() - start_time;
    
    cout << "Random access (microseconds):" << endl;
    cout << "  Vector: " << duration_cast<microseconds>(vector_access_time).count() << endl;
    cout << "  List: " << duration_cast<microseconds>(list_access_time).count() << endl;
    
    cout << endl;
}

/*
 * ========================================================================
 * 5. ADVANCED ALGORITHM FEATURES
 * ========================================================================
 */

// Custom algorithm example
template<typename InputIt, typename OutputIt, typename UnaryPredicate, typename UnaryOperation>
OutputIt transform_if(InputIt first, InputIt last, OutputIt d_first,
                     UnaryPredicate pred, UnaryOperation op) {
    while (first != last) {
        if (pred(*first)) {
            *d_first = op(*first);
            ++d_first;
        }
        ++first;
    }
    return d_first;
}

// Parallel execution example (C++17)
void demonstrateParallelExecution() {
    cout << "Parallel execution policies (C++17):" << endl;
    
    #if __cplusplus >= 201703L
    vector<int> large_data(1000000);
    iota(large_data.begin(), large_data.end(), 1);
    
    // Sequential execution
    auto start = high_resolution_clock::now();
    auto sum_seq = reduce(execution::seq, large_data.begin(), large_data.end(), 0LL);
    auto seq_time = high_resolution_clock::now() - start;
    
    // Parallel execution
    start = high_resolution_clock::now();
    auto sum_par = reduce(execution::par, large_data.begin(), large_data.end(), 0LL);
    auto par_time = high_resolution_clock::now() - start;
    
    cout << "Sequential sum: " << sum_seq << " (time: " 
         << duration_cast<microseconds>(seq_time).count() << " μs)" << endl;
    cout << "Parallel sum: " << sum_par << " (time: " 
         << duration_cast<microseconds>(par_time).count() << " μs)" << endl;
    
    // Parallel sorting
    vector<int> sort_data(100000);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 1000000);
    generate(sort_data.begin(), sort_data.end(), [&]() { return dis(gen); });
    
    vector<int> seq_data = sort_data;
    vector<int> par_data = sort_data;
    
    start = high_resolution_clock::now();
    sort(execution::seq, seq_data.begin(), seq_data.end());
    seq_time = high_resolution_clock::now() - start;
    
    start = high_resolution_clock::now();
    sort(execution::par, par_data.begin(), par_data.end());
    par_time = high_resolution_clock::now() - start;
    
    cout << "Sequential sort time: " << duration_cast<microseconds>(seq_time).count() << " μs" << endl;
    cout << "Parallel sort time: " << duration_cast<microseconds>(par_time).count() << " μs" << endl;
    
    #else
    cout << "C++17 execution policies not available in this compiler" << endl;
    #endif
}

void demonstrateAdvancedAlgorithms() {
    cout << "5. ADVANCED ALGORITHM FEATURES" << endl;
    cout << "===============================" << endl;
    
    // Custom algorithm demonstration
    cout << "Custom transform_if algorithm:" << endl;
    vector<int> input = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<int> output;
    
    // Transform even numbers by squaring them
    transform_if(input.begin(), input.end(), back_inserter(output),
                [](int x) { return x % 2 == 0; },  // predicate: even numbers
                [](int x) { return x * x; });       // operation: square
    
    cout << "Input: ";
    for (int x : input) cout << x << " ";
    cout << endl;
    
    cout << "Output (squared even numbers): ";
    for (int x : output) cout << x << " ";
    cout << endl;
    
    // Algorithm complexity demonstration
    cout << "\nAlgorithm complexity demonstration:" << endl;
    vector<int> search_data(100000);
    iota(search_data.begin(), search_data.end(), 1);
    
    // Linear search vs binary search
    int target = 75000;
    
    auto start = high_resolution_clock::now();
    auto linear_result = find(search_data.begin(), search_data.end(), target);
    auto linear_time = high_resolution_clock::now() - start;
    
    start = high_resolution_clock::now();
    auto binary_result = lower_bound(search_data.begin(), search_data.end(), target);
    auto binary_time = high_resolution_clock::now() - start;
    
    cout << "Searching for " << target << " in " << search_data.size() << " elements:" << endl;
    cout << "Linear search: " << (linear_result != search_data.end() ? "found" : "not found")
         << " (time: " << duration_cast<nanoseconds>(linear_time).count() << " ns)" << endl;
    cout << "Binary search: " << (binary_result != search_data.end() && *binary_result == target ? "found" : "not found")
         << " (time: " << duration_cast<nanoseconds>(binary_time).count() << " ns)" << endl;
    
    // Advanced numeric algorithms
    cout << "\nAdvanced numeric algorithms:" << endl;
    vector<int> numeric_data = {1, 2, 3, 4, 5};
    
    // Partial sums
    vector<int> partial_sums;
    partial_sum(numeric_data.begin(), numeric_data.end(), back_inserter(partial_sums));
    cout << "Partial sums: ";
    for (int x : partial_sums) cout << x << " ";
    cout << endl;
    
    // Adjacent differences
    vector<int> differences;
    adjacent_difference(partial_sums.begin(), partial_sums.end(), back_inserter(differences));
    cout << "Adjacent differences: ";
    for (int x : differences) cout << x << " ";
    cout << endl;
    
    // Inner product
    vector<int> weights = {2, 3, 1, 4, 5};
    int weighted_sum = inner_product(numeric_data.begin(), numeric_data.end(), 
                                   weights.begin(), 0);
    cout << "Weighted sum: " << weighted_sum << endl;
    
    // Parallel execution demonstration
    demonstrateParallelExecution();
    
    cout << endl;
}

/*
 * ========================================================================
 * 6. MEMORY AND PERFORMANCE OPTIMIZATION
 * ========================================================================
 */

void demonstrateMemoryOptimization() {
    cout << "6. MEMORY AND PERFORMANCE OPTIMIZATION" << endl;
    cout << "=======================================" << endl;
    
    // Memory alignment and cache efficiency
    cout << "Memory alignment considerations:" << endl;
    
    struct UnalignedStruct {
        char c;
        int i;
        char c2;
        double d;
    };
    
    struct AlignedStruct {
        double d;  // 8 bytes, naturally aligned
        int i;     // 4 bytes
        char c;    // 1 byte
        char c2;   // 1 byte
        // 2 bytes padding to align to 8-byte boundary
    };
    
    cout << "UnalignedStruct size: " << sizeof(UnalignedStruct) << " bytes" << endl;
    cout << "AlignedStruct size: " << sizeof(AlignedStruct) << " bytes" << endl;
    
    // Cache-friendly vs cache-unfriendly access patterns
    cout << "\nCache efficiency demonstration:" << endl;
    const int MATRIX_SIZE = 512;
    vector<vector<int>> matrix(MATRIX_SIZE, vector<int>(MATRIX_SIZE, 1));
    
    // Row-major access (cache-friendly)
    auto start = high_resolution_clock::now();
    volatile long sum1 = 0;
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            sum1 += matrix[i][j];
        }
    }
    auto row_major_time = high_resolution_clock::now() - start;
    
    // Column-major access (cache-unfriendly)
    start = high_resolution_clock::now();
    volatile long sum2 = 0;
    for (int j = 0; j < MATRIX_SIZE; ++j) {
        for (int i = 0; i < MATRIX_SIZE; ++i) {
            sum2 += matrix[i][j];
        }
    }
    auto col_major_time = high_resolution_clock::now() - start;
    
    cout << "Row-major access time: " << duration_cast<microseconds>(row_major_time).count() << " μs" << endl;
    cout << "Column-major access time: " << duration_cast<microseconds>(col_major_time).count() << " μs" << endl;
    cout << "Performance ratio: " << 
            static_cast<double>(duration_cast<microseconds>(col_major_time).count()) /
            duration_cast<microseconds>(row_major_time).count() << "x" << endl;
    
    // Memory pool vs individual allocations
    cout << "\nMemory allocation patterns:" << endl;
    const int NUM_OBJECTS = 10000;
    
    // Individual allocations
    start = high_resolution_clock::now();
    vector<unique_ptr<Point3D>> individual_objects;
    for (int i = 0; i < NUM_OBJECTS; ++i) {
        individual_objects.push_back(make_unique<Point3D>(i, i+1, i+2, ""));
    }
    individual_objects.clear();  // Deallocate
    auto individual_time = high_resolution_clock::now() - start;
    
    // Contiguous allocation
    start = high_resolution_clock::now();
    vector<Point3D> contiguous_objects;
    contiguous_objects.reserve(NUM_OBJECTS);
    for (int i = 0; i < NUM_OBJECTS; ++i) {
        contiguous_objects.emplace_back(i, i+1, i+2, "");
    }
    contiguous_objects.clear();
    auto contiguous_time = high_resolution_clock::now() - start;
    
    cout << "Individual allocations time: " << duration_cast<microseconds>(individual_time).count() << " μs" << endl;
    cout << "Contiguous allocations time: " << duration_cast<microseconds>(contiguous_time).count() << " μs" << endl;
    cout << "Performance improvement: " << 
            static_cast<double>(duration_cast<microseconds>(individual_time).count()) /
            duration_cast<microseconds>(contiguous_time).count() << "x" << endl;
    
    // Small string optimization demonstration
    cout << "\nSmall String Optimization (SSO):" << endl;
    cout << "sizeof(string): " << sizeof(string) << " bytes" << endl;
    
    string short_str = "short";
    string long_str = "this is a very long string that exceeds SSO buffer size";
    
    cout << "Short string ('" << short_str << "') likely uses SSO" << endl;
    cout << "Long string length: " << long_str.length() << " (likely heap allocated)" << endl;
    
    cout << endl;
}

/*
 * ========================================================================
 * MAIN FUNCTION
 * ========================================================================
 */

int main() {
    cout << "=== ADVANCED STL FEATURES COMPREHENSIVE GUIDE ===" << endl << endl;
    
    demonstrateMoveSemantics();
    demonstrateEmplaceOperations();
    demonstrateCustomAllocators();
    demonstrateContainerFeatures();
    demonstrateAdvancedAlgorithms();
    demonstrateMemoryOptimization();
    
    cout << "=== Advanced STL Features Mastery Complete! ===" << endl;
    
    return 0;
}

/*
 * ============================================================================
 * PRACTICE EXERCISES:
 * ============================================================================
 * 
 * 1. Implement a custom allocator that tracks memory usage statistics.
 * 
 * 2. Create a container wrapper that provides move-only semantics.
 * 
 * 3. Write a function that efficiently merges multiple sorted ranges.
 * 
 * 4. Implement a cache-conscious data structure for matrix operations.
 * 
 * 5. Create a parallel algorithm for computing histogram of large dataset.
 * 
 * 6. Design a memory pool allocator for objects of specific size.
 * 
 * 7. Implement a container that minimizes iterator invalidation.
 * 
 * 8. Write performance benchmarks comparing different container operations.
 * 
 * 9. Create a RAII wrapper for C-style resources using move semantics.
 * 
 * 10. Implement a parallel sort algorithm using std::async.
 * 
 * ============================================================================
 * PERFORMANCE OPTIMIZATION GUIDELINES:
 * ============================================================================
 * 
 * 1. CONTAINER SELECTION:
 *    - vector: Random access, cache-friendly, fast iteration
 *    - list: Fast insertion/deletion anywhere, non-contiguous
 *    - deque: Fast front/back operations, less cache-friendly than vector
 *    - array: Fixed size, stack allocated, fastest for small collections
 * 
 * 2. ALGORITHM SELECTION:
 *    - Know time complexities: O(1), O(log n), O(n), O(n log n), O(n²)
 *    - Use appropriate search: linear O(n) vs binary O(log n)
 *    - Consider parallel algorithms for large datasets
 * 
 * 3. MEMORY EFFICIENCY:
 *    - Use emplace instead of insert/push when constructing objects
 *    - Prefer move semantics over copying for expensive objects
 *    - Consider custom allocators for specialized memory patterns
 *    - Reserve container capacity when size is known
 * 
 * 4. CACHE OPTIMIZATION:
 *    - Access memory sequentially when possible
 *    - Pack data structures to minimize padding
 *    - Use contiguous containers (vector, array) over linked structures
 *    - Consider cache line size in algorithm design
 * 
 * ============================================================================
 * MOVE SEMANTICS BEST PRACTICES:
 * ============================================================================
 * 
 * 1. WHEN TO IMPLEMENT:
 *    - Classes managing resources (memory, file handles, etc.)
 *    - Classes with expensive copy operations
 *    - Value types that need to be stored in containers
 * 
 * 2. IMPLEMENTATION GUIDELINES:
 *    - Mark move constructors and move assignment operators noexcept
 *    - Leave moved-from objects in valid but unspecified state
 *    - Use std::move when transferring ownership
 *    - Use std::forward in perfect forwarding scenarios
 * 
 * 3. COMMON PATTERNS:
 *    - Return by value (RVO/NRVO optimization)
 *    - Pass expensive parameters by value when moving
 *    - Use emplace operations instead of insert + temporary
 * 
 * ============================================================================
 * ALLOCATOR DESIGN PRINCIPLES:
 * ============================================================================
 * 
 * 1. REQUIREMENTS:
 *    - Must satisfy Allocator requirements
 *    - Should be CopyConstructible and CopyAssignable
 *    - Must provide value_type, allocate(), and deallocate()
 * 
 * 2. DESIGN CONSIDERATIONS:
 *    - Thread safety for multi-threaded applications
 *    - Exception safety in allocation/deallocation
 *    - Memory alignment requirements
 *    - Performance characteristics
 * 
 * 3. COMMON ALLOCATOR TYPES:
 *    - Pool allocators: Pre-allocated memory pools
 *    - Stack allocators: LIFO allocation pattern
 *    - Tracking allocators: Monitor memory usage
 *    - Custom alignment allocators: Specific alignment needs
 * 
 * ============================================================================
 * ADVANCED STL DEBUGGING TIPS:
 * ============================================================================
 * 
 * 1. ITERATOR DEBUGGING:
 *    - Enable debug mode in STL implementations
 *    - Check for iterator invalidation
 *    - Validate iterator ranges
 * 
 * 2. MEMORY DEBUGGING:
 *    - Use custom allocators to track leaks
 *    - Validate container state after operations
 *    - Check for use-after-move scenarios
 * 
 * 3. PERFORMANCE PROFILING:
 *    - Measure actual performance, not theoretical
 *    - Profile with realistic data sizes
 *    - Consider both time and space complexity
 *    - Test on target hardware architecture
 * 
 * ============================================================================
 */
