#include <iostream>
#include <list>
#include "product.h"
#include "menu.h"

int main() {
    std::list<Product*> product_list;
    MainOptions option;
    do{
        splash();
        option = menu();

        switch (option) {
            case MainOptions::OPTION_REGISTER_PRODUCT:
                insert_product(product_list);
                break;
            case MainOptions::OPTION_SEARCH_PRODUCT:
                search_product(product_list);
                break;
            case MainOptions::OPTION_UPDATE_STOCK:
                update_stock(product_list);
                break;
            case MainOptions::OPTION_SHOW_PRODUCTS:
                list_print(product_list);
                break;
            case MainOptions::OPTION_EXIT:
                std::cout << "Saindo...\n";
                break;
            default:
                std::cout << "Opcao invalida!\n";
                break;
        }
    } while (option != MainOptions::OPTION_EXIT);
    return 0;
}