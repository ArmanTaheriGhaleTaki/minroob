#include <iostream>
#include <cstdlib>
#include <ctime>
#include <time.h>
// #include <conio.h>
#include <windows.h>
struct field
{
    short int area;
    bool visited;
};
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
        if (field[x][y] != -1)
        {
            i++;
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
void gotoXY(short int x, short int y)
{
    static HANDLE h = NULL;
    if (!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = {x, y};
    SetConsoleCursorPosition(h, c);
}
short int main_menu()
{
    short int menu_item = 1, x = 7;
    bool running = true;
    gotoXY(18, 5);
    std::cout << "Mine Roob";
    gotoXY(18, 7);
    std::cout << "->";
    while (running)
    {
        gotoXY(20, 7);
        std::cout << "1) Play";
        gotoXY(20, 8);
        std::cout << "2) How to play";
        gotoXY(20, 9);
        std::cout << "Quit Program";
        system("pause>nul");                     // the >nul bit causes it the print no message
        if (GetAsyncKeyState(VK_DOWN) && x != 9) // down button pressed
        {
            gotoXY(18, x);
            std::cout << "  ";
            x++;
            gotoXY(18, x);
            std::cout << "->";
            menu_item++;
            continue;
        }
        if (GetAsyncKeyState(VK_UP) && x != 7) // up button pressed
        {
            gotoXY(18, x);
            std::cout << "  ";
            x--;
            gotoXY(18, x);
            std::cout << "->";
            menu_item--;
            continue;
        }
        if (GetAsyncKeyState(VK_RETURN))
        {
            std::cout << std::endl;
            return menu_item;
        }
    }
    return 0;
}
void play(short int **Field, int rows, int column, int mines)
{
    int x_posiont = 4, y_position = 0;
    std::cout << "Enter first player's name: \n";
    std::string player_1_name;
    std::getline(std::cin, player_1_name);
    std::cout << "Enter second player's name: \n";
    std::string player_2_name;
    std::getline(std::cin, player_2_name);
    int mine_collected_player_1 = 0;
    int mine_collected_player_2 = 0;
    bool running = true;
    bool round = true;
    while (running)
    {
        system("cls");
        std::cout << player_1_name << ": " << mine_collected_player_1 << "\n";
        std::cout << player_2_name << ": " << mine_collected_player_2 << "\n";
        if (round)
        {
            std::cout << "\n"
                      << player_1_name << "\'s turn\n";
            round = false;
        }
        else
        {
            std::cout << "\n"
                      << player_2_name << "\'s turn\n";
            round = true;
        }
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < column; j++)
            {
                if (Field[i][j] == -1)
                {
                    gotoXY(j + 4, i + 4);
                }
            }
        }
    }
}
void show_how_to_play();