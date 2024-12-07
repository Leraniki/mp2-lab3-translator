#ifndef __Translator_H__
#define __Translator_H__

#include <iostream>
#include "stack.h"
#include <cctype>
#include <sstream>
#include <stdexcept>
#include <map>
#include <string>
#include <algorithm> 

using namespace std;

template <typename T>
class Translator {
protected:
    string postfix;
    string infix;
    map<char, int> priority = { {'(', 0}, {')', 0}, {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2} };

    enum class State {
        START,
        OPERAND,
        OPERATOR,
        LPAREN,
        RPAREN
    };

public:
    Translator(string infix) : infix(infix) {
        to_postfix();
    }

    void to_postfix() {
        int openParenthesesCount = 0;
        Stack<char> operators;
        State state = State::START;
        std::string cleanInfix;

        for (char c : infix) {
            if (c != ' ') {
                cleanInfix += c;
            }
        }

        for (size_t i = 0; i < cleanInfix.length(); ++i) {
            char c = cleanInfix[i];

            switch (state) {
            case State::START:
            case State::OPERAND:
                if (isalnum(c) || c == '.') {
                    
                    postfix += c;
                    state = State::OPERAND;
                    
                }
                else {
                    if (postfix.length() > 0 && postfix.back() != ' ') {
                        postfix += ' ';
                    }
                    if (c == '(') {
                        operators.push(c);
                        openParenthesesCount++;
                    }
                    else if (string("+-*/").find(c) != string::npos) {
                        while (!operators.empty() && operators.top() != '(' && priority[c] <= priority[operators.top()]) {
                            postfix += operators.top();
                            postfix += ' ';
                            operators.pop();
                        }
                        operators.push(c);
                    }
                    else if (c == ')') {
                        while (!operators.empty() && operators.top() != '(') {
                            postfix += operators.top();
                            postfix += ' ';
                            operators.pop();
                        }
                        if (operators.empty()) {
                            throw 1;
                        }
                        operators.pop();
                        openParenthesesCount--;

                    }
                    else {
                        throw 1;
                    }

                    state = (c == '(') ? State::LPAREN : State::OPERATOR; 
                }
                break;

            case State::OPERATOR:
                if (isalnum(c) || c == '.') {
                    postfix += c;
                    state = State::OPERAND;
                }
                else {
                    if (postfix.length() > 0 && postfix.back() != ' ') {
                        postfix += ' ';
                    }
                    if (c == '(') {
                        operators.push(c);
                        openParenthesesCount++;

                    }
                    else if (string("+-*/").find(c) != string::npos) {
                        while (!operators.empty() && operators.top() != '(' && priority[c] <= priority[operators.top()]) {
                            postfix += operators.top();
                            postfix += ' ';
                            operators.pop();
                        }
                        operators.push(c);
                    }
                    else if (c == ')') {
                        while (!operators.empty() && operators.top() != '(') {
                            postfix += operators.top();
                            postfix += ' ';
                            operators.pop();
                        }
                        if (operators.empty()) {
                            throw 1;
                        }
                        operators.pop();
                        openParenthesesCount--;

                    }
                    else {
                        throw 1;
                    }
                    state = (c == '(') ? State::LPAREN : State::OPERATOR; 
                }
                break;

            case State::LPAREN:
                if (isalnum(c) || c == '.') {
                    postfix += c;
                    state = State::OPERAND;
                }
                else if (c == '(') {
                    operators.push(c);
                    openParenthesesCount++;
                }
                else if (string("+-*/").find(c) != string::npos) {
                    operators.push(c);
                    state = State::OPERATOR; 
                }
                else {
                    throw 1;
                }
                break;

            }
        }


        while (!operators.empty()) {
            if (postfix.back() != ' ') { 
                postfix += ' ';
            }
            postfix += operators.top();
            operators.pop();
        }


        if (openParenthesesCount != 0) {
            throw 1;
        }
    }


    string get_infix() const { return infix; }
    string get_postfix() const { return postfix; }

    double calculate(const std::map<char, double>& val) {
        Stack<double> operands;
        std::stringstream ss(postfix);
        std::string token;

        while (ss >> token) {
            if (isdigit(token[0]) || token[0] == '.') {
                try {
                    operands.push(stod(token));
                }
                catch (const std::invalid_argument& e) {
                    throw 1;
                }
            }
            else if (token.length() == 1 && (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/')) {
                if (token[0] == '+' || token[0] == '-') { 
                    if (operands.size() == 1 && (ss.peek() == EOF || !isalnum(ss.peek()))) { 
                        double op = operands.top();
                        operands.pop();
                        operands.push(calc_unar_operations(op, token[0]));
                    }
                    else if (operands.size() >= 2) { // Бинарный оператор
                        double op2 = operands.top(); operands.pop();
                        double op1 = operands.top(); operands.pop();
                        operands.push(calc_operations(op1, op2, token[0]));
                    }
                    else {
                        throw 1;
                    }

                }
                else { 
                    if (operands.size() < 2) {
                        throw 1;
                    }
                    double op2 = operands.top(); operands.pop();
                    double op1 = operands.top(); operands.pop();
                    try {
                        operands.push(calc_operations(op1, op2, token[0]));
                    }
                    catch (const std::runtime_error& e) {
                        throw;
                    }
                }
            }
            else {
                throw 1;
            }

        }

        if (operands.size() != 1) {
            throw 1;
        }
        return operands.top();
    }


    double calc_operations(double operand1, double operand2, char operation) {
        switch (operation) {
        case '+': return operand1 + operand2;
        case '-': return operand1 - operand2;
        case '*': return operand1 * operand2;
        case '/':
            if (operand2 == 0) throw 1;
            return operand1 / operand2;
        default: throw 1;
        }
    }

    double calc_unar_operations(double operand1, char operation) { // Для унарных операторов
        switch (operation) {
        case '+': return +operand1; 
        case '-': return -operand1;
        default: throw 1;
        }
    }
};

#endif