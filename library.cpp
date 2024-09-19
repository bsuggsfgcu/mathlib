#include "library.h"

std::vector<int> getPrimes(int upperBound, int lowerBound){
    std::vector<int> primeNumbers;
    // true: index is prime
    // false: index is not prime
    std::vector<bool> primeBooleans;

    // Sets all booleans in primeBooleans to true
    primeBooleans.reserve(upperBound);
    for (int i = 0; i < upperBound; i++) {
        primeBooleans.push_back(true);
    }

    // Sieve of Eratosthenes to generate primes
    for (int i = lowerBound; i < upperBound; i++) {
        for (int j = lowerBound; j < upperBound / i + 1; j++) {
            primeBooleans[i * j] = false;
        }
    }

    // Copies indexes marked true to a list
    for (int i = 2; i < upperBound; i++) {
        if (primeBooleans[i]) {
            primeNumbers.push_back(i);
        }
    }
    return primeNumbers;
}

int getMultiplicativePersistence(int number) {
    // Converts number to string in order to reference each digit
    std::string strNumber = std::to_string(number);

    int iterations = 0;

    int product;
    do {
        product = 1;
        // for each digit in number
        for (int i = 0; i < strNumber.length(); i++) {
            product *= strNumber[i] - '0'; // - '0' converts a char to an int
        }

        iterations ++;
        strNumber = std::to_string(product);
//        std::cout << product << ", " << iterations << "\n";
    } while (product > 9); // while product is not a single digit
    return iterations;
}

int getCollatzNumber(int number) {
    int collatzIterations = 0;
    // The collatz conjecture states that all numbers will reach one
    // when C(n) is applied recursively
    while (number != 1) {
        // If n is odd
        if (number % 2 == 1) {
            number = number * 3 + 1;
        }
        // if n is even
        else {
            number /= 2;
        }
        collatzIterations ++;
    }
    return collatzIterations;
}

long double fibonacciIndex(long int number){
    return log(number * sqrt(5)) / log((1+sqrt(5))/2);
}