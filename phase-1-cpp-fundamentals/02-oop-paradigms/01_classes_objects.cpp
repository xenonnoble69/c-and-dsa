/*
 * ============================================================================
 * OBJECT-ORIENTED PROGRAMMING: CLASSES AND OBJECTS
 * ============================================================================
 * 
 * THEORY:
 * Object-Oriented Programming (OOP) is a programming paradigm that organizes
 * code around objects rather than functions. It's based on four main principles:
 * 1. Encapsulation - Bundling data and methods together
 * 2. Inheritance - Creating new classes based on existing ones
 * 3. Polymorphism - Objects taking multiple forms
 * 4. Abstraction - Hiding complex implementation details
 * 
 * CLASSES AND OBJECTS:
 * - Class: A blueprint or template for creating objects
 * - Object: An instance of a class
 * - Member variables: Data stored in objects (attributes)
 * - Member functions: Functions that operate on objects (methods)
 * 
 * ACCESS SPECIFIERS:
 * - private: Accessible only within the class
 * - protected: Accessible within class and derived classes
 * - public: Accessible from anywhere
 * 
 * CONSTRUCTORS AND DESTRUCTORS:
 * - Constructor: Special function called when object is created
 * - Destructor: Special function called when object is destroyed
 * ============================================================================
 */

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

/*
 * ========================================================================
 * 1. BASIC CLASS DEFINITION
 * ========================================================================
 */

class Student {
private:
    // Private member variables (data encapsulation)
    string name;
    int age;
    string studentId;
    vector<double> grades;
    
public:
    // Constructor (called when object is created)
    Student() {
        name = "Unknown";
        age = 0;
        studentId = "0000";
        cout << "Default constructor called for student" << endl;
    }
    
    // Parameterized constructor
    Student(string n, int a, string id) {
        name = n;
        age = a;
        studentId = id;
        cout << "Parameterized constructor called for student: " << name << endl;
    }
    
    // Constructor with initializer list (preferred method)
    Student(string n, int a, string id, vector<double> g) : 
        name(n), age(a), studentId(id), grades(g) {
        cout << "Constructor with initializer list called for: " << name << endl;
    }
    
    // Destructor (called when object is destroyed)
    ~Student() {
        cout << "Destructor called for student: " << name << endl;
    }
    
    // Public member functions (methods)
    void setName(const string& n) {
        name = n;
    }
    
    string getName() const {  // const means this function doesn't modify the object
        return name;
    }
    
    void setAge(int a) {
        if (a >= 0 && a <= 150) {  // Basic validation
            age = a;
        } else {
            cout << "Invalid age!" << endl;
        }
    }
    
    int getAge() const {
        return age;
    }
    
    void setStudentId(const string& id) {
        studentId = id;
    }
    
    string getStudentId() const {
        return studentId;
    }
    
    // Method to add a grade
    void addGrade(double grade) {
        if (grade >= 0.0 && grade <= 100.0) {
            grades.push_back(grade);
        } else {
            cout << "Invalid grade! Must be between 0 and 100." << endl;
        }
    }
    
    // Method to calculate average grade
    double calculateAverage() const {
        if (grades.empty()) {
            return 0.0;
        }
        
        double sum = 0.0;
        for (double grade : grades) {
            sum += grade;
        }
        return sum / grades.size();
    }
    
    // Method to display student information
    void displayInfo() const {
        cout << "\n=== Student Information ===" << endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Student ID: " << studentId << endl;
        cout << "Number of grades: " << grades.size() << endl;
        
        if (!grades.empty()) {
            cout << "Grades: ";
            for (double grade : grades) {
                cout << grade << " ";
            }
            cout << endl;
            cout << "Average: " << fixed << setprecision(2) << calculateAverage() << endl;
        }
        cout << "===========================" << endl;
    }
    
    // Method to get grade at specific index
    double getGrade(int index) const {
        if (index >= 0 && index < grades.size()) {
            return grades[index];
        }
        cout << "Invalid grade index!" << endl;
        return -1;
    }
    
    // Method to get total number of grades
    int getGradeCount() const {
        return grades.size();
    }
};

/*
 * ========================================================================
 * 2. CLASS WITH STATIC MEMBERS
 * ========================================================================
 */

class University {
private:
    string name;
    string location;
    static int totalStudents;  // Static member - shared by all objects
    
public:
    // Constructor
    University(string n, string loc) : name(n), location(loc) {
        cout << "University constructor called: " << name << endl;
    }
    
    // Destructor
    ~University() {
        cout << "University destructor called: " << name << endl;
    }
    
    // Static method - can be called without creating an object
    static void enrollStudent() {
        totalStudents++;
        cout << "Student enrolled. Total students: " << totalStudents << endl;
    }
    
    static void graduateStudent() {
        if (totalStudents > 0) {
            totalStudents--;
            cout << "Student graduated. Total students: " << totalStudents << endl;
        }
    }
    
    static int getTotalStudents() {
        return totalStudents;
    }
    
    // Regular methods
    void displayUniversityInfo() const {
        cout << "\n=== University Information ===" << endl;
        cout << "Name: " << name << endl;
        cout << "Location: " << location << endl;
        cout << "Total Students: " << totalStudents << endl;
        cout << "==============================" << endl;
    }
    
    string getName() const { return name; }
    string getLocation() const { return location; }
};

// Static member definition (must be defined outside the class)
int University::totalStudents = 0;

/*
 * ========================================================================
 * 3. CLASS WITH FRIEND FUNCTIONS
 * ========================================================================
 */

class BankAccount {
private:
    string accountNumber;
    string accountHolder;
    double balance;
    
public:
    // Constructor
    BankAccount(string accNum, string holder, double initialBalance = 0.0) 
        : accountNumber(accNum), accountHolder(holder), balance(initialBalance) {
        cout << "Bank account created for: " << accountHolder << endl;
    }
    
    // Destructor
    ~BankAccount() {
        cout << "Bank account closed for: " << accountHolder << endl;
    }
    
    // Public methods
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited $" << amount << ". New balance: $" << balance << endl;
        } else {
            cout << "Invalid deposit amount!" << endl;
        }
    }
    
    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrew $" << amount << ". New balance: $" << balance << endl;
        } else {
            cout << "Invalid withdrawal amount or insufficient funds!" << endl;
        }
    }
    
    double getBalance() const {
        return balance;
    }
    
    void displayAccountInfo() const {
        cout << "\n=== Account Information ===" << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder: " << accountHolder << endl;
        cout << "Balance: $" << fixed << setprecision(2) << balance << endl;
        cout << "===========================" << endl;
    }
    
    // Friend function declaration
    friend void transferFunds(BankAccount& from, BankAccount& to, double amount);
    friend class BankManager;  // Friend class
};

// Friend function definition
void transferFunds(BankAccount& from, BankAccount& to, double amount) {
    if (amount > 0 && amount <= from.balance) {
        from.balance -= amount;
        to.balance += amount;
        cout << "Transferred $" << amount << " from " << from.accountHolder 
             << " to " << to.accountHolder << endl;
    } else {
        cout << "Transfer failed: Invalid amount or insufficient funds!" << endl;
    }
}

// Friend class
class BankManager {
public:
    void viewAccountDetails(const BankAccount& account) {
        cout << "\n=== Manager View ===" << endl;
        cout << "Account: " << account.accountNumber << endl;
        cout << "Holder: " << account.accountHolder << endl;
        cout << "Balance: $" << account.balance << endl;
        cout << "===================" << endl;
    }
    
    void adjustBalance(BankAccount& account, double adjustment) {
        account.balance += adjustment;
        cout << "Balance adjusted by $" << adjustment << endl;
    }
};

/*
 * ========================================================================
 * 4. CLASS WITH COPY CONSTRUCTOR AND ASSIGNMENT OPERATOR
 * ========================================================================
 */

class Book {
private:
    string title;
    string author;
    int pages;
    double* rating;  // Pointer to demonstrate deep copy
    
public:
    // Default constructor
    Book() : title("Unknown"), author("Unknown"), pages(0), rating(nullptr) {
        cout << "Default Book constructor called" << endl;
    }
    
    // Parameterized constructor
    Book(string t, string a, int p, double r) : title(t), author(a), pages(p) {
        rating = new double(r);  // Dynamic allocation
        cout << "Book constructor called: " << title << endl;
    }
    
    // Copy constructor (deep copy)
    Book(const Book& other) : title(other.title), author(other.author), pages(other.pages) {
        if (other.rating != nullptr) {
            rating = new double(*(other.rating));  // Deep copy
        } else {
            rating = nullptr;
        }
        cout << "Copy constructor called for: " << title << endl;
    }
    
    // Assignment operator (deep copy)
    Book& operator=(const Book& other) {
        if (this != &other) {  // Self-assignment check
            // Clean up existing resource
            delete rating;
            
            // Copy data
            title = other.title;
            author = other.author;
            pages = other.pages;
            
            // Deep copy pointer
            if (other.rating != nullptr) {
                rating = new double(*(other.rating));
            } else {
                rating = nullptr;
            }
        }
        cout << "Assignment operator called for: " << title << endl;
        return *this;
    }
    
    // Destructor
    ~Book() {
        delete rating;  // Clean up dynamic memory
        cout << "Book destructor called: " << title << endl;
    }
    
    // Getter methods
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getPages() const { return pages; }
    double getRating() const { 
        return (rating != nullptr) ? *rating : 0.0; 
    }
    
    // Setter methods
    void setTitle(const string& t) { title = t; }
    void setAuthor(const string& a) { author = a; }
    void setPages(int p) { 
        if (p >= 0) pages = p; 
    }
    void setRating(double r) {
        if (rating == nullptr) {
            rating = new double(r);
        } else {
            *rating = r;
        }
    }
    
    // Display method
    void displayBookInfo() const {
        cout << "\n=== Book Information ===" << endl;
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Pages: " << pages << endl;
        cout << "Rating: " << (rating ? to_string(*rating) : "No rating") << endl;
        cout << "=======================" << endl;
    }
};

/*
 * ========================================================================
 * 5. MAIN FUNCTION - DEMONSTRATION
 * ========================================================================
 */

int main() {
    cout << "=== OBJECT-ORIENTED PROGRAMMING: CLASSES AND OBJECTS ===" << endl << endl;
    
    /*
     * ====================================================================
     * 1. BASIC CLASS USAGE
     * ====================================================================
     */
    
    cout << "1. BASIC CLASS USAGE" << endl;
    cout << "====================" << endl;
    
    // Creating objects using different constructors
    Student student1;  // Default constructor
    student1.setName("John Doe");
    student1.setAge(20);
    student1.setStudentId("S001");
    
    Student student2("Alice Smith", 19, "S002");  // Parameterized constructor
    
    vector<double> initialGrades = {85.5, 92.0, 78.5};
    Student student3("Bob Johnson", 21, "S003", initialGrades);  // Constructor with initializer list
    
    // Adding grades
    student1.addGrade(88.5);
    student1.addGrade(91.0);
    student1.addGrade(76.5);
    
    student2.addGrade(95.0);
    student2.addGrade(87.5);
    
    student3.addGrade(89.0);
    
    // Display student information
    student1.displayInfo();
    student2.displayInfo();
    student3.displayInfo();
    
    /*
     * ====================================================================
     * 2. STATIC MEMBERS
     * ====================================================================
     */
    
    cout << "\n2. STATIC MEMBERS" << endl;
    cout << "=================" << endl;
    
    // Accessing static methods without creating objects
    cout << "Initial total students: " << University::getTotalStudents() << endl;
    
    University::enrollStudent();
    University::enrollStudent();
    University::enrollStudent();
    
    // Creating university objects
    University uni1("Tech University", "New York");
    University uni2("Science College", "California");
    
    uni1.displayUniversityInfo();
    uni2.displayUniversityInfo();
    
    University::graduateStudent();
    cout << "Total students after graduation: " << University::getTotalStudents() << endl;
    
    /*
     * ====================================================================
     * 3. FRIEND FUNCTIONS AND CLASSES
     * ====================================================================
     */
    
    cout << "\n3. FRIEND FUNCTIONS AND CLASSES" << endl;
    cout << "================================" << endl;
    
    BankAccount account1("ACC001", "John Doe", 1000.0);
    BankAccount account2("ACC002", "Jane Smith", 500.0);
    
    account1.displayAccountInfo();
    account2.displayAccountInfo();
    
    // Using friend function
    transferFunds(account1, account2, 200.0);
    
    account1.displayAccountInfo();
    account2.displayAccountInfo();
    
    // Using friend class
    BankManager manager;
    manager.viewAccountDetails(account1);
    manager.adjustBalance(account1, 50.0);
    account1.displayAccountInfo();
    
    /*
     * ====================================================================
     * 4. COPY CONSTRUCTOR AND ASSIGNMENT OPERATOR
     * ====================================================================
     */
    
    cout << "\n4. COPY CONSTRUCTOR AND ASSIGNMENT OPERATOR" << endl;
    cout << "============================================" << endl;
    
    Book book1("The C++ Programming Language", "Bjarne Stroustrup", 1376, 4.8);
    book1.displayBookInfo();
    
    // Copy constructor
    Book book2 = book1;  // or Book book2(book1);
    book2.setTitle("Copy of " + book2.getTitle());
    book2.displayBookInfo();
    
    // Assignment operator
    Book book3;
    book3 = book1;
    book3.setTitle("Another copy of " + book1.getTitle());
    book3.displayBookInfo();
    
    // Verify that copies are independent
    book1.setRating(4.9);
    cout << "\nAfter changing book1 rating:" << endl;
    cout << "book1 rating: " << book1.getRating() << endl;
    cout << "book2 rating: " << book2.getRating() << endl;
    cout << "book3 rating: " << book3.getRating() << endl;
    
    /*
     * ====================================================================
     * 5. OBJECT ARRAYS AND VECTORS
     * ====================================================================
     */
    
    cout << "\n5. OBJECT ARRAYS AND VECTORS" << endl;
    cout << "=============================" << endl;
    
    // Array of objects
    Student studentArray[3] = {
        Student("Student A", 20, "SA01"),
        Student("Student B", 19, "SA02"),
        Student("Student C", 21, "SA03")
    };
    
    cout << "Student array:" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "Student " << i + 1 << ": " << studentArray[i].getName() << endl;
    }
    
    // Vector of objects
    vector<Book> bookLibrary;
    bookLibrary.push_back(Book("Book 1", "Author 1", 300, 4.0));
    bookLibrary.push_back(Book("Book 2", "Author 2", 250, 4.2));
    bookLibrary.push_back(Book("Book 3", "Author 3", 400, 4.5));
    
    cout << "\nBook library:" << endl;
    for (const auto& book : bookLibrary) {
        cout << "Title: " << book.getTitle() << ", Rating: " << book.getRating() << endl;
    }
    
    cout << "\n=== Classes and Objects Demonstration Complete! ===" << endl;
    
    return 0;
}

/*
 * ============================================================================
 * PRACTICE EXERCISES:
 * ============================================================================
 * 
 * 1. Create a Rectangle class with length and width, including methods to
 *    calculate area, perimeter, and check if it's a square.
 * 
 * 2. Design a Car class with properties like make, model, year, and mileage.
 *    Include methods for starting, stopping, and driving.
 * 
 * 3. Implement a DateTime class that can store and manipulate dates and times.
 * 
 * 4. Create a Library class that manages a collection of Book objects.
 * 
 * 5. Design a ComplexNumber class with arithmetic operations.
 * 
 * 6. Implement a Matrix class with operations like addition, multiplication.
 * 
 * 7. Create a Person class and derive Employee and Student classes from it.
 * 
 * 8. Design a ShoppingCart class that manages a collection of items.
 * 
 * 9. Implement a Point class and use it to create a Line class.
 * 
 * 10. Create a Temperature class that can convert between Celsius, Fahrenheit,
 *     and Kelvin.
 * 
 * ============================================================================
 * OOP DESIGN PRINCIPLES:
 * ============================================================================
 * 
 * 1. Single Responsibility Principle: A class should have only one reason to change
 * 2. Open/Closed Principle: Classes should be open for extension, closed for modification
 * 3. Liskov Substitution Principle: Derived classes must be substitutable for base classes
 * 4. Interface Segregation Principle: Clients shouldn't depend on interfaces they don't use
 * 5. Dependency Inversion Principle: Depend on abstractions, not concrete implementations
 * 
 * ============================================================================
 * BEST PRACTICES:
 * ============================================================================
 * 
 * 1. Use meaningful class and method names
 * 2. Keep classes focused on a single responsibility
 * 3. Make data members private and provide public accessor methods
 * 4. Use const methods for functions that don't modify the object
 * 5. Initialize all member variables in constructors
 * 6. Implement proper copy constructor and assignment operator for classes with pointers
 * 7. Use initializer lists in constructors for better performance
 * 8. Follow the Rule of Three/Five for resource management
 * 9. Use static members sparingly and appropriately
 * 10. Document your classes and their intended usage
 * 
 * ============================================================================
 */
