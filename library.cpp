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

bool isPrime(int number)
{
    std::vector<int> primes = getPrimes(ceil(sqrt(number))) ;
    for (const int &p : primes)
    {
        if (number % p == 0)
        {
            return false;
        }
    }
    return true;
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

std::string derivative(std::string function)
{
    std::vector<std::string> vecFunc;

    // Adds a space (which is not a digit) to the end of the input to help with extracting numbers
    function.push_back(' ');

    // The number to be extracted
    std::string num;
    // Counter the number of characters in a row that are numbers
    int counter = 0;


    for (int c = 0; c < function.size(); c++)
    {
        if (!isnumber(function[c]))
        {
            for (int j = counter; j >= 1; j--)
            {
                num.push_back(function[c-j]);
            }

            vecFunc.push_back(num);
            counter = 0;
            num = "";
//            num.push_back(' ');

            switch (function[c])
            {
                case ' ':
                    break;
                case 'x':
                    vecFunc.push_back("x");
//                    std::cout << "x ";
                    break;
                case '+':
                    vecFunc.push_back("+");
//                    std::cout << "plus ";
                    break;
                case '-':
                    vecFunc.push_back("-");
//                    std::cout << "minus ";
                    break;
                case '*':
                    vecFunc.push_back("*");
//                    std::cout << "multiplication ";
                    break;
                case '/':
                    vecFunc.push_back("/");
//                    std::cout << "division ";
                    break;
                case '^':
                    vecFunc.push_back("^");
//                    std::cout << "exponent ";
                    break;
                default:
                    std::cout << "error 0 ";
            }
        }
        else {
            counter++;
        }
    }



//    for (std::string c: vecFunc)
//    {
//        std::cout << c;
//    }

    std::cout << std::stof(vecFunc[0]) * std::stof(vecFunc[4]);
    std::cout << "x^";
    std::cout << std::stof(vecFunc[4]) - 1;
    return num;
}

std::vector<std::string> tokenize(std::string func)
{
    // "List" of string tokens
    std::vector<std::string> tfunc;
    // Each new token
    std::string token;

    // What separates each token
    char splitStr = '+';
    // The start and end index of each token
    int newTokenStartIndex = 0, newTokenEndIndex = 0;

    for (int i = 0; i < func.size(); i++)
    {
        if (func[i] != splitStr)
        {
            newTokenEndIndex++;
        }
        else
        {
            for (int j = newTokenStartIndex; j <= newTokenEndIndex; j++)
            {
                // Add each character to the string token
                token.push_back(func[j]);
            }
            // Add token to "list" of tokens
            tfunc.push_back(token);

            newTokenStartIndex = ++newTokenEndIndex;

            // Resets the token
            token = "";
        }
    }

    for (std::string s: tfunc)
    {
        std::cout << s << '\n';
    }

    return tfunc;
}

std::string removeWhiteSpace(std::string string)
{
    for (int i = 0; i < string.size(); i++)
    {
        if (string[i] == ' ')
            string.erase(i);
    }
    return string;
}

std::vector<std::string> MakeNameList()
{
    std::vector<std::string> nameList;

    // Declares and defines input based on user, adds space at end to register last character as a new string
    std::string input;
    std::cout << "Enter your variables seperated by a space: \n";
    // https://stackoverflow.com/questions/5838711/stdcin-input-with-spaces
    std::getline(std::cin, input );
    input += " ";

    // Add each string seperated by a space to nameList
    std::string tempString;
    for (char c : input)
    {
        if (c == ' ')
        {
            nameList.push_back(tempString);
            tempString = "";
        }
        else
        {
            tempString.push_back(c);
        }
    }
    return nameList;
}

void GenerateLaTeXDocument()
{
    //https://www.w3schools.com/cpp/cpp_files.asp
    std::ofstream outputFile("LaTeXTable.tex");

    std::vector<std::string> packageList = {"amsmath, simpsons"};
    outputFile << GenerateLaTeXHeader(packageList);

    outputFile << "\\begin{document}\n";
    // Makes Truth Table
    std::vector<std::string> nameList = MakeNameList();
    std::string truthTable = GenerateTruthTable(nameList);
    outputFile << truthTable;

    outputFile << "\\end{document}";
    outputFile.close();
}

std::string GenerateLaTeXHeader(const std::vector<std::string>& packageList)
{
    std::string header = "\\documentclass{article}\n"
                         "\\pagestyle{fancy}\n";

    header += "\\usepackage{";
    for (int packageListIndex = 0; packageListIndex < packageList.size(); packageListIndex++)
    {
        if (packageListIndex != packageList.size() - 1)
            header += packageList[packageListIndex] + ", ";
        else
            header += packageList[packageListIndex] + "}\n";
    }

    header += "\\lhead{GeneratedTextDocument}\n"
              "\\rhead{Raven Suggs and Paul Cimarusti}\n";
    return header;
}

std::string GenerateTruthTable(std::vector<std::string> nameList)
{
    std::string truthTable = "\\begin{center}\n"
                             "\t \\begin{tabular}";

    std::string columnsString = "{";
    for (int columnNumber = 0; columnNumber < nameList.size(); columnNumber++)
    {
        if (columnNumber != nameList.size() - 1)
            columnsString += "c | ";
        else
            columnsString += "c}\n";
    }
    truthTable +=  columnsString;

    std::string nameString;
    for (int varIndex = 0; varIndex < nameList.size(); varIndex++)
    {
        if (varIndex != nameList.size() - 1)
            nameString += "$" + nameList[varIndex] + "$ & ";
        else
            nameString += "$" + nameList[varIndex] + "$";
    }
    truthTable += "\t \t" + nameString + " \\\\\n";


    return truthTable;
}

