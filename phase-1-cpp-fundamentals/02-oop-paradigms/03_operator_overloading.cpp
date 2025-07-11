/*
 * ============================================================================
 * OPERATOR OVERLOADING - COMPREHENSIVE GUIDE
 * ============================================================================
 * 
 * THEORY:
 * Operator overloading allows you to define custom behavior for operators
 * when used with user-defined types. This enables more intuitive and
 * readable code by allowing objects to work with familiar operators.
 * 
 * KEY CONCEPTS:
 * 
 * 1. OVERLOADABLE OPERATORS:
 *    - Arithmetic: +, -, *, /, %, ++, --
 *    - Comparison: ==, !=, <, >, <=, >=, <=>
 *    - Logical: &&, ||, !
 *    - Bitwise: &, |, ^, ~, <<, >>
 *    - Assignment: =, +=, -=, *=, /=, %=, &=, |=, ^=, <<=, >>=
 *    - Subscript: []
 *    - Function call: ()
 *    - Member access: ->, ->*
 *    - Memory: new, delete, new[], delete[]
 *    - Other: ,, type conversion operators
 * 
 * 2. NON-OVERLOADABLE OPERATORS:
 *    - Scope resolution: ::
 *    - Member access: .
 *    - Ternary: ?:
 *    - sizeof
 *    - typeid
 * 
 * 3. IMPLEMENTATION CHOICES:
 *    - Member functions: Access to private data, implicit left operand
 *    - Non-member functions: Symmetric operations, type conversions
 *    - Friend functions: Access to private data + non-member benefits
 * 
 * 4. DESIGN PRINCIPLES:
 *    - Don't overload operators unless it makes code more readable
 *    - Maintain conventional meaning and behavior
 *    - Be consistent with built-in types
 *    - Follow the principle of least surprise
 * ============================================================================
 */

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cmath>
#include <stdexcept>
#include <memory>
#include <sstream>
#include <functional>

using namespace std;

/*
 * ========================================================================
 * 1. ARITHMETIC OPERATORS
 * ========================================================================
 */

class Complex {
private:
    double real, imag;
    
public:
    // Constructors
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}
    
    // Getters
    double getReal() const { return real; }
    double getImag() const { return imag; }
    
    // Arithmetic operators (member functions)
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }
    
    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }
    
    Complex operator*(const Complex& other) const {
        return Complex(real * other.real - imag * other.imag,
                      real * other.imag + imag * other.real);
    }
    
    Complex operator/(const Complex& other) const {
        double denominator = other.real * other.real + other.imag * other.imag;
        if (denominator == 0) {
            throw runtime_error("Division by zero");
        }
        return Complex((real * other.real + imag * other.imag) / denominator,
                      (imag * other.real - real * other.imag) / denominator);
    }
    
    // Unary operators
    Complex operator-() const {
        return Complex(-real, -imag);
    }
    
    Complex operator+() const {
        return *this;
    }
    
    // Compound assignment operators
    Complex& operator+=(const Complex& other) {
        real += other.real;
        imag += other.imag;
        return *this;
    }
    
    Complex& operator-=(const Complex& other) {
        real -= other.real;
        imag -= other.imag;
        return *this;
    }
    
    Complex& operator*=(const Complex& other) {
        double temp_real = real * other.real - imag * other.imag;
        imag = real * other.imag + imag * other.real;
        real = temp_real;
        return *this;
    }
    
    // Prefix increment/decrement
    Complex& operator++() {  // ++c
        ++real;
        return *this;
    }
    
    Complex& operator--() {  // --c
        --real;
        return *this;
    }
    
    // Postfix increment/decrement
    Complex operator++(int) {  // c++
        Complex temp = *this;
        ++real;
        return temp;
    }
    
    Complex operator--(int) {  // c--
        Complex temp = *this;
        --real;
        return temp;
    }
    
    // Magnitude
    double magnitude() const {
        return sqrt(real * real + imag * imag);
    }
    
    // Display
    void display() const {
        cout << real;
        if (imag >= 0) cout << " + " << imag << "i";
        else cout << " - " << -imag << "i";
    }
};

// Non-member operator for scalar multiplication
Complex operator*(double scalar, const Complex& c) {
    return Complex(scalar * c.getReal(), scalar * c.getImag());
}

Complex operator*(const Complex& c, double scalar) {
    return scalar * c;
}

void demonstrateArithmeticOperators() {
    cout << "1. ARITHMETIC OPERATORS" << endl;
    cout << "========================" << endl;
    
    Complex c1(3, 4);
    Complex c2(1, 2);
    
    cout << "c1 = "; c1.display(); cout << endl;
    cout << "c2 = "; c2.display(); cout << endl;
    
    cout << "\nBasic arithmetic:" << endl;
    Complex sum = c1 + c2;
    cout << "c1 + c2 = "; sum.display(); cout << endl;
    
    Complex diff = c1 - c2;
    cout << "c1 - c2 = "; diff.display(); cout << endl;
    
    Complex prod = c1 * c2;
    cout << "c1 * c2 = "; prod.display(); cout << endl;
    
    Complex quot = c1 / c2;
    cout << "c1 / c2 = "; quot.display(); cout << endl;
    
    cout << "\nUnary operators:" << endl;
    Complex neg = -c1;
    cout << "-c1 = "; neg.display(); cout << endl;
    
    Complex pos = +c1;
    cout << "+c1 = "; pos.display(); cout << endl;
    
    cout << "\nCompound assignment:" << endl;
    Complex c3 = c1;
    c3 += c2;
    cout << "c1 += c2: "; c3.display(); cout << endl;
    
    cout << "\nIncrement/Decrement:" << endl;
    Complex c4(5, 3);
    cout << "Original c4: "; c4.display(); cout << endl;
    
    ++c4;
    cout << "After ++c4: "; c4.display(); cout << endl;
    
    Complex c5 = c4++;
    cout << "c4++ returned: "; c5.display(); cout << endl;
    cout << "c4 after post-increment: "; c4.display(); cout << endl;
    
    cout << "\nScalar multiplication:" << endl;
    Complex scaled1 = 2.5 * c1;
    cout << "2.5 * c1 = "; scaled1.display(); cout << endl;
    
    Complex scaled2 = c1 * 2.5;
    cout << "c1 * 2.5 = "; scaled2.display(); cout << endl;
    
    cout << endl;
}

/*
 * ========================================================================
 * 2. COMPARISON OPERATORS
 * ========================================================================
 */

class Point3D {
private:
    double x, y, z;
    
public:
    Point3D(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
    
    // Getters
    double getX() const { return x; }
    double getY() const { return y; }
    double getZ() const { return z; }
    
    // Equality operators
    bool operator==(const Point3D& other) const {
        const double EPSILON = 1e-9;
        return abs(x - other.x) < EPSILON && 
               abs(y - other.y) < EPSILON && 
               abs(z - other.z) < EPSILON;
    }
    
    bool operator!=(const Point3D& other) const {
        return !(*this == other);
    }
    
    // Ordering operators (lexicographic order)
    bool operator<(const Point3D& other) const {
        if (x != other.x) return x < other.x;
        if (y != other.y) return y < other.y;
        return z < other.z;
    }
    
    bool operator<=(const Point3D& other) const {
        return *this < other || *this == other;
    }
    
    bool operator>(const Point3D& other) const {
        return !(*this <= other);
    }
    
    bool operator>=(const Point3D& other) const {
        return !(*this < other);
    }
    
    // C++20 spaceship operator (if available)
    #if __cplusplus >= 202002L
    auto operator<=>(const Point3D& other) const {
        if (auto cmp = x <=> other.x; cmp != 0) return cmp;
        if (auto cmp = y <=> other.y; cmp != 0) return cmp;
        return z <=> other.z;
    }
    #endif
    
    // Distance from origin
    double distanceFromOrigin() const {
        return sqrt(x*x + y*y + z*z);
    }
    
    void display() const {
        cout << "(" << x << ", " << y << ", " << z << ")";
    }
};

void demonstrateComparisonOperators() {
    cout << "2. COMPARISON OPERATORS" << endl;
    cout << "=======================" << endl;
    
    Point3D p1(1, 2, 3);
    Point3D p2(1, 2, 3);
    Point3D p3(2, 1, 3);
    Point3D p4(1, 2, 4);
    
    cout << "p1 = "; p1.display(); cout << endl;
    cout << "p2 = "; p2.display(); cout << endl;
    cout << "p3 = "; p3.display(); cout << endl;
    cout << "p4 = "; p4.display(); cout << endl;
    
    cout << "\nEquality tests:" << endl;
    cout << "p1 == p2: " << boolalpha << (p1 == p2) << endl;
    cout << "p1 == p3: " << boolalpha << (p1 == p3) << endl;
    cout << "p1 != p3: " << boolalpha << (p1 != p3) << endl;
    
    cout << "\nOrdering tests (lexicographic):" << endl;
    cout << "p1 < p3: " << boolalpha << (p1 < p3) << endl;
    cout << "p1 < p4: " << boolalpha << (p1 < p4) << endl;
    cout << "p3 > p1: " << boolalpha << (p3 > p1) << endl;
    cout << "p1 <= p2: " << boolalpha << (p1 <= p2) << endl;
    cout << "p1 >= p2: " << boolalpha << (p1 >= p2) << endl;
    
    cout << "\nSorting points:" << endl;
    vector<Point3D> points = {p4, p1, p3, p2};
    cout << "Before sorting: ";
    for (const auto& p : points) { p.display(); cout << " "; }
    cout << endl;
    
    sort(points.begin(), points.end());
    cout << "After sorting: ";
    for (const auto& p : points) { p.display(); cout << " "; }
    cout << endl;
    
    cout << endl;
}

/*
 * ========================================================================
 * 3. STREAM OPERATORS (I/O)
 * ========================================================================
 */

class Fraction {
private:
    int numerator, denominator;
    
    // Helper function to find GCD
    int gcd(int a, int b) const {
        a = abs(a);
        b = abs(b);
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }
    
    // Simplify the fraction
    void simplify() {
        if (denominator == 0) {
            throw runtime_error("Denominator cannot be zero");
        }
        
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
        
        int g = gcd(numerator, denominator);
        numerator /= g;
        denominator /= g;
    }
    
public:
    Fraction(int num = 0, int den = 1) : numerator(num), denominator(den) {
        simplify();
    }
    
    // Getters
    int getNumerator() const { return numerator; }
    int getDenominator() const { return denominator; }
    
    // Arithmetic operators
    Fraction operator+(const Fraction& other) const {
        return Fraction(numerator * other.denominator + other.numerator * denominator,
                       denominator * other.denominator);
    }
    
    Fraction operator-(const Fraction& other) const {
        return Fraction(numerator * other.denominator - other.numerator * denominator,
                       denominator * other.denominator);
    }
    
    Fraction operator*(const Fraction& other) const {
        return Fraction(numerator * other.numerator, denominator * other.denominator);
    }
    
    Fraction operator/(const Fraction& other) const {
        if (other.numerator == 0) {
            throw runtime_error("Division by zero fraction");
        }
        return Fraction(numerator * other.denominator, denominator * other.numerator);
    }
    
    // Comparison operators
    bool operator==(const Fraction& other) const {
        return numerator == other.numerator && denominator == other.denominator;
    }
    
    bool operator<(const Fraction& other) const {
        return numerator * other.denominator < other.numerator * denominator;
    }
    
    // Type conversion
    operator double() const {
        return static_cast<double>(numerator) / denominator;
    }
    
    // Stream operators (friend functions for access to private members)
    friend ostream& operator<<(ostream& os, const Fraction& frac);
    friend istream& operator>>(istream& is, Fraction& frac);
};

// Output stream operator
ostream& operator<<(ostream& os, const Fraction& frac) {
    if (frac.denominator == 1) {
        os << frac.numerator;
    } else {
        os << frac.numerator << "/" << frac.denominator;
    }
    return os;
}

// Input stream operator
istream& operator>>(istream& is, Fraction& frac) {
    char slash;
    int num, den = 1;
    
    is >> num;
    if (is.peek() == '/') {
        is >> slash >> den;
    }
    
    frac = Fraction(num, den);
    return is;
}

void demonstrateStreamOperators() {
    cout << "3. STREAM OPERATORS (I/O)" << endl;
    cout << "==========================" << endl;
    
    // Output operator demonstration
    cout << "Output operator demonstration:" << endl;
    Fraction f1(3, 4);
    Fraction f2(5, 1);
    Fraction f3(22, 7);
    
    cout << "f1 = " << f1 << endl;
    cout << "f2 = " << f2 << endl;
    cout << "f3 = " << f3 << endl;
    
    // Arithmetic with output
    cout << "\nArithmetic operations:" << endl;
    cout << f1 << " + " << f2 << " = " << (f1 + f2) << endl;
    cout << f1 << " - " << f2 << " = " << (f1 - f2) << endl;
    cout << f1 << " * " << f2 << " = " << (f1 * f2) << endl;
    cout << f1 << " / " << f2 << " = " << (f1 / f2) << endl;
    
    // Type conversion
    cout << "\nType conversion to double:" << endl;
    cout << f1 << " = " << static_cast<double>(f1) << endl;
    cout << f3 << " = " << static_cast<double>(f3) << endl;
    
    // Input operator demonstration
    cout << "\nInput operator demonstration:" << endl;
    cout << "Enter fractions in format 'num/den' or 'num':" << endl;
    
    // Using stringstream to simulate user input
    stringstream input("7/8 5 -3/4");
    Fraction input_frac;
    
    while (input >> input_frac) {
        cout << "Read fraction: " << input_frac << " = " << static_cast<double>(input_frac) << endl;
    }
    
    cout << endl;
}

/*
 * ========================================================================
 * 4. SUBSCRIPT AND FUNCTION CALL OPERATORS
 * ========================================================================
 */

class Matrix {
private:
    vector<vector<double>> data;
    size_t rows, cols;
    
public:
    Matrix(size_t r, size_t c, double initial_value = 0.0) 
        : rows(r), cols(c), data(r, vector<double>(c, initial_value)) {}
    
    // Copy constructor
    Matrix(const Matrix& other) : rows(other.rows), cols(other.cols), data(other.data) {}
    
    // Assignment operator
    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            rows = other.rows;
            cols = other.cols;
            data = other.data;
        }
        return *this;
    }
    
    // Subscript operators
    vector<double>& operator[](size_t row) {
        if (row >= rows) {
            throw out_of_range("Row index out of range");
        }
        return data[row];
    }
    
    const vector<double>& operator[](size_t row) const {
        if (row >= rows) {
            throw out_of_range("Row index out of range");
        }
        return data[row];
    }
    
    // Function call operator for 2D access
    double& operator()(size_t row, size_t col) {
        if (row >= rows || col >= cols) {
            throw out_of_range("Matrix index out of range");
        }
        return data[row][col];
    }
    
    const double& operator()(size_t row, size_t col) const {
        if (row >= rows || col >= cols) {
            throw out_of_range("Matrix index out of range");
        }
        return data[row][col];
    }
    
    // Getters
    size_t getRows() const { return rows; }
    size_t getCols() const { return cols; }
    
    // Matrix operations
    Matrix operator+(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw runtime_error("Matrix dimensions must match for addition");
        }
        
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result(i, j) = (*this)(i, j) + other(i, j);
            }
        }
        return result;
    }
    
    Matrix operator*(const Matrix& other) const {
        if (cols != other.rows) {
            throw runtime_error("Invalid matrix dimensions for multiplication");
        }
        
        Matrix result(rows, other.cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < other.cols; ++j) {
                for (size_t k = 0; k < cols; ++k) {
                    result(i, j) += (*this)(i, k) * other(k, j);
                }
            }
        }
        return result;
    }
    
    // Display matrix
    void display() const {
        for (size_t i = 0; i < rows; ++i) {
            cout << "[";
            for (size_t j = 0; j < cols; ++j) {
                cout << setw(8) << fixed << setprecision(2) << data[i][j];
                if (j < cols - 1) cout << " ";
            }
            cout << "]" << endl;
        }
    }
};

// Functor class demonstrating function call operator
class Polynomial {
private:
    vector<double> coefficients;  // coefficients[i] is coefficient of x^i
    
public:
    Polynomial(const vector<double>& coeffs) : coefficients(coeffs) {}
    
    // Function call operator to evaluate polynomial
    double operator()(double x) const {
        double result = 0.0;
        double power = 1.0;
        
        for (double coeff : coefficients) {
            result += coeff * power;
            power *= x;
        }
        
        return result;
    }
    
    // Display polynomial
    void display() const {
        cout << "P(x) = ";
        bool first = true;
        
        for (size_t i = 0; i < coefficients.size(); ++i) {
            if (coefficients[i] != 0.0) {
                if (!first && coefficients[i] > 0) cout << " + ";
                else if (coefficients[i] < 0) cout << " - ";
                
                if (i == 0) {
                    cout << abs(coefficients[i]);
                } else if (i == 1) {
                    if (abs(coefficients[i]) != 1.0) cout << abs(coefficients[i]);
                    cout << "x";
                } else {
                    if (abs(coefficients[i]) != 1.0) cout << abs(coefficients[i]);
                    cout << "x^" << i;
                }
                first = false;
            }
        }
        if (first) cout << "0";
    }
};

void demonstrateSubscriptAndFunctionCall() {
    cout << "4. SUBSCRIPT AND FUNCTION CALL OPERATORS" << endl;
    cout << "=========================================" << endl;
    
    // Matrix subscript operator demonstration
    cout << "Matrix subscript operator:" << endl;
    Matrix m1(3, 3);
    
    // Fill matrix using subscript operator
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            m1[i][j] = (i + 1) * 10 + (j + 1);
        }
    }
    
    cout << "Matrix m1:" << endl;
    m1.display();
    
    // Matrix function call operator demonstration
    cout << "\nMatrix function call operator:" << endl;
    Matrix m2(3, 3);
    
    // Fill matrix using function call operator
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            m2(i, j) = (i + j + 1) * 5;
        }
    }
    
    cout << "Matrix m2:" << endl;
    m2.display();
    
    // Matrix operations
    cout << "\nMatrix addition:" << endl;
    Matrix m3 = m1 + m2;
    cout << "m1 + m2:" << endl;
    m3.display();
    
    // Function call operator with functor
    cout << "\nPolynomial function call operator:" << endl;
    
    // Create polynomial: 2 + 3x - x^2 + 0.5x^3
    Polynomial poly({2.0, 3.0, -1.0, 0.5});
    poly.display();
    cout << endl;
    
    cout << "Evaluating polynomial at different points:" << endl;
    for (double x = -2.0; x <= 2.0; x += 0.5) {
        cout << "P(" << x << ") = " << poly(x) << endl;
    }
    
    cout << endl;
}

/*
 * ========================================================================
 * 5. ASSIGNMENT AND MEMBER ACCESS OPERATORS
 * ========================================================================
 */

// Smart pointer class demonstrating -> and * operators
template<typename T>
class SmartPtr {
private:
    T* ptr;
    size_t* ref_count;
    
    void cleanup() {
        if (ref_count && --(*ref_count) == 0) {
            delete ptr;
            delete ref_count;
        }
    }
    
public:
    // Constructor
    explicit SmartPtr(T* p = nullptr) : ptr(p), ref_count(p ? new size_t(1) : nullptr) {}
    
    // Copy constructor
    SmartPtr(const SmartPtr& other) : ptr(other.ptr), ref_count(other.ref_count) {
        if (ref_count) ++(*ref_count);
    }
    
    // Assignment operator
    SmartPtr& operator=(const SmartPtr& other) {
        if (this != &other) {
            cleanup();
            ptr = other.ptr;
            ref_count = other.ref_count;
            if (ref_count) ++(*ref_count);
        }
        return *this;
    }
    
    // Destructor
    ~SmartPtr() {
        cleanup();
    }
    
    // Dereference operator
    T& operator*() const {
        if (!ptr) throw runtime_error("Dereferencing null pointer");
        return *ptr;
    }
    
    // Arrow operator
    T* operator->() const {
        if (!ptr) throw runtime_error("Accessing null pointer");
        return ptr;
    }
    
    // Boolean conversion
    explicit operator bool() const {
        return ptr != nullptr;
    }
    
    // Get raw pointer
    T* get() const { return ptr; }
    
    // Get reference count
    size_t getRefCount() const { return ref_count ? *ref_count : 0; }
};

class Person {
private:
    string name;
    int age;
    
public:
    Person(const string& n, int a) : name(n), age(a) {}
    
    string getName() const { return name; }
    int getAge() const { return age; }
    
    void setName(const string& n) { name = n; }
    void setAge(int a) { age = a; }
    
    void display() const {
        cout << name << " (age " << age << ")";
    }
};

// Class demonstrating compound assignment operators
class Vector2D {
private:
    double x, y;
    
public:
    Vector2D(double x = 0, double y = 0) : x(x), y(y) {}
    
    // Getters
    double getX() const { return x; }
    double getY() const { return y; }
    
    // Assignment operator
    Vector2D& operator=(const Vector2D& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
        }
        return *this;
    }
    
    // Compound assignment operators
    Vector2D& operator+=(const Vector2D& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
    
    Vector2D& operator-=(const Vector2D& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }
    
    Vector2D& operator*=(double scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }
    
    Vector2D& operator/=(double scalar) {
        if (scalar == 0) throw runtime_error("Division by zero");
        x /= scalar;
        y /= scalar;
        return *this;
    }
    
    // Binary operators
    Vector2D operator+(const Vector2D& other) const {
        return Vector2D(x + other.x, y + other.y);
    }
    
    Vector2D operator-(const Vector2D& other) const {
        return Vector2D(x - other.x, y - other.y);
    }
    
    Vector2D operator*(double scalar) const {
        return Vector2D(x * scalar, y * scalar);
    }
    
    double magnitude() const {
        return sqrt(x * x + y * y);
    }
    
    void display() const {
        cout << "(" << x << ", " << y << ")";
    }
};

void demonstrateAssignmentAndAccess() {
    cout << "5. ASSIGNMENT AND MEMBER ACCESS OPERATORS" << endl;
    cout << "==========================================" << endl;
    
    // Smart pointer demonstration
    cout << "Smart pointer demonstration:" << endl;
    
    {
        SmartPtr<Person> sp1(new Person("Alice", 25));
        cout << "Created smart pointer sp1" << endl;
        cout << "Reference count: " << sp1.getRefCount() << endl;
        
        // Use arrow operator
        cout << "Using arrow operator: ";
        sp1->display();
        cout << endl;
        
        // Use dereference operator
        cout << "Using dereference operator: ";
        (*sp1).display();
        cout << endl;
        
        // Copy smart pointer
        SmartPtr<Person> sp2 = sp1;
        cout << "After copying to sp2" << endl;
        cout << "sp1 reference count: " << sp1.getRefCount() << endl;
        cout << "sp2 reference count: " << sp2.getRefCount() << endl;
        
        // Assignment operator
        SmartPtr<Person> sp3;
        sp3 = sp1;
        cout << "After assigning to sp3" << endl;
        cout << "Reference count: " << sp1.getRefCount() << endl;
        
        // Boolean conversion
        if (sp1) {
            cout << "sp1 is not null" << endl;
        }
        
        SmartPtr<Person> null_ptr;
        if (!null_ptr) {
            cout << "null_ptr is null" << endl;
        }
    }
    cout << "Smart pointers destroyed" << endl;
    
    // Compound assignment operators
    cout << "\nCompound assignment operators:" << endl;
    Vector2D v1(3, 4);
    Vector2D v2(1, 2);
    
    cout << "v1 = "; v1.display(); cout << endl;
    cout << "v2 = "; v2.display(); cout << endl;
    
    v1 += v2;
    cout << "After v1 += v2: "; v1.display(); cout << endl;
    
    v1 -= v2;
    cout << "After v1 -= v2: "; v1.display(); cout << endl;
    
    v1 *= 2.0;
    cout << "After v1 *= 2.0: "; v1.display(); cout << endl;
    
    v1 /= 2.0;
    cout << "After v1 /= 2.0: "; v1.display(); cout << endl;
    
    cout << "Magnitude of v1: " << v1.magnitude() << endl;
    
    cout << endl;
}

/*
 * ========================================================================
 * 6. CONVERSION OPERATORS
 * ========================================================================
 */

class Temperature {
private:
    double celsius;
    
public:
    Temperature(double c = 0.0) : celsius(c) {}
    
    // Implicit conversion to double (Celsius)
    operator double() const {
        return celsius;
    }
    
    // Explicit conversion to Fahrenheit
    explicit operator float() const {
        return static_cast<float>(celsius * 9.0 / 5.0 + 32.0);
    }
    
    // Named conversion functions
    double toCelsius() const { return celsius; }
    double toFahrenheit() const { return celsius * 9.0 / 5.0 + 32.0; }
    double toKelvin() const { return celsius + 273.15; }
    
    void display() const {
        cout << celsius << "°C";
    }
};

class SafeString {
private:
    string data;
    
public:
    SafeString(const string& s = "") : data(s) {}
    SafeString(const char* s) : data(s ? s : "") {}
    
    // Implicit conversion to string
    operator string() const {
        return data;
    }
    
    // Explicit conversion to const char*
    explicit operator const char*() const {
        return data.c_str();
    }
    
    // Bool conversion for checking if string is empty
    explicit operator bool() const {
        return !data.empty();
    }
    
    size_t length() const { return data.length(); }
    
    void display() const {
        cout << "\"" << data << "\"";
    }
};

void demonstrateConversionOperators() {
    cout << "6. CONVERSION OPERATORS" << endl;
    cout << "=======================" << endl;
    
    // Temperature conversion demonstration
    cout << "Temperature conversions:" << endl;
    Temperature temp(25.0);  // 25°C
    
    cout << "Temperature: "; temp.display(); cout << endl;
    
    // Implicit conversion to double
    double celsius_value = temp;
    cout << "Implicit conversion to double: " << celsius_value << endl;
    
    // Explicit conversion to float (Fahrenheit)
    float fahrenheit_value = static_cast<float>(temp);
    cout << "Explicit conversion to Fahrenheit: " << fahrenheit_value << "°F" << endl;
    
    // Named conversion functions
    cout << "Named conversions:" << endl;
    cout << "  Celsius: " << temp.toCelsius() << "°C" << endl;
    cout << "  Fahrenheit: " << temp.toFahrenheit() << "°F" << endl;
    cout << "  Kelvin: " << temp.toKelvin() << "K" << endl;
    
    // Function that accepts double
    auto printTemperature = [](double t) {
        cout << "Temperature value: " << t << endl;
    };
    
    cout << "Passing Temperature to function expecting double:" << endl;
    printTemperature(temp);  // Implicit conversion
    
    // SafeString conversion demonstration
    cout << "\nSafeString conversions:" << endl;
    SafeString safe_str("Hello, World!");
    
    cout << "SafeString: "; safe_str.display(); cout << endl;
    
    // Implicit conversion to string
    string std_string = safe_str;
    cout << "Implicit conversion to string: " << std_string << endl;
    
    // Explicit conversion to const char*
    const char* c_string = static_cast<const char*>(safe_str);
    cout << "Explicit conversion to const char*: " << c_string << endl;
    
    // Bool conversion
    SafeString empty_str("");
    cout << "Non-empty SafeString is true: " << boolalpha << static_cast<bool>(safe_str) << endl;
    cout << "Empty SafeString is false: " << boolalpha << static_cast<bool>(empty_str) << endl;
    
    // Using in conditional
    if (safe_str) {
        cout << "SafeString contains data" << endl;
    }
    
    if (!empty_str) {
        cout << "Empty SafeString detected" << endl;
    }
    
    cout << endl;
}

/*
 * ========================================================================
 * 7. ADVANCED OPERATOR OVERLOADING PATTERNS
 * ========================================================================
 */

// CRTP (Curiously Recurring Template Pattern) for operator consistency
template<typename Derived>
class Comparable {
public:
    friend bool operator!=(const Derived& lhs, const Derived& rhs) {
        return !(lhs == rhs);
    }
    
    friend bool operator>(const Derived& lhs, const Derived& rhs) {
        return rhs < lhs;
    }
    
    friend bool operator<=(const Derived& lhs, const Derived& rhs) {
        return !(lhs > rhs);
    }
    
    friend bool operator>=(const Derived& lhs, const Derived& rhs) {
        return !(lhs < rhs);
    }
};

class Score : public Comparable<Score> {
private:
    int value;
    
public:
    Score(int v = 0) : value(v) {}
    
    int getValue() const { return value; }
    
    // Only need to implement == and < operators
    bool operator==(const Score& other) const {
        return value == other.value;
    }
    
    bool operator<(const Score& other) const {
        return value < other.value;
    }
    
    void display() const {
        cout << value;
    }
};

// Chain assignment operator
class ChainableInt {
private:
    int value;
    
public:
    ChainableInt(int v = 0) : value(v) {}
    
    // Chain assignment operator
    ChainableInt& operator=(int v) {
        value = v;
        return *this;
    }
    
    ChainableInt& operator=(const ChainableInt& other) {
        if (this != &other) {
            value = other.value;
        }
        return *this;
    }
    
    // Compound assignment with chaining
    ChainableInt& operator+=(int v) {
        value += v;
        return *this;
    }
    
    ChainableInt& operator*=(int v) {
        value *= v;
        return *this;
    }
    
    int getValue() const { return value; }
    
    void display() const {
        cout << value;
    }
};

void demonstrateAdvancedPatterns() {
    cout << "7. ADVANCED OPERATOR OVERLOADING PATTERNS" << endl;
    cout << "==========================================" << endl;
    
    // CRTP pattern demonstration
    cout << "CRTP Comparable pattern:" << endl;
    Score s1(85);
    Score s2(92);
    Score s3(85);
    
    cout << "s1 = "; s1.display(); cout << endl;
    cout << "s2 = "; s2.display(); cout << endl;
    cout << "s3 = "; s3.display(); cout << endl;
    
    cout << "\nComparison results:" << endl;
    cout << "s1 == s3: " << boolalpha << (s1 == s3) << endl;
    cout << "s1 != s2: " << boolalpha << (s1 != s2) << endl;
    cout << "s1 < s2: " << boolalpha << (s1 < s2) << endl;
    cout << "s1 > s2: " << boolalpha << (s1 > s2) << endl;
    cout << "s1 <= s3: " << boolalpha << (s1 <= s3) << endl;
    cout << "s2 >= s1: " << boolalpha << (s2 >= s1) << endl;
    
    // Chain assignment demonstration
    cout << "\nChain assignment pattern:" << endl;
    ChainableInt a, b, c;
    
    cout << "Before chaining:" << endl;
    cout << "a = "; a.display(); cout << ", b = "; b.display(); cout << ", c = "; c.display(); cout << endl;
    
    // Chain assignment
    a = b = c = 42;
    cout << "After a = b = c = 42:" << endl;
    cout << "a = "; a.display(); cout << ", b = "; b.display(); cout << ", c = "; c.display(); cout << endl;
    
    // Chain compound assignment
    (a += 10) *= 2;
    cout << "After (a += 10) *= 2:" << endl;
    cout << "a = "; a.display(); cout << endl;
    
    cout << endl;
}

/*
 * ========================================================================
 * MAIN FUNCTION
 * ========================================================================
 */

int main() {
    cout << "=== OPERATOR OVERLOADING COMPREHENSIVE GUIDE ===" << endl << endl;
    
    demonstrateArithmeticOperators();
    demonstrateComparisonOperators();
    demonstrateStreamOperators();
    demonstrateSubscriptAndFunctionCall();
    demonstrateAssignmentAndAccess();
    demonstrateConversionOperators();
    demonstrateAdvancedPatterns();
    
    cout << "=== Operator Overloading Mastery Complete! ===" << endl;
    
    return 0;
}

/*
 * ============================================================================
 * PRACTICE EXERCISES:
 * ============================================================================
 * 
 * 1. Create a Rational number class with all arithmetic and comparison operators.
 * 
 * 2. Implement a BigInteger class that can handle arbitrarily large numbers.
 * 
 * 3. Create a Vector3D class with dot product, cross product, and all operators.
 * 
 * 4. Implement a custom string class with all necessary operators.
 * 
 * 5. Create a DateTime class with comparison and arithmetic operators.
 * 
 * 6. Implement a Set class with union (|), intersection (&), and difference (-).
 * 
 * 7. Create a Polynomial class with addition, subtraction, and multiplication.
 * 
 * 8. Implement a Currency class with proper arithmetic and conversion operators.
 * 
 * 9. Create a bitset-like class with bitwise operators.
 * 
 * 10. Implement a smart pointer class with all necessary operators.
 * 
 * ============================================================================
 * OPERATOR OVERLOADING BEST PRACTICES:
 * ============================================================================
 * 
 * 1. SEMANTIC CONSISTENCY:
 *    - Make overloaded operators behave like built-in types
 *    - Maintain mathematical relationships (a + b - b == a)
 *    - Don't surprise users with unexpected behavior
 * 
 * 2. MEMBER VS NON-MEMBER:
 *    - Unary operators: Usually member functions
 *    - Binary operators with left operand conversion: Non-member
 *    - Assignment operators: Must be member functions
 *    - Comparison operators: Often non-member for symmetry
 * 
 * 3. RETURN TYPES:
 *    - Assignment operators: Return reference to *this
 *    - Arithmetic operators: Return by value
 *    - Comparison operators: Return bool
 *    - Stream operators: Return reference to stream
 * 
 * 4. CONST CORRECTNESS:
 *    - Mark operators const when they don't modify the object
 *    - Use const parameters when operands shouldn't be modified
 * 
 * 5. EXCEPTION SAFETY:
 *    - Provide strong exception safety guarantee when possible
 *    - Mark operators noexcept when appropriate
 * 
 * ============================================================================
 * IMPLEMENTATION GUIDELINES:
 * ============================================================================
 * 
 * 1. ARITHMETIC OPERATORS:
 *    - Implement compound assignment first (+=, -=, etc.)
 *    - Implement binary operators in terms of compound assignment
 *    - Example: a + b implemented as { a tmp = a; return tmp += b; }
 * 
 * 2. COMPARISON OPERATORS:
 *    - In C++20, implement <=> (spaceship operator) if possible
 *    - Pre-C++20: Implement == and <, derive others
 *    - Use CRTP pattern for automatic derivation
 * 
 * 3. STREAM OPERATORS:
 *    - Implement as friend functions for access to private members
 *    - Return stream reference for chaining
 *    - Handle error conditions appropriately
 * 
 * 4. CONVERSION OPERATORS:
 *    - Use explicit for conversions that might lose information
 *    - Provide named conversion functions as alternatives
 *    - Be careful with implicit conversions
 * 
 * ============================================================================
 * COMMON PITFALLS TO AVOID:
 * ============================================================================
 * 
 * 1. DON'T OVERLOAD:
 *    - Operators for unrelated classes
 *    - Operators with non-intuitive meanings
 *    - Address-of operator (&) unless absolutely necessary
 *    - Comma operator (,) unless creating DSL
 * 
 * 2. AVOID SURPRISING BEHAVIOR:
 *    - Don't make + operator perform multiplication
 *    - Don't make comparison operators have side effects
 *    - Don't violate mathematical properties
 * 
 * 3. CONSISTENCY ISSUES:
 *    - If you overload ==, also overload !=
 *    - If you overload <, consider overloading >, <=, >=
 *    - If you overload +, consider overloading +=
 * 
 * 4. PERFORMANCE CONSIDERATIONS:
 *    - Return by const value to prevent modification of temporaries
 *    - Use references for parameters when copying is expensive
 *    - Consider move semantics for expensive operations
 * 
 * ============================================================================
 */
