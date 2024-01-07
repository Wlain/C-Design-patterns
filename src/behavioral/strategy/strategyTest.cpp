//
// Created by william on 2024/1/7.
//

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
enum class Format
{
    Markdown,
    Html
};

struct ListStrategy
{
    virtual ~ListStrategy() = default;
    virtual void addListItem(std::ostringstream& oss, const std::string& item) {}
    virtual void start(std::ostringstream& oss) {}
    virtual void end(std::ostringstream& oss){};
};

struct MarkdownListStrategy : ListStrategy
{
    void addListItem(std::ostringstream& oss, const std::string& item) override
    {
        oss << " - " << item << std::endl;
    }
};

struct HtmlListStrategy : ListStrategy
{
    void start(std::ostringstream& oss) override { oss << "<ul>" << std::endl; }
    void end(std::ostringstream& oss) override { oss << "</ul>" << std::endl; }
    void addListItem(std::ostringstream& oss, const std::string& item) override
    {
        oss << "\t<li>" << item << "</li>" << std::endl;
    }
};

/// 动态策略
struct TextProcessor
{
    void clear()
    {
        m_oss.str("");
        m_oss.clear();
    }

    void appendList(const std::vector<std::string>& items)
    {
        m_listStrategy->start(m_oss);
        for (auto& item : items)
        {
            m_listStrategy->addListItem(m_oss, item);
        }
        m_listStrategy->end(m_oss);
    }

    void setOutputFormat(Format format)
    {
        switch (format)
        {
        case Format::Markdown:
            m_listStrategy = std::make_unique<MarkdownListStrategy>();
            break;
        case Format::Html:
            m_listStrategy = std::make_unique<HtmlListStrategy>();
            break;
        }
    }

    std::string str()
    {
        return m_oss.str();
    }

private:
    std::ostringstream m_oss;
    std::unique_ptr<ListStrategy> m_listStrategy;
};

/// 静态策略
template <typename LS>
struct TextProcessor2
{
    void appendList(const std::vector<std::string>& items)
    {
        m_listStrategy.start(m_oss);
        for (auto& item : items)
        {
            m_listStrategy.addListItem(m_oss, item);
        }
        m_listStrategy.end(m_oss);
    }

    std::string str()
    {
        return m_oss.str();
    }

private:
    std::ostringstream m_oss;
    LS m_listStrategy;
};

void strategyTest()
{
    TextProcessor tp;
    tp.setOutputFormat(Format::Markdown);
    tp.appendList({ "foo", "bar", "baz" });
    std::cout << tp.str() << std::endl;

    tp.clear();
    tp.setOutputFormat(Format::Html);
    tp.appendList({ "foo", "bar", "baz" });
    std::cout << tp.str() << std::endl;

    TextProcessor2<MarkdownListStrategy> tp1;
    tp1.appendList({ "foo", "bar", "baz" });
    std::cout << tp1.str() << std::endl;

    // html
    TextProcessor2<HtmlListStrategy> tp2;
    tp2.appendList({ "foo", "bar", "baz" });
    std::cout << tp2.str() << std::endl;
}