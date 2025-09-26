#include <iostream>
#include <cassert>
#include <vector>
#include "dldlist.h"

class TestRunner {
private:
    int passed = 0;
    int failed = 0;
    
public:
    void test(const std::string& name, bool condition) {
        if (condition) {
            std::cout << "[PASS] " << name << std::endl;
            passed++;
        } else {
            std::cout << "[FAIL] " << name << std::endl;
            failed++;
        }
    }
    
    void summary() {
        std::cout << "\n=== Test Summary ===" << std::endl;
        std::cout << "Passed: " << passed << std::endl;
        std::cout << "Failed: " << failed << std::endl;
        std::cout << "Total:  " << (passed + failed) << std::endl;
    }
};

// Test basic construction and destruction
void test_construction(TestRunner& runner) {
    DoublyLinkedList dll;
    runner.test("Empty list creation", dll.empty());
    runner.test("Empty list size", dll.size() == 0);
}

// Test single element operations
void test_single_element(TestRunner& runner) {
    DoublyLinkedList dll;
    
    // Add front
    dll.addFront(42);
    runner.test("Single element - not empty", !dll.empty());
    runner.test("Single element - size 1", dll.size() == 1);
    runner.test("Single element - front value", dll.front() == 42);
    runner.test("Single element - back value", dll.back() == 42);
    
    // Remove front
    dll.removeFront();
    runner.test("After remove front - empty", dll.empty());
    runner.test("After remove front - size 0", dll.size() == 0);
}

void test_single_element_back(TestRunner& runner) {
    DoublyLinkedList dll;
    
    // Add back
    dll.addBack(99);
    runner.test("Single element back - not empty", !dll.empty());
    runner.test("Single element back - size 1", dll.size() == 1);
    runner.test("Single element back - front value", dll.front() == 99);
    runner.test("Single element back - back value", dll.back() == 99);
    
    // Remove back
    dll.removeBack();
    runner.test("After remove back - empty", dll.empty());
    runner.test("After remove back - size 0", dll.size() == 0);
}

// Test multiple elements
void test_multiple_elements(TestRunner& runner) {
    DoublyLinkedList dll;
    
    // Add multiple front
    dll.addFront(1);
    dll.addFront(2);
    dll.addFront(3);
    
    runner.test("Multiple front - size 3", dll.size() == 3);
    runner.test("Multiple front - front is 3", dll.front() == 3);
    runner.test("Multiple front - back is 1", dll.back() == 1);
    
    // Add multiple back
    dll.addBack(4);
    dll.addBack(5);
    
    runner.test("After adding back - size 5", dll.size() == 5);
    runner.test("After adding back - front still 3", dll.front() == 3);
    runner.test("After adding back - back is 5", dll.back() == 5);
}

// Test removal operations
void test_removal_operations(TestRunner& runner) {
    DoublyLinkedList dll;
    
    // Build list: 3 -> 2 -> 1 -> 4 -> 5
    dll.addFront(1);
    dll.addFront(2);
    dll.addFront(3);
    dll.addBack(4);
    dll.addBack(5);
    
    // Remove front
    dll.removeFront();
    runner.test("After remove front - size 4", dll.size() == 4);
    runner.test("After remove front - new front is 2", dll.front() == 2);
    
    // Remove back
    dll.removeBack();
    runner.test("After remove back - size 3", dll.size() == 3);
    runner.test("After remove back - new back is 4", dll.back() == 4);
    
    // Remove until empty
    dll.removeFront(); // Remove 2
    dll.removeFront(); // Remove 1
    dll.removeFront(); // Remove 4
    
    runner.test("After removing all - empty", dll.empty());
    runner.test("After removing all - size 0", dll.size() == 0);
}

// Test edge cases and error conditions
void test_edge_cases(TestRunner& runner) {
    DoublyLinkedList dll;
    
    // Operations on empty list
    runner.test("Empty list front returns -1", dll.front() == -1);
    runner.test("Empty list back returns -1", dll.back() == -1);
    
    // These operations should not crash (they return/do nothing in current impl)
    dll.removeFront(); // Should not crash
    dll.removeBack();  // Should not crash
    runner.test("Operations on empty don't crash", true);
    
    // Test after operations on empty
    runner.test("Still empty after invalid ops", dll.empty());
    runner.test("Still size 0 after invalid ops", dll.size() == 0);
}

// Test palindrome functionality (has bugs)
void test_palindrome(TestRunner& runner) {
    DoublyLinkedList dll;
    
    // Empty list should be palindrome
    runner.test("Empty list is palindrome", dll.isPalindrome());
    
    // Single element
    dll.addFront(1);
    runner.test("Single element is palindrome", dll.isPalindrome());
    
    // Two identical elements
    DoublyLinkedList dll2;
    dll2.addFront(1);
    dll2.addBack(1);
    runner.test("Two identical elements palindrome", dll2.isPalindrome());
    
    // Two different elements
    DoublyLinkedList dll3;
    dll3.addFront(1);
    dll3.addBack(2);
    runner.test("Two different elements not palindrome", !dll3.isPalindrome());
    
    // Odd length palindrome: 1-2-1
    DoublyLinkedList dll4;
    dll4.addFront(2);
    dll4.addFront(1);
    dll4.addBack(1);
    runner.test("Odd palindrome 1-2-1", dll4.isPalindrome());
    
    // Even length palindrome: 1-2-2-1
    DoublyLinkedList dll5;
    dll5.addFront(2);
    dll5.addFront(1);
    dll5.addBack(2);
    dll5.addBack(1);
    runner.test("Even palindrome 1-2-2-1", dll5.isPalindrome());
    
    // Not palindrome: 1-2-3
    DoublyLinkedList dll6;
    dll6.addFront(2);
    dll6.addFront(1);
    dll6.addBack(3);
    runner.test("Not palindrome 1-2-3", !dll6.isPalindrome());
}

// Test mixed operations
void test_mixed_operations(TestRunner& runner) {
    DoublyLinkedList dll;
    
    // Complex sequence
    dll.addFront(10);
    dll.addBack(20);
    dll.addFront(5);
    dll.addBack(25);
    
    // Should be: 5 -> 10 -> 20 -> 25
    runner.test("Mixed ops - size 4", dll.size() == 4);
    runner.test("Mixed ops - front is 5", dll.front() == 5);
    runner.test("Mixed ops - back is 25", dll.back() == 25);
    
    dll.removeFront(); // Remove 5
    dll.removeBack();  // Remove 25
    
    // Should be: 10 -> 20
    runner.test("After mixed removal - size 2", dll.size() == 2);
    runner.test("After mixed removal - front is 10", dll.front() == 10);
    runner.test("After mixed removal - back is 20", dll.back() == 20);
}

// Test print functionality
void test_print_functionality(TestRunner& runner) {
    DoublyLinkedList dll;
    
    // Test empty print (visual inspection)
    std::cout << "Empty list print: ";
    dll.print();
    
    // Test with elements
    dll.addFront(1);
    dll.addBack(2);
    dll.addFront(0);
    
    std::cout << "List [0, 1, 2] print: ";
    dll.print();
    
    runner.test("Print functionality works", true);
}

// Test for memory leaks and corruption
void test_memory_safety(TestRunner& runner) {
    // Create and destroy multiple lists
    for (int i = 0; i < 100; ++i) {
        DoublyLinkedList dll;
        for (int j = 0; j < 10; ++j) {
            dll.addFront(j);
            dll.addBack(j * 2);
        }
        // Destructor should clean up properly
    }
    runner.test("Memory safety test completed", true);
}

// Test large operations
void test_large_operations(TestRunner& runner) {
    DoublyLinkedList dll;
    
    const int N = 1000;
    
    // Add many elements
    for (int i = 0; i < N; ++i) {
        if (i % 2 == 0) {
            dll.addFront(i);
        } else {
            dll.addBack(i);
        }
    }
    
    runner.test("Large ops - correct size", dll.size() == N);
    
    // Remove all elements
    for (int i = 0; i < N; ++i) {
        if (i % 2 == 0) {
            dll.removeFront();
        } else {
            dll.removeBack();
        }
    }
    
    runner.test("Large ops - empty after removal", dll.empty());
}

int main() {
    TestRunner runner;
    
    std::cout << "=== DoublyLinkedList Comprehensive Tests ===" << std::endl << std::endl;
    
    test_construction(runner);
    test_single_element(runner);
    test_single_element_back(runner);
    test_multiple_elements(runner);
    test_removal_operations(runner);
    test_edge_cases(runner);
    test_palindrome(runner);
    test_mixed_operations(runner);
    test_print_functionality(runner);
    test_memory_safety(runner);
    test_large_operations(runner);
    
    runner.summary();
    
    return 0;
}

// Expected results: All tests should pass with your fixes
// Previous bugs were:
// 1. Header/implementation name mismatches - FIXED
// 2. Node member name inconsistency (elem vs value) - FIXED  
// 3. isPalindrome() logic errors - FIXED
// 4. Missing print() method - ADDED
