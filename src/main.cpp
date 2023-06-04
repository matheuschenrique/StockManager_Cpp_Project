#include <iostream>
#include "product.h"
#include <list>

int main() {
    
    std::list<Product*> product_list;
    insert_product(product_list);
    print_list(product_list);
    search_by_code(product_list, 1);
    search_by_name(product_list, "oi");
    update_stock(product_list);
    print_list(product_list);
    return 0;
}