/*
 * ============================================================================
 * INHERITANCE AND POLYMORPHISM IN C++
 * ============================================================================
 * 
 * THEORY:
 * Inheritance is a fundamental OOP concept that allows a class (derived class)
 * to inherit properties and methods from another class (base class). This
 * promotes code reusability and establishes an "is-a" relationship.
 * 
 * Polymorphism means "many forms" and allows objects of different types to be
 * treated as objects of a common base type. It enables a single interface to
 * represent different underlying forms (data types).
 * 
 * TYPES OF INHERITANCE:
 * 1. Single Inheritance - One base class, one derived class
 * 2. Multiple Inheritance - Multiple base classes, one derived class
 * 3. Multilevel Inheritance - Chain of inheritance
 * 4. Hierarchical Inheritance - One base class, multiple derived classes
 * 5. Hybrid Inheritance - Combination of above types
 * 
 * TYPES OF POLYMORPHISM:
 * 1. Compile-time (Static) - Function overloading, operator overloading
 * 2. Runtime (Dynamic) - Virtual functions, function overriding
 * 
 * ACCESS CONTROL IN INHERITANCE:
 * - public inheritance: public -> public, protected -> protected
 * - protected inheritance: public -> protected, protected -> protected  
 * - private inheritance: public -> private, protected -> private
 * ============================================================================
 */

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <iomanip>

using namespace std;

/*
 * ========================================================================
 * 1. BASIC INHERITANCE - SINGLE INHERITANCE
 * ========================================================================
 */

// Base class (Parent class)
class Animal {
protected:  // Protected members can be accessed by derived classes
    string name;
    int age;
    string species;
    
public:
    // Constructor
    Animal(string n = "Unknown", int a = 0, string s = "Unknown") 
        : name(n), age(a), species(s) {
        cout << "Animal constructor called for: " << name << endl;
    }
    
    // Virtual destructor (important for polymorphism)
    virtual ~Animal() {
        cout << "Animal destructor called for: " << name << endl;
    }
    
    // Virtual functions (can be overridden in derived classes)
    virtual void makeSound() const {
        cout << name << " makes a generic animal sound." << endl;
    }
    
    virtual void move() const {
        cout << name << " moves in some way." << endl;
    }
    
    virtual void displayInfo() const {
        cout << "\n=== Animal Information ===" << endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << " years" << endl;
        cout << "Species: " << species << endl;
        cout << "=========================" << endl;
    }
    
    // Non-virtual methods
    void eat(const string& food) const {
        cout << name << " is eating " << food << "." << endl;
    }
    
    void sleep() const {
        cout << name << " is sleeping." << endl;
    }
    
    // Getters
    string getName() const { return name; }
    int getAge() const { return age; }
    string getSpecies() const { return species; }
    
    // Setters
    void setName(const string& n) { name = n; }
    void setAge(int a) { if (a >= 0) age = a; }
};

// Derived class (Child class)
class Dog : public Animal {
private:
    string breed;
    bool isTrained;
    
public:
    // Constructor - calls base class constructor
    Dog(string n = "Unknown Dog", int a = 0, string b = "Mixed") 
        : Animal(n, a, "Canine"), breed(b), isTrained(false) {
        cout << "Dog constructor called for: " << name << endl;
    }
    
    // Destructor
    ~Dog() {
        cout << "Dog destructor called for: " << name << endl;
    }
    
    // Override virtual functions from base class
    void makeSound() const override {
        cout << name << " barks: Woof! Woof!" << endl;
    }
    
    void move() const override {
        cout << name << " runs on four legs." << endl;
    }
    
    void displayInfo() const override {
        cout << "\n=== Dog Information ===" << endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << " years" << endl;
        cout << "Species: " << species << endl;
        cout << "Breed: " << breed << endl;
        cout << "Trained: " << (isTrained ? "Yes" : "No") << endl;
        cout << "======================" << endl;
    }
    
    // Dog-specific methods
    void fetch() const {
        cout << name << " fetches the ball!" << endl;
    }
    
    void train() {
        isTrained = true;
        cout << name << " has been trained!" << endl;
    }
    
    void wagTail() const {
        cout << name << " wags tail happily!" << endl;
    }
    
    // Getters
    string getBreed() const { return breed; }
    bool getIsTrained() const { return isTrained; }
};

class Cat : public Animal {
private:
    bool isIndoor;
    int livesLeft;
    
public:
    // Constructor
    Cat(string n = "Unknown Cat", int a = 0, bool indoor = true) 
        : Animal(n, a, "Feline"), isIndoor(indoor), livesLeft(9) {
        cout << "Cat constructor called for: " << name << endl;
    }
    
    // Destructor
    ~Cat() {
        cout << "Cat destructor called for: " << name << endl;
    }
    
    // Override virtual functions
    void makeSound() const override {
        cout << name << " meows: Meow! Meow!" << endl;
    }
    
    void move() const override {
        cout << name << " gracefully walks on silent paws." << endl;
    }
    
    void displayInfo() const override {
        cout << "\n=== Cat Information ===" << endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << " years" << endl;
        cout << "Species: " << species << endl;
        cout << "Indoor: " << (isIndoor ? "Yes" : "No") << endl;
        cout << "Lives left: " << livesLeft << endl;
        cout << "======================" << endl;
    }
    
    // Cat-specific methods
    void purr() const {
        cout << name << " purrs contentedly." << endl;
    }
    
    void climb() const {
        cout << name << " climbs up high!" << endl;
    }
    
    void useLitter() const {
        if (isIndoor) {
            cout << name << " uses the litter box." << endl;
        } else {
            cout << name << " goes outside." << endl;
        }
    }
    
    // Getters
    bool getIsIndoor() const { return isIndoor; }
    int getLivesLeft() const { return livesLeft; }
};

/*
 * ========================================================================
 * 2. MULTILEVEL INHERITANCE
 * ========================================================================
 */

// Base class
class Vehicle {
protected:
    string brand;
    int year;
    double price;
    
public:
    Vehicle(string b, int y, double p) : brand(b), year(y), price(p) {
        cout << "Vehicle constructor: " << brand << endl;
    }
    
    virtual ~Vehicle() {
        cout << "Vehicle destructor: " << brand << endl;
    }
    
    virtual void start() const {
        cout << brand << " vehicle starting..." << endl;
    }
    
    virtual void stop() const {
        cout << brand << " vehicle stopping..." << endl;
    }
    
    virtual void displayInfo() const {
        cout << "Brand: " << brand << ", Year: " << year << ", Price: $" << price << endl;
    }
    
    string getBrand() const { return brand; }
    int getYear() const { return year; }
    double getPrice() const { return price; }
};

// Intermediate derived class
class Car : public Vehicle {
protected:
    int doors;
    string fuelType;
    
public:
    Car(string b, int y, double p, int d, string fuel) 
        : Vehicle(b, y, p), doors(d), fuelType(fuel) {
        cout << "Car constructor: " << brand << endl;
    }
    
    virtual ~Car() {
        cout << "Car destructor: " << brand << endl;
    }
    
    void start() const override {
        cout << brand << " car engine starting..." << endl;
    }
    
    void stop() const override {
        cout << brand << " car engine stopping..." << endl;
    }
    
    virtual void drive() const {
        cout << "Driving the " << brand << " car." << endl;
    }
    
    void displayInfo() const override {
        cout << "Car - Brand: " << brand << ", Year: " << year 
             << ", Doors: " << doors << ", Fuel: " << fuelType << endl;
    }
    
    int getDoors() const { return doors; }
    string getFuelType() const { return fuelType; }
};

// Further derived class
class SportsCar : public Car {
private:
    int maxSpeed;
    bool hasTurbo;
    
public:
    SportsCar(string b, int y, double p, int d, string fuel, int speed, bool turbo)
        : Car(b, y, p, d, fuel), maxSpeed(speed), hasTurbo(turbo) {
        cout << "SportsCar constructor: " << brand << endl;
    }
    
    ~SportsCar() {
        cout << "SportsCar destructor: " << brand << endl;
    }
    
    void start() const override {
        cout << brand << " sports car engine roaring to life!" << endl;
    }
    
    void drive() const override {
        cout << "Racing the " << brand << " sports car at high speed!" << endl;
    }
    
    void activateTurbo() const {
        if (hasTurbo) {
            cout << brand << " turbo activated! Maximum power!" << endl;
        } else {
            cout << brand << " doesn't have turbo." << endl;
        }
    }
    
    void displayInfo() const override {
        cout << "Sports Car - Brand: " << brand << ", Year: " << year 
             << ", Max Speed: " << maxSpeed << " mph, Turbo: " 
             << (hasTurbo ? "Yes" : "No") << endl;
    }
    
    int getMaxSpeed() const { return maxSpeed; }
    bool getHasTurbo() const { return hasTurbo; }
};

/*
 * ========================================================================
 * 3. MULTIPLE INHERITANCE
 * ========================================================================
 */

class Flyable {
public:
    virtual ~Flyable() = default;
    
    virtual void fly() const {
        cout << "Flying through the air!" << endl;
    }
    
    virtual int getMaxAltitude() const = 0;  // Pure virtual function
};

class Swimmable {
public:
    virtual ~Swimmable() = default;
    
    virtual void swim() const {
        cout << "Swimming through water!" << endl;
    }
    
    virtual int getMaxDepth() const = 0;  // Pure virtual function
};

// Multiple inheritance from Animal, Flyable, and Swimmable
class Duck : public Animal, public Flyable, public Swimmable {
private:
    int maxAltitude;
    int maxDepth;
    
public:
    Duck(string n, int a, int altitude = 1000, int depth = 10) 
        : Animal(n, a, "Waterfowl"), maxAltitude(altitude), maxDepth(depth) {
        cout << "Duck constructor: " << name << endl;
    }
    
    ~Duck() {
        cout << "Duck destructor: " << name << endl;
    }
    
    // Override Animal methods
    void makeSound() const override {
        cout << name << " quacks: Quack! Quack!" << endl;
    }
    
    void move() const override {
        cout << name << " waddles on land." << endl;
    }
    
    // Override Flyable methods
    void fly() const override {
        cout << name << " flies gracefully across the sky!" << endl;
    }
    
    int getMaxAltitude() const override {
        return maxAltitude;
    }
    
    // Override Swimmable methods
    void swim() const override {
        cout << name << " swims elegantly in the water!" << endl;
    }
    
    int getMaxDepth() const override {
        return maxDepth;
    }
    
    // Duck-specific method
    void showVersatility() const {
        cout << name << " demonstrates versatility:" << endl;
        move();     // Walk
        swim();     // Swim
        fly();      // Fly
        makeSound(); // Quack
    }
};

/*
 * ========================================================================
 * 4. ABSTRACT CLASSES AND PURE VIRTUAL FUNCTIONS
 * ========================================================================
 */

// Abstract base class
class Shape {
protected:
    string color;
    
public:
    Shape(string c) : color(c) {
        cout << "Shape constructor: " << color << " shape" << endl;
    }
    
    virtual ~Shape() {
        cout << "Shape destructor: " << color << " shape" << endl;
    }
    
    // Pure virtual functions make this an abstract class
    virtual double calculateArea() const = 0;
    virtual double calculatePerimeter() const = 0;
    virtual void draw() const = 0;
    
    // Regular virtual function
    virtual void displayInfo() const {
        cout << "Shape: " << color << endl;
        cout << "Area: " << calculateArea() << endl;
        cout << "Perimeter: " << calculatePerimeter() << endl;
    }
    
    string getColor() const { return color; }
    void setColor(const string& c) { color = c; }
};

class Rectangle : public Shape {
private:
    double length;
    double width;
    
public:
    Rectangle(double l, double w, string c = "white") 
        : Shape(c), length(l), width(w) {
        cout << "Rectangle constructor: " << length << "x" << width << endl;
    }
    
    ~Rectangle() {
        cout << "Rectangle destructor" << endl;
    }
    
    double calculateArea() const override {
        return length * width;
    }
    
    double calculatePerimeter() const override {
        return 2 * (length + width);
    }
    
    void draw() const override {
        cout << "Drawing a " << color << " rectangle (" 
             << length << "x" << width << ")" << endl;
    }
    
    double getLength() const { return length; }
    double getWidth() const { return width; }
};

class Circle : public Shape {
private:
    double radius;
    
public:
    Circle(double r, string c = "white") : Shape(c), radius(r) {
        cout << "Circle constructor: radius " << radius << endl;
    }
    
    ~Circle() {
        cout << "Circle destructor" << endl;
    }
    
    double calculateArea() const override {
        return 3.14159 * radius * radius;
    }
    
    double calculatePerimeter() const override {
        return 2 * 3.14159 * radius;
    }
    
    void draw() const override {
        cout << "Drawing a " << color << " circle (radius " 
             << radius << ")" << endl;
    }
    
    double getRadius() const { return radius; }
};

/*
 * ========================================================================
 * 5. MAIN FUNCTION - DEMONSTRATION
 * ========================================================================
 */

int main() {
    cout << "=== INHERITANCE AND POLYMORPHISM IN C++ ===" << endl << endl;
    
    /*
     * ====================================================================
     * 1. BASIC INHERITANCE DEMONSTRATION
     * ====================================================================
     */
    
    cout << "1. BASIC INHERITANCE" << endl;
    cout << "====================" << endl;
    
    // Create objects
    Animal genericAnimal("Generic", 5, "Unknown");
    Dog myDog("Buddy", 3, "Golden Retriever");
    Cat myCat("Whiskers", 2, true);
    
    // Demonstrate inherited methods
    cout << "\nDemonstrating inherited methods:" << endl;
    myDog.eat("dog food");
    myCat.sleep();
    
    // Demonstrate overridden methods
    cout << "\nDemonstrating method overriding:" << endl;
    genericAnimal.makeSound();
    myDog.makeSound();
    myCat.makeSound();
    
    // Demonstrate polymorphism with base class pointers
    cout << "\nPolymorphism with base class pointers:" << endl;
    Animal* animals[] = {&genericAnimal, &myDog, &myCat};
    
    for (int i = 0; i < 3; i++) {
        animals[i]->makeSound();
        animals[i]->move();
        animals[i]->displayInfo();
    }
    
    /*
     * ====================================================================
     * 2. MULTILEVEL INHERITANCE
     * ====================================================================
     */
    
    cout << "\n2. MULTILEVEL INHERITANCE" << endl;
    cout << "=========================" << endl;
    
    SportsCar ferrari("Ferrari", 2023, 250000, 2, "Gasoline", 210, true);
    
    ferrari.start();
    ferrari.drive();
    ferrari.activateTurbo();
    ferrari.stop();
    ferrari.displayInfo();
    
    // Polymorphism through inheritance chain
    Vehicle* vehiclePtr = &ferrari;
    Car* carPtr = &ferrari;
    
    cout << "\nPolymorphism through inheritance chain:" << endl;
    vehiclePtr->start();
    carPtr->drive();
    
    /*
     * ====================================================================
     * 3. MULTIPLE INHERITANCE
     * ====================================================================
     */
    
    cout << "\n3. MULTIPLE INHERITANCE" << endl;
    cout << "=======================" << endl;
    
    Duck donald("Donald", 4, 2000, 15);
    
    // Access methods from all base classes
    donald.makeSound();      // From Animal
    donald.fly();           // From Flyable
    donald.swim();          // From Swimmable
    donald.showVersatility(); // Duck's own method
    
    cout << "Max altitude: " << donald.getMaxAltitude() << " feet" << endl;
    cout << "Max depth: " << donald.getMaxDepth() << " feet" << endl;
    
    /*
     * ====================================================================
     * 4. ABSTRACT CLASSES AND PURE VIRTUAL FUNCTIONS
     * ====================================================================
     */
    
    cout << "\n4. ABSTRACT CLASSES" << endl;
    cout << "===================" << endl;
    
    // Shape shape("red");  // Error! Cannot instantiate abstract class
    
    Rectangle rect(5.0, 3.0, "blue");
    Circle circle(4.0, "red");
    
    rect.draw();
    rect.displayInfo();
    
    circle.draw();
    circle.displayInfo();
    
    // Polymorphism with abstract base class
    cout << "\nPolymorphism with abstract base class:" << endl;
    vector<unique_ptr<Shape>> shapes;
    shapes.push_back(make_unique<Rectangle>(10.0, 6.0, "green"));
    shapes.push_back(make_unique<Circle>(5.0, "yellow"));
    shapes.push_back(make_unique<Rectangle>(8.0, 8.0, "purple"));
    
    for (const auto& shape : shapes) {
        shape->draw();
        cout << "Area: " << shape->calculateArea() << endl;
        cout << "Perimeter: " << shape->calculatePerimeter() << endl;
        cout << "---" << endl;
    }
    
    /*
     * ====================================================================
     * 5. ADVANCED POLYMORPHISM EXAMPLES
     * ====================================================================
     */
    
    cout << "\n5. ADVANCED POLYMORPHISM" << endl;
    cout << "========================" << endl;
    
    // Function that works with any Animal
    auto makeAnimalPerform = [](Animal& animal) {
        cout << "\nPerformance by " << animal.getName() << ":" << endl;
        animal.makeSound();
        animal.move();
        animal.eat("treats");
    };
    
    makeAnimalPerform(myDog);
    makeAnimalPerform(myCat);
    makeAnimalPerform(donald);
    
    // Dynamic casting
    cout << "\nDynamic casting examples:" << endl;
    Animal* animalPtr = &myDog;
    
    Dog* dogPtr = dynamic_cast<Dog*>(animalPtr);
    if (dogPtr) {
        cout << "Successfully cast to Dog*" << endl;
        dogPtr->fetch();
        dogPtr->wagTail();
    }
    
    Cat* catPtr = dynamic_cast<Cat*>(animalPtr);
    if (!catPtr) {
        cout << "Cannot cast Dog to Cat (as expected)" << endl;
    }
    
    // Using typeid for runtime type information
    cout << "\nRuntime type information:" << endl;
    cout << "Type of myDog: " << typeid(myDog).name() << endl;
    cout << "Type of myCat: " << typeid(myCat).name() << endl;
    cout << "Type through pointer: " << typeid(*animalPtr).name() << endl;
    
    cout << "\n=== Inheritance and Polymorphism Complete! ===" << endl;
    
    return 0;
}

/*
 * ============================================================================
 * PRACTICE EXERCISES:
 * ============================================================================
 * 
 * 1. Create a hierarchy: Employee -> Manager -> ExecutiveManager
 *    Include salary calculation with different bonus structures.
 * 
 * 2. Design a media player system: Media -> Audio -> MP3, Video -> MP4
 *    Include play, pause, stop functionality.
 * 
 * 3. Implement a banking system: Account -> SavingsAccount, CheckingAccount
 *    Include interest calculation and transaction limits.
 * 
 * 4. Create a game character system: Character -> Warrior, Mage, Archer
 *    Include different attack patterns and special abilities.
 * 
 * 5. Design a document system: Document -> TextDocument, ImageDocument
 *    Include open, save, print functionality.
 * 
 * 6. Implement multiple inheritance: Person, Employee -> Teacher
 *    Handle potential diamond problem scenarios.
 * 
 * 7. Create an interface hierarchy: Drawable, Resizable -> Image
 *    Use pure virtual functions for interfaces.
 * 
 * 8. Design a transportation system with multiple inheritance:
 *    Vehicle, Electric -> ElectricCar
 * 
 * ============================================================================
 * INHERITANCE BEST PRACTICES:
 * ============================================================================
 * 
 * 1. Use public inheritance for "is-a" relationships
 * 2. Make destructors virtual in base classes
 * 3. Use protected for members accessed by derived classes
 * 4. Prefer composition over inheritance when appropriate
 * 5. Use abstract classes to define interfaces
 * 6. Be careful with multiple inheritance (diamond problem)
 * 7. Use override keyword for clarity (C++11)
 * 8. Implement proper copy semantics in inheritance hierarchies
 * 9. Use dynamic_cast for safe downcasting
 * 10. Follow the Liskov Substitution Principle
 * 
 * ============================================================================
 * POLYMORPHISM GUIDELINES:
 * ============================================================================
 * 
 * 1. Use virtual functions for runtime polymorphism
 * 2. Make base class destructors virtual
 * 3. Use pure virtual functions for abstract interfaces
 * 4. Prefer smart pointers for polymorphic objects
 * 5. Use function overloading for compile-time polymorphism
 * 6. Be aware of virtual function call overhead
 * 7. Use final keyword to prevent further inheritance (C++11)
 * 8. Understand virtual function table (vtable) mechanics
 * 9. Use typeid and dynamic_cast judiciously
 * 10. Design for polymorphic usage from the beginning
 * 
 * ============================================================================
 */
