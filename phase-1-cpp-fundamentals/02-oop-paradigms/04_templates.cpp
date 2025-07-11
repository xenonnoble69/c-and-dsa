/*
 * ============================================================================
 * TEMPLATES - COMPREHENSIVE GUIDE
 * ============================================================================
 * 
 * THEORY:
 * Templates are one of C++'s most powerful features, enabling generic
 * programming and compile-time polymorphism. They allow you to write
 * code that works with multiple types without sacrificing type safety
 * or performance.
 * 
 * KEY CONCEPTS:
 * 
 * 1. TEMPLATE TYPES:
 *    - Function Templates: Generic functions for different types
 *    - Class Templates: Generic classes for different types
 *    - Variable Templates (C++14): Generic variables
 *    - Alias Templates: Template type aliases
 * 
 * 2. TEMPLATE PARAMETERS:
 *    - Type Parameters: template<typename T>
 *    - Non-type Parameters: template<int N>
 *    - Template Template Parameters: template<template<typename> class C>
 *    - Parameter Packs (C++11): template<typename... Args>
 * 
 * 3. TEMPLATE SPECIALIZATION:
 *    - Full Specialization: Specific implementation for specific types
 *    - Partial Specialization: Specialization for subset of types
 *    - SFINAE: Substitution Failure Is Not An Error
 * 
 * 4. ADVANCED FEATURES:
 *    - Template Metaprogramming: Computation at compile time
 *    - Concepts (C++20): Constraints on template parameters
 *    - Auto and decltype: Type deduction
 *    - Variadic Templates: Variable number of template arguments
 * 
 * ADVANTAGES:
 * - Code reuse without runtime overhead
 * - Type safety at compile time
 * - Automatic type deduction
 * - Zero-cost abstraction
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>
#include <type_traits>
#include <utility>
#include <array>
#include <map>
#include <functional>
#include <sstream>
#include <cassert>

using namespace std;

/*
 * ========================================================================
 * 1. FUNCTION TEMPLATES
 * ========================================================================
 */

// Basic function template
template<typename T>
T maximum(T a, T b) {
    return (a > b) ? a : b;
}

// Function template with multiple parameters
template<typename T, typename U>
auto add(T a, U b) -> decltype(a + b) {
    return a + b;
}

// Function template with non-type parameter
template<typename T, int N>
T power(T base) {
    T result = 1;
    for (int i = 0; i < N; ++i) {
        result *= base;
    }
    return result;
}

// Function template with default template argument
template<typename T = int>
T getDefaultValue() {
    return T{};  // Value initialization
}

// Variadic function template
template<typename T>
T sum(T value) {
    return value;  // Base case
}

template<typename T, typename... Args>
T sum(T first, Args... args) {
    return first + sum(args...);  // Recursive case
}

// Function template with perfect forwarding
template<typename T, typename... Args>
unique_ptr<T> make_unique_custom(Args&&... args) {
    return unique_ptr<T>(new T(forward<Args>(args)...));
}

// Function template specialization
template<typename T>
void print_type() {
    cout << "Generic type" << endl;
}

// Full specialization for int
template<>
void print_type<int>() {
    cout << "Integer type" << endl;
}

// Full specialization for string
template<>
void print_type<string>() {
    cout << "String type" << endl;
}

void demonstrateFunctionTemplates() {
    cout << "1. FUNCTION TEMPLATES" << endl;
    cout << "=====================" << endl;
    
    // Basic function template usage
    cout << "Basic function template:" << endl;
    cout << "maximum(5, 3) = " << maximum(5, 3) << endl;
    cout << "maximum(3.14, 2.71) = " << maximum(3.14, 2.71) << endl;
    cout << "maximum(string(\"hello\"), string(\"world\")) = " 
         << maximum(string("hello"), string("world")) << endl;
    
    // Multiple parameter types
    cout << "\nMultiple parameter types:" << endl;
    cout << "add(5, 3.14) = " << add(5, 3.14) << endl;
    cout << "add(string(\"Hello \"), string(\"World\")) = " 
         << add(string("Hello "), string("World")) << endl;
    
    // Non-type parameters
    cout << "\nNon-type parameters:" << endl;
    cout << "power<double, 3>(2.0) = " << power<double, 3>(2.0) << endl;
    cout << "power<int, 5>(2) = " << power<int, 5>(2) << endl;
    
    // Default template arguments
    cout << "\nDefault template arguments:" << endl;
    cout << "getDefaultValue<int>() = " << getDefaultValue<int>() << endl;
    cout << "getDefaultValue<double>() = " << getDefaultValue<double>() << endl;
    cout << "getDefaultValue() = " << getDefaultValue() << endl;  // Uses default int
    
    // Variadic templates
    cout << "\nVariadic templates:" << endl;
    cout << "sum(1) = " << sum(1) << endl;
    cout << "sum(1, 2, 3) = " << sum(1, 2, 3) << endl;
    cout << "sum(1.5, 2.5, 3.5, 4.5) = " << sum(1.5, 2.5, 3.5, 4.5) << endl;
    
    // Perfect forwarding
    cout << "\nPerfect forwarding:" << endl;
    auto ptr1 = make_unique_custom<string>("Hello, Templates!");
    auto ptr2 = make_unique_custom<vector<int>>(5, 42);
    cout << "Created string: " << *ptr1 << endl;
    cout << "Created vector size: " << ptr2->size() << endl;
    
    // Template specialization
    cout << "\nTemplate specialization:" << endl;
    print_type<double>();
    print_type<int>();
    print_type<string>();
    
    cout << endl;
}

/*
 * ========================================================================
 * 2. CLASS TEMPLATES
 * ========================================================================
 */

// Basic class template
template<typename T>
class Stack {
private:
    vector<T> elements;
    
public:
    void push(const T& element) {
        elements.push_back(element);
    }
    
    void pop() {
        if (elements.empty()) {
            throw runtime_error("Stack is empty");
        }
        elements.pop_back();
    }
    
    T& top() {
        if (elements.empty()) {
            throw runtime_error("Stack is empty");
        }
        return elements.back();
    }
    
    const T& top() const {
        if (elements.empty()) {
            throw runtime_error("Stack is empty");
        }
        return elements.back();
    }
    
    bool empty() const {
        return elements.empty();
    }
    
    size_t size() const {
        return elements.size();
    }
};

// Class template with multiple parameters
template<typename Key, typename Value, typename Compare = less<Key>>
class SimpleMap {
private:
    vector<pair<Key, Value>> data;
    Compare comp;
    
public:
    void insert(const Key& key, const Value& value) {
        auto it = find_if(data.begin(), data.end(),
                         [&key](const pair<Key, Value>& p) { return p.first == key; });
        
        if (it != data.end()) {
            it->second = value;  // Update existing
        } else {
            data.emplace_back(key, value);
            // Keep sorted for efficient searching
            sort(data.begin(), data.end(),
                 [this](const pair<Key, Value>& a, const pair<Key, Value>& b) {
                     return comp(a.first, b.first);
                 });
        }
    }
    
    Value& operator[](const Key& key) {
        auto it = find_if(data.begin(), data.end(),
                         [&key](const pair<Key, Value>& p) { return p.first == key; });
        
        if (it != data.end()) {
            return it->second;
        } else {
            data.emplace_back(key, Value{});
            sort(data.begin(), data.end(),
                 [this](const pair<Key, Value>& a, const pair<Key, Value>& b) {
                     return comp(a.first, b.first);
                 });
            return data.back().second;
        }
    }
    
    bool contains(const Key& key) const {
        return find_if(data.begin(), data.end(),
                      [&key](const pair<Key, Value>& p) { return p.first == key; }) != data.end();
    }
    
    size_t size() const { return data.size(); }
    
    void display() const {
        cout << "{";
        for (size_t i = 0; i < data.size(); ++i) {
            cout << data[i].first << ": " << data[i].second;
            if (i < data.size() - 1) cout << ", ";
        }
        cout << "}";
    }
};

// Class template with non-type parameters
template<typename T, size_t Size>
class FixedArray {
private:
    T data[Size];
    
public:
    FixedArray() = default;
    
    FixedArray(const T& initial_value) {
        fill(data, data + Size, initial_value);
    }
    
    T& operator[](size_t index) {
        if (index >= Size) {
            throw out_of_range("Index out of range");
        }
        return data[index];
    }
    
    const T& operator[](size_t index) const {
        if (index >= Size) {
            throw out_of_range("Index out of range");
        }
        return data[index];
    }
    
    constexpr size_t size() const { return Size; }
    
    T* begin() { return data; }
    T* end() { return data + Size; }
    const T* begin() const { return data; }
    const T* end() const { return data + Size; }
};

// Template class with member function templates
template<typename T>
class Container {
private:
    vector<T> elements;
    
public:
    void add(const T& element) {
        elements.push_back(element);
    }
    
    // Member function template
    template<typename InputIt>
    void addRange(InputIt first, InputIt last) {
        elements.insert(elements.end(), first, last);
    }
    
    // Member function template with type conversion
    template<typename U>
    void addConverted(const U& element) {
        elements.push_back(static_cast<T>(element));
    }
    
    size_t size() const { return elements.size(); }
    
    void display() const {
        cout << "[";
        for (size_t i = 0; i < elements.size(); ++i) {
            cout << elements[i];
            if (i < elements.size() - 1) cout << ", ";
        }
        cout << "]";
    }
};

void demonstrateClassTemplates() {
    cout << "2. CLASS TEMPLATES" << endl;
    cout << "==================" << endl;
    
    // Basic class template
    cout << "Basic class template (Stack):" << endl;
    Stack<int> int_stack;
    Stack<string> string_stack;
    
    int_stack.push(10);
    int_stack.push(20);
    int_stack.push(30);
    
    string_stack.push("first");
    string_stack.push("second");
    
    cout << "Int stack size: " << int_stack.size() << endl;
    cout << "Top of int stack: " << int_stack.top() << endl;
    
    cout << "String stack size: " << string_stack.size() << endl;
    cout << "Top of string stack: " << string_stack.top() << endl;
    
    // Multiple template parameters
    cout << "\nMultiple template parameters (SimpleMap):" << endl;
    SimpleMap<string, int> name_age_map;
    name_age_map.insert("Alice", 25);
    name_age_map.insert("Bob", 30);
    name_age_map["Charlie"] = 35;
    
    cout << "Map contents: ";
    name_age_map.display();
    cout << endl;
    
    cout << "Alice's age: " << name_age_map["Alice"] << endl;
    cout << "Contains 'Bob': " << boolalpha << name_age_map.contains("Bob") << endl;
    
    // Non-type parameters
    cout << "\nNon-type parameters (FixedArray):" << endl;
    FixedArray<int, 5> fixed_array(42);
    
    cout << "Fixed array size: " << fixed_array.size() << endl;
    cout << "Initial values: ";
    for (size_t i = 0; i < fixed_array.size(); ++i) {
        cout << fixed_array[i] << " ";
    }
    cout << endl;
    
    // Modify some elements
    fixed_array[0] = 10;
    fixed_array[4] = 50;
    
    cout << "After modification: ";
    for (const auto& element : fixed_array) {
        cout << element << " ";
    }
    cout << endl;
    
    // Member function templates
    cout << "\nMember function templates (Container):" << endl;
    Container<double> container;
    container.add(1.5);
    container.add(2.5);
    
    // Add range using member function template
    vector<double> more_values = {3.5, 4.5, 5.5};
    container.addRange(more_values.begin(), more_values.end());
    
    // Add with type conversion
    container.addConverted(6);  // int to double conversion
    
    cout << "Container contents: ";
    container.display();
    cout << endl;
    
    cout << endl;
}

/*
 * ========================================================================
 * 3. TEMPLATE SPECIALIZATION
 * ========================================================================
 */

// Primary template
template<typename T>
class TypeInfo {
public:
    static string getName() {
        return "Unknown type";
    }
    
    static size_t getSize() {
        return sizeof(T);
    }
    
    static bool isPointer() {
        return false;
    }
};

// Full specialization for int
template<>
class TypeInfo<int> {
public:
    static string getName() {
        return "Integer";
    }
    
    static size_t getSize() {
        return sizeof(int);
    }
    
    static bool isPointer() {
        return false;
    }
};

// Full specialization for pointer types
template<typename T>
class TypeInfo<T*> {
public:
    static string getName() {
        return "Pointer to " + TypeInfo<T>::getName();
    }
    
    static size_t getSize() {
        return sizeof(T*);
    }
    
    static bool isPointer() {
        return true;
    }
};

// Template class for demonstrating partial specialization
template<typename T, typename U>
class Pair {
private:
    T first;
    U second;
    
public:
    Pair(const T& f, const U& s) : first(f), second(s) {}
    
    void display() const {
        cout << "Generic pair: (" << first << ", " << second << ")";
    }
    
    T getFirst() const { return first; }
    U getSecond() const { return second; }
};

// Partial specialization for same types
template<typename T>
class Pair<T, T> {
private:
    T first, second;
    
public:
    Pair(const T& f, const T& s) : first(f), second(s) {}
    
    void display() const {
        cout << "Same type pair: (" << first << ", " << second << ")";
    }
    
    T getFirst() const { return first; }
    T getSecond() const { return second; }
    
    bool areEqual() const {
        return first == second;
    }
};

// SFINAE example - Substitution Failure Is Not An Error
template<typename T>
typename enable_if<is_integral<T>::value, T>::type
safe_divide(T a, T b) {
    if (b == 0) throw runtime_error("Division by zero");
    return a / b;
}

template<typename T>
typename enable_if<is_floating_point<T>::value, T>::type
safe_divide(T a, T b) {
    if (abs(b) < numeric_limits<T>::epsilon()) {
        throw runtime_error("Division by value too close to zero");
    }
    return a / b;
}

// Modern SFINAE with constexpr if (C++17)
template<typename T>
T modern_safe_divide(T a, T b) {
    if constexpr (is_integral_v<T>) {
        if (b == 0) throw runtime_error("Division by zero");
        return a / b;
    } else if constexpr (is_floating_point_v<T>) {
        if (abs(b) < numeric_limits<T>::epsilon()) {
            throw runtime_error("Division by value too close to zero");
        }
        return a / b;
    } else {
        static_assert(is_arithmetic_v<T>, "Type must be arithmetic");
    }
}

void demonstrateTemplateSpecialization() {
    cout << "3. TEMPLATE SPECIALIZATION" << endl;
    cout << "===========================" << endl;
    
    // Full specialization
    cout << "Full specialization (TypeInfo):" << endl;
    cout << "TypeInfo<double>: " << TypeInfo<double>::getName() 
         << ", size: " << TypeInfo<double>::getSize() 
         << ", pointer: " << boolalpha << TypeInfo<double>::isPointer() << endl;
    
    cout << "TypeInfo<int>: " << TypeInfo<int>::getName() 
         << ", size: " << TypeInfo<int>::getSize() 
         << ", pointer: " << boolalpha << TypeInfo<int>::isPointer() << endl;
    
    cout << "TypeInfo<int*>: " << TypeInfo<int*>::getName() 
         << ", size: " << TypeInfo<int*>::getSize() 
         << ", pointer: " << boolalpha << TypeInfo<int*>::isPointer() << endl;
    
    // Partial specialization
    cout << "\nPartial specialization (Pair):" << endl;
    Pair<int, string> mixed_pair(42, "answer");
    Pair<int, int> same_pair(10, 20);
    
    mixed_pair.display(); cout << endl;
    same_pair.display(); cout << endl;
    cout << "Same pair equal: " << boolalpha << same_pair.areEqual() << endl;
    
    // SFINAE
    cout << "\nSFINAE (safe_divide):" << endl;
    try {
        cout << "safe_divide(10, 3) = " << safe_divide(10, 3) << endl;
        cout << "safe_divide(10.0, 3.0) = " << safe_divide(10.0, 3.0) << endl;
        
        // This will throw
        // cout << "safe_divide(10, 0) = " << safe_divide(10, 0) << endl;
    } catch (const runtime_error& e) {
        cout << "Error: " << e.what() << endl;
    }
    
    // Modern SFINAE
    cout << "\nModern SFINAE with constexpr if:" << endl;
    cout << "modern_safe_divide(15, 4) = " << modern_safe_divide(15, 4) << endl;
    cout << "modern_safe_divide(15.5, 4.2) = " << modern_safe_divide(15.5, 4.2) << endl;
    
    cout << endl;
}

/*
 * ========================================================================
 * 4. VARIADIC TEMPLATES
 * ========================================================================
 */

// Simple variadic template example
template<typename... Args>
void print_args(Args... args) {
    cout << "Number of arguments: " << sizeof...(args) << endl;
    
    // C++17 fold expression
    #if __cplusplus >= 201703L
    ((cout << args << " "), ...);
    cout << endl;
    #else
    // Pre-C++17 recursive approach
    print_recursive(args...);
    #endif
}

// Pre-C++17 recursive printing
template<typename T>
void print_recursive(T&& t) {
    cout << t << " ";
    cout << endl;
}

template<typename T, typename... Args>
void print_recursive(T&& t, Args&&... args) {
    cout << t << " ";
    print_recursive(args...);
}

// Variadic template for creating tuples
template<typename... Args>
class SimpleTuple;

// Base case: empty tuple
template<>
class SimpleTuple<> {
public:
    static constexpr size_t size() { return 0; }
};

// Recursive case: tuple with at least one element
template<typename Head, typename... Tail>
class SimpleTuple<Head, Tail...> : private SimpleTuple<Tail...> {
private:
    Head head;
    
public:
    SimpleTuple(Head h, Tail... t) : SimpleTuple<Tail...>(t...), head(h) {}
    
    Head& getHead() { return head; }
    const Head& getHead() const { return head; }
    
    SimpleTuple<Tail...>& getTail() { return static_cast<SimpleTuple<Tail...>&>(*this); }
    const SimpleTuple<Tail...>& getTail() const { return static_cast<const SimpleTuple<Tail...>&>(*this); }
    
    static constexpr size_t size() { return 1 + SimpleTuple<Tail...>::size(); }
};

// Helper function to create tuples
template<typename... Args>
SimpleTuple<Args...> make_simple_tuple(Args... args) {
    return SimpleTuple<Args...>(args...);
}

// Variadic template function with perfect forwarding
template<typename Function, typename... Args>
auto call_with_timing(Function&& func, Args&&... args) -> decltype(func(forward<Args>(args)...)) {
    auto start = chrono::high_resolution_clock::now();
    auto result = func(forward<Args>(args)...);
    auto end = chrono::high_resolution_clock::now();
    
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Function executed in " << duration.count() << " microseconds" << endl;
    
    return result;
}

// Example function to time
int expensive_calculation(int n) {
    int result = 0;
    for (int i = 0; i < n; ++i) {
        result += i * i;
    }
    return result;
}

void demonstrateVariadicTemplates() {
    cout << "4. VARIADIC TEMPLATES" << endl;
    cout << "=====================" << endl;
    
    // Basic variadic template
    cout << "Basic variadic template:" << endl;
    print_args(1, 2.5, "hello", 'c');
    print_args(42);
    print_args();
    
    // Simple tuple implementation
    cout << "\nSimple tuple implementation:" << endl;
    auto tuple1 = make_simple_tuple(42, 3.14, string("hello"));
    cout << "Tuple size: " << tuple1.size() << endl;
    cout << "Head: " << tuple1.getHead() << endl;
    cout << "Tail head: " << tuple1.getTail().getHead() << endl;
    
    // Function timing with perfect forwarding
    cout << "\nFunction timing with perfect forwarding:" << endl;
    int result = call_with_timing(expensive_calculation, 10000);
    cout << "Result: " << result << endl;
    
    // Lambda with timing
    auto lambda = [](int a, int b) { return a + b; };
    int sum_result = call_with_timing(lambda, 10, 20);
    cout << "Lambda result: " << sum_result << endl;
    
    cout << endl;
}

/*
 * ========================================================================
 * 5. TYPE TRAITS AND METAPROGRAMMING
 * ========================================================================
 */

// Custom type trait
template<typename T>
struct is_pointer_custom {
    static constexpr bool value = false;
};

template<typename T>
struct is_pointer_custom<T*> {
    static constexpr bool value = true;
};

// Template metaprogram: factorial at compile time
template<int N>
struct Factorial {
    static constexpr int value = N * Factorial<N - 1>::value;
};

template<>
struct Factorial<0> {
    static constexpr int value = 1;
};

// Template metaprogram: type list
template<typename... Types>
struct TypeList {};

template<typename T, typename... Types>
struct TypeList<T, Types...> {
    using Head = T;
    using Tail = TypeList<Types...>;
    static constexpr size_t size = 1 + sizeof...(Types);
};

template<>
struct TypeList<> {
    static constexpr size_t size = 0;
};

// Find type in type list
template<typename T, typename List>
struct Contains;

template<typename T>
struct Contains<T, TypeList<>> {
    static constexpr bool value = false;
};

template<typename T, typename Head, typename... Tail>
struct Contains<T, TypeList<Head, Tail...>> {
    static constexpr bool value = is_same_v<T, Head> || Contains<T, TypeList<Tail...>>::value;
};

// Conditional type selection
template<bool Condition, typename TrueType, typename FalseType>
struct ConditionalType {
    using type = TrueType;
};

template<typename TrueType, typename FalseType>
struct ConditionalType<false, TrueType, FalseType> {
    using type = FalseType;
};

// Template function using type traits
template<typename T>
void describe_type() {
    cout << "Type information:" << endl;
    cout << "  Is integral: " << boolalpha << is_integral_v<T> << endl;
    cout << "  Is floating point: " << boolalpha << is_floating_point_v<T> << endl;
    cout << "  Is pointer (standard): " << boolalpha << is_pointer_v<T> << endl;
    cout << "  Is pointer (custom): " << boolalpha << is_pointer_custom<T>::value << endl;
    cout << "  Size: " << sizeof(T) << " bytes" << endl;
    cout << "  Alignment: " << alignof(T) << " bytes" << endl;
}

void demonstrateTypeTraitsAndMetaprogramming() {
    cout << "5. TYPE TRAITS AND METAPROGRAMMING" << endl;
    cout << "===================================" << endl;
    
    // Custom type traits
    cout << "Custom type traits:" << endl;
    cout << "is_pointer_custom<int>::value = " << boolalpha << is_pointer_custom<int>::value << endl;
    cout << "is_pointer_custom<int*>::value = " << boolalpha << is_pointer_custom<int*>::value << endl;
    
    // Compile-time factorial
    cout << "\nCompile-time factorial:" << endl;
    cout << "Factorial<5>::value = " << Factorial<5>::value << endl;
    cout << "Factorial<10>::value = " << Factorial<10>::value << endl;
    
    // Type list operations
    cout << "\nType list operations:" << endl;
    using MyTypes = TypeList<int, double, string, char>;
    cout << "TypeList size: " << MyTypes::size << endl;
    cout << "Contains int: " << boolalpha << Contains<int, MyTypes>::value << endl;
    cout << "Contains float: " << boolalpha << Contains<float, MyTypes>::value << endl;
    
    // Conditional type selection
    cout << "\nConditional type selection:" << endl;
    using IntOrDouble = ConditionalType<true, int, double>::type;
    using DoubleOrInt = ConditionalType<false, int, double>::type;
    
    cout << "ConditionalType<true, int, double> is int: " 
         << boolalpha << is_same_v<IntOrDouble, int> << endl;
    cout << "ConditionalType<false, int, double> is double: " 
         << boolalpha << is_same_v<DoubleOrInt, double> << endl;
    
    // Type description using traits
    cout << "\nType descriptions:" << endl;
    describe_type<int>();
    cout << endl;
    describe_type<double*>();
    cout << endl;
    describe_type<string>();
    
    cout << endl;
}

/*
 * ========================================================================
 * 6. ADVANCED TEMPLATE TECHNIQUES
 * ========================================================================
 */

// CRTP (Curiously Recurring Template Pattern)
template<typename Derived>
class Printable {
public:
    void print() const {
        static_cast<const Derived*>(this)->print_impl();
    }
};

class Document : public Printable<Document> {
private:
    string content;
    
public:
    Document(const string& c) : content(c) {}
    
    void print_impl() const {
        cout << "Document: " << content << endl;
    }
};

class Image : public Printable<Image> {
private:
    string filename;
    
public:
    Image(const string& f) : filename(f) {}
    
    void print_impl() const {
        cout << "Image: " << filename << endl;
    }
};

// Template template parameters
template<template<typename> class Container, typename T>
class GenericContainer {
private:
    Container<T> data;
    
public:
    void add(const T& item) {
        data.push_back(item);
    }
    
    size_t size() const {
        return data.size();
    }
    
    void display() const {
        cout << "Container contents: ";
        for (const auto& item : data) {
            cout << item << " ";
        }
        cout << endl;
    }
};

// Alias templates
template<typename T>
using Vec = vector<T>;

template<typename Key, typename Value>
using Map = map<Key, Value>;

// Variable templates (C++14)
template<typename T>
constexpr T pi = T(3.14159265358979323846);

template<typename T>
constexpr bool is_small_v = sizeof(T) <= 4;

// Expression templates (simplified example)
template<typename E>
class VecExpression {
public:
    double operator[](size_t i) const {
        return static_cast<const E&>(*this)[i];
    }
    
    size_t size() const {
        return static_cast<const E&>(*this).size();
    }
};

class Vec3 : public VecExpression<Vec3> {
private:
    array<double, 3> data;
    
public:
    Vec3(double x = 0, double y = 0, double z = 0) : data{{x, y, z}} {}
    
    double operator[](size_t i) const { return data[i]; }
    double& operator[](size_t i) { return data[i]; }
    size_t size() const { return 3; }
    
    template<typename E>
    Vec3& operator=(const VecExpression<E>& expr) {
        for (size_t i = 0; i < size(); ++i) {
            data[i] = expr[i];
        }
        return *this;
    }
    
    void display() const {
        cout << "(" << data[0] << ", " << data[1] << ", " << data[2] << ")";
    }
};

template<typename E1, typename E2>
class VecAdd : public VecExpression<VecAdd<E1, E2>> {
private:
    const E1& u;
    const E2& v;
    
public:
    VecAdd(const VecExpression<E1>& u, const VecExpression<E2>& v) 
        : u(static_cast<const E1&>(u)), v(static_cast<const E2&>(v)) {}
    
    double operator[](size_t i) const {
        return u[i] + v[i];
    }
    
    size_t size() const {
        return u.size();
    }
};

template<typename E1, typename E2>
VecAdd<E1, E2> operator+(const VecExpression<E1>& u, const VecExpression<E2>& v) {
    return VecAdd<E1, E2>(u, v);
}

void demonstrateAdvancedTechniques() {
    cout << "6. ADVANCED TEMPLATE TECHNIQUES" << endl;
    cout << "================================" << endl;
    
    // CRTP
    cout << "CRTP (Curiously Recurring Template Pattern):" << endl;
    Document doc("Important report");
    Image img("photo.jpg");
    
    doc.print();
    img.print();
    
    // Template template parameters
    cout << "\nTemplate template parameters:" << endl;
    GenericContainer<vector, int> vec_container;
    vec_container.add(1);
    vec_container.add(2);
    vec_container.add(3);
    vec_container.display();
    
    // Alias templates
    cout << "\nAlias templates:" << endl;
    Vec<string> string_vec = {"hello", "world", "templates"};
    Map<string, int> string_int_map = {{"one", 1}, {"two", 2}};
    
    cout << "Vec<string> size: " << string_vec.size() << endl;
    cout << "Map<string, int> size: " << string_int_map.size() << endl;
    
    // Variable templates
    cout << "\nVariable templates:" << endl;
    cout << "pi<float> = " << pi<float> << endl;
    cout << "pi<double> = " << pi<double> << endl;
    cout << "is_small_v<char> = " << boolalpha << is_small_v<char> << endl;
    cout << "is_small_v<long long> = " << boolalpha << is_small_v<long long> << endl;
    
    // Expression templates
    cout << "\nExpression templates:" << endl;
    Vec3 v1(1, 2, 3);
    Vec3 v2(4, 5, 6);
    Vec3 v3;
    
    cout << "v1 = "; v1.display(); cout << endl;
    cout << "v2 = "; v2.display(); cout << endl;
    
    v3 = v1 + v2;  // Uses expression template
    cout << "v1 + v2 = "; v3.display(); cout << endl;
    
    cout << endl;
}

/*
 * ========================================================================
 * MAIN FUNCTION
 * ========================================================================
 */

int main() {
    cout << "=== TEMPLATES COMPREHENSIVE GUIDE ===" << endl << endl;
    
    demonstrateFunctionTemplates();
    demonstrateClassTemplates();
    demonstrateTemplateSpecialization();
    demonstrateVariadicTemplates();
    demonstrateTypeTraitsAndMetaprogramming();
    demonstrateAdvancedTechniques();
    
    cout << "=== Templates Mastery Complete! ===" << endl;
    
    return 0;
}

/*
 * ============================================================================
 * PRACTICE EXERCISES:
 * ============================================================================
 * 
 * 1. Create a template function that finds the minimum element in any container.
 * 
 * 2. Implement a generic binary search tree class template.
 * 
 * 3. Write a template class for a thread-safe queue with proper synchronization.
 * 
 * 4. Create a compile-time string class using template metaprogramming.
 * 
 * 5. Implement a template function that works only with arithmetic types.
 * 
 * 6. Write a template class that automatically chooses the best container type.
 * 
 * 7. Create a template-based JSON parser using recursive templates.
 * 
 * 8. Implement a compile-time sort algorithm using template metaprogramming.
 * 
 * 9. Write a template function that can serialize any type to string.
 * 
 * 10. Create a template library for linear algebra operations.
 * 
 * ============================================================================
 * TEMPLATE DESIGN GUIDELINES:
 * ============================================================================
 * 
 * 1. INTERFACE DESIGN:
 *    - Make template interfaces as simple and intuitive as possible
 *    - Use meaningful names for template parameters
 *    - Provide default template arguments when appropriate
 *    - Document template requirements clearly
 * 
 * 2. ERROR HANDLING:
 *    - Use static_assert for compile-time error checking
 *    - Provide clear error messages for template instantiation failures
 *    - Use SFINAE to enable/disable templates based on type properties
 *    - Consider using concepts (C++20) for better error messages
 * 
 * 3. PERFORMANCE:
 *    - Templates are zero-cost abstractions when used properly
 *    - Avoid unnecessary template instantiations
 *    - Use perfect forwarding to avoid unnecessary copies
 *    - Consider compilation time impact of complex templates
 * 
 * 4. MAINTAINABILITY:
 *    - Keep template implementations as simple as possible
 *    - Use template specialization judiciously
 *    - Separate interface from implementation in complex templates
 *    - Provide non-template alternatives when appropriate
 * 
 * ============================================================================
 * TEMPLATE BEST PRACTICES:
 * ============================================================================
 * 
 * 1. FUNCTION TEMPLATES:
 *    - Use typename for dependent types
 *    - Prefer auto return type deduction (C++14)
 *    - Use perfect forwarding for universal references
 *    - Provide overloads rather than specializations when possible
 * 
 * 2. CLASS TEMPLATES:
 *    - Use template template parameters for policy-based design
 *    - Provide type aliases for commonly used instantiations
 *    - Use CRTP for static polymorphism
 *    - Separate template declaration from definition in headers
 * 
 * 3. SPECIALIZATION:
 *    - Prefer partial specialization over full specialization
 *    - Use tag dispatching as an alternative to specialization
 *    - Be careful with specialization ordering
 *    - Document specialization behavior clearly
 * 
 * 4. METAPROGRAMMING:
 *    - Use type traits from <type_traits> when available
 *    - Prefer constexpr functions over template metaprograms (C++11+)
 *    - Use variable templates for type traits (C++17)
 *    - Keep metaprograms simple and well-documented
 * 
 * ============================================================================
 * COMMON TEMPLATE PITFALLS:
 * ============================================================================
 * 
 * 1. COMPILATION ISSUES:
 *    - Template code must be in headers (unless using explicit instantiation)
 *    - Dependent name lookup requires typename/template keywords
 *    - Two-phase lookup can cause surprising behavior
 *    - Circular template dependencies
 * 
 * 2. ERROR MESSAGES:
 *    - Template error messages can be very verbose and confusing
 *    - Use static_assert to provide clearer error messages
 *    - Test templates with various types to catch errors early
 *    - Use concepts (C++20) for better diagnostics
 * 
 * 3. PERFORMANCE:
 *    - Template instantiation can lead to code bloat
 *    - Recursive template instantiation depth limits
 *    - Compilation time can be significantly impacted
 *    - Debug builds may have poor performance with complex templates
 * 
 * 4. DESIGN:
 *    - Over-generalization can make templates hard to use
 *    - Template interfaces should be stable
 *    - Avoid exposing implementation details in template interfaces
 *    - Consider backwards compatibility when evolving templates
 * 
 * ============================================================================
 * MODERN C++ TEMPLATE FEATURES:
 * ============================================================================
 * 
 * C++11:
 * - Variadic templates
 * - Template aliases
 * - decltype and auto
 * - Perfect forwarding
 * 
 * C++14:
 * - Variable templates
 * - Generic lambdas
 * - Return type deduction
 * 
 * C++17:
 * - Class template argument deduction
 * - Fold expressions
 * - constexpr if
 * - Structured bindings
 * 
 * C++20:
 * - Concepts
 * - Abbreviated function templates
 * - Template parameter lists for lambdas
 * - Three-way comparison operator
 * 
 * ============================================================================
 */
