#ifndef MENU_H
#define MENU_H

enum class MainOptions {
    OPTION_EXIT = 0,
    OPTION_REGISTER_PRODUCT,
    OPTION_SEARCH_PRODUCT,
    OPTION_UPDATE_STOCK,
    OPTION_SHOW_PRODUCTS,
};

enum class SearchOptions {
    SEARCH_OPTION_BACK = 0,
    SEARCH_OPTION_NAME,
    SEARCH_OPTION_CODE,
};

MainOptions menu();
SearchOptions search_menu();
void splash();
void screen_divider();

#endif