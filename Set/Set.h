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
    Set() : head() {}
    Set(T val, Node* next = nullptr) { head = new Node(val, next); }
    Set(const Set& other);
    Set(T* elems, int n);
    Set(T x);
    ~Set();
   
    Set& add(T x);
    Set& add(T* x, int size);

    Set union(const Set& T) const;
    Set interset() const;
    Set differ() const;
    Set sym_diff() const;

    bool Contain(const T& x) const;
    Set& remove(const T& x); // if no such element - exception 
    int size() const { return size; };
    // Оператор []
    T& operator[] (int index); 
    // Константний оператор []
    const T& operator[] (int index) const; 
    // Оператор =
    Set& operator=(const Set& other);
    // Метод друку
    void printAll() const; 

};

template<typename T>
inline T& Set<T>::operator[](int index)
{
    Node* curr = head;
    for (int i = 0; i < index && curr != nullptr; ++i)
    {
        curr = curr->next;
    }
    if (curr == nullptr)
    {
        std::ostringstream oss;
        oss << "Error: Cannot get element at index #" << index << std::endl;
        throw std::out_of_range(oss.str());
    }
    return curr->value;
}
template<typename T>
inline const T& Set<T>::operator[](int index) const
{
    Node* curr = head;
    for (int i = 0; i < index && curr != nullptr; ++i)
    {
        curr = curr->next;
    }
    if (curr == nullptr)
    {
        std::ostringstream oss;
        oss << "Error: Cannot get element at index #" << index << std::endl;
        throw std::out_of_range(oss.str());
    }
    return curr->value;
}
template<typename T>
inline void Set<T>::printAll() const
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
inline Set<T>::Set(T* elems, int n)
{

}

template<typename T>
inline Set<T>::Set(T x)
{

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
