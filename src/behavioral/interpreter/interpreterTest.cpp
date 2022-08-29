//
// Created by william on 2022/8/29.
//
#include <iostream>
#include <string>
#include <vector>

namespace
{
struct Token
{
    enum type
    {
        integer,
        plus,
        minus,
        lparen,
        rparen
    };

    Token(type type, const std::string& txt) :
        m_type(type), m_text(txt)
    {
    }
    friend std::ostream& operator<<(std::ostream& os, const Token& o)
    {
        return os << "`" << o.m_text << "`";
    }
    type m_type;
    std::string m_text;
};

// parsed->eval()多态重载将被递归调用,表达式的评估发生在自下而上的方法中
std::vector<Token> lex(const std::string& input)
{
    std::vector<Token> result;
    for (auto curr = std::begin(input); curr != std::end(input); ++curr)
    {
        switch (*curr)
        {
        case '+':
            result.emplace_back(Token::plus, "+");
            break;
        case '-':
            result.emplace_back(Token::minus, "-");
            break;
        case '(':
            result.emplace_back(Token::lparen, "(");
            break;
        case ')':
            result.emplace_back(Token::rparen, ")");
            break;
        default: // number
            auto firstNotDigit = std::find_if(curr, end(input), [](auto c) {
                return !isdigit(c);
            });
            std::string integer = std::string(curr, firstNotDigit);
            result.emplace_back(Token::integer, integer);
            curr = --firstNotDigit;
            break;
        }
    }
    return result;
}

void test()
{
    auto tokens = lex("(13-4)-(12+1)");
    for (auto& t : tokens)
        std::cout << t << " "; // Output: `(` `13` `-` `4` `)` `-` `(` `12` `+` `1` `)`
    std::cout << std::endl;
}

struct Element
{
    virtual int eval() const = 0;
};

struct Integer : Element
{
    int m_value;
    explicit Integer(int v) :
        m_value(v) {}
    int eval() const override
    {
        return m_value;
    }
};

// 二叉树
struct BinaryOperation : Element
{
    enum Type
    {
        addition,
        subtraction

    };
    int eval() const override
    {
        if (m_type == addition) return m_lhs->eval() + m_rhs->eval();
        return m_lhs->eval() - m_rhs->eval();
    }
    Type m_type;
    std::shared_ptr<Element> m_lhs, m_rhs; // 左子树，右子树
};

std::shared_ptr<Element> parse(const std::vector<Token>& tokens)
{
    auto result = std::make_unique<BinaryOperation>();
    for (auto currToken = std::begin(tokens); currToken != std::end(tokens); ++currToken)
    {
        switch (currToken->m_type)
        {
        /// 正常表达式:即 13-4 很容易被 switch 语句的第三种情况Token::plus&Token::minus解析Token::integer
        case Token::integer:
            if (!result->m_lhs)
                result->m_lhs = std::make_shared<Integer>(stoi(currToken->m_text));
            else
                result->m_rhs = std::make_shared<Integer>(stoi(currToken->m_text));
            break;
        case Token::plus:
            result->m_type = BinaryOperation::addition;
            break;
        case Token::minus:
            result->m_type = BinaryOperation::subtraction;
            break;
        /// 子表达式:即从括号开始的表达式,例如，(13-4)我在括号中提取内容并再次将其提供给它，parse()因为这是一个反复出现的问题。
        case Token::lparen:
            auto rparen = std::find_if(currToken, std::end(tokens), [](auto& token) {
                return token.m_type == Token::rparen;
            });
            std::vector<Token> subexpression(currToken + 1, rparen);
            if (!result->m_lhs)
                result->m_lhs = parse(subexpression);
            else
                result->m_rhs = parse(subexpression);
            currToken = rparen;
            break;
        }
    }
    return result;
}

void parseTest()
{
    std::string expression{ "(13-4)-(12+1)" };
    auto tokens = lex(expression);
    auto parsed = parse(tokens);
    std::cout << expression << " = " << parsed->eval() << std::endl; // Output: (13-4)-(12+1) = -4
}

} // namespace

void interpreterTest()
{
    test();
    parseTest();
}