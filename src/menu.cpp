#include <iostream>
#include <iomanip>
#include <limits>
#include "menu.h"

void screen_divider() {
    std::cout << std::setfill('-') << std::setw(100) << "";
    std::cout << std::setfill(' ') << std::endl;
}

MainOptions menu() {
    int option;
    std::cout << "Escolha uma das opcoes:\n";
    std::cout << "1 - Registrar novo produto\n";
    std::cout << "2 - Buscar produto\n";
    std::cout << "3 - Atualizar estoque\n";
    std::cout << "4 - Mostrar todos os produtos\n";
    std::cout << "0 - Sair\n";
    std::cout << "Opcao escolhida: ";
    while(!(std::cin >> option) || option < 0 || option > 4) {
        std::cout << "Entrada invalida, digite um valor valido: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cout << "\n";
    return static_cast<MainOptions>(option);
}

SearchOptions search_menu() {
    int option;
    std::cout << "Escolha uma das opcoes:\n";
    std::cout << "1 - Procurar por nome\n";
    std::cout << "2 - Procurar por codigo\n";
    std::cout << "0 - Voltar\n";
    std::cout << "Opcao escolhida: ";
    while(!(std::cin >> option) || option < 0 || option > 2) {
        std::cout << "Entrada invalida, digite um valor valido: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cout << "\n";
    return static_cast<SearchOptions>(option);
}

void splash() {
    std::cout << std::setw(22) << "\n\nWelcome to the system!\n";
    screen_divider();
    std::cout << "\n"; 
}