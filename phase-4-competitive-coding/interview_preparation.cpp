/*
 * ===============================================================
 * TECHNICAL INTERVIEW PREPARATION
 * ===============================================================
 * 
 * Comprehensive collection of commonly asked interview questions
 * with multiple solution approaches, complexity analysis, and
 * detailed explanations. Organized by company and difficulty level.
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
#include <climits>
using namespace std;

// ===============================================================
// ARRAY AND STRING PROBLEMS
// ===============================================================

class ArrayStringProblems {
public:
    /*
     * PROBLEM: Two Sum
     * Given array and target, find indices of two numbers that add up to target
     * Companies: Google, Amazon, Facebook, Microsoft
     */
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> map;
        for (int i = 0; i < nums.size(); i++) {
            int complement = target - nums[i];
            if (map.find(complement) != map.end()) {
                return {map[complement], i};
            }
            map[nums[i]] = i;
        }
        return {};
    }
    
    /*
     * PROBLEM: Valid Anagram
     * Check if two strings are anagrams
     * Companies: Amazon, Microsoft, Bloomberg
     */
    bool isAnagram(string s, string t) {
        if (s.length() != t.length()) return false;
        
        vector<int> count(26, 0);
        for (int i = 0; i < s.length(); i++) {
            count[s[i] - 'a']++;
            count[t[i] - 'a']--;
        }
        
        for (int c : count) {
            if (c != 0) return false;
        }
        return true;
    }
    
    /*
     * PROBLEM: Product of Array Except Self
     * Return array where output[i] = product of all elements except nums[i]
     * Companies: Google, Amazon, Facebook
     */
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> result(n, 1);
        
        // Forward pass: result[i] = product of all elements before i
        for (int i = 1; i < n; i++) {
            result[i] = result[i-1] * nums[i-1];
        }
        
        // Backward pass: multiply by product of all elements after i
        int rightProduct = 1;
        for (int i = n-1; i >= 0; i--) {
            result[i] *= rightProduct;
            rightProduct *= nums[i];
        }
        
        return result;
    }
    
    /*
     * PROBLEM: Container With Most Water
     * Find max area that can be formed by two vertical lines
     * Companies: Google, Amazon, Microsoft
     */
    int maxArea(vector<int>& height) {
        int left = 0, right = height.size() - 1;
        int maxWater = 0;
        
        while (left < right) {
            int width = right - left;
            int minHeight = min(height[left], height[right]);
            maxWater = max(maxWater, width * minHeight);
            
            if (height[left] < height[right]) {
                left++;
            } else {
                right--;
            }
        }
        return maxWater;
    }
    
    /*
     * PROBLEM: Longest Substring Without Repeating Characters
     * Find length of longest substring without repeating characters
     * Companies: Google, Amazon, Microsoft, Facebook
     */
    int lengthOfLongestSubstring(string s) {
        unordered_set<char> seen;
        int left = 0, maxLen = 0;
        
        for (int right = 0; right < s.length(); right++) {
            while (seen.count(s[right])) {
                seen.erase(s[left]);
                left++;
            }
            seen.insert(s[right]);
            maxLen = max(maxLen, right - left + 1);
        }
        return maxLen;
    }
    
    /*
     * PROBLEM: Group Anagrams
     * Group strings that are anagrams of each other
     * Companies: Google, Amazon, Uber
     */
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> groups;
        
        for (string& str : strs) {
            string key = str;
            sort(key.begin(), key.end());
            groups[key].push_back(str);
        }
        
        vector<vector<string>> result;
        for (auto& group : groups) {
            result.push_back(group.second);
        }
        return result;
    }
};

// ===============================================================
// LINKED LIST PROBLEMS
// ===============================================================

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class LinkedListProblems {
public:
    /*
     * PROBLEM: Reverse Linked List
     * Reverse a singly linked list
     * Companies: Google, Amazon, Microsoft, Facebook
     */
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* curr = head;
        
        while (curr) {
            ListNode* nextTemp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextTemp;
        }
        return prev;
    }
    
    /*
     * PROBLEM: Detect Cycle in Linked List
     * Check if linked list has a cycle
     * Companies: Google, Amazon, Microsoft
     */
    bool hasCycle(ListNode* head) {
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
     * PROBLEM: Merge Two Sorted Lists
     * Merge two sorted linked lists
     * Companies: Google, Amazon, Microsoft, Facebook
     */
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode dummy(0);
        ListNode* tail = &dummy;
        
        while (l1 && l2) {
            if (l1->val <= l2->val) {
                tail->next = l1;
                l1 = l1->next;
            } else {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }
        
        tail->next = l1 ? l1 : l2;
        return dummy.next;
    }
    
    /*
     * PROBLEM: Remove Nth Node From End
     * Remove nth node from end of linked list
     * Companies: Google, Amazon, Microsoft
     */
    ListNode* removeNthFromEnd(ListNode* head, int n) {
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
        
        // Remove the nth node from end
        second->next = second->next->next;
        return dummy.next;
    }
};

// ===============================================================
// TREE PROBLEMS
// ===============================================================

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class TreeProblems {
public:
    /*
     * PROBLEM: Maximum Depth of Binary Tree
     * Find maximum depth of binary tree
     * Companies: Google, Amazon, Microsoft, Facebook
     */
    int maxDepth(TreeNode* root) {
        if (!root) return 0;
        return 1 + max(maxDepth(root->left), maxDepth(root->right));
    }
    
    /*
     * PROBLEM: Validate Binary Search Tree
     * Check if binary tree is valid BST
     * Companies: Google, Amazon, Microsoft, Facebook
     */
    bool isValidBST(TreeNode* root) {
        return validate(root, LONG_MIN, LONG_MAX);
    }
    
    bool validate(TreeNode* node, long minVal, long maxVal) {
        if (!node) return true;
        
        if (node->val <= minVal || node->val >= maxVal) {
            return false;
        }
        
        return validate(node->left, minVal, node->val) &&
               validate(node->right, node->val, maxVal);
    }
    
    /*
     * PROBLEM: Binary Tree Level Order Traversal
     * Return level order traversal of binary tree
     * Companies: Google, Amazon, Microsoft, Facebook
     */
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> result;
        if (!root) return result;
        
        queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            int levelSize = q.size();
            vector<int> level;
            
            for (int i = 0; i < levelSize; i++) {
                TreeNode* node = q.front();
                q.pop();
                level.push_back(node->val);
                
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            result.push_back(level);
        }
        return result;
    }
    
    /*
     * PROBLEM: Lowest Common Ancestor
     * Find LCA of two nodes in BST
     * Companies: Google, Amazon, Microsoft, Facebook
     */
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root) return nullptr;
        
        if (root->val > p->val && root->val > q->val) {
            return lowestCommonAncestor(root->left, p, q);
        } else if (root->val < p->val && root->val < q->val) {
            return lowestCommonAncestor(root->right, p, q);
        } else {
            return root;
        }
    }
    
    /*
     * PROBLEM: Path Sum
     * Check if tree has path with given sum
     * Companies: Google, Amazon, Microsoft
     */
    bool hasPathSum(TreeNode* root, int targetSum) {
        if (!root) return false;
        
        if (!root->left && !root->right) {
            return root->val == targetSum;
        }
        
        return hasPathSum(root->left, targetSum - root->val) ||
               hasPathSum(root->right, targetSum - root->val);
    }
};

// ===============================================================
// DYNAMIC PROGRAMMING PROBLEMS
// ===============================================================

class DynamicProgrammingProblems {
public:
    /*
     * PROBLEM: House Robber
     * Maximum money that can be robbed without robbing adjacent houses
     * Companies: Google, Amazon, Microsoft
     */
    int rob(vector<int>& nums) {
        if (nums.empty()) return 0;
        if (nums.size() == 1) return nums[0];
        
        int prev2 = 0, prev1 = 0;
        for (int num : nums) {
            int curr = max(prev1, prev2 + num);
            prev2 = prev1;
            prev1 = curr;
        }
        return prev1;
    }
    
    /*
     * PROBLEM: Best Time to Buy and Sell Stock
     * Find maximum profit from stock transactions
     * Companies: Google, Amazon, Microsoft, Facebook
     */
    int maxProfit(vector<int>& prices) {
        int minPrice = INT_MAX;
        int maxProfit = 0;
        
        for (int price : prices) {
            if (price < minPrice) {
                minPrice = price;
            } else {
                maxProfit = max(maxProfit, price - minPrice);
            }
        }
        return maxProfit;
    }
    
    /*
     * PROBLEM: Unique Paths
     * Number of unique paths from top-left to bottom-right
     * Companies: Google, Amazon, Microsoft
     */
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m, vector<int>(n, 1));
        
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        }
        return dp[m-1][n-1];
    }
    
    /*
     * PROBLEM: Decode Ways
     * Number of ways to decode a string of digits
     * Companies: Google, Amazon, Microsoft, Facebook
     */
    int numDecodings(string s) {
        if (s.empty() || s[0] == '0') return 0;
        
        int prev2 = 1, prev1 = 1;
        
        for (int i = 1; i < s.length(); i++) {
            int curr = 0;
            
            // Single digit
            if (s[i] != '0') {
                curr += prev1;
            }
            
            // Two digits
            int twoDigit = (s[i-1] - '0') * 10 + (s[i] - '0');
            if (twoDigit >= 10 && twoDigit <= 26) {
                curr += prev2;
            }
            
            prev2 = prev1;
            prev1 = curr;
        }
        return prev1;
    }
};

// ===============================================================
// GRAPH PROBLEMS
// ===============================================================

class GraphProblems {
public:
    /*
     * PROBLEM: Number of Islands
     * Count number of islands in 2D grid
     * Companies: Google, Amazon, Microsoft, Facebook
     */
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty()) return 0;
        
        int islands = 0;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                if (grid[i][j] == '1') {
                    islands++;
                    dfs(grid, i, j);
                }
            }
        }
        return islands;
    }
    
    void dfs(vector<vector<char>>& grid, int i, int j) {
        if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size() || 
            grid[i][j] == '0') {
            return;
        }
        
        grid[i][j] = '0'; // Mark as visited
        dfs(grid, i+1, j);
        dfs(grid, i-1, j);
        dfs(grid, i, j+1);
        dfs(grid, i, j-1);
    }
    
    /*
     * PROBLEM: Course Schedule
     * Check if courses can be completed (cycle detection)
     * Companies: Google, Amazon, Microsoft, Facebook
     */
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> graph(numCourses);
        vector<int> indegree(numCourses, 0);
        
        // Build graph and calculate indegrees
        for (auto& prereq : prerequisites) {
            graph[prereq[1]].push_back(prereq[0]);
            indegree[prereq[0]]++;
        }
        
        // Topological sort using Kahn's algorithm
        queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }
        
        int completed = 0;
        while (!q.empty()) {
            int course = q.front();
            q.pop();
            completed++;
            
            for (int neighbor : graph[course]) {
                indegree[neighbor]--;
                if (indegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }
        
        return completed == numCourses;
    }
    
    /*
     * PROBLEM: Clone Graph
     * Clone an undirected graph
     * Companies: Google, Amazon, Microsoft, Facebook
     */
    struct Node {
        int val;
        vector<Node*> neighbors;
        Node(int _val) : val(_val) {}
    };
    
    Node* cloneGraph(Node* node) {
        if (!node) return nullptr;
        
        unordered_map<Node*, Node*> visited;
        return dfsClone(node, visited);
    }
    
    Node* dfsClone(Node* node, unordered_map<Node*, Node*>& visited) {
        if (visited.count(node)) {
            return visited[node];
        }
        
        Node* clone = new Node(node->val);
        visited[node] = clone;
        
        for (Node* neighbor : node->neighbors) {
            clone->neighbors.push_back(dfsClone(neighbor, visited));
        }
        
        return clone;
    }
};

// ===============================================================
// SYSTEM DESIGN INTERVIEW COMPONENTS
// ===============================================================

class SystemDesignConcepts {
public:
    /*
     * DESIGN: LRU Cache
     * Least Recently Used cache implementation
     * Companies: Google, Amazon, Microsoft, Facebook
     */
    class LRUCache {
    private:
        struct Node {
            int key, value;
            Node* prev;
            Node* next;
            Node(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
        };
        
        int capacity;
        unordered_map<int, Node*> cache;
        Node* head;
        Node* tail;
        
        void addToHead(Node* node) {
            node->prev = head;
            node->next = head->next;
            head->next->prev = node;
            head->next = node;
        }
        
        void removeNode(Node* node) {
            node->prev->next = node->next;
            node->next->prev = node->prev;
        }
        
        Node* removeTail() {
            Node* lastNode = tail->prev;
            removeNode(lastNode);
            return lastNode;
        }
        
        void moveToHead(Node* node) {
            removeNode(node);
            addToHead(node);
        }
        
    public:
        LRUCache(int capacity) : capacity(capacity) {
            head = new Node(0, 0);
            tail = new Node(0, 0);
            head->next = tail;
            tail->prev = head;
        }
        
        int get(int key) {
            if (cache.count(key)) {
                Node* node = cache[key];
                moveToHead(node);
                return node->value;
            }
            return -1;
        }
        
        void put(int key, int value) {
            if (cache.count(key)) {
                Node* node = cache[key];
                node->value = value;
                moveToHead(node);
            } else {
                Node* newNode = new Node(key, value);
                
                if (cache.size() >= capacity) {
                    Node* tail = removeTail();
                    cache.erase(tail->key);
                    delete tail;
                }
                
                cache[key] = newNode;
                addToHead(newNode);
            }
        }
    };
    
    /*
     * DESIGN: Min Stack
     * Stack with getMin operation in O(1)
     * Companies: Google, Amazon, Microsoft
     */
    class MinStack {
    private:
        stack<int> dataStack;
        stack<int> minStack;
        
    public:
        void push(int val) {
            dataStack.push(val);
            if (minStack.empty() || val <= minStack.top()) {
                minStack.push(val);
            }
        }
        
        void pop() {
            if (dataStack.top() == minStack.top()) {
                minStack.pop();
            }
            dataStack.pop();
        }
        
        int top() {
            return dataStack.top();
        }
        
        int getMin() {
            return minStack.top();
        }
    };
};

// ===============================================================
// INTERVIEW SIMULATION AND TIPS
// ===============================================================

void interviewSimulation() {
    cout << "=== TECHNICAL INTERVIEW SIMULATION ===\n\n";
    
    cout << "PROBLEM: Given an array of integers, find two numbers that add up to a target.\n";
    cout << "APPROACH:\n";
    cout << "1. Clarify requirements (duplicates? multiple solutions?)\n";
    cout << "2. Discuss brute force O(n²) solution\n";
    cout << "3. Optimize using hash map O(n) solution\n";
    cout << "4. Code the solution\n";
    cout << "5. Test with examples\n";
    cout << "6. Discuss edge cases\n\n";
    
    // Test Two Sum
    ArrayStringProblems problems;
    vector<int> nums = {2, 7, 11, 15};
    int target = 9;
    vector<int> result = problems.twoSum(nums, target);
    cout << "Two Sum Result: [" << result[0] << ", " << result[1] << "]\n";
    
    cout << "\n=== INTERVIEW TIPS ===\n";
    cout << "1. Always clarify the problem before coding\n";
    cout << "2. Start with brute force, then optimize\n";
    cout << "3. Think out loud during problem solving\n";
    cout << "4. Test your solution with examples\n";
    cout << "5. Consider edge cases and error handling\n";
    cout << "6. Analyze time and space complexity\n";
    cout << "7. Be prepared to make modifications\n\n";
}

int main() {
    interviewSimulation();
    return 0;
}

/*
 * ===============================================================
 * INTERVIEW PREPARATION CHECKLIST
 * ===============================================================
 * 
 * TECHNICAL SKILLS:
 * ✓ Data Structures: Arrays, Linked Lists, Trees, Graphs, Hash Tables
 * ✓ Algorithms: Sorting, Searching, Dynamic Programming, Greedy
 * ✓ System Design: Scalability, Load Balancing, Caching, Databases
 * ✓ Coding: Clean code, Error handling, Edge cases
 * 
 * BEHAVIORAL SKILLS:
 * ✓ Problem-solving approach
 * ✓ Communication skills
 * ✓ Teamwork examples
 * ✓ Leadership experiences
 * ✓ Handling failures/challenges
 * 
 * COMPANY RESEARCH:
 * ✓ Company mission and values
 * ✓ Recent news and products
 * ✓ Team structure and culture
 * ✓ Common interview questions
 * 
 * PRACTICE SCHEDULE:
 * ✓ Daily coding practice (1-2 hours)
 * ✓ Mock interviews weekly
 * ✓ System design practice
 * ✓ Behavioral question preparation
 * 
 * RESOURCES:
 * ✓ LeetCode/HackerRank problems
 * ✓ Cracking the Coding Interview
 * ✓ System Design Interview books
 * ✓ Company-specific preparation guides
 */
