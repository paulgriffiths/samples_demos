/*
 *  menu functions
 *  ==============
 */

#ifndef PG_PRICELIST_MENU_H
#define PG_PRICELIST_MENU_H

/*  Main menu options enumeration type  */

enum MenuOption {
    MENU_LIST = 1,
    MENU_ADD,
    MENU_DELETE,
    MENU_QUIT = 9
};

int get_menu_choice(void);

#endif      /*  PG_PRICELIST_MENU_H  */
