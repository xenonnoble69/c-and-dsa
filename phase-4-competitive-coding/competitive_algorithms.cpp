/*
 * ===============================================================
 * PHASE 4: COMPETITIVE PROGRAMMING & INTERVIEW PREPARATION
 * ===============================================================
 * 
 * This file contains essential algorithms, data structures, and
 * techniques commonly used in competitive programming and technical
 * interviews. Each section includes optimized implementations,
 * complexity analysis, and practical applications.
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <climits>
#include <cmath>
#include <bitset>
using namespace std;

// ===============================================================
// FAST I/O OPTIMIZATION
// ===============================================================

void setupFastIO() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

// ===============================================================
// MATHEMATICAL ALGORITHMS
// ===============================================================

class MathUtils {
public:
    // Fast exponentiation - O(log n)
    long long fastPow(long long base, long long exp, long long mod = 1e9 + 7) {
        long long result = 1;
        while (exp > 0) {
            if (exp % 2 == 1) {
                result = (result * base) % mod;
            }
            base = (base * base) % mod;
            exp /= 2;
        }
        return result;
    }
    
    // GCD using Euclidean algorithm - O(log min(a,b))
    long long gcd(long long a, long long b) {
        return b == 0 ? a : gcd(b, a % b);
    }
    
    // LCM calculation
    long long lcm(long long a, long long b) {
        return (a / gcd(a, b)) * b;
    }
    
    // Sieve of Eratosthenes - O(n log log n)
    vector<bool> sieve(int n) {
        vector<bool> isPrime(n + 1, true);
        isPrime[0] = isPrime[1] = false;
        
        for (int i = 2; i * i <= n; i++) {
            if (isPrime[i]) {
                for (int j = i * i; j <= n; j += i) {
                    isPrime[j] = false;
                }
            }
        }
        return isPrime;
    }
    
    // Prime factorization - O(sqrt(n))
    vector<pair<long long, int>> primeFactors(long long n) {
        vector<pair<long long, int>> factors;
        
        for (long long i = 2; i * i <= n; i++) {
            int count = 0;
            while (n % i == 0) {
                n /= i;
                count++;
            }
            if (count > 0) {
                factors.push_back({i, count});
            }
        }
        if (n > 1) {
            factors.push_back({n, 1});
        }
        return factors;
    }
    
    // Modular inverse using Fermat's little theorem
    long long modInverse(long long a, long long mod = 1e9 + 7) {
        return fastPow(a, mod - 2, mod);
    }
    
    // Combination calculation with modulo
    long long nCr(int n, int r, long long mod = 1e9 + 7) {
        if (r > n || r < 0) return 0;
        if (r == 0 || r == n) return 1;
        
        // Calculate factorials
        vector<long long> fact(n + 1);
        fact[0] = 1;
        for (int i = 1; i <= n; i++) {
            fact[i] = (fact[i-1] * i) % mod;
        }
        
        long long numerator = fact[n];
        long long denominator = (fact[r] * fact[n-r]) % mod;
        return (numerator * modInverse(denominator, mod)) % mod;
    }
};

// ===============================================================
// STRING ALGORITHMS
// ===============================================================

class StringAlgorithms {
public:
    // KMP (Knuth-Morris-Pratt) pattern matching - O(n + m)
    vector<int> computeLPS(const string& pattern) {
        int m = pattern.length();
        vector<int> lps(m, 0);
        int len = 0, i = 1;
        
        while (i < m) {
            if (pattern[i] == pattern[len]) {
                lps[i++] = ++len;
            } else if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i++] = 0;
            }
        }
        return lps;
    }
    
    vector<int> KMP(const string& text, const string& pattern) {
        vector<int> result;
        vector<int> lps = computeLPS(pattern);
        int i = 0, j = 0;
        int n = text.length(), m = pattern.length();
        
        while (i < n) {
            if (text[i] == pattern[j]) {
                i++; j++;
            }
            
            if (j == m) {
                result.push_back(i - j);
                j = lps[j - 1];
            } else if (i < n && text[i] != pattern[j]) {
                if (j != 0) {
                    j = lps[j - 1];
                } else {
                    i++;
                }
            }
        }
        return result;
    }
    
    // Z-algorithm for pattern matching - O(n)
    vector<int> zAlgorithm(const string& s) {
        int n = s.length();
        vector<int> z(n);
        int l = 0, r = 0;
        
        for (int i = 1; i < n; i++) {
            if (i <= r) {
                z[i] = min(r - i + 1, z[i - l]);
            }
            while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
                z[i]++;
            }
            if (i + z[i] - 1 > r) {
                l = i;
                r = i + z[i] - 1;
            }
        }
        return z;
    }
    
    // Manacher's algorithm for palindromes - O(n)
    string preprocess(const string& s) {
        string result = "^";
        for (char c : s) {
            result += "#" + string(1, c);
        }
        result += "#$";
        return result;
    }
    
    string longestPalindrome(const string& s) {
        string processed = preprocess(s);
        int n = processed.length();
        vector<int> P(n, 0);
        int center = 0, right = 0;
        
        for (int i = 1; i < n - 1; i++) {
            int mirror = 2 * center - i;
            
            if (i < right) {
                P[i] = min(right - i, P[mirror]);
            }
            
            while (processed[i + P[i] + 1] == processed[i - P[i] - 1]) {
                P[i]++;
            }
            
            if (i + P[i] > right) {
                center = i;
                right = i + P[i];
            }
        }
        
        int maxLen = 0, centerIndex = 0;
        for (int i = 1; i < n - 1; i++) {
            if (P[i] > maxLen) {
                maxLen = P[i];
                centerIndex = i;
            }
        }
        
        int start = (centerIndex - maxLen) / 2;
        return s.substr(start, maxLen);
    }
};

// ===============================================================
// GRAPH ALGORITHMS
// ===============================================================

class GraphAlgorithms {
private:
    vector<vector<pair<int, int>>> adjList; // {neighbor, weight}
    int V;
    
public:
    GraphAlgorithms(int vertices) : V(vertices) {
        adjList.resize(V);
    }
    
    void addEdge(int u, int v, int weight = 1) {
        adjList[u].push_back({v, weight});
        adjList[v].push_back({u, weight}); // For undirected graph
    }
    
    // Dijkstra's shortest path - O(V log V + E)
    vector<int> dijkstra(int start) {
        vector<int> dist(V, INT_MAX);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        
        dist[start] = 0;
        pq.push({0, start});
        
        while (!pq.empty()) {
            int d = pq.top().first;
            int u = pq.top().second;
            pq.pop();
            
            if (d > dist[u]) continue;
            
            for (auto& edge : adjList[u]) {
                int v = edge.first;
                int weight = edge.second;
                
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                }
            }
        }
        return dist;
    }
    
    // Floyd-Warshall all-pairs shortest path - O(V³)
    vector<vector<int>> floydWarshall() {
        vector<vector<int>> dist(V, vector<int>(V, INT_MAX));
        
        // Initialize distances
        for (int i = 0; i < V; i++) {
            dist[i][i] = 0;
            for (auto& edge : adjList[i]) {
                dist[i][edge.first] = edge.second;
            }
        }
        
        // Floyd-Warshall main loop
        for (int k = 0; k < V; k++) {
            for (int i = 0; i < V; i++) {
                for (int j = 0; j < V; j++) {
                    if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX) {
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                    }
                }
            }
        }
        return dist;
    }
    
    // Topological sort using DFS - O(V + E)
    void topologicalSortUtil(int v, vector<bool>& visited, stack<int>& Stack) {
        visited[v] = true;
        
        for (auto& edge : adjList[v]) {
            if (!visited[edge.first]) {
                topologicalSortUtil(edge.first, visited, Stack);
            }
        }
        Stack.push(v);
    }
    
    vector<int> topologicalSort() {
        stack<int> Stack;
        vector<bool> visited(V, false);
        
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                topologicalSortUtil(i, visited, Stack);
            }
        }
        
        vector<int> result;
        while (!Stack.empty()) {
            result.push_back(Stack.top());
            Stack.pop();
        }
        return result;
    }
    
    // Strongly Connected Components (Kosaraju's algorithm) - O(V + E)
    void fillOrder(int v, vector<bool>& visited, stack<int>& Stack) {
        visited[v] = true;
        for (auto& edge : adjList[v]) {
            if (!visited[edge.first]) {
                fillOrder(edge.first, visited, Stack);
            }
        }
        Stack.push(v);
    }
    
    void DFSUtil(int v, vector<bool>& visited, vector<int>& component, 
                 const vector<vector<int>>& revGraph) {
        visited[v] = true;
        component.push_back(v);
        
        for (int u : revGraph[v]) {
            if (!visited[u]) {
                DFSUtil(u, visited, component, revGraph);
            }
        }
    }
    
    vector<vector<int>> stronglyConnectedComponents() {
        stack<int> Stack;
        vector<bool> visited(V, false);
        
        // Fill vertices in stack according to their finishing times
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                fillOrder(i, visited, Stack);
            }
        }
        
        // Create reversed graph
        vector<vector<int>> revGraph(V);
        for (int v = 0; v < V; v++) {
            for (auto& edge : adjList[v]) {
                revGraph[edge.first].push_back(v);
            }
        }
        
        // Process all vertices in order defined by Stack
        fill(visited.begin(), visited.end(), false);
        vector<vector<int>> sccs;
        
        while (!Stack.empty()) {
            int v = Stack.top();
            Stack.pop();
            
            if (!visited[v]) {
                vector<int> component;
                DFSUtil(v, visited, component, revGraph);
                sccs.push_back(component);
            }
        }
        return sccs;
    }
};

// ===============================================================
// ADVANCED DATA STRUCTURES
// ===============================================================

// Disjoint Set Union (Union-Find) with path compression and union by rank
class DSU {
private:
    vector<int> parent, rank;
    
public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }
    
    bool unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return false;
        
        // Union by rank
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
    
    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};

// Segment Tree for range queries and updates
class SegmentTree {
private:
    vector<int> tree;
    int n;
    
    void build(vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            build(arr, 2*node, start, mid);
            build(arr, 2*node+1, mid+1, end);
            tree[node] = tree[2*node] + tree[2*node+1];
        }
    }
    
    void updateHelper(int node, int start, int end, int idx, int val) {
        if (start == end) {
            tree[node] = val;
        } else {
            int mid = (start + end) / 2;
            if (idx <= mid) {
                updateHelper(2*node, start, mid, idx, val);
            } else {
                updateHelper(2*node+1, mid+1, end, idx, val);
            }
            tree[node] = tree[2*node] + tree[2*node+1];
        }
    }
    
    int queryHelper(int node, int start, int end, int l, int r) {
        if (r < start || end < l) {
            return 0; // Out of range
        }
        if (l <= start && end <= r) {
            return tree[node]; // Current segment is totally within range
        }
        int mid = (start + end) / 2;
        return queryHelper(2*node, start, mid, l, r) +
               queryHelper(2*node+1, mid+1, end, l, r);
    }
    
public:
    SegmentTree(vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        build(arr, 1, 0, n-1);
    }
    
    void update(int idx, int val) {
        updateHelper(1, 0, n-1, idx, val);
    }
    
    int query(int l, int r) {
        return queryHelper(1, 0, n-1, l, r);
    }
};

// Trie (Prefix Tree) for string operations
class Trie {
private:
    struct TrieNode {
        TrieNode* children[26];
        bool isEndOfWord;
        int count; // Number of words passing through this node
        
        TrieNode() {
            for (int i = 0; i < 26; i++) {
                children[i] = nullptr;
            }
            isEndOfWord = false;
            count = 0;
        }
    };
    
    TrieNode* root;
    
public:
    Trie() {
        root = new TrieNode();
    }
    
    void insert(const string& word) {
        TrieNode* curr = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!curr->children[idx]) {
                curr->children[idx] = new TrieNode();
            }
            curr = curr->children[idx];
            curr->count++;
        }
        curr->isEndOfWord = true;
    }
    
    bool search(const string& word) {
        TrieNode* curr = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!curr->children[idx]) {
                return false;
            }
            curr = curr->children[idx];
        }
        return curr->isEndOfWord;
    }
    
    bool startsWith(const string& prefix) {
        TrieNode* curr = root;
        for (char c : prefix) {
            int idx = c - 'a';
            if (!curr->children[idx]) {
                return false;
            }
            curr = curr->children[idx];
        }
        return true;
    }
    
    int countWordsWithPrefix(const string& prefix) {
        TrieNode* curr = root;
        for (char c : prefix) {
            int idx = c - 'a';
            if (!curr->children[idx]) {
                return 0;
            }
            curr = curr->children[idx];
        }
        return curr->count;
    }
};

// ===============================================================
// BIT MANIPULATION UTILITIES
// ===============================================================

class BitUtils {
public:
    // Count set bits (Brian Kernighan's algorithm)
    int countSetBits(int n) {
        int count = 0;
        while (n) {
            n &= (n - 1); // Clear the lowest set bit
            count++;
        }
        return count;
    }
    
    // Check if number is power of 2
    bool isPowerOfTwo(int n) {
        return n > 0 && (n & (n - 1)) == 0;
    }
    
    // Find the only non-repeating element (XOR approach)
    int singleNumber(vector<int>& nums) {
        int result = 0;
        for (int num : nums) {
            result ^= num;
        }
        return result;
    }
    
    // Generate all subsets using bit manipulation
    vector<vector<int>> generateSubsets(vector<int>& nums) {
        vector<vector<int>> subsets;
        int n = nums.size();
        
        for (int mask = 0; mask < (1 << n); mask++) {
            vector<int> subset;
            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) {
                    subset.push_back(nums[i]);
                }
            }
            subsets.push_back(subset);
        }
        return subsets;
    }
    
    // Find position of rightmost set bit
    int rightmostSetBit(int n) {
        return n & (-n);
    }
    
    // Swap two numbers without temporary variable
    void swapNumbers(int& a, int& b) {
        if (a != b) {
            a ^= b;
            b ^= a;
            a ^= b;
        }
    }
};

// ===============================================================
// COMPETITIVE PROGRAMMING UTILITIES
// ===============================================================

class CPUtils {
public:
    // Binary search template
    template<typename T>
    int binarySearch(vector<T>& arr, T target) {
        int left = 0, right = arr.size() - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (arr[mid] == target) {
                return mid;
            } else if (arr[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return -1;
    }
    
    // Lower bound and upper bound
    template<typename T>
    int lowerBound(vector<T>& arr, T target) {
        int left = 0, right = arr.size();
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] < target) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return left;
    }
    
    // Coordinate compression
    void coordinateCompression(vector<int>& coords) {
        sort(coords.begin(), coords.end());
        coords.erase(unique(coords.begin(), coords.end()), coords.end());
    }
    
    // Next greater element using stack
    vector<int> nextGreaterElement(vector<int>& nums) {
        int n = nums.size();
        vector<int> result(n, -1);
        stack<int> st;
        
        for (int i = 0; i < n; i++) {
            while (!st.empty() && nums[st.top()] < nums[i]) {
                result[st.top()] = nums[i];
                st.pop();
            }
            st.push(i);
        }
        return result;
    }
    
    // Sliding window maximum using deque
    vector<int> slidingWindowMaximum(vector<int>& nums, int k) {
        vector<int> result;
        deque<int> dq; // Store indices
        
        for (int i = 0; i < nums.size(); i++) {
            // Remove elements outside window
            while (!dq.empty() && dq.front() <= i - k) {
                dq.pop_front();
            }
            
            // Remove smaller elements
            while (!dq.empty() && nums[dq.back()] <= nums[i]) {
                dq.pop_back();
            }
            
            dq.push_back(i);
            
            if (i >= k - 1) {
                result.push_back(nums[dq.front()]);
            }
        }
        return result;
    }
};

// ===============================================================
// TESTING AND DEMONSTRATION
// ===============================================================

void demonstrateAlgorithms() {
    cout << "=== COMPETITIVE PROGRAMMING ALGORITHMS DEMO ===\n\n";
    
    // Setup fast I/O
    setupFastIO();
    
    // Test mathematical utilities
    MathUtils math;
    cout << "GCD(48, 18): " << math.gcd(48, 18) << "\n";
    cout << "LCM(12, 8): " << math.lcm(12, 8) << "\n";
    cout << "2^10 mod 1000: " << math.fastPow(2, 10, 1000) << "\n";
    
    // Test string algorithms
    StringAlgorithms stringAlgo;
    vector<int> matches = stringAlgo.KMP("ababcababa", "ababa");
    cout << "Pattern matches found: " << matches.size() << "\n";
    
    // Test graph algorithms
    GraphAlgorithms graph(5);
    graph.addEdge(0, 1, 2);
    graph.addEdge(0, 2, 4);
    graph.addEdge(1, 2, 1);
    graph.addEdge(1, 3, 7);
    graph.addEdge(2, 4, 3);
    
    vector<int> distances = graph.dijkstra(0);
    cout << "Shortest distances from node 0:\n";
    for (int i = 0; i < distances.size(); i++) {
        cout << "To " << i << ": " << distances[i] << "\n";
    }
    
    // Test advanced data structures
    vector<int> arr = {1, 3, 5, 7, 9, 11};
    SegmentTree segTree(arr);
    cout << "Sum of range [1, 3]: " << segTree.query(1, 3) << "\n";
    
    Trie trie;
    trie.insert("apple");
    trie.insert("app");
    trie.insert("application");
    cout << "Words with prefix 'app': " << trie.countWordsWithPrefix("app") << "\n";
    
    // Test bit manipulation
    BitUtils bitUtils;
    cout << "Set bits in 15: " << bitUtils.countSetBits(15) << "\n";
    cout << "Is 16 power of 2: " << bitUtils.isPowerOfTwo(16) << "\n";
    
    cout << "\n=== All algorithms demonstrated successfully! ===\n";
}

int main() {
    demonstrateAlgorithms();
    return 0;
}

/*
 * ===============================================================
 * COMPETITIVE PROGRAMMING CHEAT SHEET
 * ===============================================================
 * 
 * COMMON COMPLEXITY TARGETS:
 * - n ≤ 10: O(n!), O(2^n)
 * - n ≤ 20: O(2^n), O(n²)
 * - n ≤ 500: O(n³)
 * - n ≤ 5000: O(n²)
 * - n ≤ 10⁶: O(n log n)
 * - n ≤ 10⁸: O(n)
 * 
 * ESSENTIAL TEMPLATES:
 * 1. Fast I/O setup
 * 2. Binary search variations
 * 3. Graph traversals (DFS/BFS)
 * 4. Dynamic programming patterns
 * 5. String processing algorithms
 * 
 * COMMON TECHNIQUES:
 * - Two pointers
 * - Sliding window
 * - Prefix sums
 * - Coordinate compression
 * - Bit manipulation
 * - Greedy algorithms
 * 
 * DEBUGGING TIPS:
 * - Use assert statements
 * - Test with edge cases
 * - Check integer overflow
 * - Verify array bounds
 * - Handle special cases (n=0, n=1)
 */
