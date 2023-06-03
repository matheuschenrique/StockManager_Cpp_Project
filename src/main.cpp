#include <iostream>
#include "product.h"
#include <list>

int main() {
    
    std::list<Product*> product_list;
    insert_product(product_list);
    print_list(product_list);
    return 0;
}