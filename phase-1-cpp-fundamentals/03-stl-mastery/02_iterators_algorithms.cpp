/*
 * ============================================================================
 * STL ITERATORS & ALGORITHMS - COMPREHENSIVE GUIDE
 * ============================================================================
 * 
 * THEORY:
 * Iterators are objects that point to elements in containers and provide
 * a way to traverse and access container elements. They act as a bridge
 * between containers and algorithms, enabling generic programming.
 * 
 * STL algorithms are template functions that operate on sequences of
 * elements through iterators. They provide common operations like sorting,
 * searching, modifying, and numeric operations.
 * 
 * ITERATOR CATEGORIES:
 * 1. Input Iterator - Read only, single pass (istream_iterator)
 * 2. Output Iterator - Write only, single pass (ostream_iterator)
 * 3. Forward Iterator - Read/write, multi-pass (forward_list iterators)
 * 4. Bidirectional Iterator - Forward + backward (list, set, map iterators)
 * 5. Random Access Iterator - Jump to any position (vector, deque iterators)
 * 
 * ALGORITHM CATEGORIES:
 * 1. Non-modifying sequence operations (find, count, search)
 * 2. Modifying sequence operations (copy, transform, replace)
 * 3. Partitioning operations (partition, stable_partition)
 * 4. Sorting operations (sort, partial_sort, nth_element)
 * 5. Binary search operations (binary_search, lower_bound)
 * 6. Set operations (set_union, set_intersection)
 * 7. Heap operations (make_heap, push_heap, pop_heap)
 * 8. Min/max operations (min_element, max_element)
 * 9. Numeric operations (accumulate, inner_product)
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <functional>
#include <random>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <chrono>

using namespace std;

/*
 * ========================================================================
 * 1. ITERATOR FUNDAMENTALS
 * ========================================================================
 */

void demonstrateIteratorBasics() {
    cout << "1. ITERATOR FUNDAMENTALS" << endl;
    cout << "========================" << endl;
    
    vector<int> vec = {10, 20, 30, 40, 50};
    
    // Basic iterator operations
    cout << "Basic iterator usage:" << endl;
    cout << "Vector contents: ";
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    // Iterator arithmetic (Random Access Iterators)
    auto it = vec.begin();
    cout << "\nIterator arithmetic:" << endl;
    cout << "First element: " << *it << endl;
    cout << "Second element: " << *(it + 1) << endl;
    cout << "Third element: " << *(++it, ++it) << endl;
    
    // Distance between iterators
    cout << "Distance from begin to end: " << distance(vec.begin(), vec.end()) << endl;
    
    // Advance iterator
    it = vec.begin();
    advance(it, 2);
    cout << "After advance(it, 2): " << *it << endl;
    
    // Next and prev (C++11)
    auto next_it = next(it);
    auto prev_it = prev(it);
    cout << "Next element: " << *next_it << endl;
    cout << "Previous element: " << *prev_it << endl;
    
    cout << endl;
}

void demonstrateIteratorCategories() {
    cout << "2. ITERATOR CATEGORIES" << endl;
    cout << "======================" << endl;
    
    // Random Access Iterator (vector, deque)
    vector<int> vec = {1, 2, 3, 4, 5};
    cout << "Random Access Iterator (vector):" << endl;
    cout << "Can jump: vec.begin() + 3 = " << *(vec.begin() + 3) << endl;
    cout << "Can compare: (vec.begin() < vec.end()) = " << (vec.begin() < vec.end()) << endl;
    
    // Bidirectional Iterator (list, set, map)
    list<int> lst = {1, 2, 3, 4, 5};
    cout << "\nBidirectional Iterator (list):" << endl;
    cout << "Forward: ";
    for (auto it = lst.begin(); it != lst.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    cout << "Backward: ";
    for (auto it = lst.rbegin(); it != lst.rend(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    // Input/Output Iterators
    cout << "\nInput/Output Iterators:" << endl;
    vector<int> source = {1, 2, 3, 4, 5};
    vector<int> destination(5);
    
    // Copy using iterators
    copy(source.begin(), source.end(), destination.begin());
    cout << "Copied data: ";
    for (int val : destination) cout << val << " ";
    cout << endl;
    
    cout << endl;
}

void demonstrateIteratorAdapters() {
    cout << "3. ITERATOR ADAPTERS" << endl;
    cout << "====================" << endl;
    
    vector<int> vec = {1, 2, 3, 4, 5};
    
    // Reverse iterator
    cout << "Reverse iterator:" << endl;
    cout << "Forward: ";
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    cout << "Reverse: ";
    for (auto it = vec.rbegin(); it != vec.rend(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    // Insert iterators
    cout << "\nInsert iterators:" << endl;
    vector<int> dest;
    
    // Back insert iterator
    copy(vec.begin(), vec.end(), back_inserter(dest));
    cout << "Back inserter result: ";
    for (int val : dest) cout << val << " ";
    cout << endl;
    
    // Front insert iterator (works with deque, list)
    list<int> dest_list;
    copy(vec.begin(), vec.end(), front_inserter(dest_list));
    cout << "Front inserter result: ";
    for (int val : dest_list) cout << val << " ";
    cout << endl;
    
    // General insert iterator
    vector<int> dest2 = {100, 200};
    copy(vec.begin(), vec.end(), inserter(dest2, dest2.begin() + 1));
    cout << "Insert iterator result: ";
    for (int val : dest2) cout << val << " ";
    cout << endl;
    
    // Stream iterators
    cout << "\nStream iterators:" << endl;
    cout << "Enter 3 numbers: ";
    vector<int> input_nums;
    copy_n(istream_iterator<int>(cin), 3, back_inserter(input_nums));
    
    cout << "You entered: ";
    copy(input_nums.begin(), input_nums.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    
    cout << endl;
}

/*
 * ========================================================================
 * 2. NON-MODIFYING SEQUENCE OPERATIONS
 * ========================================================================
 */

void demonstrateSearchingAlgorithms() {
    cout << "4. SEARCHING ALGORITHMS" << endl;
    cout << "=======================" << endl;
    
    vector<int> vec = {1, 3, 5, 7, 9, 3, 11, 13, 3};
    
    // find - finds first occurrence
    auto it = find(vec.begin(), vec.end(), 3);
    if (it != vec.end()) {
        cout << "Found 3 at position: " << distance(vec.begin(), it) << endl;
    }
    
    // find_if - finds first element satisfying condition
    auto it2 = find_if(vec.begin(), vec.end(), [](int x) { return x > 10; });
    if (it2 != vec.end()) {
        cout << "First element > 10: " << *it2 << " at position " << distance(vec.begin(), it2) << endl;
    }
    
    // find_if_not - finds first element NOT satisfying condition
    auto it3 = find_if_not(vec.begin(), vec.end(), [](int x) { return x < 10; });
    if (it3 != vec.end()) {
        cout << "First element >= 10: " << *it3 << endl;
    }
    
    // count - counts occurrences
    int count_3 = count(vec.begin(), vec.end(), 3);
    cout << "Number of 3s: " << count_3 << endl;
    
    // count_if - counts elements satisfying condition
    int count_even = count_if(vec.begin(), vec.end(), [](int x) { return x % 2 == 0; });
    cout << "Number of even elements: " << count_even << endl;
    
    // search - finds subsequence
    vector<int> pattern = {7, 9};
    auto it4 = search(vec.begin(), vec.end(), pattern.begin(), pattern.end());
    if (it4 != vec.end()) {
        cout << "Pattern {7, 9} found at position: " << distance(vec.begin(), it4) << endl;
    }
    
    // search_n - finds n consecutive equal elements
    vector<int> vec2 = {1, 2, 2, 2, 3, 4, 4, 5};
    auto it5 = search_n(vec2.begin(), vec2.end(), 3, 2);
    if (it5 != vec2.end()) {
        cout << "Found 3 consecutive 2s at position: " << distance(vec2.begin(), it5) << endl;
    }
    
    // adjacent_find - finds two adjacent equal elements
    auto it6 = adjacent_find(vec2.begin(), vec2.end());
    if (it6 != vec2.end()) {
        cout << "First adjacent equal elements: " << *it6 << " at position " << distance(vec2.begin(), it6) << endl;
    }
    
    cout << endl;
}

void demonstrateComparisonAlgorithms() {
    cout << "5. COMPARISON ALGORITHMS" << endl;
    cout << "========================" << endl;
    
    vector<int> vec1 = {1, 2, 3, 4, 5};
    vector<int> vec2 = {1, 2, 3, 4, 5};
    vector<int> vec3 = {1, 2, 4, 4, 5};
    
    // equal - checks if two ranges are equal
    bool are_equal = equal(vec1.begin(), vec1.end(), vec2.begin());
    cout << "vec1 equals vec2: " << (are_equal ? "Yes" : "No") << endl;
    
    are_equal = equal(vec1.begin(), vec1.end(), vec3.begin());
    cout << "vec1 equals vec3: " << (are_equal ? "Yes" : "No") << endl;
    
    // mismatch - finds first position where two ranges differ
    auto mismatch_pair = mismatch(vec1.begin(), vec1.end(), vec3.begin());
    if (mismatch_pair.first != vec1.end()) {
        cout << "First mismatch at position " << distance(vec1.begin(), mismatch_pair.first);
        cout << ": " << *mismatch_pair.first << " vs " << *mismatch_pair.second << endl;
    }
    
    // lexicographical_compare - lexicographical comparison
    vector<string> words1 = {"apple", "banana", "cherry"};
    vector<string> words2 = {"apple", "banana", "date"};
    
    bool is_less = lexicographical_compare(words1.begin(), words1.end(), 
                                         words2.begin(), words2.end());
    cout << "words1 < words2 lexicographically: " << (is_less ? "Yes" : "No") << endl;
    
    cout << endl;
}

/*
 * ========================================================================
 * 3. MODIFYING SEQUENCE OPERATIONS
 * ========================================================================
 */

void demonstrateCopyingAlgorithms() {
    cout << "6. COPYING ALGORITHMS" << endl;
    cout << "=====================" << endl;
    
    vector<int> source = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<int> dest(source.size());
    
    // copy - copies range
    copy(source.begin(), source.end(), dest.begin());
    cout << "copy result: ";
    for (int val : dest) cout << val << " ";
    cout << endl;
    
    // copy_n - copies n elements
    vector<int> dest2(5);
    copy_n(source.begin(), 5, dest2.begin());
    cout << "copy_n(5) result: ";
    for (int val : dest2) cout << val << " ";
    cout << endl;
    
    // copy_if - copies elements satisfying condition
    vector<int> dest3;
    copy_if(source.begin(), source.end(), back_inserter(dest3), 
            [](int x) { return x % 2 == 0; });
    cout << "copy_if (even numbers): ";
    for (int val : dest3) cout << val << " ";
    cout << endl;
    
    // copy_backward - copies in reverse order
    vector<int> dest4(source.size());
    copy_backward(source.begin(), source.end(), dest4.end());
    cout << "copy_backward result: ";
    for (int val : dest4) cout << val << " ";
    cout << endl;
    
    cout << endl;
}

void demonstrateTransformAlgorithms() {
    cout << "7. TRANSFORM ALGORITHMS" << endl;
    cout << "=======================" << endl;
    
    vector<int> vec = {1, 2, 3, 4, 5};
    vector<int> result(vec.size());
    
    // transform - applies function to range
    transform(vec.begin(), vec.end(), result.begin(), 
              [](int x) { return x * x; });
    cout << "Squares: ";
    for (int val : result) cout << val << " ";
    cout << endl;
    
    // transform with two input ranges
    vector<int> vec2 = {10, 20, 30, 40, 50};
    vector<int> result2(vec.size());
    transform(vec.begin(), vec.end(), vec2.begin(), result2.begin(),
              [](int a, int b) { return a + b; });
    cout << "Sum of corresponding elements: ";
    for (int val : result2) cout << val << " ";
    cout << endl;
    
    // In-place transformation
    vector<string> words = {"hello", "world", "cpp", "programming"};
    transform(words.begin(), words.end(), words.begin(),
              [](const string& s) { 
                  string upper = s;
                  transform(s.begin(), s.end(), upper.begin(), ::toupper);
                  return upper;
              });
    cout << "Uppercase words: ";
    for (const string& word : words) cout << word << " ";
    cout << endl;
    
    cout << endl;
}

void demonstrateReplaceAlgorithms() {
    cout << "8. REPLACE ALGORITHMS" << endl;
    cout << "=====================" << endl;
    
    vector<int> vec = {1, 2, 3, 2, 4, 2, 5};
    
    // replace - replaces all occurrences
    cout << "Original: ";
    for (int val : vec) cout << val << " ";
    cout << endl;
    
    replace(vec.begin(), vec.end(), 2, 99);
    cout << "After replace(2, 99): ";
    for (int val : vec) cout << val << " ";
    cout << endl;
    
    // replace_if - replaces elements satisfying condition
    vector<int> vec2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    replace_if(vec2.begin(), vec2.end(), 
               [](int x) { return x % 2 == 0; }, 0);
    cout << "After replace_if(even, 0): ";
    for (int val : vec2) cout << val << " ";
    cout << endl;
    
    // replace_copy - copies with replacement
    vector<int> vec3 = {1, 2, 3, 2, 4, 2, 5};
    vector<int> result;
    replace_copy(vec3.begin(), vec3.end(), back_inserter(result), 2, 88);
    cout << "replace_copy(2, 88): ";
    for (int val : result) cout << val << " ";
    cout << endl;
    
    cout << endl;
}

void demonstrateFillAlgorithms() {
    cout << "9. FILL ALGORITHMS" << endl;
    cout << "==================" << endl;
    
    // fill - fills range with value
    vector<int> vec(10);
    fill(vec.begin(), vec.end(), 42);
    cout << "After fill(42): ";
    for (int val : vec) cout << val << " ";
    cout << endl;
    
    // fill_n - fills first n elements
    fill_n(vec.begin(), 5, 99);
    cout << "After fill_n(5, 99): ";
    for (int val : vec) cout << val << " ";
    cout << endl;
    
    // generate - fills with function results
    vector<int> vec2(10);
    int counter = 0;
    generate(vec2.begin(), vec2.end(), [&counter]() { return counter++; });
    cout << "After generate(counter): ";
    for (int val : vec2) cout << val << " ";
    cout << endl;
    
    // generate_n - generates first n elements
    vector<int> vec3(10, 0);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 100);
    generate_n(vec3.begin(), 5, [&]() { return dis(gen); });
    cout << "After generate_n(5, random): ";
    for (int val : vec3) cout << val << " ";
    cout << endl;
    
    cout << endl;
}

/*
 * ========================================================================
 * 4. REMOVING ALGORITHMS
 * ========================================================================
 */

void demonstrateRemoveAlgorithms() {
    cout << "10. REMOVE ALGORITHMS" << endl;
    cout << "=====================" << endl;
    
    // remove - removes elements (doesn't actually erase)
    vector<int> vec = {1, 2, 3, 2, 4, 2, 5};
    cout << "Original: ";
    for (int val : vec) cout << val << " ";
    cout << endl;
    
    auto new_end = remove(vec.begin(), vec.end(), 2);
    cout << "After remove(2): ";
    for (auto it = vec.begin(); it != new_end; ++it) cout << *it << " ";
    cout << endl;
    cout << "Vector still contains: ";
    for (int val : vec) cout << val << " ";
    cout << " (size: " << vec.size() << ")" << endl;
    
    // Erase-remove idiom
    vec.erase(new_end, vec.end());
    cout << "After erase: ";
    for (int val : vec) cout << val << " ";
    cout << " (size: " << vec.size() << ")" << endl;
    
    // remove_if - removes elements satisfying condition
    vector<int> vec2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    cout << "\nOriginal vec2: ";
    for (int val : vec2) cout << val << " ";
    cout << endl;
    
    auto new_end2 = remove_if(vec2.begin(), vec2.end(), 
                              [](int x) { return x % 2 == 0; });
    vec2.erase(new_end2, vec2.end());
    cout << "After remove_if(even): ";
    for (int val : vec2) cout << val << " ";
    cout << endl;
    
    // remove_copy - copies without removed elements
    vector<int> vec3 = {1, 2, 3, 2, 4, 2, 5};
    vector<int> result;
    remove_copy(vec3.begin(), vec3.end(), back_inserter(result), 2);
    cout << "\nremove_copy(2) result: ";
    for (int val : result) cout << val << " ";
    cout << endl;
    
    // unique - removes consecutive duplicates
    vector<int> vec4 = {1, 1, 2, 2, 2, 3, 1, 1, 4, 4};
    cout << "\nOriginal with duplicates: ";
    for (int val : vec4) cout << val << " ";
    cout << endl;
    
    auto new_end3 = unique(vec4.begin(), vec4.end());
    vec4.erase(new_end3, vec4.end());
    cout << "After unique (consecutive): ";
    for (int val : vec4) cout << val << " ";
    cout << endl;
    
    // To remove all duplicates, sort first
    vector<int> vec5 = {1, 3, 2, 3, 1, 4, 2, 4};
    cout << "\nOriginal: ";
    for (int val : vec5) cout << val << " ";
    cout << endl;
    
    sort(vec5.begin(), vec5.end());
    cout << "After sort: ";
    for (int val : vec5) cout << val << " ";
    cout << endl;
    
    auto new_end4 = unique(vec5.begin(), vec5.end());
    vec5.erase(new_end4, vec5.end());
    cout << "After unique: ";
    for (int val : vec5) cout << val << " ";
    cout << endl;
    
    cout << endl;
}

/*
 * ========================================================================
 * 5. SORTING ALGORITHMS
 * ========================================================================
 */

void demonstrateSortingAlgorithms() {
    cout << "11. SORTING ALGORITHMS" << endl;
    cout << "======================" << endl;
    
    // sort - sorts range
    vector<int> vec = {64, 34, 25, 12, 22, 11, 90};
    cout << "Original: ";
    for (int val : vec) cout << val << " ";
    cout << endl;
    
    sort(vec.begin(), vec.end());
    cout << "After sort: ";
    for (int val : vec) cout << val << " ";
    cout << endl;
    
    // sort with custom comparator
    vector<string> words = {"banana", "apple", "cherry", "date"};
    cout << "\nOriginal words: ";
    for (const string& word : words) cout << word << " ";
    cout << endl;
    
    sort(words.begin(), words.end(), greater<string>());
    cout << "Sorted descending: ";
    for (const string& word : words) cout << word << " ";
    cout << endl;
    
    // Sort by length
    sort(words.begin(), words.end(), 
         [](const string& a, const string& b) { return a.length() < b.length(); });
    cout << "Sorted by length: ";
    for (const string& word : words) cout << word << " ";
    cout << endl;
    
    // stable_sort - maintains relative order of equal elements
    vector<pair<string, int>> people = {
        {"Alice", 25}, {"Bob", 30}, {"Charlie", 25}, {"David", 30}
    };
    cout << "\nOriginal people: ";
    for (const auto& p : people) cout << "{" << p.first << "," << p.second << "} ";
    cout << endl;
    
    stable_sort(people.begin(), people.end(),
                [](const pair<string, int>& a, const pair<string, int>& b) {
                    return a.second < b.second;
                });
    cout << "Stable sort by age: ";
    for (const auto& p : people) cout << "{" << p.first << "," << p.second << "} ";
    cout << endl;
    
    // partial_sort - sorts first n elements
    vector<int> vec2 = {64, 34, 25, 12, 22, 11, 90, 88, 76, 50};
    cout << "\nOriginal: ";
    for (int val : vec2) cout << val << " ";
    cout << endl;
    
    partial_sort(vec2.begin(), vec2.begin() + 5, vec2.end());
    cout << "Partial sort (first 5): ";
    for (int val : vec2) cout << val << " ";
    cout << endl;
    
    // nth_element - puts nth element in correct position
    vector<int> vec3 = {64, 34, 25, 12, 22, 11, 90, 88, 76, 50};
    nth_element(vec3.begin(), vec3.begin() + 4, vec3.end());
    cout << "After nth_element(4): ";
    for (int val : vec3) cout << val << " ";
    cout << endl;
    cout << "5th smallest element: " << vec3[4] << endl;
    
    cout << endl;
}

/*
 * ========================================================================
 * 6. BINARY SEARCH ALGORITHMS (work on sorted ranges)
 * ========================================================================
 */

void demonstrateBinarySearchAlgorithms() {
    cout << "12. BINARY SEARCH ALGORITHMS" << endl;
    cout << "============================" << endl;
    
    vector<int> vec = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    cout << "Sorted vector: ";
    for (int val : vec) cout << val << " ";
    cout << endl;
    
    // binary_search - checks if element exists
    bool found = binary_search(vec.begin(), vec.end(), 7);
    cout << "binary_search(7): " << (found ? "Found" : "Not found") << endl;
    
    found = binary_search(vec.begin(), vec.end(), 8);
    cout << "binary_search(8): " << (found ? "Found" : "Not found") << endl;
    
    // lower_bound - first position where element could be inserted
    auto lb = lower_bound(vec.begin(), vec.end(), 7);
    cout << "lower_bound(7) position: " << distance(vec.begin(), lb) << endl;
    cout << "Element at that position: " << *lb << endl;
    
    lb = lower_bound(vec.begin(), vec.end(), 8);
    cout << "lower_bound(8) position: " << distance(vec.begin(), lb) << endl;
    cout << "Element at that position: " << *lb << endl;
    
    // upper_bound - first position after all equal elements
    auto ub = upper_bound(vec.begin(), vec.end(), 7);
    cout << "upper_bound(7) position: " << distance(vec.begin(), ub) << endl;
    cout << "Element at that position: " << *ub << endl;
    
    // equal_range - returns pair of lower_bound and upper_bound
    vector<int> vec_with_dups = {1, 3, 5, 7, 7, 7, 9, 11, 13};
    cout << "\nVector with duplicates: ";
    for (int val : vec_with_dups) cout << val << " ";
    cout << endl;
    
    auto range = equal_range(vec_with_dups.begin(), vec_with_dups.end(), 7);
    cout << "equal_range(7): positions " << distance(vec_with_dups.begin(), range.first);
    cout << " to " << distance(vec_with_dups.begin(), range.second) << endl;
    cout << "All 7s: ";
    for (auto it = range.first; it != range.second; ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    cout << endl;
}

/*
 * ========================================================================
 * 7. SET OPERATIONS (work on sorted ranges)
 * ========================================================================
 */

void demonstrateSetOperations() {
    cout << "13. SET OPERATIONS" << endl;
    cout << "==================" << endl;
    
    vector<int> set1 = {1, 2, 3, 4, 5};
    vector<int> set2 = {3, 4, 5, 6, 7};
    
    cout << "Set 1: ";
    for (int val : set1) cout << val << " ";
    cout << endl;
    cout << "Set 2: ";
    for (int val : set2) cout << val << " ";
    cout << endl;
    
    // set_union
    vector<int> result_union;
    set_union(set1.begin(), set1.end(), set2.begin(), set2.end(),
              back_inserter(result_union));
    cout << "Union: ";
    for (int val : result_union) cout << val << " ";
    cout << endl;
    
    // set_intersection
    vector<int> result_intersection;
    set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(),
                     back_inserter(result_intersection));
    cout << "Intersection: ";
    for (int val : result_intersection) cout << val << " ";
    cout << endl;
    
    // set_difference
    vector<int> result_difference;
    set_difference(set1.begin(), set1.end(), set2.begin(), set2.end(),
                   back_inserter(result_difference));
    cout << "Difference (set1 - set2): ";
    for (int val : result_difference) cout << val << " ";
    cout << endl;
    
    // set_symmetric_difference
    vector<int> result_sym_diff;
    set_symmetric_difference(set1.begin(), set1.end(), set2.begin(), set2.end(),
                            back_inserter(result_sym_diff));
    cout << "Symmetric difference: ";
    for (int val : result_sym_diff) cout << val << " ";
    cout << endl;
    
    // includes - checks if one set is subset of another
    vector<int> subset = {2, 3, 4};
    bool is_subset = includes(set1.begin(), set1.end(), subset.begin(), subset.end());
    cout << "Is {2,3,4} subset of set1: " << (is_subset ? "Yes" : "No") << endl;
    
    cout << endl;
}

/*
 * ========================================================================
 * 8. HEAP OPERATIONS
 * ========================================================================
 */

void demonstrateHeapOperations() {
    cout << "14. HEAP OPERATIONS" << endl;
    cout << "===================" << endl;
    
    vector<int> vec = {64, 34, 25, 12, 22, 11, 90};
    cout << "Original: ";
    for (int val : vec) cout << val << " ";
    cout << endl;
    
    // make_heap - creates max heap
    make_heap(vec.begin(), vec.end());
    cout << "After make_heap (max): ";
    for (int val : vec) cout << val << " ";
    cout << endl;
    cout << "Max element (top): " << vec.front() << endl;
    
    // push_heap - adds element to heap
    vec.push_back(100);
    push_heap(vec.begin(), vec.end());
    cout << "After adding 100 to heap: ";
    for (int val : vec) cout << val << " ";
    cout << endl;
    cout << "New max element: " << vec.front() << endl;
    
    // pop_heap - removes max element
    pop_heap(vec.begin(), vec.end());
    int max_val = vec.back();
    vec.pop_back();
    cout << "Removed max element: " << max_val << endl;
    cout << "Heap after pop: ";
    for (int val : vec) cout << val << " ";
    cout << endl;
    
    // sort_heap - sorts heap (destroys heap property)
    sort_heap(vec.begin(), vec.end());
    cout << "After sort_heap: ";
    for (int val : vec) cout << val << " ";
    cout << endl;
    
    // Min heap
    vector<int> vec2 = {64, 34, 25, 12, 22, 11, 90};
    make_heap(vec2.begin(), vec2.end(), greater<int>());
    cout << "\nMin heap: ";
    for (int val : vec2) cout << val << " ";
    cout << endl;
    cout << "Min element: " << vec2.front() << endl;
    
    // is_heap - checks if range is heap
    bool is_max_heap = is_heap(vec.begin(), vec.end());
    cout << "Is sorted vector a heap: " << (is_max_heap ? "Yes" : "No") << endl;
    
    cout << endl;
}

/*
 * ========================================================================
 * 9. MIN/MAX OPERATIONS
 * ========================================================================
 */

void demonstrateMinMaxOperations() {
    cout << "15. MIN/MAX OPERATIONS" << endl;
    cout << "======================" << endl;
    
    vector<int> vec = {64, 34, 25, 12, 22, 11, 90, 88};
    
    // min_element, max_element
    auto min_it = min_element(vec.begin(), vec.end());
    auto max_it = max_element(vec.begin(), vec.end());
    
    cout << "Vector: ";
    for (int val : vec) cout << val << " ";
    cout << endl;
    cout << "Min element: " << *min_it << " at position " << distance(vec.begin(), min_it) << endl;
    cout << "Max element: " << *max_it << " at position " << distance(vec.begin(), max_it) << endl;
    
    // minmax_element - returns both min and max
    auto minmax_pair = minmax_element(vec.begin(), vec.end());
    cout << "Min: " << *minmax_pair.first << ", Max: " << *minmax_pair.second << endl;
    
    // min, max for individual values
    cout << "min(5, 10): " << min(5, 10) << endl;
    cout << "max(5, 10): " << max(5, 10) << endl;
    cout << "minmax(5, 10): {" << minmax(5, 10).first << ", " << minmax(5, 10).second << "}" << endl;
    
    // With custom comparator
    vector<string> words = {"elephant", "cat", "dog", "butterfly"};
    auto longest = max_element(words.begin(), words.end(),
                              [](const string& a, const string& b) {
                                  return a.length() < b.length();
                              });
    cout << "Longest word: " << *longest << endl;
    
    cout << endl;
}

/*
 * ========================================================================
 * 10. NUMERIC ALGORITHMS
 * ========================================================================
 */

void demonstrateNumericAlgorithms() {
    cout << "16. NUMERIC ALGORITHMS" << endl;
    cout << "======================" << endl;
    
    vector<int> vec = {1, 2, 3, 4, 5};
    
    // accumulate - sum of elements
    int sum = accumulate(vec.begin(), vec.end(), 0);
    cout << "Sum: " << sum << endl;
    
    // accumulate with custom operation
    int product = accumulate(vec.begin(), vec.end(), 1, multiplies<int>());
    cout << "Product: " << product << endl;
    
    // Custom accumulate operation
    string concatenated = accumulate(vec.begin(), vec.end(), string(""),
                                   [](const string& acc, int val) {
                                       return acc + to_string(val) + " ";
                                   });
    cout << "Concatenated: " << concatenated << endl;
    
    // inner_product - dot product
    vector<int> vec2 = {2, 3, 4, 5, 6};
    int dot_product = inner_product(vec.begin(), vec.end(), vec2.begin(), 0);
    cout << "Dot product: " << dot_product << endl;
    
    // partial_sum - running sum
    vector<int> partial_sums(vec.size());
    partial_sum(vec.begin(), vec.end(), partial_sums.begin());
    cout << "Partial sums: ";
    for (int val : partial_sums) cout << val << " ";
    cout << endl;
    
    // adjacent_difference
    vector<int> differences(vec.size());
    adjacent_difference(vec.begin(), vec.end(), differences.begin());
    cout << "Adjacent differences: ";
    for (int val : differences) cout << val << " ";
    cout << endl;
    
    // iota - fills with incrementing values (C++11)
    vector<int> sequence(10);
    iota(sequence.begin(), sequence.end(), 100);
    cout << "iota starting from 100: ";
    for (int val : sequence) cout << val << " ";
    cout << endl;
    
    cout << endl;
}

/*
 * ========================================================================
 * 11. PARTITION OPERATIONS
 * ========================================================================
 */

void demonstratePartitionOperations() {
    cout << "17. PARTITION OPERATIONS" << endl;
    cout << "========================" << endl;
    
    vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    cout << "Original: ";
    for (int val : vec) cout << val << " ";
    cout << endl;
    
    // partition - partitions elements
    auto partition_point = partition(vec.begin(), vec.end(), 
                                   [](int x) { return x % 2 == 0; });
    
    cout << "After partition (even first): ";
    for (int val : vec) cout << val << " ";
    cout << endl;
    cout << "Partition point at position: " << distance(vec.begin(), partition_point) << endl;
    
    // stable_partition - maintains relative order within partitions
    vector<int> vec2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    stable_partition(vec2.begin(), vec2.end(), 
                    [](int x) { return x % 2 == 0; });
    
    cout << "After stable_partition (even first): ";
    for (int val : vec2) cout << val << " ";
    cout << endl;
    
    // is_partitioned - checks if range is partitioned
    bool is_part = is_partitioned(vec2.begin(), vec2.end(),
                                 [](int x) { return x % 2 == 0; });
    cout << "Is partitioned by even predicate: " << (is_part ? "Yes" : "No") << endl;
    
    // partition_point - finds partition point
    auto pp = partition_point(vec2.begin(), vec2.end(),
                             [](int x) { return x % 2 == 0; });
    cout << "Partition point: " << distance(vec2.begin(), pp) << endl;
    
    cout << endl;
}

/*
 * ========================================================================
 * 12. PRACTICAL EXAMPLES
 * ========================================================================
 */

void demonstratePracticalExamples() {
    cout << "18. PRACTICAL EXAMPLES" << endl;
    cout << "======================" << endl;
    
    // Example 1: Text processing
    cout << "Example 1: Text Processing" << endl;
    string text = "The quick brown fox jumps over the lazy dog";
    
    // Count words
    istringstream iss(text);
    vector<string> words(istream_iterator<string>{iss}, istream_iterator<string>{});
    cout << "Text: " << text << endl;
    cout << "Word count: " << words.size() << endl;
    
    // Find longest word
    auto longest = max_element(words.begin(), words.end(),
                              [](const string& a, const string& b) {
                                  return a.length() < b.length();
                              });
    cout << "Longest word: " << *longest << " (" << longest->length() << " chars)" << endl;
    
    // Count words starting with vowel
    int vowel_words = count_if(words.begin(), words.end(),
                              [](const string& word) {
                                  return word[0] == 'a' || word[0] == 'e' || 
                                         word[0] == 'i' || word[0] == 'o' || 
                                         word[0] == 'u' || word[0] == 'A' || 
                                         word[0] == 'E' || word[0] == 'I' || 
                                         word[0] == 'O' || word[0] == 'U';
                              });
    cout << "Words starting with vowel: " << vowel_words << endl;
    
    // Example 2: Data analysis
    cout << "\nExample 2: Data Analysis" << endl;
    vector<double> temperatures = {23.5, 25.1, 22.8, 26.3, 24.7, 21.9, 27.2, 25.8, 23.1};
    
    cout << "Temperatures: ";
    for (double temp : temperatures) cout << temp << " ";
    cout << endl;
    
    // Statistics
    double sum_temp = accumulate(temperatures.begin(), temperatures.end(), 0.0);
    double avg_temp = sum_temp / temperatures.size();
    auto minmax_temp = minmax_element(temperatures.begin(), temperatures.end());
    
    cout << "Average temperature: " << fixed << setprecision(2) << avg_temp << endl;
    cout << "Min temperature: " << *minmax_temp.first << endl;
    cout << "Max temperature: " << *minmax_temp.second << endl;
    
    // Count temperatures above average
    int above_avg = count_if(temperatures.begin(), temperatures.end(),
                            [avg_temp](double temp) { return temp > avg_temp; });
    cout << "Days above average: " << above_avg << endl;
    
    // Example 3: Sorting with multiple criteria
    cout << "\nExample 3: Multi-criteria Sorting" << endl;
    vector<pair<string, pair<int, double>>> students = {
        {"Alice", {85, 3.2}}, {"Bob", {92, 3.8}}, {"Charlie", {85, 3.5}}, 
        {"David", {78, 3.1}}, {"Eve", {92, 3.6}}
    };
    
    cout << "Students (Name, Score, GPA):" << endl;
    for (const auto& student : students) {
        cout << student.first << " " << student.second.first << " " << student.second.second << endl;
    }
    
    // Sort by score, then by GPA for ties
    sort(students.begin(), students.end(),
         [](const auto& a, const auto& b) {
             if (a.second.first != b.second.first) {
                 return a.second.first > b.second.first; // Higher score first
             }
             return a.second.second > b.second.second; // Higher GPA for ties
         });
    
    cout << "After sorting by score then GPA:" << endl;
    for (const auto& student : students) {
        cout << student.first << " " << student.second.first << " " << student.second.second << endl;
    }
    
    cout << endl;
}

/*
 * ========================================================================
 * MAIN FUNCTION
 * ========================================================================
 */

int main() {
    cout << "=== STL ITERATORS & ALGORITHMS COMPREHENSIVE GUIDE ===" << endl << endl;
    
    demonstrateIteratorBasics();
    demonstrateIteratorCategories();
    demonstrateIteratorAdapters();
    demonstrateSearchingAlgorithms();
    demonstrateComparisonAlgorithms();
    demonstrateCopyingAlgorithms();
    demonstrateTransformAlgorithms();
    demonstrateReplaceAlgorithms();
    demonstrateFillAlgorithms();
    demonstrateRemoveAlgorithms();
    demonstrateSortingAlgorithms();
    demonstrateBinarySearchAlgorithms();
    demonstrateSetOperations();
    demonstrateHeapOperations();
    demonstrateMinMaxOperations();
    demonstrateNumericAlgorithms();
    demonstratePartitionOperations();
    demonstratePracticalExamples();
    
    cout << "=== STL Iterators & Algorithms Mastery Complete! ===" << endl;
    
    return 0;
}

/*
 * ============================================================================
 * PRACTICE EXERCISES:
 * ============================================================================
 * 
 * 1. Implement a function that finds the kth smallest element using nth_element.
 * 
 * 2. Write a program that merges two sorted vectors into one sorted vector.
 * 
 * 3. Create a function that rotates a vector left by k positions using rotate.
 * 
 * 4. Implement a word frequency counter that ignores case and punctuation.
 * 
 * 5. Write a program that finds all anagrams in a list of words.
 * 
 * 6. Create a function that checks if one string is a permutation of another.
 * 
 * 7. Implement a simple spell checker using binary search on sorted dictionary.
 * 
 * 8. Write a program that finds the longest increasing subsequence.
 * 
 * 9. Create a function that groups elements by a key using stable_partition.
 * 
 * 10. Implement a parallel sort using multiple threads and merge.
 * 
 * ============================================================================
 * ALGORITHM COMPLEXITY GUIDE:
 * ============================================================================
 * 
 * Searching:
 * - find, find_if: O(n)
 * - binary_search, lower_bound, upper_bound: O(log n) for sorted ranges
 * - search: O(n*m) where m is pattern size
 * 
 * Sorting:
 * - sort, stable_sort: O(n log n)
 * - partial_sort: O(n log k) where k is number of elements to sort
 * - nth_element: O(n) average
 * 
 * Modifying:
 * - copy, transform, replace: O(n)
 * - remove, unique: O(n)
 * - reverse, rotate: O(n)
 * 
 * Set Operations:
 * - set_union, set_intersection: O(n + m)
 * - set_difference: O(n + m)
 * 
 * Heap Operations:
 * - make_heap: O(n)
 * - push_heap, pop_heap: O(log n)
 * - sort_heap: O(n log n)
 * 
 * Numeric:
 * - accumulate, inner_product: O(n)
 * - partial_sum, adjacent_difference: O(n)
 * 
 * ============================================================================
 * ITERATOR INVALIDATION RULES:
 * ============================================================================
 * 
 * Vector:
 * - Insert/erase invalidates all iterators after the operation point
 * - push_back may invalidate all iterators if reallocation occurs
 * - reserve() may invalidate all iterators
 * 
 * Deque:
 * - Insert/erase at ends: only end iterators invalidated
 * - Insert/erase in middle: all iterators invalidated
 * 
 * List:
 * - Insert never invalidates iterators
 * - Erase only invalidates iterators to erased elements
 * 
 * Set/Map:
 * - Insert never invalidates iterators
 * - Erase only invalidates iterators to erased elements
 * 
 * ============================================================================
 * BEST PRACTICES:
 * ============================================================================
 * 
 * 1. Use appropriate algorithm for the task (don't reinvent the wheel)
 * 2. Prefer algorithms over hand-written loops for better performance
 * 3. Use const iterators when not modifying elements
 * 4. Check iterator validity before dereferencing
 * 5. Use range-based for loops when appropriate (C++11)
 * 6. Understand iterator categories and algorithm requirements
 * 7. Use lambda functions for custom predicates (C++11)
 * 8. Consider using parallel algorithms for large datasets (C++17)
 * 9. Use appropriate container for algorithm requirements
 * 10. Profile your code to ensure algorithms provide expected performance
 * 
 * Common Patterns:
 * - Erase-remove idiom: vec.erase(remove(...), vec.end())
 * - Sort before unique to remove all duplicates
 * - Use stable_sort when order of equal elements matters
 * - Use partial_sort when you only need top k elements
 * - Use nth_element for median finding
 * - Use partition for two-way classification
 * 
 * ============================================================================
 */
