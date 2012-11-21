

#include <iostream>

using namespace std;

///
///
///
class parent
{
public:
    virtual void process() = 0;

    virtual ~parent() = 0;
};

// 1. defined parent to abstract class, 
// 2. but this abstract will be inherited by sub class, so we need to define a destructor
// 3. so define a pure virtual destructor
// 4. in order to make it work, we need to add the following code - pure virtual destructor definition
parent::~parent(){};    // definition of pure virtual destructor

class children : public parent
{

public:
    children() : m(0)
    {}

    virtual ~children()
    {
        m = 0;
    }


    virtual void process()
    {
        m++;
    }

private:
    int m;
};

class IInterfaceA
{
public:
    virtual void AFunc(int a) = 0;
    virtual ~IInterfaceA() = 0;
};
IInterfaceA::~IInterfaceA() {};

class IInterfaceB
{
public:
    virtual int BFunc(int b) = 0;
};

class IInterfaceC
{
public:
    virtual void CFunc(void) = 0;
};

class MyClass : public IInterfaceA, public IInterfaceB, public IInterfaceC
{
private:
    int m_data;
public:
    MyClass() : m_data(0) {}
    virtual ~MyClass()
    {
        m_data = 0;
    }


    virtual void AFunc(int a)
    {
        m_data += a;
        printf("AFunc::my class data is: %d\n", m_data);
    }

    virtual int BFunc(int b)
    {
        m_data -= b;
        printf("BFunc::my class data is: %d\n", m_data);
        return m_data;
    }

    virtual void CFunc(void)
    {
        m_data++;
        printf("CFunc::my class data is: %d\n", m_data);
    }

    int data()
    {
        return m_data;
    }
};

class MyParent
{
public:
    MyParent() : p(0) {};
    virtual ~MyParent() {};

    virtual void process()
    {
        p++;
        cout << L"MyParent::process: " << p << endl;
    }

private:
    int p;
};

class MySon : public MyParent
{
private:
    int s;

public:
    MySon() : s(0) {};
    virtual ~MySon() {};

    virtual void process()
    {
        s++;
        cout << L"MyParent::process: " << s << endl;
    }
};