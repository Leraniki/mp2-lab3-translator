#ifndef __Translator_H__
#define __Translator_H__

#include <iostream>
#include "stack.h" 
#include <cctype>
#include <sstream>
#include <stdexcept>
#include <map>
#include <string>
#include <vector>

using namespace std;

template <typename T>
class Translator {
protected:
    string postfix;
    string infix;
    map<char, int> priority = { {'(', 0}, {')', 0}, {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2} };

    enum class TokenType {
        OPERAND,
        OPERATOR,
        LPAREN,
        RPAREN
    };

    struct Token {
        TokenType type;
        string value;
    };

public:
    Translator(string infix) : infix(infix) {
        to_postfix();
    }

    vector<Token> parse() {
        vector<Token> tokens;
        string current_number;

        for (size_t i = 0; i < infix.length(); ++i) {
            char c = infix[i];
            if (isspace(c)) continue;

            if (isdigit(c) || c == '.') {
                current_number += c; 
            }
            else {
                if (!current_number.empty()) {
                    tokens.push_back({ TokenType::OPERAND, current_number });
                    current_number = "";
                }

                if (c == '(') {
                    tokens.push_back({ TokenType::LPAREN, "(" });
                }
                else if (c == ')') {
                    tokens.push_back({ TokenType::RPAREN, ")" });
                }
                else if (c == '-') {
                    
                    int minus_count = 1;
                    while (i + 1 < infix.length() && infix[i + 1] == '-') {
                        ++minus_count;
                        ++i;
                    }

                    if (tokens.empty() || tokens.back().type != TokenType::OPERAND && tokens.back().value != ")") {
                        tokens.push_back({ TokenType::OPERAND, "0" });
                    }

                    if (minus_count % 2 == 0) {
                        tokens.push_back({ TokenType::OPERATOR, "+" });
                    }
                    else {
                        tokens.push_back({ TokenType::OPERATOR, "-" }); 
                    }
                }
                else if (string("+-*/").find(c) != string::npos) {
                    tokens.push_back({ TokenType::OPERATOR, string(1, c) });
                }
                else {
                    throw 1; 
                }
            }
        }

        if (!current_number.empty()) {
            tokens.push_back({ TokenType::OPERAND, current_number });
        }

        return tokens;
    }


    void to_postfix() {
        Stack<Token> operators;
        vector<Token> tokens = parse();


        for (const auto& token : tokens) {
            if (token.type == TokenType::OPERAND) {
                postfix += token.value + " ";
            } else if (token.type == TokenType::LPAREN) {
                operators.push(token);
            } else if (token.type == TokenType::RPAREN) {
                while (!operators.empty() && operators.top().type != TokenType::LPAREN) {
                    postfix += operators.top().value + " ";
                    operators.pop();
                }
                if(operators.empty()){
                    throw 1;
                }
                operators.pop(); 
            } else if (token.type == TokenType::OPERATOR) {
                while (!operators.empty() && operators.top().type != TokenType::LPAREN && priority[token.value[0]] <= priority[operators.top().value[0]]) {
                    postfix += operators.top().value + " ";
                    operators.pop();
                }
                operators.push(token);
            }
        }

        while (!operators.empty()) {
            if (operators.top().type == TokenType::LPAREN) {
                throw 1; 
            }
             postfix += operators.top().value + " ";
             operators.pop();
        }

        if (!postfix.empty()) {
            postfix.pop_back(); 
        }
    }


    string get_infix() const { return infix; }
    string get_postfix() const { return postfix; }

    double calculate(const std::map<char, double>& val) { 
        Stack<double> operands;
        stringstream ss(postfix);
        string token;

        while (ss >> token) {
            if (isdigit(token[0]) || token[0] == '.') {
                try {
                    operands.push(stod(token));
                } catch (const std::invalid_argument& e) {
                    throw 1; 
                }
            } else if (string("+-*/").find(token[0]) != string::npos) {
                if (operands.size() < 2) {
                     throw 1; 
                }
                double op2 = operands.top(); operands.pop();
                double op1 = operands.top(); operands.pop();
                 try {
                    operands.push(calc_operations(op1, op2, token[0]));
                } catch (const std::runtime_error& e) {
                     throw ; 
                }
            } else {
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
            if (operand2 == 0) throw "Division by zero";
            return operand1 / operand2;
        default: throw "Invalid operator";
        }
    }
};

#endif