#include <iostream>
#include <sstream>
#include <iomanip>
#include "product.h"

void insert_date(tm *destiny) {
    string date_string;

    do {
        std::getline(std::cin, date_string);

        std::istringstream date_stream(date_string);
        std::tm temp = {};

        date_stream >> std::get_time(&temp, "%d/%m/%Y");

        if (date_stream.fail()) {
            std::cout << "Formato de data incorreto. Tente novamente." << std::endl;
            continue;
        }

        auto time_point = std::mktime(&temp);

        if (time_point == -1) {
            std::cout << "Data inválida. Tente novamente." << std::endl;
            continue;
        }

        *destiny = *std::localtime(&time_point);
        break;
    } while(1);
}

Product::Product(int code, string &name, float cost_price) 
    : code(code), name(name), cost_price(cost_price) { }

Book::Book(int code, string &name, float cost_price) 
    : Product(code, name, cost_price) {  }

void Book::set_cover_style() {
    int cover;
    cout << "O livro possui capa dura? ";
    while(!(cin >> cover) || cover < 0 || cover > 1) {
        cout << "Entrada invalida, digite um valor valido: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    cover_style = cover;
}

Electronics::Electronics(int code, string &name, float cost_price) 
    : Product(code, name, cost_price) { }

void Electronics::set_manufacturing_date() {
    cout << "Digite a data de fabricacao do produto (no formato DD/MM/YYYY): ";
    insert_date(manufacturing_date);
}

Clothing::Clothing(int code, string &name, float cost_price) 
    : Product(code, name, cost_price) { }

Food::Food(int code, string &name, float cost_price) 
    : Product(code, name, cost_price) { }

void Food::set_expiration_date() {
    cout << "Digite a data de validade do produto (no formato DD/MM/YYYY): ";
    insert_date(expiration_date);
}

Other::Other(int code, string &name, float cost_price) 
    : Product(code, name, cost_price) { }

void insert_product(list<Product*> &list) {
    string name;
    int type;
    int quantity;
    float cost_price;

    cout << "Digite o nome do produto: ";
    getline(cin, name);

    cout << "Digite a quantidade do produto em estoque: ";
    while(!(cin >> quantity) || (quantity < 0)) {
        cout << "Entrada invalida, digite um valor valido: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    cout << "Digite a quantidade do produto em estoque: ";
    while(!(cin >> cost_price) || (cost_price <= 0.0f)) {
        cout << "Entrada invalida, digite um valor valido: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    cout << "Escolha o tipo de produto:\n";
    cout << "1 - Livro\n";
    cout << "2 - Eletronicos\n";
    cout << "3 - Vestuario\n";
    cout << "4 - Alimentos\n";
    cout << "5 - Outros\n";
    cout << "Opcao escolhida: ";
    while(!(cin >> type) || (type < 1) || (type > 5)) {
        cout << "Entrada invalida, digite um valor valido: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    Product *product = nullptr;

    switch (type)
    {
    case 1:
        {  
            Book* book = new Book(list.size() + 1, name, cost_price);
            book->set_cover_style();
            product = book;
        }
        break;
    case 2:
        {
            Electronics* electronics = new Electronics(list.size() + 1, name, cost_price);
            electronics->set_manufacturing_date();
            product = electronics;
        }
        break;
    case 3:
        {
            Clothing* clothing = new Clothing(list.size() + 1, name, cost_price);
            clothing->set_size();
            product = clothing;
        }
        break;
    case 4:
        {
            Food* food = new Food(list.size() + 1, name, cost_price);
            food->set_expiration_date();
            product = food;
        }
        break;
    case 5:
        product = new Other(list.size() + 1, name, cost_price);
        break;
    default:
        break;
    }

    product->calculate_total_price();

    list.push_back(product);
}
