# Arrays & Strings Module

Welcome to the **Arrays & Strings** module of Phase 2: Data Structures & Algorithms! This module provides comprehensive coverage of array and string manipulation techniques essential for technical interviews and competitive programming.

## 📚 Module Contents

### Core Learning Files
- **`array_fundamentals.cpp`** - Complete coverage of array concepts, algorithms, and techniques
- **`string_algorithms.cpp`** - Comprehensive string manipulation and algorithms

### Practice Problems
- **`problems/array_problems.cpp`** - 15 essential array problems (Easy to Hard)
- **`problems/string_problems.cpp`** - 20 essential string problems (Easy to Hard)
- **`problems/mixed_problems.cpp`** - 15 advanced problems combining arrays and strings

## 🎯 Learning Objectives

By the end of this module, you will master:

### Array Techniques
- Array traversal and manipulation
- Two-pointer technique
- Sliding window algorithm
- Binary search on arrays
- Sorting algorithms and applications
- Prefix sums and range queries
- Dynamic arrays and resizing

### String Techniques
- String searching algorithms (KMP, Rabin-Karp, Boyer-Moore)
- Pattern matching and regular expressions
- String parsing and tokenization
- Anagram and palindrome problems
- Sliding window on strings
- Trie-based string operations

### Advanced Patterns
- Combining array and string techniques
- Multi-dimensional problems
- Dynamic programming on sequences
- Backtracking with constraints
- BFS/DFS with string transformations

## 🗺️ Study Path

### Phase 1: Foundation (Week 1)
1. **Start with `array_fundamentals.cpp`**
   - Understand basic array operations
   - Master two-pointer technique
   - Learn sliding window patterns
   - Practice sorting algorithms

2. **Move to `string_algorithms.cpp`**
   - Learn string manipulation basics
   - Understand string searching algorithms
   - Master pattern matching techniques
   - Practice string parsing

### Phase 2: Problem Solving (Week 2-3)
3. **Practice `problems/array_problems.cpp`**
   - Start with easy problems (⭐)
   - Progress to medium problems (⭐⭐)
   - Challenge yourself with hard problems (⭐⭐⭐)

4. **Practice `problems/string_problems.cpp`**
   - Follow the same progression
   - Focus on algorithmic patterns
   - Time yourself on each problem

### Phase 3: Advanced Integration (Week 4)
5. **Master `problems/mixed_problems.cpp`**
   - Apply combined techniques
   - Solve complex scenarios
   - Prepare for advanced interviews

## 🔥 Key Algorithms to Master

### Array Algorithms
```cpp
// Two Pointers
while (left < right) {
    // Process logic
    if (condition) left++;
    else right--;
}

// Sliding Window
for (int right = 0; right < n; right++) {
    // Expand window
    while (window_invalid) {
        // Shrink window
        left++;
    }
    // Update result
}

// Binary Search
while (left <= right) {
    int mid = left + (right - left) / 2;
    if (nums[mid] == target) return mid;
    else if (nums[mid] < target) left = mid + 1;
    else right = mid - 1;
}
```

### String Algorithms
```cpp
// KMP Pattern Matching
vector<int> computeLPS(string pattern) {
    // Compute longest proper prefix-suffix array
}

// Rolling Hash
hash = (hash * base + char) % mod;

// Palindrome Check
bool isPalindrome(string s, int left, int right) {
    while (left < right) {
        if (s[left] != s[right]) return false;
        left++; right--;
    }
    return true;
}
```

## 📊 Problem Difficulty Distribution

### Array Problems (15 total)
- **Easy (⭐)**: 5 problems - Foundation building
- **Medium (⭐⭐)**: 7 problems - Interview level
- **Hard (⭐⭐⭐)**: 3 problems - Advanced challenges

### String Problems (20 total)
- **Easy (⭐)**: 6 problems - String basics
- **Medium (⭐⭐)**: 10 problems - Pattern matching
- **Hard (⭐⭐⭐)**: 4 problems - Complex algorithms

### Mixed Problems (15 total)
- **Medium (⭐⭐)**: 8 problems - Integration practice
- **Hard (⭐⭐⭐)**: 7 problems - Advanced integration

## 🎮 Practice Strategy

### Daily Schedule (4 weeks)
**Week 1: Fundamentals**
- Day 1-2: Array fundamentals + basic operations
- Day 3-4: String algorithms + pattern matching
- Day 5-7: Review and practice basics

**Week 2: Core Problems**
- Day 1-3: Array problems (easy to medium)
- Day 4-6: String problems (easy to medium)
- Day 7: Review and consolidation

**Week 3: Advanced Problems**
- Day 1-3: Hard array and string problems
- Day 4-6: Mixed problems (medium level)
- Day 7: Timed practice session

**Week 4: Mastery**
- Day 1-3: Hard mixed problems
- Day 4-5: Mock interview practice
- Day 6-7: Review and move to next module

## 🧪 Testing Your Knowledge

### Quick Self-Assessment

Can you solve these in under 30 minutes each?
1. **Two Sum** - Find two numbers that add to target
2. **Longest Substring Without Repeating Characters**
3. **Maximum Subarray** (Kadane's Algorithm)
4. **Valid Palindrome**
5. **Group Anagrams**

### Advanced Assessment

Can you solve these in under 45 minutes each?
1. **Minimum Window Substring**
2. **Trapping Rain Water**
3. **Regular Expression Matching**
4. **Word Ladder**
5. **Edit Distance**

## 🏆 Success Metrics

You've mastered this module when you can:
- [ ] Solve 80% of easy problems in under 15 minutes
- [ ] Solve 70% of medium problems in under 30 minutes
- [ ] Solve 50% of hard problems in under 45 minutes
- [ ] Explain time/space complexity for all solutions
- [ ] Implement solutions from memory
- [ ] Identify optimal approaches quickly

## 🔗 Connections to Other Modules

### From Phase 1 (Prerequisites)
- **Modern C++**: STL containers and algorithms
- **OOP**: Class design for problem solutions
- **STL Mastery**: Iterators and function objects

### To Phase 2 Modules
- **Linked Lists**: Sequential data structure patterns
- **Trees & Graphs**: Advanced traversal techniques
- **Heaps**: Priority-based algorithms

## 📖 Additional Resources

### Books
- "Cracking the Coding Interview" - Arrays and Strings chapters
- "Elements of Programming Interviews" - Arrays and Strings
- "Algorithm Design Manual" - String algorithms

### Online Platforms
- **LeetCode**: Arrays and Strings tags
- **HackerRank**: Arrays and Strings domains
- **CodeForces**: String algorithms problems

### Video Resources
- MIT 6.006: String algorithms lectures
- Stanford CS106B: Recursion and strings
- YouTube: "Back to Back SWE" string algorithms

## 🚀 Next Steps

After mastering this module:

1. **Move to Linked Lists** (`../02-linked-lists/`)
2. **Practice mixed problems** combining arrays with linked lists
3. **Start dynamic programming** on sequences
4. **Prepare for system design** with data structure choices

## 💡 Pro Tips

### For Interviews
- Always clarify input constraints and edge cases
- Think out loud about your approach
- Start with brute force, then optimize
- Test your solution with examples
- Discuss time/space complexity

### For Competitive Programming
- Practice typing speed for implementations
- Memorize common algorithm templates
- Learn to quickly identify problem patterns
- Practice under time pressure
- Understand when to use which approach

---

**Remember**: Consistency beats intensity. Practice 1-2 problems daily rather than cramming. Focus on understanding patterns rather than memorizing solutions.

Good luck with your arrays and strings journey! 🎯
