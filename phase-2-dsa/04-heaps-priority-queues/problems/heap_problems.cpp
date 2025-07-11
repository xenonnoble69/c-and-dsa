/*
 * ============================================================================
 * HEAP & PRIORITY QUEUE PROBLEMS - COMPREHENSIVE PROBLEM SET
 * ============================================================================
 * 
 * A comprehensive collection of problems covering:
 * - Heap operations and maintenance
 * - Priority queue applications
 * - Top-k problems
 * - Merge problems
 * - Median and statistics problems
 * - Scheduling and optimization problems
 * 
 * Each problem includes:
 * - Problem statement and examples
 * - Multiple solution approaches
 * - Time and space complexity analysis
 * - Edge cases and optimizations
 * 
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <string>
#include <functional>
#include <climits>

using namespace std;

/*
 * ========================================================================
 * PROBLEM 1: KTH LARGEST ELEMENT IN ARRAY
 * ========================================================================
 * 
 * Find the kth largest element in an unsorted array.
 * Note: It is the kth largest element in sorted order, not the kth distinct element.
 * 
 * Example:
 * Input: [3,2,1,5,6,4] and k = 2
 * Output: 5
 */

class Solution_KthLargest {
public:
    // Approach 1: Min Heap (Most efficient for small k)
    int findKthLargest_MinHeap(vector<int>& nums, int k) {
        /*
         * Use min heap of size k
         * Time: O(n log k), Space: O(k)
         */
        priority_queue<int, vector<int>, greater<int>> minHeap;
        
        for (int num : nums) {
            minHeap.push(num);
            if (minHeap.size() > k) {
                minHeap.pop();
            }
        }
        
        return minHeap.top();
    }
    
    // Approach 2: Max Heap (Build entire heap)
    int findKthLargest_MaxHeap(vector<int>& nums, int k) {
        /*
         * Build max heap and extract k times
         * Time: O(n + k log n), Space: O(1)
         */
        make_heap(nums.begin(), nums.end());
        
        for (int i = 0; i < k - 1; ++i) {
            pop_heap(nums.begin(), nums.end());
            nums.pop_back();
        }
        
        return nums[0];
    }
    
    // Approach 3: Quickselect (Most efficient on average)
    int findKthLargest_QuickSelect(vector<int>& nums, int k) {
        /*
         * Quickselect algorithm
         * Time: O(n) average, O(n²) worst case, Space: O(1)
         */
        int target = nums.size() - k;  // Convert to 0-indexed from end
        return quickSelect(nums, 0, nums.size() - 1, target);
    }
    
    // Approach 4: STL nth_element
    int findKthLargest_STL(vector<int>& nums, int k) {
        /*
         * Using STL nth_element function
         * Time: O(n) average, Space: O(1)
         */
        int target = nums.size() - k;
        nth_element(nums.begin(), nums.begin() + target, nums.end());
        return nums[target];
    }

private:
    int quickSelect(vector<int>& nums, int left, int right, int target) {
        int pivot = partition(nums, left, right);
        
        if (pivot == target) {
            return nums[pivot];
        } else if (pivot < target) {
            return quickSelect(nums, pivot + 1, right, target);
        } else {
            return quickSelect(nums, left, pivot - 1, target);
        }
    }
    
    int partition(vector<int>& nums, int left, int right) {
        int pivot = nums[right];
        int i = left;
        
        for (int j = left; j < right; ++j) {
            if (nums[j] <= pivot) {
                swap(nums[i], nums[j]);
                i++;
            }
        }
        
        swap(nums[i], nums[right]);
        return i;
    }
};

/*
 * ========================================================================
 * PROBLEM 2: MERGE K SORTED LISTS
 * ========================================================================
 * 
 * Merge k sorted linked lists and return it as one sorted list.
 * 
 * Example:
 * Input: [[1,4,5],[1,3,4],[2,6]]
 * Output: [1,1,2,3,4,4,5,6]
 */

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution_MergeKSortedLists {
public:
    // Approach 1: Priority Queue
    ListNode* mergeKLists_PriorityQueue(vector<ListNode*>& lists) {
        /*
         * Use min heap to always get the smallest element
         * Time: O(N log k), Space: O(k)
         * N = total number of nodes, k = number of lists
         */
        struct Compare {
            bool operator()(ListNode* a, ListNode* b) {
                return a->val > b->val;  // Min heap
            }
        };
        
        priority_queue<ListNode*, vector<ListNode*>, Compare> pq;
        
        // Add first node of each list
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
            
            if (node->next) {
                pq.push(node->next);
            }
        }
        
        return dummy.next;
    }
    
    // Approach 2: Divide and Conquer
    ListNode* mergeKLists_DivideConquer(vector<ListNode*>& lists) {
        /*
         * Merge lists pairwise until one list remains
         * Time: O(N log k), Space: O(log k) for recursion
         */
        if (lists.empty()) return nullptr;
        
        while (lists.size() > 1) {
            vector<ListNode*> mergedLists;
            
            for (int i = 0; i < lists.size(); i += 2) {
                ListNode* l1 = lists[i];
                ListNode* l2 = (i + 1 < lists.size()) ? lists[i + 1] : nullptr;
                mergedLists.push_back(mergeTwoLists(l1, l2));
            }
            
            lists = mergedLists;
        }
        
        return lists[0];
    }
    
    // Approach 3: Sequential merge
    ListNode* mergeKLists_Sequential(vector<ListNode*>& lists) {
        /*
         * Merge lists one by one
         * Time: O(N * k), Space: O(1)
         */
        ListNode* result = nullptr;
        
        for (ListNode* list : lists) {
            result = mergeTwoLists(result, list);
        }
        
        return result;
    }

private:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
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
};

/*
 * ========================================================================
 * PROBLEM 3: TOP K FREQUENT ELEMENTS
 * ========================================================================
 * 
 * Given a non-empty array of integers, return the k most frequent elements.
 * 
 * Example:
 * Input: nums = [1,1,1,2,2,3], k = 2
 * Output: [1,2]
 */

class Solution_TopKFrequent {
public:
    // Approach 1: Min Heap
    vector<int> topKFrequent_MinHeap(vector<int>& nums, int k) {
        /*
         * Count frequencies and use min heap
         * Time: O(n log k), Space: O(n)
         */
        unordered_map<int, int> freq;
        for (int num : nums) {
            freq[num]++;
        }
        
        // Min heap based on frequency
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        
        for (auto& p : freq) {
            pq.push({p.second, p.first});
            if (pq.size() > k) {
                pq.pop();
            }
        }
        
        vector<int> result;
        while (!pq.empty()) {
            result.push_back(pq.top().second);
            pq.pop();
        }
        
        return result;
    }
    
    // Approach 2: Max Heap
    vector<int> topKFrequent_MaxHeap(vector<int>& nums, int k) {
        /*
         * Count frequencies and use max heap
         * Time: O(n log n), Space: O(n)
         */
        unordered_map<int, int> freq;
        for (int num : nums) {
            freq[num]++;
        }
        
        // Max heap based on frequency
        priority_queue<pair<int, int>> pq;
        for (auto& p : freq) {
            pq.push({p.second, p.first});
        }
        
        vector<int> result;
        for (int i = 0; i < k; ++i) {
            result.push_back(pq.top().second);
            pq.pop();
        }
        
        return result;
    }
    
    // Approach 3: Bucket Sort
    vector<int> topKFrequent_BucketSort(vector<int>& nums, int k) {
        /*
         * Use bucket sort for O(n) solution
         * Time: O(n), Space: O(n)
         */
        unordered_map<int, int> freq;
        for (int num : nums) {
            freq[num]++;
        }
        
        vector<vector<int>> buckets(nums.size() + 1);
        for (auto& p : freq) {
            buckets[p.second].push_back(p.first);
        }
        
        vector<int> result;
        for (int i = buckets.size() - 1; i >= 0 && result.size() < k; --i) {
            for (int num : buckets[i]) {
                result.push_back(num);
                if (result.size() == k) break;
            }
        }
        
        return result;
    }
    
    // Approach 4: Quickselect
    vector<int> topKFrequent_QuickSelect(vector<int>& nums, int k) {
        /*
         * Use quickselect on frequencies
         * Time: O(n) average, Space: O(n)
         */
        unordered_map<int, int> freq;
        for (int num : nums) {
            freq[num]++;
        }
        
        vector<pair<int, int>> freqPairs;
        for (auto& p : freq) {
            freqPairs.push_back({p.second, p.first});
        }
        
        quickSelect(freqPairs, 0, freqPairs.size() - 1, freqPairs.size() - k);
        
        vector<int> result;
        for (int i = freqPairs.size() - k; i < freqPairs.size(); ++i) {
            result.push_back(freqPairs[i].second);
        }
        
        return result;
    }

private:
    void quickSelect(vector<pair<int, int>>& arr, int left, int right, int target) {
        if (left >= right) return;
        
        int pivot = partition(arr, left, right);
        
        if (pivot == target) {
            return;
        } else if (pivot < target) {
            quickSelect(arr, pivot + 1, right, target);
        } else {
            quickSelect(arr, left, pivot - 1, target);
        }
    }
    
    int partition(vector<pair<int, int>>& arr, int left, int right) {
        int pivot = arr[right].first;
        int i = left;
        
        for (int j = left; j < right; ++j) {
            if (arr[j].first <= pivot) {
                swap(arr[i], arr[j]);
                i++;
            }
        }
        
        swap(arr[i], arr[right]);
        return i;
    }
};

/*
 * ========================================================================
 * PROBLEM 4: SLIDING WINDOW MAXIMUM
 * ========================================================================
 * 
 * Given an array and a sliding window of size k, find the maximum element
 * in each window as it slides from left to right.
 * 
 * Example:
 * Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
 * Output: [3,3,5,5,6,7]
 */

class Solution_SlidingWindowMaximum {
public:
    // Approach 1: Brute Force
    vector<int> maxSlidingWindow_BruteForce(vector<int>& nums, int k) {
        /*
         * For each window, find maximum element
         * Time: O(n * k), Space: O(1)
         */
        vector<int> result;
        
        for (int i = 0; i <= nums.size() - k; ++i) {
            int maxVal = nums[i];
            for (int j = i; j < i + k; ++j) {
                maxVal = max(maxVal, nums[j]);
            }
            result.push_back(maxVal);
        }
        
        return result;
    }
    
    // Approach 2: Deque (Most efficient)
    vector<int> maxSlidingWindow_Deque(vector<int>& nums, int k) {
        /*
         * Use deque to maintain potential maximums
         * Time: O(n), Space: O(k)
         */
        deque<int> dq;  // Store indices
        vector<int> result;
        
        for (int i = 0; i < nums.size(); ++i) {
            // Remove indices outside current window
            while (!dq.empty() && dq.front() < i - k + 1) {
                dq.pop_front();
            }
            
            // Remove indices with smaller values
            while (!dq.empty() && nums[dq.back()] <= nums[i]) {
                dq.pop_back();
            }
            
            dq.push_back(i);
            
            // Add result for current window
            if (i >= k - 1) {
                result.push_back(nums[dq.front()]);
            }
        }
        
        return result;
    }
    
    // Approach 3: Max Heap (Less efficient due to lazy deletion)
    vector<int> maxSlidingWindow_MaxHeap(vector<int>& nums, int k) {
        /*
         * Use max heap with lazy deletion
         * Time: O(n log k), Space: O(k)
         */
        priority_queue<pair<int, int>> pq;  // (value, index)
        vector<int> result;
        
        for (int i = 0; i < nums.size(); ++i) {
            pq.push({nums[i], i});
            
            // Remove elements outside current window
            while (!pq.empty() && pq.top().second < i - k + 1) {
                pq.pop();
            }
            
            if (i >= k - 1) {
                result.push_back(pq.top().first);
            }
        }
        
        return result;
    }
    
    // Approach 4: Segment Tree (Overkill but educational)
    vector<int> maxSlidingWindow_SegmentTree(vector<int>& nums, int k) {
        /*
         * Build segment tree for range maximum queries
         * Time: O(n log n), Space: O(n)
         */
        int n = nums.size();
        vector<int> tree(4 * n);
        
        buildSegmentTree(nums, tree, 0, 0, n - 1);
        
        vector<int> result;
        for (int i = 0; i <= n - k; ++i) {
            result.push_back(querySegmentTree(tree, 0, 0, n - 1, i, i + k - 1));
        }
        
        return result;
    }

private:
    void buildSegmentTree(vector<int>& nums, vector<int>& tree, int node, int start, int end) {
        if (start == end) {
            tree[node] = nums[start];
        } else {
            int mid = (start + end) / 2;
            buildSegmentTree(nums, tree, 2 * node + 1, start, mid);
            buildSegmentTree(nums, tree, 2 * node + 2, mid + 1, end);
            tree[node] = max(tree[2 * node + 1], tree[2 * node + 2]);
        }
    }
    
    int querySegmentTree(vector<int>& tree, int node, int start, int end, int l, int r) {
        if (r < start || end < l) {
            return INT_MIN;
        }
        if (l <= start && end <= r) {
            return tree[node];
        }
        int mid = (start + end) / 2;
        int left = querySegmentTree(tree, 2 * node + 1, start, mid, l, r);
        int right = querySegmentTree(tree, 2 * node + 2, mid + 1, end, l, r);
        return max(left, right);
    }
};

/*
 * ========================================================================
 * PROBLEM 5: FIND MEDIAN FROM DATA STREAM
 * ========================================================================
 * 
 * Design a data structure that supports:
 * - addNum(int num): Add integer to data structure
 * - findMedian(): Return median of all elements
 * 
 * Example:
 * addNum(1), addNum(2), findMedian() -> 1.5
 * addNum(3), findMedian() -> 2
 */

class MedianFinder {
private:
    priority_queue<int> maxHeap;  // Left half (smaller elements)
    priority_queue<int, vector<int>, greater<int>> minHeap;  // Right half (larger elements)
    
public:
    MedianFinder() {}
    
    void addNum(int num) {
        /*
         * Add number while maintaining balanced heaps
         * Time: O(log n), Space: O(1)
         */
        // Add to appropriate heap
        if (maxHeap.empty() || num <= maxHeap.top()) {
            maxHeap.push(num);
        } else {
            minHeap.push(num);
        }
        
        // Balance heaps (size difference at most 1)
        if (maxHeap.size() > minHeap.size() + 1) {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        } else if (minHeap.size() > maxHeap.size() + 1) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }
    
    double findMedian() {
        /*
         * Return median of all elements
         * Time: O(1), Space: O(1)
         */
        if (maxHeap.size() == minHeap.size()) {
            return (maxHeap.top() + minHeap.top()) / 2.0;
        } else if (maxHeap.size() > minHeap.size()) {
            return maxHeap.top();
        } else {
            return minHeap.top();
        }
    }
};

/*
 * ========================================================================
 * PROBLEM 6: UGLY NUMBER II
 * ========================================================================
 * 
 * Find the nth ugly number. Ugly numbers are positive numbers whose prime
 * factors only include 2, 3, and 5.
 * 
 * Example:
 * Input: n = 10
 * Output: 12
 * Explanation: 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 are first 10 ugly numbers.
 */

class Solution_UglyNumber {
public:
    // Approach 1: Min Heap
    int nthUglyNumber_MinHeap(int n) {
        /*
         * Use min heap to generate ugly numbers in order
         * Time: O(n log n), Space: O(n)
         */
        priority_queue<long, vector<long>, greater<long>> pq;
        unordered_set<long> seen;
        
        pq.push(1);
        seen.insert(1);
        
        vector<int> factors = {2, 3, 5};
        
        for (int i = 0; i < n; ++i) {
            long current = pq.top();
            pq.pop();
            
            if (i == n - 1) {
                return current;
            }
            
            for (int factor : factors) {
                long next = current * factor;
                if (seen.find(next) == seen.end()) {
                    seen.insert(next);
                    pq.push(next);
                }
            }
        }
        
        return -1;
    }
    
    // Approach 2: Dynamic Programming (More efficient)
    int nthUglyNumber_DP(int n) {
        /*
         * Use three pointers to generate ugly numbers
         * Time: O(n), Space: O(n)
         */
        vector<int> ugly(n);
        ugly[0] = 1;
        
        int i2 = 0, i3 = 0, i5 = 0;
        
        for (int i = 1; i < n; ++i) {
            int next2 = ugly[i2] * 2;
            int next3 = ugly[i3] * 3;
            int next5 = ugly[i5] * 5;
            
            ugly[i] = min({next2, next3, next5});
            
            if (ugly[i] == next2) i2++;
            if (ugly[i] == next3) i3++;
            if (ugly[i] == next5) i5++;
        }
        
        return ugly[n - 1];
    }
};

/*
 * ========================================================================
 * PROBLEM 7: MERGE INTERVALS
 * ========================================================================
 * 
 * Given a collection of intervals, merge all overlapping intervals.
 * 
 * Example:
 * Input: [[1,3],[2,6],[8,10],[15,18]]
 * Output: [[1,6],[8,10],[15,18]]
 */

class Solution_MergeIntervals {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        /*
         * Sort intervals by start time and merge overlapping ones
         * Time: O(n log n), Space: O(1)
         */
        if (intervals.empty()) return {};
        
        sort(intervals.begin(), intervals.end());
        
        vector<vector<int>> result;
        result.push_back(intervals[0]);
        
        for (int i = 1; i < intervals.size(); ++i) {
            if (intervals[i][0] <= result.back()[1]) {
                // Overlapping intervals, merge them
                result.back()[1] = max(result.back()[1], intervals[i][1]);
            } else {
                // Non-overlapping interval, add to result
                result.push_back(intervals[i]);
            }
        }
        
        return result;
    }
    
    // Using priority queue for event-based approach
    vector<vector<int>> merge_EventBased(vector<vector<int>>& intervals) {
        /*
         * Use events (start/end) with priority queue
         * Time: O(n log n), Space: O(n)
         */
        if (intervals.empty()) return {};
        
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        
        for (auto& interval : intervals) {
            pq.push({interval[0], 1});  // Start event
            pq.push({interval[1], -1}); // End event
        }
        
        vector<vector<int>> result;
        int count = 0;
        int start = -1;
        
        while (!pq.empty()) {
            auto [time, event] = pq.top();
            pq.pop();
            
            if (count == 0 && event == 1) {
                start = time;
            }
            
            count += event;
            
            if (count == 0 && event == -1) {
                result.push_back({start, time});
            }
        }
        
        return result;
    }
};

/*
 * ========================================================================
 * PROBLEM 8: TASK SCHEDULER
 * ========================================================================
 * 
 * Given tasks and a cooling time n, find the minimum time to complete all tasks.
 * Same tasks must be separated by at least n time units.
 * 
 * Example:
 * Input: tasks = ["A","A","A","B","B","B"], n = 2
 * Output: 8
 * Explanation: A -> B -> idle -> A -> B -> idle -> A -> B
 */

class Solution_TaskScheduler {
public:
    int leastInterval(vector<char>& tasks, int n) {
        /*
         * Use frequency count and max heap
         * Time: O(n log 26) = O(n), Space: O(26) = O(1)
         */
        unordered_map<char, int> freq;
        for (char task : tasks) {
            freq[task]++;
        }
        
        priority_queue<int> pq;
        for (auto& p : freq) {
            pq.push(p.second);
        }
        
        int time = 0;
        
        while (!pq.empty()) {
            vector<int> temp;
            int cycle = n + 1;
            
            // Process tasks in current cycle
            while (cycle > 0 && !pq.empty()) {
                int count = pq.top();
                pq.pop();
                
                if (count > 1) {
                    temp.push_back(count - 1);
                }
                
                cycle--;
                time++;
            }
            
            // Add remaining tasks back to heap
            for (int count : temp) {
                pq.push(count);
            }
            
            // Add idle time if needed
            if (!pq.empty()) {
                time += cycle;
            }
        }
        
        return time;
    }
    
    // Mathematical approach (more efficient)
    int leastInterval_Math(vector<char>& tasks, int n) {
        /*
         * Calculate minimum time using frequency analysis
         * Time: O(n), Space: O(1)
         */
        unordered_map<char, int> freq;
        for (char task : tasks) {
            freq[task]++;
        }
        
        int maxFreq = 0;
        for (auto& p : freq) {
            maxFreq = max(maxFreq, p.second);
        }
        
        int maxCount = 0;
        for (auto& p : freq) {
            if (p.second == maxFreq) {
                maxCount++;
            }
        }
        
        // Calculate minimum time
        int partCount = maxFreq - 1;
        int partLength = n - (maxCount - 1);
        int emptySlots = partCount * partLength;
        int availableTasks = tasks.size() - maxFreq * maxCount;
        int idles = max(0, emptySlots - availableTasks);
        
        return tasks.size() + idles;
    }
};

/*
 * ========================================================================
 * TESTING AND DEMONSTRATION
 * ========================================================================
 */

void testHeapProblems() {
    cout << "=== TESTING HEAP PROBLEMS ===" << endl;
    
    // Test Kth Largest Element
    {
        cout << "\n--- Kth Largest Element ---" << endl;
        Solution_KthLargest sol;
        vector<int> nums = {3,2,1,5,6,4};
        int k = 2;
        
        cout << "Array: ";
        for (int x : nums) cout << x << " ";
        cout << "\nKth largest (k=" << k << "): " << sol.findKthLargest_MinHeap(nums, k) << endl;
    }
    
    // Test Top K Frequent Elements
    {
        cout << "\n--- Top K Frequent Elements ---" << endl;
        Solution_TopKFrequent sol;
        vector<int> nums = {1,1,1,2,2,3};
        int k = 2;
        
        cout << "Array: ";
        for (int x : nums) cout << x << " ";
        cout << "\nTop " << k << " frequent: ";
        
        auto result = sol.topKFrequent_MinHeap(nums, k);
        for (int x : result) cout << x << " ";
        cout << endl;
    }
    
    // Test Sliding Window Maximum
    {
        cout << "\n--- Sliding Window Maximum ---" << endl;
        Solution_SlidingWindowMaximum sol;
        vector<int> nums = {1,3,-1,-3,5,3,6,7};
        int k = 3;
        
        cout << "Array: ";
        for (int x : nums) cout << x << " ";
        cout << "\nWindow size: " << k << endl;
        cout << "Maximum in each window: ";
        
        auto result = sol.maxSlidingWindow_Deque(nums, k);
        for (int x : result) cout << x << " ";
        cout << endl;
    }
    
    // Test Median Finder
    {
        cout << "\n--- Median Finder ---" << endl;
        MedianFinder mf;
        vector<int> nums = {5, 15, 1, 3, 8, 7, 9, 2, 6};
        
        for (int num : nums) {
            mf.addNum(num);
            cout << "Added " << num << ", median: " << mf.findMedian() << endl;
        }
    }
    
    // Test Ugly Number II
    {
        cout << "\n--- Ugly Number II ---" << endl;
        Solution_UglyNumber sol;
        int n = 10;
        
        cout << n << "th ugly number: " << sol.nthUglyNumber_DP(n) << endl;
    }
    
    // Test Task Scheduler
    {
        cout << "\n--- Task Scheduler ---" << endl;
        Solution_TaskScheduler sol;
        vector<char> tasks = {'A','A','A','B','B','B'};
        int n = 2;
        
        cout << "Tasks: ";
        for (char t : tasks) cout << t << " ";
        cout << "\nCooling time: " << n << endl;
        cout << "Minimum time: " << sol.leastInterval(tasks, n) << endl;
    }
}

/*
 * ========================================================================
 * MAIN FUNCTION
 * ========================================================================
 */

int main() {
    cout << "=== HEAP & PRIORITY QUEUE PROBLEMS COMPREHENSIVE GUIDE ===" << endl;
    
    testHeapProblems();
    
    cout << "\n=== All Heap Problems Tested! ===" << endl;
    
    return 0;
}

/*
 * ============================================================================
 * HEAP PROBLEMS COMPLEXITY ANALYSIS:
 * ============================================================================
 * 
 * 1. KTH LARGEST ELEMENT:
 *    - Min Heap: O(n log k) time, O(k) space
 *    - Max Heap: O(n + k log n) time, O(1) space
 *    - QuickSelect: O(n) average time, O(1) space
 * 
 * 2. MERGE K SORTED LISTS:
 *    - Priority Queue: O(N log k) time, O(k) space
 *    - Divide & Conquer: O(N log k) time, O(log k) space
 *    - Sequential: O(N * k) time, O(1) space
 * 
 * 3. TOP K FREQUENT ELEMENTS:
 *    - Min Heap: O(n log k) time, O(n) space
 *    - Bucket Sort: O(n) time, O(n) space
 *    - QuickSelect: O(n) average time, O(n) space
 * 
 * 4. SLIDING WINDOW MAXIMUM:
 *    - Deque: O(n) time, O(k) space
 *    - Max Heap: O(n log k) time, O(k) space
 *    - Brute Force: O(n * k) time, O(1) space
 * 
 * 5. MEDIAN FROM DATA STREAM:
 *    - Two Heaps: O(log n) insert, O(1) median, O(n) space
 * 
 * 6. UGLY NUMBER II:
 *    - Min Heap: O(n log n) time, O(n) space
 *    - DP: O(n) time, O(n) space
 * 
 * 7. TASK SCHEDULER:
 *    - Max Heap: O(n) time, O(1) space
 *    - Mathematical: O(n) time, O(1) space
 * 
 * PROBLEM PATTERNS:
 * - Finding extremes: Use min/max heap
 * - Streaming data: Use balanced heaps
 * - K problems: Use heap of size k
 * - Sliding window: Use deque or heap with cleanup
 * - Merge problems: Use priority queue
 * - Frequency problems: Count + heap
 * 
 * ============================================================================
 */
