// Hello-World.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC 
#include<stdlib.h>
#include<crtdbg.h>
#endif

#include "ClassDemo.h"
#include <iostream>

using namespace std;

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

    IInterfaceB* b = reinterpret_cast<IInterfaceB*>(a);
    if (b)
        b->BFunc(20);

    IInterfaceC* c = dynamic_cast<IInterfaceC*>(b);
    if (c)
        c->CFunc();

    MyClass* m = dynamic_cast<MyClass*>(c);
    if (m)
        printf("my class data is: %d\n", m->data());

    delete a;

    /*  FROM MSDN: 
        In general you use static_cast when you want to convert numeric data types such as enums to ints or ints to floats, and you are certain of the data types involved in the conversion. 
        static_cast conversions are not as safe as dynamic_cast conversions, because static_cast does no run-time type check, while dynamic_cast does. 
        A dynamic_cast to an ambiguous pointer will fail, while a static_cast returns as if nothing were wrong; this can be dangerous. 
        Although dynamic_cast conversions are safer, dynamic_cast only works on pointers or references, and the run-time type check is an overhead.
    */

    /*  some comments:
        Use static_cast. If you know that your Base* points to a Derived, then use static_cast. 
        dynamic_cast is useful for when it might point to a derived.
    */

    // test dyanmic_cast and static_cast
    MyParent* mp = new MyParent();
    MySon* sp = dynamic_cast<MySon*>(mp);
    if (!sp)
        cout << "dynamic_cast failed." << endl; 

    delete mp;

    mp =  new MySon();
    sp = static_cast<MySon*>(mp);   // both dynamic_cast and static_cast work here as mp is really the type of MySon
    if (sp)
        cout << "dynamic_cast succeeded." << endl; 
    delete sp;

    // 'parent': cann't instantiate abstrace class
    // parent* ppp =  new parent();



    int** aaa = My2DAlloc(2, 2); 
    free(aaa);

    wchar_t** t = Ac2DAlloc<wchar_t>(2, 256);
    wcscpy_s(t[0], 256, L"this is the one wchar_t.");
    wcscpy_s(t[1], 256, L"another wchar_t is copied.");

    _tprintf(L"output 2d Array t[0]: %s\n", t[0]);
    _tprintf(L"output 2d Array t[1]: %s\n", t[1]);

    // Disable this line of code to make a memory leak, so that we can catch it (in output window of visual studio)
    Ac2DFree<wchar_t>(t);

    // if you know where the program will exit or your program only has one exit point
    // you can use the following method to check the memory
//#ifdef _DEBUG
//    _CrtDumpMemoryLeaks();
//#endif

    // memcpy a struct
    TC tc1(1,2,3);
    TC tc2;

    memcpy_s(&tc2, sizeof(TC), &tc1, sizeof(TC));


    // test class demo
    parent* p = new children();
    p->process();
    delete p;

    system("pause");
	return 0;
}