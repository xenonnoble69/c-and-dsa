/*
 * ============================================================================
 * ARRAY FUNDAMENTALS - COMPREHENSIVE GUIDE
 * ============================================================================
 * 
 * THEORY:
 * Arrays are fundamental data structures that store elements of the same type
 * in contiguous memory locations. They provide constant-time access to elements
 * using indices and form the foundation for more complex data structures.
 * 
 * KEY CONCEPTS:
 * 
 * 1. ARRAY PROPERTIES:
 *    - Fixed size (static arrays) or dynamic size (dynamic arrays)
 *    - Homogeneous elements (same data type)
 *    - Contiguous memory allocation
 *    - Zero-based indexing in C++
 *    - Cache-friendly due to spatial locality
 * 
 * 2. TYPES OF ARRAYS:
 *    - Static Arrays: int arr[100] - size fixed at compile time
 *    - Dynamic Arrays: vector<int> arr - size can change at runtime
 *    - Multi-dimensional Arrays: int arr[10][20] - arrays of arrays
 * 
 * 3. TIME COMPLEXITIES:
 *    - Access: O(1) - direct index access
 *    - Search: O(n) - linear search, O(log n) - binary search (sorted)
 *    - Insertion: O(n) - worst case (need to shift elements)
 *    - Deletion: O(n) - worst case (need to shift elements)
 * 
 * 4. COMMON ALGORITHMS:
 *    - Searching: Linear search, Binary search
 *    - Sorting: Bubble, Selection, Insertion, Merge, Quick sort
 *    - Two Pointers: Efficient for many array problems
 *    - Sliding Window: For subarray problems
 *    - Prefix Sum: For range sum queries
 * 
 * 5. PROBLEM PATTERNS:
 *    - Array manipulation and traversal
 *    - Subarray problems (maximum sum, sliding window)
 *    - Two-pointer techniques
 *    - Sorting and searching variations
 *    - Matrix operations
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <chrono>
#include <random>
#include <iomanip>

using namespace std;
using namespace std::chrono;

/*
 * ========================================================================
 * 1. BASIC ARRAY OPERATIONS
 * ========================================================================
 */

class ArrayOperations {
public:
    // Initialize array with random values
    static void initializeArray(vector<int>& arr, int size, int minVal = 1, int maxVal = 100) {
        arr.resize(size);
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(minVal, maxVal);
        
        for (int& num : arr) {
            num = dis(gen);
        }
    }
    
    // Display array elements
    static void displayArray(const vector<int>& arr, const string& label = "Array") {
        cout << label << ": [";
        for (size_t i = 0; i < arr.size(); ++i) {
            cout << arr[i];
            if (i < arr.size() - 1) cout << ", ";
        }
        cout << "]" << endl;
    }
    
    // Linear search
    static int linearSearch(const vector<int>& arr, int target) {
        for (size_t i = 0; i < arr.size(); ++i) {
            if (arr[i] == target) {
                return static_cast<int>(i);
            }
        }
        return -1;  // Not found
    }
    
    // Binary search (requires sorted array)
    static int binarySearch(const vector<int>& arr, int target) {
        int left = 0, right = static_cast<int>(arr.size()) - 1;
        
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
        return -1;  // Not found
    }
    
    // Find maximum element
    static int findMaximum(const vector<int>& arr) {
        if (arr.empty()) return INT_MIN;
        
        int maxVal = arr[0];
        for (size_t i = 1; i < arr.size(); ++i) {
            maxVal = max(maxVal, arr[i]);
        }
        return maxVal;
    }
    
    // Find minimum element
    static int findMinimum(const vector<int>& arr) {
        if (arr.empty()) return INT_MAX;
        
        int minVal = arr[0];
        for (size_t i = 1; i < arr.size(); ++i) {
            minVal = min(minVal, arr[i]);
        }
        return minVal;
    }
    
    // Calculate sum of elements
    static long long calculateSum(const vector<int>& arr) {
        return accumulate(arr.begin(), arr.end(), 0LL);
    }
    
    // Reverse array in-place
    static void reverseArray(vector<int>& arr) {
        int left = 0, right = static_cast<int>(arr.size()) - 1;
        
        while (left < right) {
            swap(arr[left], arr[right]);
            left++;
            right--;
        }
    }
    
    // Rotate array to the right by k positions
    static void rotateRight(vector<int>& arr, int k) {
        int n = static_cast<int>(arr.size());
        if (n == 0) return;
        
        k = k % n;  // Handle k > n
        
        // Reverse entire array
        reverse(arr.begin(), arr.end());
        // Reverse first k elements
        reverse(arr.begin(), arr.begin() + k);
        // Reverse remaining elements
        reverse(arr.begin() + k, arr.end());
    }
};

void demonstrateBasicOperations() {
    cout << "1. BASIC ARRAY OPERATIONS" << endl;
    cout << "==========================" << endl;
    
    // Initialize and display array
    vector<int> arr;
    ArrayOperations::initializeArray(arr, 10, 1, 20);
    ArrayOperations::displayArray(arr, "Original Array");
    
    // Search operations
    int target = arr[3];  // Pick an element that exists
    cout << "\nSearching for " << target << ":" << endl;
    
    auto start = high_resolution_clock::now();
    int linearResult = ArrayOperations::linearSearch(arr, target);
    auto linearTime = high_resolution_clock::now() - start;
    
    cout << "Linear search result: index " << linearResult << endl;
    cout << "Linear search time: " << duration_cast<nanoseconds>(linearTime).count() << " ns" << endl;
    
    // Sort for binary search
    vector<int> sortedArr = arr;
    sort(sortedArr.begin(), sortedArr.end());
    ArrayOperations::displayArray(sortedArr, "Sorted Array");
    
    start = high_resolution_clock::now();
    int binaryResult = ArrayOperations::binarySearch(sortedArr, target);
    auto binaryTime = high_resolution_clock::now() - start;
    
    cout << "Binary search result: index " << binaryResult << endl;
    cout << "Binary search time: " << duration_cast<nanoseconds>(binaryTime).count() << " ns" << endl;
    
    // Statistical operations
    cout << "\nArray Statistics:" << endl;
    cout << "Maximum: " << ArrayOperations::findMaximum(arr) << endl;
    cout << "Minimum: " << ArrayOperations::findMinimum(arr) << endl;
    cout << "Sum: " << ArrayOperations::calculateSum(arr) << endl;
    cout << "Average: " << static_cast<double>(ArrayOperations::calculateSum(arr)) / arr.size() << endl;
    
    // Array manipulation
    cout << "\nArray Manipulation:" << endl;
    vector<int> copyArr = arr;
    
    ArrayOperations::reverseArray(copyArr);
    ArrayOperations::displayArray(copyArr, "Reversed Array");
    
    copyArr = arr;  // Reset
    ArrayOperations::rotateRight(copyArr, 3);
    ArrayOperations::displayArray(copyArr, "Rotated Right by 3");
    
    cout << endl;
}

/*
 * ========================================================================
 * 2. SORTING ALGORITHMS
 * ========================================================================
 */

class SortingAlgorithms {
public:
    // Bubble Sort - O(n²) time, O(1) space
    static void bubbleSort(vector<int>& arr) {
        int n = static_cast<int>(arr.size());
        for (int i = 0; i < n - 1; ++i) {
            bool swapped = false;
            for (int j = 0; j < n - i - 1; ++j) {
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                    swapped = true;
                }
            }
            if (!swapped) break;  // Optimization: early termination
        }
    }
    
    // Selection Sort - O(n²) time, O(1) space
    static void selectionSort(vector<int>& arr) {
        int n = static_cast<int>(arr.size());
        for (int i = 0; i < n - 1; ++i) {
            int minIdx = i;
            for (int j = i + 1; j < n; ++j) {
                if (arr[j] < arr[minIdx]) {
                    minIdx = j;
                }
            }
            if (minIdx != i) {
                swap(arr[i], arr[minIdx]);
            }
        }
    }
    
    // Insertion Sort - O(n²) time, O(1) space, efficient for small arrays
    static void insertionSort(vector<int>& arr) {
        int n = static_cast<int>(arr.size());
        for (int i = 1; i < n; ++i) {
            int key = arr[i];
            int j = i - 1;
            
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }
    
    // Merge Sort - O(n log n) time, O(n) space
    static void mergeSort(vector<int>& arr, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            
            mergeSort(arr, left, mid);
            mergeSort(arr, mid + 1, right);
            merge(arr, left, mid, right);
        }
    }
    
    static void mergeSort(vector<int>& arr) {
        mergeSort(arr, 0, static_cast<int>(arr.size()) - 1);
    }
    
private:
    static void merge(vector<int>& arr, int left, int mid, int right) {
        vector<int> temp(right - left + 1);
        int i = left, j = mid + 1, k = 0;
        
        while (i <= mid && j <= right) {
            if (arr[i] <= arr[j]) {
                temp[k++] = arr[i++];
            } else {
                temp[k++] = arr[j++];
            }
        }
        
        while (i <= mid) temp[k++] = arr[i++];
        while (j <= right) temp[k++] = arr[j++];
        
        for (i = left, k = 0; i <= right; ++i, ++k) {
            arr[i] = temp[k];
        }
    }
    
public:
    // Quick Sort - O(n log n) average, O(n²) worst case, O(log n) space
    static void quickSort(vector<int>& arr, int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }
    
    static void quickSort(vector<int>& arr) {
        quickSort(arr, 0, static_cast<int>(arr.size()) - 1);
    }
    
private:
    static int partition(vector<int>& arr, int low, int high) {
        int pivot = arr[high];
        int i = low - 1;
        
        for (int j = low; j < high; ++j) {
            if (arr[j] < pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        return i + 1;
    }
    
public:
    // Heap Sort - O(n log n) time, O(1) space
    static void heapSort(vector<int>& arr) {
        int n = static_cast<int>(arr.size());
        
        // Build heap
        for (int i = n / 2 - 1; i >= 0; --i) {
            heapify(arr, n, i);
        }
        
        // Extract elements from heap
        for (int i = n - 1; i > 0; --i) {
            swap(arr[0], arr[i]);
            heapify(arr, i, 0);
        }
    }
    
private:
    static void heapify(vector<int>& arr, int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        
        if (left < n && arr[left] > arr[largest]) {
            largest = left;
        }
        
        if (right < n && arr[right] > arr[largest]) {
            largest = right;
        }
        
        if (largest != i) {
            swap(arr[i], arr[largest]);
            heapify(arr, n, largest);
        }
    }
};

void demonstrateSortingAlgorithms() {
    cout << "2. SORTING ALGORITHMS" << endl;
    cout << "=====================" << endl;
    
    const int ARRAY_SIZE = 1000;
    vector<int> originalArr;
    ArrayOperations::initializeArray(originalArr, ARRAY_SIZE, 1, 1000);
    
    cout << "Comparing sorting algorithms with " << ARRAY_SIZE << " elements:" << endl;
    
    // Test each sorting algorithm
    vector<pair<string, function<void(vector<int>&)>>> algorithms = {
        {"Bubble Sort", SortingAlgorithms::bubbleSort},
        {"Selection Sort", SortingAlgorithms::selectionSort},
        {"Insertion Sort", SortingAlgorithms::insertionSort},
        {"Merge Sort", SortingAlgorithms::mergeSort},
        {"Quick Sort", SortingAlgorithms::quickSort},
        {"Heap Sort", SortingAlgorithms::heapSort},
        {"STL Sort", [](vector<int>& arr) { sort(arr.begin(), arr.end()); }}
    };
    
    for (auto& [name, sortFunc] : algorithms) {
        vector<int> testArr = originalArr;
        
        auto start = high_resolution_clock::now();
        sortFunc(testArr);
        auto end = high_resolution_clock::now();
        
        auto duration = duration_cast<microseconds>(end - start);
        
        // Verify sorted
        bool isSorted = is_sorted(testArr.begin(), testArr.end());
        
        cout << setw(15) << name << ": " << setw(8) << duration.count() 
             << " μs, Correct: " << (isSorted ? "✓" : "✗") << endl;
    }
    
    // Demonstrate with small array for visualization
    cout << "\nSorting visualization (small array):" << endl;
    vector<int> smallArr = {64, 34, 25, 12, 22, 11, 90};
    ArrayOperations::displayArray(smallArr, "Original");
    
    SortingAlgorithms::quickSort(smallArr);
    ArrayOperations::displayArray(smallArr, "Quick Sorted");
    
    cout << endl;
}

/*
 * ========================================================================
 * 3. TWO POINTER TECHNIQUES
 * ========================================================================
 */

class TwoPointerTechniques {
public:
    // Two Sum problem - find pair with given sum
    static vector<int> twoSum(const vector<int>& arr, int target) {
        unordered_map<int, int> numMap;
        
        for (int i = 0; i < static_cast<int>(arr.size()); ++i) {
            int complement = target - arr[i];
            if (numMap.find(complement) != numMap.end()) {
                return {numMap[complement], i};
            }
            numMap[arr[i]] = i;
        }
        return {};  // No solution found
    }
    
    // Two Sum in sorted array using two pointers
    static vector<int> twoSumSorted(const vector<int>& arr, int target) {
        int left = 0, right = static_cast<int>(arr.size()) - 1;
        
        while (left < right) {
            int currentSum = arr[left] + arr[right];
            if (currentSum == target) {
                return {left, right};
            } else if (currentSum < target) {
                left++;
            } else {
                right--;
            }
        }
        return {};  // No solution found
    }
    
    // Three Sum - find triplets with sum = 0
    static vector<vector<int>> threeSum(vector<int> arr) {
        vector<vector<int>> result;
        sort(arr.begin(), arr.end());
        int n = static_cast<int>(arr.size());
        
        for (int i = 0; i < n - 2; ++i) {
            if (i > 0 && arr[i] == arr[i - 1]) continue;  // Skip duplicates
            
            int left = i + 1, right = n - 1;
            while (left < right) {
                int sum = arr[i] + arr[left] + arr[right];
                if (sum == 0) {
                    result.push_back({arr[i], arr[left], arr[right]});
                    
                    // Skip duplicates
                    while (left < right && arr[left] == arr[left + 1]) left++;
                    while (left < right && arr[right] == arr[right - 1]) right--;
                    
                    left++;
                    right--;
                } else if (sum < 0) {
                    left++;
                } else {
                    right--;
                }
            }
        }
        return result;
    }
    
    // Container with most water
    static int maxArea(const vector<int>& height) {
        int maxWater = 0;
        int left = 0, right = static_cast<int>(height.size()) - 1;
        
        while (left < right) {
            int currentArea = min(height[left], height[right]) * (right - left);
            maxWater = max(maxWater, currentArea);
            
            if (height[left] < height[right]) {
                left++;
            } else {
                right--;
            }
        }
        return maxWater;
    }
    
    // Remove duplicates from sorted array
    static int removeDuplicates(vector<int>& arr) {
        if (arr.empty()) return 0;
        
        int writeIndex = 1;
        for (int i = 1; i < static_cast<int>(arr.size()); ++i) {
            if (arr[i] != arr[i - 1]) {
                arr[writeIndex++] = arr[i];
            }
        }
        return writeIndex;
    }
    
    // Move zeros to end
    static void moveZeros(vector<int>& arr) {
        int writeIndex = 0;
        
        // Move all non-zero elements to front
        for (int num : arr) {
            if (num != 0) {
                arr[writeIndex++] = num;
            }
        }
        
        // Fill remaining positions with zeros
        while (writeIndex < static_cast<int>(arr.size())) {
            arr[writeIndex++] = 0;
        }
    }
};

void demonstrateTwoPointerTechniques() {
    cout << "3. TWO POINTER TECHNIQUES" << endl;
    cout << "==========================" << endl;
    
    // Two Sum problem
    cout << "Two Sum Problem:" << endl;
    vector<int> nums1 = {2, 7, 11, 15};
    int target1 = 9;
    
    ArrayOperations::displayArray(nums1, "Array");
    cout << "Target: " << target1 << endl;
    
    auto result1 = TwoPointerTechniques::twoSum(nums1, target1);
    if (!result1.empty()) {
        cout << "Two Sum indices: [" << result1[0] << ", " << result1[1] << "]" << endl;
        cout << "Values: " << nums1[result1[0]] << " + " << nums1[result1[1]] << " = " << target1 << endl;
    }
    
    // Two Sum in sorted array
    vector<int> sortedNums = {1, 2, 3, 4, 6};
    int target2 = 6;
    cout << "\nTwo Sum in Sorted Array:" << endl;
    ArrayOperations::displayArray(sortedNums, "Sorted Array");
    cout << "Target: " << target2 << endl;
    
    auto result2 = TwoPointerTechniques::twoSumSorted(sortedNums, target2);
    if (!result2.empty()) {
        cout << "Two Sum indices: [" << result2[0] << ", " << result2[1] << "]" << endl;
    }
    
    // Three Sum problem
    cout << "\nThree Sum Problem:" << endl;
    vector<int> nums3 = {-1, 0, 1, 2, -1, -4};
    ArrayOperations::displayArray(nums3, "Array");
    
    auto result3 = TwoPointerTechniques::threeSum(nums3);
    cout << "Three Sum triplets:" << endl;
    for (const auto& triplet : result3) {
        cout << "[" << triplet[0] << ", " << triplet[1] << ", " << triplet[2] << "]" << endl;
    }
    
    // Container with most water
    cout << "\nContainer With Most Water:" << endl;
    vector<int> heights = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    ArrayOperations::displayArray(heights, "Heights");
    
    int maxWater = TwoPointerTechniques::maxArea(heights);
    cout << "Maximum water: " << maxWater << endl;
    
    // Remove duplicates
    cout << "\nRemove Duplicates:" << endl;
    vector<int> withDuplicates = {1, 1, 2, 2, 2, 3, 4, 4, 5};
    ArrayOperations::displayArray(withDuplicates, "With Duplicates");
    
    int newLength = TwoPointerTechniques::removeDuplicates(withDuplicates);
    cout << "After removing duplicates (length " << newLength << "): [";
    for (int i = 0; i < newLength; ++i) {
        cout << withDuplicates[i];
        if (i < newLength - 1) cout << ", ";
    }
    cout << "]" << endl;
    
    // Move zeros
    cout << "\nMove Zeros to End:" << endl;
    vector<int> withZeros = {0, 1, 0, 3, 12, 0, 5};
    ArrayOperations::displayArray(withZeros, "With Zeros");
    
    TwoPointerTechniques::moveZeros(withZeros);
    ArrayOperations::displayArray(withZeros, "Zeros Moved");
    
    cout << endl;
}

/*
 * ========================================================================
 * 4. SLIDING WINDOW TECHNIQUE
 * ========================================================================
 */

class SlidingWindow {
public:
    // Maximum sum of subarray of size k
    static int maxSumSubarray(const vector<int>& arr, int k) {
        if (static_cast<int>(arr.size()) < k) return -1;
        
        // Calculate sum of first window
        int windowSum = 0;
        for (int i = 0; i < k; ++i) {
            windowSum += arr[i];
        }
        
        int maxSum = windowSum;
        
        // Slide the window
        for (int i = k; i < static_cast<int>(arr.size()); ++i) {
            windowSum += arr[i] - arr[i - k];
            maxSum = max(maxSum, windowSum);
        }
        
        return maxSum;
    }
    
    // Longest substring with at most k distinct characters
    static int longestSubstringKDistinct(const string& s, int k) {
        if (s.empty() || k == 0) return 0;
        
        unordered_map<char, int> charCount;
        int left = 0, maxLength = 0;
        
        for (int right = 0; right < static_cast<int>(s.length()); ++right) {
            charCount[s[right]]++;
            
            while (static_cast<int>(charCount.size()) > k) {
                charCount[s[left]]--;
                if (charCount[s[left]] == 0) {
                    charCount.erase(s[left]);
                }
                left++;
            }
            
            maxLength = max(maxLength, right - left + 1);
        }
        
        return maxLength;
    }
    
    // Minimum window substring
    static string minWindow(const string& s, const string& t) {
        if (s.empty() || t.empty()) return "";
        
        unordered_map<char, int> tCount, windowCount;
        for (char c : t) tCount[c]++;
        
        int left = 0, minLen = INT_MAX, minStart = 0;
        int formed = 0, required = static_cast<int>(tCount.size());
        
        for (int right = 0; right < static_cast<int>(s.length()); ++right) {
            char c = s[right];
            windowCount[c]++;
            
            if (tCount.count(c) && windowCount[c] == tCount[c]) {
                formed++;
            }
            
            while (left <= right && formed == required) {
                if (right - left + 1 < minLen) {
                    minLen = right - left + 1;
                    minStart = left;
                }
                
                char leftChar = s[left];
                windowCount[leftChar]--;
                if (tCount.count(leftChar) && windowCount[leftChar] < tCount[leftChar]) {
                    formed--;
                }
                left++;
            }
        }
        
        return minLen == INT_MAX ? "" : s.substr(minStart, minLen);
    }
    
    // Find all anagrams of pattern in text
    static vector<int> findAnagrams(const string& s, const string& p) {
        vector<int> result;
        if (s.length() < p.length()) return result;
        
        vector<int> pCount(26, 0), windowCount(26, 0);
        
        // Count characters in pattern
        for (char c : p) pCount[c - 'a']++;
        
        int windowSize = static_cast<int>(p.length());
        
        // Process first window
        for (int i = 0; i < windowSize; ++i) {
            windowCount[s[i] - 'a']++;
        }
        
        if (pCount == windowCount) result.push_back(0);
        
        // Slide the window
        for (int i = windowSize; i < static_cast<int>(s.length()); ++i) {
            // Add new character
            windowCount[s[i] - 'a']++;
            // Remove old character
            windowCount[s[i - windowSize] - 'a']--;
            
            if (pCount == windowCount) {
                result.push_back(i - windowSize + 1);
            }
        }
        
        return result;
    }
};

void demonstrateSlidingWindow() {
    cout << "4. SLIDING WINDOW TECHNIQUE" << endl;
    cout << "============================" << endl;
    
    // Maximum sum subarray of size k
    cout << "Maximum Sum Subarray of Size K:" << endl;
    vector<int> arr1 = {2, 1, 5, 1, 3, 2};
    int k1 = 3;
    ArrayOperations::displayArray(arr1, "Array");
    cout << "K = " << k1 << endl;
    cout << "Maximum sum: " << SlidingWindow::maxSumSubarray(arr1, k1) << endl;
    
    // Longest substring with k distinct characters
    cout << "\nLongest Substring with K Distinct Characters:" << endl;
    string s1 = "araaci";
    int k2 = 2;
    cout << "String: \"" << s1 << "\"" << endl;
    cout << "K = " << k2 << endl;
    cout << "Longest length: " << SlidingWindow::longestSubstringKDistinct(s1, k2) << endl;
    
    // Minimum window substring
    cout << "\nMinimum Window Substring:" << endl;
    string s2 = "ADOBECODEBANC";
    string t2 = "ABC";
    cout << "String: \"" << s2 << "\"" << endl;
    cout << "Pattern: \"" << t2 << "\"" << endl;
    cout << "Minimum window: \"" << SlidingWindow::minWindow(s2, t2) << "\"" << endl;
    
    // Find anagrams
    cout << "\nFind All Anagrams:" << endl;
    string s3 = "abab";
    string p3 = "ab";
    cout << "String: \"" << s3 << "\"" << endl;
    cout << "Pattern: \"" << p3 << "\"" << endl;
    
    auto anagramIndices = SlidingWindow::findAnagrams(s3, p3);
    cout << "Anagram start indices: [";
    for (size_t i = 0; i < anagramIndices.size(); ++i) {
        cout << anagramIndices[i];
        if (i < anagramIndices.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    
    cout << endl;
}

/*
 * ========================================================================
 * 5. PREFIX SUM AND RANGE QUERIES
 * ========================================================================
 */

class PrefixSum {
private:
    vector<long long> prefixSum;
    
public:
    // Build prefix sum array
    PrefixSum(const vector<int>& arr) {
        prefixSum.resize(arr.size() + 1, 0);
        for (size_t i = 0; i < arr.size(); ++i) {
            prefixSum[i + 1] = prefixSum[i] + arr[i];
        }
    }
    
    // Range sum query O(1)
    long long rangeSum(int left, int right) {
        return prefixSum[right + 1] - prefixSum[left];
    }
    
    // Subarray sum equals K
    static int subarraySum(const vector<int>& arr, int k) {
        unordered_map<int, int> prefixSumCount;
        prefixSumCount[0] = 1;  // Empty subarray
        
        int count = 0, currentSum = 0;
        for (int num : arr) {
            currentSum += num;
            if (prefixSumCount.count(currentSum - k)) {
                count += prefixSumCount[currentSum - k];
            }
            prefixSumCount[currentSum]++;
        }
        
        return count;
    }
    
    // Maximum subarray sum (Kadane's algorithm)
    static int maxSubarraySum(const vector<int>& arr) {
        int maxSum = arr[0], currentSum = arr[0];
        
        for (size_t i = 1; i < arr.size(); ++i) {
            currentSum = max(arr[i], currentSum + arr[i]);
            maxSum = max(maxSum, currentSum);
        }
        
        return maxSum;
    }
    
    // Product of array except self
    static vector<int> productExceptSelf(const vector<int>& arr) {
        int n = static_cast<int>(arr.size());
        vector<int> result(n, 1);
        
        // Left products
        for (int i = 1; i < n; ++i) {
            result[i] = result[i - 1] * arr[i - 1];
        }
        
        // Right products
        int rightProduct = 1;
        for (int i = n - 1; i >= 0; --i) {
            result[i] *= rightProduct;
            rightProduct *= arr[i];
        }
        
        return result;
    }
};

void demonstratePrefixSum() {
    cout << "5. PREFIX SUM AND RANGE QUERIES" << endl;
    cout << "================================" << endl;
    
    // Range sum queries
    cout << "Range Sum Queries:" << endl;
    vector<int> arr1 = {1, 3, 5, 7, 9, 11};
    ArrayOperations::displayArray(arr1, "Array");
    
    PrefixSum ps(arr1);
    cout << "Range sum [1, 4]: " << ps.rangeSum(1, 4) << endl;
    cout << "Range sum [0, 2]: " << ps.rangeSum(0, 2) << endl;
    cout << "Range sum [3, 5]: " << ps.rangeSum(3, 5) << endl;
    
    // Subarray sum equals K
    cout << "\nSubarray Sum Equals K:" << endl;
    vector<int> arr2 = {1, 1, 1};
    int k = 2;
    ArrayOperations::displayArray(arr2, "Array");
    cout << "K = " << k << endl;
    cout << "Number of subarrays: " << PrefixSum::subarraySum(arr2, k) << endl;
    
    // Maximum subarray sum
    cout << "\nMaximum Subarray Sum (Kadane's Algorithm):" << endl;
    vector<int> arr3 = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    ArrayOperations::displayArray(arr3, "Array");
    cout << "Maximum sum: " << PrefixSum::maxSubarraySum(arr3) << endl;
    
    // Product except self
    cout << "\nProduct of Array Except Self:" << endl;
    vector<int> arr4 = {1, 2, 3, 4};
    ArrayOperations::displayArray(arr4, "Array");
    
    auto products = PrefixSum::productExceptSelf(arr4);
    ArrayOperations::displayArray(products, "Products");
    
    cout << endl;
}

/*
 * ========================================================================
 * MAIN FUNCTION
 * ========================================================================
 */

int main() {
    cout << "=== ARRAY FUNDAMENTALS COMPREHENSIVE GUIDE ===" << endl << endl;
    
    demonstrateBasicOperations();
    demonstrateSortingAlgorithms();
    demonstrateTwoPointerTechniques();
    demonstrateSlidingWindow();
    demonstratePrefixSum();
    
    cout << "=== Array Fundamentals Mastery Complete! ===" << endl;
    
    return 0;
}

/*
 * ============================================================================
 * PRACTICE EXERCISES:
 * ============================================================================
 * 
 * EASY LEVEL:
 * 1. Find the second largest element in an array
 * 2. Rotate array left by k positions
 * 3. Check if array is sorted
 * 4. Find missing number in array 1 to n
 * 5. Remove element in-place
 * 6. Merge two sorted arrays
 * 7. Find intersection of two arrays
 * 8. Plus one (array represents a number)
 * 9. Pascal's triangle generation
 * 10. Valid mountain array
 * 
 * MEDIUM LEVEL:
 * 1. 3Sum closest to target
 * 2. Container with most water
 * 3. Spiral matrix traversal
 * 4. Rotate image (matrix) 90 degrees
 * 5. Set matrix zeros
 * 6. Longest consecutive sequence
 * 7. Find duplicate number
 * 8. Subarray sum equals K
 * 9. Maximum product subarray
 * 10. Next permutation
 * 
 * HARD LEVEL:
 * 1. Median of two sorted arrays
 * 2. Sliding window maximum
 * 3. Minimum window substring
 * 4. First missing positive
 * 5. Trapping rain water
 * 6. Maximum rectangle in histogram
 * 7. Largest rectangle in binary matrix
 * 8. Count of smaller numbers after self
 * 9. Range sum query 2D - mutable
 * 10. Maximum sum of 3 non-overlapping subarrays
 * 
 * ============================================================================
 * ARRAY PROBLEM PATTERNS:
 * ============================================================================
 * 
 * 1. TWO POINTERS:
 *    - Use when dealing with sorted arrays
 *    - Opposite direction: start from both ends
 *    - Same direction: slow and fast pointers
 *    - Problems: Two sum, three sum, remove duplicates
 * 
 * 2. SLIDING WINDOW:
 *    - Fixed size window: for problems with exact size k
 *    - Variable size window: for optimization problems
 *    - Use hash map to track window contents
 *    - Problems: Maximum sum subarray, longest substring
 * 
 * 3. PREFIX SUM:
 *    - Precompute cumulative sums for O(1) range queries
 *    - Use hash map for subarray sum problems
 *    - 2D prefix sum for matrix range queries
 *    - Problems: Range sum, subarray sum equals K
 * 
 * 4. KADANE'S ALGORITHM:
 *    - For maximum/minimum subarray problems
 *    - Dynamic programming approach
 *    - Keep track of current and global optimum
 *    - Problems: Maximum subarray sum, maximum product
 * 
 * 5. HASH MAP/SET:
 *    - For problems requiring lookups
 *    - Track seen elements or counts
 *    - Complement-based searching
 *    - Problems: Two sum, intersection, duplicates
 * 
 * ============================================================================
 * TIME COMPLEXITY ANALYSIS:
 * ============================================================================
 * 
 * ARRAY OPERATIONS:
 * - Access: O(1) - direct indexing
 * - Search: O(n) - linear search, O(log n) - binary search
 * - Insertion: O(n) - worst case, O(1) - amortized for dynamic arrays
 * - Deletion: O(n) - worst case due to shifting
 * - Sorting: O(n log n) - efficient algorithms
 * 
 * ALGORITHM COMPLEXITIES:
 * - Two Pointers: O(n) time, O(1) space
 * - Sliding Window: O(n) time, O(k) space
 * - Prefix Sum: O(n) preprocessing, O(1) query
 * - Hash Map Operations: O(1) average, O(n) worst case
 * 
 * SPACE COMPLEXITY:
 * - In-place algorithms: O(1) extra space
 * - Hash map solutions: O(n) space
 * - Prefix sum: O(n) space
 * - Sorting: O(1) to O(n) depending on algorithm
 * 
 * ============================================================================
 * OPTIMIZATION TECHNIQUES:
 * ============================================================================
 * 
 * 1. SPACE OPTIMIZATION:
 *    - Use two pointers instead of extra arrays
 *    - Modify input array in-place when possible
 *    - Use bit manipulation for boolean arrays
 *    - Compress coordinates for sparse data
 * 
 * 2. TIME OPTIMIZATION:
 *    - Precompute frequently used values
 *    - Use appropriate data structures (hash map vs array)
 *    - Early termination in loops
 *    - Avoid redundant calculations
 * 
 * 3. CACHE OPTIMIZATION:
 *    - Access arrays sequentially when possible
 *    - Use smaller data types when appropriate
 *    - Minimize memory allocations
 *    - Consider memory layout for 2D arrays
 * 
 * ============================================================================
 * COMMON PITFALLS:
 * ============================================================================
 * 
 * 1. INDEX ERRORS:
 *    - Off-by-one errors in loops
 *    - Array bounds checking
 *    - Integer overflow in index calculations
 *    - Negative indices handling
 * 
 * 2. EDGE CASES:
 *    - Empty arrays
 *    - Single element arrays
 *    - All elements same
 *    - Maximum/minimum values
 * 
 * 3. ALGORITHM ISSUES:
 *    - Not handling duplicates properly
 *    - Incorrect termination conditions
 *    - Missing boundary checks
 *    - Incorrect complexity analysis
 * 
 * ============================================================================
 * BEST PRACTICES:
 * ============================================================================
 * 
 * 1. Always validate input (null checks, size checks)
 * 2. Consider edge cases in algorithm design
 * 3. Use meaningful variable names
 * 4. Comment complex algorithms
 * 5. Test with various input sizes
 * 6. Analyze time and space complexity
 * 7. Consider iterative vs recursive approaches
 * 8. Use built-in library functions when appropriate
 * 9. Profile performance for large inputs
 * 10. Write clean, readable code
 * 
 * ============================================================================
 */
