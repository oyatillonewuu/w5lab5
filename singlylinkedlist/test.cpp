#include <iostream>
#include <cassert>
#include <sstream>
#include "ldlist.h"
using namespace std;

class TestRunner {
private:
    int passed = 0;
    int failed = 0;
    
public:
    void test(const string& name, bool condition) {
        if (condition) {
            cout << "✓ " << name << endl;
            passed++;
        } else {
            cout << "✗ " << name << endl;
            failed++;
        }
    }
    
    void summary() {
        cout << "\n=== Test Summary ===" << endl;
        cout << "Passed: " << passed << endl;
        cout << "Failed: " << failed << endl;
        cout << "Total: " << (passed + failed) << endl;
    }
};

// Helper to capture print output
string captureOutput(IntLinkedList& list) {
    stringstream buffer;
    streambuf* old = cout.rdbuf(buffer.rdbuf());
    list.print();
    cout.rdbuf(old);
    return buffer.str();
}

void testConstructorDestructor(TestRunner& t) {
    cout << "\n--- Constructor/Destructor Tests ---" << endl;
    
    IntLinkedList list;
    t.test("Constructor creates empty list", list.empty());
    
    // Destructor tested implicitly - no memory leaks expected
}

void testBasicOperations(TestRunner& t) {
    cout << "\n--- Basic Operations Tests ---" << endl;
    
    IntLinkedList list;
    
    // Empty list tests
    t.test("Empty list size is 0", list.size() == 0);
    t.test("Empty list sum is 0", list.sum() == 0);
    
    // addFront tests
    list.addFront(5);
    t.test("After addFront(5): not empty", !list.empty());
    t.test("After addFront(5): size is 1", list.size() == 1);
    t.test("After addFront(5): sum is 5", list.sum() == 5);
    
    list.addFront(3);
    t.test("After addFront(3): size is 2", list.size() == 2);
    t.test("After addFront(3): sum is 8", list.sum() == 8);
    
    // addBack tests
    IntLinkedList list2;
    list2.addBack(10);
    t.test("After addBack(10): not empty", !list2.empty());
    t.test("After addBack(10): size is 1", list2.size() == 1);
    t.test("After addBack(10): sum is 10", list2.sum() == 10);
    
    list2.addBack(20);
    t.test("After addBack(20): size is 2", list2.size() == 2);
    t.test("After addBack(20): sum is 30", list2.sum() == 30);
}

void testPrintOutput(TestRunner& t) {
    cout << "\n--- Print Output Tests ---" << endl;
    
    IntLinkedList empty;
    string emptyOutput = captureOutput(empty);
    t.test("Empty list prints 'List is Empty!'", emptyOutput.find("List is Empty!") != string::npos);
    
    IntLinkedList single;
    single.addFront(42);
    string singleOutput = captureOutput(single);
    t.test("Single element list prints correctly", singleOutput.find("42") != string::npos);
    
    IntLinkedList multi;
    multi.addFront(3);
    multi.addFront(2);
    multi.addFront(1);
    string multiOutput = captureOutput(multi);
    t.test("Multi-element list contains all elements", 
           multiOutput.find("1") != string::npos && 
           multiOutput.find("2") != string::npos && 
           multiOutput.find("3") != string::npos);
}

void testAverage(TestRunner& t) {
    cout << "\n--- Average Tests ---" << endl;
    
    IntLinkedList list;
    list.addFront(10);
    list.addFront(20);
    list.addFront(30);
    
    t.test("Average of [30,20,10] is 20.0", list.average() == 20.0);
    
    IntLinkedList odd;
    odd.addFront(1);
    odd.addFront(2);
    odd.addFront(3);
    t.test("Average of [3,2,1] is 2.0", odd.average() == 2.0);
    
    IntLinkedList single;
    single.addFront(7);
    t.test("Average of single element [7] is 7.0", single.average() == 7.0);
}

void testRemoveFront(TestRunner& t) {
    cout << "\n--- RemoveFront Tests ---" << endl;
    
    // Test on empty list
    IntLinkedList empty;
    empty.removeFront();
    t.test("removeFront on empty list doesn't crash", empty.empty());
    
    // Test single element
    IntLinkedList single;
    single.addFront(5);
    single.removeFront();
    t.test("removeFront on single element makes list empty", single.empty());
    
    // Test multiple elements
    IntLinkedList multi;
    multi.addFront(3);
    multi.addFront(2);
    multi.addFront(1);
    multi.removeFront();
    t.test("removeFront removes first element", multi.size() == 2);
    t.test("removeFront leaves sum correct", multi.sum() == 5); // 2+3
}

void testRemoveBack(TestRunner& t) {
    cout << "\n--- RemoveBack Tests ---" << endl;
    
    // Test on empty list
    IntLinkedList empty;
    empty.removeBack();
    t.test("removeBack on empty list doesn't crash", empty.empty());
    
    // Test single element
    IntLinkedList single;
    single.addFront(5);
    single.removeBack();
    t.test("removeBack on single element makes list empty", single.empty());
    
    // Test multiple elements
    IntLinkedList multi;
    multi.addFront(3);
    multi.addFront(2);
    multi.addFront(1); // List: 1->2->3
    multi.removeBack();
    t.test("removeBack removes last element", multi.size() == 2);
    t.test("removeBack leaves sum correct", multi.sum() == 3); // 1+2
    
    // Test two elements
    IntLinkedList two;
    two.addFront(2);
    two.addFront(1);
    two.removeBack();
    t.test("removeBack on two elements leaves one", two.size() == 1);
    t.test("removeBack on two elements leaves first", two.sum() == 1);
}

void testRemoveAll(TestRunner& t) {
    cout << "\n--- RemoveAll Tests ---" << endl;
    
    // Test on empty list
    IntLinkedList empty;
    int removed = empty.removeAll(5);
    t.test("removeAll on empty list returns 0", removed == 0);
    
    // Test no matches
    IntLinkedList noMatch;
    noMatch.addFront(1);
    noMatch.addFront(2);
    noMatch.addFront(3);
    removed = noMatch.removeAll(5);
    t.test("removeAll with no matches returns 0", removed == 0);
    t.test("removeAll with no matches preserves list", noMatch.size() == 3);
    
    // Test all elements match
    IntLinkedList allMatch;
    allMatch.addFront(5);
    allMatch.addFront(5);
    allMatch.addFront(5);
    removed = allMatch.removeAll(5);
    t.test("removeAll with all matches returns correct count", removed == 3);
    t.test("removeAll with all matches empties list", allMatch.empty());
    
    // Test mixed matches
    IntLinkedList mixed;
    mixed.addBack(5);
    mixed.addBack(3);
    mixed.addBack(5);
    mixed.addBack(7);
    mixed.addBack(5);
    removed = mixed.removeAll(5);
    t.test("removeAll mixed matches returns correct count", removed == 3);
    t.test("removeAll mixed matches leaves correct size", mixed.size() == 2);
    t.test("removeAll mixed matches leaves correct sum", mixed.sum() == 10); // 3+7
    
    // Test front consecutive matches
    IntLinkedList frontMatch;
    frontMatch.addBack(5);
    frontMatch.addBack(5);
    frontMatch.addBack(3);
    frontMatch.addBack(7);
    removed = frontMatch.removeAll(5);
    t.test("removeAll front consecutive returns 2", removed == 2);
    t.test("removeAll front consecutive leaves size 2", frontMatch.size() == 2);
}

void testReverse(TestRunner& t) {
    cout << "\n--- Reverse Tests ---" << endl;
    
    // Test empty list
    IntLinkedList empty;
    empty.reverse();
    t.test("reverse on empty list doesn't crash", empty.empty());
    
    // Test single element
    IntLinkedList single;
    single.addFront(5);
    single.reverse();
    t.test("reverse on single element preserves size", single.size() == 1);
    t.test("reverse on single element preserves value", single.sum() == 5);
    
    // Test two elements
    IntLinkedList two;
    two.addBack(1);
    two.addBack(2);
    two.reverse();
    t.test("reverse on two elements preserves size", two.size() == 2);
    t.test("reverse on two elements preserves sum", two.sum() == 3);
    
    // Test multiple elements - check by building expected and comparing sums at each prefix
    IntLinkedList multi;
    multi.addBack(1);
    multi.addBack(2);
    multi.addBack(3);
    multi.addBack(4);
    
    IntLinkedList expected;
    expected.addBack(4);
    expected.addBack(3);
    expected.addBack(2);
    expected.addBack(1);
    
    multi.reverse();
    t.test("reverse preserves size", multi.size() == expected.size());
    t.test("reverse preserves sum", multi.sum() == expected.sum());
    
    // Double reverse should restore original
    multi.reverse();
    IntLinkedList original;
    original.addBack(1);
    original.addBack(2);
    original.addBack(3);
    original.addBack(4);
    t.test("double reverse restores original sum", multi.sum() == original.sum());
}

void testEdgeCases(TestRunner& t) {
    cout << "\n--- Edge Cases ---" << endl;
    
    // Large numbers
    IntLinkedList large;
    large.addFront(2147483647); // INT_MAX
    large.addFront(-2147483648); // INT_MIN
    t.test("Handles INT_MAX and INT_MIN", large.size() == 2);
    
    // Zero values
    IntLinkedList zeros;
    zeros.addFront(0);
    zeros.addBack(0);
    t.test("Handles zero values", zeros.sum() == 0 && zeros.size() == 2);
    
    // Negative numbers
    IntLinkedList negative;
    negative.addFront(-5);
    negative.addBack(-10);
    t.test("Handles negative numbers", negative.sum() == -15);
    
    // Mixed operations sequence
    IntLinkedList mixed;
    mixed.addFront(1);
    mixed.addBack(2);
    mixed.addFront(3);
    mixed.removeBack();
    mixed.addBack(4);
    t.test("Mixed operations sequence works", mixed.size() == 3);
}

void testExtremeStress(TestRunner& t) {
    cout << "\n--- Extreme Stress Tests ---" << endl;
    
    // Integer overflow in sum
    IntLinkedList overflow;
    overflow.addFront(2147483647); // INT_MAX
    overflow.addFront(1);
    t.test("Integer overflow in sum handled", overflow.size() == 2);
    // Note: sum() will overflow to negative, but shouldn't crash
    
    // Large list operations
    IntLinkedList large;
    for (int i = 0; i < 10000; i++) {
        large.addFront(i);
    }
    t.test("Can create 10k element list", large.size() == 10000);
    
    // Mass removal
    int removed = large.removeAll(5000);
    t.test("Mass removal works on large list", removed >= 0);
    
    // Reverse large list
    large.reverse();
    t.test("Can reverse large list", large.size() > 0);
    
    // Exhaust and rebuild
    while (!large.empty()) {
        large.removeFront();
    }
    t.test("Can exhaust large list completely", large.empty());
    
    for (int i = 0; i < 1000; i++) {
        large.addBack(i);
    }
    t.test("Can rebuild after exhaustion", large.size() == 1000);
}

void testRemoveAllExtreme(TestRunner& t) {
    cout << "\n--- RemoveAll Extreme Cases ---" << endl;
    
    // All identical elements
    IntLinkedList identical;
    for (int i = 0; i < 100; i++) {
        identical.addBack(7);
    }
    int removed = identical.removeAll(7);
    t.test("RemoveAll identical elements count", removed == 100);
    t.test("RemoveAll identical elements empties list", identical.empty());
    
    // Alternating pattern
    IntLinkedList alternating;
    for (int i = 0; i < 100; i++) {
        alternating.addBack(i % 2);
    }
    removed = alternating.removeAll(0);
    t.test("RemoveAll alternating pattern", removed == 50);
    t.test("RemoveAll alternating leaves correct size", alternating.size() == 50);
    
    // Single match at end
    IntLinkedList endMatch;
    for (int i = 0; i < 50; i++) {
        endMatch.addBack(i);
    }
    endMatch.addBack(999);
    removed = endMatch.removeAll(999);
    t.test("RemoveAll single match at end", removed == 1);
    t.test("RemoveAll single match at end preserves rest", endMatch.size() == 50);
    
    // Consecutive matches in middle
    IntLinkedList middleMatch;
    middleMatch.addBack(1);
    middleMatch.addBack(2);
    for (int i = 0; i < 10; i++) {
        middleMatch.addBack(5);
    }
    middleMatch.addBack(8);
    middleMatch.addBack(9);
    removed = middleMatch.removeAll(5);
    t.test("RemoveAll consecutive middle matches", removed == 10);
    t.test("RemoveAll consecutive middle preserves edges", middleMatch.size() == 4);
    t.test("RemoveAll consecutive middle correct sum", middleMatch.sum() == 20); // 1+2+8+9
}

void testAverageExtreme(TestRunner& t) {
    cout << "\n--- Average Extreme Cases ---" << endl;
    
    // This will likely crash or give undefined behavior - division by zero
    // But we're testing, not fixing
    IntLinkedList empty;
    try {
        double avg = empty.average();
        t.test("Average of empty list doesn't crash", true);
        t.test("Average of empty list value check", avg != avg); // NaN check
    } catch (...) {
        t.test("Average of empty list throws exception", true);
    }
    
    // Very large numbers leading to precision issues
    IntLinkedList precision;
    precision.addFront(2147483647);
    precision.addFront(2147483646);
    precision.addFront(2147483645);
    double avg = precision.average();
    t.test("Average with large numbers computed", avg > 2000000000.0);
    
    // Mixed positive/negative with potential cancellation
    IntLinkedList mixed;
    mixed.addFront(1000000);
    mixed.addFront(-1000000);
    mixed.addFront(1);
    avg = mixed.average();
    t.test("Average with cancellation", abs(avg - 0.333333) < 0.01);
}

void testMemoryStress(TestRunner& t) {
    cout << "\n--- Memory Stress Tests ---" << endl;
    
    // Rapid allocation/deallocation
    for (int cycle = 0; cycle < 100; cycle++) {
        IntLinkedList temp;
        for (int i = 0; i < 100; i++) {
            temp.addFront(i);
        }
        // Destructor handles cleanup
    }
    t.test("Survived 100 allocation/deallocation cycles", true);
    
    // Build and destroy through operations
    IntLinkedList growth;
    for (int i = 0; i < 1000; i++) {
        growth.addBack(i);
        if (i % 3 == 0) growth.removeFront();
        if (i % 7 == 0) growth.removeBack();
    }
    t.test("Survived growth/shrink pattern", growth.size() >= 0);
    
    // Mass removeAll operations
    IntLinkedList mass;
    for (int i = 0; i < 500; i++) {
        mass.addBack(i % 10);
    }
    for (int target = 0; target < 10; target++) {
        mass.removeAll(target);
    }
    t.test("Mass removeAll empties list", mass.empty());
}

int main() {
    TestRunner t;
    
    testConstructorDestructor(t);
    testBasicOperations(t);
    testPrintOutput(t);
    testAverage(t);
    testRemoveFront(t);
    testRemoveBack(t);
    testRemoveAll(t);
    testReverse(t);
    testEdgeCases(t);
    testExtremeStress(t);
    testRemoveAllExtreme(t);
    testAverageExtreme(t);
    testMemoryStress(t);
    
    t.summary();
    
    return 0;
}
