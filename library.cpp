#include "library.h"


// UTILITIES
std::string Utilities::removeWhiteSpace(std::string string)
{
    for (int i = 0; i < string.size(); i++)
    {
        if (string[i] == ' ')
            string.erase(i);
    }
    return string;
}


// NUMBER THEORY
std::vector<int> NumberTheory::getPrimes(int upperBound, int lowerBound){
    std::vector<bool> primeBooleans;    // true: index is prime, false: index is not prime
    std::vector<int> primeNumbers;

    // Sets all booleans in primeBooleans to true
    primeBooleans.reserve(upperBound);
    for (int i = 2; i < upperBound; i++)
        primeBooleans.push_back(true);

    // Use Sieve of Eratosthenes to find primes
    for (int i = 2; i < upperBound; i++)
    {
        for (int j = 2; j < upperBound / i + 1; j++)
            primeBooleans[i * j] = false;
    }

    // Copies indexes marked true to a list
    for (int i = lowerBound; i < upperBound; i++)
    {
        if (primeBooleans[i])
            primeNumbers.push_back(i);
    }
    return primeNumbers;
}

bool NumberTheory::isPrime(int number)
{
    // Checks if the ceiling of the square root of the input is in a generated prime list, if so, return false, otherwise true
    std::vector<int> primes = getPrimes(ceil(sqrt(number))) ;
    // https://www.geeksforgeeks.org/stdall_of-in-cpp/
    if (std::ranges::any_of(primes, [&number](int p) {return number % p == 0;}))
        return false;
    return true;
}

int NumberTheory::getMultiplicativePersistence(int number) {
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

int NumberTheory::getCollatzNumber(int number) {
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

long double NumberTheory::fibonacciIndex(int number)
{
    // Number approximating the fibonacci index of a number
    return log(number * sqrt(5)) / log((1+sqrt(5))/2);
}


// FUNCTION
// Constructor
Function::Function(std::string input)
{
    Function::string = Utilities::removeWhiteSpace(std::move(input)) + ' ';
}

// Break up open addition and subtraction
std::vector<std::string> OpenLevel0Break(std::string func)
{
    func = Utilities::removeWhiteSpace(func) + '+';
    std::vector<std::string> openLevel0Functions;

    // Integer representing 'openness' -> the current char is not enclosed in parentheses
    int parensNum = 0;

    int preIndex;
    int firstIndex = 0;
    for (int index = 0; index < func.size(); index++)
    {
        // Check if a character is 'open'
        if (func[index] == '(')
            parensNum++;
        else if (func[index] == ')')
            parensNum--;

        // Char is 'open' (parensNum = 0)
        if (!parensNum)
        {
            if (func[index] == '+' || func[index] == '-')
            {
                // Adds previous chars
                std::string tempString;
                for (preIndex = firstIndex; preIndex < index; preIndex++)
                    tempString += func[preIndex];
                openLevel0Functions.push_back(tempString);
                firstIndex = preIndex;
            }
        }

    }
    return openLevel0Functions;
}

std::string Function::Derivative() const
{
    std::string func = Function::string;

    // Input Validation

    // Break up open level zero operations
    std::vector<std::string> level0Func = OpenLevel0Break(func);

    // Print each part
//    for (const auto & index : level0Func)
//        std::cout << index + '\n';

    return func;
}


// LATEX
// TODO: Raven-LATEX
std::vector<std::string> LaTeX::MakeNameList()
{
    // The final list to be returned
    std::vector<std::string> nameList;

    // Declares and defines input based on user, adds space at end to register last character as a new string
    std::string input;
    std::cout << "Enter your variables separated by a space: \n";
    // https://stackoverflow.com/questions/5838711/stdcin-input-with-spaces
    std::getline(std::cin, input );
    input += " "; // Adds space at end so the last character is added to nameList

    // Add each string seperated by a space to nameList
    std::string tempString;
    for (char c : input)
    {
        if (c == ' ')
        {
            nameList.push_back(tempString);
            tempString = ""; // Resets the temporary string
        }
        else
            tempString.push_back(c);
    }
    return nameList;
}
std::vector<std::string> MakeLogicExpressionList()
{
    // The final list to be returned
    std::vector<std::string> logicList;

    // Declares and defines input based on user, adds space at end to register last character as a new string
    std::string input;
    std::cout << "Enter your logic expressions separated by a space: \n";
    std::cout << "&& for and (conjuction)\n";
    std::cout << "|| for logical or (disjunction)\n";
    std::cout << "-> for conditional\n";
    std::cout << "<> for bijunction\n";
    // https://stackoverflow.com/questions/5838711/stdcin-input-with-spaces
    std::getline(std::cin, input );
    input += " "; // Adds space at end so the last character is added to logicList

    // Add each string seperated by a space to logicList
    std::string tempString;
    for (char c : input)
    {
        if (c == ' ')
        {
            logicList.push_back(tempString);
            tempString = ""; // Resets the temporary string
        }
        else
            tempString.push_back(c);
    }
    return logicList;
}

void LaTeX::GenerateLaTeXDocument()
{
    //https://www.w3schools.com/cpp/cpp_files.asp
    std::ofstream outputFile("LaTeXTable.tex");

    std::vector<std::string> packageList = {"amsmath", "fancyhdr"}; // use simpsons not working :(
    outputFile << GenerateLaTeXHeader(packageList);

    outputFile << "\\begin{document}\n";
    // Makes Truth Table
    std::vector<std::string> nameList = MakeNameList();
    std::vector<std::string> logicList = MakeLogicExpressionList();
    std::string truthTable = GenerateTruthTable(nameList, logicList);
    outputFile << truthTable;
    std::cout << "Truth table generated.";

    outputFile << "\\end{document}";
    outputFile.close();
}

std::string LaTeX::GenerateLaTeXHeader(const std::vector<std::string>& packageList)
{
    std::string header = "\\documentclass{article}\n";

    header += "\\usepackage{";
    for (int packageListIndex = 0; packageListIndex < packageList.size(); packageListIndex++)
    {
        if (packageListIndex != packageList.size() - 1) // If the current package is not the last in the list
            header += packageList[packageListIndex] + ", ";
        else                                            // If this is the last package
            header += packageList[packageListIndex] + "}\n";
    }

    header += "\\pagestyle{fancy}\n"
              "\\lhead{GeneratedTextDocument}\n"
              "\\rhead{Raven Suggs and Paul Cimarusti}\n";
    return header;
}

std::string LaTeX::GenerateTruthTable(std::vector<std::string> nameList, std::vector<std::string> logicList)
{
    std::string truthTable = "\\begin{center}\n"
                             "\t \\begin{tabular}";

    //Telling table how many columns it will have
    std::string columnsString = "{";
    for (int columnNumber = 0; columnNumber < nameList.size() + logicList.size(); columnNumber++)
    {
        if (columnNumber < nameList.size() + logicList.size() - 1)
            columnsString += "c | ";
        else
            columnsString += "c}\n";
    }
    truthTable +=  columnsString;

    std::string headerString;
    //Making Truth Table header
    //Variable names header
    for (int varIndex = 0; varIndex < nameList.size(); varIndex++)
    {
        //logicList.empty is to check if there are any logic statements to keep formatting correct
        if (varIndex < nameList.size() - 1 || !logicList.empty())
            headerString += "$" + nameList[varIndex] + "$ & ";
        else
            headerString += "$" + nameList[varIndex] + "$";
    }
    //Logical Expressions header
    if(!logicList.empty())
    {
        for (int logicIndex = 0; logicIndex < logicList.size(); logicIndex++)
        {
            if (logicIndex < logicList.size() - 1)
                headerString += "$" + logicList[logicIndex] + "$ & ";
            else
                headerString += "$" + logicList[logicIndex] + "$";
        }
    }
    truthTable += "\t \t" + headerString + " \\\\\n";

    //Making Truth Table body
    int columns = static_cast<int>(nameList.size());
    int rows = static_cast<int>(pow(2, columns));
    bool truth[columns][rows];
    //Fill truth values for each row
    for(int truthRow = 0; truthRow < rows; truthRow++)
    {

    }
    truthTable += "\t \\end{tabular}\n";
    truthTable += "\\end{center}\n";

    return truthTable;
}
