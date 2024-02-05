#include <iostream>
#include <list>

using namespace std;

#pragma region list
// 
// list (연결 리스트)  (단일 / 이중 / 원형) (STL list는 이중 연결 리스트)
// - list의 동작원리
// - 중간 삽입 삭제
// - 처음/끝 삽입 삭제
// 
// 리스트는 메모리 상 연속된 공간에 저장 X
// 
// 
// Vector vs List
// - List가 삽입, 삭제 용이
// - Vector가 탐색, 임의 접근 용이
// - list는 인덱스 접근 [] 제공X, vector는 Remove() 제공 X
// 
// 
// list.end()는 end(Head)Node임, 값이 들어가있지 않음
// 그러나 처음 값에서 end Node로 가는 것은 불가능
// 
// end Node는 li.end()와 비교하기 위한 용도로만 사용, 리스트의 끝 확인
// 
// 
// list는 탐색 속도가 느린데, 중간 값 삽입,삭제가 빠르다는건 모순이지 않나??
// - 그냥 분리해서 생각하자, 우리가 삭제할 n번째 iterator 포인터를 갖고 있다고 하면 중간 삽입 삭제가 빠르다..
// 
#pragma endregion




template<typename T>
class Node
{
public:
    Node() :_next(nullptr), _prev(nullptr), _data(T())      //T()는 해당 타입의 기본 값 생성, int 경우 0
    {
        
    }

    Node(const T& value) : _next(nullptr), _prev(nullptr), _data(value)
    {

    }

public:
    Node* _next;
    Node* _prev;
    T _data;
};


template<typename T>
class Iterator
{
public:

    Iterator() : _node(nullptr)
    {

    }

    Iterator(Node<T>* node) : _node(node)
    {

    }

    // ++it
    Iterator<T>& operator++()
    {
        _node = _node->_next;
        return this;
    }

    // it++
    Iterator<T> operator++()
    {
        Iterator<T> temp = *this;
        _node = _node->_next;
        return temp;
    }


    // --it
    Iterator<T>& operator--()
    {
        _node = _node->_prev;
        return this;
    }

    // it--
    Iterator<T> operator--()
    {
        Iterator<T> temp = *this;
        _node = _node->_prev;
        return temp;
    }


    T& operator*()
    {
        return _node->_data;
    }


    bool operator==(const Iterator& right)
    {
        return _node == right._node;
    }


public:
    Node<T>* _node;
};



template<typename T>
class List
{
public:
    List() : _size(0)
    {
        _header = new Node<T>();
        _header->_next = _header;
        _header->_prev = _header;
    }
    
    ~List()
    {
        while (_size > 0)
            pop_back();

        delete _header;
    }

    void push_back(const T& value)
    {
        AddNode(_header, value);
    }

    Node<T>* AddNode(Node<T>* before, const T& value)
    {
        Node<T>* node = new Node<T>(value);

        Node<T>* prevNode = before->_prev;
        prevNode->_next = node;
        node->_prev = prevNode;

        node->_next = before;
        before->_prev = node;

        _size++;

        return node;
    }


    void pop_back()
    {
        RemoveNode(_header->_prev);
    }

    Node<T>* RemoveNode(Node<T>* node)
    {
        Node<T>* prevNode = node->_prev;
        Node<T>* nextNode = node->_next;

        prevNode->_next = nextNode;
        prevNode->_prev = prevNode;

        delete node;

        _size--;
               

        return nextNode;
    }

    int size() { return _size; }

public:
    typedef Iterator<T> iterator;

    iterator begin() { return iterator(_header->_next); }
    iterator end() { return iterator(_header); }

    iterator insert(iterator it, const T& value)
    {
        return iterator(AddNode(it._node, value));
    }

    iterator erase(iterator it)
    {
        Node<T>* node = RemoveNode(it._node);
        return iterator(node);
    }

public:
    Node<T>* _header;
    int _size;
};






int main()
{
    list<int> li;

    list<int>::iterator eraseIt;

    for (int i = 0; i < 10; i++)
    {
        if (i == 5)
        {
            eraseIt = li.insert(li.end(), i);
        }
        else
        {
            li.push_back(i);
        }
    }

    li.pop_back();

    li.erase(eraseIt);


    for (list<int>::iterator it = li.begin(); it != li.end(); ++it)
    {
        cout << *it << endl;
    }
}
