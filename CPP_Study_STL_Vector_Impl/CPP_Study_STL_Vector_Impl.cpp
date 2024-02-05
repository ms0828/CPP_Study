#include <iostream>
#include<vector>

using namespace std;

//vector 구현

template<typename T>
class Iterator
{
public:
    Iterator() : _ptr(nullptr)
    {

    }

    Iterator(T* ptr) : _ptr(ptr)
    {

    }

    //전위++
    Iterator& operator++()
    {
        _ptr++;

        return *this;
    }

    //후위++
    Iterator operator++(int)
    {
        Iterator temp = this;
        _ptr++;
        return temp;
    }

    //전위--
    Iterator& operator--()
    {
        _ptr--;

        return *this;
    }

    //후위--
    Iterator operator--(int)
    {
        Iterator temp = this;
        _ptr--;
        return temp;
    }



    bool operator==(const Iterator& right)
    {
        return _ptr == right._ptr;
    }

    bool operator!=(const Iterator& right)
    {
        return _ptr != right._ptr;
    }


    T& operator*()
    {
        return *_ptr;
    }

    Iterator operator+(const int count)
    {
        Iterator temp = *this;
        temp._ptr += count;
        return temp;
    }

    Iterator operator-(const int count)
    {
        Iterator temp = *this;
        temp._ptr -= count;
        return temp;
    }

public:
    T* _ptr;

};


template<typename T>
class Vector
{
public:
    Vector() : _data(nullptr), _size(0), _capacity(0)
    {

    }

    ~Vector()
    {
        if (_data != nullptr)
            delete[] _data;
    }


    void push_back(const T& val)
    {
        if (_size == _capacity)
        {
            // 증설 작업
            int newCapacity = static_cast<int>(_capacity * 1.5);

            //0이나 1처럼 1.5배 해도 똑같은 숫자로 떨어지는 상황 예외
            if (newCapacity == _capacity)
                newCapacity++;
            
            reserve(newCapacity);
        }

        // 데이터 저장
        _data[_size] = val;

        // 데이터 개수 증가
        _size++;
        
    }


    void reserve(int capacity)
    {
        _capacity = capacity;

        // 새로운 메모리 공간
        T* newData = new T[_capacity];

        // 복사
        for (int i = 0; i < _size; i++)
        {
            newData[i] = _data[i];
        }

        // 기존 메모리 해제
        if (_data != nullptr)
            delete[] _data;

        // 새로운 메모리 할당
        _data = newData;
    }


    T& operator[](const int pos)
    {
        return _data[pos];
    }

    

    int size() { return _size; }
    int capacity(){ return _capacity; }


public:
    typedef Iterator<T> iterator;

    iterator begin() { return iterator(&_data[0]); }
    iterator end() { return begin() + _size; }

; public:
    T* _data;
    int _size;
    int _capacity;
};

int main()
{
    Vector<int> v;
    v.reserve(100);


    for (int i = 0; i < 100; i++)
    {
        v.push_back(i);
        cout << v.size() << " " << v.capacity() << endl;
    }

    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << endl;
    }

    cout << "-------------" << endl;




    for (Vector<int>::iterator it = v.begin(); it != v.end(); ++it)
    {
        cout << (*it) << endl;
    }

}