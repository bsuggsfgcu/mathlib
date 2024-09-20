#include<iostream>
#include "library.h"

int main(){
    std::cout << "Primes between 1 and 100: ";
    std::vector<int> a = getPrimes(100);
    for (const int &i : a){
        std::cout << i << ' ';
    }


    std::cout << '\n';


    std::cout << "Multiplicative Persistence of 876: ";
    std::cout << getMultiplicativePersistence(876);


    std::cout << '\n';


    std::cout << "Collatz number of 87: " << getCollatzNumber(87);


    std::cout << '\n';

    std::cout << "Fibonacci Index of 100: " << fibonacciIndex(
            7540113804746346429);


    std::cout << '\n';

    std::cout << "794 is prime: " << isPrime(-90);

    derivative("40*x^2");
    return 0;
}
