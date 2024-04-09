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

void analyze_ex(const std::string ex)
{
    char brr[5] = { '+', '-', '*', '/', '=' };
    Set<char> set_operators;
    set_operators.add(brr, 5);

    size_t numeral = 0;
    size_t operators = 0;
    size_t open_parenthesis = 0;
    size_t closed_parenthesis = 0;


    const char* arr = ex.c_str();
    for (int i = 0; arr[i] != '\0'; ++i)
    {

        if (arr[i] > 47 && arr[i] < 58)
        {
            ++numeral;

        }
        else if (arr[i] == 40)
        {
            ++open_parenthesis;
        }
        else if (arr[i] == 41)
        {
            ++closed_parenthesis;
        }
        else if (set_operators.contain(arr[i]))
        {
            ++operators;
        }
    }


    std::cout << "numbers = " << numeral << std::endl;
    std::cout << "operators = " << operators << std::endl;
    std::cout << "open_parenthesis = " << open_parenthesis << std::endl;
    std::cout << "closed_parenthesis = " << closed_parenthesis << std::endl << std::endl;

    if (open_parenthesis == closed_parenthesis)
    {
        std::cout << "open_parenthesis = closed_parenthesis. All is good :)" << std::endl;
    }
    else
    {
        std::cout << "open_parenthesis != closed_parenthesis. Check the correctness of the expression." << std::endl;
    }

}

void first_enter(const std::string exm)
{
    const char* arr = exm.c_str();
    Set<char> abrcd;
    for (size_t i = 0; arr[i] != '\0'; ++i)
    {
        if (!abrcd.contain(arr[i]))
        {
            std::cout << arr[i];
        }
        abrcd.add(arr[i]);
    }
}

void at_least_twice(const std::string exm)
{
    Set<char> abr;
    const char* arr = exm.c_str();
    Set<char> abcrd;
    for (size_t i = 0; arr[i] != '\0'; ++i)
    {
        if (abcrd.contain(arr[i]))
        {
            abr.add(arr[i]);
        }
        abcrd.add(arr[i]);

    }
    try
    {
        abr.remove(' ');
    }
    catch (...)
    {}
    abr.print_all();
}

void only_once(const std::string exm)
{
    Set<char> abr;
    const char* arr = exm.c_str();
    Set<char> abcrd;
    for (size_t i = 0; arr[i] != '\0'; ++i)
    {
        if (abcrd.contain(arr[i]))
        {
            abr.add(arr[i]);
        }
        abcrd.add(arr[i]);
    }
    Set<char> result = abcrd.differ(abr);
    try
    {
        result.remove(' ');
    }
    catch (...)
    {}
    result.print_all();
}
