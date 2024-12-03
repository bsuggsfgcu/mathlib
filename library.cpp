// Coder/Developer: Cesar Fandino, Raven Suggs, & Paul Cimarusti
// Class:           COP 2006-80599, Fall 2024
// Date:            September 19, 2024
// Description:     C++ Math Library Program
// Log:             September 19, Project start
//                  September 20, Created isPrime function
//                  October 3, Started work on derivatives
//                  October 15, Created remove-whitespace function and tex file generation
//                  October 17, Set up truth table functions and tex header and variable names
//                  October 29, Split functions into different classes to help organize code
//                  November 12, Code cleaned up and mac-os to windows-os fixes, added tex /end statements to fix the tex file
//                  November 13, Set up truth table generation using binary, and set up taking user expressions and storing into a vector of strings to test using the truth table
//                  November 13, Derivatives draft work and input validation
//                  November 18, Set up saving truth table operation as variables
//                  December 2, Finished basic truth table with negation support and one operation
// Sources:         https://www.geeksforgeeks.org/stdstringinsert-in-c/
//                  https://www.scaler.com/topics/cpp/binary-representation-of-a-number/
//                  https://www.geeksforgeeks.org/tokenizing-a-string-cpp/
#include "library.h"
#include <regex>


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
        for (int i = 0; i < strNumber.length(); i++)
            product *= strNumber[i] - '0'; // - '0' converts a char to an int
        iterations ++;
        strNumber = std::to_string(product);
//        std::cout << product << ", " << iterations << "\n";
    } while (product > 9); // while product is not a single digit
    return iterations;
}

int NumberTheory::getCollatzNumber(int number)
{
    int collatzIterations = 0;
    // The collatz conjecture states that all numbers will reach one
    // when C(n) is applied recursively
    while (number != 1)
    {
        // If n is odd
        if (number % 2 == 1)
            number = number * 3 + 1;
        // if n is even
        else
            number /= 2;
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

std::map<std::string, std::string> OpenLevel1Break(std::string func)
{
    std::map<std::string, std::string> openLevel1Functions;

    int parensNum = 0;

    for (int index = 0; index < func.size(); index++)
    {
        if (func[index] == '(')
            parensNum++;
        else if (func[index] == ')')
            parensNum--;

        if (!parensNum)
        {
            if (func[index] == '*' || func[index] == '/')
            {
                std::string tempString;
            }
        }
    }


}

std::string Function::Derivative() const
{
    std::string func = Function::string;

    // Input Validation

    // Break up open level zero operations
    std::vector<std::string> level0Func = OpenLevel0Break(func);

    // Take out constants


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

    while (input.empty())
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
    std::cout << "! for negation\n";
    std::cout << "&& for and (conjuction)\n";
    std::cout << "|| for logical or (disjunction)\n";
    std::cout << "-> for conditional\n";
    std::cout << "<> for bijunction\n";
    // https://stackoverflow.com/questions/5838711/stdcin-input-with-spaces
    std::getline(std::cin, input );
    //Return early if user entered empty input, so that the return is an empty vector instead of a vector with one element which is an empty string "".
    if(input.empty())
    {
        return logicList;
    }
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
              "\\rhead{Raven Suggs, Paul Cimarusti, and Cesar Fandino}\n";
    return header;
}

std::string LogicToLaTeXFormat(std::string input, std::string &operation)
{
    std::string outputString = input;
    for(int stringIndex = 0; stringIndex < outputString.length(); stringIndex++)
    {
        switch(outputString[stringIndex]) {
            case '&':
                if(outputString[stringIndex + 1] == '&')
                {
                    outputString.erase(stringIndex, 2);
                    outputString.insert(stringIndex, "\\land ");
                    //stringIndex = stringIndex - 2;
                    operation = "&&";
                    //std::cout << operation << std::endl;
                    break;
                }
                //Adds escape character \ to the & sign since it would otherwise cause a compilation error
                if(outputString[stringIndex - 1] != '\\')
                {
                    outputString.insert(stringIndex - 1, "\\");
                    //stringIndex = stringIndex - 1;
                }
                break;
            case '-':
                if(outputString[stringIndex + 1] == '>')
                {
                    outputString.erase(stringIndex, 2);
                    outputString.insert(stringIndex, "\\rightarrow ");
                    //stringIndex = stringIndex - 2;
                    operation = "->";
                    //std::cout << operation << std::endl;
                    break;
                }
                break;
            case '|':
                if(outputString[stringIndex + 1] == '|')
                {
                    outputString.erase(stringIndex, 2);
                    outputString.insert(stringIndex, "\\lor ");
                    //stringIndex = stringIndex - 2;
                    operation = "||";
                    //std::cout << operation << std::endl;
                    break;
                }
                break;
            case '<':
                if(outputString[stringIndex + 1] == '>')
                {
                    outputString.erase(stringIndex, 2);
                    outputString.insert(stringIndex, "\\leftrightarrow ");
                    //stringIndex = stringIndex - 2;
                    operation = "<>";
                    //std::cout << operation << std::endl;
                    break;
                }
                break;
            //Don't save negation into operator since only one operation will work at a time in this solution method
            case '!':
                outputString.erase(stringIndex, 1);
                outputString.insert(stringIndex, "\\neg ");
                stringIndex = stringIndex - 1;
                //operation = "!";
                break;
            default:
                break;

        }
    }
    return outputString;
}

std::string TruthToLaTeXFormat(bool truth)
{
    if(truth)
        return "T";
    return "F";
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

    //Declaring string to hold user's operator
    std::string operation[logicList.size()];
    //Storing index of used variables in logic
    //Set to -1 by default to function as a null value
    int variable1[logicList.size()];
    std::fill(variable1, variable1+logicList.size(), -1);
    bool variable1Negated[logicList.size()];
    int variable2[logicList.size()];
    std::fill(variable2, variable2+logicList.size(), -1);
    bool variable2Negated[logicList.size()];
    //Logical Expressions header
    //Uses outside function to convert to a LaTeX friendly and prettier formatting
    //& is a key character for LaTeX so using it without a \ breaks compilation
    if(!logicList.empty())
    {
        //Looping through the logic expressions the user inputted and converting them to a LaTeX format, and saving them as variables to calculate with later
        for (int logicIndex = 0; logicIndex < logicList.size(); logicIndex++)
        {
            if (logicIndex < logicList.size() - 1)
                headerString += "$" + LogicToLaTeXFormat(logicList[logicIndex], operation[logicIndex]) + "$ & ";
            else
                headerString += "$" + LogicToLaTeXFormat(logicList[logicIndex], operation[logicIndex]) + "$";

            //Looping through entire string of a user inputted logic expression
            for(int stringIndex = 0; stringIndex < logicList[logicIndex].length(); stringIndex++)
            {
                //Repeat process for each variable in nameList
                for(int nameListIndex = 0; nameListIndex < nameList.size(); nameListIndex++)
                {
                    std::string variableName = nameList[nameListIndex];
                    if (logicList[logicIndex][stringIndex] == variableName[0])
                    {
                        //If the first character of the nameList variable name string name is found then it checks for the next characters to see if there is a complete match
                        bool matching = true;

                        //If the character we are looking at is not at index 0, checks the previous character to see if it is an !, which means that the variable is negated
                        bool negated = false;
                        if(stringIndex != 0)
                        {
                            if(logicList[logicIndex][stringIndex - 1] == '!')
                            {
                                negated = true;
                            }
                        }

                        //Keep looping until finding a <, |, &, which mark the expression, or until the end of the logic expression string
                        for(int variableIndex = 1; variableIndex + stringIndex < logicList[logicIndex].length() && !(logicList[logicIndex][stringIndex + variableIndex] == '&' || logicList[logicIndex][stringIndex + variableIndex] == '-' || logicList[logicIndex][stringIndex + variableIndex] == '|' || logicList[logicIndex][stringIndex + variableIndex] == '<') ; variableIndex++)
                        {
                            if(variableName[variableIndex] != logicList[logicIndex][stringIndex + variableIndex])
                            {
                                //If a not matching character is found then it ends the loop early and doesn't save the input as a variable to work with
                                matching = false;
                                break;
                            }
                        }
                        if(matching)
                        {
                            if(variable1[logicIndex] != -1)
                            {
                                variable2[logicIndex] = nameListIndex;
                                variable2Negated[logicIndex] = negated;
                                std::cout << variable2[logicIndex] << std::endl;
                            }
                            else
                            {
                                variable1[logicIndex] = nameListIndex;
                                variable1Negated[logicIndex] = negated;
                                std::cout << variable1[logicIndex] << std::endl;
                            }
                        }
                    }
                }
            }
        }
    }
    truthTable += "\t\t" + headerString + " \\\\\n";
    truthTable += "\t\t\\hline\n";


    //Making Truth Table body
    int columns = static_cast<int>(nameList.size() + logicList.size());
    int rows = static_cast<int>(pow(2, static_cast<int>(nameList.size())));
    bool truth[columns];
    for(int rowIndex = 0; rowIndex < rows; rowIndex++)
    {
        int binaryNumber = 0, remainder, rowNumber = rowIndex, digitPlace = 1;
        while(rowNumber != 0)
        {
            remainder = rowNumber % 2;

            rowNumber = rowNumber / 2;
            binaryNumber = binaryNumber + remainder * digitPlace;

            digitPlace = digitPlace * 10;
        }

        //Converting the binary representation into a string so that we can match its size to the columnIndex
        std::string binaryStr = std::to_string(binaryNumber);
        while(binaryStr.length() < nameList.size())
        {
            binaryStr.insert(binaryStr.begin(), '0');
        }
        //std::cout << binaryStr << std::endl;
        //Setting truth table column truth value to be false if the binary number has a 1 in its index
        for(int columnIndex = 0; columnIndex < nameList.size(); columnIndex++)
        {
            if(binaryStr[columnIndex] == '0')
            {
                truth[columnIndex] = true;
            }
            else
            {
                truth[columnIndex] = false;
            }
        }
        //Now we add the logic expressions for this row to the truth array
        //Need to find out how to read user input and use built-in boolean to handle
        //I think a good way to do it is to utilize the NamesList list and get the index of that variable when it is found in the logic expression input
        for(int columnIndex = columns - logicList.size(), logicIndex = 0; columnIndex < columns; columnIndex++, logicIndex++)
        {
            //Need to tokenize logic string, then use a shunting yard algorithm to parse logic
            // std::vector<std::string> tokenizedLogic();
            // Tokenize user input so that the shunting yard operation will work
            //Then Save truth value into the table to be printed out later
            //truth[columnIndex] = true;

            //Saving truth value into a different spot from the truth table so that it can be negated without changing the table
            bool truthvar1 = truth[variable1[logicIndex]];
            bool truthvar2 = truth[variable2[logicIndex]];
            if(variable1Negated[logicIndex])
            {
                truthvar1 = !truthvar1;
                std::cout << "var1 negated!" << std::endl;
            }
            if(variable2Negated[logicIndex])
            {
                truthvar2 = !truthvar2;
                std::cout << "var2 negated!" << std::endl;
            }

            switch(operation[logicIndex][0])
            {
                case '&':
                    if(operation[logicIndex][1] == '&')
                    {
                        truth[columnIndex] = truthvar1 && truthvar2;
                        break;
                    }
                case '-':
                    if(operation[logicIndex][1] == '>')
                    {
                        truth[columnIndex] = !truthvar1 || truthvar2;
                        break;
                    }
                    break;
                case '|':
                    if(operation[logicIndex][1] == '|')
                    {
                        truth[columnIndex] = truthvar1 || truthvar2;
                        break;
                    }
                    break;
                case '<':
                    if(operation[logicIndex][1] == '>')
                    {
                        truth[columnIndex] = (!truthvar1|| truthvar2) && (!truthvar2 || truthvar1);
                        break;
                    }
                    break;
                default:
                    break;
            }
        }

        //Finally print the completed row to the latex document with proper formatting
        std::string truthRowOut;
        for(int columnIndex = 0; columnIndex < columns; columnIndex++)
        {
            if (columnIndex < columns - 1)
                truthRowOut += "$" + TruthToLaTeXFormat(truth[columnIndex]) + "$ & ";
            else
                truthRowOut += "$" + TruthToLaTeXFormat(truth[columnIndex]) + "$";
        }
        truthTable += "\t \t" + truthRowOut + "\\\\\n";
    }
    truthTable += "\t \\end{tabular}\n";
    truthTable += "\\end{center}\n";

    return truthTable;
}
