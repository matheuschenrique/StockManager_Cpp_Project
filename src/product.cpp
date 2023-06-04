#include <iostream>
#include <sstream>
#include <iomanip>
#include "product.h"

Product::Product(int code, const std::string &name, float cost_price)
    : code(code), name(name), cost_price(cost_price) { }

void Product::calculate_total_price() {}
void Product::set_details() {}
void Product::print() const {}

bool Product::operator==(const Product &other) const {
    return (code == other.code) || (name == other.name);
}

Book::Book(int code, const std::string &name, float cost_price)
    : Product(code, name, cost_price) { }

void Book::set_cover_style() {
    int cover;
    std::cout << "O livro possui capa dura? ";
    while(!(std::cin >> cover) || cover < 0 || cover > 1) {
        std::cout << "Entrada invalida, digite um valor valido: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    cover_style = cover;
}

void Book::calculate_total_price() {
    sale_price = cost_price;
}

void Book::set_details() {
    set_cover_style();
}

void Book::print() const {
    std::cout << code << " " << name << " " << quantity;
}

Electronics::Electronics(int code, const std::string &name, float cost_price)
    : Product(code, name, cost_price), manufacturing_date(new std::tm()) {}

void Electronics::set_manufacturing_date() {
    std::cout << "Digite a data de fabricacao do produto (no formato DD/MM/YYYY): ";
    insert_date(manufacturing_date);
}

void Electronics::set_details() {
    set_manufacturing_date();
}

void Electronics::calculate_total_price() {
    sale_price = cost_price;
}

void Electronics::print() const {
    std::cout << code << " " << name << " " << quantity;
}

Electronics::~Electronics() {
    delete manufacturing_date;
}

Clothing::Clothing(int code, const std::string &name, float cost_price)
    : Product(code, name, cost_price) { }

void Clothing::set_size() {
    std::cout << "set size \n";
}

void Clothing::set_details() {
    set_size();
}

void Clothing::calculate_total_price() {
    sale_price = cost_price;
}

void Clothing::print() const {
    std::cout << code << " " << name << " " << quantity;
}

Food::Food(int code, const std::string &name, float cost_price)
    : Product(code, name, cost_price), expiration_date(new std::tm()) {}

void Food::set_expiration_date() {
    std::cout << "Digite a data de validade do produto (no formato DD/MM/YYYY): ";
    insert_date(expiration_date);
}

void Food::set_details() {
    set_expiration_date();
}

void Food::calculate_total_price() {
    sale_price = cost_price;
}

void Food::print() const {
    std::cout << code << " " << name << " " << quantity;
}

Food::~Food() {
    delete expiration_date;
}

Other::Other(int code, const std::string &name, float cost_price)
    : Product(code, name, cost_price) { }

void Other::set_details() { }

void Other::calculate_total_price() {
    sale_price = cost_price;
}

void Other::print() const {
    std::cout << code << " " << name << " " << quantity;
}

void insert_date(std::tm *destiny) {
    std::string date_string;

    do {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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

void insert_product(std::list<Product*> &list) {
    std::string name;
    int type;
    int quantity;
    float cost_price;

    std::cout << "Digite o nome do produto: ";
    std::getline(std::cin, name);

    std::cout << "Digite a quantidade do produto em estoque: ";
    while(!(std::cin >> quantity) || (quantity < 0)) {
        std::cout << "Entrada invalida, digite um valor valido: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Digite o preco de custo do produto: ";
    while(!(std::cin >> cost_price) || (cost_price <= 0.0f)) {
        std::cout << "Entrada invalida, digite um valor valido: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Escolha o tipo de produto:\n";
    std::cout << "1 - Livro\n";
    std::cout << "2 - Eletronicos\n";
    std::cout << "3 - Vestuario\n";
    std::cout << "4 - Alimentos\n";
    std::cout << "5 - Outros\n";
    std::cout << "Opcao escolhida: ";
    while(!(std::cin >> type) || (type < 1) || (type > 5)) {
        std::cout << "Entrada invalida, digite um valor valido: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    Product* product = nullptr;

    switch (static_cast<ProductType>(type))
    {
        case ProductType::Book:
        {
            product = new Book(list.size() + 1, name, cost_price);
            break;
        }
        case ProductType::Electronics:
        {
            product = new Electronics(list.size() + 1, name, cost_price);
            break;
        }
        case ProductType::Clothing:
        {
            product = new Clothing(list.size() + 1, name, cost_price);
            break;
        }
        case ProductType::Food:
        {
            product = new Food(list.size() + 1, name, cost_price);
            break;
        }
        case ProductType::Other:
        {
            product = new Other(list.size() + 1, name, cost_price);
            break;
        }
        default:
            break;
    }

    if (product != nullptr) {
        product->set_details();
        product->calculate_total_price();
        product->quantity = quantity;
        list.push_back(product);
    }
}

void print_list(const std::list<Product*> &list) {
    std::cout << "Lista de produtos:" << std::endl;

    for (const auto &product : list) {
        product->print();
        std::cout << std::endl;
    }
}

Product *search_by_name(std::list<Product*> &list, const std::string &name) {
    Product p(0, name, 0.0f);
    auto it = std::find_if(list.begin(), list.end(), [&](Product* product) {
        return product->name == name; });
    
    if (list.end() != it) {
        (*it)->print();
        return *it;
    }
    std::cout << "Produto nao encontrado\n";
    return nullptr;
}

Product *search_by_code(std::list<Product*> &list, const int code) {
    Product p(code, "", 0.0f);
    auto it = std::find_if(list.begin(), list.end(), [&](Product* product) { 
        return product->code == code; });
    
    if (list.end() != it) {
        (*it)->print();
        return *it;
    }
    
    // busca sem iterator
    // for (const auto &product : list) {
    //     if(*product == p) {
    //         product->print();
    //         return product;
    //     }
    // }

    std::cout << "Produto nao encontrado\n";
    return nullptr;
}

void update_product(Product *product) {
    std::cout << "Digite a quantidade do produto em estoque: ";
    int quantity {};
    while(!(std::cin >> quantity) || quantity < 0) {
        std::cout << "Entrada invalida, digite um valor valido: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    product->quantity = quantity;
}

void update_stock(std::list<Product*> &list) {
    int code {};
    std::cout << "Digite o codigo do produto: ";
    while(!(std::cin >> code) || code < 0) {
        std::cout << "Entrada invalida, digite um valor valido: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    Product *product = search_by_code(list, code);
    if (product != nullptr) {
        update_product(product);
    }
}