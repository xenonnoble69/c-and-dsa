# Complete Solutions Guide

## Table of Contents
1. [Phase 1 Solutions - C++ Fundamentals](#phase-1-solutions)
2. [Phase 2 Solutions - Data Structures & Algorithms](#phase-2-solutions)
3. [Phase 3 Solutions - Dynamic Programming](#phase-3-solutions)
4. [Phase 4 Solutions - Competitive Programming & Interviews](#phase-4-solutions)
5. [Common Problem Patterns](#common-problem-patterns)
6. [Optimization Techniques](#optimization-techniques)

## Phase 1 Solutions

### Modern C++ Fundamentals

#### Problem: Implement a Smart Pointer Class
```cpp
template<typename T>
class SmartPtr {
private:
    T* ptr;
    int* ref_count;
    
public:
    explicit SmartPtr(T* p = nullptr) : ptr(p) {
        ref_count = new int(1);
    }
    
    SmartPtr(const SmartPtr& other) : ptr(other.ptr), ref_count(other.ref_count) {
        if (ref_count) (*ref_count)++;
    }
    
    SmartPtr& operator=(const SmartPtr& other) {
        if (this != &other) {
            reset();
            ptr = other.ptr;
            ref_count = other.ref_count;
            if (ref_count) (*ref_count)++;
        }
        return *this;
    }
    
    ~SmartPtr() { reset(); }
    
    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }
    T* get() const { return ptr; }
    
    void reset() {
        if (ref_count && --(*ref_count) == 0) {
            delete ptr;
            delete ref_count;
        }
        ptr = nullptr;
        ref_count = nullptr;
    }
    
    int use_count() const {
        return ref_count ? *ref_count : 0;
    }
};
```

#### Problem: Template Function for Finding Maximum
```cpp
template<typename T>
T findMax(const std::vector<T>& vec) {
    if (vec.empty()) {
        throw std::invalid_argument("Vector is empty");
    }
    
    T maxVal = vec[0];
    for (size_t i = 1; i < vec.size(); ++i) {
        if (vec[i] > maxVal) {
            maxVal = vec[i];
        }
    }
    return maxVal;
}

// Specialized version for string comparison
template<>
std::string findMax<std::string>(const std::vector<std::string>& vec) {
    if (vec.empty()) {
        throw std::invalid_argument("Vector is empty");
    }
    
    std::string maxVal = vec[0];
    for (size_t i = 1; i < vec.size(); ++i) {
        if (vec[i].length() > maxVal.length()) {
            maxVal = vec[i];
        }
    }
    return maxVal;
}
```

### Object-Oriented Programming Solutions

#### Problem: Design a Vehicle Hierarchy
```cpp
class Vehicle {
protected:
    std::string make, model;
    int year;
    
public:
    Vehicle(const std::string& make, const std::string& model, int year)
        : make(make), model(model), year(year) {}
    
    virtual ~Vehicle() = default;
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual double fuelEfficiency() const = 0;
    
    // Non-virtual interface
    void displayInfo() const {
        std::cout << year << " " << make << " " << model << std::endl;
    }
};

class Car : public Vehicle {
private:
    int doors;
    
public:
    Car(const std::string& make, const std::string& model, int year, int doors)
        : Vehicle(make, model, year), doors(doors) {}
    
    void start() override {
        std::cout << "Car engine started" << std::endl;
    }
    
    void stop() override {
        std::cout << "Car engine stopped" << std::endl;
    }
    
    double fuelEfficiency() const override {
        return 25.0; // mpg
    }
};

class Motorcycle : public Vehicle {
private:
    bool hasSidecar;
    
public:
    Motorcycle(const std::string& make, const std::string& model, int year, bool sidecar)
        : Vehicle(make, model, year), hasSidecar(sidecar) {}
    
    void start() override {
        std::cout << "Motorcycle engine started" << std::endl;
    }
    
    void stop() override {
        std::cout << "Motorcycle engine stopped" << std::endl;
    }
    
    double fuelEfficiency() const override {
        return 45.0; // mpg
    }
};
```

## Phase 2 Solutions

### Array and String Problems

#### Problem: Rotate Array by K Positions
```cpp
void rotateArray(std::vector<int>& nums, int k) {
    int n = nums.size();
    k = k % n; // Handle cases where k > n
    
    // Method 1: Using extra space
    std::vector<int> temp(nums);
    for (int i = 0; i < n; i++) {
        nums[(i + k) % n] = temp[i];
    }
}

void rotateArrayInPlace(std::vector<int>& nums, int k) {
    int n = nums.size();
    k = k % n;
    
    // Method 2: Reverse approach (O(1) space)
    std::reverse(nums.begin(), nums.end());
    std::reverse(nums.begin(), nums.begin() + k);
    std::reverse(nums.begin() + k, nums.end());
}
```

#### Problem: Find All Anagrams in String
```cpp
std::vector<int> findAnagrams(std::string s, std::string p) {
    std::vector<int> result;
    if (s.length() < p.length()) return result;
    
    std::vector<int> pCount(26, 0), sCount(26, 0);
    
    // Count characters in pattern
    for (char c : p) {
        pCount[c - 'a']++;
    }
    
    int windowSize = p.length();
    
    // Initialize first window
    for (int i = 0; i < windowSize; i++) {
        sCount[s[i] - 'a']++;
    }
    
    if (pCount == sCount) {
        result.push_back(0);
    }
    
    // Slide the window
    for (int i = windowSize; i < s.length(); i++) {
        // Add new character
        sCount[s[i] - 'a']++;
        // Remove old character
        sCount[s[i - windowSize] - 'a']--;
        
        if (pCount == sCount) {
            result.push_back(i - windowSize + 1);
        }
    }
    
    return result;
}
```

### Linked List Solutions

#### Problem: Merge K Sorted Lists
```cpp
ListNode* mergeKLists(std::vector<ListNode*>& lists) {
    if (lists.empty()) return nullptr;
    
    // Using priority queue (min-heap)
    auto comp = [](ListNode* a, ListNode* b) {
        return a->val > b->val;
    };
    
    std::priority_queue<ListNode*, std::vector<ListNode*>, decltype(comp)> pq(comp);
    
    // Add first node of each list
    for (ListNode* list : lists) {
        if (list) pq.push(list);
    }
    
    ListNode dummy(0);
    ListNode* current = &dummy;
    
    while (!pq.empty()) {
        ListNode* smallest = pq.top();
        pq.pop();
        
        current->next = smallest;
        current = current->next;
        
        if (smallest->next) {
            pq.push(smallest->next);
        }
    }
    
    return dummy.next;
}

// Alternative: Divide and conquer approach
ListNode* mergeKListsDivideConquer(std::vector<ListNode*>& lists) {
    if (lists.empty()) return nullptr;
    
    while (lists.size() > 1) {
        std::vector<ListNode*> mergedLists;
        
        for (int i = 0; i < lists.size(); i += 2) {
            ListNode* l1 = lists[i];
            ListNode* l2 = (i + 1 < lists.size()) ? lists[i + 1] : nullptr;
            mergedLists.push_back(mergeTwoLists(l1, l2));
        }
        
        lists = mergedLists;
    }
    
    return lists[0];
}
```

### Tree and Graph Solutions

#### Problem: Serialize and Deserialize Binary Tree
```cpp
class Codec {
public:
    std::string serialize(TreeNode* root) {
        std::ostringstream out;
        serializeHelper(root, out);
        return out.str();
    }
    
    TreeNode* deserialize(std::string data) {
        std::istringstream in(data);
        return deserializeHelper(in);
    }
    
private:
    void serializeHelper(TreeNode* root, std::ostringstream& out) {
        if (root) {
            out << root->val << " ";
            serializeHelper(root->left, out);
            serializeHelper(root->right, out);
        } else {
            out << "null ";
        }
    }
    
    TreeNode* deserializeHelper(std::istringstream& in) {
        std::string val;
        in >> val;
        
        if (val == "null") {
            return nullptr;
        }
        
        TreeNode* root = new TreeNode(std::stoi(val));
        root->left = deserializeHelper(in);
        root->right = deserializeHelper(in);
        return root;
    }
};
```

#### Problem: Word Ladder (Graph BFS)
```cpp
int ladderLength(std::string beginWord, std::string endWord, 
                std::vector<std::string>& wordList) {
    std::unordered_set<std::string> wordSet(wordList.begin(), wordList.end());
    
    if (wordSet.find(endWord) == wordSet.end()) {
        return 0;
    }
    
    std::queue<std::pair<std::string, int>> q;
    q.push({beginWord, 1});
    
    while (!q.empty()) {
        auto [currentWord, level] = q.front();
        q.pop();
        
        if (currentWord == endWord) {
            return level;
        }
        
        // Try changing each character
        for (int i = 0; i < currentWord.length(); i++) {
            char originalChar = currentWord[i];
            
            for (char c = 'a'; c <= 'z'; c++) {
                if (c == originalChar) continue;
                
                currentWord[i] = c;
                
                if (wordSet.find(currentWord) != wordSet.end()) {
                    q.push({currentWord, level + 1});
                    wordSet.erase(currentWord); // Mark as visited
                }
            }
            
            currentWord[i] = originalChar; // Restore
        }
    }
    
    return 0;
}
```

## Phase 3 Solutions

### Dynamic Programming Solutions

#### Problem: Palindrome Partitioning II
```cpp
int minCut(std::string s) {
    int n = s.length();
    
    // isPalindrome[i][j] = true if s[i...j] is palindrome
    std::vector<std::vector<bool>> isPalindrome(n, std::vector<bool>(n, false));
    
    // Fill palindrome table
    for (int len = 1; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            
            if (len == 1) {
                isPalindrome[i][j] = true;
            } else if (len == 2) {
                isPalindrome[i][j] = (s[i] == s[j]);
            } else {
                isPalindrome[i][j] = (s[i] == s[j]) && isPalindrome[i+1][j-1];
            }
        }
    }
    
    // dp[i] = minimum cuts needed for s[0...i]
    std::vector<int> dp(n, INT_MAX);
    
    for (int i = 0; i < n; i++) {
        if (isPalindrome[0][i]) {
            dp[i] = 0;
        } else {
            for (int j = 0; j < i; j++) {
                if (isPalindrome[j+1][i]) {
                    dp[i] = std::min(dp[i], dp[j] + 1);
                }
            }
        }
    }
    
    return dp[n-1];
}
```

#### Problem: Distinct Subsequences
```cpp
int numDistinct(std::string s, std::string t) {
    int m = s.length(), n = t.length();
    
    // dp[i][j] = number of ways to form t[0...j-1] using s[0...i-1]
    std::vector<std::vector<long long>> dp(m + 1, std::vector<long long>(n + 1, 0));
    
    // Empty string can be formed in one way
    for (int i = 0; i <= m; i++) {
        dp[i][0] = 1;
    }
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            dp[i][j] = dp[i-1][j]; // Don't use s[i-1]
            
            if (s[i-1] == t[j-1]) {
                dp[i][j] += dp[i-1][j-1]; // Use s[i-1]
            }
        }
    }
    
    return dp[m][n];
}
```

## Phase 4 Solutions

### Advanced Graph Algorithms

#### Problem: Network Delay Time (Dijkstra's)
```cpp
int networkDelayTime(std::vector<std::vector<int>>& times, int n, int k) {
    // Build adjacency list
    std::vector<std::vector<std::pair<int, int>>> graph(n + 1);
    for (auto& time : times) {
        graph[time[0]].push_back({time[1], time[2]});
    }
    
    // Dijkstra's algorithm
    std::vector<int> dist(n + 1, INT_MAX);
    std::priority_queue<std::pair<int, int>, 
                       std::vector<std::pair<int, int>>, 
                       std::greater<std::pair<int, int>>> pq;
    
    dist[k] = 0;
    pq.push({0, k});
    
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        
        if (d > dist[u]) continue;
        
        for (auto [v, w] : graph[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    
    int maxTime = 0;
    for (int i = 1; i <= n; i++) {
        if (dist[i] == INT_MAX) return -1;
        maxTime = std::max(maxTime, dist[i]);
    }
    
    return maxTime;
}
```

#### Problem: Minimum Spanning Tree (Kruskal's)
```cpp
class UnionFind {
public:
    std::vector<int> parent, rank;
    
    UnionFind(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    bool unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return false;
        
        if (rank[px] < rank[py]) {
            parent[px] = py;
        } else if (rank[px] > rank[py]) {
            parent[py] = px;
        } else {
            parent[py] = px;
            rank[px]++;
        }
        return true;
    }
};

int minimumSpanningTree(int n, std::vector<std::vector<int>>& edges) {
    // Sort edges by weight
    std::sort(edges.begin(), edges.end(), 
              [](const auto& a, const auto& b) {
                  return a[2] < b[2];
              });
    
    UnionFind uf(n);
    int mstWeight = 0, edgesUsed = 0;
    
    for (auto& edge : edges) {
        int u = edge[0], v = edge[1], w = edge[2];
        
        if (uf.unite(u, v)) {
            mstWeight += w;
            edgesUsed++;
            
            if (edgesUsed == n - 1) break;
        }
    }
    
    return mstWeight;
}
```

## Common Problem Patterns

### 1. Two Pointers Pattern
```cpp
// Remove duplicates from sorted array
int removeDuplicates(std::vector<int>& nums) {
    if (nums.empty()) return 0;
    
    int writeIndex = 1;
    for (int readIndex = 1; readIndex < nums.size(); readIndex++) {
        if (nums[readIndex] != nums[readIndex - 1]) {
            nums[writeIndex++] = nums[readIndex];
        }
    }
    return writeIndex;
}
```

### 2. Sliding Window Pattern
```cpp
// Maximum sum subarray of size k
int maxSumSubarray(std::vector<int>& nums, int k) {
    int windowSum = 0;
    
    // Calculate sum of first window
    for (int i = 0; i < k; i++) {
        windowSum += nums[i];
    }
    
    int maxSum = windowSum;
    
    // Slide the window
    for (int i = k; i < nums.size(); i++) {
        windowSum = windowSum - nums[i - k] + nums[i];
        maxSum = std::max(maxSum, windowSum);
    }
    
    return maxSum;
}
```

### 3. Fast and Slow Pointers
```cpp
// Find middle of linked list
ListNode* findMiddle(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;
    
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    return slow;
}
```

## Optimization Techniques

### 1. Space Optimization in DP
```cpp
// Space-optimized Fibonacci
int fibonacci(int n) {
    if (n <= 1) return n;
    
    int prev2 = 0, prev1 = 1;
    for (int i = 2; i <= n; i++) {
        int curr = prev1 + prev2;
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}
```

### 2. Bit Manipulation Optimizations
```cpp
// Check if number is power of 2
bool isPowerOfTwo(int n) {
    return n > 0 && (n & (n - 1)) == 0;
}

// Count set bits
int countSetBits(int n) {
    int count = 0;
    while (n) {
        n &= (n - 1); // Remove rightmost set bit
        count++;
    }
    return count;
}
```

### 3. Mathematical Optimizations
```cpp
// GCD using Euclidean algorithm
int gcd(int a, int b) {
    while (b) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Fast exponentiation
long long fastPow(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp & 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}
```

## Testing and Validation

### Test Case Generation
```cpp
// Generate test cases for algorithms
std::vector<int> generateRandomArray(int size, int minVal, int maxVal) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(minVal, maxVal);
    
    std::vector<int> arr(size);
    for (int& x : arr) {
        x = dis(gen);
    }
    return arr;
}

// Stress testing framework
void stressTest(int iterations) {
    for (int i = 0; i < iterations; i++) {
        auto testData = generateRandomArray(100, 1, 1000);
        
        // Test your algorithm
        auto result1 = yourAlgorithm(testData);
        auto result2 = bruteForceAlgorithm(testData);
        
        if (result1 != result2) {
            std::cout << "Test failed on iteration " << i << std::endl;
            // Print test case for debugging
            break;
        }
    }
}
```

Remember: These solutions represent optimal approaches for each problem. Always analyze time and space complexity, consider edge cases, and test thoroughly. The key to mastering algorithms is understanding the underlying patterns and being able to adapt solutions to new problems.
