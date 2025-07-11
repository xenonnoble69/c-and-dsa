/*
 * ============================================================================
 * ARRAYS AND POINTERS IN C++
 * ============================================================================
 * 
 * THEORY:
 * Arrays are collections of elements of the same data type stored in 
 * contiguous memory locations. Pointers are variables that store memory
 * addresses of other variables.
 * 
 * ARRAYS:
 * - Fixed size collections of elements
 * - Elements accessed using indices (0-based)
 * - Stored in contiguous memory
 * - Array name represents base address
 * 
 * POINTERS:
 * - Variables that store memory addresses
 * - Provide direct access to memory
 * - Enable dynamic memory allocation
 * - Fundamental for advanced data structures
 * 
 * RELATIONSHIP:
 * - Array names are pointers to first element
 * - Pointer arithmetic allows array traversal
 * - Dynamic arrays created using pointers
 * 
 * MEMORY MANAGEMENT:
 * - Stack memory (automatic variables)
 * - Heap memory (dynamic allocation)
 * - Memory leaks and dangling pointers
 * ============================================================================
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>      // For C-style string functions
#include <algorithm>    // For sorting algorithms
#include <memory>       // For smart pointers

using namespace std;

/*
 * ========================================================================
 * FUNCTION PROTOTYPES
 * ========================================================================
 */
void demonstrateArrays();
void demonstratePointers();
void demonstratePointerArithmetic();
void demonstrateArraysAndPointers();
void demonstrateDynamicMemory();
void demonstrateStringArrays();
void demonstrateMultidimensionalArrays();
void demonstratePointerToPointer();
void demonstrateFunctionPointers();
void demonstrateSmartPointers();

int main() {
    cout << "=== C++ ARRAYS AND POINTERS COMPREHENSIVE GUIDE ===" << endl << endl;
    
    demonstrateArrays();
    demonstratePointers();
    demonstratePointerArithmetic();
    demonstrateArraysAndPointers();
    demonstrateDynamicMemory();
    demonstrateStringArrays();
    demonstrateMultidimensionalArrays();
    demonstratePointerToPointer();
    demonstrateFunctionPointers();
    demonstrateSmartPointers();
    
    cout << "\n=== Arrays and Pointers Mastery Complete! ===" << endl;
    return 0;
}

/*
 * ========================================================================
 * 1. ARRAYS FUNDAMENTALS
 * ========================================================================
 */
void demonstrateArrays() {
    cout << "1. ARRAYS FUNDAMENTALS" << endl;
    cout << "======================" << endl;
    
    // Array declaration and initialization
    int numbers[5] = {10, 20, 30, 40, 50};          // Complete initialization
    int grades[] = {85, 90, 78, 92, 88};            // Size inferred from initializer
    int scores[10] = {95, 87};                       // Partial initialization (rest are 0)
    int zeros[5] = {0};                              // All elements initialized to 0
    int empty[5];                                    // Uninitialized (contains garbage)
    
    cout << "Array initialization examples:" << endl;
    cout << "numbers: ";
    for (int i = 0; i < 5; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;
    
    cout << "grades: ";
    for (int i = 0; i < 5; i++) {
        cout << grades[i] << " ";
    }
    cout << endl;
    
    cout << "scores (partial init): ";
    for (int i = 0; i < 10; i++) {
        cout << scores[i] << " ";
    }
    cout << endl;
    
    // Array properties
    cout << "\nArray properties:" << endl;
    cout << "Size of numbers array: " << sizeof(numbers) << " bytes" << endl;
    cout << "Size of int: " << sizeof(int) << " bytes" << endl;
    cout << "Number of elements: " << sizeof(numbers)/sizeof(int) << endl;
    
    // Array manipulation
    cout << "\nArray manipulation:" << endl;
    cout << "Original numbers: ";
    for (int i = 0; i < 5; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;
    
    // Modify elements
    numbers[0] = 100;
    numbers[4] = 500;
    
    cout << "After modification: ";
    for (int i = 0; i < 5; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;
    
    // Array operations
    int sum = 0;
    int max = numbers[0];
    int min = numbers[0];
    
    for (int i = 0; i < 5; i++) {
        sum += numbers[i];
        if (numbers[i] > max) max = numbers[i];
        if (numbers[i] < min) min = numbers[i];
    }
    
    cout << "Sum: " << sum << endl;
    cout << "Average: " << static_cast<double>(sum) / 5 << endl;
    cout << "Maximum: " << max << endl;
    cout << "Minimum: " << min << endl;
    
    // Array bounds (important security consideration)
    cout << "\nArray bounds checking:" << endl;
    cout << "Valid access - numbers[2]: " << numbers[2] << endl;
    // cout << "Invalid access - numbers[10]: " << numbers[10] << endl;  // Undefined behavior!
    cout << "Always ensure array indices are within valid range [0, size-1]" << endl;
    
    cout << endl;
}

/*
 * ========================================================================
 * 2. POINTERS FUNDAMENTALS
 * ========================================================================
 */
void demonstratePointers() {
    cout << "2. POINTERS FUNDAMENTALS" << endl;
    cout << "========================" << endl;
    
    // Basic pointer concepts
    int value = 42;
    int* ptr = &value;              // Pointer declaration and initialization
    
    cout << "Pointer basics:" << endl;
    cout << "Value: " << value << endl;
    cout << "Address of value (&value): " << &value << endl;
    cout << "Pointer ptr: " << ptr << endl;
    cout << "Value pointed to by ptr (*ptr): " << *ptr << endl;
    cout << "Address of pointer itself (&ptr): " << &ptr << endl;
    
    // Pointer operations
    cout << "\nPointer operations:" << endl;
    cout << "Original value: " << value << endl;
    
    *ptr = 100;  // Modify value through pointer
    cout << "After *ptr = 100, value: " << value << endl;
    
    // Null pointers
    cout << "\nNull pointers:" << endl;
    int* nullPtr = nullptr;         // C++11 way (preferred)
    int* nullPtr2 = NULL;           // C-style (legacy)
    int* nullPtr3 = 0;              // Also valid but not recommended
    
    cout << "nullPtr: " << nullPtr << endl;
    
    // Always check before dereferencing
    if (nullPtr != nullptr) {
        cout << "*nullPtr: " << *nullPtr << endl;
    } else {
        cout << "nullPtr is null, cannot dereference" << endl;
    }
    
    // Pointer to different data types
    cout << "\nPointers to different data types:" << endl;
    
    char character = 'A';
    double pi = 3.14159;
    string name = "John";
    
    char* charPtr = &character;
    double* doublePtr = &pi;
    string* stringPtr = &name;
    
    cout << "char: " << *charPtr << " (address: " << (void*)charPtr << ")" << endl;
    cout << "double: " << *doublePtr << " (address: " << doublePtr << ")" << endl;
    cout << "string: " << *stringPtr << " (address: " << stringPtr << ")" << endl;
    
    // Pointer size
    cout << "\nPointer sizes:" << endl;
    cout << "Size of int*: " << sizeof(int*) << " bytes" << endl;
    cout << "Size of char*: " << sizeof(char*) << " bytes" << endl;
    cout << "Size of double*: " << sizeof(double*) << " bytes" << endl;
    cout << "All pointers have the same size (address size)" << endl;
    
    cout << endl;
}

/*
 * ========================================================================
 * 3. POINTER ARITHMETIC
 * ========================================================================
 */
void demonstratePointerArithmetic() {
    cout << "3. POINTER ARITHMETIC" << endl;
    cout << "=====================" << endl;
    
    int numbers[] = {10, 20, 30, 40, 50};
    int* ptr = numbers;  // Points to first element
    
    cout << "Array: ";
    for (int i = 0; i < 5; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;
    
    cout << "\nPointer arithmetic:" << endl;
    cout << "ptr points to: " << *ptr << " (address: " << ptr << ")" << endl;
    
    ptr++;  // Move to next element
    cout << "After ptr++: " << *ptr << " (address: " << ptr << ")" << endl;
    
    ptr += 2;  // Move 2 elements forward
    cout << "After ptr += 2: " << *ptr << " (address: " << ptr << ")" << endl;
    
    ptr--;  // Move back one element
    cout << "After ptr--: " << *ptr << " (address: " << ptr << ")" << endl;
    
    // Pointer difference
    int* start = numbers;
    int* end = numbers + 4;
    cout << "\nPointer difference:" << endl;
    cout << "end - start = " << (end - start) << " elements" << endl;
    
    // Traversing array using pointer arithmetic
    cout << "\nArray traversal using pointer arithmetic:" << endl;
    ptr = numbers;  // Reset to beginning
    for (int i = 0; i < 5; i++) {
        cout << "Element " << i << ": " << *(ptr + i) << endl;
    }
    
    // Alternative traversal
    cout << "\nAlternative traversal:" << endl;
    for (int* p = numbers; p < numbers + 5; p++) {
        cout << *p << " ";
    }
    cout << endl;
    
    cout << endl;
}

/*
 * ========================================================================
 * 4. ARRAYS AND POINTERS RELATIONSHIP
 * ========================================================================
 */
void demonstrateArraysAndPointers() {
    cout << "4. ARRAYS AND POINTERS RELATIONSHIP" << endl;
    cout << "===================================" << endl;
    
    int arr[] = {1, 2, 3, 4, 5};
    
    cout << "Array and pointer equivalence:" << endl;
    cout << "arr[0] = " << arr[0] << endl;
    cout << "*(arr + 0) = " << *(arr + 0) << endl;
    cout << "arr[2] = " << arr[2] << endl;
    cout << "*(arr + 2) = " << *(arr + 2) << endl;
    
    // Array name as pointer
    cout << "\nArray name as pointer:" << endl;
    cout << "arr = " << arr << endl;
    cout << "&arr[0] = " << &arr[0] << endl;
    cout << "These are the same address!" << endl;
    
    // Pointer assignment
    int* ptr = arr;
    cout << "\nPointer assignment:" << endl;
    cout << "ptr = arr, now ptr points to first element" << endl;
    cout << "ptr[0] = " << ptr[0] << endl;
    cout << "ptr[1] = " << ptr[1] << endl;
    
    // Function parameter passing
    cout << "\nFunction parameter passing:" << endl;
    
    // Function that receives array as pointer
    auto printArrayUsingPointer = [](int* arr, int size) {
        cout << "Array elements: ";
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    };
    
    // Function that receives array (actually receives pointer)
    auto printArrayUsingArray = [](int arr[], int size) {
        cout << "Array elements: ";
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    };
    
    printArrayUsingPointer(arr, 5);
    printArrayUsingArray(arr, 5);
    
    cout << endl;
}

/*
 * ========================================================================
 * 5. DYNAMIC MEMORY ALLOCATION
 * ========================================================================
 */
void demonstrateDynamicMemory() {
    cout << "5. DYNAMIC MEMORY ALLOCATION" << endl;
    cout << "============================" << endl;
    
    // Dynamic allocation of single variable
    cout << "Dynamic allocation of single variable:" << endl;
    int* dynamicInt = new int(42);
    cout << "Value: " << *dynamicInt << endl;
    cout << "Address: " << dynamicInt << endl;
    
    // Modify and display
    *dynamicInt = 100;
    cout << "Modified value: " << *dynamicInt << endl;
    
    // Don't forget to deallocate!
    delete dynamicInt;
    dynamicInt = nullptr;  // Good practice to avoid dangling pointers
    
    // Dynamic allocation of arrays
    cout << "\nDynamic allocation of arrays:" << endl;
    int size = 5;
    int* dynamicArray = new int[size];
    
    // Initialize array
    for (int i = 0; i < size; i++) {
        dynamicArray[i] = (i + 1) * 10;
    }
    
    cout << "Dynamic array: ";
    for (int i = 0; i < size; i++) {
        cout << dynamicArray[i] << " ";
    }
    cout << endl;
    
    // Deallocate array
    delete[] dynamicArray;
    dynamicArray = nullptr;
    
    // Dynamic allocation with initialization
    cout << "\nDynamic allocation with initialization:" << endl;
    double* dynamicDouble = new double(3.14159);
    cout << "Pi: " << *dynamicDouble << endl;
    delete dynamicDouble;
    
    // Memory allocation failure handling
    cout << "\nMemory allocation failure handling:" << endl;
    try {
        // Try to allocate a huge amount of memory
        size_t hugeSize = 1000000000;  // 1 billion integers
        int* hugeArray = new int[hugeSize];
        cout << "Successfully allocated huge array" << endl;
        delete[] hugeArray;
    } catch (const bad_alloc& e) {
        cout << "Memory allocation failed: " << e.what() << endl;
    }
    
    // Using new with nothrow
    cout << "\nUsing new with nothrow:" << endl;
    int* safePtr = new(nothrow) int[1000];
    if (safePtr != nullptr) {
        cout << "Memory allocated successfully" << endl;
        delete[] safePtr;
    } else {
        cout << "Memory allocation failed" << endl;
    }
    
    // Resizing dynamic arrays (manual approach)
    cout << "\nResizing dynamic arrays:" << endl;
    int currentSize = 3;
    int* originalArray = new int[currentSize]{1, 2, 3};
    
    cout << "Original array: ";
    for (int i = 0; i < currentSize; i++) {
        cout << originalArray[i] << " ";
    }
    cout << endl;
    
    // Resize to larger array
    int newSize = 5;
    int* newArray = new int[newSize];
    
    // Copy old elements
    for (int i = 0; i < currentSize; i++) {
        newArray[i] = originalArray[i];
    }
    
    // Initialize new elements
    for (int i = currentSize; i < newSize; i++) {
        newArray[i] = (i + 1) * 10;
    }
    
    cout << "Resized array: ";
    for (int i = 0; i < newSize; i++) {
        cout << newArray[i] << " ";
    }
    cout << endl;
    
    // Clean up
    delete[] originalArray;
    delete[] newArray;
    
    cout << endl;
}

/*
 * ========================================================================
 * 6. STRING ARRAYS AND CHARACTER POINTERS
 * ========================================================================
 */
void demonstrateStringArrays() {
    cout << "6. STRING ARRAYS AND CHARACTER POINTERS" << endl;
    cout << "=======================================" << endl;
    
    // C-style strings (character arrays)
    cout << "C-style strings:" << endl;
    char str1[] = "Hello";                    // Array of characters
    char str2[10] = "World";                  // Fixed size array
    char str3[20];                            // Uninitialized
    
    cout << "str1: " << str1 << endl;
    cout << "str2: " << str2 << endl;
    
    // String operations
    strcpy(str3, "C++ Programming");
    cout << "str3 after strcpy: " << str3 << endl;
    
    // String length
    cout << "Length of str1: " << strlen(str1) << endl;
    cout << "Size of str1 array: " << sizeof(str1) << endl;
    
    // Character pointer
    cout << "\nCharacter pointers:" << endl;
    const char* message = "Hello, World!";    // Points to string literal
    cout << "message: " << message << endl;
    
    // Array of strings
    cout << "\nArray of strings:" << endl;
    const char* fruits[] = {"Apple", "Banana", "Orange", "Grape"};
    int numFruits = sizeof(fruits) / sizeof(fruits[0]);
    
    cout << "Fruits:" << endl;
    for (int i = 0; i < numFruits; i++) {
        cout << i + 1 << ". " << fruits[i] << endl;
    }
    
    // Dynamic string allocation
    cout << "\nDynamic string allocation:" << endl;
    char* dynamicString = new char[50];
    strcpy(dynamicString, "Dynamic String");
    cout << "Dynamic string: " << dynamicString << endl;
    delete[] dynamicString;
    
    // C++ string class vs C-style strings
    cout << "\nC++ string vs C-style string:" << endl;
    string cppString = "C++ String";
    const char* cString = "C String";
    
    cout << "C++ string: " << cppString << endl;
    cout << "C string: " << cString << endl;
    cout << "C++ string length: " << cppString.length() << endl;
    cout << "C string length: " << strlen(cString) << endl;
    
    cout << endl;
}

/*
 * ========================================================================
 * 7. MULTIDIMENSIONAL ARRAYS
 * ========================================================================
 */
void demonstrateMultidimensionalArrays() {
    cout << "7. MULTIDIMENSIONAL ARRAYS" << endl;
    cout << "==========================" << endl;
    
    // 2D arrays
    cout << "2D arrays:" << endl;
    int matrix[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    
    cout << "Matrix:" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            cout << setw(4) << matrix[i][j];
        }
        cout << endl;
    }
    
    // 2D array as pointer to pointer
    cout << "\n2D array memory layout:" << endl;
    cout << "matrix[0] (first row address): " << matrix[0] << endl;
    cout << "matrix[1] (second row address): " << matrix[1] << endl;
    cout << "matrix[2] (third row address): " << matrix[2] << endl;
    
    // Accessing 2D array elements using pointers
    cout << "\nAccessing 2D array using pointers:" << endl;
    cout << "matrix[1][2] = " << matrix[1][2] << endl;
    cout << "*(*(matrix + 1) + 2) = " << *(*(matrix + 1) + 2) << endl;
    
    // Dynamic 2D array allocation
    cout << "\nDynamic 2D array allocation:" << endl;
    int rows = 3, cols = 4;
    
    // Method 1: Array of pointers
    int** dynamicMatrix = new int*[rows];
    for (int i = 0; i < rows; i++) {
        dynamicMatrix[i] = new int[cols];
    }
    
    // Initialize dynamic matrix
    int value = 1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            dynamicMatrix[i][j] = value++;
        }
    }
    
    cout << "Dynamic matrix:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << setw(4) << dynamicMatrix[i][j];
        }
        cout << endl;
    }
    
    // Deallocate dynamic matrix
    for (int i = 0; i < rows; i++) {
        delete[] dynamicMatrix[i];
    }
    delete[] dynamicMatrix;
    
    // Method 2: Single allocation (more efficient)
    cout << "\nSingle allocation 2D array:" << endl;
    int* singleArray = new int[rows * cols];
    
    // Initialize using 1D indexing
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            singleArray[i * cols + j] = (i + 1) * 10 + (j + 1);
        }
    }
    
    // Display using 2D indexing
    cout << "Single allocation matrix:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << setw(4) << singleArray[i * cols + j];
        }
        cout << endl;
    }
    
    delete[] singleArray;
    
    // 3D arrays
    cout << "\n3D arrays:" << endl;
    int cube[2][3][4];
    
    // Initialize 3D array
    int val = 1;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 4; k++) {
                cube[i][j][k] = val++;
            }
        }
    }
    
    // Display 3D array
    for (int i = 0; i < 2; i++) {
        cout << "Layer " << i << ":" << endl;
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 4; k++) {
                cout << setw(4) << cube[i][j][k];
            }
            cout << endl;
        }
        cout << endl;
    }
    
    cout << endl;
}

/*
 * ========================================================================
 * 8. POINTER TO POINTER
 * ========================================================================
 */
void demonstratePointerToPointer() {
    cout << "8. POINTER TO POINTER" << endl;
    cout << "=====================" << endl;
    
    int value = 42;
    int* ptr = &value;
    int** ptrToPtr = &ptr;
    
    cout << "Pointer to pointer:" << endl;
    cout << "value = " << value << endl;
    cout << "ptr = " << ptr << " (points to value)" << endl;
    cout << "ptrToPtr = " << ptrToPtr << " (points to ptr)" << endl;
    
    cout << "\nDereferencing:" << endl;
    cout << "*ptr = " << *ptr << " (value through ptr)" << endl;
    cout << "**ptrToPtr = " << **ptrToPtr << " (value through ptrToPtr)" << endl;
    
    // Modifying value through pointer to pointer
    **ptrToPtr = 100;
    cout << "\nAfter **ptrToPtr = 100:" << endl;
    cout << "value = " << value << endl;
    
    // Array of pointers example
    cout << "\nArray of pointers:" << endl;
    int a = 10, b = 20, c = 30;
    int* ptrArray[] = {&a, &b, &c};
    
    cout << "Values through array of pointers:" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "ptrArray[" << i << "] points to: " << *ptrArray[i] << endl;
    }
    
    // Pointer to array of pointers
    int** ptrToPtrArray = ptrArray;
    cout << "\nUsing pointer to array of pointers:" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "*(ptrToPtrArray + " << i << ") points to: " << *(*(ptrToPtrArray + i)) << endl;
    }
    
    cout << endl;
}

/*
 * ========================================================================
 * 9. FUNCTION POINTERS
 * ========================================================================
 */
void demonstrateFunctionPointers() {
    cout << "9. FUNCTION POINTERS" << endl;
    cout << "===================" << endl;
    
    // Define some functions
    auto add = [](int a, int b) -> int { return a + b; };
    auto multiply = [](int a, int b) -> int { return a * b; };
    auto subtract = [](int a, int b) -> int { return a - b; };
    
    // Function pointer declaration and assignment
    int (*operation)(int, int) = add;
    
    cout << "Function pointer examples:" << endl;
    cout << "operation(5, 3) = " << operation(5, 3) << endl;
    
    // Change function pointer to point to different function
    operation = multiply;
    cout << "After changing to multiply: operation(5, 3) = " << operation(5, 3) << endl;
    
    operation = subtract;
    cout << "After changing to subtract: operation(5, 3) = " << operation(5, 3) << endl;
    
    // Array of function pointers
    cout << "\nArray of function pointers:" << endl;
    int (*operations[])(int, int) = {add, subtract, multiply};
    string names[] = {"add", "subtract", "multiply"};
    
    for (int i = 0; i < 3; i++) {
        cout << names[i] << "(10, 5) = " << operations[i](10, 5) << endl;
    }
    
    // Function pointer as parameter
    auto calculate = [](int a, int b, int (*func)(int, int)) -> int {
        return func(a, b);
    };
    
    cout << "\nFunction pointer as parameter:" << endl;
    cout << "calculate(8, 3, add) = " << calculate(8, 3, add) << endl;
    cout << "calculate(8, 3, multiply) = " << calculate(8, 3, multiply) << endl;
    
    cout << endl;
}

/*
 * ========================================================================
 * 10. SMART POINTERS (MODERN C++)
 * ========================================================================
 */
void demonstrateSmartPointers() {
    cout << "10. SMART POINTERS (MODERN C++)" << endl;
    cout << "===============================" << endl;
    
    // unique_ptr - exclusive ownership
    cout << "unique_ptr - exclusive ownership:" << endl;
    unique_ptr<int> uniquePtr = make_unique<int>(42);
    cout << "uniquePtr value: " << *uniquePtr << endl;
    
    // Transfer ownership
    unique_ptr<int> anotherPtr = move(uniquePtr);
    cout << "After move, anotherPtr value: " << *anotherPtr << endl;
    
    if (uniquePtr == nullptr) {
        cout << "uniquePtr is now null after move" << endl;
    }
    
    // unique_ptr with arrays
    cout << "\nunique_ptr with arrays:" << endl;
    unique_ptr<int[]> arrayPtr = make_unique<int[]>(5);
    for (int i = 0; i < 5; i++) {
        arrayPtr[i] = (i + 1) * 10;
    }
    
    cout << "Array elements: ";
    for (int i = 0; i < 5; i++) {
        cout << arrayPtr[i] << " ";
    }
    cout << endl;
    
    // shared_ptr - shared ownership
    cout << "\nshared_ptr - shared ownership:" << endl;
    shared_ptr<int> sharedPtr1 = make_shared<int>(100);
    cout << "sharedPtr1 value: " << *sharedPtr1 << endl;
    cout << "Reference count: " << sharedPtr1.use_count() << endl;
    
    {
        shared_ptr<int> sharedPtr2 = sharedPtr1;  // Share ownership
        cout << "After creating sharedPtr2:" << endl;
        cout << "Reference count: " << sharedPtr1.use_count() << endl;
        cout << "sharedPtr2 value: " << *sharedPtr2 << endl;
    }  // sharedPtr2 goes out of scope
    
    cout << "After sharedPtr2 goes out of scope:" << endl;
    cout << "Reference count: " << sharedPtr1.use_count() << endl;
    
    // weak_ptr - non-owning observer
    cout << "\nweak_ptr - non-owning observer:" << endl;
    weak_ptr<int> weakPtr = sharedPtr1;
    cout << "weak_ptr expired: " << (weakPtr.expired() ? "Yes" : "No") << endl;
    
    if (auto lockedPtr = weakPtr.lock()) {
        cout << "weak_ptr locked successfully, value: " << *lockedPtr << endl;
    }
    
    // Custom deleter
    cout << "\nCustom deleter:" << endl;
    auto customDeleter = [](int* p) {
        cout << "Custom deleter called for value: " << *p << endl;
        delete p;
    };
    
    {
        unique_ptr<int, decltype(customDeleter)> customPtr(new int(200), customDeleter);
        cout << "customPtr value: " << *customPtr << endl;
    }  // Custom deleter will be called here
    
    cout << endl;
}

/*
 * ============================================================================
 * PRACTICE EXERCISES:
 * ============================================================================
 * 
 * 1. Write a function that reverses an array using pointers.
 * 
 * 2. Implement a function that finds the second largest element in an array.
 * 
 * 3. Create a program that performs matrix multiplication using 2D arrays.
 * 
 * 4. Write a function that removes duplicates from an array.
 * 
 * 5. Implement a dynamic array class with resize functionality.
 * 
 * 6. Create a program that sorts an array of strings using pointers.
 * 
 * 7. Write a function that rotates an array by k positions.
 * 
 * 8. Implement a simple memory pool allocator.
 * 
 * 9. Create a program that demonstrates the difference between deep and shallow copy.
 * 
 * 10. Write a function that merges two sorted arrays into a third array.
 * 
 * ============================================================================
 * MEMORY MANAGEMENT BEST PRACTICES:
 * ============================================================================
 * 
 * 1. Always initialize pointers (to nullptr if not pointing to valid memory)
 * 2. Check for null pointers before dereferencing
 * 3. Free dynamically allocated memory with delete/delete[]
 * 4. Set pointers to nullptr after deletion to avoid dangling pointers
 * 5. Use smart pointers in modern C++ for automatic memory management
 * 6. Avoid memory leaks by matching every new with delete
 * 7. Be careful with pointer arithmetic to avoid buffer overruns
 * 8. Use const-correctness for read-only data
 * 9. Prefer stack allocation over heap allocation when possible
 * 10. Use valgrind or similar tools to detect memory issues
 * 
 * ============================================================================
 * COMMON MISTAKES TO AVOID:
 * ============================================================================
 * 
 * 1. Array index out of bounds
 * 2. Dereferencing null or uninitialized pointers
 * 3. Memory leaks (forgetting to delete dynamically allocated memory)
 * 4. Dangling pointers (using pointers after the memory is freed)
 * 5. Double deletion (calling delete twice on the same pointer)
 * 6. Mixing new/delete with malloc/free
 * 7. Using delete instead of delete[] for arrays
 * 8. Pointer arithmetic errors
 * 9. Not checking return values of dynamic allocation
 * 10. Modifying string literals through char pointers
 * 
 * ============================================================================
 */
