#pragma once
#include <iostream>
#include <set>
#include <cstdlib>

class SinglyLinkedList
{
private:
    struct Node
    {
        int x;
        Node* next;

        Node(int val = 0, Node* n = nullptr)
            : x(val), next(n)
        {
        }
    };
    Node* _head = nullptr;
    unsigned int _size = 0;

    Node* get_node(unsigned int idx) const;

public:
    SinglyLinkedList();
    SinglyLinkedList(unsigned int len);
    SinglyLinkedList(const SinglyLinkedList& other);
    SinglyLinkedList& operator=(const SinglyLinkedList& other);
    ~SinglyLinkedList();

#pragma region getters
    unsigned int size() const;
    int head() const;
#pragma endregion

    // returns true if the head is null
    bool empty() const;
    // returns the content of the last node
    // SinglyLinkedList does not contain an internal variable for the tail, 
    // so this operation is O(n) time
    int tail() const;
    // reverses the list in O(n) time and O(1) space
    void reverse();
    // prints the list elements to the console
    void print();
    // gets the content of the Node at the specified index
    int get(unsigned int idx) const;
    // sets the content of the Node at the specidied index
    void set(int x, unsigned int idx);
    // inserts the element at the specified index 
    void insert(int x, unsigned int idx);
    // inserts a copy of a list at the specified index
    void insert(const SinglyLinkedList& other, unsigned int idx);
    // adds an element at the head of the list
    void push_front(int x);
    // adds an element at the tail of the list
    void push_back(int x);
    // deletes every node of the list
    void clear();
    // deletes the node at the specified index
    void remove(unsigned int idx);
    // deletes the nodes from the startIdx to the endIdx
    // end idx is excluded
    void remove(unsigned int startIdx, unsigned int endIdx);
    // deletes the head of the list
    void pop_front();
    // deletes the tail of the list
    void pop_back();
    // returns the reference of the element at the specified index 
    int& operator[](unsigned int idx);
    // returns the constant reference of the element at the specified index 
    const int& operator[](unsigned int idx) const;
    // adds a copy of a list to the tail of this list
    void operator+=(const SinglyLinkedList& other);
    // returns the middle element without knowing the size of the list
    // obviously does not use size()
    int find_middle_element() const;
    // sorts the list in ascending or descending order
    void selection_sort(bool ascending = true);

#pragma region static_methods
    // returns a new list by merging the two ones in ascending order
    // the two lists need to be already sorted in ascending order, if not, use selection_sort()
    static SinglyLinkedList merge_sorted_lists(SinglyLinkedList* l1, SinglyLinkedList* l2);
#pragma endregion

    // removes the duplicate values, but leaves one instance of them
    // this should work both with sorted and unsorted lists
    void delete_duplicates();
    // removes the duplicate values and does not leave any instance of them
    // this only works with sorted lists
    void delete_duplicates_entirely();
    // returns true if the list is palindrome
    // ---- O(n) time; O(n) space ----
    bool is_palindrome();
    // returns true if at some point a node points to a previous one, 
    // so if there is a cycle. This uses the tortoise and hare algorithm
    bool has_cycle();

#pragma region testing_methods
    // sets a random value between a range for every element in the list
    void randomize_values(int minVal = 10, int maxVal = -10);
#pragma endregion
};
