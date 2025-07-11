/*
 * STRING ALGORITHMS AND FUNDAMENTALS
 * =================================
 * 
 * This module covers comprehensive string manipulation and algorithms in C++.
 * 
 * TOPICS COVERED:
 * 1. String Fundamentals (C-style strings vs std::string)
 * 2. String Operations and Manipulation
 * 3. String Searching Algorithms
 * 4. Pattern Matching Algorithms
 * 5. String Parsing and Tokenization
 * 6. Common String Problems and Solutions
 * 7. Advanced String Algorithms
 * 
 * LEARNING OBJECTIVES:
 * - Master string manipulation techniques
 * - Understand time/space complexity of string operations
 * - Implement efficient string algorithms
 * - Solve complex string-based problems
 * 
 * PREREQUISITES:
 * - Basic C++ knowledge
 * - Understanding of arrays and pointers
 * - Familiarity with STL containers
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <cctype>
#include <sstream>
#include <regex>

using namespace std;

// ========================================================================
// 1. STRING FUNDAMENTALS
// ========================================================================

/*
 * THEORY: String Representation in C++
 * 
 * 1. C-style strings: null-terminated character arrays
 *    - char str[] = "Hello";
 *    - Efficient but unsafe, manual memory management
 * 
 * 2. std::string: C++ string class
 *    - Dynamic size, automatic memory management
 *    - Rich set of member functions
 *    - Better safety and convenience
 * 
 * 3. String literals: compile-time constants
 *    - "Hello" is a string literal
 *    - Stored in read-only memory
 */

void stringFundamentals() {
    cout << "\n=== STRING FUNDAMENTALS ===" << endl;
    
    // C-style strings
    const char* cstr = "Hello, World!";
    char buffer[100];
    strcpy(buffer, cstr);
    cout << "C-style string: " << buffer << endl;
    
    // std::string
    string str = "Hello, C++!";
    cout << "std::string: " << str << endl;
    cout << "Length: " << str.length() << endl;
    cout << "Capacity: " << str.capacity() << endl;
    
    // String operations
    str += " Welcome!";
    cout << "After append: " << str << endl;
    
    // Character access
    cout << "First char: " << str[0] << endl;
    cout << "At index 7: " << str.at(7) << endl;
    
    // Substring
    string sub = str.substr(7, 3);
    cout << "Substring (7,3): " << sub << endl;
    
    // Find operations
    size_t pos = str.find("C++");
    if (pos != string::npos) {
        cout << "Found 'C++' at position: " << pos << endl;
    }
}

// ========================================================================
// 2. STRING OPERATIONS AND MANIPULATION
// ========================================================================

/*
 * THEORY: Common String Operations
 * 
 * 1. Concatenation: O(n) - creates new string
 * 2. Insertion: O(n) - may require shifting characters
 * 3. Deletion: O(n) - may require shifting characters
 * 4. Replacement: O(n) - depends on replacement size
 * 5. Case conversion: O(n) - iterate through all characters
 */

class StringManipulator {
public:
    // Remove all spaces from string
    static string removeSpaces(const string& str) {
        string result;
        for (char c : str) {
            if (c != ' ') {
                result += c;
            }
        }
        return result;
    }
    
    // Reverse string in-place
    static void reverseString(string& str) {
        int left = 0, right = str.length() - 1;
        while (left < right) {
            swap(str[left], str[right]);
            left++;
            right--;
        }
    }
    
    // Check if string is palindrome
    static bool isPalindrome(const string& str) {
        int left = 0, right = str.length() - 1;
        while (left < right) {
            if (str[left] != str[right]) {
                return false;
            }
            left++;
            right--;
        }
        return true;
    }
    
    // Convert to uppercase
    static string toUpper(const string& str) {
        string result = str;
        transform(result.begin(), result.end(), result.begin(), ::toupper);
        return result;
    }
    
    // Convert to lowercase
    static string toLower(const string& str) {
        string result = str;
        transform(result.begin(), result.end(), result.begin(), ::tolower);
        return result;
    }
    
    // Count character frequency
    static unordered_map<char, int> charFrequency(const string& str) {
        unordered_map<char, int> freq;
        for (char c : str) {
            freq[c]++;
        }
        return freq;
    }
    
    // Remove duplicate characters
    static string removeDuplicates(const string& str) {
        unordered_set<char> seen;
        string result;
        for (char c : str) {
            if (seen.find(c) == seen.end()) {
                seen.insert(c);
                result += c;
            }
        }
        return result;
    }
};

void stringOperationsDemo() {
    cout << "\n=== STRING OPERATIONS ===" << endl;
    
    string test = "Hello World";
    cout << "Original: " << test << endl;
    
    // Remove spaces
    cout << "Remove spaces: " << StringManipulator::removeSpaces(test) << endl;
    
    // Reverse
    string reversed = test;
    StringManipulator::reverseString(reversed);
    cout << "Reversed: " << reversed << endl;
    
    // Palindrome check
    string palindrome = "racecar";
    cout << palindrome << " is palindrome: " << 
         StringManipulator::isPalindrome(palindrome) << endl;
    
    // Case conversion
    cout << "Uppercase: " << StringManipulator::toUpper(test) << endl;
    cout << "Lowercase: " << StringManipulator::toLower(test) << endl;
    
    // Character frequency
    auto freq = StringManipulator::charFrequency(test);
    cout << "Character frequencies:" << endl;
    for (auto& p : freq) {
        cout << "  '" << p.first << "': " << p.second << endl;
    }
    
    // Remove duplicates
    string duplicates = "programming";
    cout << "Remove duplicates from '" << duplicates << "': " << 
         StringManipulator::removeDuplicates(duplicates) << endl;
}

// ========================================================================
// 3. STRING SEARCHING ALGORITHMS
// ========================================================================

/*
 * THEORY: String Searching Algorithms
 * 
 * 1. Naive Search: O(n*m) - check every position
 * 2. KMP Algorithm: O(n+m) - uses failure function
 * 3. Boyer-Moore: O(n/m) best case - skip characters
 * 4. Rabin-Karp: O(n+m) average - rolling hash
 */

class StringSearcher {
public:
    // Naive string search - O(n*m)
    static vector<int> naiveSearch(const string& text, const string& pattern) {
        vector<int> matches;
        int n = text.length();
        int m = pattern.length();
        
        for (int i = 0; i <= n - m; i++) {
            bool match = true;
            for (int j = 0; j < m; j++) {
                if (text[i + j] != pattern[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                matches.push_back(i);
            }
        }
        return matches;
    }
    
    // KMP Algorithm - O(n+m)
    static vector<int> computeLPS(const string& pattern) {
        int m = pattern.length();
        vector<int> lps(m, 0);
        int len = 0;
        int i = 1;
        
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
    
    static vector<int> KMPSearch(const string& text, const string& pattern) {
        vector<int> matches;
        int n = text.length();
        int m = pattern.length();
        
        vector<int> lps = computeLPS(pattern);
        
        int i = 0; // index for text
        int j = 0; // index for pattern
        
        while (i < n) {
            if (pattern[j] == text[i]) {
                i++;
                j++;
            }
            
            if (j == m) {
                matches.push_back(i - j);
                j = lps[j - 1];
            } else if (i < n && pattern[j] != text[i]) {
                if (j != 0) {
                    j = lps[j - 1];
                } else {
                    i++;
                }
            }
        }
        return matches;
    }
    
    // Rabin-Karp Algorithm - O(n+m) average
    static vector<int> rabinKarpSearch(const string& text, const string& pattern) {
        vector<int> matches;
        int n = text.length();
        int m = pattern.length();
        int d = 256; // number of characters in alphabet
        int q = 101; // prime number
        
        int p = 0; // hash value for pattern
        int t = 0; // hash value for text
        int h = 1;
        
        // Calculate h = pow(d, m-1) % q
        for (int i = 0; i < m - 1; i++) {
            h = (h * d) % q;
        }
        
        // Calculate hash value for pattern and first window
        for (int i = 0; i < m; i++) {
            p = (d * p + pattern[i]) % q;
            t = (d * t + text[i]) % q;
        }
        
        // Slide pattern over text
        for (int i = 0; i <= n - m; i++) {
            if (p == t) {
                // Check character by character
                bool match = true;
                for (int j = 0; j < m; j++) {
                    if (text[i + j] != pattern[j]) {
                        match = false;
                        break;
                    }
                }
                if (match) {
                    matches.push_back(i);
                }
            }
            
            // Calculate hash for next window
            if (i < n - m) {
                t = (d * (t - text[i] * h) + text[i + m]) % q;
                if (t < 0) {
                    t = t + q;
                }
            }
        }
        return matches;
    }
};

void stringSearchDemo() {
    cout << "\n=== STRING SEARCHING ===" << endl;
    
    string text = "ABABDABACDABABCABCABCABCABC";
    string pattern = "ABABCABCABCABC";
    
    cout << "Text: " << text << endl;
    cout << "Pattern: " << pattern << endl;
    
    // Naive search
    auto matches1 = StringSearcher::naiveSearch(text, pattern);
    cout << "Naive search matches: ";
    for (int pos : matches1) {
        cout << pos << " ";
    }
    cout << endl;
    
    // KMP search
    auto matches2 = StringSearcher::KMPSearch(text, pattern);
    cout << "KMP search matches: ";
    for (int pos : matches2) {
        cout << pos << " ";
    }
    cout << endl;
    
    // Rabin-Karp search
    auto matches3 = StringSearcher::rabinKarpSearch(text, pattern);
    cout << "Rabin-Karp matches: ";
    for (int pos : matches3) {
        cout << pos << " ";
    }
    cout << endl;
}

// ========================================================================
// 4. PATTERN MATCHING AND REGULAR EXPRESSIONS
// ========================================================================

/*
 * THEORY: Pattern Matching
 * 
 * 1. Wildcards: '?' matches any single character, '*' matches any sequence
 * 2. Regular expressions: powerful pattern matching language
 * 3. Dynamic programming approaches for complex patterns
 */

class PatternMatcher {
public:
    // Wildcard pattern matching - O(n*m)
    static bool wildcardMatch(const string& text, const string& pattern) {
        int n = text.length();
        int m = pattern.length();
        
        // DP table
        vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));
        
        // Base case
        dp[0][0] = true;
        
        // Handle patterns with '*' at the beginning
        for (int j = 1; j <= m; j++) {
            if (pattern[j - 1] == '*') {
                dp[0][j] = dp[0][j - 1];
            }
        }
        
        // Fill DP table
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (pattern[j - 1] == '*') {
                    dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
                } else if (pattern[j - 1] == '?' || text[i - 1] == pattern[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                }
            }
        }
        
        return dp[n][m];
    }
    
    // Regular expression matching
    static bool regexMatch(const string& text, const string& pattern) {
        int n = text.length();
        int m = pattern.length();
        
        vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));
        dp[0][0] = true;
        
        // Handle patterns like a*, a*b*, a*b*c*
        for (int j = 2; j <= m; j += 2) {
            if (pattern[j - 1] == '*') {
                dp[0][j] = dp[0][j - 2];
            }
        }
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (pattern[j - 1] == '*') {
                    dp[i][j] = dp[i][j - 2];
                    if (pattern[j - 2] == '.' || pattern[j - 2] == text[i - 1]) {
                        dp[i][j] = dp[i][j] || dp[i - 1][j];
                    }
                } else if (pattern[j - 1] == '.' || pattern[j - 1] == text[i - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                }
            }
        }
        
        return dp[n][m];
    }
};

void patternMatchingDemo() {
    cout << "\n=== PATTERN MATCHING ===" << endl;
    
    // Wildcard matching
    string text1 = "adceb";
    string pattern1 = "*a*b*";
    cout << "Wildcard match '" << text1 << "' with '" << pattern1 << "': " << 
         PatternMatcher::wildcardMatch(text1, pattern1) << endl;
    
    // Regular expression matching
    string text2 = "mississippi";
    string pattern2 = "mis*is*p*.";
    cout << "Regex match '" << text2 << "' with '" << pattern2 << "': " << 
         PatternMatcher::regexMatch(text2, pattern2) << endl;
    
    // Using std::regex
    regex email_pattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    string email = "user@example.com";
    cout << "Email validation: " << regex_match(email, email_pattern) << endl;
}

// ========================================================================
// 5. STRING PARSING AND TOKENIZATION
// ========================================================================

/*
 * THEORY: String Parsing
 * 
 * 1. Tokenization: splitting string into tokens
 * 2. Delimiter-based parsing
 * 3. State machine parsing
 * 4. Recursive descent parsing
 */

class StringParser {
public:
    // Split string by delimiter
    static vector<string> split(const string& str, char delimiter) {
        vector<string> tokens;
        stringstream ss(str);
        string token;
        
        while (getline(ss, token, delimiter)) {
            tokens.push_back(token);
        }
        
        return tokens;
    }
    
    // Split by any whitespace
    static vector<string> splitByWhitespace(const string& str) {
        vector<string> tokens;
        stringstream ss(str);
        string token;
        
        while (ss >> token) {
            tokens.push_back(token);
        }
        
        return tokens;
    }
    
    // Parse CSV line
    static vector<string> parseCSV(const string& line) {
        vector<string> tokens;
        string token;
        bool inQuotes = false;
        
        for (char c : line) {
            if (c == '"') {
                inQuotes = !inQuotes;
            } else if (c == ',' && !inQuotes) {
                tokens.push_back(token);
                token.clear();
            } else {
                token += c;
            }
        }
        
        tokens.push_back(token);
        return tokens;
    }
    
    // Extract numbers from string
    static vector<int> extractNumbers(const string& str) {
        vector<int> numbers;
        string num;
        
        for (char c : str) {
            if (isdigit(c)) {
                num += c;
            } else {
                if (!num.empty()) {
                    numbers.push_back(stoi(num));
                    num.clear();
                }
            }
        }
        
        if (!num.empty()) {
            numbers.push_back(stoi(num));
        }
        
        return numbers;
    }
    
    // Simple expression evaluator
    static int evaluateExpression(const string& expr) {
        // Remove spaces
        string clean;
        for (char c : expr) {
            if (c != ' ') clean += c;
        }
        
        // Simple left-to-right evaluation
        int result = 0;
        int num = 0;
        char op = '+';
        
        for (char c : clean + '+') {
            if (isdigit(c)) {
                num = num * 10 + (c - '0');
            } else {
                if (op == '+') result += num;
                else if (op == '-') result -= num;
                else if (op == '*') result *= num;
                else if (op == '/') result /= num;
                
                num = 0;
                op = c;
            }
        }
        
        return result;
    }
};

void stringParsingDemo() {
    cout << "\n=== STRING PARSING ===" << endl;
    
    // Split by delimiter
    string data = "apple,banana,cherry,date";
    auto fruits = StringParser::split(data, ',');
    cout << "Split fruits: ";
    for (const string& fruit : fruits) {
        cout << fruit << " ";
    }
    cout << endl;
    
    // Split by whitespace
    string sentence = "Hello   world  from   C++";
    auto words = StringParser::splitByWhitespace(sentence);
    cout << "Words: ";
    for (const string& word : words) {
        cout << word << " ";
    }
    cout << endl;
    
    // Parse CSV
    string csvLine = R"(John,"Doe, Jr.",25,"Software Engineer")";
    auto csvFields = StringParser::parseCSV(csvLine);
    cout << "CSV fields: ";
    for (const string& field : csvFields) {
        cout << "[" << field << "] ";
    }
    cout << endl;
    
    // Extract numbers
    string text = "I have 10 apples and 20 oranges, total 30 fruits";
    auto numbers = StringParser::extractNumbers(text);
    cout << "Numbers: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    // Simple expression evaluation
    string expr = "10 + 5 * 2 - 3";
    cout << "Expression '" << expr << "' = " << StringParser::evaluateExpression(expr) << endl;
}

// ========================================================================
// 6. COMMON STRING PROBLEMS
// ========================================================================

/*
 * THEORY: Common String Problem Categories
 * 
 * 1. Anagrams and permutations
 * 2. Longest common subsequence/substring
 * 3. String transformation problems
 * 4. Palindrome problems
 * 5. String compression and encoding
 */

class StringProblems {
public:
    // Check if two strings are anagrams
    static bool areAnagrams(const string& str1, const string& str2) {
        if (str1.length() != str2.length()) return false;
        
        unordered_map<char, int> freq;
        for (char c : str1) freq[c]++;
        for (char c : str2) freq[c]--;
        
        for (auto& p : freq) {
            if (p.second != 0) return false;
        }
        return true;
    }
    
    // Find all anagrams of a string in another string
    static vector<int> findAnagrams(const string& s, const string& p) {
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
    
    // Longest common subsequence
    static int longestCommonSubsequence(const string& str1, const string& str2) {
        int m = str1.length(), n = str2.length();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (str1[i - 1] == str2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        
        return dp[m][n];
    }
    
    // Longest common substring
    static int longestCommonSubstring(const string& str1, const string& str2) {
        int m = str1.length(), n = str2.length();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        int maxLen = 0;
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (str1[i - 1] == str2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                    maxLen = max(maxLen, dp[i][j]);
                } else {
                    dp[i][j] = 0;
                }
            }
        }
        
        return maxLen;
    }
    
    // String compression
    static string compress(const string& str) {
        if (str.empty()) return str;
        
        string compressed;
        int count = 1;
        
        for (int i = 1; i < str.length(); i++) {
            if (str[i] == str[i - 1]) {
                count++;
            } else {
                compressed += str[i - 1];
                if (count > 1) {
                    compressed += to_string(count);
                }
                count = 1;
            }
        }
        
        // Add last character
        compressed += str.back();
        if (count > 1) {
            compressed += to_string(count);
        }
        
        return compressed.length() < str.length() ? compressed : str;
    }
    
    // Longest palindromic substring
    static string longestPalindrome(const string& s) {
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
    static int expandAroundCenter(const string& s, int left, int right) {
        while (left >= 0 && right < s.length() && s[left] == s[right]) {
            left--;
            right++;
        }
        return right - left - 1;
    }
};

void stringProblemsDemo() {
    cout << "\n=== STRING PROBLEMS ===" << endl;
    
    // Anagram check
    string str1 = "listen", str2 = "silent";
    cout << "'" << str1 << "' and '" << str2 << "' are anagrams: " << 
         StringProblems::areAnagrams(str1, str2) << endl;
    
    // Find anagrams
    string s = "abab", p = "ab";
    auto anagrams = StringProblems::findAnagrams(s, p);
    cout << "Anagrams of '" << p << "' in '" << s << "' at positions: ";
    for (int pos : anagrams) {
        cout << pos << " ";
    }
    cout << endl;
    
    // Longest common subsequence
    string lcs1 = "ABCDGH", lcs2 = "AEDFHR";
    cout << "LCS of '" << lcs1 << "' and '" << lcs2 << "': " << 
         StringProblems::longestCommonSubsequence(lcs1, lcs2) << endl;
    
    // Longest common substring
    string lcss1 = "GeeksforGeeks", lcss2 = "GeeksQuiz";
    cout << "Longest common substring length: " << 
         StringProblems::longestCommonSubstring(lcss1, lcss2) << endl;
    
    // String compression
    string toCompress = "aabcccccaaa";
    cout << "Compressed '" << toCompress << "': " << 
         StringProblems::compress(toCompress) << endl;
    
    // Longest palindrome
    string palindromeStr = "babad";
    cout << "Longest palindrome in '" << palindromeStr << "': " << 
         StringProblems::longestPalindrome(palindromeStr) << endl;
}

// ========================================================================
// 7. ADVANCED STRING ALGORITHMS
// ========================================================================

/*
 * THEORY: Advanced String Algorithms
 * 
 * 1. Suffix arrays and trees
 * 2. String hashing and rolling hash
 * 3. Aho-Corasick algorithm for multiple pattern matching
 * 4. Manacher's algorithm for palindromes
 */

class AdvancedStringAlgorithms {
public:
    // Rolling hash for string comparison
    static bool rabinKarpCompare(const string& s1, const string& s2) {
        if (s1.length() != s2.length()) return false;
        
        const int MOD = 1e9 + 7;
        const int BASE = 31;
        
        long long hash1 = 0, hash2 = 0;
        long long power = 1;
        
        for (int i = 0; i < s1.length(); i++) {
            hash1 = (hash1 + (s1[i] - 'a' + 1) * power) % MOD;
            hash2 = (hash2 + (s2[i] - 'a' + 1) * power) % MOD;
            power = (power * BASE) % MOD;
        }
        
        return hash1 == hash2;
    }
    
    // Manacher's algorithm for all palindromes
    static vector<int> manacher(const string& s) {
        string T = "#";
        for (char c : s) {
            T += c;
            T += "#";
        }
        
        int n = T.length();
        vector<int> P(n);
        int center = 0, right = 0;
        
        for (int i = 0; i < n; i++) {
            int mirror = 2 * center - i;
            
            if (i < right) {
                P[i] = min(right - i, P[mirror]);
            }
            
            // Try to expand palindrome centered at i
            while (i + P[i] + 1 < n && i - P[i] - 1 >= 0 && 
                   T[i + P[i] + 1] == T[i - P[i] - 1]) {
                P[i]++;
            }
            
            // If palindrome centered at i extends past right, adjust center and right
            if (i + P[i] > right) {
                center = i;
                right = i + P[i];
            }
        }
        
        return P;
    }
    
    // Z-algorithm for pattern matching
    static vector<int> zAlgorithm(const string& s) {
        int n = s.length();
        vector<int> z(n);
        int left = 0, right = 0;
        
        for (int i = 1; i < n; i++) {
            if (i <= right) {
                z[i] = min(right - i + 1, z[i - left]);
            }
            
            while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
                z[i]++;
            }
            
            if (i + z[i] - 1 > right) {
                left = i;
                right = i + z[i] - 1;
            }
        }
        
        return z;
    }
    
    // Suffix array construction (simple O(n^2 log n) version)
    static vector<int> buildSuffixArray(const string& s) {
        int n = s.length();
        vector<pair<string, int>> suffixes;
        
        for (int i = 0; i < n; i++) {
            suffixes.push_back({s.substr(i), i});
        }
        
        sort(suffixes.begin(), suffixes.end());
        
        vector<int> suffixArray;
        for (auto& suffix : suffixes) {
            suffixArray.push_back(suffix.second);
        }
        
        return suffixArray;
    }
};

void advancedStringAlgorithmsDemo() {
    cout << "\n=== ADVANCED STRING ALGORITHMS ===" << endl;
    
    // Rolling hash comparison
    string s1 = "hello", s2 = "hello";
    cout << "Rolling hash comparison: " << 
         AdvancedStringAlgorithms::rabinKarpCompare(s1, s2) << endl;
    
    // Manacher's algorithm
    string palindromeTest = "ababa";
    auto manacherResult = AdvancedStringAlgorithms::manacher(palindromeTest);
    cout << "Manacher result for '" << palindromeTest << "': ";
    for (int val : manacherResult) {
        cout << val << " ";
    }
    cout << endl;
    
    // Z-algorithm
    string zTest = "aaabaaaa";
    auto zResult = AdvancedStringAlgorithms::zAlgorithm(zTest);
    cout << "Z-algorithm result for '" << zTest << "': ";
    for (int val : zResult) {
        cout << val << " ";
    }
    cout << endl;
    
    // Suffix array
    string suffixTest = "banana";
    auto suffixArray = AdvancedStringAlgorithms::buildSuffixArray(suffixTest);
    cout << "Suffix array for '" << suffixTest << "': ";
    for (int idx : suffixArray) {
        cout << idx << " ";
    }
    cout << endl;
}

// ========================================================================
// 8. PRACTICE EXERCISES
// ========================================================================

/*
 * PRACTICE PROBLEMS:
 * 
 * 1. Valid Anagram
 * 2. Group Anagrams
 * 3. Longest Substring Without Repeating Characters
 * 4. Minimum Window Substring
 * 5. Valid Palindrome
 * 6. Palindromic Substrings
 * 7. Implement strStr()
 * 8. String to Integer (atoi)
 * 9. Zigzag Conversion
 * 10. Text Justification
 */

class StringExercises {
public:
    // Exercise 1: Longest substring without repeating characters
    static int lengthOfLongestSubstring(const string& s) {
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
    
    // Exercise 2: Group anagrams
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
    
    // Exercise 3: Minimum window substring
    static string minWindow(const string& s, const string& t) {
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
    
    // Exercise 4: Count palindromic substrings
    static int countSubstrings(const string& s) {
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
    static int countPalindromesAroundCenter(const string& s, int left, int right) {
        int count = 0;
        while (left >= 0 && right < s.length() && s[left] == s[right]) {
            count++;
            left--;
            right++;
        }
        return count;
    }
};

void practiceExercisesDemo() {
    cout << "\n=== PRACTICE EXERCISES ===" << endl;
    
    // Exercise 1: Longest substring without repeating characters
    string s1 = "abcabcbb";
    cout << "Longest substring without repeating chars in '" << s1 << "': " << 
         StringExercises::lengthOfLongestSubstring(s1) << endl;
    
    // Exercise 2: Group anagrams
    vector<string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};
    auto groups = StringExercises::groupAnagrams(strs);
    cout << "Anagram groups:" << endl;
    for (auto& group : groups) {
        cout << "  [";
        for (int i = 0; i < group.size(); i++) {
            cout << group[i];
            if (i < group.size() - 1) cout << ", ";
        }
        cout << "]" << endl;
    }
    
    // Exercise 3: Minimum window substring
    string s = "ADOBECODEBANC", t = "ABC";
    cout << "Minimum window substring of '" << t << "' in '" << s << "': " << 
         StringExercises::minWindow(s, t) << endl;
    
    // Exercise 4: Count palindromic substrings
    string palindromes = "abc";
    cout << "Palindromic substrings in '" << palindromes << "': " << 
         StringExercises::countSubstrings(palindromes) << endl;
}

// ========================================================================
// MAIN FUNCTION - DEMONSTRATION
// ========================================================================

int main() {
    cout << "STRING ALGORITHMS AND FUNDAMENTALS" << endl;
    cout << "===================================" << endl;
    
    try {
        // Run all demonstrations
        stringFundamentals();
        stringOperationsDemo();
        stringSearchDemo();
        patternMatchingDemo();
        stringParsingDemo();
        stringProblemsDemo();
        advancedStringAlgorithmsDemo();
        practiceExercisesDemo();
        
        cout << "\n=== SUMMARY ===" << endl;
        cout << "✓ String fundamentals and operations" << endl;
        cout << "✓ String searching algorithms (Naive, KMP, Rabin-Karp)" << endl;
        cout << "✓ Pattern matching and regular expressions" << endl;
        cout << "✓ String parsing and tokenization" << endl;
        cout << "✓ Common string problems and solutions" << endl;
        cout << "✓ Advanced string algorithms" << endl;
        cout << "✓ Practice exercises and implementations" << endl;
        
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}

/*
 * COMPILATION AND EXECUTION:
 * 
 * To compile: g++ -std=c++17 -O2 -o string_algorithms string_algorithms.cpp
 * To run: ./string_algorithms
 * 
 * ADDITIONAL RESOURCES:
 * - C++ Reference: https://en.cppreference.com/w/cpp/string
 * - String algorithms: https://www.geeksforgeeks.org/string-data-structure/
 * - Regular expressions: https://www.cplusplus.com/reference/regex/
 * 
 * NEXT STEPS:
 * 1. Practice more string problems on coding platforms
 * 2. Implement string algorithms from scratch
 * 3. Learn about suffix trees and arrays
 * 4. Explore text processing and natural language processing
 */
