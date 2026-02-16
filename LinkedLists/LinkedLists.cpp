#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;


class SinglyLinkedList
{
private: 
    struct Node
    {
        int X = 0;
        Node* Next = nullptr;
    };
    Node* _head = nullptr;
    unsigned int _size = 0;

public: 
    SinglyLinkedList() {}

    SinglyLinkedList(unsigned int len)
    {
        if (len <= 0)
            return;

        Node* curr = nullptr;
        Node* newNode = new Node{ 0, nullptr };
        _head = newNode;
        curr = newNode;

        for (unsigned int i = 1; i < len; i++)
        {
            newNode = new Node{ (int)i, nullptr };

            curr->Next = newNode;
            curr = newNode;
        }

        _size = len;
    }

#pragma region getters
    unsigned int size() const { return _size; }
    int head() const 
    { 
        if (_size == 0)
            throw out_of_range("List is empty");
        return _head->X; 
    }
#pragma endregion

    bool empty() const
    {
        return _size == 0;
    }

    int tail() const 
    { 
        if (_size == 0)
            throw out_of_range("List is empty");
        return get(_size - 1);
    }

    void reverse()
    {
        Node* prev = nullptr;
        Node* curr = _head;
        Node* next = nullptr;

        while (curr != nullptr)
        {
            next = curr->Next;
            curr->Next = prev;
            prev = curr;
            curr = next;
        }

        _head = prev;
    }

    void print()
    {
        Node* currNode = _head;

        cout << "Linked list elements: ";

        while (currNode != nullptr)
        {
            cout << currNode->X << ", ";
            currNode = currNode->Next;
        } 

        cout << "\n";
    }

    int get(unsigned int idx) const
    {
        Node* node = get_node(idx);
        return node->X;
    }

    void set(int x, unsigned int idx)
    {
        get_node(idx)->X = x;
    }

    void insert(int x, unsigned int idx)
    {
        if (idx == 0)
            return push_front(x);

        Node* prev = get_node(idx - 1);
        Node* node = new Node{ x, prev->Next };
        prev->Next = node;

        _size++;
    }

    void insert(SinglyLinkedList other, unsigned int idx)
    {
        unsigned int otherSize = other.size();

        if (other.size() == 0)
            return;

        Node* otherTail = otherSize == 1 ? other._head : other.get_node(otherSize - 1);

        if (idx == 0)
        {
            Node* prevHead = _head;
            _head = other._head;
            otherTail->Next = prevHead;
        }
        else
        {
            Node* prev = get_node(idx - 1);
            Node* next = prev->Next;
            prev->Next = other._head;
            otherTail->Next = next;
        }

        _size += otherSize;
    }

    void push_front(int x)
    {
        Node* node = new Node{ x, _head };
        _head = node;
        _size++;
    }

    void push_back(int x)
    {
        if (_size == 0)
            return push_front(x);
        insert(x, _size);
    }

    void clear()
    {
        if (_size == 0)
            return;
        if (_size == 1)
            return remove(0);
        remove(0, _size);
    }

    void remove(unsigned int idx)
    {
        if (idx == 0)
            return pop_front();
        
        Node* prev = get_node(idx - 1);
        Node* curr = prev->Next;
        prev->Next = curr->Next;
        delete curr;

        _size--;
    }

    // end idx is excluded
    void remove(unsigned int startIdx, unsigned int endIdx)
    {
        if (startIdx > endIdx)
            swap(startIdx, endIdx);

        if (startIdx >= _size)
            return;

        if (endIdx > _size)
            endIdx = _size;

        Node dummy{ 0, _head };
        Node* beforeStart = &dummy;

        for (unsigned int i = 0; i < startIdx; i++)
            beforeStart = beforeStart->Next;

        Node* curr = beforeStart->Next;

        for (unsigned int i = startIdx; i < endIdx && curr != nullptr; i++)
        {
            Node* temp = curr;
            curr = curr->Next;
            delete temp;
            _size--;
        }

        beforeStart->Next = curr;

        _head = dummy.Next;
    }

    void pop_front()
    {
        if (_size == 0)
            throw out_of_range("List is empty");

        Node* prevHead = _head;
        _head = _head->Next;
        delete prevHead;
        _size--;
    }

    void pop_back() 
    { 
        if (_size == 0)
            throw out_of_range("List is empty");
        remove(_size - 1); 
    }

    int& operator[](unsigned int idx)
    {
        return get_node(idx)->X;
    }

    const int& operator[](unsigned int idx) const
    {
        return get_node(idx)->X;
    }

    void operator+=(SinglyLinkedList other)
    {
        int idx = _size - 1 >= 0 ? _size : 0;
        insert(other, idx);
    }

private:
    Node* get_node(unsigned int idx) const
    {
        if (idx >= _size)
            throw out_of_range("Index out of range");

        Node* curr = _head;

        for (unsigned int i = 0; i < idx; i++)
        {
            curr = curr->Next;
        }

        return curr;
    }
};



int main()
{
    vector<int> v = vector<int>();

    v.clear();

    int len = 10;
    int len2 = 4;

    SinglyLinkedList list = SinglyLinkedList(len);
    SinglyLinkedList list2 = SinglyLinkedList(len2);

    cout << list.size() << " " << list2.size() << endl;

    list.print();
    list[5] = 8927349;
    list.print();
    //list.insert(list2, list.size());
    list += list2;
    list.print();

    return 0;
}
