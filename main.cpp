#include <iostream>
#include "game.h"
#include <iomanip>
#include <vector>
#include <map>
int main()
{
    int rows = 8;
    int column = 7;
    int mines = 12;
    vector<vector<myfield>> field;
    field = Field(rows, column, mines);
    switch (main_menu())
    {
    case 1:
        play(field,rows,column,mines);
        break;
    case 2:
        show_how_to_play();
        break;
    case 3:
        return 0;
        break;
    default:
        std::cout << "there is a problem with our program" << std::endl  ; 
}
return 0;
}