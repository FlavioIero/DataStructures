#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
using namespace std;


class SinglyLinkedList
{
private: 
    struct Node
    {
        int x = 0;
        Node* next = nullptr;
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

            curr->next = newNode;
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
        return _head->x; 
    }
#pragma endregion

    bool empty() const
    {
        return _head == nullptr;
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
            next = curr->next;
            curr->next = prev;
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
            cout << currNode->x << ", ";
            currNode = currNode->next;
        } 

        cout << "\n";
    }

    int get(unsigned int idx) const
    {
        Node* node = get_node(idx);
        return node->x;
    }

    void set(int x, unsigned int idx)
    {
        get_node(idx)->x = x;
    }

    void insert(int x, unsigned int idx)
    {
        if (idx == 0)
            return push_front(x);

        Node* prev = get_node(idx - 1);
        Node* node = new Node{ x, prev->next };
        prev->next = node;

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
            otherTail->next = prevHead;
        }
        else
        {
            Node* prev = get_node(idx - 1);
            Node* next = prev->next;
            prev->next = other._head;
            otherTail->next = next;
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
        Node* curr = prev->next;
        prev->next = curr->next;
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
            beforeStart = beforeStart->next;

        Node* curr = beforeStart->next;

        for (unsigned int i = startIdx; i < endIdx && curr != nullptr; i++)
        {
            Node* temp = curr;
            curr = curr->next;
            delete temp;
            _size--;
        }

        if (beforeStart == nullptr)
            throw logic_error("Error while removing element");

        beforeStart->next = curr;
        _head = dummy.next;
    }

    void pop_front()
    {
        if (_size == 0)
            throw out_of_range("List is empty");

        Node* prevHead = _head;
        _head = _head->next;
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
        return get_node(idx)->x;
    }

    const int& operator[](unsigned int idx) const
    {
        return get_node(idx)->x;
    }

    void operator+=(SinglyLinkedList other)
    {
        int idx = _size - 1 >= 0 ? _size : 0;
        insert(other, idx);
    }

    // obviously does not use _size
    int find_middle_element() const
    {
        if (empty())
            throw logic_error("List is empty");

        Node* slow = _head;
        Node* fast = _head;

        while (fast != nullptr && fast->next != nullptr)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        // Defensive null-check to satisfy static analysis tools.
        if (slow == nullptr)
            throw logic_error("List is empty");

        return slow->x;
    }

    // da implementare ascending
    void selection_sort(bool ascending = true)
    {
        if (empty())
            return;

        for (Node* l = _head; l != nullptr; l = l->next)
        {
            Node* replace = l;
            for (Node* r = l->next; r != nullptr; r = r->next)
            {
                if (ascending)
                {
                    if (r->x < replace->x)
                    {
                        replace = r;
                    }
                }
                else
                {
                    if (r->x > replace->x)
                    {
                        replace = r;
                    }
                }
            }
            if (replace != l)
            {
                int temp = l->x;
                l->x = replace->x;
                replace->x = temp;
            }
        }
    }

#pragma region static_methods
    static SinglyLinkedList* merge_sorted_lists(SinglyLinkedList* l1, SinglyLinkedList* l2)
    {
        if ((l1 == nullptr || l1->empty()) && (l2 == nullptr || l2->empty()))
            return nullptr;

        SinglyLinkedList* res = new SinglyLinkedList();
        Node* beforeHead = new Node();
        Node* curr = beforeHead;

        Node* h1 = l1->_head;
        Node* h2 = l2->_head;

        while (h1 && h2)
        {
            if (h1->x < h2->x)
            {
                curr->next = new Node{ h1->x, nullptr };
                h1 = h1->next;
            }
            else
            {
                curr->next = new Node{ h2->x, nullptr };
                h2 = h2->next;
            }
            curr = curr->next;
        }

        while (h1)
        {
            curr->next = new Node{ h1->x, nullptr };
            h1 = h1->next;
            curr = curr->next;
        }

        while (h2)
        {
            curr->next = new Node{ h2->x, nullptr };
            h2 = h2->next;
            curr = curr->next;
        }

        unsigned int size = l1->_size + l2->_size;
        res->_head = beforeHead->next;
        res->_size = size;

        delete beforeHead;

        return res;
    }

#pragma endregion

    void delete_duplicates()
    {
        if (empty())
            return;

        Node* prev = nullptr;
        Node* curr = _head;
        Node* next = nullptr;
        std::set<int> nums = { _head->x };

        while (curr->next != nullptr)
        {
            if (nums.find(curr->next->x) == nums.end())
            {
                nums.insert(curr->next->x);
                curr = curr->next;
            }
            else
            {
                Node* temp = curr->next;
                curr->next = curr->next->next;
                delete temp;
            }
        }
    }

    /* Cool exercises with singly linked lists include  
    detecting cycles using Floyd’s Cycle-Finding Algorithm,
    and reordering lists in zig-zag fashion.*/

private:
    Node* get_node(unsigned int idx) const
    {
        if (idx >= _size)
            throw out_of_range("Index out of range");

        Node* curr = _head;

        for (unsigned int i = 0; i < idx; i++)
        {
            curr = curr->next;
        }

        return curr;
    }
};


int main()
{
    vector<int> v = vector<int> { 3, 2, 2, 3 };

    int len = 7;
    int len2 = 4;

    SinglyLinkedList list = SinglyLinkedList(len);
    SinglyLinkedList list2 = SinglyLinkedList(len2);

    cout << "List 1 size(): " << list.size() << "; List2 size(): " << list2.size() << endl;

    list.print();
    cout << "Middle element: " << list.find_middle_element() << endl;
    
    list.print();
    //list.insert(list2, list.size());
    list += list2;
    list.print();

    //list.selection_sort(false);
    list.print();


    cout << "List1: " << endl;
    list.selection_sort();
    list.print();
    cout << "List2: " << endl;
    list.selection_sort();
    list2.print();
    SinglyLinkedList* mergedList = SinglyLinkedList::merge_sorted_lists(&list, &list2);
    cout << "Merged list: " << endl; 
    mergedList[1] = 99;
    mergedList[mergedList->size() - 1] = 99;
    mergedList->print();
    mergedList->delete_duplicates();
    mergedList->print();

    return 0;
}
