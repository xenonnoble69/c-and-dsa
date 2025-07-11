# Phase 3: Advanced Algorithms - Dynamic Programming

## Overview
This phase focuses exclusively on Dynamic Programming (DP), one of the most important algorithmic paradigms for competitive programming and technical interviews. DP is essential for solving optimization problems with overlapping subproblems and optimal substructure.

## Module Structure

### 01-dynamic-programming/
- **dp_fundamentals.cpp** - Core DP concepts and basic problems
- **problems/dp_problems.cpp** - Comprehensive collection of 15+ DP problems

## Learning Path

### 1. Foundation Concepts (Week 1)
- **Optimal Substructure**: Understanding when DP applies
- **Overlapping Subproblems**: Identifying repeated computations
- **Memoization vs Tabulation**: Top-down vs bottom-up approaches
- **State Definition**: How to represent subproblems

### 2. Basic DP Problems (Week 2)
- Fibonacci sequence and variants
- Climbing stairs problems
- Simple path counting
- Basic optimization problems

### 3. Intermediate DP (Week 3-4)
- **Linear DP**: Coin change, maximum subarray
- **String DP**: Longest common subsequence, edit distance
- **Sequence DP**: Longest increasing subsequence
- **Knapsack variants**: 0/1 knapsack, unbounded knapsack

### 4. Advanced DP (Week 5-6)
- **Interval DP**: Matrix chain multiplication, palindrome partitioning
- **Tree DP**: Problems on trees and graphs
- **Digit DP**: Number-based DP problems
- **Bitmask DP**: State compression techniques

### 5. Expert Level (Week 7-8)
- **Complex state transitions**: Multi-dimensional DP
- **DP optimizations**: Space optimization, convex hull trick
- **Probability DP**: Expected value problems
- **Game theory DP**: Minimax and optimal strategies

## Problem Categories

### Beginner (5 problems)
1. Fibonacci Sequence
2. Climbing Stairs
3. Minimum Cost Climbing Stairs
4. House Robber
5. Maximum Subarray

### Intermediate (5 problems)
1. Coin Change
2. Longest Increasing Subsequence
3. Longest Common Subsequence
4. 0/1 Knapsack
5. Word Break

### Advanced (5 problems)
1. Edit Distance
2. Matrix Chain Multiplication
3. Palindromic Subsequences
4. Burst Balloons
5. Regular Expression Matching

## Key DP Patterns

### 1. Linear DP
```cpp
dp[i] = f(dp[i-1], dp[i-2], ..., dp[0])
```
- Examples: Fibonacci, climbing stairs, house robber

### 2. Grid DP
```cpp
dp[i][j] = f(dp[i-1][j], dp[i][j-1], dp[i-1][j-1])
```
- Examples: Unique paths, minimum path sum, edit distance

### 3. Interval DP
```cpp
dp[i][j] = min/max(dp[i][k] + dp[k+1][j] + cost)
```
- Examples: Matrix chain multiplication, burst balloons

### 4. Subsequence DP
```cpp
dp[i] = max(dp[j] + 1) for all j < i where condition holds
```
- Examples: LIS, LCS, palindromic subsequences

## Time Complexity Analysis

| Problem Type | Typical Complexity | Space Optimization |
|--------------|-------------------|-------------------|
| Linear DP | O(n) | O(1) possible |
| 2D Grid DP | O(mn) | O(min(m,n)) |
| Interval DP | O(n³) | Usually O(n²) |
| Tree DP | O(n) | O(height) |

## Study Tips

### 1. Problem-Solving Approach
1. **Identify the problem type**: Is it optimization? Counting? Decision?
2. **Define state clearly**: What does dp[i] represent?
3. **Find recurrence relation**: How do smaller problems relate?
4. **Handle base cases**: What are the simplest subproblems?
5. **Optimize if needed**: Can we reduce space complexity?

### 2. Common Mistakes to Avoid
- Incorrect state definition
- Missing base cases
- Wrong order of computation
- Not handling edge cases
- Inefficient space usage

### 3. Practice Strategy
- Start with recursive solution
- Add memoization (top-down DP)
- Convert to tabulation (bottom-up DP)
- Optimize space complexity
- Analyze time/space trade-offs

## Resources for Further Study

### Books
- "Dynamic Programming for Coding Interviews" by Meenakshi & Kamal Rawat
- "Introduction to Algorithms" by CLRS (Chapter 15)
- "Competitive Programming 3" by Steven & Felix Halim

### Online Resources
- LeetCode DP problems collection
- AtCoder DP contest
- Codeforces DP problems
- GeeksforGeeks DP tutorials

### Video Tutorials
- MIT 6.046J Dynamic Programming lectures
- Tushar Roy DP playlist
- Back to Back SWE DP series

## Assessment and Practice

### Daily Practice (30 minutes)
- Solve 1-2 DP problems
- Focus on understanding recurrence relations
- Practice state optimization techniques

### Weekly Goals
- Master one new DP pattern
- Solve problems of increasing difficulty
- Review and optimize previous solutions

### Interview Preparation
- Practice explaining DP intuition
- Master space optimization techniques
- Learn to identify DP problems quickly
- Practice coding under time pressure

## Next Steps
After mastering Dynamic Programming, you'll be ready for:
- Phase 4: System Design and Interview Preparation
- Advanced competitive programming contests
- Complex algorithmic problem solving
- Technical interview success

Remember: DP is not just about memorizing solutions—it's about developing the intuition to break down complex problems into simpler, manageable subproblems!
