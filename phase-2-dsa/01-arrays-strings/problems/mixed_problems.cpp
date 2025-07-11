/*
 * MIXED ARRAY & STRING PROBLEMS
 * =============================
 * 
 * This file contains challenging problems that combine array and string techniques.
 * These problems will test your understanding of both data structures and help you
 * see how they work together in complex scenarios.
 * 
 * DIFFICULTY LEVELS:
 * ⭐⭐ Medium (1-15)
 * ⭐⭐⭐ Hard (16-25)
 * 
 * TOPICS COVERED:
 * - Array manipulation with strings
 * - String processing with array algorithms
 * - Complex pattern matching
 * - Advanced sliding window techniques
 * - Multi-dimensional string problems
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <climits>

using namespace std;

// ========================================================================
// PROBLEM 1: FIND ALL ANAGRAMS IN STRING ⭐⭐
// ========================================================================
/*
 * Given two strings s and p, return an array of all the start indices of p's 
 * anagrams in s. You may return the answer in any order.
 */

class FindAnagrams {
public:
    // Sliding window - O(n) time, O(1) space
    static vector<int> findAnagrams(string s, string p) {
        vector<int> result;
        if (s.length() < p.length()) return result;
        
        vector<int> pCount(26, 0), sCount(26, 0);
        
        // Count characters in pattern
        for (char c : p) pCount[c - 'a']++;
        
        // Sliding window
        for (int i = 0; i < s.length(); i++) {
            sCount[s[i] - 'a']++;
            
            // Remove leftmost character if window size exceeds pattern length
            if (i >= p.length()) {
                sCount[s[i - p.length()] - 'a']--;
            }
            
            // Check if current window is an anagram
            if (sCount == pCount) {
                result.push_back(i - p.length() + 1);
            }
        }
        
        return result;
    }
};

// ========================================================================
// PROBLEM 2: SLIDING WINDOW MAXIMUM ⭐⭐⭐
// ========================================================================
/*
 * You are given an array of integers nums, there is a sliding window of size k 
 * which is moving from the very left of the array to the very right. You can 
 * only see the k numbers in the window. Each time the sliding window moves 
 * right by one position. Return the max sliding window.
 */

class SlidingWindowMaximum {
public:
    // Deque approach - O(n) time, O(k) space
    static vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> dq; // stores indices
        vector<int> result;
        
        for (int i = 0; i < nums.size(); i++) {
            // Remove indices that are out of current window
            while (!dq.empty() && dq.front() < i - k + 1) {
                dq.pop_front();
            }
            
            // Remove indices whose corresponding values are smaller than current
            while (!dq.empty() && nums[dq.back()] < nums[i]) {
                dq.pop_back();
            }
            
            dq.push_back(i);
            
            // Add to result if window is complete
            if (i >= k - 1) {
                result.push_back(nums[dq.front()]);
            }
        }
        
        return result;
    }
};

// ========================================================================
// PROBLEM 3: LONGEST SUBSTRING WITH AT MOST K DISTINCT CHARACTERS ⭐⭐
// ========================================================================
/*
 * Given a string s and an integer k, return the length of the longest 
 * substring of s that contains at most k distinct characters.
 */

class LongestSubstringKDistinct {
public:
    // Sliding window - O(n) time, O(k) space
    static int lengthOfLongestSubstringKDistinct(string s, int k) {
        if (k == 0) return 0;
        
        unordered_map<char, int> charCount;
        int left = 0, maxLen = 0;
        
        for (int right = 0; right < s.length(); right++) {
            charCount[s[right]]++;
            
            // Shrink window if more than k distinct characters
            while (charCount.size() > k) {
                charCount[s[left]]--;
                if (charCount[s[left]] == 0) {
                    charCount.erase(s[left]);
                }
                left++;
            }
            
            maxLen = max(maxLen, right - left + 1);
        }
        
        return maxLen;
    }
};

// ========================================================================
// PROBLEM 4: MINIMUM WINDOW SUBSTRING WITH DUPLICATES ⭐⭐⭐
// ========================================================================
/*
 * Given strings s and t, return the minimum window substring of s that 
 * contains all characters of t with their required frequencies.
 */

class MinimumWindowSubstringAdvanced {
public:
    // Advanced sliding window - O(n) time, O(m) space
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
            
            // Contract window
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
// PROBLEM 5: PERMUTATION IN STRING ⭐⭐
// ========================================================================
/*
 * Given two strings s1 and s2, return true if s2 contains a permutation of s1.
 */

class PermutationInString {
public:
    // Sliding window - O(n) time, O(1) space
    static bool checkInclusion(string s1, string s2) {
        if (s1.length() > s2.length()) return false;
        
        vector<int> s1Count(26, 0), s2Count(26, 0);
        
        // Count characters in s1
        for (char c : s1) s1Count[c - 'a']++;
        
        // Sliding window of size s1.length()
        for (int i = 0; i < s2.length(); i++) {
            s2Count[s2[i] - 'a']++;
            
            // Remove leftmost character if window size exceeds s1 length
            if (i >= s1.length()) {
                s2Count[s2[i - s1.length()] - 'a']--;
            }
            
            // Check if current window is a permutation of s1
            if (s1Count == s2Count) {
                return true;
            }
        }
        
        return false;
    }
};

// ========================================================================
// PROBLEM 6: SUBSTRING WITH CONCATENATION OF ALL WORDS ⭐⭐⭐
// ========================================================================
/*
 * You are given a string s and an array of strings words. All strings in words 
 * are of the same length. A concatenated substring is a substring that contains 
 * exactly one occurrence of each word in words.
 */

class SubstringConcatenation {
public:
    // Sliding window with hash maps - O(n*m) time, O(m) space
    static vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> result;
        if (s.empty() || words.empty()) return result;
        
        int wordLen = words[0].length();
        int totalLen = wordLen * words.size();
        
        if (s.length() < totalLen) return result;
        
        // Count words
        unordered_map<string, int> wordCount;
        for (string& word : words) {
            wordCount[word]++;
        }
        
        // Try all possible starting positions
        for (int i = 0; i <= s.length() - totalLen; i++) {
            unordered_map<string, int> seen;
            int j = 0;
            
            // Check each word in the current window
            while (j < words.size()) {
                string word = s.substr(i + j * wordLen, wordLen);
                if (wordCount.find(word) == wordCount.end()) {
                    break;
                }
                
                seen[word]++;
                if (seen[word] > wordCount[word]) {
                    break;
                }
                
                j++;
            }
            
            if (j == words.size()) {
                result.push_back(i);
            }
        }
        
        return result;
    }
};

// ========================================================================
// PROBLEM 7: INTERLEAVING STRING ⭐⭐⭐
// ========================================================================
/*
 * Given strings s1, s2, and s3, find whether s3 is formed by an interleaving 
 * of s1 and s2.
 */

class InterleavingString {
public:
    // Dynamic Programming - O(m*n) time, O(m*n) space
    static bool isInterleave(string s1, string s2, string s3) {
        if (s1.length() + s2.length() != s3.length()) return false;
        
        int m = s1.length(), n = s2.length();
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
        
        dp[0][0] = true;
        
        // Fill first row
        for (int j = 1; j <= n; j++) {
            dp[0][j] = dp[0][j - 1] && s2[j - 1] == s3[j - 1];
        }
        
        // Fill first column
        for (int i = 1; i <= m; i++) {
            dp[i][0] = dp[i - 1][0] && s1[i - 1] == s3[i - 1];
        }
        
        // Fill the rest
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                dp[i][j] = (dp[i - 1][j] && s1[i - 1] == s3[i + j - 1]) ||
                           (dp[i][j - 1] && s2[j - 1] == s3[i + j - 1]);
            }
        }
        
        return dp[m][n];
    }
};

// ========================================================================
// PROBLEM 8: VALID WORD SQUARE ⭐⭐
// ========================================================================
/*
 * Given an array of strings words, return true if it forms a valid word square.
 * A sequence of strings forms a valid word square if the kth row and column 
 * read the same string, where 0 ≤ k < max(numRows, numColumns).
 */

class ValidWordSquare {
public:
    // Matrix validation - O(n*m) time, O(1) space
    static bool validWordSquare(vector<string>& words) {
        int n = words.size();
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < words[i].length(); j++) {
                // Check if the character at (i,j) equals character at (j,i)
                if (j >= n || i >= words[j].length() || words[i][j] != words[j][i]) {
                    return false;
                }
            }
        }
        
        return true;
    }
};

// ========================================================================
// PROBLEM 9: WORD LADDER ⭐⭐⭐
// ========================================================================
/*
 * Given two words, beginWord and endWord, and a dictionary wordList, return 
 * the number of words in the shortest transformation sequence from beginWord 
 * to endWord.
 */

class WordLadder {
public:
    // BFS - O(m²*n) time, O(m²*n) space
    static int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> dict(wordList.begin(), wordList.end());
        if (dict.find(endWord) == dict.end()) return 0;
        
        queue<string> q;
        q.push(beginWord);
        int level = 1;
        
        while (!q.empty()) {
            int size = q.size();
            
            for (int i = 0; i < size; i++) {
                string word = q.front();
                q.pop();
                
                if (word == endWord) return level;
                
                // Try all possible one-character changes
                for (int j = 0; j < word.length(); j++) {
                    char originalChar = word[j];
                    for (char c = 'a'; c <= 'z'; c++) {
                        if (c == originalChar) continue;
                        
                        word[j] = c;
                        if (dict.find(word) != dict.end()) {
                            q.push(word);
                            dict.erase(word);
                        }
                    }
                    word[j] = originalChar;
                }
            }
            level++;
        }
        
        return 0;
    }
};

// ========================================================================
// PROBLEM 10: WORD LADDER II ⭐⭐⭐
// ========================================================================
/*
 * Given two words, beginWord and endWord, and a dictionary wordList, return 
 * all the shortest transformation sequences from beginWord to endWord.
 */

class WordLadderII {
public:
    // BFS + DFS - O(m²*n) time, O(m²*n) space
    static vector<vector<string>> findLadders(string beginWord, string endWord, 
                                            vector<string>& wordList) {
        vector<vector<string>> result;
        unordered_set<string> dict(wordList.begin(), wordList.end());
        
        if (dict.find(endWord) == dict.end()) return result;
        
        unordered_map<string, vector<string>> neighbors;
        unordered_set<string> visited;
        
        // BFS to build the graph
        queue<string> q;
        q.push(beginWord);
        visited.insert(beginWord);
        bool found = false;
        
        while (!q.empty() && !found) {
            int size = q.size();
            unordered_set<string> currentLevel;
            
            for (int i = 0; i < size; i++) {
                string word = q.front();
                q.pop();
                
                for (int j = 0; j < word.length(); j++) {
                    char originalChar = word[j];
                    for (char c = 'a'; c <= 'z'; c++) {
                        if (c == originalChar) continue;
                        
                        word[j] = c;
                        if (dict.find(word) != dict.end()) {
                            neighbors[word].push_back(word.substr(0, j) + originalChar + word.substr(j + 1));
                            
                            if (word == endWord) {
                                found = true;
                            }
                            
                            if (visited.find(word) == visited.end()) {
                                currentLevel.insert(word);
                            }
                        }
                    }
                    word[j] = originalChar;
                }
            }
            
            for (string word : currentLevel) {
                q.push(word);
                visited.insert(word);
            }
        }
        
        // DFS to build paths
        vector<string> path = {beginWord};
        dfs(beginWord, endWord, neighbors, path, result);
        
        return result;
    }
    
private:
    static void dfs(string word, string endWord, 
                   unordered_map<string, vector<string>>& neighbors,
                   vector<string>& path, vector<vector<string>>& result) {
        if (word == endWord) {
            result.push_back(path);
            return;
        }
        
        for (string neighbor : neighbors[word]) {
            path.push_back(neighbor);
            dfs(neighbor, endWord, neighbors, path, result);
            path.pop_back();
        }
    }
};

// ========================================================================
// PROBLEM 11: PALINDROME PAIRS ⭐⭐⭐
// ========================================================================
/*
 * Given a list of unique words, return all the pairs of the distinct indices 
 * (i, j) such that the concatenation of the two words is a palindrome.
 */

class PalindromePairs {
public:
    // Trie-based solution - O(n*m²) time, O(n*m) space
    static vector<vector<int>> palindromePairs(vector<string>& words) {
        vector<vector<int>> result;
        unordered_map<string, int> wordMap;
        
        // Build word map
        for (int i = 0; i < words.size(); i++) {
            wordMap[words[i]] = i;
        }
        
        for (int i = 0; i < words.size(); i++) {
            string word = words[i];
            
            for (int j = 0; j <= word.length(); j++) {
                string str1 = word.substr(0, j);
                string str2 = word.substr(j);
                
                // Check if str1 is palindrome and reverse of str2 exists
                if (isPalindrome(str1)) {
                    string rev2 = str2;
                    reverse(rev2.begin(), rev2.end());
                    if (wordMap.find(rev2) != wordMap.end() && 
                        wordMap[rev2] != i) {
                        result.push_back({wordMap[rev2], i});
                    }
                }
                
                // Check if str2 is palindrome and reverse of str1 exists
                if (str2.length() > 0 && isPalindrome(str2)) {
                    string rev1 = str1;
                    reverse(rev1.begin(), rev1.end());
                    if (wordMap.find(rev1) != wordMap.end() && 
                        wordMap[rev1] != i) {
                        result.push_back({i, wordMap[rev1]});
                    }
                }
            }
        }
        
        return result;
    }
    
private:
    static bool isPalindrome(string s) {
        int left = 0, right = s.length() - 1;
        while (left < right) {
            if (s[left] != s[right]) return false;
            left++;
            right--;
        }
        return true;
    }
};

// ========================================================================
// PROBLEM 12: TEXT JUSTIFICATION ⭐⭐⭐
// ========================================================================
/*
 * Given an array of strings words and a width maxWidth, format the text such 
 * that each line has exactly maxWidth characters and is fully justified.
 */

class TextJustification {
public:
    // String formatting - O(n) time, O(n) space
    static vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> result;
        int i = 0;
        
        while (i < words.size()) {
            int j = i;
            int lineLength = 0;
            
            // Find words that fit in current line
            while (j < words.size() && lineLength + words[j].length() + j - i <= maxWidth) {
                lineLength += words[j].length();
                j++;
            }
            
            // Build the line
            string line = "";
            int spaces = maxWidth - lineLength;
            
            if (j == words.size() || j == i + 1) {
                // Last line or single word line - left justify
                for (int k = i; k < j; k++) {
                    line += words[k];
                    if (k < j - 1) line += " ";
                }
                line += string(maxWidth - line.length(), ' ');
            } else {
                // Fully justify
                int gaps = j - i - 1;
                int spacePerGap = spaces / gaps;
                int extraSpaces = spaces % gaps;
                
                for (int k = i; k < j; k++) {
                    line += words[k];
                    if (k < j - 1) {
                        line += string(spacePerGap, ' ');
                        if (extraSpaces > 0) {
                            line += " ";
                            extraSpaces--;
                        }
                    }
                }
            }
            
            result.push_back(line);
            i = j;
        }
        
        return result;
    }
};

// ========================================================================
// PROBLEM 13: SHORTEST PALINDROME ⭐⭐⭐
// ========================================================================
/*
 * You are given a string s. You can convert s to a palindrome by adding 
 * characters in front of it. Return the shortest palindrome you can find.
 */

class ShortestPalindrome {
public:
    // KMP-based solution - O(n) time, O(n) space
    static string shortestPalindrome(string s) {
        if (s.empty()) return s;
        
        string rev = s;
        reverse(rev.begin(), rev.end());
        string combined = s + "#" + rev;
        
        vector<int> lps = computeLPS(combined);
        int overlap = lps.back();
        
        string prefix = rev.substr(0, s.length() - overlap);
        return prefix + s;
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
// PROBLEM 14: REMOVE INVALID PARENTHESES ⭐⭐⭐
// ========================================================================
/*
 * Given a string s that contains parentheses and letters, remove the minimum 
 * number of invalid parentheses to make the input string valid.
 */

class RemoveInvalidParentheses {
public:
    // BFS - O(n*2^n) time, O(n*2^n) space
    static vector<string> removeInvalidParentheses(string s) {
        vector<string> result;
        queue<string> q;
        unordered_set<string> visited;
        
        q.push(s);
        visited.insert(s);
        bool found = false;
        
        while (!q.empty() && !found) {
            int size = q.size();
            
            for (int i = 0; i < size; i++) {
                string current = q.front();
                q.pop();
                
                if (isValid(current)) {
                    result.push_back(current);
                    found = true;
                }
                
                if (!found) {
                    // Try removing each character
                    for (int j = 0; j < current.length(); j++) {
                        if (current[j] == '(' || current[j] == ')') {
                            string next = current.substr(0, j) + current.substr(j + 1);
                            if (visited.find(next) == visited.end()) {
                                q.push(next);
                                visited.insert(next);
                            }
                        }
                    }
                }
            }
        }
        
        return result;
    }
    
private:
    static bool isValid(string s) {
        int count = 0;
        for (char c : s) {
            if (c == '(') count++;
            else if (c == ')') count--;
            if (count < 0) return false;
        }
        return count == 0;
    }
};

// ========================================================================
// PROBLEM 15: WORD PATTERN II ⭐⭐⭐
// ========================================================================
/*
 * Given a pattern and a string s, return true if s matches the pattern.
 * A string s matches a pattern if there is a bijective mapping between 
 * a letter in pattern and a non-empty substring in s.
 */

class WordPatternII {
public:
    // Backtracking - O(n^m) time, O(n) space
    static bool wordPatternMatch(string pattern, string s) {
        unordered_map<char, string> charToString;
        unordered_map<string, char> stringToChar;
        return backtrack(pattern, 0, s, 0, charToString, stringToChar);
    }
    
private:
    static bool backtrack(string pattern, int pIndex, string s, int sIndex,
                         unordered_map<char, string>& charToString,
                         unordered_map<string, char>& stringToChar) {
        if (pIndex == pattern.length() && sIndex == s.length()) {
            return true;
        }
        
        if (pIndex == pattern.length() || sIndex == s.length()) {
            return false;
        }
        
        char c = pattern[pIndex];
        
        if (charToString.find(c) != charToString.end()) {
            string str = charToString[c];
            if (sIndex + str.length() > s.length() || 
                s.substr(sIndex, str.length()) != str) {
                return false;
            }
            return backtrack(pattern, pIndex + 1, s, sIndex + str.length(),
                           charToString, stringToChar);
        }
        
        // Try all possible substrings
        for (int i = sIndex; i < s.length(); i++) {
            string str = s.substr(sIndex, i - sIndex + 1);
            
            if (stringToChar.find(str) != stringToChar.end() && 
                stringToChar[str] != c) {
                continue;
            }
            
            charToString[c] = str;
            stringToChar[str] = c;
            
            if (backtrack(pattern, pIndex + 1, s, i + 1, charToString, stringToChar)) {
                return true;
            }
            
            charToString.erase(c);
            stringToChar.erase(str);
        }
        
        return false;
    }
};

// ========================================================================
// TESTING FUNCTIONS
// ========================================================================

void testMixedProblems() {
    cout << "\n=== TESTING MIXED PROBLEMS ===" << endl;
    
    // Test Find Anagrams
    auto anagrams = FindAnagrams::findAnagrams("abab", "ab");
    cout << "Find Anagrams (abab, ab): ";
    for (int pos : anagrams) cout << pos << " ";
    cout << endl;
    
    // Test Sliding Window Maximum
    vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
    auto maxWindow = SlidingWindowMaximum::maxSlidingWindow(nums, 3);
    cout << "Sliding Window Maximum: ";
    for (int val : maxWindow) cout << val << " ";
    cout << endl;
    
    // Test Longest Substring K Distinct
    cout << "Longest Substring 2 Distinct (eceba): " << 
         LongestSubstringKDistinct::lengthOfLongestSubstringKDistinct("eceba", 2) << endl;
    
    // Test Permutation in String
    cout << "Permutation in String (ab, eidbaooo): " << 
         PermutationInString::checkInclusion("ab", "eidbaooo") << endl;
    
    // Test Word Ladder
    vector<string> wordList = {"hot", "dot", "dog", "lot", "log", "cog"};
    cout << "Word Ladder (hit -> cog): " << 
         WordLadder::ladderLength("hit", "cog", wordList) << endl;
    
    // Test Valid Word Square
    vector<string> words = {"abcd", "bnrt", "crmy", "dtye"};
    cout << "Valid Word Square: " << ValidWordSquare::validWordSquare(words) << endl;
}

// ========================================================================
// MAIN FUNCTION
// ========================================================================

int main() {
    cout << "MIXED ARRAY & STRING PROBLEMS" << endl;
    cout << "=============================" << endl;
    
    testMixedProblems();
    
    cout << "\n=== PROBLEMS SUMMARY ===" << endl;
    cout << "1. Find All Anagrams in String ⭐⭐" << endl;
    cout << "2. Sliding Window Maximum ⭐⭐⭐" << endl;
    cout << "3. Longest Substring with At Most K Distinct Characters ⭐⭐" << endl;
    cout << "4. Minimum Window Substring (Advanced) ⭐⭐⭐" << endl;
    cout << "5. Permutation in String ⭐⭐" << endl;
    cout << "6. Substring with Concatenation of All Words ⭐⭐⭐" << endl;
    cout << "7. Interleaving String ⭐⭐⭐" << endl;
    cout << "8. Valid Word Square ⭐⭐" << endl;
    cout << "9. Word Ladder ⭐⭐⭐" << endl;
    cout << "10. Word Ladder II ⭐⭐⭐" << endl;
    cout << "11. Palindrome Pairs ⭐⭐⭐" << endl;
    cout << "12. Text Justification ⭐⭐⭐" << endl;
    cout << "13. Shortest Palindrome ⭐⭐⭐" << endl;
    cout << "14. Remove Invalid Parentheses ⭐⭐⭐" << endl;
    cout << "15. Word Pattern II ⭐⭐⭐" << endl;
    
    cout << "\nCongratulations! You've completed the Arrays & Strings module!" << endl;
    cout << "Next: Move on to Linked Lists in phase-2-dsa/02-linked-lists/" << endl;
    
    return 0;
}

/*
 * COMPILATION: g++ -std=c++17 -O2 -o mixed_problems mixed_problems.cpp
 * 
 * ADVANCED STUDY TIPS:
 * 1. These problems combine multiple techniques - analyze each component
 * 2. Practice identifying when to use sliding window vs. two pointers
 * 3. Master the art of combining BFS/DFS with string operations
 * 4. Understand time/space trade-offs in complex problems
 * 5. Practice implementing these problems from memory
 * 
 * KEY ADVANCED PATTERNS:
 * - Sliding window with hash maps
 * - BFS/DFS with string transformations
 * - Dynamic programming on strings
 * - Backtracking with constraint satisfaction
 * - Trie-based string matching
 * - KMP algorithm applications
 */
