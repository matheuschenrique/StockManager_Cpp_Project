#include <iostream>
#include <string>
#include <limits>
#include <sstream>
#include <iomanip>
#include "current_time.h"

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

struct tm *get_current_time() {
    time_t current_time = time(NULL);
    return localtime(&current_time);
}