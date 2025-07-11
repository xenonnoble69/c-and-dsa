/*
 * ============================================================================
 * FUNCTION OBJECTS (FUNCTORS) - COMPREHENSIVE GUIDE
 * ============================================================================
 * 
 * THEORY:
 * Function objects (functors) are objects that can be called like functions.
 * They are implemented by overloading the operator() in a class.
 * Function objects are more powerful than regular functions because:
 * 1. They can maintain state between calls
 * 2. They can be templated for type safety
 * 3. They can be optimized better by compilers (inlined)
 * 4. They can carry additional data and behavior
 * 
 * TYPES OF CALLABLE OBJECTS IN C++:
 * 1. Function Pointers - Traditional C-style function pointers
 * 2. Function Objects (Functors) - Classes with operator() overloaded
 * 3. Lambda Expressions - Anonymous functions (C++11)
 * 4. std::function - Type-erased wrapper for callables (C++11)
 * 
 * STL PREDEFINED FUNCTORS:
 * - Arithmetic: plus, minus, multiplies, divides, modulus, negate
 * - Comparison: equal_to, not_equal_to, greater, less, greater_equal, less_equal
 * - Logical: logical_and, logical_or, logical_not
 * 
 * ADVANTAGES OF FUNCTORS:
 * - Stateful: Can store data between calls
 * - Efficient: Often inlined by compiler
 * - Flexible: Can be customized and parameterized
 * - Compatible: Work seamlessly with STL algorithms
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <set>
#include <map>
#include <string>
#include <numeric>
#include <iterator>
#include <queue>
#include <random>
#include <chrono>

using namespace std;

/*
 * ========================================================================
 * 1. BASIC FUNCTION OBJECTS
 * ========================================================================
 */

// Simple function object
class Multiply {
private:
    int factor;
public:
    Multiply(int f) : factor(f) {}
    
    int operator()(int x) const {
        return x * factor;
    }
};

// Predicate function object (returns bool)
class IsEven {
public:
    bool operator()(int x) const {
        return x % 2 == 0;
    }
};

// Stateful function object
class Counter {
private:
    mutable int count;  // mutable allows modification in const member function
public:
    Counter() : count(0) {}
    
    int operator()(int x) const {
        return ++count;  // Returns call count, not the value
    }
    
    int getCount() const { return count; }
};

void demonstrateBasicFunctors() {
    cout << "1. BASIC FUNCTION OBJECTS" << endl;
    cout << "=========================" << endl;
    
    // Using Multiply functor
    Multiply multiplyBy3(3);
    cout << "multiplyBy3(5) = " << multiplyBy3(5) << endl;
    cout << "multiplyBy3(10) = " << multiplyBy3(10) << endl;
    
    // Using with STL algorithms
    vector<int> numbers = {1, 2, 3, 4, 5};
    cout << "\nOriginal vector: ";
    for (int n : numbers) cout << n << " ";
    cout << endl;
    
    transform(numbers.begin(), numbers.end(), numbers.begin(), Multiply(2));
    cout << "After multiplying by 2: ";
    for (int n : numbers) cout << n << " ";
    cout << endl;
    
    // Using predicate functor
    vector<int> test_numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    cout << "\nEven numbers: ";
    copy_if(test_numbers.begin(), test_numbers.end(), 
            ostream_iterator<int>(cout, " "), IsEven());
    cout << endl;
    
    // Using stateful functor
    Counter counter;
    cout << "\nCounting function calls:" << endl;
    for (int i = 0; i < 5; i++) {
        counter(i);
        cout << "Call " << counter.getCount() << endl;
    }
    
    cout << endl;
}

/*
 * ========================================================================
 * 2. STL PREDEFINED FUNCTORS
 * ========================================================================
 */

void demonstrateSTLFunctors() {
    cout << "2. STL PREDEFINED FUNCTORS" << endl;
    cout << "==========================" << endl;
    
    vector<int> vec1 = {1, 2, 3, 4, 5};
    vector<int> vec2 = {2, 3, 4, 5, 6};
    vector<int> result(5);
    
    // Arithmetic functors
    cout << "Arithmetic Functors:" << endl;
    
    // plus<int>
    transform(vec1.begin(), vec1.end(), vec2.begin(), result.begin(), plus<int>());
    cout << "vec1 + vec2: ";
    for (int r : result) cout << r << " ";
    cout << endl;
    
    // multiplies<int>
    transform(vec1.begin(), vec1.end(), vec2.begin(), result.begin(), multiplies<int>());
    cout << "vec1 * vec2: ";
    for (int r : result) cout << r << " ";
    cout << endl;
    
    // negate<int>
    transform(vec1.begin(), vec1.end(), result.begin(), negate<int>());
    cout << "Negated vec1: ";
    for (int r : result) cout << r << " ";
    cout << endl;
    
    // Comparison functors
    cout << "\nComparison Functors:" << endl;
    vector<int> numbers = {5, 2, 8, 1, 9, 3};
    
    cout << "Original: ";
    for (int n : numbers) cout << n << " ";
    cout << endl;
    
    // Sort in ascending order using less<int>
    sort(numbers.begin(), numbers.end(), less<int>());
    cout << "Sorted (ascending): ";
    for (int n : numbers) cout << n << " ";
    cout << endl;
    
    // Sort in descending order using greater<int>
    sort(numbers.begin(), numbers.end(), greater<int>());
    cout << "Sorted (descending): ";
    for (int n : numbers) cout << n << " ";
    cout << endl;
    
    // Logical functors
    cout << "\nLogical Functors:" << endl;
    vector<bool> bool_vec1 = {true, false, true, false};
    vector<bool> bool_vec2 = {true, true, false, false};
    vector<bool> bool_result(4);
    
    transform(bool_vec1.begin(), bool_vec1.end(), bool_vec2.begin(), 
              bool_result.begin(), logical_and<bool>());
    cout << "Logical AND result: ";
    for (bool b : bool_result) cout << boolalpha << b << " ";
    cout << endl;
    
    cout << endl;
}

/*
 * ========================================================================
 * 3. CUSTOM COMPARATORS
 * ========================================================================
 */

// Custom comparator for strings (case-insensitive)
class CaseInsensitiveCompare {
public:
    bool operator()(const string& a, const string& b) const {
        return lexicographical_compare(a.begin(), a.end(),
                                     b.begin(), b.end(),
                                     [](char c1, char c2) {
                                         return tolower(c1) < tolower(c2);
                                     });
    }
};

// Custom comparator for sorting by absolute value
class AbsoluteCompare {
public:
    bool operator()(int a, int b) const {
        return abs(a) < abs(b);
    }
};

// Custom comparator for complex objects
struct Person {
    string name;
    int age;
    
    Person(const string& n, int a) : name(n), age(a) {}
};

class PersonAgeCompare {
public:
    bool operator()(const Person& a, const Person& b) const {
        return a.age < b.age;
    }
};

class PersonNameCompare {
public:
    bool operator()(const Person& a, const Person& b) const {
        return a.name < b.name;
    }
};

void demonstrateCustomComparators() {
    cout << "3. CUSTOM COMPARATORS" << endl;
    cout << "=====================" << endl;
    
    // Case-insensitive string sorting
    cout << "Case-insensitive string sorting:" << endl;
    vector<string> words = {"Apple", "banana", "Cherry", "date", "Elderberry"};
    
    cout << "Original: ";
    for (const string& word : words) cout << word << " ";
    cout << endl;
    
    sort(words.begin(), words.end(), CaseInsensitiveCompare());
    cout << "Case-insensitive sorted: ";
    for (const string& word : words) cout << word << " ";
    cout << endl;
    
    // Sorting by absolute value
    cout << "\nSorting by absolute value:" << endl;
    vector<int> numbers = {-5, 3, -1, 7, -9, 2, -4};
    
    cout << "Original: ";
    for (int n : numbers) cout << n << " ";
    cout << endl;
    
    sort(numbers.begin(), numbers.end(), AbsoluteCompare());
    cout << "Sorted by absolute value: ";
    for (int n : numbers) cout << n << " ";
    cout << endl;
    
    // Custom comparators with objects
    cout << "\nSorting Person objects:" << endl;
    vector<Person> people = {
        Person("Alice", 25),
        Person("Bob", 30),
        Person("Charlie", 20),
        Person("Diana", 35)
    };
    
    cout << "Original order:" << endl;
    for (const Person& p : people) {
        cout << p.name << " (" << p.age << ") ";
    }
    cout << endl;
    
    // Sort by age
    sort(people.begin(), people.end(), PersonAgeCompare());
    cout << "Sorted by age:" << endl;
    for (const Person& p : people) {
        cout << p.name << " (" << p.age << ") ";
    }
    cout << endl;
    
    // Sort by name
    sort(people.begin(), people.end(), PersonNameCompare());
    cout << "Sorted by name:" << endl;
    for (const Person& p : people) {
        cout << p.name << " (" << p.age << ") ";
    }
    cout << endl;
    
    // Using custom comparator with set
    cout << "\nUsing custom comparator with set:" << endl;
    set<string, CaseInsensitiveCompare> case_insensitive_set;
    case_insensitive_set.insert("Apple");
    case_insensitive_set.insert("apple");  // Won't be inserted (case-insensitive duplicate)
    case_insensitive_set.insert("Banana");
    case_insensitive_set.insert("banana"); // Won't be inserted
    
    cout << "Case-insensitive set contents: ";
    for (const string& item : case_insensitive_set) {
        cout << item << " ";
    }
    cout << endl;
    
    cout << endl;
}

/*
 * ========================================================================
 * 4. LAMBDA EXPRESSIONS AS FUNCTORS
 * ========================================================================
 */

void demonstrateLambdas() {
    cout << "4. LAMBDA EXPRESSIONS AS FUNCTORS" << endl;
    cout << "==================================" << endl;
    
    vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // Simple lambda
    cout << "Even numbers using lambda: ";
    copy_if(numbers.begin(), numbers.end(), 
            ostream_iterator<int>(cout, " "),
            [](int x) { return x % 2 == 0; });
    cout << endl;
    
    // Lambda with capture
    int threshold = 5;
    cout << "Numbers greater than " << threshold << ": ";
    copy_if(numbers.begin(), numbers.end(),
            ostream_iterator<int>(cout, " "),
            [threshold](int x) { return x > threshold; });
    cout << endl;
    
    // Lambda with mutable capture
    int multiplier = 2;
    cout << "Numbers multiplied by increasing factor: ";
    transform(numbers.begin(), numbers.begin() + 5, 
              ostream_iterator<int>(cout, " "),
              [multiplier](int x) mutable { return x * (multiplier++); });
    cout << endl;
    
    // Lambda for sorting
    vector<string> words = {"short", "a", "very_long_word", "medium"};
    cout << "\nOriginal words: ";
    for (const string& word : words) cout << word << " ";
    cout << endl;
    
    // Sort by length
    sort(words.begin(), words.end(),
         [](const string& a, const string& b) { return a.length() < b.length(); });
    cout << "Sorted by length: ";
    for (const string& word : words) cout << word << " ";
    cout << endl;
    
    // Complex lambda with multiple statements
    vector<int> test_data = {1, -2, 3, -4, 5, -6};
    cout << "\nProcessed data (absolute value if negative, square if positive): ";
    transform(test_data.begin(), test_data.end(),
              ostream_iterator<int>(cout, " "),
              [](int x) {
                  if (x < 0) return -x;      // absolute value
                  else return x * x;         // square
              });
    cout << endl;
    
    cout << endl;
}

/*
 * ========================================================================
 * 5. STD::FUNCTION AND FUNCTION WRAPPERS
 * ========================================================================
 */

// Regular function
int add(int a, int b) {
    return a + b;
}

// Function object
class Subtract {
public:
    int operator()(int a, int b) const {
        return a - b;
    }
};

void demonstrateStdFunction() {
    cout << "5. STD::FUNCTION AND FUNCTION WRAPPERS" << endl;
    cout << "=======================================" << endl;
    
    // std::function can hold different types of callables
    cout << "Different callables with std::function:" << endl;
    
    // Function pointer
    function<int(int, int)> f1 = add;
    cout << "Function pointer: f1(10, 5) = " << f1(10, 5) << endl;
    
    // Function object
    function<int(int, int)> f2 = Subtract();
    cout << "Function object: f2(10, 5) = " << f2(10, 5) << endl;
    
    // Lambda
    function<int(int, int)> f3 = [](int a, int b) { return a * b; };
    cout << "Lambda: f3(10, 5) = " << f3(10, 5) << endl;
    
    // Using std::function in containers
    cout << "\nUsing std::function in containers:" << endl;
    vector<function<int(int)>> operations;
    
    operations.push_back([](int x) { return x * 2; });        // double
    operations.push_back([](int x) { return x * x; });        // square
    operations.push_back([](int x) { return x + 10; });       // add 10
    
    int value = 5;
    cout << "Starting value: " << value << endl;
    for (size_t i = 0; i < operations.size(); i++) {
        int result = operations[i](value);
        cout << "Operation " << i + 1 << ": " << result << endl;
    }
    
    // Using std::bind
    cout << "\nUsing std::bind:" << endl;
    auto multiply_by_3 = bind(multiplies<int>(), placeholders::_1, 3);
    cout << "multiply_by_3(7) = " << multiply_by_3(7) << endl;
    
    auto subtract_from_10 = bind(minus<int>(), 10, placeholders::_1);
    cout << "subtract_from_10(3) = " << subtract_from_10(3) << endl;
    
    cout << endl;
}

/*
 * ========================================================================
 * 6. FUNCTORS WITH CONTAINERS
 * ========================================================================
 */

void demonstrateFunctorsWithContainers() {
    cout << "6. FUNCTORS WITH CONTAINERS" << endl;
    cout << "===========================" << endl;
    
    // Priority queue with custom comparator
    cout << "Priority queue with custom comparator:" << endl;
    
    // Min heap using greater<int>
    priority_queue<int, vector<int>, greater<int>> min_heap;
    min_heap.push(30);
    min_heap.push(10);
    min_heap.push(50);
    min_heap.push(20);
    
    cout << "Min heap elements: ";
    while (!min_heap.empty()) {
        cout << min_heap.top() << " ";
        min_heap.pop();
    }
    cout << endl;
    
    // Map with custom comparator (case-insensitive keys)
    cout << "\nMap with case-insensitive comparator:" << endl;
    map<string, int, CaseInsensitiveCompare> case_insensitive_map;
    case_insensitive_map["Apple"] = 1;
    case_insensitive_map["banana"] = 2;
    case_insensitive_map["Cherry"] = 3;
    
    cout << "Map contents:" << endl;
    for (const auto& pair : case_insensitive_map) {
        cout << pair.first << ": " << pair.second << endl;
    }
    
    // Set with custom comparator for complex objects
    cout << "\nSet with custom Person comparator:" << endl;
    set<Person, PersonAgeCompare> people_by_age;
    people_by_age.insert(Person("Alice", 25));
    people_by_age.insert(Person("Bob", 20));
    people_by_age.insert(Person("Charlie", 30));
    
    cout << "People sorted by age:" << endl;
    for (const Person& p : people_by_age) {
        cout << p.name << " (" << p.age << ") ";
    }
    cout << endl;
    
    cout << endl;
}

/*
 * ========================================================================
 * 7. ADVANCED FUNCTOR TECHNIQUES
 * ========================================================================
 */

// Template functor
template<typename T>
class Scale {
private:
    T factor;
public:
    Scale(T f) : factor(f) {}
    
    T operator()(T value) const {
        return value * factor;
    }
};

// Functor composition
template<typename F1, typename F2>
class Compose {
private:
    F1 f1;
    F2 f2;
public:
    Compose(F1 func1, F2 func2) : f1(func1), f2(func2) {}
    
    template<typename T>
    auto operator()(T&& value) const -> decltype(f1(f2(forward<T>(value)))) {
        return f1(f2(forward<T>(value)));
    }
};

// Helper function to create composed functors
template<typename F1, typename F2>
Compose<F1, F2> compose(F1 f1, F2 f2) {
    return Compose<F1, F2>(f1, f2);
}

// Accumulator functor
class Accumulator {
private:
    mutable int sum;
public:
    Accumulator() : sum(0) {}
    
    int operator()(int value) const {
        sum += value;
        return sum;
    }
    
    int getSum() const { return sum; }
};

void demonstrateAdvancedFunctors() {
    cout << "7. ADVANCED FUNCTOR TECHNIQUES" << endl;
    cout << "===============================" << endl;
    
    // Template functor
    cout << "Template functor:" << endl;
    Scale<int> scale_int(3);
    Scale<double> scale_double(2.5);
    
    cout << "scale_int(5) = " << scale_int(5) << endl;
    cout << "scale_double(4.0) = " << scale_double(4.0) << endl;
    
    // Functor composition
    cout << "\nFunctor composition:" << endl;
    auto add_5 = [](int x) { return x + 5; };
    auto multiply_2 = [](int x) { return x * 2; };
    
    auto composed = compose(multiply_2, add_5);  // (x + 5) * 2
    cout << "composed(3) = (3 + 5) * 2 = " << composed(3) << endl;
    
    // Using with STL algorithms
    vector<int> numbers = {1, 2, 3, 4, 5};
    cout << "\nOriginal: ";
    for (int n : numbers) cout << n << " ";
    cout << endl;
    
    transform(numbers.begin(), numbers.end(), numbers.begin(), composed);
    cout << "After composition: ";
    for (int n : numbers) cout << n << " ";
    cout << endl;
    
    // Accumulator functor
    cout << "\nAccumulator functor:" << endl;
    vector<int> values = {1, 2, 3, 4, 5};
    Accumulator acc;
    
    cout << "Running sums: ";
    for (int val : values) {
        cout << acc(val) << " ";
    }
    cout << endl;
    cout << "Final sum: " << acc.getSum() << endl;
    
    cout << endl;
}

/*
 * ========================================================================
 * 8. PRACTICAL APPLICATIONS
 * ========================================================================
 */

// Event handler system using functors
class EventHandler {
private:
    vector<function<void(const string&)>> handlers;
public:
    void addHandler(function<void(const string&)> handler) {
        handlers.push_back(handler);
    }
    
    void triggerEvent(const string& event) {
        for (auto& handler : handlers) {
            handler(event);
        }
    }
};

// Custom hash functor for unordered containers
struct PairHash {
    size_t operator()(const pair<int, int>& p) const {
        return hash<int>()(p.first) ^ (hash<int>()(p.second) << 1);
    }
};

void demonstratePracticalApplications() {
    cout << "8. PRACTICAL APPLICATIONS" << endl;
    cout << "==========================" << endl;
    
    // Event handler system
    cout << "Event handler system:" << endl;
    EventHandler event_system;
    
    // Add different types of handlers
    event_system.addHandler([](const string& event) {
        cout << "Logger: Event '" << event << "' occurred" << endl;
    });
    
    event_system.addHandler([](const string& event) {
        cout << "Notifier: Sending notification for '" << event << "'" << endl;
    });
    
    event_system.triggerEvent("user_login");
    event_system.triggerEvent("file_saved");
    
    // Custom sorting for complex scenarios
    cout << "\nComplex sorting scenario:" << endl;
    vector<pair<string, int>> products = {
        {"Laptop", 1000}, {"Mouse", 25}, {"Keyboard", 75}, 
        {"Monitor", 300}, {"Headphones", 150}
    };
    
    cout << "Original products:" << endl;
    for (const auto& product : products) {
        cout << product.first << ": $" << product.second << endl;
    }
    
    // Sort by price (descending), then by name (ascending)
    sort(products.begin(), products.end(),
         [](const pair<string, int>& a, const pair<string, int>& b) {
             if (a.second != b.second) {
                 return a.second > b.second;  // Price descending
             }
             return a.first < b.first;        // Name ascending
         });
    
    cout << "\nSorted by price (desc), then name (asc):" << endl;
    for (const auto& product : products) {
        cout << product.first << ": $" << product.second << endl;
    }
    
    // Using custom hash with unordered containers
    cout << "\nUsing custom hash functor:" << endl;
    unordered_set<pair<int, int>, PairHash> coordinate_set;
    coordinate_set.insert({1, 2});
    coordinate_set.insert({3, 4});
    coordinate_set.insert({1, 2});  // Duplicate, won't be inserted
    
    cout << "Coordinate set contents:" << endl;
    for (const auto& coord : coordinate_set) {
        cout << "(" << coord.first << ", " << coord.second << ") ";
    }
    cout << endl;
    
    // Filtering and transforming data pipeline
    cout << "\nData processing pipeline:" << endl;
    vector<int> raw_data = {1, -2, 3, -4, 5, -6, 7, -8, 9, -10};
    vector<int> processed_data;
    
    cout << "Raw data: ";
    for (int val : raw_data) cout << val << " ";
    cout << endl;
    
    // Pipeline: filter positive -> square -> keep if > 10
    copy_if(raw_data.begin(), raw_data.end(), back_inserter(processed_data),
            [](int x) { return x > 0; });  // Filter positive
    
    transform(processed_data.begin(), processed_data.end(), processed_data.begin(),
              [](int x) { return x * x; });  // Square
    
    processed_data.erase(
        remove_if(processed_data.begin(), processed_data.end(),
                 [](int x) { return x <= 10; }),  // Remove if <= 10
        processed_data.end());
    
    cout << "Processed data (positive -> square -> > 10): ";
    for (int val : processed_data) cout << val << " ";
    cout << endl;
    
    cout << endl;
}

/*
 * ========================================================================
 * MAIN FUNCTION
 * ========================================================================
 */

int main() {
    cout << "=== FUNCTION OBJECTS (FUNCTORS) COMPREHENSIVE GUIDE ===" << endl << endl;
    
    demonstrateBasicFunctors();
    demonstrateSTLFunctors();
    demonstrateCustomComparators();
    demonstrateLambdas();
    demonstrateStdFunction();
    demonstrateFunctorsWithContainers();
    demonstrateAdvancedFunctors();
    demonstratePracticalApplications();
    
    cout << "=== Function Objects Mastery Complete! ===" << endl;
    
    return 0;
}

/*
 * ============================================================================
 * PRACTICE EXERCISES:
 * ============================================================================
 * 
 * 1. Create a functor that counts the number of vowels in a string.
 * 
 * 2. Implement a stateful functor that generates Fibonacci numbers.
 * 
 * 3. Write a custom comparator to sort rectangles by area, then by perimeter.
 * 
 * 4. Create a functor that applies different mathematical operations based on
 *    a parameter (add, multiply, power, etc.).
 * 
 * 5. Implement a event filtering system using function objects.
 * 
 * 6. Write a functor that validates email addresses using regex.
 * 
 * 7. Create a caching functor that memoizes expensive function calls.
 * 
 * 8. Implement a rate limiter using a stateful functor.
 * 
 * 9. Write a functor composition system that chains multiple operations.
 * 
 * 10. Create a custom hash functor for a complex user-defined type.
 * 
 * ============================================================================
 * FUNCTOR DESIGN GUIDELINES:
 * ============================================================================
 * 
 * 1. SINGLE RESPONSIBILITY:
 *    - Each functor should have one clear purpose
 *    - Keep the operator() implementation focused
 * 
 * 2. STATE MANAGEMENT:
 *    - Use const member functions when possible
 *    - Mark mutable data members if state needs to change
 *    - Consider thread safety for shared functors
 * 
 * 3. PERFORMANCE:
 *    - Keep functors lightweight for frequent calls
 *    - Prefer inlining for simple operations
 *    - Consider move semantics for expensive operations
 * 
 * 4. REUSABILITY:
 *    - Make functors templated when appropriate
 *    - Design for composition and chaining
 *    - Provide clear interfaces and documentation
 * 
 * 5. STL COMPATIBILITY:
 *    - Follow STL naming conventions
 *    - Ensure functors work with STL algorithms
 *    - Provide appropriate type traits when needed
 * 
 * ============================================================================
 * WHEN TO USE DIFFERENT CALLABLE TYPES:
 * ============================================================================
 * 
 * Use Function Pointers when:
 * - Working with C APIs
 * - Simple, stateless operations
 * - Runtime function selection from limited set
 * 
 * Use Function Objects when:
 * - Need to maintain state between calls
 * - Want better performance (inlining)
 * - Need customizable behavior
 * - Working extensively with STL algorithms
 * 
 * Use Lambda Expressions when:
 * - Need quick, local function definitions
 * - Simple operations that don't justify separate class
 * - Capturing local variables
 * - One-time use functors
 * 
 * Use std::function when:
 * - Need type erasure for different callable types
 * - Storing callables in containers
 * - Runtime polymorphism with functions
 * - Interface design requiring flexible callable parameters
 * 
 * ============================================================================
 * PERFORMANCE CONSIDERATIONS:
 * ============================================================================
 * 
 * 1. INLINING:
 *    - Function objects are often inlined by compilers
 *    - Lambda expressions typically get inlined
 *    - std::function has virtual call overhead
 * 
 * 2. MEMORY:
 *    - Function objects can carry state efficiently
 *    - std::function has additional storage overhead
 *    - Lambda captures can increase object size
 * 
 * 3. COMPILATION:
 *    - Template functors may increase compilation time
 *    - Heavy use of std::function can slow compilation
 *    - Simple functors compile very quickly
 * 
 * 4. RUNTIME:
 *    - Function objects: fastest (direct call)
 *    - Lambda expressions: fast (usually inlined)
 *    - Function pointers: good (direct jump)
 *    - std::function: slower (virtual dispatch)
 * 
 * ============================================================================
 * BEST PRACTICES:
 * ============================================================================
 * 
 * 1. Prefer lambdas for simple, local operations
 * 2. Use function objects for stateful or reusable operations
 * 3. Choose std::function for type erasure and flexibility
 * 4. Design functors to be copyable and assignable
 * 5. Use const correctness consistently
 * 6. Consider noexcept specifications for simple functors
 * 7. Provide meaningful names for function objects
 * 8. Document captured variables in lambdas clearly
 * 9. Test functors with edge cases and empty inputs
 * 10. Profile performance-critical functor usage
 * 
 * ============================================================================
 */
