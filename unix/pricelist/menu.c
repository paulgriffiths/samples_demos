/*
 *  menu functions
 *  ==============
 */

#include <stdio.h>

#include "util.h"

/*  Main menu options enumeration type  */

enum MenuOption {
    MENU_LIST = 1,
    MENU_ADD,
    MENU_DELETE,
    MENU_QUIT = 9
};

/*  Prints a menu and returns the user's choice  */

int get_menu_choice(void)
{
    printf("Select an option:\n");
    printf("1) List records\n");
    printf("2) Add record\n");
    printf("3) Delete record\n");
    printf("9) Quit\n");
    print_input_prompt();

    return get_integer();
}
