
#include "searchable_array_bag.hpp"
#include "searchable_tree_bag.hpp"
#include "set.hpp"
#include <iostream>

void check(bool condition, const char *name, int &tests, int &failed)
{
    tests++;

    if (condition)
        std::cout << "[PASS] " << name << std::endl;
    else
    {
        std::cout << "[FAIL] " << name << std::endl;
        failed++;
    }
}

int main()
{
    int tests = 0;
    int failed = 0;

    std::cout << "========== POLYSET TEST ==========\n" << std::endl;

    // ==================================================
    // 1. ARRAY BAG
    // ==================================================

    std::cout << "--- Array Bag ---" << std::endl;

    searchable_array_bag arrayBag;

    arrayBag.insert(10);
    arrayBag.insert(20);
    arrayBag.insert(10);

    check(arrayBag.has(10), "array: find existing value",
          tests, failed);

    check(arrayBag.has(20), "array: find second value",
          tests, failed);

    check(!arrayBag.has(99), "array: reject missing value",
          tests, failed);

    std::cout << "Contents: ";
    arrayBag.print();


    // ==================================================
    // 2. TREE BAG
    // ==================================================

    std::cout << "\n--- Tree Bag ---" << std::endl;

    searchable_tree_bag treeBag;

    treeBag.insert(50);
    treeBag.insert(20);
    treeBag.insert(70);
    treeBag.insert(10);
    treeBag.insert(30);
    treeBag.insert(60);
    treeBag.insert(80);

    check(treeBag.has(50), "tree: find root",
          tests, failed);

    check(treeBag.has(10), "tree: find left leaf",
          tests, failed);

    check(treeBag.has(80), "tree: find right leaf",
          tests, failed);

    check(!treeBag.has(999), "tree: reject missing value",
          tests, failed);

    std::cout << "Contents: ";
    treeBag.print();


    // ==================================================
    // 3. SET DUPLICATES
    // ==================================================

    std::cout << "\n--- Set ---" << std::endl;

    searchable_array_bag storage;
    set s(storage);

    s.insert(5);
    s.insert(10);
    s.insert(5);
    s.insert(10);
    s.insert(15);

    check(s.has(5), "set: contains 5",
          tests, failed);

    check(s.has(10), "set: contains 10",
          tests, failed);

    check(s.has(15), "set: contains 15",
          tests, failed);

    check(!s.has(100), "set: reject missing value",
          tests, failed);

    std::cout << "Set contents: ";
    s.print();

    /*
        Expected:

        5 10 15

        The duplicates must not be inserted.
    */


    // ==================================================
    // 4. INSERT ARRAY
    // ==================================================

    std::cout << "\n--- Insert Array ---" << std::endl;

    searchable_array_bag bag;

    int values[] = {1, 2, 3, 4, 5};

    bag.insert(values, 5);

    check(bag.has(1) &&
          bag.has(2) &&
          bag.has(3) &&
          bag.has(4) &&
          bag.has(5),
          "array: insert array",
          tests, failed);

    std::cout << "Contents: ";
    bag.print();


    // ==================================================
    // 5. SET INSERT ARRAY
    // ==================================================

    std::cout << "\n--- Set Insert Array ---" << std::endl;

    searchable_array_bag storage2;
    set s2(storage2);

    int numbers[] = {1, 1, 2, 2, 3, 3, 3};

    s2.insert(numbers, 7);

    check(s2.has(1) &&
          s2.has(2) &&
          s2.has(3),
          "set: insert array",
          tests, failed);

    std::cout << "Set contents: ";
    s2.print();


    // ==================================================
    // 6. CLEAR
    // ==================================================

    std::cout << "\n--- Clear ---" << std::endl;

    s2.clear();

    check(!s2.has(1) &&
          !s2.has(2) &&
          !s2.has(3),
          "set: clear removes values",
          tests, failed);

    std::cout << "After clear: ";
    s2.print();


    // ==================================================
    // 7. COPY CONSTRUCTOR
    // ==================================================

    std::cout << "\n--- Copy Constructor ---" << std::endl;

    searchable_array_bag original;

    original.insert(100);
    original.insert(200);

    searchable_array_bag copy(original);

    check(copy.has(100) &&
          copy.has(200),
          "array: copy constructor",
          tests, failed);


    // ==================================================
    // 8. ASSIGNMENT OPERATOR
    // ==================================================

    std::cout << "\n--- Assignment ---" << std::endl;

    searchable_array_bag assigned;

    assigned.insert(999);
    assigned = original;

    check(assigned.has(100) &&
          assigned.has(200) &&
          !assigned.has(999),
          "array: assignment operator",
          tests, failed);


    // ==================================================
    // 9. POLYMORPHISM
    // ==================================================

    std::cout << "\n--- Polymorphism ---" << std::endl;

    searchable_array_bag polymorphicArray;
    searchable_tree_bag polymorphicTree;

    searchable_bag *p1 = &polymorphicArray;
    searchable_bag *p2 = &polymorphicTree;

    p1->insert(42);
    p2->insert(42);

    check(p1->has(42), "polymorphism: array through base",
          tests, failed);

    check(p2->has(42), "polymorphism: tree through base",
          tests, failed);


    // ==================================================
    // FINAL RESULT
    // ==================================================

    std::cout << "\n=================================" << std::endl;
    std::cout << "Tests : " << tests << std::endl;
    std::cout << "Passed: " << tests - failed << std::endl;
    std::cout << "Failed: " << failed << std::endl;
    std::cout << "=================================" << std::endl;

    if (failed == 0)
        std::cout << "ALL TESTS PASSED!" << std::endl;
    else
        std::cout << "SOME TESTS FAILED!" << std::endl;

    return failed;
}
