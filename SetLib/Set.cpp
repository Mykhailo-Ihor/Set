#include "Set.h"
using namespace std;
Set<size_t> sieve_of_eratosthenes(size_t n)
{
    Set<size_t> Sieve(2);
    Set<size_t>::Node* curr = Sieve.head;
    for (size_t i = 3; i <= n; i+=2)
    {
        curr->next = new Set<size_t>::Node(i);
        curr = curr->next;
        ++Sieve.size;
    }
    curr = Sieve.head->next;
    Set<size_t>::Node* otherCurr;
    while (curr != nullptr)
    {
        otherCurr = curr;
        while (otherCurr != nullptr && otherCurr->next != nullptr)
        {
            if (otherCurr->next->value % curr->value == 0)
            {
                Set<size_t>::Node* temp = otherCurr->next;
                otherCurr->next = otherCurr->next->next;
                delete temp;
                --Sieve.size;
            }
            otherCurr = otherCurr->next;
        }
        curr = curr->next;
    }
    return Sieve;
}

size_t digits(size_t n)
{
    Set<unsigned> dig;
    while (n % 10 != n)
    {
        dig.add(n % 10);
        n *= 0.1;
    } 
    dig.add(n);
    return dig.get_size();
}

void digits(size_t n,ostream& os)
{
    Set<unsigned> dig;
    while (n % 10 != n)
    {
        dig.add(n % 10);
        n *= 0.1;
    }
    dig.add(n);
    dig.print_all(os);
}

