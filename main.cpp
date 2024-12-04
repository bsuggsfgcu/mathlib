// Coder/Developer: Cesar Fandino, Raven Suggs, & Paul Cimarusti
// Class:           COP 2006-80599, Fall 2024
// Date:            September 19, 2024
// Description:     C++ Math Library Program
// Log:             September 19, Project start
// Log:             November 13, Created example main function to test library functions
#include "library.h"
void NumberTheoryMain();
void calcMain();
void LaTexMain();

int main()
{
    char choice;
    std::cout << "What would you like to do: \n"
                 "a) Explore math functions\n"
                 "b) Find the derivative\n"
                 "c) Generate a LaTeX truth table\n";
    std::cin >> choice;

    switch(choice)
    {
        case 'a':
            NumberTheoryMain();
            break;
        case 'b':
            calcMain();
            break;
        case 'c':
            LaTexMain();
            break;
        default:
            std::cerr << "Error code 0: improper choice input, please try again...";
    }
}

// Examples of how to implement library
void NumberTheoryMain()
{
    char numberTheoryChoice;
    std::cout << "What would you like to do: \n"
                 "a) Generate primes\n"
                 "b) Test for prime\n"
                 "c) Find multiplicative persistence of a number\n"
                 "d) Find the collatz number of a number\n"
                 "e) Find the fibonacci Index of a number (about where in the fibonacci sequence a number appears\n";

    std::cin >> numberTheoryChoice;

    switch (numberTheoryChoice)
    {
        case 'a':
        {
            int upperBound;
            std::cout << "Enter an upperbound: ";
            std::cin >> upperBound;
            std::vector<int> a = NumberTheory::getPrimes(upperBound);
            for (const int &i: a)
                std::cout << i << ' ';
            break;
        }
        case 'b':
            int number;
            std::cout << "Enter an integer: ";
            std::cin >> number;
            if( NumberTheory::isPrime(number))
                std::cout << number << " is prime.";
            else
                std::cout << number << " is not prime.";
            break;

        case 'c':
            int mulNumber;
            std::cout << "Enter an integer: ";
            std::cin >> mulNumber;
            std::cout << "The multiplicative persistence of " << mulNumber << " is " << NumberTheory::getMultiplicativePersistence(mulNumber);
            break;

        case 'd':
            int colNumber;
            std::cout << "Enter an integer: ";
            std::cin >> colNumber;
            std::cout << "The collatz number of " << colNumber << " is " << NumberTheory::getCollatzNumber(colNumber);
            break;

        case 'e':
            int fibNumber;
            std::cout << "Enter an integer: ";
            std::cin >> fibNumber;
            std::cout << "The fibonacci index of " << fibNumber << " is " << NumberTheory::fibonacciIndex(fibNumber);
            break;

        default:
            std::cerr << "Error 0: Invalid choice input, please try again...";
    }
}

void calcMain()
{
    std::string func;
    std::cout << "Enter a function: ";
    while (func.empty())
        std::getline(std::cin, func);

//    std::string func = "7*(x^4+2)-4(x^2)+2";
//    std::cout << func  + '\n';
    Function function = Function(func);
    std::cout << function.Derivative();
}

void LaTexMain()
{
    LaTeX::GenerateLaTeXDocument();
}
