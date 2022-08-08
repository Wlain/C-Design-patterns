//
// Created by william on 2022/8/8.
//
#include "sampleBuilder.h"

#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

// 使用 C++创建HTML生成器
// 虽然这是一个很好的方法，但它可能会使对象表示复杂化。
void withoutBuilder()
{
    auto test = "hello";
    std::string output;
    output += "<p>";
    output += test;
    output += "</p>";
    std::cout << "</p>" << test << "</p>";

    // <ul><li>hello</li><li>world</li></ul>
    std::vector<std::string> words = { "hello", "world" };
    std::ostringstream oss;
    oss << "<ul>";
    for (auto& w : words)
    {
        oss << "</li>" << w << "</li>";
    }
    oss << "</ul>" << std::endl;
    std::cout << oss.str();
}

// indent：缩进
class HtmlBuilder;
class HtmlElement
{
public:
    std::string str(int32_t indent = 0)
    {
        std::ostringstream oss;
        oss << std::string(m_indentSize * indent, ' ') << "<" << m_name << ">" << std::endl;
        if (!m_text.empty())
        {
            oss << std::string(m_indentSize * (indent + 1), ' ') << m_text << std::endl;
        }
        for (auto& element : m_children)
        {
            oss << element.str(indent + 1);
        }
        oss << std::string(m_indentSize * indent, ' ') << "</" << m_name << ">" << std::endl;
        return oss.str();
    }

    static std::unique_ptr<HtmlBuilder> build(std::string rootName)
    {
        return std::make_unique<HtmlBuilder>(std::move(rootName));
    }

private:
    HtmlElement() = default;
    HtmlElement(std::string name, std::string text) :
        m_name(std::move(name)), m_text(std::move(text)) {}

private:
    std::string m_name;
    std::string m_text;
    std::vector<HtmlElement> m_children;
    constexpr static size_t m_indentSize = 4;
    friend HtmlBuilder;
};

class HtmlBuilder
{
public:
    explicit HtmlBuilder(std::string rootName)
    {
        m_root.m_name = std::move(rootName);
    }

    HtmlBuilder* addChild(std::string name, std::string text)
    {
        m_root.m_children.emplace_back(HtmlElement{ std::move(name), std::move(text) });
        return this;
    }
    std::string str() { return m_root.str(); }
    explicit operator HtmlElement() { return m_root; }

private:
    HtmlElement m_root;
};

// Builder 提供了一个 API 用于逐步构建对象，而不会显示实际的对象表示
void withBuilder()
{
    auto builder = HtmlElement::build("ul");
    builder->addChild("li", "hello")->addChild("li", "world");
    std::cout << builder->str() << std::endl;
}

void builderTest()
{
    Sample sample = Sample::create("william")
                      .lives()
                      .at("LaiGuangYing Road")
                      .withPostCode("364401")
                      .works()
                      .withCompany("Bank")
                      .withPosition("Engineer")
                      .earning("10e6");
    std::cout << sample << std::endl;
}

// 以上lives，works方法会被编译器优化

void builderPatternTest()
{
    withoutBuilder();
    withBuilder();
    builderTest();
}