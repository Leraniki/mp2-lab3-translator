#include <gtest.h>
#include "translator.h"
#include <iostream>
#include <string>
#include <map>

int main(int argc, char **argv)
{
    string infixExpression;
    map<char, double> variables;

    std::cout << "Welcome to my translator. You can use the following operations:\n+\n-\n*\n/\nunary -\nunary +\n" << std::endl;
    while (true) {
        cout << "Enter expression to calculate or q to exit: ";
        getline(cin, infixExpression);

        if (infixExpression == "q") {
            break;
        }

        try {
            Translator<double> translator(infixExpression);
            double result = translator.calculate(variables);
            cout << "Result: " << result << endl;
        }
        catch (const runtime_error& error) {
            cerr << "Îøèáêà: " << error.what() << endl;
        }
    }

   
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
