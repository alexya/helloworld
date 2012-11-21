// Hello-World.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC 
#include<stdlib.h>
#include<crtdbg.h>
#endif

class IInterfaceA
{
public:
    virtual void AFunc(int a) = 0;
};

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

int** My2DAlloc(int rows, int cols) 
{
    int header = rows * sizeof(int*);
    int data = rows * cols * sizeof(int);
    int** rowptr = (int**)malloc(header + data);
    int* buf = (int*)(rowptr + rows);

    for (int k = 0; k < rows; ++k) 
    {
        rowptr[k] = buf + k*cols;
    }
    return rowptr;
}

template<typename T>
T** Ac2DAlloc(int rows, int cols) 
{
    int header = rows * sizeof(T*);
    int data = rows * cols * sizeof(T);
    T** rowptr = (T**)malloc(header + data);
    T* buf = (T*)(rowptr + rows);

    for (int k = 0; k < rows; ++k) 
    {
        rowptr[k] = buf + k*cols;
    }

    return rowptr;
}

template<typename T>
void Ac2DFree(T** ptr)
{
    if (NULL != ptr)
        free(ptr);

    ptr = NULL;
}

struct TC
{
    TC()
    {
        x = y = z = 0;
    }

    TC(int a, int b, int c) : x(a), y(b), z(c)
    {}

    int sum()
    {
        return x + y + z;
    }

    int x;
    int y;
    int z;
};


int _tmain(int argc, _TCHAR* argv[])
{
    // If your program has several exit points, please add the following statement
    // when the program exits, the memory check will be executed automatically.
#ifdef _DEBUG
    _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

    IInterfaceA* a = new MyClass();
    a->AFunc(10);

    IInterfaceB* b = dynamic_cast<IInterfaceB*>(a);
    if (b)
        b->BFunc(20);

    IInterfaceC* c = dynamic_cast<IInterfaceC*>(b);
    if (c)
        c->CFunc();

    MyClass* m = dynamic_cast<MyClass*>(c);
    if (m)
        printf("my class data is: %d\n", m->data());

    delete a;

    int** aaa = My2DAlloc(2, 2); 
    free(aaa);

    wchar_t** t = Ac2DAlloc<wchar_t>(2, 256);
    wcscpy_s(t[0], 256, L"this is the one wchar_t.");
    wcscpy_s(t[1], 256, L"another wchar_t is copied.");

    _tprintf(L"output 2d Array t[0]: %s\n", t[0]);
    _tprintf(L"output 2d Array t[1]: %s\n", t[1]);

    // !Disable this line of code to make a memory leak, so that we can catch it (in output window of visual studio)
    Ac2DFree<wchar_t>(t);

    // if you know where the program will exit or your program only has one exit point
    // you can use the following method to check the memory
//#ifdef _DEBUG
//    _CrtDumpMemoryLeaks();
//#endif

    TC tc1(1,2,3);
    TC tc2;

    memcpy_s(&tc2, sizeof(TC), &tc1, sizeof(TC));


    system("pause");
	return 0;
}