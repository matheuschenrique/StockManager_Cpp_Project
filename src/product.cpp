#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <unordered_map>
#include <limits>
#include <iomanip>
#include "product.h"

Product::Product(int code, const std::string &name, float cost_price, float tax)
    : code(code), name(name), cost_price(cost_price), tax(tax) { }

void Product::calculate_total_price() {
    sale_price = cost_price * (1 + DEFAULT_TAX);
}
void Product::set_details() {}
void Product::print() const {}

bool Product::operator==(const Product &other) const {
    return (code == other.code) || (name == other.name);
}

Book::Book(int code, const std::string &name, float cost_price)
    : Product(code, name, cost_price, BOOK_TAX) { }

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
    sale_price = cost_price * (1 + tax + (0.1f * cover_style));
}

void Book::set_details() {
    set_cover_style();
}

void Book::print() const {
    std::cout << std::setw(20) << std::left << name 
                << std::setw(20) << "Livro"
                << std::setw(10) << code 
                << std::setw(10) << quantity
                << std::setw(10) << cost_price
                << std::setw(10) << sale_price
                << "Capa dura: " << std::setw(20) << cover_style;
    screen_divider();
}

Electronics::Electronics(int code, const std::string &name, float cost_price)
    : Product(code, name, cost_price, ELECTRONICS_TAX), manufacturing_date(new std::tm()) {}

void Electronics::set_manufacturing_date() {
    std::cout << "Digite a data de fabricacao do produto (no formato DD/MM/YYYY): ";
    insert_date(manufacturing_date);
}

void Electronics::set_details() {
    set_manufacturing_date();
}

void Electronics::calculate_total_price() {
    int diff = std::difftime(std::mktime(get_current_time()), std::mktime(manufacturing_date)) / (60 * 60 * 24);
    
    if (diff <= static_cast<int>(YEAR_IN_DAYS / 2)) 
        sale_price = cost_price * (1 + ELECTRONICS_TAX + 0.1f);
    else if (diff <= YEAR_IN_DAYS * 2)
        sale_price = cost_price * (1 + ELECTRONICS_TAX + 0.05f);
    else 
        sale_price = cost_price * (1 + ELECTRONICS_TAX);
}

void Electronics::print() const {
    std::cout << std::setw(20) << std::left << name 
                << std::setw(20) << "Eletronico"
                << std::setw(10) << code 
                << std::setw(10) << quantity
                << std::setw(10) << cost_price
                << std::setw(10) << sale_price
                << "Fabricacao: " 
                << manufacturing_date->tm_mday << "/" 
                << manufacturing_date->tm_mon + 1 << "/"
                << manufacturing_date->tm_year + 1900 << std::endl;
    screen_divider();
}

Electronics::~Electronics() {
    delete manufacturing_date;
}

Clothing::Clothing(int code, const std::string &name, float cost_price)
    : Product(code, name, cost_price, CLOTHING_TAX) { }

void Clothing::set_size() {
    std::string size_aux;
    std::cout << "Digite o tamanho da roupa (P, M, G, GG, XG, XXG): ";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    do {
        std::getline(std::cin, size_aux);

        if (size_aux.compare("P") == 0) {
            size = SizeOptions::Size_P;
        }
        else if (size_aux.compare("M") == 0) {
            size = SizeOptions::Size_M;
        }
        else if (size_aux.compare("G") == 0) {
            size = SizeOptions::Size_G;
        }
        else if (size_aux.compare("GG") == 0) {
            size = SizeOptions::Size_GG;
        }
        else if (size_aux.compare("XG") == 0) {
            size = SizeOptions::Size_XG;
        }
        else if (size_aux.compare("XXG") == 0) {
            size = SizeOptions::Size_XXG;
        }
        else {
            std::cout << "Entrada invalida, digite um valor valido: ";
            continue;
        }
        break;
    } while (1);
}

void Clothing::set_details() {
    set_size();
}

std::string Clothing::get_size_from_int(SizeOptions size_int) const {
    static const std::unordered_map<SizeOptions, std::string> size_map = {
        { SizeOptions::Size_P, "P" },
        { SizeOptions::Size_M, "M" },
        { SizeOptions::Size_G, "G" },
        { SizeOptions::Size_GG, "GG" },
        { SizeOptions::Size_XG, "XG" },
        { SizeOptions::Size_XXG, "XXG" }
    };

    return size_map.at(size_int);
}

void Clothing::calculate_total_price() {
    switch (size)
    {
    case SizeOptions::Size_P:
        sale_price = cost_price * (1 + CLOTHING_TAX + 0.02f);
        break;
    case SizeOptions::Size_M:
        sale_price = cost_price * (1 + CLOTHING_TAX + 0.04f);
        break;
    case SizeOptions::Size_G:
        sale_price = cost_price * (1 + CLOTHING_TAX + 0.06f);
        break;
    case SizeOptions::Size_GG:
        sale_price = cost_price * (1 + CLOTHING_TAX + 0.08f);
        break;
    case SizeOptions::Size_XG:
        sale_price = cost_price * (1 + CLOTHING_TAX + 0.19f);
        break;
    case SizeOptions::Size_XXG:
        sale_price = cost_price * (1 + CLOTHING_TAX + 0.12f);
        break;
    default:
        break;
    }
}

void Clothing::print() const {
    std::cout << std::setw(20) << std::left << name 
                << std::setw(20) << "Roupa"
                << std::setw(10) << code 
                << std::setw(10) << quantity
                << std::setw(10) << cost_price
                << std::setw(10) << sale_price
                << "Tamanho: " << std::setw(20) << get_size_from_int(size) << std::endl;
    screen_divider();
}

Food::Food(int code, const std::string &name, float cost_price)
    : Product(code, name, cost_price, FOOD_TAX), expiration_date(new std::tm()) {}

void Food::set_expiration_date() {
    std::cout << "Digite a data de validade do produto (no formato DD/MM/YYYY): ";
    insert_date(expiration_date);
}

void Food::set_details() {
    set_expiration_date();
}

void Food::calculate_total_price() {
    int diff = std::difftime(mktime(expiration_date), std::mktime(get_current_time())) / (60 * 60 * 24);
    if (diff <= 10) 
        sale_price = cost_price * (1 + FOOD_TAX);
    else if (diff <= 30) 
        sale_price = cost_price * (1 + FOOD_TAX + 0.05f);
    else if (diff <= 90) 
        sale_price = cost_price * (1 + FOOD_TAX + 0.1f);
    else
        sale_price = cost_price * (1 + FOOD_TAX + 0.15f);
}

void Food::print() const {
    std::cout << std::setw(20) << std::left << name 
                << std::setw(20) << "Alimento"
                << std::setw(10) << code 
                << std::setw(10) << quantity
                << std::setw(10) << cost_price
                << std::setw(10) << sale_price
                << "Validade: " 
                << expiration_date->tm_mday << "/" 
                << expiration_date->tm_mon + 1 << "/"
                << expiration_date->tm_year + 1900 << std::endl;
    screen_divider();
}

Food::~Food() {
    delete expiration_date;
}

Other::Other(int code, const std::string &name, float cost_price)
    : Product(code, name, cost_price, OTHER_TAX) { }

void Other::print() const {
    std::cout << std::setw(20) << std::left << name 
                << std::setw(20) << "Outro"
                << std::setw(10) << code 
                << std::setw(10) << quantity
                << std::setw(10) << cost_price
                << std::setw(10) << sale_price << std::endl;
    screen_divider();
}

void insert_product(std::list<Product*> &list) {
    std::string name;
    int type;
    int quantity;
    float cost_price;

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Digite o nome do produto: ";
    while(!(std::cin >> name) || name.empty()) {
        std::cout << "Entrada invalida, digite um valor valido: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

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

void print_header() {
    std::cout << std::setprecision(2) << std::fixed;
    screen_divider();
    std::cout << std::setw(20) << std::left << "Nome"
                << std::setw(20) << "Tipo"
                << std::setw(10) << "Codigo" 
                << std::setw(10) << "Qtd"
                << std::setw(10) << "Custo"
                << std::setw(10) << "Venda"
                << std::setw(20) << "Info" << std::endl;
    screen_divider();
}

void list_print(const std::list<Product*> &list) {
    print_header();

    for (const auto &product : list) {
        product->print();
    }
}

Product *search_by_name(std::list<Product*> &list, const std::string &name) {
    Product p(0, name, 0.0f, 0.0f);
    auto it = std::find_if(list.begin(), list.end(), [&](Product* product) {
        return product->name == name; });
    
    if (list.end() != it) {
        screen_divider();
        (*it)->print();
        return *it;
    }
    std::cout << "Produto nao encontrado\n";
    return nullptr;
}

Product *search_by_code(std::list<Product*> &list, const int code) {
    Product p(code, "", 0.0f, 0.0f);
    auto it = std::find_if(list.begin(), list.end(), [&](Product* product) { 
        return product->code == code; });
    
    if (list.end() != it) {
        screen_divider();
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

void search_product(std::list<Product*> &list) {
    std::string name;
    int code;
    SearchOptions option;

    do {
        option = search_menu();
        switch (option) {
            case SearchOptions::SEARCH_OPTION_NAME:
                std::cout << "Digite o nome do produto: ";
                while(!(std::cin >> name) || name.empty()) {
                    std::cout << "Entrada invalida, digite um valor valido: ";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                (void)search_by_name(list, name);
                break;
            case SearchOptions::SEARCH_OPTION_CODE:
                std::cout << "Digite o codigo do produto: ";
                while(!(std::cin >> code) || code < 0) {
                    std::cout << "Entrada invalida, digite um valor valido: ";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                (void)search_by_code(list, code);
                break;
            case SearchOptions::SEARCH_OPTION_BACK:
            default:
                break;
        }
    } while (option != SearchOptions::SEARCH_OPTION_BACK);
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