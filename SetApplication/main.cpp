#include "../SetLib/Set.h"
#include "../SetLib/Сities.h"
#include "../SetLib/Guests.h"
#include "../SetLib/Shop.h"
#include <Windows.h>
using namespace std;
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    cout << "Демонстрація класу Set\n";
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
    cout << "After removal: H = " << H << endl << "Press any button to continue...\n";
    cin.get();
    cout << "Демонстрація - Проць Михайло-Ігор\nЗадача п.1\n";
    analyze_expression("(2a+b*3-c");
    cout << "\nЗадача п.2\n";
    cout << "Число 123454321 складається з цифр: ";
    digits(12345321, cout);
    cout << "\nЗадача п.4\n";
    cout << "Всі прості числа від 2 до 100:\n";
    Set<size_t> Sieve = sieve_of_eratosthenes(100);
    Sieve.print_all();
    CitiesTable table;
    table.readFromFile("../SetLib/cities.txt");
    /*table.print_table();*/
    cout << "\nЗадача п.7\n";
    find_route(table, cities::Львів, cities::Луцьк);
    find_route(table, cities::Житомир, cities::Львів);
    find_route(table, cities::Львів, cities::Київ);
    find_route(table, cities::Львів, cities::Вінниця);
    find_route(table, cities::Львів, cities::Львів);
    cout << "\nPress any button to continue...\n";
    cin.get();

    GuestTable T;
    cout << "Демонстрація - Мехеда Ксенія\n";
    cout << "\nЗадача п.6:\n";
    T.read_from_file("../SetLib/guests.txt");
    T.print_table(); 
    cout << "\nPress any button to continue...\n";
    cin.get();

    cout << "\n6.1, 6.2\n";
    T.visited_all(); 
    T.visited_the_least();
    cout << "\nPress any button to continue...\n";
    cin.get();
    cout << "\n6.3\n";
    T.circle_of_three();
    cout << "\nPress any button to continue...\n";
    cin.get();
    cout << "\n6.4\n";
    T.reverse_table().print_table();
    cout << "\nPress any button to continue...\n";
    cin.get();
    cout << "Демонстрація - Доманов Віталій\n";
    cout << "Задача п.1\n";
    analyze_ex("(2+2) * (a - b)");
    cout << "Задача п.3\n";
    string line = "Hello World! Hello to everyone!";
    cout << "3.1\n";
    first_enter(line);
    cout << "\n3.2\n";
    at_least_twice(line);
    cout << "3.3\n";
    only_once(line);
    cout << "\nPress any button to continue...\n";
    cin.get();
    cout << "Демонстрація - Шульгак Данило\n";
    cout << "\nЗадача п.5:\n";
    Set<Product> all_products = add_all_products(); 
    Set<Product> store1;
    store1.add(Product::Chesse).add(Product::Fish).add(Product::Bread).add(Product::Tea).add(Product::Water);
    Set<Product> store2;
    store2.add(Product::Salt).add(Product::Milk).add(Product::Fish).add(Product::Butter).add(Product::Chesse);
    Set<Product> common_products = common(store1, store2);
    cout << "Продукти які є у всіх магазинах\n ";
    common_products.print_all();

    Set<Product> any = any_product(store1, store2);
    cout << "Продукти які є хоча б в одному магазині\n ";
    any.print_all();

    Set<Product> notf = not_find(all_products, store1, store2);
    cout << "Продукти яких немає в жодному магазині\n ";
    notf.print_all();

    return 0;
}