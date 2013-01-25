

#include <iostream>

using namespace std;


class absCC
{
public:
    virtual void p() = 0;   // as long as there is a pure virtual function, the class will be abstract class, and cannot instantiate.
    virtual void p2() 
    {
        m++;        
    }

private:
    int m;

};

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

class abstraceA
{
public:
    virtual void Func1() = 0;
    virtual ~abstraceA();
};

abstraceA::~abstraceA() {};

class KA : public abstraceA
{
public:
    KA()
    {
        i = -1;
    }

    KA(int ai)
    {
        i = ai;
    }

    virtual void Func1()
    {

    }

    virtual ~KA()
    {
         i = 0;
    }

private:
    int i;
};

class KAA : public KA
{
public:
    KAA() : KA(-2)
    {
        
        v = -1;
    }

    virtual ~KAA()
    {
        v= 0;
    }

private :
    int v;
};

class IInterfaceA
{
public:
    virtual void AFunc(int a) = 0;
    virtual ~IInterfaceA() = 0 {};  // pure virtual destructor, IInterfaceA is also abstrace class
};

class IInterfaceB
{
public:
    virtual int BFunc(int b) = 0;
    virtual ~IInterfaceB() = 0 {};
};

class IInterfaceC
{
public:
    virtual void CFunc(void) = 0;
    virtual ~IInterfaceC() = 0 {};
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

class c1
{
public:
    virtual void p() = 0;
    //virtual ~c1() = 0 {};
};

class c2 : public c1
{
public:
    virtual ~c2() {};

};

class c3 : public c2
{
public:
    virtual void p()
    {
        m++;
    }

    virtual ~c3()
    {
        m = 0;
    }

private:
    int m;
};

template <typename T > 
struct is_a_ptr 
{ 
    enum{ yes = FALSE }; 
}; 
template <typename T > 
struct is_a_ptr <T* > 
{ 
    enum{ yes = TRUE }; 
}; 

template <typename T>
inline void UnusedVar(const T&)
{
    if(is_a_ptr<T>::yes)
        printf("Type T is a pointer!\r\n");
    else
        printf("Type T is *NOT* a pointer!\r\n");
}

class CalcSequenceNumber
{
private:
    static void print(int values[], int n)
    {
        for (int i = 0; i < n; ++i) // n may be less then length of values[]
        {
            cout << " " << values[i];
        }
        cout << endl;
    }

    static void decompose(int x, int values[], int index) 
    {
        if(x == 0) 
        {
            print(values, index);
            return ;
        }

        // this algorithm is similar to permutation, charge coin, etc.
        for (int i = 1; i < x; i++) 
        {
            values[index] = i;
            decompose(x - i, values, index + 1);
        }

        // special case for non-zero component
        if (index > 0)  // when i >= x, we need to fill the next number to make (previous numbers + next number == input number)
        {
            values[index] = x;
            decompose(0, values, index + 1);
        }
    }


public:
    static void decompose(int x) 
    {
        cout << "The input number is " << x << " :" << endl;

        int* values = new int[x];
        decompose(x, values, 0);
        delete[] values;
    }
};


/*

public class DecomposeNumber 
{

    private static void print(int[] values, int n) 
    {
        for (int i = 0; i < n; i++) {
            System.out.print(" "+values[i]);
        }
        System.out.println();
    }

    private static void decompose(int x, int[] values, int index) 
    {
        if(x == 0) {
            print(values, index);
            return ;
        }

        for (int i = 1; i < x; i++) {
            values[index] = i;
            decompose(x - i, values, index + 1);
        }

        // special case for non-zero component
        if (index > 0) 
        {
            values[index] = x;
            decompose(0, values, index + 1);
        }
    }

    public static void decompose(int x) 
    {
        int[] values = new int[x];
        decompose(x, values, 0);
    }

    public static void main(String[] args) 
    {
        int x = 5;
        decompose(x);
    }
}

Answer for x = 5:
1 1 1 1 1
1 1 1 2
1 1 2 1
1 1 3
1 2 1 1
1 2 2
1 3 1
1 4
2 1 1 1
2 1 2
2 2 1
2 3
3 1 1
3 2
4 1

*/
