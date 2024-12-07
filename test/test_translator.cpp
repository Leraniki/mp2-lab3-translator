#include "translator.h"
#include <iostream>
#include <gtest.h>


TEST(TranslatorTest, Parentheses) {
    Translator<int> translator("(2 + 3) * 4");
    ASSERT_EQ(translator.get_postfix(), "2 3 + 4 *");
}

TEST(TranslatorTest, CalculateComplexExpression) {
    Translator<double> translator("2 * (3 + 4) / 5 - 1");
    std::map<char, double> variables;
    ASSERT_DOUBLE_EQ(translator.calculate(variables), 1.8);
} 
TEST(TranslatorTest, CalculateComplexExpression2) {
    Translator<double> translator("1.2 + 2.3");
    std::map<char, double> variables;
    ASSERT_DOUBLE_EQ(translator.calculate(variables), 3.5);
}

TEST(TranslatorTest, UnaryMinus) {
    Translator<double> translator("-2 + 3");
    std::map<char, double> variables;
    ASSERT_DOUBLE_EQ(translator.calculate(variables), 1.0);
}

TEST(TranslatorTest, NoCloseSkob) {
    ASSERT_ANY_THROW(Translator<double>("(2 + 3"));
}

TEST(TranslatorTest, NoCloseSkob_2) {
    ASSERT_ANY_THROW(Translator<double>("2 + 3)"));
}

