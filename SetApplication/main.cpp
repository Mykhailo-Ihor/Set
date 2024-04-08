#include "../SetLib/Set.h"

using namespace std;
int main()
{
    int a[5] = { 1, 3, 5, 7, 9 };
    Set<int> A(a, 5);
    cout << "A = " << A;
    int b[4] = { 2, 8, 3, 9 };
    Set<int> B(b, 4);
    cout << "B = " << B;
    try
    {
        cout << "Trying to remove 5 from set A...\n";
        A.remove(5);
        cout << "Deletion successful\n";

        cout << "Trying to remove 4 from set A...\n";
        A.remove(4);
        cout << "Deletion successful\n";
    }
    catch (const std::runtime_error& ex)
    {
        std::cout << ex.what() << '\n';
    }
    Set<int> C = A.set_union(B);
    cout << "C = A+B = " << C << endl;
    Set<int> D = A.intersect(B);
    cout << "D = A*B = " << D << endl;
    Set<int> E = B.intersect(C);
    cout << "E = B*C = " << E << endl;
    Set<int> F = A.differ(B);  
    cout << "F = A-B = " << F << endl;
    Set<int> G = A.sym_diff(B);
    cout << "G = (A-B)+(B-A) = " << G << endl;
    Set<pair<int, char>> H;
    char abc[] = {"abc"};
    Set<char> ABC(abc,3);
    H = cartesian_product(B.differ(3), ABC);
    cout << "H = (B-{3}) X {a,b,c} = " << H << endl;
    H.remove_all();
    cout << "After removal: H = " << H << endl;
    cout << "All primes from 2 to 1000:\n";
    Set<size_t> Sieve = sieve_of_eratosthenes(1000);
    Sieve.print_all();
    cout << "\nNumber 123454321 consists of digits: ";
    digits(12345321,cout);
    analyze_expression("(2a+b*3-c");
    return 0;
}