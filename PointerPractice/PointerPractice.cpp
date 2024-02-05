#include <iostream>
using namespace std;

#pragma warning(disable: 4996)


int main()
{
    const int BUF_SIZE = 100;


    char a[BUF_SIZE] = "Hello";
    char b[BUF_SIZE] = "Hello";

    if (a == b)
    {
        cout << "same" << endl;
    }
    else
    {
        cout << "different" << endl;
    }


    
}

