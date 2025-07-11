/*
 * ============================================================================
 * OPERATORS AND EXPRESSIONS IN C++
 * ============================================================================
 * 
 * THEORY:
 * Operators are symbols that perform operations on variables and values.
 * An expression is a combination of operators, constants, and variables
 * that evaluates to a single value.
 * 
 * TYPES OF OPERATORS:
 * 1. Arithmetic Operators (+, -, *, /, %, ++, --)
 * 2. Relational/Comparison Operators (<, >, <=, >=, ==, !=)
 * 3. Logical Operators (&&, ||, !)
 * 4. Assignment Operators (=, +=, -=, *=, /=, %=)
 * 5. Bitwise Operators (&, |, ^, ~, <<, >>)
 * 6. Conditional/Ternary Operator (?:)
 * 7. Special Operators (sizeof, &, *, etc.)
 * 
 * OPERATOR PRECEDENCE:
 * Determines the order in which operators are evaluated in expressions.
 * Use parentheses to override default precedence.
 * ============================================================================
 */

#include <iostream>
#include <iomanip>
#include <cmath>        // For mathematical functions

using namespace std;

int main() {
    cout << "=== C++ OPERATORS AND EXPRESSIONS ===" << endl << endl;
    
    /*
     * ========================================================================
     * 1. ARITHMETIC OPERATORS
     * ========================================================================
     * Used for mathematical calculations
     */
    
    cout << "1. ARITHMETIC OPERATORS" << endl;
    cout << "========================" << endl;
    
    int a = 15, b = 4;
    double x = 15.5, y = 4.2;
    
    // Basic arithmetic operations
    cout << "Integer Operations (a=15, b=4):" << endl;
    cout << "Addition (a + b): " << a + b << endl;           // 19
    cout << "Subtraction (a - b): " << a - b << endl;        // 11
    cout << "Multiplication (a * b): " << a * b << endl;     // 60
    cout << "Division (a / b): " << a / b << endl;           // 3 (integer division)
    cout << "Modulus (a % b): " << a % b << endl;            // 3 (remainder)
    
    cout << "\nFloating Point Operations (x=15.5, y=4.2):" << endl;
    cout << "Addition (x + y): " << x + y << endl;           // 19.7
    cout << "Subtraction (x - y): " << x - y << endl;        // 11.3
    cout << "Multiplication (x * y): " << x * y << endl;     // 65.1
    cout << "Division (x / y): " << x / y << endl;           // 3.69048
    // Note: Modulus (%) cannot be used with floating-point numbers
    
    /*
     * THEORY: Integer vs Floating Point Division
     * When both operands are integers, division results in integer division
     * (truncates the decimal part). To get floating point result, at least
     * one operand should be floating point.
     */
    
    cout << "\nDivision Behavior:" << endl;
    cout << "15 / 4 = " << 15 / 4 << " (integer division)" << endl;
    cout << "15.0 / 4 = " << 15.0 / 4 << " (floating point division)" << endl;
    cout << "static_cast<double>(15) / 4 = " << static_cast<double>(15) / 4 << endl;
    
    /*
     * ========================================================================
     * 2. INCREMENT AND DECREMENT OPERATORS
     * ========================================================================
     * ++: Increment by 1
     * --: Decrement by 1
     * Two forms: prefix (++var) and postfix (var++)
     */
    
    cout << "\n2. INCREMENT/DECREMENT OPERATORS" << endl;
    cout << "=================================" << endl;
    
    int counter = 10;
    cout << "Initial counter: " << counter << endl;
    
    // Prefix increment: increment first, then use value
    cout << "Pre-increment (++counter): " << ++counter << endl;  // 11
    cout << "Counter after pre-increment: " << counter << endl;  // 11
    
    // Postfix increment: use value first, then increment
    cout << "Post-increment (counter++): " << counter++ << endl; // 11
    cout << "Counter after post-increment: " << counter << endl; // 12
    
    // Same logic applies to decrement
    cout << "Pre-decrement (--counter): " << --counter << endl;  // 11
    cout << "Post-decrement (counter--): " << counter-- << endl; // 11
    cout << "Final counter: " << counter << endl;               // 10
    
    /*
     * ========================================================================
     * 3. ASSIGNMENT OPERATORS
     * ========================================================================
     * Used to assign values to variables
     */
    
    cout << "\n3. ASSIGNMENT OPERATORS" << endl;
    cout << "========================" << endl;
    
    int num = 20;
    cout << "Initial num: " << num << endl;
    
    num += 5;   // Equivalent to: num = num + 5
    cout << "After num += 5: " << num << endl;       // 25
    
    num -= 3;   // Equivalent to: num = num - 3
    cout << "After num -= 3: " << num << endl;       // 22
    
    num *= 2;   // Equivalent to: num = num * 2
    cout << "After num *= 2: " << num << endl;       // 44
    
    num /= 4;   // Equivalent to: num = num / 4
    cout << "After num /= 4: " << num << endl;       // 11
    
    num %= 3;   // Equivalent to: num = num % 3
    cout << "After num %= 3: " << num << endl;       // 2
    
    /*
     * ========================================================================
     * 4. RELATIONAL/COMPARISON OPERATORS
     * ========================================================================
     * Used to compare two values. Result is always boolean (true or false)
     */
    
    cout << "\n4. RELATIONAL OPERATORS" << endl;
    cout << "========================" << endl;
    
    int p = 10, q = 20, r = 10;
    
    cout << "p = " << p << ", q = " << q << ", r = " << r << endl;
    cout << "p == q: " << (p == q) << " (Equal to)" << endl;           // false (0)
    cout << "p != q: " << (p != q) << " (Not equal to)" << endl;       // true (1)
    cout << "p < q: " << (p < q) << " (Less than)" << endl;            // true (1)
    cout << "p > q: " << (p > q) << " (Greater than)" << endl;         // false (0)
    cout << "p <= r: " << (p <= r) << " (Less than or equal)" << endl; // true (1)
    cout << "p >= r: " << (p >= r) << " (Greater than or equal)" << endl; // true (1)
    
    /*
     * ========================================================================
     * 5. LOGICAL OPERATORS
     * ========================================================================
     * Used to combine or modify boolean expressions
     * &&: Logical AND (both conditions must be true)
     * ||: Logical OR (at least one condition must be true)
     * !: Logical NOT (reverses the boolean value)
     */
    
    cout << "\n5. LOGICAL OPERATORS" << endl;
    cout << "====================" << endl;
    
    bool condition1 = true;
    bool condition2 = false;
    
    cout << "condition1 = " << condition1 << ", condition2 = " << condition2 << endl;
    cout << "condition1 && condition2: " << (condition1 && condition2) << " (AND)" << endl;  // false
    cout << "condition1 || condition2: " << (condition1 || condition2) << " (OR)" << endl;   // true
    cout << "!condition1: " << (!condition1) << " (NOT condition1)" << endl;                 // false
    cout << "!condition2: " << (!condition2) << " (NOT condition2)" << endl;                 // true
    
    // Practical example
    int age = 25;
    bool hasLicense = true;
    bool canDrive = (age >= 18) && hasLicense;
    cout << "\nPractical Example:" << endl;
    cout << "Age: " << age << ", Has License: " << hasLicense << endl;
    cout << "Can Drive: " << canDrive << endl;
    
    /*
     * ========================================================================
     * 6. CONDITIONAL (TERNARY) OPERATOR
     * ========================================================================
     * Syntax: condition ? value_if_true : value_if_false
     * Shorthand for simple if-else statements
     */
    
    cout << "\n6. CONDITIONAL (TERNARY) OPERATOR" << endl;
    cout << "==================================" << endl;
    
    int score = 85;
    string grade = (score >= 90) ? "A" : (score >= 80) ? "B" : (score >= 70) ? "C" : "F";
    cout << "Score: " << score << ", Grade: " << grade << endl;
    
    // Finding maximum of two numbers
    int max_value = (p > q) ? p : q;
    cout << "Maximum of " << p << " and " << q << " is: " << max_value << endl;
    
    /*
     * ========================================================================
     * 7. BITWISE OPERATORS
     * ========================================================================
     * Operate on individual bits of integer values
     * &: Bitwise AND
     * |: Bitwise OR
     * ^: Bitwise XOR
     * ~: Bitwise NOT (complement)
     * <<: Left shift
     * >>: Right shift
     */
    
    cout << "\n7. BITWISE OPERATORS" << endl;
    cout << "====================" << endl;
    
    int bit_a = 12;     // Binary: 1100
    int bit_b = 10;     // Binary: 1010
    
    cout << "bit_a = " << bit_a << " (binary: 1100)" << endl;
    cout << "bit_b = " << bit_b << " (binary: 1010)" << endl;
    cout << "bit_a & bit_b = " << (bit_a & bit_b) << " (AND)" << endl;    // 8 (1000)
    cout << "bit_a | bit_b = " << (bit_a | bit_b) << " (OR)" << endl;     // 14 (1110)
    cout << "bit_a ^ bit_b = " << (bit_a ^ bit_b) << " (XOR)" << endl;    // 6 (0110)
    cout << "~bit_a = " << (~bit_a) << " (NOT)" << endl;                  // -13
    cout << "bit_a << 1 = " << (bit_a << 1) << " (Left shift)" << endl;  // 24
    cout << "bit_a >> 1 = " << (bit_a >> 1) << " (Right shift)" << endl; // 6
    
    /*
     * ========================================================================
     * 8. OPERATOR PRECEDENCE AND ASSOCIATIVITY
     * ========================================================================
     * Order in which operators are evaluated in complex expressions
     */
    
    cout << "\n8. OPERATOR PRECEDENCE" << endl;
    cout << "======================" << endl;
    
    int result1 = 2 + 3 * 4;        // Multiplication first: 2 + 12 = 14
    int result2 = (2 + 3) * 4;      // Parentheses first: 5 * 4 = 20
    int result3 = 10 - 5 - 2;       // Left to right: (10 - 5) - 2 = 3
    
    cout << "2 + 3 * 4 = " << result1 << " (multiplication first)" << endl;
    cout << "(2 + 3) * 4 = " << result2 << " (parentheses first)" << endl;
    cout << "10 - 5 - 2 = " << result3 << " (left to right)" << endl;
    
    /*
     * ========================================================================
     * 9. COMPLEX EXPRESSIONS AND EVALUATION
     * ========================================================================
     * Combining multiple operators in single expressions
     */
    
    cout << "\n9. COMPLEX EXPRESSIONS" << endl;
    cout << "======================" << endl;
    
    int val1 = 5, val2 = 10, val3 = 3;
    
    // Complex arithmetic expression
    int complex_result = val1 * val2 + val3 * 2 - val1 / val3;
    cout << "5 * 10 + 3 * 2 - 5 / 3 = " << complex_result << endl;
    
    // Complex logical expression
    bool complex_condition = (val1 > val3) && (val2 != val1) || (val3 <= 5);
    cout << "(5 > 3) && (10 != 5) || (3 <= 5) = " << complex_condition << endl;
    
    /*
     * ========================================================================
     * 10. PRACTICAL EXAMPLES
     * ========================================================================
     */
    
    cout << "\n10. PRACTICAL EXAMPLES" << endl;
    cout << "======================" << endl;
    
    // Example 1: Calculate area and perimeter of rectangle
    double length = 10.5, width = 7.2;
    double area = length * width;
    double perimeter = 2 * (length + width);
    
    cout << "Rectangle - Length: " << length << ", Width: " << width << endl;
    cout << "Area: " << area << endl;
    cout << "Perimeter: " << perimeter << endl;
    
    // Example 2: Temperature conversion
    double celsius = 25.0;
    double fahrenheit = (celsius * 9.0/5.0) + 32.0;
    double kelvin = celsius + 273.15;
    
    cout << "\nTemperature Conversion:" << endl;
    cout << celsius << "°C = " << fahrenheit << "°F = " << kelvin << "K" << endl;
    
    // Example 3: Check if a number is even or odd using bitwise AND
    int number = 17;
    string parity = (number & 1) ? "odd" : "even";
    cout << "\n" << number << " is " << parity << endl;
    
    // Example 4: Swap two numbers without temporary variable
    int swap_a = 25, swap_b = 35;
    cout << "\nBefore swap: a = " << swap_a << ", b = " << swap_b << endl;
    
    swap_a = swap_a + swap_b;   // a = 60, b = 35
    swap_b = swap_a - swap_b;   // a = 60, b = 25
    swap_a = swap_a - swap_b;   // a = 35, b = 25
    
    cout << "After swap: a = " << swap_a << ", b = " << swap_b << endl;
    
    cout << "\n=== Program Completed Successfully! ===" << endl;
    
    return 0;
}

/*
 * ============================================================================
 * PRACTICE EXERCISES:
 * ============================================================================
 * 
 * 1. Write a program that takes two numbers and performs all arithmetic
 *    operations on them.
 * 
 * 2. Create a simple calculator that takes two numbers and an operator,
 *    then performs the corresponding operation.
 * 
 * 3. Write a program to check if a year is a leap year using logical operators.
 *    (Leap year: divisible by 4, but not by 100, unless also divisible by 400)
 * 
 * 4. Implement a program that converts time from seconds to hours, minutes,
 *    and remaining seconds using arithmetic and assignment operators.
 * 
 * 5. Create a program that demonstrates all bitwise operations with user input.
 * 
 * 6. Write a program that evaluates the quadratic formula: ax² + bx + c = 0
 * 
 * ============================================================================
 * OPERATOR PRECEDENCE TABLE (High to Low):
 * ============================================================================
 * 
 * 1. () [] -> .                    (Highest precedence)
 * 2. ! ~ ++ -- + - * & (type)     (Unary operators)
 * 3. * / %                         (Multiplicative)
 * 4. + -                           (Additive)
 * 5. << >>                         (Shift)
 * 6. < <= > >=                     (Relational)
 * 7. == !=                         (Equality)
 * 8. &                             (Bitwise AND)
 * 9. ^                             (Bitwise XOR)
 * 10. |                            (Bitwise OR)
 * 11. &&                           (Logical AND)
 * 12. ||                           (Logical OR)
 * 13. ?:                           (Conditional)
 * 14. = += -= *= /= %= &= ^= |= <<= >>= (Assignment)
 * 15. ,                            (Comma - Lowest precedence)
 * 
 * ============================================================================
 * COMMON MISTAKES TO AVOID:
 * ============================================================================
 * 
 * 1. Confusing = (assignment) with == (equality)
 * 2. Integer division when floating point is expected
 * 3. Forgetting operator precedence (use parentheses when in doubt)
 * 4. Using = instead of == in conditional statements
 * 5. Modulus operator with floating point numbers
 * 6. Not understanding the difference between prefix and postfix operators
 * 
 * ============================================================================
 */
