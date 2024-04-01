#pragma once
#include <sstream>
#include <iostream>
template <typename T>
class Set
{
private:
    struct Node
    {
        T value;
        Node* next;
        Node(T val, Node* ptr = nullptr) : value(val), next(ptr) {}
    };
    Node* head;
    unsigned size;
public:
    Set() : head(nullptr), size(0) {}
    Set(T x, Node* next = nullptr) : size(1), head(new Node(x, next)) {}
    Set(const Set& other);
    Set(T* elems, int n);
    ~Set();

    Set<T>& add(T x);
    Set<T>& add(T* x, int size);

    Set set_union(const Set& T) const;
    Set interset(const Set& T) const;
    Set differ(const Set& T) const;
    Set sym_diff(const Set& T) const;

    bool contain(const T& x) const;
    Set& remove(const T& x); // if no such element - exception 
    int get_size() const { return size; };
    Set& operator=(const Set& other);
    void print_all() const;


};

template<typename T>
inline bool Set<T>::contain(const T& x) const
{
    Node* curr = head;
    while (curr != nullptr && x <= curr->value)
    {
        curr = curr->next;
    }

    if (curr->value == x) {
        return true;
    }

    return false;
}

template<typename T>
inline void Set<T>::print_all() const
{
    Node* curr = head;
    if (curr == nullptr)
    {
        std::cout << "Set is empty :(\n";
    }
    else
    {
        std::cout << "Set: { ";
        while (curr != nullptr)
        {
            std::cout << curr->value;
            if (curr->next != nullptr) std::cout << " ; ";
            curr = curr->next;
        }
        std::cout << " }, size: " << size << std::endl;
    }
}
template<typename T>
inline Set<T>& Set<T>::operator=(const Set<T>& other)
{
    {
        if (this == &other)
        {
            return *this;
        }
        while (head != nullptr)
        {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        if (other.head == nullptr)
        {
            return *this;
        }
        size = other.size;
        head = new Node(other.head->value);
        Node* curr = head;
        Node* otherCurr = other.head->next;
        while (otherCurr != nullptr)
        {
            curr->next = new Node(otherCurr->value);
            curr = curr->next;
            otherCurr = otherCurr->next;
        }
        return *this;
    }
}

template<typename T>
inline Set<T>::Set(const Set& other)
    : head(nullptr), size(other.size)
{
    if (other.head == nullptr)
    {
        return;
    }
    size = other.size;
    head = new Node(other.head->value);
    Node* curr = head;
    Node* otherCurr = other.head->next;
    while (otherCurr != nullptr)
    {
        curr->next = new Node(otherCurr->value);
        curr = curr->next;
        otherCurr = otherCurr->next;
    }
}
template<typename T>
inline Set<T>::Set(T* elems, int n) : head(nullptr)
{
    add(elems, n);
}

template<typename T>
inline Set<T>::~Set()
{
    while (head != nullptr)
    {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

template<typename T>
inline Set<T> Set<T>::set_union(const Set& T) const
{
    Set Result;
    Node* ptr1 = head;
    Node* ptr2 = T.head;

    while (ptr1 != nullptr && ptr2 != nullptr)
    {
        if (ptr1->value == ptr2->value)
        {
            Result.add(ptr1->value);
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }
        else if (ptr1->value > ptr2->value)
        {
            Result.add(ptr2->value);
            ptr2 = ptr2->next;
        }
        else
        {
            Result.add(ptr1->value);
            ptr1 = ptr1->next;
        }
    }
    while (ptr1 != nullptr) 
    {
        Result.add(ptr1->value);
        ptr1 = ptr1->next;
    }
    while (ptr2 != nullptr)
    {
        Result.add(ptr2->value);
        ptr2 = ptr2->next;
    }
    return Result;
}
template <typename T>
inline Set<T>& Set<T>::add(T x)
{
    if (!contain(x))
    {
        ++size;
        Node phantom(T(), head);
        Node* curr = &phantom;
        while (curr->next != nullptr && x > curr->next->value)
        {
            curr = curr->next;
        } 
        Node* newNode = new Node(x, curr->next);
        curr->next = newNode;
        head = phantom.next;
    }
    return *this;
}

template<typename T>
inline Set<T>& Set<T>::add(T* x, int size)
{
    for (int i = 0; i < size; ++i)
    {
        add(x[i]);
    }
    return *this;
}
template<typename T>
inline Set<T> Set<T>::interset(const Set& T) const
{
    return Set();
}

template<typename T>
inline Set<T> Set<T>::differ(const Set& T) const
{
    return Set();
}

template<typename T>
inline Set<T> Set<T>::sym_diff(const Set& T) const
{
    Set A = this->differ(T);
    Set B = T.differ(this);

    Set C = A.set_union(B);
    return C;
}

template<typename T>
inline Set<T>& Set<T>::remove(const T& x)
{
    if (contain(x))
    {
        --size;
        Node phantom(T(), head);
        Node* curr = &phantom;
        while (curr->next->value != x)
        {
            curr = curr->next;
        }
        Node* temp = curr->next;
        curr->next = curr->next->next;
        delete temp;
        head = phantom.next;
    }
    else
    {
        std::ostringstream oss;
        oss << "Element: " << x << " is not in the set\n";
        throw std::runtime_error(oss.str());
    }
    return *this;
}
