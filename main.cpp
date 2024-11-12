#include "library.h"
void exMain();
void calcMain();

int main(){
   calcMain();
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
    std::vector<int> a = NumberTheory::getPrimes(100, 80);
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
//    Derivative("50x^4");


//     LaTeX
//    std::vector<std::string> list = LaTeX::MakeNameList();
//    for (const std::string& c : list)
//    {
//        std::cout << c << '-';
//    }

    LaTeX::GenerateLaTeXDocument();
}

void calcMain()
{
//    std::string func;
//    std::cout << "Enter a function: ";
//    std::getline(std::cin, func);

    std::string func = "7*(x^4+2)-4(x^2)+2";
    std::cout << func  + '\n';
    Function function = Function(func);
    function.Derivative();
}