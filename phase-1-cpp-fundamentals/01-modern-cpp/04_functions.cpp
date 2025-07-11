/*
 * ============================================================================
 * FUNCTIONS IN C++
 * ============================================================================
 * 
 * THEORY:
 * Functions are blocks of code that perform specific tasks. They help in:
 * - Code reusability and modularity
 * - Breaking complex problems into smaller parts
 * - Easier debugging and maintenance
 * - Avoiding code duplication
 * 
 * FUNCTION COMPONENTS:
 * 1. Return type - data type of value returned (void if no return)
 * 2. Function name - identifier to call the function
 * 3. Parameters - input values (optional)
 * 4. Function body - actual code that executes
 * 
 * TYPES OF FUNCTIONS:
 * 1. Built-in functions (library functions)
 * 2. User-defined functions
 * 3. Recursive functions
 * 4. Inline functions
 * 5. Function overloading
 * 
 * PARAMETER PASSING:
 * 1. Pass by value (copy of value)
 * 2. Pass by reference (alias to original variable)
 * 3. Pass by pointer (address of variable)
 * ============================================================================
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>        // For mathematical functions
#include <vector>       // For vector examples
#include <algorithm>    // For built-in algorithms

using namespace std;

/*
 * ========================================================================
 * FUNCTION DECLARATIONS (PROTOTYPES)
 * ========================================================================
 * Function declarations tell the compiler about function signature
 * before the actual definition. This allows functions to be called
 * before they are defined in the code.
 */

// Basic function prototypes
void displayWelcome();
int addTwoNumbers(int a, int b);
double calculateArea(double length, double width);
bool isPrime(int number);
void printArray(int arr[], int size);

// Pass by reference prototypes
void swapNumbers(int& a, int& b);
void incrementByReference(int& value);

// Function overloading prototypes
int multiply(int a, int b);
double multiply(double a, double b);
int multiply(int a, int b, int c);

// Recursive function prototypes
int factorial(int n);
int fibonacci(int n);
long long power(int base, int exponent);

/*
 * ========================================================================
 * MAIN FUNCTION - PROGRAM ENTRY POINT
 * ========================================================================
 */
int main() {
    cout << "=== C++ FUNCTIONS COMPREHENSIVE GUIDE ===" << endl << endl;
    
    /*
     * ====================================================================
     * 1. BASIC FUNCTION CALLS
     * ====================================================================
     */
    
    cout << "1. BASIC FUNCTION USAGE" << endl;
    cout << "=======================" << endl;
    
    // Calling void function (no return value)
    displayWelcome();
    
    // Calling function with parameters and return value
    int num1 = 15, num2 = 25;
    int sum = addTwoNumbers(num1, num2);
    cout << num1 << " + " << num2 << " = " << sum << endl;
    
    // Calling function with floating-point parameters
    double length = 10.5, width = 7.2;
    double area = calculateArea(length, width);
    cout << "Area of rectangle (" << length << " x " << width << ") = " 
         << area << endl;
    
    /*
     * ====================================================================
     * 2. FUNCTIONS WITH DIFFERENT RETURN TYPES
     * ====================================================================
     */
    
    cout << "\n2. FUNCTIONS WITH DIFFERENT RETURN TYPES" << endl;
    cout << "=========================================" << endl;
    
    // Boolean function
    int testNumber = 17;
    if (isPrime(testNumber)) {
        cout << testNumber << " is a prime number." << endl;
    } else {
        cout << testNumber << " is not a prime number." << endl;
    }
    
    // Function returning string
    string getGreeting(string name) {
        return "Hello, " + name + "! Welcome to C++ Functions!";
    }
    
    string greeting = getGreeting("Alice");
    cout << greeting << endl;
    
    /*
     * ====================================================================
     * 3. PASS BY VALUE VS PASS BY REFERENCE
     * ====================================================================
     */
    
    cout << "\n3. PARAMETER PASSING MECHANISMS" << endl;
    cout << "================================" << endl;
    
    // Pass by value demonstration
    int original = 10;
    cout << "Before increment by value: " << original << endl;
    
    // This function receives a copy, doesn't modify original
    auto incrementByValue = [](int value) {
        value++;
        cout << "Inside increment by value: " << value << endl;
    };
    
    incrementByValue(original);
    cout << "After increment by value: " << original << endl;
    
    // Pass by reference demonstration
    cout << "\nBefore increment by reference: " << original << endl;
    incrementByReference(original);  // Modifies the original variable
    cout << "After increment by reference: " << original << endl;
    
    // Swapping numbers using pass by reference
    int x = 100, y = 200;
    cout << "\nBefore swap: x = " << x << ", y = " << y << endl;
    swapNumbers(x, y);
    cout << "After swap: x = " << x << ", y = " << y << endl;
    
    /*
     * ====================================================================
     * 4. FUNCTION OVERLOADING
     * ====================================================================
     */
    
    cout << "\n4. FUNCTION OVERLOADING" << endl;
    cout << "=======================" << endl;
    
    // Same function name, different parameters
    cout << "multiply(5, 3) = " << multiply(5, 3) << endl;
    cout << "multiply(4.5, 2.0) = " << multiply(4.5, 2.0) << endl;
    cout << "multiply(2, 3, 4) = " << multiply(2, 3, 4) << endl;
    
    /*
     * ====================================================================
     * 5. RECURSIVE FUNCTIONS
     * ====================================================================
     */
    
    cout << "\n5. RECURSIVE FUNCTIONS" << endl;
    cout << "======================" << endl;
    
    // Factorial calculation
    int factNum = 6;
    cout << "Factorial of " << factNum << " = " << factorial(factNum) << endl;
    
    // Fibonacci sequence
    cout << "First 10 Fibonacci numbers: ";
    for (int i = 0; i < 10; i++) {
        cout << fibonacci(i) << " ";
    }
    cout << endl;
    
    // Power calculation
    int base = 2, exponent = 10;
    cout << base << "^" << exponent << " = " << power(base, exponent) << endl;
    
    /*
     * ====================================================================
     * 6. ARRAY FUNCTIONS
     * ====================================================================
     */
    
    cout << "\n6. FUNCTIONS WITH ARRAYS" << endl;
    cout << "========================" << endl;
    
    int numbers[] = {5, 2, 8, 1, 9, 3};
    int arraySize = sizeof(numbers) / sizeof(numbers[0]);
    
    cout << "Original array: ";
    printArray(numbers, arraySize);
    
    // Function to find maximum element
    auto findMax = [](int arr[], int size) -> int {
        int maxVal = arr[0];
        for (int i = 1; i < size; i++) {
            if (arr[i] > maxVal) {
                maxVal = arr[i];
            }
        }
        return maxVal;
    };
    
    cout << "Maximum element: " << findMax(numbers, arraySize) << endl;
    
    // Function to sort array (bubble sort)
    auto bubbleSort = [](int arr[], int size) {
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    };
    
    bubbleSort(numbers, arraySize);
    cout << "Sorted array: ";
    printArray(numbers, arraySize);
    
    /*
     * ====================================================================
     * 7. DEFAULT PARAMETERS
     * ====================================================================
     */
    
    cout << "\n7. DEFAULT PARAMETERS" << endl;
    cout << "=====================" << endl;
    
    // Function with default parameters
    auto calculateInterest = [](double principal, double rate = 5.0, int time = 1) -> double {
        return (principal * rate * time) / 100;
    };
    
    double principal = 1000;
    cout << "Principal: $" << principal << endl;
    cout << "Interest (default rate & time): $" << calculateInterest(principal) << endl;
    cout << "Interest (rate=7%): $" << calculateInterest(principal, 7.0) << endl;
    cout << "Interest (rate=7%, time=3): $" << calculateInterest(principal, 7.0, 3) << endl;
    
    /*
     * ====================================================================
     * 8. INLINE FUNCTIONS
     * ====================================================================
     */
    
    cout << "\n8. INLINE FUNCTIONS" << endl;
    cout << "===================" << endl;
    
    // Inline function for small, frequently called operations
    auto inline square = [](int x) -> int {
        return x * x;
    };
    
    auto inline cube = [](int x) -> int {
        return x * x * x;
    };
    
    int number = 5;
    cout << "Number: " << number << endl;
    cout << "Square: " << square(number) << endl;
    cout << "Cube: " << cube(number) << endl;
    
    /*
     * ====================================================================
     * 9. LAMBDA FUNCTIONS (C++11 and later)
     * ====================================================================
     */
    
    cout << "\n9. LAMBDA FUNCTIONS (MODERN C++)" << endl;
    cout << "================================" << endl;
    
    // Simple lambda
    auto greet = []() {
        cout << "Hello from lambda function!" << endl;
    };
    greet();
    
    // Lambda with parameters
    auto add = [](int a, int b) -> int {
        return a + b;
    };
    cout << "Lambda add(10, 20) = " << add(10, 20) << endl;
    
    // Lambda with capture
    int multiplier = 3;
    auto multiplyBy = [multiplier](int value) -> int {
        return value * multiplier;
    };
    cout << "Multiply 7 by " << multiplier << " = " << multiplyBy(7) << endl;
    
    // Using lambda with STL algorithms
    vector<int> vec = {1, 2, 3, 4, 5};
    cout << "Original vector: ";
    for (int val : vec) cout << val << " ";
    cout << endl;
    
    // Transform each element
    transform(vec.begin(), vec.end(), vec.begin(), [](int x) { return x * x; });
    cout << "Squared vector: ";
    for (int val : vec) cout << val << " ";
    cout << endl;
    
    /*
     * ====================================================================
     * 10. PRACTICAL EXAMPLES
     * ====================================================================
     */
    
    cout << "\n10. PRACTICAL FUNCTION EXAMPLES" << endl;
    cout << "===============================" << endl;
    
    // Example 1: Temperature conversion functions
    auto celsiusToFahrenheit = [](double celsius) -> double {
        return (celsius * 9.0/5.0) + 32.0;
    };
    
    auto fahrenheitToCelsius = [](double fahrenheit) -> double {
        return (fahrenheit - 32.0) * 5.0/9.0;
    };
    
    double temp = 25.0;
    cout << temp << "°C = " << celsiusToFahrenheit(temp) << "°F" << endl;
    cout << "100°F = " << fahrenheitToCelsius(100) << "°C" << endl;
    
    // Example 2: Geometry functions
    auto circleArea = [](double radius) -> double {
        return M_PI * radius * radius;
    };
    
    auto circleCircumference = [](double radius) -> double {
        return 2 * M_PI * radius;
    };
    
    double radius = 5.0;
    cout << "\nCircle with radius " << radius << ":" << endl;
    cout << "Area: " << circleArea(radius) << endl;
    cout << "Circumference: " << circleCircumference(radius) << endl;
    
    // Example 3: String manipulation functions
    auto reverseString = [](string str) -> string {
        string reversed = "";
        for (int i = str.length() - 1; i >= 0; i--) {
            reversed += str[i];
        }
        return reversed;
    };
    
    auto isPalindrome = [&reverseString](string str) -> bool {
        return str == reverseString(str);
    };
    
    string testStr = "radar";
    cout << "\nString: \"" << testStr << "\"" << endl;
    cout << "Reversed: \"" << reverseString(testStr) << "\"" << endl;
    cout << "Is palindrome: " << (isPalindrome(testStr) ? "Yes" : "No") << endl;
    
    cout << "\n=== Functions Mastery Complete! ===" << endl;
    
    return 0;
}

/*
 * ========================================================================
 * FUNCTION DEFINITIONS
 * ========================================================================
 */

// Simple void function
void displayWelcome() {
    cout << "Welcome to the wonderful world of C++ Functions!" << endl;
    cout << "Functions make your code modular and reusable." << endl;
}

// Function with parameters and return value
int addTwoNumbers(int a, int b) {
    return a + b;
}

// Function with floating-point parameters
double calculateArea(double length, double width) {
    return length * width;
}

// Boolean function to check if number is prime
bool isPrime(int number) {
    if (number <= 1) return false;
    if (number <= 3) return true;
    if (number % 2 == 0 || number % 3 == 0) return false;
    
    for (int i = 5; i * i <= number; i += 6) {
        if (number % i == 0 || number % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

// Function to print array elements
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Pass by reference function
void swapNumbers(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void incrementByReference(int& value) {
    value++;
    cout << "Inside increment by reference: " << value << endl;
}

// Function overloading examples
int multiply(int a, int b) {
    return a * b;
}

double multiply(double a, double b) {
    return a * b;
}

int multiply(int a, int b, int c) {
    return a * b * c;
}

// Recursive functions
int factorial(int n) {
    // Base case
    if (n <= 1) {
        return 1;
    }
    // Recursive case
    return n * factorial(n - 1);
}

int fibonacci(int n) {
    // Base cases
    if (n <= 1) {
        return n;
    }
    // Recursive case
    return fibonacci(n - 1) + fibonacci(n - 2);
}

long long power(int base, int exponent) {
    // Base case
    if (exponent == 0) {
        return 1;
    }
    // Recursive case
    if (exponent % 2 == 0) {
        long long half = power(base, exponent / 2);
        return half * half;
    } else {
        return base * power(base, exponent - 1);
    }
}

/*
 * ============================================================================
 * PRACTICE EXERCISES:
 * ============================================================================
 * 
 * 1. Write a function to calculate the GCD (Greatest Common Divisor) of two
 *    numbers using the Euclidean algorithm.
 * 
 * 2. Create a function that checks if a string is a palindrome (case-insensitive).
 * 
 * 3. Implement a function that converts a decimal number to binary representation.
 * 
 * 4. Write overloaded functions to find the maximum of 2, 3, and 4 numbers.
 * 
 * 5. Create a recursive function to calculate the sum of digits of a number.
 * 
 * 6. Implement a function that sorts an array using selection sort algorithm.
 * 
 * 7. Write a function that finds all prime numbers up to a given limit
 *    (Sieve of Eratosthenes).
 * 
 * 8. Create a function that performs matrix multiplication.
 * 
 * 9. Implement a recursive function for binary search.
 * 
 * 10. Write a function that validates an email address format.
 * 
 * ============================================================================
 * FUNCTION BEST PRACTICES:
 * ============================================================================
 * 
 * 1. Use descriptive function names that indicate what the function does
 * 2. Keep functions small and focused on a single task
 * 3. Use const for parameters that shouldn't be modified
 * 4. Prefer pass by reference for large objects to avoid copying
 * 5. Use default parameters judiciously
 * 6. Document complex functions with comments
 * 7. Handle edge cases and validate input parameters
 * 8. Avoid global variables; use parameters and return values
 * 9. Use inline functions for small, frequently called functions
 * 10. Consider using lambda functions for short, local operations
 * 
 * ============================================================================
 * COMMON FUNCTION MISTAKES:
 * ============================================================================
 * 
 * 1. Forgetting to return a value in non-void functions
 * 2. Not declaring function prototypes when needed
 * 3. Passing large objects by value instead of reference
 * 4. Infinite recursion without proper base cases
 * 5. Modifying array parameters without documenting the side effect
 * 6. Using global variables instead of parameters
 * 7. Not handling all possible input cases
 * 8. Function names that don't describe their purpose
 * 
 * ============================================================================
 */
