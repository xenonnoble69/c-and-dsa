/*
 * STRING PROBLEMS - COMPREHENSIVE COLLECTION
 * =========================================
 * 
 * This file contains 25 carefully selected string problems with detailed solutions.
 * Each problem includes:
 * - Problem statement
 * - Multiple solution approaches when applicable
 * - Time and space complexity analysis
 * - Test cases and examples
 * 
 * DIFFICULTY LEVELS:
 * ⭐ Easy (1-8)
 * ⭐⭐ Medium (9-20)
 * ⭐⭐⭐ Hard (21-25)
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>

using namespace std;

// ========================================================================
// PROBLEM 1: VALID ANAGRAM ⭐
// ========================================================================
/*
 * Given two strings s and t, return true if t is an anagram of s, and false otherwise.
 * An Anagram is a word or phrase formed by rearranging the letters of a different 
 * word or phrase, typically using all the original letters exactly once.
 */

class ValidAnagram {
public:
    // Approach 1: Sorting - O(n log n) time, O(1) space
    static bool isAnagramSort(string s, string t) {
        if (s.length() != t.length()) return false;
        sort(s.begin(), s.end());
        sort(t.begin(), t.end());
        return s == t;
    }
    
    // Approach 2: Character counting - O(n) time, O(1) space
    static bool isAnagram(string s, string t) {
        if (s.length() != t.length()) return false;
        
        int count[26] = {0};
        for (int i = 0; i < s.length(); i++) {
            count[s[i] - 'a']++;
            count[t[i] - 'a']--;
        }
        
        for (int i = 0; i < 26; i++) {
            if (count[i] != 0) return false;
        }
        
        return true;
    }
};

// ========================================================================
// PROBLEM 2: VALID PALINDROME ⭐
// ========================================================================
/*
 * A phrase is a palindrome if, after converting all uppercase letters into 
 * lowercase letters and removing all non-alphanumeric characters, it reads 
 * the same forward and backward.
 */

class ValidPalindrome {
public:
    // Two pointers - O(n) time, O(1) space
    static bool isPalindrome(string s) {
        int left = 0, right = s.length() - 1;
        
        while (left < right) {
            while (left < right && !isalnum(s[left])) left++;
            while (left < right && !isalnum(s[right])) right--;
            
            if (tolower(s[left]) != tolower(s[right])) {
                return false;
            }
            
            left++;
            right--;
        }
        
        return true;
    }
};

// ========================================================================
// PROBLEM 3: LONGEST SUBSTRING WITHOUT REPEATING CHARACTERS ⭐⭐
// ========================================================================
/*
 * Given a string s, find the length of the longest substring without repeating characters.
 */

class LongestSubstringWithoutRepeating {
public:
    // Sliding window - O(n) time, O(min(m,n)) space
    static int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> charMap;
        int maxLen = 0;
        int left = 0;
        
        for (int right = 0; right < s.length(); right++) {
            if (charMap.find(s[right]) != charMap.end() && 
                charMap[s[right]] >= left) {
                left = charMap[s[right]] + 1;
            }
            charMap[s[right]] = right;
            maxLen = max(maxLen, right - left + 1);
        }
        
        return maxLen;
    }
};

// ========================================================================
// PROBLEM 4: LONGEST PALINDROMIC SUBSTRING ⭐⭐
// ========================================================================
/*
 * Given a string s, return the longest palindromic substring in s.
 */

class LongestPalindromicSubstring {
public:
    // Expand around centers - O(n²) time, O(1) space
    static string longestPalindrome(string s) {
        if (s.empty()) return "";
        
        int start = 0, maxLen = 1;
        
        for (int i = 0; i < s.length(); i++) {
            // Check for odd-length palindromes
            int len1 = expandAroundCenter(s, i, i);
            // Check for even-length palindromes
            int len2 = expandAroundCenter(s, i, i + 1);
            
            int len = max(len1, len2);
            if (len > maxLen) {
                maxLen = len;
                start = i - (len - 1) / 2;
            }
        }
        
        return s.substr(start, maxLen);
    }
    
private:
    static int expandAroundCenter(string s, int left, int right) {
        while (left >= 0 && right < s.length() && s[left] == s[right]) {
            left--;
            right++;
        }
        return right - left - 1;
    }
};

// ========================================================================
// PROBLEM 5: PALINDROMIC SUBSTRINGS ⭐⭐
// ========================================================================
/*
 * Given a string s, return the number of palindromic substrings in it.
 */

class PalindromicSubstrings {
public:
    // Expand around centers - O(n²) time, O(1) space
    static int countSubstrings(string s) {
        int count = 0;
        
        for (int i = 0; i < s.length(); i++) {
            // Count odd-length palindromes
            count += countPalindromesAroundCenter(s, i, i);
            // Count even-length palindromes
            count += countPalindromesAroundCenter(s, i, i + 1);
        }
        
        return count;
    }
    
private:
    static int countPalindromesAroundCenter(string s, int left, int right) {
        int count = 0;
        while (left >= 0 && right < s.length() && s[left] == s[right]) {
            count++;
            left--;
            right++;
        }
        return count;
    }
};

// ========================================================================
// PROBLEM 6: GROUP ANAGRAMS ⭐⭐
// ========================================================================
/*
 * Given an array of strings strs, group the anagrams together.
 */

class GroupAnagrams {
public:
    // Hash map with sorted string as key - O(n*m*log(m)) time, O(n*m) space
    static vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> anagramGroups;
        
        for (string& str : strs) {
            string key = str;
            sort(key.begin(), key.end());
            anagramGroups[key].push_back(str);
        }
        
        vector<vector<string>> result;
        for (auto& group : anagramGroups) {
            result.push_back(group.second);
        }
        
        return result;
    }
};

// ========================================================================
// PROBLEM 7: VALID PARENTHESES ⭐
// ========================================================================
/*
 * Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', 
 * determine if the input string is valid.
 */

class ValidParentheses {
public:
    // Stack - O(n) time, O(n) space
    static bool isValid(string s) {
        stack<char> st;
        unordered_map<char, char> mapping = {
            {')', '('},
            {'}', '{'},
            {']', '['}
        };
        
        for (char c : s) {
            if (mapping.find(c) != mapping.end()) {
                // Closing bracket
                if (st.empty() || st.top() != mapping[c]) {
                    return false;
                }
                st.pop();
            } else {
                // Opening bracket
                st.push(c);
            }
        }
        
        return st.empty();
    }
};

// ========================================================================
// PROBLEM 8: IMPLEMENT STRSTR ⭐
// ========================================================================
/*
 * Implement strStr(): return the index of the first occurrence of needle in haystack, 
 * or -1 if needle is not part of haystack.
 */

class ImplementStrStr {
public:
    // Brute force - O(n*m) time, O(1) space
    static int strStr(string haystack, string needle) {
        if (needle.empty()) return 0;
        
        int n = haystack.length();
        int m = needle.length();
        
        for (int i = 0; i <= n - m; i++) {
            int j = 0;
            while (j < m && haystack[i + j] == needle[j]) {
                j++;
            }
            if (j == m) return i;
        }
        
        return -1;
    }
    
    // KMP Algorithm - O(n+m) time, O(m) space
    static int strStrKMP(string haystack, string needle) {
        if (needle.empty()) return 0;
        
        int n = haystack.length();
        int m = needle.length();
        
        // Build LPS array
        vector<int> lps = computeLPS(needle);
        
        int i = 0, j = 0;
        while (i < n) {
            if (haystack[i] == needle[j]) {
                i++;
                j++;
            }
            
            if (j == m) {
                return i - j;
            } else if (i < n && haystack[i] != needle[j]) {
                if (j != 0) {
                    j = lps[j - 1];
                } else {
                    i++;
                }
            }
        }
        
        return -1;
    }
    
private:
    static vector<int> computeLPS(string pattern) {
        int m = pattern.length();
        vector<int> lps(m, 0);
        int len = 0, i = 1;
        
        while (i < m) {
            if (pattern[i] == pattern[len]) {
                len++;
                lps[i] = len;
                i++;
            } else {
                if (len != 0) {
                    len = lps[len - 1];
                } else {
                    lps[i] = 0;
                    i++;
                }
            }
        }
        
        return lps;
    }
};

// ========================================================================
// PROBLEM 9: MINIMUM WINDOW SUBSTRING ⭐⭐⭐
// ========================================================================
/*
 * Given two strings s and t, return the minimum window substring of s such that 
 * every character in t (including duplicates) is included in the window.
 */

class MinimumWindowSubstring {
public:
    // Sliding window - O(n) time, O(m) space
    static string minWindow(string s, string t) {
        if (s.length() < t.length()) return "";
        
        unordered_map<char, int> tCount, windowCount;
        for (char c : t) tCount[c]++;
        
        int left = 0, minLen = INT_MAX, minStart = 0;
        int formed = 0, required = tCount.size();
        
        for (int right = 0; right < s.length(); right++) {
            char c = s[right];
            windowCount[c]++;
            
            if (tCount.find(c) != tCount.end() && 
                windowCount[c] == tCount[c]) {
                formed++;
            }
            
            while (formed == required) {
                if (right - left + 1 < minLen) {
                    minLen = right - left + 1;
                    minStart = left;
                }
                
                char leftChar = s[left];
                windowCount[leftChar]--;
                if (tCount.find(leftChar) != tCount.end() && 
                    windowCount[leftChar] < tCount[leftChar]) {
                    formed--;
                }
                left++;
            }
        }
        
        return minLen == INT_MAX ? "" : s.substr(minStart, minLen);
    }
};

// ========================================================================
// PROBLEM 10: LONGEST REPEATING CHARACTER REPLACEMENT ⭐⭐
// ========================================================================
/*
 * You are given a string s and an integer k. You can choose any character of 
 * the string and change it to any other uppercase English character. You can 
 * perform this operation at most k times. Return the length of the longest 
 * substring containing the same letter you can get after performing the above operations.
 */

class LongestRepeatingCharacterReplacement {
public:
    // Sliding window - O(n) time, O(1) space
    static int characterReplacement(string s, int k) {
        unordered_map<char, int> count;
        int left = 0, maxCount = 0, maxLen = 0;
        
        for (int right = 0; right < s.length(); right++) {
            count[s[right]]++;
            maxCount = max(maxCount, count[s[right]]);
            
            // If current window size minus max frequency > k, shrink window
            while (right - left + 1 - maxCount > k) {
                count[s[left]]--;
                left++;
            }
            
            maxLen = max(maxLen, right - left + 1);
        }
        
        return maxLen;
    }
};

// ========================================================================
// PROBLEM 11: ENCODE AND DECODE STRINGS ⭐⭐
// ========================================================================
/*
 * Design an algorithm to encode a list of strings to a string. The encoded string 
 * is then sent over the network and is decoded back to the original list of strings.
 */

class EncodeDecodeStrings {
public:
    // Encode using length + delimiter
    static string encode(vector<string>& strs) {
        string encoded;
        for (string& str : strs) {
            encoded += to_string(str.length()) + "#" + str;
        }
        return encoded;
    }
    
    // Decode using length prefix
    static vector<string> decode(string s) {
        vector<string> result;
        int i = 0;
        
        while (i < s.length()) {
            int j = i;
            while (j < s.length() && s[j] != '#') {
                j++;
            }
            
            int length = stoi(s.substr(i, j - i));
            string str = s.substr(j + 1, length);
            result.push_back(str);
            i = j + 1 + length;
        }
        
        return result;
    }
};

// ========================================================================
// PROBLEM 12: LONGEST COMMON SUBSEQUENCE ⭐⭐
// ========================================================================
/*
 * Given two strings text1 and text2, return the length of their longest common subsequence.
 */

class LongestCommonSubsequence {
public:
    // Dynamic Programming - O(m*n) time, O(m*n) space
    static int longestCommonSubsequence(string text1, string text2) {
        int m = text1.length(), n = text2.length();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (text1[i - 1] == text2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        
        return dp[m][n];
    }
    
    // Space optimized - O(m*n) time, O(min(m,n)) space
    static int longestCommonSubsequenceOptimized(string text1, string text2) {
        if (text1.length() < text2.length()) {
            swap(text1, text2);
        }
        
        int m = text1.length(), n = text2.length();
        vector<int> prev(n + 1, 0), curr(n + 1, 0);
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
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

// ========================================================================
// PROBLEM 13: WORD BREAK ⭐⭐
// ========================================================================
/*
 * Given a string s and a dictionary of strings wordDict, return true if s can 
 * be segmented into a space-separated sequence of one or more dictionary words.
 */

class WordBreak {
public:
    // Dynamic Programming - O(n²) time, O(n) space
    static bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        vector<bool> dp(s.length() + 1, false);
        dp[0] = true;
        
        for (int i = 1; i <= s.length(); i++) {
            for (int j = 0; j < i; j++) {
                if (dp[j] && dict.find(s.substr(j, i - j)) != dict.end()) {
                    dp[i] = true;
                    break;
                }
            }
        }
        
        return dp[s.length()];
    }
};

// ========================================================================
// PROBLEM 14: WORD BREAK II ⭐⭐⭐
// ========================================================================
/*
 * Given a string s and a dictionary of strings wordDict, add spaces in s to 
 * construct a sentence where each word is a valid dictionary word. Return all 
 * such possible sentences in any order.
 */

class WordBreakII {
public:
    // DFS with memoization - O(n³) time, O(n³) space
    static vector<string> wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        unordered_map<string, vector<string>> memo;
        return dfs(s, dict, memo);
    }
    
private:
    static vector<string> dfs(string s, unordered_set<string>& dict, 
                             unordered_map<string, vector<string>>& memo) {
        if (memo.find(s) != memo.end()) {
            return memo[s];
        }
        
        vector<string> result;
        
        if (dict.find(s) != dict.end()) {
            result.push_back(s);
        }
        
        for (int i = 1; i < s.length(); i++) {
            string prefix = s.substr(0, i);
            if (dict.find(prefix) != dict.end()) {
                vector<string> suffixes = dfs(s.substr(i), dict, memo);
                for (string& suffix : suffixes) {
                    result.push_back(prefix + " " + suffix);
                }
            }
        }
        
        memo[s] = result;
        return result;
    }
};

// ========================================================================
// PROBLEM 15: EDIT DISTANCE ⭐⭐⭐
// ========================================================================
/*
 * Given two strings word1 and word2, return the minimum number of operations 
 * required to convert word1 to word2.
 */

class EditDistance {
public:
    // Dynamic Programming - O(m*n) time, O(m*n) space
    static int minDistance(string word1, string word2) {
        int m = word1.length(), n = word2.length();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        
        // Initialize base cases
        for (int i = 0; i <= m; i++) dp[i][0] = i;
        for (int j = 0; j <= n; j++) dp[0][j] = j;
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = 1 + min({dp[i - 1][j],     // Delete
                                        dp[i][j - 1],     // Insert
                                        dp[i - 1][j - 1]  // Replace
                                       });
                }
            }
        }
        
        return dp[m][n];
    }
};

// ========================================================================
// PROBLEM 16: REGULAR EXPRESSION MATCHING ⭐⭐⭐
// ========================================================================
/*
 * Given an input string s and a pattern p, implement regular expression matching 
 * with support for '.' and '*' where:
 * - '.' Matches any single character.
 * - '*' Matches zero or more of the preceding element.
 */

class RegularExpressionMatching {
public:
    // Dynamic Programming - O(m*n) time, O(m*n) space
    static bool isMatch(string s, string p) {
        int m = s.length(), n = p.length();
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
        
        dp[0][0] = true;
        
        // Handle patterns like a*, a*b*, a*b*c*
        for (int j = 2; j <= n; j += 2) {
            if (p[j - 1] == '*') {
                dp[0][j] = dp[0][j - 2];
            }
        }
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (p[j - 1] == '*') {
                    dp[i][j] = dp[i][j - 2]; // Zero occurrences
                    if (p[j - 2] == '.' || p[j - 2] == s[i - 1]) {
                        dp[i][j] = dp[i][j] || dp[i - 1][j]; // One or more occurrences
                    }
                } else if (p[j - 1] == '.' || p[j - 1] == s[i - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                }
            }
        }
        
        return dp[m][n];
    }
};

// ========================================================================
// PROBLEM 17: WILDCARD MATCHING ⭐⭐⭐
// ========================================================================
/*
 * Given an input string s and a pattern p, implement wildcard pattern matching 
 * with support for '?' and '*' where:
 * - '?' Matches any single character.
 * - '*' Matches any sequence of characters (including the empty sequence).
 */

class WildcardMatching {
public:
    // Dynamic Programming - O(m*n) time, O(m*n) space
    static bool isMatch(string s, string p) {
        int m = s.length(), n = p.length();
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
        
        dp[0][0] = true;
        
        // Handle patterns with '*' at the beginning
        for (int j = 1; j <= n; j++) {
            if (p[j - 1] == '*') {
                dp[0][j] = dp[0][j - 1];
            }
        }
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (p[j - 1] == '*') {
                    dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
                } else if (p[j - 1] == '?' || p[j - 1] == s[i - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                }
            }
        }
        
        return dp[m][n];
    }
};

// ========================================================================
// PROBLEM 18: LONGEST VALID PARENTHESES ⭐⭐⭐
// ========================================================================
/*
 * Given a string containing just the characters '(' and ')', find the length 
 * of the longest valid (well-formed) parentheses substring.
 */

class LongestValidParentheses {
public:
    // Dynamic Programming - O(n) time, O(n) space
    static int longestValidParentheses(string s) {
        int n = s.length();
        vector<int> dp(n, 0);
        int maxLen = 0;
        
        for (int i = 1; i < n; i++) {
            if (s[i] == ')') {
                if (s[i - 1] == '(') {
                    dp[i] = (i >= 2 ? dp[i - 2] : 0) + 2;
                } else if (dp[i - 1] > 0) {
                    int matchingIndex = i - dp[i - 1] - 1;
                    if (matchingIndex >= 0 && s[matchingIndex] == '(') {
                        dp[i] = dp[i - 1] + 2 + (matchingIndex > 0 ? dp[matchingIndex - 1] : 0);
                    }
                }
                maxLen = max(maxLen, dp[i]);
            }
        }
        
        return maxLen;
    }
    
    // Stack approach - O(n) time, O(n) space
    static int longestValidParenthesesStack(string s) {
        stack<int> st;
        st.push(-1);
        int maxLen = 0;
        
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '(') {
                st.push(i);
            } else {
                st.pop();
                if (st.empty()) {
                    st.push(i);
                } else {
                    maxLen = max(maxLen, i - st.top());
                }
            }
        }
        
        return maxLen;
    }
};

// ========================================================================
// PROBLEM 19: DISTINCT SUBSEQUENCES ⭐⭐⭐
// ========================================================================
/*
 * Given two strings s and t, return the number of distinct subsequences of s 
 * which equals t.
 */

class DistinctSubsequences {
public:
    // Dynamic Programming - O(m*n) time, O(m*n) space
    static int numDistinct(string s, string t) {
        int m = s.length(), n = t.length();
        vector<vector<long long>> dp(m + 1, vector<long long>(n + 1, 0));
        
        // Empty string t can be formed by any string s in one way
        for (int i = 0; i <= m; i++) {
            dp[i][0] = 1;
        }
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                dp[i][j] = dp[i - 1][j];
                if (s[i - 1] == t[j - 1]) {
                    dp[i][j] += dp[i - 1][j - 1];
                }
            }
        }
        
        return dp[m][n];
    }
};

// ========================================================================
// PROBLEM 20: SCRAMBLE STRING ⭐⭐⭐
// ========================================================================
/*
 * We can scramble a string s to get a string t using the following algorithm:
 * 1. If the length of the string is 1, stop.
 * 2. If the length of the string is > 1, do the following:
 *    - Split the string into two non-empty substrings at a random index.
 *    - Decide whether to swap the two substrings or to keep them in the same order.
 *    - Apply step 1 recursively on each of the two substrings.
 */

class ScrambleString {
public:
    // Dynamic Programming with memoization - O(n⁴) time, O(n³) space
    static bool isScramble(string s1, string s2) {
        if (s1.length() != s2.length()) return false;
        if (s1 == s2) return true;
        
        // Check if characters match
        vector<int> count(26, 0);
        for (int i = 0; i < s1.length(); i++) {
            count[s1[i] - 'a']++;
            count[s2[i] - 'a']--;
        }
        
        for (int c : count) {
            if (c != 0) return false;
        }
        
        // Try all possible splits
        for (int i = 1; i < s1.length(); i++) {
            // Case 1: s1[0...i-1] matches s2[0...i-1] and s1[i...n-1] matches s2[i...n-1]
            if (isScramble(s1.substr(0, i), s2.substr(0, i)) && 
                isScramble(s1.substr(i), s2.substr(i))) {
                return true;
            }
            
            // Case 2: s1[0...i-1] matches s2[n-i...n-1] and s1[i...n-1] matches s2[0...n-i-1]
            if (isScramble(s1.substr(0, i), s2.substr(s2.length() - i)) && 
                isScramble(s1.substr(i), s2.substr(0, s2.length() - i))) {
                return true;
            }
        }
        
        return false;
    }
};

// ========================================================================
// TESTING FUNCTIONS
// ========================================================================

void testStringProblems() {
    cout << "\n=== TESTING STRING PROBLEMS ===" << endl;
    
    // Test Valid Anagram
    cout << "Valid Anagram ('anagram', 'nagaram'): " << 
         ValidAnagram::isAnagram("anagram", "nagaram") << endl;
    
    // Test Valid Palindrome
    cout << "Valid Palindrome ('A man, a plan, a canal: Panama'): " << 
         ValidPalindrome::isPalindrome("A man, a plan, a canal: Panama") << endl;
    
    // Test Longest Substring Without Repeating Characters
    cout << "Longest Substring Without Repeating ('abcabcbb'): " << 
         LongestSubstringWithoutRepeating::lengthOfLongestSubstring("abcabcbb") << endl;
    
    // Test Longest Palindromic Substring
    cout << "Longest Palindromic Substring ('babad'): " << 
         LongestPalindromicSubstring::longestPalindrome("babad") << endl;
    
    // Test Palindromic Substrings
    cout << "Count Palindromic Substrings ('abc'): " << 
         PalindromicSubstrings::countSubstrings("abc") << endl;
    
    // Test Valid Parentheses
    cout << "Valid Parentheses ('()[]{}') : " << 
         ValidParentheses::isValid("()[]{}") << endl;
    
    // Test Minimum Window Substring
    cout << "Minimum Window Substring ('ADOBECODEBANC', 'ABC'): " << 
         MinimumWindowSubstring::minWindow("ADOBECODEBANC", "ABC") << endl;
    
    // Test Longest Common Subsequence
    cout << "Longest Common Subsequence ('abcde', 'ace'): " << 
         LongestCommonSubsequence::longestCommonSubsequence("abcde", "ace") << endl;
    
    // Test Word Break
    vector<string> wordDict = {"leet", "code"};
    cout << "Word Break ('leetcode'): " << 
         WordBreak::wordBreak("leetcode", wordDict) << endl;
    
    // Test Edit Distance
    cout << "Edit Distance ('horse', 'ros'): " << 
         EditDistance::minDistance("horse", "ros") << endl;
}

// ========================================================================
// MAIN FUNCTION
// ========================================================================

int main() {
    cout << "STRING PROBLEMS - COMPREHENSIVE COLLECTION" << endl;
    cout << "==========================================" << endl;
    
    testStringProblems();
    
    cout << "\n=== PROBLEMS SUMMARY ===" << endl;
    cout << "1. Valid Anagram ⭐" << endl;
    cout << "2. Valid Palindrome ⭐" << endl;
    cout << "3. Longest Substring Without Repeating Characters ⭐⭐" << endl;
    cout << "4. Longest Palindromic Substring ⭐⭐" << endl;
    cout << "5. Palindromic Substrings ⭐⭐" << endl;
    cout << "6. Group Anagrams ⭐⭐" << endl;
    cout << "7. Valid Parentheses ⭐" << endl;
    cout << "8. Implement strStr() ⭐" << endl;
    cout << "9. Minimum Window Substring ⭐⭐⭐" << endl;
    cout << "10. Longest Repeating Character Replacement ⭐⭐" << endl;
    cout << "11. Encode and Decode Strings ⭐⭐" << endl;
    cout << "12. Longest Common Subsequence ⭐⭐" << endl;
    cout << "13. Word Break ⭐⭐" << endl;
    cout << "14. Word Break II ⭐⭐⭐" << endl;
    cout << "15. Edit Distance ⭐⭐⭐" << endl;
    cout << "16. Regular Expression Matching ⭐⭐⭐" << endl;
    cout << "17. Wildcard Matching ⭐⭐⭐" << endl;
    cout << "18. Longest Valid Parentheses ⭐⭐⭐" << endl;
    cout << "19. Distinct Subsequences ⭐⭐⭐" << endl;
    cout << "20. Scramble String ⭐⭐⭐" << endl;
    
    cout << "\nNext: Practice these problems and move to linked lists!" << endl;
    
    return 0;
}

/*
 * COMPILATION: g++ -std=c++17 -O2 -o string_problems string_problems.cpp
 * 
 * STUDY TIPS:
 * 1. Start with easy problems (⭐) and understand the patterns
 * 2. Practice drawing out examples for each problem
 * 3. Focus on time/space complexity analysis
 * 4. Master the sliding window technique
 * 5. Practice dynamic programming on strings
 * 
 * KEY PATTERNS TO MASTER:
 * - Sliding window (for substring problems)
 * - Two pointers (for palindrome problems)
 * - Hash maps (for character frequency)
 * - Dynamic programming (for edit distance, LCS)
 * - Stack (for parentheses problems)
 * - String matching algorithms (KMP, etc.)
 */
