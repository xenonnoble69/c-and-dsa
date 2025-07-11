/*
 * ============================================================================
 * C++ BASICS - FOUNDATIONS OF MODERN C++
 * ============================================================================
 * 
 * THEORY:
 * C++ is a general-purpose programming language that was developed by Bjarne 
 * Stroustrup at Bell Labs starting in 1979. It's an extension of the C language
 * with object-oriented programming capabilities.
 * 
 * KEY CONCEPTS COVERED:
 * 1. Basic Program Structure
 * 2. Variables and Data Types
 * 3. Input/Output Operations
 * 4. Constants and Literals
 * 5. Comments and Documentation
 * 
 * LEARNING OBJECTIVES:
 * - Understand the structure of a C++ program
 * - Learn about different data types and their usage
 * - Master input/output operations
 * - Understand variable declaration and initialization
 * ============================================================================
 */

#include <iostream>     // For input/output operations
#include <string>       // For string operations
#include <iomanip>      // For formatting output

/*
 * THEORY: Namespaces
 * Namespaces are used to organize code and prevent naming conflicts.
 * The 'std' namespace contains all standard library functions.
 * Using 'using namespace std;' allows us to use std functions without prefix.
 */
using namespace std;

int main() {
    /*
     * ========================================================================
     * 1. BASIC OUTPUT - cout (Console Output)
     * ========================================================================
     * cout is used to display output to the console
     * << is the insertion operator
     * endl or \n creates a new line
     */
    
    cout << "=== Welcome to C++ Mastery Course ===" << endl;
    cout << "Chapter 1: C++ Basics and Fundamentals\n" << endl;
    
    /*
     * ========================================================================
     * 2. VARIABLES AND DATA TYPES
     * ========================================================================
     * 
     * PRIMITIVE DATA TYPES:
     * - int: Integer numbers (typically 4 bytes)
     * - float: Single precision floating point (4 bytes)
     * - double: Double precision floating point (8 bytes)
     * - char: Single character (1 byte)
     * - bool: Boolean values (true/false)
     * - string: Sequence of characters (C++ string class)
     */
    
    // Integer Variables
    int age = 25;                    // Direct initialization
    int year(2024);                  // Constructor initialization
    int population{1000000};         // Uniform initialization (C++11)
    
    cout << "Integer Examples:" << endl;
    cout << "Age: " << age << endl;
    cout << "Year: " << year << endl;
    cout << "Population: " << population << endl << endl;
    
    // Floating Point Variables
    float temperature = 36.5f;      // f suffix for float
    double pi = 3.14159265359;       // Higher precision
    double scientific = 1.23e-4;    // Scientific notation
    
    cout << "Floating Point Examples:" << endl;
    cout << "Temperature: " << temperature << "°C" << endl;
    cout << "Pi: " << pi << endl;
    cout << "Scientific: " << scientific << endl << endl;
    
    // Character and String Variables
    char grade = 'A';                // Single quotes for char
    string name = "John Doe";        // Double quotes for string
    string course{"C++ Mastery"};    // Uniform initialization
    
    cout << "Character and String Examples:" << endl;
    cout << "Grade: " << grade << endl;
    cout << "Name: " << name << endl;
    cout << "Course: " << course << endl << endl;
    
    // Boolean Variables
    bool isPassing = true;
    bool isCompleted = false;
    
    cout << "Boolean Examples:" << endl;
    cout << "Is Passing: " << isPassing << endl;           // Prints 1
    cout << "Is Completed: " << isCompleted << endl;       // Prints 0
    cout << "Is Passing (text): " << boolalpha << isPassing << endl;  // Prints true
    cout << endl;
    
    /*
     * ========================================================================
     * 3. CONSTANTS AND LITERALS
     * ========================================================================
     * 
     * THEORY: Constants
     * Constants are values that cannot be changed during program execution.
     * Two ways to declare constants:
     * 1. const keyword
     * 2. #define preprocessor directive (not recommended in modern C++)
     */
    
    const int MAX_STUDENTS = 100;           // Integer constant
    const double GRAVITY = 9.81;            // Double constant
    const string UNIVERSITY = "Tech University";  // String constant
    
    cout << "Constants Examples:" << endl;
    cout << "Max Students: " << MAX_STUDENTS << endl;
    cout << "Gravity: " << GRAVITY << " m/s²" << endl;
    cout << "University: " << UNIVERSITY << endl << endl;
    
    /*
     * ========================================================================
     * 4. BASIC INPUT - cin (Console Input)
     * ========================================================================
     * cin is used to get input from the user
     * >> is the extraction operator
     */
    
    string userName;
    int userAge;
    double userHeight;
    
    cout << "=== User Input Section ===" << endl;
    cout << "Enter your name: ";
    getline(cin, userName);          // getline() reads entire line including spaces
    
    cout << "Enter your age: ";
    cin >> userAge;
    
    cout << "Enter your height (in meters): ";
    cin >> userHeight;
    
    cout << "\n=== Your Information ===" << endl;
    cout << "Name: " << userName << endl;
    cout << "Age: " << userAge << " years" << endl;
    cout << "Height: " << userHeight << " meters" << endl << endl;
    
    /*
     * ========================================================================
     * 5. VARIABLE SCOPE AND LIFETIME
     * ========================================================================
     * 
     * THEORY: Scope
     * Scope determines where a variable can be accessed in the program.
     * - Global scope: Variables declared outside all functions
     * - Local scope: Variables declared inside functions or blocks
     * - Block scope: Variables declared inside { } blocks
     */
    
    cout << "=== Scope Demonstration ===" << endl;
    
    {   // Start of block scope
        int blockVariable = 42;
        cout << "Block variable inside block: " << blockVariable << endl;
    }   // End of block scope - blockVariable is destroyed here
    
    // cout << blockVariable;  // Error! blockVariable is out of scope
    
    /*
     * ========================================================================
     * 6. TYPE CASTING AND CONVERSION
     * ========================================================================
     * 
     * THEORY: Type Casting
     * Converting one data type to another. Two types:
     * 1. Implicit (automatic) - done by compiler
     * 2. Explicit (manual) - done by programmer
     */
    
    cout << "\n=== Type Casting Examples ===" << endl;
    
    // Implicit casting
    int intValue = 10;
    double doubleValue = intValue;    // int to double (safe)
    cout << "Implicit casting - int to double: " << doubleValue << endl;
    
    // Explicit casting (C-style)
    double pi_approx = 3.14159;
    int truncated = (int)pi_approx;   // double to int (data loss)
    cout << "C-style casting - double to int: " << truncated << endl;
    
    // Modern C++ casting (recommended)
    double preciseValue = 3.14159;
    int modernCast = static_cast<int>(preciseValue);
    cout << "Modern casting - double to int: " << modernCast << endl;
    
    /*
     * ========================================================================
     * 7. SIZEOF OPERATOR
     * ========================================================================
     * sizeof operator returns the size of a data type or variable in bytes
     */
    
    cout << "\n=== Memory Size Information ===" << endl;
    cout << "Size of int: " << sizeof(int) << " bytes" << endl;
    cout << "Size of float: " << sizeof(float) << " bytes" << endl;
    cout << "Size of double: " << sizeof(double) << " bytes" << endl;
    cout << "Size of char: " << sizeof(char) << " bytes" << endl;
    cout << "Size of bool: " << sizeof(bool) << " bytes" << endl;
    cout << "Size of string: " << sizeof(string) << " bytes" << endl;
    
    /*
     * ========================================================================
     * 8. ESCAPE SEQUENCES
     * ========================================================================
     * Special characters that are used to format output
     */
    
    cout << "\n=== Escape Sequences ===" << endl;
    cout << "New line: \\n" << endl;
    cout << "Tab: \tTabbed text" << endl;
    cout << "Quote: \"Hello World\"" << endl;
    cout << "Backslash: \\" << endl;
    cout << "Carriage return and new line: \r\n" << endl;
    
    /*
     * ========================================================================
     * 9. FORMATTED OUTPUT
     * ========================================================================
     * Using iomanip library for better output formatting
     */
    
    cout << "\n=== Formatted Output ===" << endl;
    double price = 123.456789;
    
    cout << "Default: " << price << endl;
    cout << "Fixed precision (2): " << fixed << setprecision(2) << price << endl;
    cout << "Width 10, left aligned: " << left << setw(10) << "Price" << price << endl;
    cout << "Width 10, right aligned: " << right << setw(10) << "Price" << price << endl;
    
    cout << "\n=== Program Completed Successfully! ===" << endl;
    
    return 0;  // Indicates successful program termination
}

/*
 * ============================================================================
 * PRACTICE EXERCISES:
 * ============================================================================
 * 
 * 1. Write a program that asks for user's name, age, and favorite number,
 *    then displays them in a formatted way.
 * 
 * 2. Create variables of all primitive data types and display their sizes.
 * 
 * 3. Demonstrate implicit and explicit type casting with different scenarios.
 * 
 * 4. Write a program that calculates the area of a rectangle using user input.
 * 
 * 5. Create a program that demonstrates variable scope with nested blocks.
 * 
 * ============================================================================
 * COMMON MISTAKES TO AVOID:
 * ============================================================================
 * 
 * 1. Forgetting to include necessary headers
 * 2. Using variables before declaration
 * 3. Mixing up = (assignment) and == (comparison)
 * 4. Not handling input buffer issues with cin
 * 5. Using uninitialized variables
 * 
 * ============================================================================
 * NEXT TOPICS:
 * ============================================================================
 * - Operators and Expressions
 * - Control Flow Statements
 * - Functions
 * - Arrays and Pointers
 * ============================================================================
 */
