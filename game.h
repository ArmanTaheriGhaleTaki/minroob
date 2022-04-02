#include <iostream>
#include <cstdlib>
#include <ctime>
#include <time.h>
short int **Field(int rows, int column, int mines)
{
    srand(time(NULL));
    short int **field = new short int *[rows];
    for (int i = 0; i < rows; i++)
    {
        field[i] = new short int[column];
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < column; j++)
        {
            field[i][j] = 0;
        }
    }
    for (int i = 0; i <= mines;)
    {
        int x = rand() % rows;
        int y = rand() % column;
        if (field[x][y] == 0)
        {
            i--;
            field[x][y] = -1;
            for (int x_temp = x - 1; x_temp <= x + 1; x_temp++)
            {
                for (int y_temp = y - 1; y_temp <= y + 1; y_temp++)
                {
                    if (x_temp >= 0 && x_temp < rows && y_temp >= 0 && y_temp < column)
                    {
                        if (field[x_temp][y_temp] != -1)
                        {
                            field[x_temp][y_temp]++;
                        }
                    }
                }
            }
        }
    }
    return field;
}