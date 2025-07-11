# Heaps & Priority Queues Module

## Overview
This module covers heap data structures and priority queues, which are essential for efficiently managing ordered data and implementing various algorithms.

## Learning Path

### 1. Heap Implementation (`heap_implementation.cpp`)
- **Core Concepts**: Complete binary tree, heap property, array representation
- **Basic Operations**: Insert, extract min/max, peek, size/empty checks
- **Advanced Operations**: Build heap, remove arbitrary element, update element, merge heaps
- **Algorithms**: Heap sort, finding k largest/smallest elements
- **Specializations**: Min heap, max heap implementations

### 2. Priority Queue Applications (`priority_queue_applications.cpp`)
- **STL Priority Queue**: Understanding and using std::priority_queue
- **Custom Priority Queues**: Building application-specific priority systems
- **Real-world Applications**: Task scheduling, Dijkstra's algorithm, event simulation
- **Advanced Topics**: K-way merge, median maintenance, custom comparators

## Problem Sets

### Heap Problems (`problems/heap_problems.cpp`)
A comprehensive collection of 8+ heap and priority queue problems including:

**Basic Heap Operations:**
- Kth largest element in array
- Top k frequent elements
- Ugly number generation

**Sliding Window Problems:**
- Sliding window maximum
- Running median maintenance

**Merge Problems:**
- Merge k sorted lists
- Merge k sorted arrays
- Interval merging

**Scheduling Problems:**
- Task scheduler with cooling time
- Meeting room scheduling
- Process scheduling

**Stream Processing:**
- Find median from data stream
- Running statistics maintenance

## Key Concepts

### Heap Properties:
- **Complete Binary Tree**: All levels filled except possibly the last
- **Heap Property**: Parent-child relationship (min/max heap)
- **Array Representation**: Efficient storage using indices
- **Height**: Always O(log n) for balanced structure

### Time Complexities:
- **Insert**: O(log n)
- **Extract Min/Max**: O(log n)
- **Peek**: O(1)
- **Build Heap**: O(n) using Floyd's algorithm
- **Heap Sort**: O(n log n)

### Space Complexity:
- **Storage**: O(n) for n elements
- **Operations**: O(1) additional space for most operations

## Implementation Techniques

### Array-Based Heap:
```cpp
// Index relationships in array representation
parent(i) = (i - 1) / 2
leftChild(i) = 2 * i + 1
rightChild(i) = 2 * i + 2
```

### Heapify Operations:
- **Heapify Up**: Used after insertion
- **Heapify Down**: Used after deletion
- **Build Heap**: Bottom-up heapification

### Priority Queue Patterns:
- **Min Heap**: For finding minimum elements
- **Max Heap**: For finding maximum elements
- **Custom Comparators**: For complex ordering rules

## Common Problem Patterns

### 1. Top-K Problems:
- Use min heap of size k for k largest elements
- Use max heap of size k for k smallest elements
- Time: O(n log k), Space: O(k)

### 2. Sliding Window Extremes:
- Use deque for O(n) solution
- Use heap with lazy deletion for O(n log k) solution
- Remove elements outside window efficiently

### 3. Stream Processing:
- Two heaps for median (max heap + min heap)
- Balanced sizes for O(1) median access
- O(log n) insertion time

### 4. Merge Problems:
- Priority queue to merge k sorted sequences
- Always extract minimum and add next element
- Time: O(N log k) where N is total elements

### 5. Scheduling Problems:
- Model tasks with priorities and deadlines
- Use heap to always process highest priority task
- Handle cooling periods and constraints

## Study Tips

### For Heaps:
1. **Understand Array Representation**: Master index calculations
2. **Practice Heapify**: Both up and down operations
3. **Build vs Insert**: Know when to use O(n) build vs O(n log n) insertions
4. **Heap Variants**: Min heap, max heap, and custom comparators

### For Priority Queues:
1. **STL Mastery**: Learn std::priority_queue thoroughly
2. **Custom Comparators**: Practice defining custom ordering
3. **Problem Recognition**: Identify when priority queue is the right tool
4. **Complexity Analysis**: Understand when heap operations are optimal

## Real-World Applications

### Operating Systems:
- **Process Scheduling**: Priority-based task management
- **Memory Management**: Page replacement algorithms
- **Event Handling**: Priority event processing

### Graph Algorithms:
- **Dijkstra's Algorithm**: Shortest path finding
- **Prim's Algorithm**: Minimum spanning tree
- **A* Search**: Heuristic-based pathfinding

### Data Processing:
- **Stream Processing**: Real-time data analysis
- **Log Processing**: Priority-based log handling
- **Load Balancing**: Task distribution based on priorities

### Game Development:
- **Event Systems**: Time-based event scheduling
- **AI Pathfinding**: Priority-based exploration
- **Resource Management**: Priority allocation systems

## Advanced Topics

### Heap Variants:
- **Binary Heap**: Standard implementation
- **d-ary Heap**: Generalization with d children
- **Fibonacci Heap**: Better amortized performance
- **Binomial Heap**: Mergeable heaps

### Optimization Techniques:
- **Lazy Deletion**: Avoid immediate removal
- **Bulk Operations**: Batch insertions and deletions
- **Memory Layout**: Cache-friendly implementations

## Practice Strategy

### Daily Practice:
- Implement heap operations from scratch
- Solve 1-2 heap problems with different approaches
- Practice recognizing heap problem patterns

### Weekly Goals:
- Week 1: Master basic heap operations and implementation
- Week 2: Focus on priority queue applications
- Week 3: Advanced problems (sliding window, merge problems)
- Week 4: Real-world applications and optimizations

### Assessment Questions:
- Can you implement a heap from scratch?
- Can you identify when to use min vs max heap?
- Can you solve top-k problems efficiently?
- Can you handle stream processing with heaps?
- Can you implement priority-based algorithms?

## Next Steps
After mastering heaps and priority queues, proceed to:
1. **Hash Tables** - For fast key-value operations
2. **Advanced Tree Structures** - B-trees, segment trees
3. **Graph Algorithms** - Using heaps in pathfinding
4. **Dynamic Programming** - Optimization problems

## Additional Resources
- **Visualizations**: Use online heap visualizers
- **Practice**: LeetCode heap problems, priority queue challenges
- **Books**: "Introduction to Algorithms" for theoretical depth
- **Implementation**: Study STL source code for optimizations
