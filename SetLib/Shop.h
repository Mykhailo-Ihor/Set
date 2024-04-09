#pragma once
#include "Set.h"
enum class Product
{
    Bread,
    Butter,
    Milk,
    Chesse,
    Meat,
    Fish,
    Salt,
    Sugar,
    Tea,
    Coffee,
    Water
};
std::ostream& operator<<(std::ostream& out, Product product)
{
    std::string prod[] = { "Bread", "Butter", "Milk", "Chesse", "Meat", "Fish", "Salt", "Sugar", "Tea", "Coffee", "Water" };

    out << prod[static_cast<int>(product)];
    return out;
}
Set<Product> add_all_products()
{
    Set<Product> all_products;
    all_products.add(Product::Bread).add(Product::Butter).add(Product::Chesse).add(Product::Coffee).add(Product::Fish).add(Product::Meat).add(Product::Milk).add(Product::Salt).add(Product::Sugar).add(Product::Tea).add(Product::Water);
    return all_products;
}
Set<Product> common(Set<Product>& A, Set<Product>& B)
{
    return A.intersect(B);
}
Set<Product> any_product(Set<Product>& A, Set<Product>& B)
{
    return A.set_union(B);
}
Set<Product> not_find(Set<Product>& A, Set<Product>& B, Set<Product>& C)
{
    return A.differ(B.set_union(C));
}
