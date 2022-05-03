#include <iostream>
#include "game.h"
#include <iomanip>
#include <vector>
int main()
{
    short int menu_item = main_menu();
    int rows = 8;
    int column = 7;
    int mines = 10;
    vector<vector<myfield>> field;
    field = Field(rows, column, mines);
    switch (menu_item)
    {
    case 1:
        play(field,rows,column,mines);
        break;
    case 2: 
        // show_how_to_play();
        break;
    case 3:
        // return 0;
        // break;
    return 0;
}
}