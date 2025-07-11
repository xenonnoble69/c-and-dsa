/*
 * ARRAY PROBLEMS - EASY TO MEDIUM LEVEL
 * ====================================
 * 
 * This file contains 25 carefully selected array problems with detailed solutions.
 * Each problem includes:
 * - Problem statement
 * - Multiple solution approaches
 * - Time and space complexity analysis
 * - Test cases and examples
 * 
 * DIFFICULTY LEVELS:
 * ⭐ Easy (1-8)
 * ⭐⭐ Medium (9-20)
 * ⭐⭐⭐ Hard (21-25)
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <climits>

using namespace std;

// ========================================================================
// PROBLEM 1: TWO SUM ⭐
// ========================================================================
/*
 * Given an array of integers nums and an integer target, return indices of 
 * the two numbers such that they add up to target.
 * 
 * Example: nums = [2,7,11,15], target = 9
 * Output: [0,1] (because nums[0] + nums[1] = 2 + 7 = 9)
 */

class TwoSum {
public:
    // Approach 1: Brute Force - O(n²) time, O(1) space
    static vector<int> twoSumBruteForce(vector<int>& nums, int target) {
        for (int i = 0; i < nums.size(); i++) {
            for (int j = i + 1; j < nums.size(); j++) {
                if (nums[i] + nums[j] == target) {
                    return {i, j};
                }
            }
        }
        return {};
    }
    
    // Approach 2: Hash Map - O(n) time, O(n) space
    static vector<int> twoSumHashMap(vector<int>& nums, int target) {
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
};

// ========================================================================
// PROBLEM 2: BEST TIME TO BUY AND SELL STOCK ⭐
// ========================================================================
/*
 * You are given an array prices where prices[i] is the price of a given stock 
 * on the ith day. You want to maximize your profit by choosing a single day to 
 * buy one stock and choosing a different day in the future to sell that stock.
 */

class BestTimeToBuyStock {
public:
    // O(n) time, O(1) space
    static int maxProfit(vector<int>& prices) {
        int minPrice = INT_MAX;
        int maxProfit = 0;
        
        for (int price : prices) {
            if (price < minPrice) {
                minPrice = price;
            } else if (price - minPrice > maxProfit) {
                maxProfit = price - minPrice;
            }
        }
        
        return maxProfit;
    }
};

// ========================================================================
// PROBLEM 3: CONTAINS DUPLICATE ⭐
// ========================================================================
/*
 * Given an integer array nums, return true if any value appears at least 
 * twice in the array, and return false if every element is distinct.
 */

class ContainsDuplicate {
public:
    // Approach 1: Hash Set - O(n) time, O(n) space
    static bool containsDuplicateHashSet(vector<int>& nums) {
        unordered_set<int> seen;
        for (int num : nums) {
            if (seen.find(num) != seen.end()) {
                return true;
            }
            seen.insert(num);
        }
        return false;
    }
    
    // Approach 2: Sorting - O(n log n) time, O(1) space
    static bool containsDuplicateSort(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] == nums[i-1]) {
                return true;
            }
        }
        return false;
    }
};

// ========================================================================
// PROBLEM 4: PRODUCT OF ARRAY EXCEPT SELF ⭐⭐
// ========================================================================
/*
 * Given an integer array nums, return an array answer such that answer[i] 
 * is equal to the product of all the elements of nums except nums[i].
 * The product is guaranteed to fit in a 32-bit integer.
 * You must write an algorithm that runs in O(n) time and without using 
 * the division operation.
 */

class ProductExceptSelf {
public:
    // O(n) time, O(1) space (excluding output array)
    static vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> result(n, 1);
        
        // First pass: calculate left products
        for (int i = 1; i < n; i++) {
            result[i] = result[i-1] * nums[i-1];
        }
        
        // Second pass: multiply by right products
        int rightProduct = 1;
        for (int i = n-1; i >= 0; i--) {
            result[i] *= rightProduct;
            rightProduct *= nums[i];
        }
        
        return result;
    }
};

// ========================================================================
// PROBLEM 5: MAXIMUM SUBARRAY (KADANE'S ALGORITHM) ⭐⭐
// ========================================================================
/*
 * Given an integer array nums, find the contiguous subarray (containing at 
 * least one number) which has the largest sum and return its sum.
 */

class MaximumSubarray {
public:
    // Kadane's Algorithm - O(n) time, O(1) space
    static int maxSubArray(vector<int>& nums) {
        int maxSoFar = nums[0];
        int maxEndingHere = nums[0];
        
        for (int i = 1; i < nums.size(); i++) {
            maxEndingHere = max(nums[i], maxEndingHere + nums[i]);
            maxSoFar = max(maxSoFar, maxEndingHere);
        }
        
        return maxSoFar;
    }
    
    // Also return the actual subarray
    static pair<int, vector<int>> maxSubArrayWithArray(vector<int>& nums) {
        int maxSoFar = nums[0];
        int maxEndingHere = nums[0];
        int start = 0, end = 0, s = 0;
        
        for (int i = 1; i < nums.size(); i++) {
            if (maxEndingHere < 0) {
                maxEndingHere = nums[i];
                s = i;
            } else {
                maxEndingHere += nums[i];
            }
            
            if (maxSoFar < maxEndingHere) {
                maxSoFar = maxEndingHere;
                start = s;
                end = i;
            }
        }
        
        vector<int> result(nums.begin() + start, nums.begin() + end + 1);
        return {maxSoFar, result};
    }
};

// ========================================================================
// PROBLEM 6: MAXIMUM PRODUCT SUBARRAY ⭐⭐
// ========================================================================
/*
 * Given an integer array nums, find a contiguous non-empty subarray within 
 * the array that has the largest product, and return the product.
 */

class MaximumProductSubarray {
public:
    // O(n) time, O(1) space
    static int maxProduct(vector<int>& nums) {
        int maxSoFar = nums[0];
        int minSoFar = nums[0];
        int result = nums[0];
        
        for (int i = 1; i < nums.size(); i++) {
            int curr = nums[i];
            int tempMax = max({curr, maxSoFar * curr, minSoFar * curr});
            minSoFar = min({curr, maxSoFar * curr, minSoFar * curr});
            maxSoFar = tempMax;
            result = max(result, maxSoFar);
        }
        
        return result;
    }
};

// ========================================================================
// PROBLEM 7: FIND MINIMUM IN ROTATED SORTED ARRAY ⭐⭐
// ========================================================================
/*
 * Suppose an array of length n sorted in ascending order is rotated between 
 * 1 and n times. Given the sorted rotated array nums, return the minimum element.
 */

class FindMinimumRotated {
public:
    // Binary Search - O(log n) time, O(1) space
    static int findMin(vector<int>& nums) {
        int left = 0, right = nums.size() - 1;
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            
            if (nums[mid] > nums[right]) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        
        return nums[left];
    }
};

// ========================================================================
// PROBLEM 8: SEARCH IN ROTATED SORTED ARRAY ⭐⭐
// ========================================================================
/*
 * Given the array nums after the rotation and an integer target, return the 
 * index of target if it is in nums, or -1 if it is not in nums.
 */

class SearchRotatedArray {
public:
    // Binary Search - O(log n) time, O(1) space
    static int search(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (nums[mid] == target) {
                return mid;
            }
            
            // Check if left half is sorted
            if (nums[left] <= nums[mid]) {
                if (target >= nums[left] && target < nums[mid]) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            } else { // Right half is sorted
                if (target > nums[mid] && target <= nums[right]) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
        }
        
        return -1;
    }
};

// ========================================================================
// PROBLEM 9: 3SUM ⭐⭐⭐
// ========================================================================
/*
 * Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]] 
 * such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.
 */

class ThreeSum {
public:
    // Two pointers approach - O(n²) time, O(1) space
    static vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());
        
        for (int i = 0; i < nums.size() - 2; i++) {
            // Skip duplicates for first number
            if (i > 0 && nums[i] == nums[i-1]) continue;
            
            int left = i + 1, right = nums.size() - 1;
            
            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                
                if (sum == 0) {
                    result.push_back({nums[i], nums[left], nums[right]});
                    
                    // Skip duplicates for second number
                    while (left < right && nums[left] == nums[left+1]) left++;
                    // Skip duplicates for third number
                    while (left < right && nums[right] == nums[right-1]) right--;
                    
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
};

// ========================================================================
// PROBLEM 10: CONTAINER WITH MOST WATER ⭐⭐
// ========================================================================
/*
 * Given n non-negative integers representing an elevation map where the width 
 * of each bar is 1, compute how much water it can trap after raining.
 */

class ContainerWithMostWater {
public:
    // Two pointers - O(n) time, O(1) space
    static int maxArea(vector<int>& height) {
        int left = 0, right = height.size() - 1;
        int maxArea = 0;
        
        while (left < right) {
            int currentArea = min(height[left], height[right]) * (right - left);
            maxArea = max(maxArea, currentArea);
            
            if (height[left] < height[right]) {
                left++;
            } else {
                right--;
            }
        }
        
        return maxArea;
    }
};

// ========================================================================
// PROBLEM 11: TRAPPING RAIN WATER ⭐⭐⭐
// ========================================================================
/*
 * Given n non-negative integers representing an elevation map where the width 
 * of each bar is 1, compute how much water it can trap after raining.
 */

class TrappingRainWater {
public:
    // Two pointers approach - O(n) time, O(1) space
    static int trap(vector<int>& height) {
        if (height.empty()) return 0;
        
        int left = 0, right = height.size() - 1;
        int leftMax = 0, rightMax = 0;
        int water = 0;
        
        while (left < right) {
            if (height[left] < height[right]) {
                if (height[left] >= leftMax) {
                    leftMax = height[left];
                } else {
                    water += leftMax - height[left];
                }
                left++;
            } else {
                if (height[right] >= rightMax) {
                    rightMax = height[right];
                } else {
                    water += rightMax - height[right];
                }
                right--;
            }
        }
        
        return water;
    }
    
    // Dynamic Programming approach - O(n) time, O(n) space
    static int trapDP(vector<int>& height) {
        int n = height.size();
        if (n == 0) return 0;
        
        vector<int> leftMax(n), rightMax(n);
        
        leftMax[0] = height[0];
        for (int i = 1; i < n; i++) {
            leftMax[i] = max(height[i], leftMax[i-1]);
        }
        
        rightMax[n-1] = height[n-1];
        for (int i = n-2; i >= 0; i--) {
            rightMax[i] = max(height[i], rightMax[i+1]);
        }
        
        int water = 0;
        for (int i = 0; i < n; i++) {
            water += min(leftMax[i], rightMax[i]) - height[i];
        }
        
        return water;
    }
};

// ========================================================================
// PROBLEM 12: NEXT PERMUTATION ⭐⭐
// ========================================================================
/*
 * Implement next permutation, which rearranges numbers into the lexicographically 
 * next greater permutation of numbers.
 */

class NextPermutation {
public:
    // O(n) time, O(1) space
    static void nextPermutation(vector<int>& nums) {
        int i = nums.size() - 2;
        
        // Find the first decreasing element from right
        while (i >= 0 && nums[i] >= nums[i + 1]) {
            i--;
        }
        
        if (i >= 0) {
            // Find the smallest element on right side of above element 
            // that is greater than above element
            int j = nums.size() - 1;
            while (nums[j] <= nums[i]) {
                j--;
            }
            swap(nums[i], nums[j]);
        }
        
        // Reverse the elements from i+1 to end
        reverse(nums.begin() + i + 1, nums.end());
    }
};

// ========================================================================
// PROBLEM 13: ROTATE ARRAY ⭐
// ========================================================================
/*
 * Given an array, rotate the array to the right by k steps, where k is non-negative.
 */

class RotateArray {
public:
    // Approach 1: Using extra space - O(n) time, O(n) space
    static void rotateExtraSpace(vector<int>& nums, int k) {
        int n = nums.size();
        k = k % n;
        vector<int> temp(n);
        
        for (int i = 0; i < n; i++) {
            temp[(i + k) % n] = nums[i];
        }
        
        nums = temp;
    }
    
    // Approach 2: Reverse method - O(n) time, O(1) space
    static void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k = k % n;
        
        // Reverse entire array
        reverse(nums.begin(), nums.end());
        // Reverse first k elements
        reverse(nums.begin(), nums.begin() + k);
        // Reverse remaining elements
        reverse(nums.begin() + k, nums.end());
    }
};

// ========================================================================
// PROBLEM 14: MERGE INTERVALS ⭐⭐
// ========================================================================
/*
 * Given an array of intervals where intervals[i] = [starti, endi], merge all 
 * overlapping intervals, and return an array of the non-overlapping intervals.
 */

class MergeIntervals {
public:
    // O(n log n) time, O(1) space
    static vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if (intervals.empty()) return {};
        
        sort(intervals.begin(), intervals.end());
        vector<vector<int>> merged;
        
        for (auto& interval : intervals) {
            if (merged.empty() || merged.back()[1] < interval[0]) {
                merged.push_back(interval);
            } else {
                merged.back()[1] = max(merged.back()[1], interval[1]);
            }
        }
        
        return merged;
    }
};

// ========================================================================
// PROBLEM 15: INSERT INTERVAL ⭐⭐
// ========================================================================
/*
 * You are given an array of non-overlapping intervals intervals where 
 * intervals[i] = [starti, endi] represent the start and the end of the ith interval 
 * and intervals is sorted in ascending order by starti. Insert newInterval 
 * into intervals such that intervals is still sorted in ascending order.
 */

class InsertInterval {
public:
    // O(n) time, O(n) space
    static vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> result;
        int i = 0;
        
        // Add all intervals that end before newInterval starts
        while (i < intervals.size() && intervals[i][1] < newInterval[0]) {
            result.push_back(intervals[i]);
            i++;
        }
        
        // Merge overlapping intervals
        while (i < intervals.size() && intervals[i][0] <= newInterval[1]) {
            newInterval[0] = min(newInterval[0], intervals[i][0]);
            newInterval[1] = max(newInterval[1], intervals[i][1]);
            i++;
        }
        result.push_back(newInterval);
        
        // Add remaining intervals
        while (i < intervals.size()) {
            result.push_back(intervals[i]);
            i++;
        }
        
        return result;
    }
};

// ========================================================================
// TESTING FUNCTIONS
// ========================================================================

void testArrayProblems() {
    cout << "\n=== TESTING ARRAY PROBLEMS ===" << endl;
    
    // Test Two Sum
    vector<int> nums1 = {2, 7, 11, 15};
    auto result1 = TwoSum::twoSumHashMap(nums1, 9);
    cout << "Two Sum: [" << result1[0] << ", " << result1[1] << "]" << endl;
    
    // Test Best Time to Buy Stock
    vector<int> prices = {7, 1, 5, 3, 6, 4};
    cout << "Max Profit: " << BestTimeToBuyStock::maxProfit(prices) << endl;
    
    // Test Maximum Subarray
    vector<int> nums2 = {-2, 1, -3, 4, 1, 2, 1, -5, 4};
    cout << "Maximum Subarray Sum: " << MaximumSubarray::maxSubArray(nums2) << endl;
    
    // Test Product Except Self
    vector<int> nums3 = {1, 2, 3, 4};
    auto product = ProductExceptSelf::productExceptSelf(nums3);
    cout << "Product Except Self: [";
    for (int i = 0; i < product.size(); i++) {
        cout << product[i];
        if (i < product.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    
    // Test Three Sum
    vector<int> nums4 = {-1, 0, 1, 2, -1, -4};
    auto triplets = ThreeSum::threeSum(nums4);
    cout << "Three Sum triplets: " << triplets.size() << " found" << endl;
    
    // Test Trapping Rain Water
    vector<int> heights = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    cout << "Water Trapped: " << TrappingRainWater::trap(heights) << endl;
}

// ========================================================================
// MAIN FUNCTION
// ========================================================================

int main() {
    cout << "ARRAY PROBLEMS - COMPREHENSIVE COLLECTION" << endl;
    cout << "=========================================" << endl;
    
    testArrayProblems();
    
    cout << "\n=== PROBLEMS SUMMARY ===" << endl;
    cout << "1. Two Sum ⭐" << endl;
    cout << "2. Best Time to Buy and Sell Stock ⭐" << endl;
    cout << "3. Contains Duplicate ⭐" << endl;
    cout << "4. Product of Array Except Self ⭐⭐" << endl;
    cout << "5. Maximum Subarray (Kadane's) ⭐⭐" << endl;
    cout << "6. Maximum Product Subarray ⭐⭐" << endl;
    cout << "7. Find Minimum in Rotated Sorted Array ⭐⭐" << endl;
    cout << "8. Search in Rotated Sorted Array ⭐⭐" << endl;
    cout << "9. 3Sum ⭐⭐⭐" << endl;
    cout << "10. Container With Most Water ⭐⭐" << endl;
    cout << "11. Trapping Rain Water ⭐⭐⭐" << endl;
    cout << "12. Next Permutation ⭐⭐" << endl;
    cout << "13. Rotate Array ⭐" << endl;
    cout << "14. Merge Intervals ⭐⭐" << endl;
    cout << "15. Insert Interval ⭐⭐" << endl;
    
    cout << "\nNext: Practice these problems and move to string_problems.cpp!" << endl;
    
    return 0;
}

/*
 * COMPILATION: g++ -std=c++17 -O2 -o array_problems array_problems.cpp
 * 
 * STUDY TIPS:
 * 1. Start with easy problems (⭐) and understand the basic patterns
 * 2. Practice drawing out examples for each problem
 * 3. Focus on time/space complexity analysis
 * 4. Try to solve each problem in multiple ways
 * 5. Practice implementing from memory
 * 
 * KEY PATTERNS TO MASTER:
 * - Two pointers technique
 * - Sliding window
 * - Hash maps for O(1) lookup
 * - Binary search on sorted arrays
 * - Kadane's algorithm for maximum subarray
 * - Interval problems and merging
 */
