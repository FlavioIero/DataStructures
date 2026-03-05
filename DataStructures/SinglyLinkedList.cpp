#include "SinglyLinkedList.h"
using namespace std;


SinglyLinkedList::SinglyLinkedList() {}

SinglyLinkedList::SinglyLinkedList(unsigned int len)
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

SinglyLinkedList::SinglyLinkedList(const SinglyLinkedList& other)
{
    _head = nullptr;
    _size = 0;

    Node* curr = other._head;
    while (curr)
    {
        push_back(curr->x);
        curr = curr->next;
    }
}

SinglyLinkedList& SinglyLinkedList::operator=(const SinglyLinkedList& other)
{
    if (this == &other)
        return *this;

    clear();

    Node* curr = other._head;
    while (curr)
    {
        push_back(curr->x);
        curr = curr->next;
    }

    return *this;
}

SinglyLinkedList::~SinglyLinkedList()
{
    clear();
}

SinglyLinkedList::Node* SinglyLinkedList::get_node(unsigned int idx) const
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

#pragma region getters
unsigned int SinglyLinkedList::size() const { return _size; }
int SinglyLinkedList::head() const
{
    if (empty())
        throw out_of_range("List is empty");
    return _head->x;
}
#pragma endregion

bool SinglyLinkedList::empty() const
{
    return _head == nullptr;
}

int SinglyLinkedList::tail() const
{
    if (empty())
        throw out_of_range("List is empty");
    return get(_size - 1);
}

void SinglyLinkedList::reverse()
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

void SinglyLinkedList::print()
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

int SinglyLinkedList::get(unsigned int idx) const
{
    Node* node = get_node(idx);
    return node->x;
}

void SinglyLinkedList::set(int x, unsigned int idx)
{
    get_node(idx)->x = x;
}

void SinglyLinkedList::insert(int x, unsigned int idx)
{
    if (idx == 0)
        return push_front(x);

    Node* prev = get_node(idx - 1);
    Node* node = new Node{ x, prev->next };
    prev->next = node;

    _size++;
}

void SinglyLinkedList::insert(const SinglyLinkedList& other, unsigned int idx)
{
    if (other.empty())
        return;

    if (idx > _size)
        throw out_of_range("Index out of range");

    Node dummy{ 0, _head };
    Node* prev = &dummy;

    for (unsigned int i = 0; i < idx; i++)
        prev = prev->next;

    Node* currOther = other._head;

    Node* firstInserted = nullptr;
    Node* lastInserted = nullptr;

    while (currOther)
    {
        Node* newNode = new Node{ currOther->x, nullptr };

        if (!firstInserted)
            firstInserted = newNode;
        else
            lastInserted->next = newNode;

        lastInserted = newNode;
        currOther = currOther->next;
    }

    lastInserted->next = prev->next;
    prev->next = firstInserted;

    _head = dummy.next;
    _size += other._size;
}


void SinglyLinkedList::push_front(int x)
{
    Node* node = new Node{ x, _head };
    _head = node;
    _size++;
}

void SinglyLinkedList::push_back(int x)
{
    if (_size == 0)
        return push_front(x);
    insert(x, _size);
}

void SinglyLinkedList::clear()
{
    if (_size == 0)
        return;
    if (_size == 1)
        return remove(0);
    remove(0, _size);
}

void SinglyLinkedList::remove(unsigned int idx)
{
    if (idx == 0)
        return pop_front();

    Node* prev = get_node(idx - 1);
    Node* curr = prev->next;
    prev->next = curr->next;
    delete curr;

    _size--;
}

void SinglyLinkedList::remove(unsigned int startIdx, unsigned int endIdx)
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

void SinglyLinkedList::pop_front()
{
    if (_size == 0)
        throw out_of_range("List is empty");

    Node* prevHead = _head;
    _head = _head->next;
    delete prevHead;
    _size--;
}

void SinglyLinkedList::pop_back()
{
    if (_size == 0)
        throw out_of_range("List is empty");
    remove(_size - 1);
}

int& SinglyLinkedList::operator[](unsigned int idx)
{
    return get_node(idx)->x;
}

const int& SinglyLinkedList::operator[](unsigned int idx) const
{
    return get_node(idx)->x;
}

void SinglyLinkedList::operator+=(const SinglyLinkedList& other)
{
    int idx = _size - 1 >= 0 ? _size : 0;
    insert(other, idx);
}

int SinglyLinkedList::find_middle_element() const
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

void SinglyLinkedList::selection_sort(bool ascending)
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
SinglyLinkedList SinglyLinkedList::merge_sorted_lists(SinglyLinkedList* l1, SinglyLinkedList* l2)
{
    if ((l1 == nullptr || l1->empty()) && (l2 == nullptr || l2->empty()))
        return SinglyLinkedList();

    SinglyLinkedList res = SinglyLinkedList();
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
    res._head = beforeHead->next;
    res._size = size;

    delete beforeHead;

    return res;
}

#pragma endregion

void SinglyLinkedList::delete_duplicates()
{
    if (empty())
        return;

    Node* prev = _head;
    Node* curr = prev->next;
    std::set<int> nums = { _head->x };

    while (curr)
    {
        Node* next = curr->next;

        if (nums.find(curr->x) == nums.end())
        {
            nums.insert(curr->x);
            prev = curr;
            curr = next;
        }
        else
        {
            Node* temp = curr;
            curr = next;
            prev->next = curr;
            delete temp;
            _size--;
        }
    }
}

void SinglyLinkedList::delete_duplicates_entirely()
{
    if (empty() || !_head->next)
        return;

    Node dummy{ 0, _head };
    Node* prev = &dummy;
    Node* curr = _head;

    while (curr)
    {
        bool duplicate = false;

        while (curr->next && curr->x == curr->next->x)
        {
            Node* temp = curr;
            curr = curr->next;
            delete temp;
            _size--;
            duplicate = true;
        }

        if (duplicate)
        {
            Node* temp = curr;
            curr = curr->next;
            delete temp;
            _size--;
            prev->next = curr;
        }
        else
        {
            prev = curr;
            curr = curr->next;
        }
    }

    _head = dummy.next;
}

bool SinglyLinkedList::is_palindrome()
{
    if (!_head->next)
        return true;

    // idk how to do it in O(1) space

    // reverse list and create a new one
    Node* prev = nullptr;
    Node* curr = _head;
    Node* next = nullptr;

    Node* otherHead = new Node{ _head->x, nullptr };
    Node* otherCurr = otherHead;
    while (curr)
    {
        next = curr->next;
        otherCurr->next = new Node{ curr->x, nullptr };
        otherCurr = otherCurr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    _head = prev;

    // check if palindrome
    curr = _head;
    otherCurr = otherHead->next;
    while (curr)
    {
        if (curr->x != otherCurr->x)
            return false;
        curr = curr->next;
        otherCurr = otherCurr->next;
    }
    return true;
}

bool SinglyLinkedList::has_cycle()
{
    if (empty())
        return false;

    Node* slow = _head;
    Node* fast = _head;

    while (fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast)
            return true;
    }
    return false;
}

#pragma region testing_methods
void SinglyLinkedList::randomize_values(int minVal, int maxVal)
{
    if (empty())
        return;

    if (minVal > maxVal)
        swap(minVal, maxVal);

    Node* curr = _head;

    while (curr)
    {
        int r = minVal + rand() % (maxVal - minVal + 1);
        curr->x = r;
        curr = curr->next;
    }
}
#pragma endregion
