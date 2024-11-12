// Programmer: Paul Cimarusti
// Date: September 12, 2024
// Log: Sep 12 2024:
/* files created, .h and .cpp linked, added executable in CMakeLists.txt,
 * optional lower bound added to getPrimes function,
 * multiplicative persistence function added,
 * collatz function added
 */
// Sources: https://favtutor.com/blogs/split-string-cpp#:~:text=The%20strtok()%20function%20is,0)%20at%20the%20delimiter%20position.for splitting strings in tokenize function

#ifndef MATHLIB_LIBRARY_H
#define MATHLIB_LIBRARY_H

#include<vector>
#include<iostream>
#include<cmath>
#include<fstream>
#include<cstdlib>

class Utilities
{
public:
    /**
     * @brief Removes whitespace from an input
     * @param string
     * @return string
     */
    static std::string removeWhiteSpace(std::string string);
    //    // TODO -> Paul: Add comment
//    static std::vector<std::string> tokenize(std::string func);
//
//    /**
//     * @brief tokenizes a function into an array of strings
//     * @param input: a string representing a function (without whitespace)
//     * @return std::vector<std::string> a list of string tokens
//     */
//    static std::vector<std::string> funcTokenize(std::string input);
};

// TODO: Paul Flow Charts for Number Theory
class NumberTheory
{
public:
    /**
     * @brief Generates all prime numbers up to the specified upper bound.
     * This function uses the Sieve of Eratosthenes algorithm to generate
     * a list of prime numbers that are strictly less than the upperBound.
     * @param upperBound The maximum number up to which primes are generated.
     * @return A vector containing all prime numbers between a lower and upper bound.
     */
    static std::vector<int> getPrimes(int upperBound, int lowerBound = 2);

    /**
     * @brief Returns a bool (if argument is prime)
     * This function uses getPrimes(int upperBound, int lowerBound) as a helper function
     * to generate all primes up to sqrt(number) and tests if any of them are factors individually
     * @param number an integer to be tested for being prime
     * @return A boolean representing if a number is prime
     */
    static bool isPrime(int number);

    /**
    * @brief Finds the multiplicative persistence of a number.
    * This function converts the provided number between integers and std::string s
     * in order to treat each digit as a char, multiplies them in a while loop, and
     * keeps track of the number iterations it takes for their product to be a single digit.
     * @param number the number to return the multiplicative persistence of.
     * @return an integer representing the multiplicative persistence of the input.
     */
    static int getMultiplicativePersistence(int number);

    /**
     * @brief Finds the number of iterations of C(n) it takes to reach 1
     * This function uses a while loop and two conditions (is even and is odd)
     * and repeatedly applies C(n) to determine how many iterations it takes
     * @param number the number to find the C(n) iterations of
     * @return an integer representing the number of iterations it takes C(n) to reach 1
     */
    static int getCollatzNumber(int number);

    /**
     * @brief Estimates the index of the fibonacci sequence where a number might belong. (Where f_1 = 1)
     * @param number the number to estimate the index of
     * @return a long double representing the index of the fibonacci sequence to find the parameter
     */
    static long double fibonacciIndex(int number);
};

// TODO: Cesar Error Handling (You'll get a std::string, if the function is not valid please return a string explaining why)
// TODO: Paul and Raven break up string via "open" + or - and constants
class Function
{
public:
    Function(std::string input);
    std::string string;

    /**
     * @brief returns the derivative of a single variable function
     * @param function (any variable can be used)
     * @return a string representing the derivative of the given function
     */
    std::string derivative();
};

// TODO: Paul Finish LaTeX
class LaTeX {
public:
    std::vector<std::string> MakeNameList();
    void GenerateLaTeXDocument();
    std::string GenerateLaTeXHeader(const std::vector<std::string>& packageList);
    std::string GenerateTruthTable(std::vector<std::string> nameList);
};

#endif //MATHLIB_LIBRARY_H
