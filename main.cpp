#include <iostream>
#include "game.h"
#include <iomanip>

int main()
{
    int rows = 8;
    int column = 7;
    int mines = 10;
    short int **field = 0;
    field = Field(rows, column, mines);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < column; j++)
        {
            std::cout << std::setw(2) << field[i][j] << "\t";
        }
        std::cout << std::endl<< std::endl;
    }
    return 0;
}