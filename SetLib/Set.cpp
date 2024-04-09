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

void analyze_expression(std::string n)
{
    char op[] = { '/','-','+','*' };
    Set<char>operators(op, sizeof(op) / sizeof(op[0]));
    unsigned numbers_counter = 0;
    unsigned operators_counter = 0;
    unsigned brackets_counter = 0;
    unsigned variables_counter = 0;
    for (std::string::iterator iter = n.begin(); iter != n.end(); ++iter)
    {
        if (*iter > '0' && '9' > *iter)
        {
            ++numbers_counter;
        }
        else if (*iter == '(' || *iter == ')')
        {
            ++brackets_counter;
        }
        else if (operators.contain(*iter))
        {
            ++operators_counter;
        }
        else ++variables_counter;
    }
    cout << "In expression: " << n << " are " << numbers_counter << ((numbers_counter == 1) ? " number, " : " numbers, ");
    cout << operators_counter << ((operators_counter == 1) ? " operator, " : " operators, ");
    cout << brackets_counter << ((brackets_counter == 1) ? " bracket and " : " brackets and ");
    cout << variables_counter << ((variables_counter == 1) ? " variable\n" : " variables\n");
    (brackets_counter % 2 == 0) ? cout << "The number of brackets is appropriate\n" : cout << "The number of brackets is inappropriate\n";
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
    ostringstream oss;
    oss << dig;
    int start = oss.str().find('{');
    int end = oss.str().find('}');
    cout << oss.str().substr(start, end - start + 1);
}
