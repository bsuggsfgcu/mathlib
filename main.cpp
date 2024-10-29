#include "library.h"
void exMain();

int main(){
    exMain();
}

// Examples of how to implement library
void exMain()
{
    // Utilities

//tokenize("4x^3 + 6x^2 + 7x + 1 + 4 + 2 + 4");
// std::cout << "\n";
//    std::cout << removeWhiteSpace("8x^2+ 6x^3 + 7    + 1");


    // Number Theory
    std::cout << "Primes between 1 and 100: ";
    std::vector<int> a = NumberTheory::getPrimes(100);
    for (const int &i : a){
        std::cout << i << ' ';
    }

    std::cout << '\n';

    std::cout << "Multiplicative Persistence of 721: ";
    std::cout << NumberTheory::getMultiplicativePersistence(721);

    std::cout << '\n';

    std::cout << "Collatz number of 87: " << NumberTheory::getCollatzNumber(87);

    std::cout << '\n';

    std::cout << "Fibonacci Index of 100: " << NumberTheory::fibonacciIndex(
            754346429);

    std::cout << '\n';

    std::cout << "794 is prime: " << NumberTheory::isPrime(-90);

    // Calculus
//    derivative("50x^4");


    // LaTeX
//    std::vector<std::string> list = MakeNameList();
//    for (const std::string& c : list)
//    {
//        std::cout << c << '-';
//    }
//
//    GenerateLaTeXDocument();
//
//    std::string func;
//    std::cout << "Enter a function: ";
//    std::cin >> func;
//    std::string stringFunc = removeWhiteSpace(func);
//    funcTokenize(stringFunc);
}