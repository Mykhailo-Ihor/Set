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

    Set(const Set& other) : head(nullptr) 
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

    T& operator[] (int index)
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

    const T& operator[] (int index) const
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

    Set& operator=(const Set& other) {
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
        head = new Node(other.head->data);
        Node* curr = head;
        Node* otherCurr = other.head->next;
        while (otherCurr != nullptr)
        {
            curr->next = new Node(otherCurr->data);
            curr = curr->next;
            otherCurr = otherCurr->next;
        }
        return *this;
    }

  /*  void add(T val)
    {
        if (head == nullptr)
        {
            head = new Node(val);
            return;
        }
        Node* curr = head;
        while (curr->next != nullptr)
        {
            curr = curr->next;
        }
        curr->next = new Node(val);
    }*/

    void printAll() const
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

    //void insert(VolShape* val, int index)
    //{
    //    Node* newNode = new Node(val);
    //    Node phantom(new Cylinder, head);
    //    Node* curr = &phantom;
    //    for (int i = 0; i < index && curr != nullptr; ++i)
    //    {
    //        curr = curr->next;
    //    }
    //    if (curr == nullptr)
    //    {
    //        delete newNode;
    //        throw std::out_of_range("Error: Cannot insert at specified position\n");
    //    }
    //    newNode->next = curr->next;
    //    curr->next = newNode;
    //    head = phantom.next;
    //}
};