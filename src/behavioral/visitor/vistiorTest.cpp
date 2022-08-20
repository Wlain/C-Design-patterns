//
// Created by william on 2022/8/19.
//
#include <iostream>
#include <list>
#include <variant>

// 基础结构
struct Document
{
    virtual void addToList(const std::string& line) = 0;
};
struct Markdown : Document
{
    void addToList(const std::string& line) { m_content.emplace_back(line); }
    std::string m_start = "* ";
    std::list<std::string> m_content;
};
struct Html : Document
{
    void addToList(const std::string& line) { m_content.emplace_back(line); }
    std::string m_start = "<li>";
    std::string m_end = "</li>";
    std::list<std::string> m_content;
};
// 需求如下： 我们需要对不同的文档加一个print方法，有很多种做法
// 做法一：
struct Document1
{
    virtual void addToList(const std::string& line) = 0;
    virtual void print() = 0;
};
struct Markdown1 : Document1
{
    void addToList(const std::string& line) { m_content.emplace_back(line); }
    void print() override
    {
        for (auto&& item : m_content)
        {
            std::cout << m_start << item << std::endl;
        }
    }
    std::string m_start = "* ";
    std::list<std::string> m_content;
};
struct Html1 : Document1
{
    void addToList(const std::string& line) { m_content.emplace_back(line); }
    void print() override
    {
        std::cout << "<ul>" << std::endl;
        for (auto&& item : m_content)
        {
            std::cout << "\t" << m_start << item << m_end << std::endl;
        }
        std::cout << "</ul>" << std::endl;
    }
    std::string m_start = "<li>";
    std::string m_end = "</li>";
    std::list<std::string> m_content;
};
// 做法一违反了一些 SOLID 原则, 如果你有20个类作为这个层次结构的一部分。
// 就需要进入20个不同的文件并为每个文件添加一种打印方法（不好）

void test1()
{
    Document1* d = new Html1();
    d->addToList("this is a html line");
    d->print();
}

// 做法二：
struct Document2
{
    virtual void addToList(const std::string& line) = 0;
};

struct Markdown2 : public Document2
{
    void addToList(const std::string& line) override
    {
        m_content.emplace_back(line);
    }
    std::string m_start = "* ";
    std::list<std::string> m_content;
};

struct Html2 : public Document2
{
    void addToList(const std::string& line) override
    {
        m_content.emplace_back(line);
    }
    std::string m_start = "<li>";
    std::string m_end = "</li>";
    std::list<std::string> m_content;
};

struct Document2Printer
{
    static void print(Document2* e)
    {
        if (auto md = dynamic_cast<Markdown2*>(e))
        {
            for (auto&& item : md->m_content)
            {
                std::cout << md->m_start << item << std::endl;
            }
        }
        else if (auto hd = dynamic_cast<Html2*>(e))
        {
            std::cout << "<ul>" << std::endl;
            for (auto&& item : hd->m_content)
            {
                std::cout << "\t" << hd->m_start << item << hd->m_end << std::endl;
            }
            std::cout << "</ul>" << std::endl;
        }
        // 如果业务越来越复杂，将会引入一堆if/else if
    }
};
void test2()
{
    Document2* hd = new Html2();
    hd->addToList("this is a html line");
    Document2Printer::print(hd);
    Document2* md = new Markdown2();
    md->addToList("this is markDown line");
    Document2Printer::print(md);
}

// 做法二不是一种有效扩展的方法，特别是当你扩展您正在处理的类集时，
// 最终会得到一长串的清单，并在RTTI，if/else-if上支付性能成本。

// 做法三，引入访问者模式：
struct DocumentVisitor
{
    virtual void visit(class Markdown3*) = 0;
    virtual void visit(class Html3*) = 0;
};

struct DocumentPrinter : DocumentVisitor
{
    void visit(class Markdown3* md) override;
    void visit(class Html3* hd) override;
};

struct Document3
{
    virtual void addToList(const std::string& line) = 0;
    virtual void visit(DocumentVisitor*) = 0;
};

struct Markdown3 : Document3
{
    void addToList(const std::string& line) { m_content.emplace_back(line); }
    void visit(DocumentVisitor* dv) { dv->visit(this); }
    std::string m_start = "* ";
    std::list<std::string> m_content;
};

struct Html3 : Document3
{
    void addToList(const std::string& line) { m_content.push_back(line); }
    void visit(DocumentVisitor* dv) { dv->visit(this); }
    std::string m_start = "<li>";
    std::string m_end = "</li>";
    std::list<std::string> m_content;
};

void DocumentPrinter::visit(struct Markdown3* md)
{
    for (auto&& item : md->m_content)
    {
        std::cout << md->m_start << item << std::endl;
    }
}

void DocumentPrinter::visit(struct Html3* hd)
{
    std::cout << "<ul>" << std::endl;
    for (auto&& item : hd->m_content)
    {
        std::cout << "\t" << hd->m_start << item << hd->m_end << std::endl;
    }
    std::cout << "</ul>" << std::endl;
}

void test3()
{
    Document3* d = new Html3();
    d->addToList("this is a html line");
    std::shared_ptr<DocumentPrinter> printer = std::make_shared<DocumentPrinter>();
    d->visit(printer.get());
}

// 做法三不违反单一职责和开闭原则，的情况下达成了需求

// 现代C++中的访问者模式
struct DocumentPrinter4
{
    void operator()(Markdown& md)
    {
        for (auto&& item : md.m_content)
        {
            std::cout << md.m_start << item << std::endl;
        }
    }
    void operator()(Html& hd)
    {
        std::cout << "<ul>" << std::endl;
        for (auto&& item : hd.m_content)
        {
            std::cout << "\t" << hd.m_start << item << hd.m_end << std::endl;
        }
        std::cout << "</ul>" << std::endl;
    }
};

struct DocumentScanner4
{
    void operator()(Markdown& md)
    {
        std::cout << "Markdown scan func called" << std::endl;
    }
    void operator()(Html& md)
    {
        std::cout << "Html scan func called" << std::endl;
    }
};
using document = std::variant<Markdown, Html>;

void text4()
{
    Html hd;
    hd.addToList("This is line");
    document d = hd;
    DocumentPrinter4 dp;
    std::visit(dp, d);
    DocumentScanner4 ds;
    std::visit(ds, d);
}

void visitorTest()
{
    test1();
    std::cout << "====================" << std::endl;
    test2();
    std::cout << "====================" << std::endl;
    test3();
    std::cout << "====================" << std::endl;
    text4();
}