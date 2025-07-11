/*
 * ===============================================================
 * PHASE 3: ADVANCED ALGORITHMS - DYNAMIC PROGRAMMING PROBLEMS
 * ===============================================================
 * 
 * Comprehensive collection of Dynamic Programming problems organized
 * by difficulty and type. Each problem includes:
 * - Problem statement and constraints
 * - Multiple solution approaches (recursive, memoized, tabulated)
 * - Time and space complexity analysis
 * - Detailed explanations and optimization techniques
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <climits>
using namespace std;

// ===============================================================
// BASIC DP PROBLEMS (BEGINNER LEVEL)
// ===============================================================

/*
 * PROBLEM 1: FIBONACCI SEQUENCE
 * Find the nth Fibonacci number
 * F(n) = F(n-1) + F(n-2), F(0) = 0, F(1) = 1
 */
class FibonacciSolutions {
public:
    // Recursive solution - O(2^n) time, O(n) space
    int fibRecursive(int n) {
        if (n <= 1) return n;
        return fibRecursive(n-1) + fibRecursive(n-2);
    }
    
    // Memoized solution - O(n) time, O(n) space
    int fibMemoized(int n, vector<int>& memo) {
        if (n <= 1) return n;
        if (memo[n] != -1) return memo[n];
        memo[n] = fibMemoized(n-1, memo) + fibMemoized(n-2, memo);
        return memo[n];
    }
    
    // Tabulated solution - O(n) time, O(n) space
    int fibTabulated(int n) {
        if (n <= 1) return n;
        vector<int> dp(n+1);
        dp[0] = 0; dp[1] = 1;
        for (int i = 2; i <= n; i++) {
            dp[i] = dp[i-1] + dp[i-2];
        }
        return dp[n];
    }
    
    // Space optimized - O(n) time, O(1) space
    int fibOptimized(int n) {
        if (n <= 1) return n;
        int prev2 = 0, prev1 = 1, curr;
        for (int i = 2; i <= n; i++) {
            curr = prev1 + prev2;
            prev2 = prev1;
            prev1 = curr;
        }
        return curr;
    }
};

/*
 * PROBLEM 2: CLIMBING STAIRS
 * Find number of ways to reach nth stair (can climb 1 or 2 steps)
 */
class ClimbingStairs {
public:
    int climbStairs(int n) {
        if (n <= 2) return n;
        vector<int> dp(n+1);
        dp[1] = 1; dp[2] = 2;
        for (int i = 3; i <= n; i++) {
            dp[i] = dp[i-1] + dp[i-2];
        }
        return dp[n];
    }
    
    // Space optimized version
    int climbStairsOptimized(int n) {
        if (n <= 2) return n;
        int prev2 = 1, prev1 = 2, curr;
        for (int i = 3; i <= n; i++) {
            curr = prev1 + prev2;
            prev2 = prev1;
            prev1 = curr;
        }
        return curr;
    }
};

/*
 * PROBLEM 3: MINIMUM COST CLIMBING STAIRS
 * Find minimum cost to reach top of stairs
 */
class MinCostClimbingStairs {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();
        vector<int> dp(n);
        dp[0] = cost[0];
        dp[1] = cost[1];
        
        for (int i = 2; i < n; i++) {
            dp[i] = cost[i] + min(dp[i-1], dp[i-2]);
        }
        return min(dp[n-1], dp[n-2]);
    }
};

// ===============================================================
// INTERMEDIATE DP PROBLEMS
// ===============================================================

/*
 * PROBLEM 4: COIN CHANGE
 * Find minimum number of coins to make amount
 */
class CoinChange {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, amount + 1);
        dp[0] = 0;
        
        for (int i = 1; i <= amount; i++) {
            for (int coin : coins) {
                if (coin <= i) {
                    dp[i] = min(dp[i], dp[i - coin] + 1);
                }
            }
        }
        return dp[amount] > amount ? -1 : dp[amount];
    }
    
    // Number of ways to make amount
    int coinChangeWays(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, 0);
        dp[0] = 1;
        
        for (int coin : coins) {
            for (int i = coin; i <= amount; i++) {
                dp[i] += dp[i - coin];
            }
        }
        return dp[amount];
    }
};

/*
 * PROBLEM 5: LONGEST INCREASING SUBSEQUENCE (LIS)
 * Find length of longest increasing subsequence
 */
class LongestIncreasingSubsequence {
public:
    // O(n^2) DP solution
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n, 1);
        int maxLength = 1;
        
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] > nums[j]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            maxLength = max(maxLength, dp[i]);
        }
        return maxLength;
    }
    
    // O(n log n) Binary search solution
    int lengthOfLISOptimized(vector<int>& nums) {
        vector<int> tails;
        for (int num : nums) {
            auto it = lower_bound(tails.begin(), tails.end(), num);
            if (it == tails.end()) {
                tails.push_back(num);
            } else {
                *it = num;
            }
        }
        return tails.size();
    }
};

/*
 * PROBLEM 6: LONGEST COMMON SUBSEQUENCE (LCS)
 * Find length of longest common subsequence between two strings
 */
class LongestCommonSubsequence {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.length(), n = text2.length();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (text1[i-1] == text2[j-1]) {
                    dp[i][j] = dp[i-1][j-1] + 1;
                } else {
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }
        return dp[m][n];
    }
    
    // Space optimized version
    int longestCommonSubsequenceOptimized(string text1, string text2) {
        int m = text1.length(), n = text2.length();
        vector<int> prev(n + 1, 0), curr(n + 1, 0);
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (text1[i-1] == text2[j-1]) {
                    curr[j] = prev[j-1] + 1;
                } else {
                    curr[j] = max(prev[j], curr[j-1]);
                }
            }
            prev = curr;
        }
        return prev[n];
    }
};

/*
 * PROBLEM 7: 0/1 KNAPSACK
 * Maximum value with weight constraint
 */
class Knapsack {
public:
    int knapsack(vector<int>& weights, vector<int>& values, int capacity) {
        int n = weights.size();
        vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));
        
        for (int i = 1; i <= n; i++) {
            for (int w = 1; w <= capacity; w++) {
                if (weights[i-1] <= w) {
                    dp[i][w] = max(values[i-1] + dp[i-1][w - weights[i-1]], 
                                   dp[i-1][w]);
                } else {
                    dp[i][w] = dp[i-1][w];
                }
            }
        }
        return dp[n][capacity];
    }
    
    // Space optimized version
    int knapsackOptimized(vector<int>& weights, vector<int>& values, int capacity) {
        vector<int> dp(capacity + 1, 0);
        
        for (int i = 0; i < weights.size(); i++) {
            for (int w = capacity; w >= weights[i]; w--) {
                dp[w] = max(dp[w], dp[w - weights[i]] + values[i]);
            }
        }
        return dp[capacity];
    }
};

// ===============================================================
// ADVANCED DP PROBLEMS
// ===============================================================

/*
 * PROBLEM 8: EDIT DISTANCE (LEVENSHTEIN DISTANCE)
 * Minimum operations to convert one string to another
 */
class EditDistance {
public:
    int minDistance(string word1, string word2) {
        int m = word1.length(), n = word2.length();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        
        // Initialize base cases
        for (int i = 0; i <= m; i++) dp[i][0] = i;
        for (int j = 0; j <= n; j++) dp[0][j] = j;
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (word1[i-1] == word2[j-1]) {
                    dp[i][j] = dp[i-1][j-1];
                } else {
                    dp[i][j] = 1 + min({dp[i-1][j],    // delete
                                        dp[i][j-1],    // insert
                                        dp[i-1][j-1]}); // replace
                }
            }
        }
        return dp[m][n];
    }
};

/*
 * PROBLEM 9: MAXIMUM SUBARRAY (KADANE'S ALGORITHM)
 * Find maximum sum of contiguous subarray
 */
class MaximumSubarray {
public:
    int maxSubArray(vector<int>& nums) {
        int maxSoFar = nums[0];
        int maxEndingHere = nums[0];
        
        for (int i = 1; i < nums.size(); i++) {
            maxEndingHere = max(nums[i], maxEndingHere + nums[i]);
            maxSoFar = max(maxSoFar, maxEndingHere);
        }
        return maxSoFar;
    }
    
    // DP version for clarity
    int maxSubArrayDP(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n);
        dp[0] = nums[0];
        int maxSum = dp[0];
        
        for (int i = 1; i < n; i++) {
            dp[i] = max(nums[i], dp[i-1] + nums[i]);
            maxSum = max(maxSum, dp[i]);
        }
        return maxSum;
    }
};

/*
 * PROBLEM 10: PALINDROMIC SUBSEQUENCES
 * Count/find palindromic subsequences
 */
class PalindromicSubsequences {
public:
    // Longest palindromic subsequence
    int longestPalindromeSubseq(string s) {
        int n = s.length();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        
        // Every single character is a palindrome
        for (int i = 0; i < n; i++) {
            dp[i][i] = 1;
        }
        
        // Fill for substrings of length 2 to n
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;
                if (s[i] == s[j]) {
                    dp[i][j] = dp[i+1][j-1] + 2;
                } else {
                    dp[i][j] = max(dp[i+1][j], dp[i][j-1]);
                }
            }
        }
        return dp[0][n-1];
    }
    
    // Count distinct palindromic subsequences
    int countPalindromicSubsequences(string s) {
        int n = s.length();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        
        for (int i = 0; i < n; i++) {
            dp[i][i] = 1;
        }
        
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;
                if (s[i] == s[j]) {
                    dp[i][j] = dp[i+1][j-1] * 2;
                    // Handle duplicates
                    int left = i + 1, right = j - 1;
                    while (left <= right && s[left] != s[i]) left++;
                    while (left <= right && s[right] != s[i]) right--;
                    
                    if (left > right) {
                        dp[i][j] += 2;
                    } else if (left == right) {
                        dp[i][j] += 1;
                    } else {
                        dp[i][j] -= dp[left+1][right-1];
                    }
                } else {
                    dp[i][j] = dp[i+1][j] + dp[i][j-1] - dp[i+1][j-1];
                }
            }
        }
        return dp[0][n-1];
    }
};

/*
 * PROBLEM 11: MATRIX CHAIN MULTIPLICATION
 * Find minimum multiplications needed
 */
class MatrixChainMultiplication {
public:
    int matrixChainOrder(vector<int>& p) {
        int n = p.size() - 1; // number of matrices
        vector<vector<int>> dp(n, vector<int>(n, 0));
        
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;
                dp[i][j] = INT_MAX;
                for (int k = i; k < j; k++) {
                    int cost = dp[i][k] + dp[k+1][j] + p[i] * p[k+1] * p[j+1];
                    dp[i][j] = min(dp[i][j], cost);
                }
            }
        }
        return dp[0][n-1];
    }
};

/*
 * PROBLEM 12: WORD BREAK
 * Check if string can be segmented into dictionary words
 */
class WordBreak {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        int n = s.length();
        vector<bool> dp(n + 1, false);
        dp[0] = true;
        
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                if (dp[j] && dict.count(s.substr(j, i - j))) {
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp[n];
    }
    
    // Count number of ways to break
    int wordBreakWays(string s, vector<string>& wordDict) {
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        int n = s.length();
        vector<int> dp(n + 1, 0);
        dp[0] = 1;
        
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                if (dp[j] && dict.count(s.substr(j, i - j))) {
                    dp[i] += dp[j];
                }
            }
        }
        return dp[n];
    }
};

// ===============================================================
// EXPERT LEVEL DP PROBLEMS
// ===============================================================

/*
 * PROBLEM 13: MAXIMUM RECTANGLE IN BINARY MATRIX
 * Find largest rectangle area in binary matrix
 */
class MaximalRectangle {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        if (matrix.empty()) return 0;
        
        int rows = matrix.size(), cols = matrix[0].size();
        vector<int> heights(cols, 0);
        int maxArea = 0;
        
        for (int i = 0; i < rows; i++) {
            // Update heights for current row
            for (int j = 0; j < cols; j++) {
                heights[j] = (matrix[i][j] == '1') ? heights[j] + 1 : 0;
            }
            // Find max rectangle in histogram
            maxArea = max(maxArea, largestRectangleArea(heights));
        }
        return maxArea;
    }
    
private:
    int largestRectangleArea(vector<int>& heights) {
        stack<int> st;
        int maxArea = 0;
        heights.push_back(0); // sentinel
        
        for (int i = 0; i < heights.size(); i++) {
            while (!st.empty() && heights[i] < heights[st.top()]) {
                int h = heights[st.top()];
                st.pop();
                int w = st.empty() ? i : i - st.top() - 1;
                maxArea = max(maxArea, h * w);
            }
            st.push(i);
        }
        heights.pop_back(); // remove sentinel
        return maxArea;
    }
};

/*
 * PROBLEM 14: BURST BALLOONS
 * Maximize coins by bursting balloons optimally
 */
class BurstBalloons {
public:
    int maxCoins(vector<int>& nums) {
        // Add boundary balloons
        nums.insert(nums.begin(), 1);
        nums.push_back(1);
        int n = nums.size();
        
        // dp[i][j] = max coins from bursting balloons between i and j
        vector<vector<int>> dp(n, vector<int>(n, 0));
        
        for (int len = 3; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;
                for (int k = i + 1; k < j; k++) {
                    dp[i][j] = max(dp[i][j], 
                                   dp[i][k] + dp[k][j] + nums[i] * nums[k] * nums[j]);
                }
            }
        }
        return dp[0][n-1];
    }
};

/*
 * PROBLEM 15: REGULAR EXPRESSION MATCHING
 * Implement regex matching with '.' and '*'
 */
class RegexMatching {
public:
    bool isMatch(string s, string p) {
        int m = s.length(), n = p.length();
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
        
        dp[0][0] = true;
        
        // Handle patterns like a*, a*b*, a*b*c*
        for (int j = 2; j <= n; j += 2) {
            if (p[j-1] == '*') {
                dp[0][j] = dp[0][j-2];
            }
        }
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (p[j-1] == '*') {
                    // Two choices: use * (match 0 times) or don't use it
                    dp[i][j] = dp[i][j-2];
                    if (matches(s, p, i, j-1)) {
                        dp[i][j] = dp[i][j] || dp[i-1][j];
                    }
                } else if (matches(s, p, i, j)) {
                    dp[i][j] = dp[i-1][j-1];
                }
            }
        }
        return dp[m][n];
    }
    
private:
    bool matches(string& s, string& p, int i, int j) {
        return p[j-1] == '.' || s[i-1] == p[j-1];
    }
};

// ===============================================================
// TESTING AND DEMONSTRATION
// ===============================================================

void demonstrateDP() {
    cout << "=== DYNAMIC PROGRAMMING PROBLEMS DEMONSTRATION ===\n\n";
    
    // Test Fibonacci
    FibonacciSolutions fib;
    cout << "Fibonacci(10): " << fib.fibOptimized(10) << "\n";
    
    // Test Climbing Stairs
    ClimbingStairs stairs;
    cout << "Ways to climb 5 stairs: " << stairs.climbStairs(5) << "\n";
    
    // Test Coin Change
    CoinChange coinChange;
    vector<int> coins = {1, 3, 4};
    cout << "Min coins for amount 6: " << coinChange.coinChange(coins, 6) << "\n";
    
    // Test LIS
    LongestIncreasingSubsequence lis;
    vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};
    cout << "Length of LIS: " << lis.lengthOfLIS(nums) << "\n";
    
    // Test LCS
    LongestCommonSubsequence lcs;
    cout << "LCS length: " << lcs.longestCommonSubsequence("abcde", "ace") << "\n";
    
    // Test Edit Distance
    EditDistance editDist;
    cout << "Edit distance: " << editDist.minDistance("horse", "ros") << "\n";
    
    // Test Maximum Subarray
    MaximumSubarray maxSub;
    vector<int> arr = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    cout << "Maximum subarray sum: " << maxSub.maxSubArray(arr) << "\n";
    
    cout << "\n=== All DP problems implemented successfully! ===\n";
}

int main() {
    demonstrateDP();
    return 0;
}

/*
 * ===============================================================
 * STUDY GUIDE AND PRACTICE TIPS
 * ===============================================================
 * 
 * 1. PROBLEM SOLVING APPROACH:
 *    - Identify if problem has optimal substructure
 *    - Check for overlapping subproblems
 *    - Define state and recurrence relation
 *    - Start with recursive solution, then optimize
 * 
 * 2. COMMON DP PATTERNS:
 *    - Linear DP: fibonacci, climbing stairs
 *    - Grid DP: unique paths, minimum path sum
 *    - Interval DP: matrix chain multiplication, palindromes
 *    - Tree DP: maximum path sum, diameter
 *    - Bitmask DP: traveling salesman, subset problems
 * 
 * 3. OPTIMIZATION TECHNIQUES:
 *    - Space optimization using rolling arrays
 *    - Memoization vs tabulation trade-offs
 *    - Bottom-up vs top-down approaches
 * 
 * 4. PRACTICE PROGRESSION:
 *    - Master basic problems first (fibonacci, stairs)
 *    - Move to string/array problems (LCS, LIS)
 *    - Tackle interval and matrix problems
 *    - Solve advanced combinatorial problems
 * 
 * 5. INTERVIEW TIPS:
 *    - Always start with brute force solution
 *    - Identify repeated subproblems
 *    - Draw state transition diagram
 *    - Optimize space complexity when possible
 *    - Practice explaining your thought process
 */
