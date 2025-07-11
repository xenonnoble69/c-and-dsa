/*
 * ============================================================================
 * DYNAMIC PROGRAMMING - COMPREHENSIVE GUIDE
 * ============================================================================
 * 
 * Dynamic Programming (DP) is an algorithmic paradigm that solves complex
 * problems by breaking them down into simpler subproblems and storing the
 * results to avoid redundant calculations.
 * 
 * Key Principles:
 * 1. Optimal Substructure: Optimal solution contains optimal solutions to subproblems
 * 2. Overlapping Subproblems: Same subproblems are solved multiple times
 * 3. Memoization: Store results to avoid recomputation
 * 4. Bottom-up approach: Build solutions from smallest to largest subproblems
 * 
 * Applications:
 * - Optimization problems (shortest path, knapsack)
 * - Counting problems (number of ways)
 * - Decision problems (can we achieve something)
 * - Sequence problems (longest subsequence, edit distance)
 * 
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <unordered_map>
#include <map>

using namespace std;

/*
 * ========================================================================
 * CLASSIC DP PROBLEMS - FIBONACCI SEQUENCE
 * ========================================================================
 */

class FibonacciDP {
public:
    // Naive recursive approach (exponential time)
    long long fibonacciNaive(int n) {
        /*
         * Time: O(2^n), Space: O(n) for recursion stack
         * Demonstrates why DP is needed
         */
        if (n <= 1) return n;
        return fibonacciNaive(n - 1) + fibonacciNaive(n - 2);
    }
    
    // Memoization (top-down DP)
    long long fibonacciMemo(int n) {
        /*
         * Time: O(n), Space: O(n)
         * Store computed values to avoid recomputation
         */
        unordered_map<int, long long> memo;
        return fibonacciMemoHelper(n, memo);
    }
    
    // Tabulation (bottom-up DP)
    long long fibonacciTabulation(int n) {
        /*
         * Time: O(n), Space: O(n)
         * Build solution from bottom up
         */
        if (n <= 1) return n;
        
        vector<long long> dp(n + 1);
        dp[0] = 0;
        dp[1] = 1;
        
        for (int i = 2; i <= n; ++i) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        
        return dp[n];
    }
    
    // Space-optimized DP
    long long fibonacciOptimized(int n) {
        /*
         * Time: O(n), Space: O(1)
         * Only keep track of last two values
         */
        if (n <= 1) return n;
        
        long long prev2 = 0, prev1 = 1;
        
        for (int i = 2; i <= n; ++i) {
            long long current = prev1 + prev2;
            prev2 = prev1;
            prev1 = current;
        }
        
        return prev1;
    }

private:
    long long fibonacciMemoHelper(int n, unordered_map<int, long long>& memo) {
        if (n <= 1) return n;
        
        if (memo.find(n) != memo.end()) {
            return memo[n];
        }
        
        memo[n] = fibonacciMemoHelper(n - 1, memo) + fibonacciMemoHelper(n - 2, memo);
        return memo[n];
    }
};

/*
 * ========================================================================
 * CLIMBING STAIRS PROBLEM
 * ========================================================================
 */

class ClimbingStairs {
public:
    // Basic climbing stairs (1 or 2 steps at a time)
    int climbStairs(int n) {
        /*
         * Number of ways to reach top
         * Time: O(n), Space: O(1)
         */
        if (n <= 2) return n;
        
        int prev2 = 1, prev1 = 2;
        
        for (int i = 3; i <= n; ++i) {
            int current = prev1 + prev2;
            prev2 = prev1;
            prev1 = current;
        }
        
        return prev1;
    }
    
    // Climbing stairs with variable steps
    int climbStairsVariableSteps(int n, const vector<int>& steps) {
        /*
         * Can take steps from the given array
         * Time: O(n * k), Space: O(n)
         */
        vector<int> dp(n + 1, 0);
        dp[0] = 1;
        
        for (int i = 1; i <= n; ++i) {
            for (int step : steps) {
                if (i >= step) {
                    dp[i] += dp[i - step];
                }
            }
        }
        
        return dp[n];
    }
    
    // Climbing stairs with cost
    int minCostClimbingStairs(const vector<int>& cost) {
        /*
         * Minimum cost to reach top
         * Time: O(n), Space: O(1)
         */
        int n = cost.size();
        int prev2 = 0, prev1 = 0;
        
        for (int i = 0; i < n; ++i) {
            int current = cost[i] + min(prev1, prev2);
            prev2 = prev1;
            prev1 = current;
        }
        
        return min(prev1, prev2);
    }
};

/*
 * ========================================================================
 * COIN CHANGE PROBLEMS
 * ========================================================================
 */

class CoinChange {
public:
    // Minimum coins to make amount
    int coinChange(const vector<int>& coins, int amount) {
        /*
         * Find minimum number of coins to make amount
         * Time: O(amount * coins.size()), Space: O(amount)
         */
        vector<int> dp(amount + 1, INT_MAX);
        dp[0] = 0;
        
        for (int i = 1; i <= amount; ++i) {
            for (int coin : coins) {
                if (i >= coin && dp[i - coin] != INT_MAX) {
                    dp[i] = min(dp[i], dp[i - coin] + 1);
                }
            }
        }
        
        return dp[amount] == INT_MAX ? -1 : dp[amount];
    }
    
    // Number of ways to make amount
    int coinChangeWays(const vector<int>& coins, int amount) {
        /*
         * Count number of ways to make amount
         * Time: O(amount * coins.size()), Space: O(amount)
         */
        vector<int> dp(amount + 1, 0);
        dp[0] = 1;
        
        for (int coin : coins) {
            for (int i = coin; i <= amount; ++i) {
                dp[i] += dp[i - coin];
            }
        }
        
        return dp[amount];
    }
    
    // Coin change with limited coins
    int coinChangeLimited(const vector<int>& coins, const vector<int>& counts, int amount) {
        /*
         * Each coin type has limited quantity
         * Time: O(amount * sum(counts)), Space: O(amount)
         */
        vector<int> dp(amount + 1, INT_MAX);
        dp[0] = 0;
        
        for (int i = 0; i < coins.size(); ++i) {
            int coin = coins[i];
            int count = counts[i];
            
            for (int j = amount; j >= coin; --j) {
                for (int k = 1; k <= count && j >= k * coin; ++k) {
                    if (dp[j - k * coin] != INT_MAX) {
                        dp[j] = min(dp[j], dp[j - k * coin] + k);
                    }
                }
            }
        }
        
        return dp[amount] == INT_MAX ? -1 : dp[amount];
    }
};

/*
 * ========================================================================
 * KNAPSACK PROBLEMS
 * ========================================================================
 */

class Knapsack {
public:
    // 0/1 Knapsack (each item can be taken at most once)
    int knapsack01(const vector<int>& weights, const vector<int>& values, int capacity) {
        /*
         * Maximum value with given weight capacity
         * Time: O(n * capacity), Space: O(n * capacity)
         */
        int n = weights.size();
        vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));
        
        for (int i = 1; i <= n; ++i) {
            for (int w = 1; w <= capacity; ++w) {
                // Don't take item i-1
                dp[i][w] = dp[i - 1][w];
                
                // Take item i-1 if possible
                if (weights[i - 1] <= w) {
                    dp[i][w] = max(dp[i][w], dp[i - 1][w - weights[i - 1]] + values[i - 1]);
                }
            }
        }
        
        return dp[n][capacity];
    }
    
    // Space-optimized 0/1 Knapsack
    int knapsack01Optimized(const vector<int>& weights, const vector<int>& values, int capacity) {
        /*
         * Time: O(n * capacity), Space: O(capacity)
         */
        vector<int> dp(capacity + 1, 0);
        
        for (int i = 0; i < weights.size(); ++i) {
            for (int w = capacity; w >= weights[i]; --w) {
                dp[w] = max(dp[w], dp[w - weights[i]] + values[i]);
            }
        }
        
        return dp[capacity];
    }
    
    // Unbounded Knapsack (unlimited items)
    int knapsackUnbounded(const vector<int>& weights, const vector<int>& values, int capacity) {
        /*
         * Each item can be taken unlimited times
         * Time: O(n * capacity), Space: O(capacity)
         */
        vector<int> dp(capacity + 1, 0);
        
        for (int w = 1; w <= capacity; ++w) {
            for (int i = 0; i < weights.size(); ++i) {
                if (weights[i] <= w) {
                    dp[w] = max(dp[w], dp[w - weights[i]] + values[i]);
                }
            }
        }
        
        return dp[capacity];
    }
    
    // Get items selected in knapsack
    vector<int> knapsackItems(const vector<int>& weights, const vector<int>& values, int capacity) {
        /*
         * Return indices of selected items
         */
        int n = weights.size();
        vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));
        
        // Fill DP table
        for (int i = 1; i <= n; ++i) {
            for (int w = 1; w <= capacity; ++w) {
                dp[i][w] = dp[i - 1][w];
                if (weights[i - 1] <= w) {
                    dp[i][w] = max(dp[i][w], dp[i - 1][w - weights[i - 1]] + values[i - 1]);
                }
            }
        }
        
        // Backtrack to find items
        vector<int> items;
        int w = capacity;
        for (int i = n; i > 0 && w > 0; --i) {
            if (dp[i][w] != dp[i - 1][w]) {
                items.push_back(i - 1);
                w -= weights[i - 1];
            }
        }
        
        reverse(items.begin(), items.end());
        return items;
    }
};

/*
 * ========================================================================
 * LONGEST COMMON SUBSEQUENCE (LCS)
 * ========================================================================
 */

class LongestCommonSubsequence {
public:
    // Length of LCS
    int lcsLength(const string& text1, const string& text2) {
        /*
         * Find length of longest common subsequence
         * Time: O(m * n), Space: O(m * n)
         */
        int m = text1.length(), n = text2.length();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (text1[i - 1] == text2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        
        return dp[m][n];
    }
    
    // Get actual LCS string
    string lcsString(const string& text1, const string& text2) {
        /*
         * Return the actual LCS string
         */
        int m = text1.length(), n = text2.length();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        
        // Fill DP table
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (text1[i - 1] == text2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        
        // Backtrack to construct LCS
        string lcs = "";
        int i = m, j = n;
        
        while (i > 0 && j > 0) {
            if (text1[i - 1] == text2[j - 1]) {
                lcs = text1[i - 1] + lcs;
                i--;
                j--;
            } else if (dp[i - 1][j] > dp[i][j - 1]) {
                i--;
            } else {
                j--;
            }
        }
        
        return lcs;
    }
    
    // Space-optimized LCS
    int lcsLengthOptimized(const string& text1, const string& text2) {
        /*
         * Time: O(m * n), Space: O(min(m, n))
         */
        if (text1.length() < text2.length()) {
            return lcsLengthOptimized(text2, text1);
        }
        
        int m = text1.length(), n = text2.length();
        vector<int> prev(n + 1, 0), curr(n + 1, 0);
        
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (text1[i - 1] == text2[j - 1]) {
                    curr[j] = prev[j - 1] + 1;
                } else {
                    curr[j] = max(prev[j], curr[j - 1]);
                }
            }
            prev = curr;
        }
        
        return curr[n];
    }
};

/*
 * ========================================================================
 * EDIT DISTANCE (LEVENSHTEIN DISTANCE)
 * ========================================================================
 */

class EditDistance {
public:
    // Minimum edit distance
    int minDistance(const string& word1, const string& word2) {
        /*
         * Minimum operations (insert, delete, replace) to transform word1 to word2
         * Time: O(m * n), Space: O(m * n)
         */
        int m = word1.length(), n = word2.length();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        
        // Base cases
        for (int i = 0; i <= m; ++i) dp[i][0] = i;
        for (int j = 0; j <= n; ++j) dp[0][j] = j;
        
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = 1 + min({
                        dp[i - 1][j],     // Delete
                        dp[i][j - 1],     // Insert
                        dp[i - 1][j - 1]  // Replace
                    });
                }
            }
        }
        
        return dp[m][n];
    }
    
    // Get sequence of operations
    vector<string> getEditOperations(const string& word1, const string& word2) {
        /*
         * Return sequence of operations to transform word1 to word2
         */
        int m = word1.length(), n = word2.length();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        
        // Fill DP table
        for (int i = 0; i <= m; ++i) dp[i][0] = i;
        for (int j = 0; j <= n; ++j) dp[0][j] = j;
        
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
                }
            }
        }
        
        // Backtrack to get operations
        vector<string> operations;
        int i = m, j = n;
        
        while (i > 0 || j > 0) {
            if (i > 0 && j > 0 && word1[i - 1] == word2[j - 1]) {
                i--;
                j--;
            } else if (i > 0 && j > 0 && dp[i][j] == dp[i - 1][j - 1] + 1) {
                operations.push_back("Replace " + string(1, word1[i - 1]) + " with " + string(1, word2[j - 1]));
                i--;
                j--;
            } else if (i > 0 && dp[i][j] == dp[i - 1][j] + 1) {
                operations.push_back("Delete " + string(1, word1[i - 1]));
                i--;
            } else if (j > 0) {
                operations.push_back("Insert " + string(1, word2[j - 1]));
                j--;
            }
        }
        
        reverse(operations.begin(), operations.end());
        return operations;
    }
    
    // Space-optimized edit distance
    int minDistanceOptimized(const string& word1, const string& word2) {
        /*
         * Time: O(m * n), Space: O(min(m, n))
         */
        if (word1.length() < word2.length()) {
            return minDistanceOptimized(word2, word1);
        }
        
        int m = word1.length(), n = word2.length();
        vector<int> prev(n + 1), curr(n + 1);
        
        for (int j = 0; j <= n; ++j) prev[j] = j;
        
        for (int i = 1; i <= m; ++i) {
            curr[0] = i;
            for (int j = 1; j <= n; ++j) {
                if (word1[i - 1] == word2[j - 1]) {
                    curr[j] = prev[j - 1];
                } else {
                    curr[j] = 1 + min({prev[j], curr[j - 1], prev[j - 1]});
                }
            }
            prev = curr;
        }
        
        return curr[n];
    }
};

/*
 * ========================================================================
 * DEMONSTRATION AND TESTING
 * ========================================================================
 */

void demonstrateFibonacci() {
    cout << "=== FIBONACCI SEQUENCE ===" << endl;
    
    FibonacciDP fib;
    int n = 10;
    
    cout << "Computing Fibonacci(" << n << "):" << endl;
    cout << "Naive (slow): " << fib.fibonacciNaive(n) << endl;
    cout << "Memoization: " << fib.fibonacciMemo(n) << endl;
    cout << "Tabulation: " << fib.fibonacciTabulation(n) << endl;
    cout << "Optimized: " << fib.fibonacciOptimized(n) << endl;
    
    // Show first 15 fibonacci numbers
    cout << "\nFirst 15 Fibonacci numbers: ";
    for (int i = 0; i < 15; ++i) {
        cout << fib.fibonacciOptimized(i) << " ";
    }
    cout << endl;
}

void demonstrateClimbingStairs() {
    cout << "\n=== CLIMBING STAIRS ===" << endl;
    
    ClimbingStairs stairs;
    
    int n = 5;
    cout << "Ways to climb " << n << " stairs (1-2 steps): " << stairs.climbStairs(n) << endl;
    
    vector<int> steps = {1, 3, 5};
    cout << "Ways to climb " << n << " stairs with steps {1,3,5}: " 
         << stairs.climbStairsVariableSteps(n, steps) << endl;
    
    vector<int> cost = {10, 15, 20};
    cout << "Min cost to climb stairs with cost {10,15,20}: " 
         << stairs.minCostClimbingStairs(cost) << endl;
}

void demonstrateCoinChange() {
    cout << "\n=== COIN CHANGE ===" << endl;
    
    CoinChange coins;
    vector<int> coinTypes = {1, 3, 4};
    int amount = 6;
    
    cout << "Coins: {1,3,4}, Amount: " << amount << endl;
    cout << "Min coins needed: " << coins.coinChange(coinTypes, amount) << endl;
    cout << "Number of ways: " << coins.coinChangeWays(coinTypes, amount) << endl;
}

void demonstrateKnapsack() {
    cout << "\n=== KNAPSACK PROBLEM ===" << endl;
    
    Knapsack ks;
    vector<int> weights = {2, 1, 3, 2};
    vector<int> values = {12, 10, 20, 15};
    int capacity = 5;
    
    cout << "Items: ";
    for (int i = 0; i < weights.size(); ++i) {
        cout << "(w:" << weights[i] << ",v:" << values[i] << ") ";
    }
    cout << "\nCapacity: " << capacity << endl;
    
    cout << "Max value (0/1): " << ks.knapsack01(weights, values, capacity) << endl;
    cout << "Max value (unbounded): " << ks.knapsackUnbounded(weights, values, capacity) << endl;
    
    auto items = ks.knapsackItems(weights, values, capacity);
    cout << "Selected items (0/1): ";
    for (int item : items) {
        cout << item << " ";
    }
    cout << endl;
}

void demonstrateLCS() {
    cout << "\n=== LONGEST COMMON SUBSEQUENCE ===" << endl;
    
    LongestCommonSubsequence lcs;
    string text1 = "abcde";
    string text2 = "ace";
    
    cout << "Text 1: " << text1 << endl;
    cout << "Text 2: " << text2 << endl;
    cout << "LCS length: " << lcs.lcsLength(text1, text2) << endl;
    cout << "LCS string: \"" << lcs.lcsString(text1, text2) << "\"" << endl;
}

void demonstrateEditDistance() {
    cout << "\n=== EDIT DISTANCE ===" << endl;
    
    EditDistance ed;
    string word1 = "horse";
    string word2 = "ros";
    
    cout << "Word 1: " << word1 << endl;
    cout << "Word 2: " << word2 << endl;
    cout << "Edit distance: " << ed.minDistance(word1, word2) << endl;
    
    auto operations = ed.getEditOperations(word1, word2);
    cout << "Operations:" << endl;
    for (const string& op : operations) {
        cout << "  " << op << endl;
    }
}

/*
 * ========================================================================
 * MAIN FUNCTION
 * ========================================================================
 */

int main() {
    cout << "=== DYNAMIC PROGRAMMING COMPREHENSIVE GUIDE ===" << endl;
    
    demonstrateFibonacci();
    demonstrateClimbingStairs();
    demonstrateCoinChange();
    demonstrateKnapsack();
    demonstrateLCS();
    demonstrateEditDistance();
    
    cout << "\n=== All DP Concepts Demonstrated! ===" << endl;
    
    return 0;
}

/*
 * ============================================================================
 * DYNAMIC PROGRAMMING COMPLEXITY ANALYSIS:
 * ============================================================================
 * 
 * FIBONACCI SEQUENCE:
 * - Naive: O(2^n) time, O(n) space
 * - Memoization: O(n) time, O(n) space
 * - Tabulation: O(n) time, O(n) space
 * - Optimized: O(n) time, O(1) space
 * 
 * CLIMBING STAIRS:
 * - Basic: O(n) time, O(1) space
 * - Variable steps: O(n * k) time, O(n) space
 * - With cost: O(n) time, O(1) space
 * 
 * COIN CHANGE:
 * - Min coins: O(amount * coins) time, O(amount) space
 * - Count ways: O(amount * coins) time, O(amount) space
 * - Limited coins: O(amount * sum(counts)) time, O(amount) space
 * 
 * KNAPSACK:
 * - 0/1 Knapsack: O(n * capacity) time, O(n * capacity) space
 * - Optimized: O(n * capacity) time, O(capacity) space
 * - Unbounded: O(n * capacity) time, O(capacity) space
 * 
 * LONGEST COMMON SUBSEQUENCE:
 * - Basic: O(m * n) time, O(m * n) space
 * - Optimized: O(m * n) time, O(min(m, n)) space
 * 
 * EDIT DISTANCE:
 * - Basic: O(m * n) time, O(m * n) space
 * - Optimized: O(m * n) time, O(min(m, n)) space
 * 
 * DP PROBLEM PATTERNS:
 * 1. Linear DP: f(n) depends on f(n-1), f(n-2), etc.
 * 2. Grid DP: 2D problems, paths in matrix
 * 3. Interval DP: Problems on subsequences/subarrays
 * 4. Tree DP: Problems on tree structures
 * 5. Bitmask DP: Problems with state representation
 * 6. Digit DP: Problems involving digits of numbers
 * 
 * OPTIMIZATION TECHNIQUES:
 * - Space optimization: Use 1D array instead of 2D
 * - Rolling arrays: Keep only necessary previous states
 * - Coordinate compression: Reduce large ranges
 * - State compression: Use bitmasks for states
 * 
 * ============================================================================
 */
