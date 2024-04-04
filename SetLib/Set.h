#pragma once
#include <sstream>
#include <iostream>
template <typename T>
class Set
{
public:
    struct Node
    {
        T value;
        Node* next;
        Node(T val, Node* ptr = nullptr) : value(val), next(ptr) {}
    };
private:
    Node* head;
    unsigned size;
public:
    Set() : head(nullptr), size(0) {}
    Set(T x, Node* next = nullptr) : size(1), head(new Node(x, next)) {}
    Set(const Set& other);
    Set(T* elems, int n);
    ~Set();

    Set& add(T x);
    Set& add(T* x, int size);
    Set& remove(const T& x); // if no such element - exception 
    Set& remove_all();

    Set set_union(const Set& other) const;
    Set intersect(const Set& other) const;
    Set differ(const Set& other) const;
    Set sym_diff(const Set& other) const;
    template <typename T, typename U>
    friend Set<std::pair<T, U>> cartesian_product(const Set<T>& ths, const Set<U>& other);
    /*template<typename U>
    Set<std::pair<T, U>> cartesian_product(const Set<U>& set2) const;*/

    bool contain(const T& x) const;
    int  get_size() const { return size; };
    void print_all(std::ostream& os = std::cout) const;
    Set& operator=(const Set& other);
    bool operator == (const Set<T>& other);
};
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

template <typename T>
inline Set<T>& Set<T>::add(T x)
{
    
    Node phantom(T(), head);
    Node* curr = &phantom;
    while (curr->next != nullptr && curr->next->value < x)
    {
        curr = curr->next;
    }
    if (curr->next == nullptr || x < curr->next->value)
    {
        Node* newNode = new Node(x, curr->next);
        curr->next = newNode;
        head = phantom.next;
        ++size;
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
inline Set<T>& Set<T>::remove(const T& x)
{
    Node  phantom(T(), head);
    Node* curr = &phantom;
    while (curr->next != nullptr && curr->next->value < x)
    {
        curr = curr->next;
    }
    if (curr->next == nullptr || x < curr->next->value)
    {
        std::ostringstream oss;
        oss << "Element: " << x << " is not in the set\n";
        throw std::runtime_error(oss.str());
    }
    else
    {
        Node* temp = curr->next;
        curr->next = curr->next->next;
        delete temp;
        head = phantom.next;
        --size;
    }
    return *this;
}

template<typename T>
inline Set<T>& Set<T>::remove_all()
{
    while (head != nullptr)
    {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    size = 0;
    return *this;
}

template<typename T>
inline Set<T> Set<T>::set_union(const Set& other) const
{
	Set<T> Result;
    Node phantom(T(),Result.head);
	Node* res = &phantom;
	Node* A = head;
	Node* B = other.head;
	while (A != nullptr && B != nullptr)
	{
		if (A->value < B->value)
		{
			res->next = new Node(A->value);
			A = A->next;
		}
		else if (B->value < A->value)
		{
			res->next = new Node(B->value);
			B = B->next;
		}
		else
		{
			res->next = new Node(A->value);
			A = A->next;
			B = B->next;
		}
		res = res->next;
		++Result.size;
	}
	while (A != nullptr)
	{
		res->next = new Node(A->value);
		A = A->next;
		res = res->next;
		++Result.size;
	}
	while (B != nullptr)
	{
		res->next = new Node(B->value);
		B = B->next;
		res = res->next;
		++Result.size;
	}
    Result.head = phantom.next;
	return Result;
}

template<typename T>
inline Set<T> Set<T>::intersect(const Set& other) const
{
    Set<int> A = other;
    Set<int> res;
    Node* curr = (get_size() < other.get_size()) ? head : other.head;
    while (curr != nullptr)
    {
        if (contain(curr->value) && A.contain(curr->value)) res.add(curr->value);
        curr = curr->next;
    }
    return res;
}

template<typename T>
inline Set<T> Set<T>::differ(const Set& other) const
{
    Set<T> B = *this;
    Node* curr = other.head;
    while (curr != nullptr)
    {
        if (B.contain(curr->value))
            B.remove(curr->value);
        curr = curr->next;
    }
    return B;
}

template<typename T>
inline Set<T> Set<T>::sym_diff(const Set& other) const
{
    Set A = this->differ(other);
    Set B = other.differ(*this);
    Set C = A.set_union(B);
    return C;
}

template <typename T, typename U>
Set<std::pair<T, U>> cartesian_product(const Set<T>& set1, const Set<U>& set2)
{
    Set<std::pair<T, U>> result;
    typename Set<T>::Node* curr1 = set1.head;
    while (curr1 != nullptr)
    {
        typename Set<U>::Node* curr2 = set2.head;
        while (curr2 != nullptr)
        {
            std::pair<T, U> pair(curr1->value, curr2->value);
            result.add(pair);
            curr2 = curr2->next;
        }
        curr1 = curr1->next;
    }
    return result;
}
//template<typename T>
//template<typename U>
//Set<std::pair<T, U>> Set<T>::cartesian_product(const Set<U>& set2) const
//{
//    Set<std::pair<T, U>> result;
//    Node* curr1 = head;
//    while (curr1 != nullptr)
//    {
//        typename Set<U>::Node* curr2 = set2.head;
//        while (curr2 != nullptr)
//        {
//            std::pair<T, U> pair(curr1->value, curr2->value);
//            result.add(pair);
//            curr2 = curr2->next;
//        }
//        curr1 = curr1->next;
//    }
//    return result;
//}
template<typename T, typename U>
std::ostream& operator<<(std::ostream& os, const std::pair<T, U>& p)
{
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

template<typename T>
inline bool Set<T>::contain(const T& x) const
{
    Node* curr = head;
    while (curr != nullptr && curr->value < x)
    {
        curr = curr->next;
    }
    if (curr == nullptr || x < curr->value)
        return false;
    else return true;
}

template<typename T>
inline void Set<T>::print_all(std::ostream& os) const
{
    Node* curr = head;
    if (curr == nullptr)
    {
        os << "Empty set\n";
    }
    else
    {
        os << "Set: { ";
        while (curr->next!= nullptr)
        {
            os << curr->value << " ; ";
            curr = curr->next;
        }
        os << curr->value << " }, size: " << size << std::endl;
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
inline bool Set<T>::operator==(const Set<T>& other)
{
    if (size != other.size) return false;
    Node* curr = head;
    Node* otherCurr = other.head;
    while (curr != nullptr)
    {
        if (curr->value != otherCurr->value) return false;
        curr = curr->next;
        otherCurr = otherCurr->next;
    }
    return (curr == nullptr && otherCurr == nullptr);
}

template <typename T>
std::ostream& operator << (std::ostream& os, const Set<T>& S)
{
    S.print_all();
    return os;
}