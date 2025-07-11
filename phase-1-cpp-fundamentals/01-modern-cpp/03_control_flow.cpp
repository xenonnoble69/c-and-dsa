/*
 * ============================================================================
 * CONTROL FLOW STATEMENTS IN C++
 * ============================================================================
 * 
 * THEORY:
 * Control flow statements determine the order in which program statements
 * are executed. They allow programs to make decisions, repeat actions,
 * and jump to different parts of code based on conditions.
 * 
 * TYPES OF CONTROL FLOW:
 * 1. Sequential - Default execution (top to bottom)
 * 2. Selection - if, if-else, switch statements
 * 3. Iteration - for, while, do-while loops
 * 4. Jump - break, continue, goto, return statements
 * 
 * LEARNING OBJECTIVES:
 * - Master conditional statements for decision making
 * - Understand different types of loops and their use cases
 * - Learn about loop control statements
 * - Understand nested control structures
 * ============================================================================
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()

using namespace std;

int main() {
    cout << "=== C++ CONTROL FLOW STATEMENTS ===" << endl << endl;
    
    /*
     * ========================================================================
     * 1. IF STATEMENTS - BASIC DECISION MAKING
     * ========================================================================
     * 
     * SYNTAX:
     * if (condition) {
     *     // statements to execute if condition is true
     * }
     * 
     * The condition must be a boolean expression or something that can be
     * converted to boolean (0 = false, non-zero = true)
     */
    
    cout << "1. IF STATEMENTS" << endl;
    cout << "================" << endl;
    
    int temperature = 25;
    cout << "Current temperature: " << temperature << "°C" << endl;
    
    // Simple if statement
    if (temperature > 30) {
        cout << "It's hot outside!" << endl;
    }
    
    if (temperature >= 20 && temperature <= 30) {
        cout << "Perfect weather for a walk!" << endl;
    }
    
    if (temperature < 20) {
        cout << "It might be a bit chilly." << endl;
    }
    
    /*
     * ========================================================================
     * 2. IF-ELSE STATEMENTS
     * ========================================================================
     * 
     * SYNTAX:
     * if (condition) {
     *     // statements if condition is true
     * } else {
     *     // statements if condition is false
     * }
     */
    
    cout << "\n2. IF-ELSE STATEMENTS" << endl;
    cout << "=====================" << endl;
    
    int age = 20;
    cout << "Age: " << age << endl;
    
    if (age >= 18) {
        cout << "You are eligible to vote!" << endl;
    } else {
        cout << "You are not old enough to vote yet." << endl;
        cout << "You can vote in " << (18 - age) << " years." << endl;
    }
    
    /*
     * ========================================================================
     * 3. IF-ELSE IF-ELSE STATEMENTS (LADDER)
     * ========================================================================
     * Used when you have multiple conditions to check
     */
    
    cout << "\n3. IF-ELSE IF-ELSE LADDER" << endl;
    cout << "=========================" << endl;
    
    int score = 87;
    char grade;
    
    cout << "Student score: " << score << endl;
    
    if (score >= 90) {
        grade = 'A';
        cout << "Excellent! Grade: " << grade << endl;
    } else if (score >= 80) {
        grade = 'B';
        cout << "Good work! Grade: " << grade << endl;
    } else if (score >= 70) {
        grade = 'C';
        cout << "Satisfactory. Grade: " << grade << endl;
    } else if (score >= 60) {
        grade = 'D';
        cout << "Needs improvement. Grade: " << grade << endl;
    } else {
        grade = 'F';
        cout << "Failed. Grade: " << grade << endl;
    }
    
    /*
     * ========================================================================
     * 4. NESTED IF STATEMENTS
     * ========================================================================
     * If statements inside other if statements
     */
    
    cout << "\n4. NESTED IF STATEMENTS" << endl;
    cout << "=======================" << endl;
    
    bool hasTicket = true;
    int ticketAge = 16;
    
    cout << "Checking movie theater entry..." << endl;
    cout << "Has ticket: " << (hasTicket ? "Yes" : "No") << endl;
    cout << "Age: " << ticketAge << endl;
    
    if (hasTicket) {
        cout << "Ticket verified." << endl;
        if (ticketAge >= 18) {
            cout << "Access granted to R-rated movies." << endl;
        } else if (ticketAge >= 13) {
            cout << "Access granted to PG-13 movies." << endl;
        } else {
            cout << "Access limited to G and PG movies." << endl;
        }
    } else {
        cout << "Please purchase a ticket first." << endl;
    }
    
    /*
     * ========================================================================
     * 5. SWITCH STATEMENTS
     * ========================================================================
     * 
     * THEORY:
     * Switch statement is used when you need to compare a variable against
     * many values. It's more efficient than multiple if-else for such cases.
     * 
     * SYNTAX:
     * switch (expression) {
     *     case value1:
     *         // statements
     *         break;
     *     case value2:
     *         // statements
     *         break;
     *     default:
     *         // default statements
     * }
     * 
     * IMPORTANT: Use 'break' to prevent fall-through to next case
     */
    
    cout << "\n5. SWITCH STATEMENTS" << endl;
    cout << "===================" << endl;
    
    int dayOfWeek = 3;
    cout << "Day number: " << dayOfWeek << endl;
    
    switch (dayOfWeek) {
        case 1:
            cout << "Monday - Start of the work week!" << endl;
            break;
        case 2:
            cout << "Tuesday - Getting into the groove." << endl;
            break;
        case 3:
            cout << "Wednesday - Hump day!" << endl;
            break;
        case 4:
            cout << "Thursday - Almost there!" << endl;
            break;
        case 5:
            cout << "Friday - TGIF!" << endl;
            break;
        case 6:
        case 7:
            cout << "Weekend - Time to relax!" << endl;
            break;
        default:
            cout << "Invalid day number!" << endl;
    }
    
    // Switch with characters
    char operation = '+';
    int num1 = 15, num2 = 5;
    
    cout << "\nCalculator: " << num1 << " " << operation << " " << num2 << " = ";
    
    switch (operation) {
        case '+':
            cout << (num1 + num2) << endl;
            break;
        case '-':
            cout << (num1 - num2) << endl;
            break;
        case '*':
            cout << (num1 * num2) << endl;
            break;
        case '/':
            if (num2 != 0) {
                cout << (static_cast<double>(num1) / num2) << endl;
            } else {
                cout << "Error: Division by zero!" << endl;
            }
            break;
        default:
            cout << "Error: Invalid operator!" << endl;
    }
    
    /*
     * ========================================================================
     * 6. WHILE LOOPS
     * ========================================================================
     * 
     * THEORY:
     * While loop executes a block of code repeatedly as long as the
     * condition remains true. The condition is checked before each iteration.
     * 
     * SYNTAX:
     * while (condition) {
     *     // statements to repeat
     *     // make sure to modify condition variable to avoid infinite loop
     * }
     */
    
    cout << "\n6. WHILE LOOPS" << endl;
    cout << "==============" << endl;
    
    // Example 1: Counting
    int counter = 1;
    cout << "Counting from 1 to 5:" << endl;
    while (counter <= 5) {
        cout << counter << " ";
        counter++;  // Important: increment to avoid infinite loop
    }
    cout << endl;
    
    // Example 2: Sum of numbers
    int sum = 0;
    int number = 1;
    cout << "\nSum of numbers 1 to 10:" << endl;
    while (number <= 10) {
        sum += number;
        number++;
    }
    cout << "Sum = " << sum << endl;
    
    // Example 3: Finding factorial
    int factorialNum = 5;
    int factorial = 1;
    int temp = factorialNum;
    
    while (temp > 0) {
        factorial *= temp;
        temp--;
    }
    cout << "\nFactorial of " << factorialNum << " = " << factorial << endl;
    
    /*
     * ========================================================================
     * 7. DO-WHILE LOOPS
     * ========================================================================
     * 
     * THEORY:
     * Do-while loop is similar to while loop, but the condition is checked
     * AFTER executing the block. This guarantees that the loop body executes
     * at least once.
     * 
     * SYNTAX:
     * do {
     *     // statements to repeat
     * } while (condition);
     */
    
    cout << "\n7. DO-WHILE LOOPS" << endl;
    cout << "=================" << endl;
    
    int userChoice;
    cout << "Menu-driven program example:" << endl;
    
    do {
        cout << "\n--- Simple Menu ---" << endl;
        cout << "1. Say Hello" << endl;
        cout << "2. Display current time info" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice (1-3): ";
        
        // For demonstration, we'll simulate user input
        userChoice = 2;  // In real program, you'd use: cin >> userChoice;
        cout << userChoice << endl;
        
        switch (userChoice) {
            case 1:
                cout << "Hello, World!" << endl;
                break;
            case 2:
                cout << "This is a demonstration of do-while loop." << endl;
                break;
            case 3:
                cout << "Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
        
        // For demonstration, we'll exit after one iteration
        userChoice = 3;
        
    } while (userChoice != 3);
    
    /*
     * ========================================================================
     * 8. FOR LOOPS
     * ========================================================================
     * 
     * THEORY:
     * For loop is the most compact loop structure. It's ideal when you
     * know the number of iterations in advance.
     * 
     * SYNTAX:
     * for (initialization; condition; increment/decrement) {
     *     // statements to repeat
     * }
     * 
     * The three parts:
     * 1. Initialization: executed once at the beginning
     * 2. Condition: checked before each iteration
     * 3. Increment/Decrement: executed after each iteration
     */
    
    cout << "\n8. FOR LOOPS" << endl;
    cout << "============" << endl;
    
    // Example 1: Basic counting
    cout << "Numbers 1 to 10:" << endl;
    for (int i = 1; i <= 10; i++) {
        cout << i << " ";
    }
    cout << endl;
    
    // Example 2: Countdown
    cout << "\nCountdown:" << endl;
    for (int i = 5; i >= 1; i--) {
        cout << i << " ";
    }
    cout << "Blast off!" << endl;
    
    // Example 3: Even numbers
    cout << "\nEven numbers from 2 to 20:" << endl;
    for (int i = 2; i <= 20; i += 2) {
        cout << i << " ";
    }
    cout << endl;
    
    // Example 4: Multiplication table
    int tableNum = 7;
    cout << "\nMultiplication table of " << tableNum << ":" << endl;
    for (int i = 1; i <= 10; i++) {
        cout << tableNum << " x " << i << " = " << (tableNum * i) << endl;
    }
    
    /*
     * ========================================================================
     * 9. NESTED LOOPS
     * ========================================================================
     * Loops inside other loops - very powerful for 2D operations
     */
    
    cout << "\n9. NESTED LOOPS" << endl;
    cout << "===============" << endl;
    
    // Example 1: Pattern printing
    cout << "Star pattern:" << endl;
    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= i; j++) {
            cout << "* ";
        }
        cout << endl;
    }
    
    // Example 2: Number pattern
    cout << "\nNumber pattern:" << endl;
    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= i; j++) {
            cout << j << " ";
        }
        cout << endl;
    }
    
    // Example 3: Multiplication table (2D)
    cout << "\nMultiplication table (1-5):" << endl;
    cout << "   ";
    for (int i = 1; i <= 5; i++) {
        cout << setw(4) << i;
    }
    cout << endl;
    
    for (int i = 1; i <= 5; i++) {
        cout << setw(2) << i << ":";
        for (int j = 1; j <= 5; j++) {
            cout << setw(4) << (i * j);
        }
        cout << endl;
    }
    
    /*
     * ========================================================================
     * 10. LOOP CONTROL STATEMENTS
     * ========================================================================
     * 
     * BREAK: Exits the loop immediately
     * CONTINUE: Skips the rest of current iteration and moves to next
     */
    
    cout << "\n10. LOOP CONTROL STATEMENTS" << endl;
    cout << "============================" << endl;
    
    // BREAK example: Find first number divisible by both 3 and 7
    cout << "Finding first number divisible by both 3 and 7:" << endl;
    for (int i = 1; i <= 100; i++) {
        if (i % 3 == 0 && i % 7 == 0) {
            cout << "Found: " << i << endl;
            break;  // Exit loop when found
        }
    }
    
    // CONTINUE example: Print odd numbers only
    cout << "\nOdd numbers from 1 to 10:" << endl;
    for (int i = 1; i <= 10; i++) {
        if (i % 2 == 0) {
            continue;  // Skip even numbers
        }
        cout << i << " ";
    }
    cout << endl;
    
    // Nested loop with break and continue
    cout << "\nNested loop with break (finding prime numbers):" << endl;
    for (int num = 2; num <= 20; num++) {
        bool isPrime = true;
        
        for (int divisor = 2; divisor <= num/2; divisor++) {
            if (num % divisor == 0) {
                isPrime = false;
                break;  // No need to check further
            }
        }
        
        if (isPrime) {
            cout << num << " ";
        }
    }
    cout << endl;
    
    /*
     * ========================================================================
     * 11. PRACTICAL EXAMPLES AND ALGORITHMS
     * ========================================================================
     */
    
    cout << "\n11. PRACTICAL EXAMPLES" << endl;
    cout << "======================" << endl;
    
    // Example 1: Guess the number game
    srand(time(0));  // Seed for random number generation
    int secretNumber = rand() % 10 + 1;  // Random number between 1-10
    int guess = 5;  // Simulated guess
    int attempts = 0;
    
    cout << "Number guessing game (1-10):" << endl;
    cout << "Secret number generated..." << endl;
    
    do {
        attempts++;
        cout << "Attempt " << attempts << ": Guessing " << guess << "... ";
        
        if (guess == secretNumber) {
            cout << "Correct! You won in " << attempts << " attempts!" << endl;
            break;
        } else if (guess < secretNumber) {
            cout << "Too low!" << endl;
            guess++;  // Simulate smarter guessing
        } else {
            cout << "Too high!" << endl;
            guess--;  // Simulate smarter guessing
        }
        
        // Prevent infinite loop in demonstration
        if (attempts >= 5) {
            cout << "Demo ended. Secret number was: " << secretNumber << endl;
            break;
        }
        
    } while (true);
    
    // Example 2: Digital root calculation
    int originalNumber = 9875;
    int digitalRoot = originalNumber;
    
    cout << "\nCalculating digital root of " << originalNumber << ":" << endl;
    
    while (digitalRoot >= 10) {
        int sumOfDigits = 0;
        int temp = digitalRoot;
        
        while (temp > 0) {
            sumOfDigits += temp % 10;
            temp /= 10;
        }
        
        cout << digitalRoot << " -> " << sumOfDigits << endl;
        digitalRoot = sumOfDigits;
    }
    
    cout << "Digital root: " << digitalRoot << endl;
    
    // Example 3: Fibonacci sequence
    cout << "\nFibonacci sequence (first 10 numbers):" << endl;
    int fib1 = 0, fib2 = 1, nextFib;
    
    cout << fib1 << " " << fib2 << " ";
    
    for (int i = 3; i <= 10; i++) {
        nextFib = fib1 + fib2;
        cout << nextFib << " ";
        fib1 = fib2;
        fib2 = nextFib;
    }
    cout << endl;
    
    cout << "\n=== Control Flow Mastery Complete! ===" << endl;
    
    return 0;
}

/*
 * ============================================================================
 * PRACTICE EXERCISES:
 * ============================================================================
 * 
 * 1. Write a program that checks if a number is prime using nested loops.
 * 
 * 2. Create a menu-driven calculator using switch statement and do-while loop.
 * 
 * 3. Print the following pattern using nested for loops:
 *    1
 *    1 2
 *    1 2 3
 *    1 2 3 4
 *    1 2 3 4 5
 * 
 * 4. Write a program to find the GCD (Greatest Common Divisor) of two numbers
 *    using the Euclidean algorithm.
 * 
 * 5. Create a program that reverses a number using while loop.
 * 
 * 6. Implement a simple ATM system with account balance, withdrawal,
 *    deposit, and balance inquiry using appropriate control structures.
 * 
 * 7. Write a program that finds all perfect numbers between 1 and 1000.
 *    (Perfect number = sum of its proper divisors equals the number itself)
 * 
 * 8. Create a program that converts decimal to binary using loops.
 * 
 * ============================================================================
 * LOOP SELECTION GUIDELINES:
 * ============================================================================
 * 
 * Use FOR loop when:
 * - You know the exact number of iterations
 * - You need a counter variable
 * - Working with arrays or containers
 * 
 * Use WHILE loop when:
 * - Number of iterations is unknown
 * - Condition-based termination
 * - Reading input until a sentinel value
 * 
 * Use DO-WHILE loop when:
 * - Loop body must execute at least once
 * - Menu-driven programs
 * - Input validation scenarios
 * 
 * ============================================================================
 * COMMON MISTAKES TO AVOID:
 * ============================================================================
 * 
 * 1. Infinite loops (forgetting to update loop variable)
 * 2. Off-by-one errors (wrong loop bounds)
 * 3. Using = instead of == in conditions
 * 4. Forgetting break statements in switch cases
 * 5. Modifying loop variable inside the loop body incorrectly
 * 6. Not handling edge cases (empty input, negative numbers, etc.)
 * 
 * ============================================================================
 */
