#ifndef TESTING_H
#define TESTING_H
#include <iostream>
#include <sstream>
#include <memory>

/*
 * NOTE: You MAY EDIT this file to perform testing as you progress through the assignment.
 * Be sure to edit the implementation in testing.cpp as well.
 *
 * You may need to edit the original tests implementation as you implement your design.
 * The original test implementations are just simple examples that do not necessarily
 * reflect the final application.
 */

/**
 * @brief The Testing class is a simple example of performing unit tests.
 * You can modify as required to support the testing of your assignment.
 *
 * Tests should cover correct operation of your classes including (but not
 * limited to): constructors, destructors, accessors, mutators, and public members.
 *
 * An incomplete example has been provided for you.
 */
class Testing
{
private:
    // Declare functions for your own tests here.
    // Be sure to update the implementation of runTests() to call the new tests.
    // Each test function must return an std::string and should return passFailText()
    // Refer to the provided examples.

    // Example test function for the Character class
    std::string testCharacter();
    std::string testCreature();
    std::string testDoor();
    std::string testDungeon();
    std::string testGame();
    std::string testWeapon();
    std::string testRoom();
    std::string testWall();

    // TODO: add functions for your own tests here

    // Test functions for the CsvFile class.
    // Do not modify! They are here for you to check your implementation for conformance.
    // Your CsvFile implementation will be automatically tested against the same test
    // suite but using different data.
    void csvFileTestSuite();
    std::string testLoadFailureForEmptyCsvFile();
    std::string testLoadSuccessForHeaderButNoDataCsvFile();
    std::string testOutOfRangeReturnsEmptyString();
    std::string testHeaderFieldsCorrectlyRead();
    std::string testCommaSeparatedRowDataAccessible();
    std::string testMultipleRowsOfData();
    std::string testLoadFailureOnRowWithDifferingNumberOfColumns();
    std::string testPreservationOfWhitespaceInFields();
    std::string testLineEndingOnLastLine();
    std::string testDoubleQuotedFields();
    std::string testDoubleQuotedFieldsMixedWithUnquoted();
    std::string testReplacementOfBlackslashNInQuotedFieldsWithNewline();
    std::string testDoubleQuotesWithinFields();
    std::string testReadingCsvDataFromFile(); // once the rest of the tests pass, so should this one

public:
    /**
     * @brief Testing default constructor to safely initialise the internal state.
     *
     * It is implemented in the header to keep the source file clean. That is,
     * 'testing.cpp' will contain only the implementations of your test functions.
     */
    Testing(): _failureCount{0}, _assertionCount{0}, _failure{false}, _failMessages{} {
        // No other setup required.
    }
    ~Testing() = default;

    /**
     * @brief runTests the entry point for running one or more tests.
     *
     * Be sure to update its implementation each time you add a new test.
     */
    void runTests();

    /**
     * @brief printFailures outputs the collected failure messages to the given stream
     * @param ostream
     */
    void printTestResults(std::ostream &ostream);

private:
    unsigned int _failureCount;    ///< count of all failures that have occurred
    unsigned int _assertionCount;  ///< tally of the number of assertions made
    bool _failure; ///< boolean indicating failure state of current test
    std::stringstream _failMessages; ///< stream to collect failure messages during testing

    /* ------------------------------------------------------------------------------
     * The following are helper functions that operate a little like common
     * Unit Testing frameworks. You do not need to understand their implementations,
     * but hopefully you will by the end of the course.
     * -----------------------------------------------------------------------------*/

    /**
     * @brief equals Test support function, compares the expected and actual values, if they
     * are not equal to one another, puts the Testing object into the failure
     * state and appends failMessage to the output to be reported later.
     *
     * @param expected the expected value
     * @param actual the actual value
     * @param failMessage the message to display if the test fails
     */
    template<class T>
    void equal(const T &expected, const T &actual, const std::string &failMessage) {
        ++_assertionCount;
        if (expected != actual) {
            ++_failureCount;
            _failure = true;
            _failMessages << failMessage << " [expected: " << expected << " actual: " << actual  << "]" << std::endl;
        }
    }

    /**
     * @brief equals Test support function, compares the expected and actual values, if they
     * are equal to one another, puts the Testing object into the failure
     * state and appends failMessage to the output to be reported later.
     *
     * @param expected the expected value
     * @param actual the actual value
     * @param failMessage the message to display if the test fails
     */
    template<class T>
    void notEqual(const T &expected, const T &actual, const std::string &failMessage) {
        ++_assertionCount;
        if (expected == actual) {
            ++_failureCount;
            _failure = true;
            _failMessages << failMessage << " [value: " << expected << "]" << std::endl;
        }
    }

    /**
     * @brief lessThan Test support function, compares the expected and actual values,
     * if they actual is greater than or equal to expected, puts the Testing object into the failure
     * state and appends failMessage to the output to be reported later.
     *
     * @param expected the expected value
     * @param actual the actual value
     * @param failMessage the message to display if the test fails
     */
    template<class T>
    void lessThan(const T &expected, const T &actual, const std::string &failMessage) {
        ++_assertionCount;
        if (actual >= expected) {
            ++_failureCount;
            _failure = true;
            _failMessages << failMessage << " [expected less than: " << expected << " actual: " << actual  << "]" << std::endl;
        }
    }

    /**
     * @brief greaterThan Test support function, compares the expected and actual values,
     * if they actual is less than or equal to expected, puts the Testing object into the failure
     * state and appends failMessage to the output to be reported later.
     *
     * @param expected the expected value
     * @param actual the actual value
     * @param failMessage the message to display if the test fails
     */
    template<class T>
    void greaterThan(const T &expected, const T &actual, const std::string &failMessage) {
        ++_assertionCount;
        if (actual <= expected) {
            ++_failureCount;
            _failure = true;
            _failMessages << failMessage << " [expected greater than: " << expected << " actual: " << actual  << "]" << std::endl;
        }
    }

    /**
     * @brief instanceOf Test support function, checks if the value of the given pointer
     * is of the template type T. If not, the Testing object is put into the fail state
     * and the failure message is appended.
     *
     * @param value the shared pointer to check the type
     * @param failMessage
     */
    template<class T, class U>
    void instanceOf(const std::shared_ptr<U> &value, const std::string &failMessage) {
        ++_assertionCount;
        if (!std::dynamic_pointer_cast<T>(value)) {
            ++_failureCount;
            _failure = true;
            _failMessages << failMessage << std::endl;
        }
    }

    /**
     * @brief passFailText convenience function to return the "Passed" or "Failed" strings.
     * @return "Pass" or "Fail"
     */
    inline std::string passFailText() {
        bool failed = _failure;
        _failure = false; // reset state for next test
        return failed ? "Failed" : "Passed";
    }
};

inline void Testing::printTestResults(std::ostream &ostream) {
    ostream << std::endl;
    ostream << _assertionCount << " tests executed; "
            << _assertionCount - _failureCount <<  " tests passed; "
            << _failureCount << " failures" << std::endl;

    if (_failMessages.rdbuf()->in_avail()) {
        ostream << "Failures:" << std::endl;
        ostream << _failMessages.str() << std::endl;
    }
    else {
        ostream << "All tests passed!" << std::endl;
    }
}


template<>
inline void Testing::equal(const std::string &expected, const std::string &actual, const std::string &failMessage) {
    ++_assertionCount;
    if (expected != actual) {
        ++_failureCount;
        _failure = true;
        _failMessages << failMessage << " [expected: " << '\'' << expected << '\'' << " actual: " << '\'' << actual << '\''  << "]" << std::endl;
    }
}

#endif // TESTING_H
