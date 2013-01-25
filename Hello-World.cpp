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
#include <vector>

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

template <typename T>
inline void UnusedVar(const T&);


int optimal_trades(int *prices, int n_prices, int N)
{
    int i, j, n;
    int **arr;
    int max_profit;
    arr = (int **)malloc(n_prices * sizeof(int**));
    for (i = 0; i < n_prices; ++i) {
        arr[i] = (int *)malloc((N+1)*sizeof(int));
        memset(arr[i], 0, (N+1)*sizeof(int));
    }
    arr[n_prices][N];


    for (n = 1; n <= N; ++n) {
        for (i = n_prices - 1; i >= 0; --i) {
            for (j = i + 1; j < n_prices; ++j) {
                if (arr[i][n] < prices[j] - prices[i]) {
                    arr[i][n] = prices[j] - prices[i];
                }
                if (arr[i][n] < prices[j] - prices[i] + arr[j][n-1]) {
                    arr[i][n] = prices[j] - prices[i] + arr[j][n-1];
                }
            }
        }
    }



    max_profit = arr[0][N];
    for (i = 0; i < n_prices; ++i) {
        free(arr[i]);
    }
    free(arr);
    return max_profit;
}

/*
def foo3():
    l = [1]*n
    while True:
        print (*l)

        if l[-1] == 1:
            l.pop()
            l[-1] += 1
        else:
            l[-2] += 1
            l[-1:] = [1]*(l[-1] - 1)
        
        if l[0] == n:
            break
*/

void CalcSequenceNumber(int n)
{
    cout << "The input number is " << n << " :" << endl;

    vector<int> v(n);
    int i = 0;
    while (i < n) v[i++] = 1;

    while (1)
    {
        int j = 0; while (j < v.size()) cout << " " << v[j++]; cout << endl;

        if (v[v.size() - 1] == 1)
        {
            v.pop_back();
            v[v.size() - 1] += 1;
        }
        else
        {
            v[v.size() - 2] += 1;
            int k = v[v.size() - 1] - 1;
            v[v.size() - 1] = 1; k--;
            while (k-- > 0) v.push_back(1);
        }

        if (v.at(0) == n)
            break;
    }
}

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

    // error C2259: 'IInterfaceC' : cannot instantiate abstract class
    // IInterfaceC c;



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

    // test virtual destructor 
    c1* cc1 = new c3();
    delete cc1;
    //c2* cc2 = dynamic_cast<c2*>(cc1);
    //delete cc2;

    //absCC c;

    KA* ka = new KAA();
    delete ka;


    // 
    int arraya[5] = {7};
    UnusedVar(arraya);

    CalcSequenceNumber::decompose(3);
    CalcSequenceNumber::decompose(5);

    CalcSequenceNumber(3);
    CalcSequenceNumber(5);

    int arrayb[] = {10, 20, 15, 17, 22};
    int r = optimal_trades(arrayb, 5, 2);
    int i = 0; while (i < 5) cout << arrayb[i++] << ", "; cout << endl;
    cout << "total profit is: " << r << endl;
    

    system("pause");
	return 0;
}