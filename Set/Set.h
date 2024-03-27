#pragma once
#include <sstream>
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
    Set() : head(T()) {}
    Set(T x, Node* next = nullptr) { head = new Node(x, next); }
    Set(const Set& other);
    Set(T* elems, int n);
    ~Set();
   
    Set<T>& add(T x);
    Set<T>& add(T* x, int size);

    Set set_union(const Set& T) const;
    Set interset() const;
    Set differ() const;
    Set sym_diff() const;

    bool contain(const T& x) const;
    Set& remove(const T& x); // if no such element - exception 
    int size() const { return size; };
    // Оператор =
    Set& operator=(const Set& other);
    // Метод друку
    void print_all() const; 

};

template<typename T>
inline void Set<T>::print_all() const
{
    Node* curr = head;
    if (curr == nullptr)
    {
        std::cout << "List is empty :(\n";
    }
    else
    {
        while (curr != nullptr)
        {

            std::cout << curr->value << " ";
            curr = curr->next;
            std::cout << std::endl;
        }
    }
}
template<typename T>
inline Set<T>& Set<T>::operator=(const Set<T>& other)
{
    {
        if (this == &other) {
            return *this;
        }
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        if (other.head == nullptr)
        {
            return *this;
        }
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
    : head(nullptr)
{
    if (other.head == nullptr)
    {
        return;
    }
    head = new Node(other.head->value);
    Node* curr = head;
    Node* otherCurr = other.head->next;
    while (otherCurr != nullptr) {
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
    Node* curr = head;
    Node* temp;
    while (curr != nullptr)
    {   
        temp = curr;
        curr = curr->next;
        delete temp;
    }
}

template<typename T>
inline Set<T>& Set<T>::add(T x)
{
    if (!contain(x))
    {
        Node phantom(T(), head);
        Node* curr = &phantom;
        while (curr->next != nullptr || curr->next->value < x)
        {
            curr = curr->next
        }
        Node* newNode(x, curr->next);
        curr->next = newNode;
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
}

template<typename T>
inline Set<T> Set<T>::set_union(const Set& T) const
{
    return Set();
}

template<typename T>
inline Set<T> Set<T>::interset() const
{
    return Set();
}

template<typename T>
inline Set<T> Set<T>::differ() const
{
    return Set();
}

template<typename T>
inline Set<T> Set<T>::sym_diff() const
{
    return Set();
}

template<typename T>
inline bool Set<T>::contain(const T& x) const
{
    return false;
}

template<typename T>
inline Set<T>& Set<T>::remove(const T& x)
{

}
