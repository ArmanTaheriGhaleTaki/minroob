#include <iostream>
#include <cstdlib>
#include <ctime>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <iomanip>
using std::vector;
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
struct myfield
{
    short int area;
    bool visited;
};
vector<vector<myfield>> Field(int rows, int column, int mines)
{
    srand(time(NULL));
    vector<vector<myfield>> field;
    vector<myfield> myrows;
    myfield temp;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < column; j++)
        {
            temp.area = 0;
            temp.visited = false;
            myrows.push_back(temp);
        }
        field.push_back(myrows);
        myrows.clear();
    }
    for (int i = 0; i <= mines;)
    {
        int x = rand() % rows;
        int y = rand() % column;
        if (field[x][y].area != -1)
        {
            i++;
            field[x][y].area = -1;
            for (int x_temp = x - 1; x_temp <= x + 1; x_temp++)
            {
                for (int y_temp = y - 1; y_temp <= y + 1; y_temp++)
                {
                    if (x_temp >= 0 && x_temp < rows && y_temp >= 0 && y_temp < column)
                    {
                        if (field[x_temp][y_temp].area != -1)
                        {
                            field[x_temp][y_temp].area++;
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
    {
         h = GetStdHandle(STD_OUTPUT_HANDLE);
    }
    COORD c = {x, y};
    SetConsoleCursorPosition(h, c);
}
short int main_menu()
{
    short int menu_item = 1;
    short int default_x = 18, default_y = 7; 
    bool running = true;
    bool first_time = true ;
    bool needed = false ; 
    while (running)
    {            // the >nul bit causes it the print no message
        if(first_time){
            system("cls") ;
            gotoXY(18, 5);
            std::cout << "Mine Roob";
            gotoXY(18,7) ;
            std::cout<<"->" ;
            gotoXY(20, 7);
            std::cout << "1) Play";
            gotoXY(20, 8);
            std::cout << "2) How to play";
            gotoXY(20, 9);
            std::cout << "3) Quit Program";  
            first_time = false ; 
        }
        else {
           if(needed==true){
            system("cls") ;
            gotoXY(18, 5);
            std::cout << "Mine Roob";
            gotoXY(default_x, default_y);
            std::cout<<"->" ;
            gotoXY(20, 7);
            std::cout << "1) Play";
            gotoXY(20, 8);
            std::cout << "2) How to play";
            gotoXY(20, 9);
            std::cout << "3) Quit Program";
            needed = false ; 
           }
        }
   int ch ;
   ch = _getch ();
   if (ch == 0 || ch == 224)
    {
    int gch = _getch () ; 
    switch (gch)
    {
        case KEY_UP:
            /* Code for up arrow handling */
            default_y--;
            menu_item--;
            if(default_y<7){
                default_y = 9 ;
                menu_item = 3 ; 
            }
            needed = true ;
            break;

        case KEY_DOWN:
            /* Code for down arrow handling */
            default_y++;
            menu_item++;
            if(default_y>9)
            {
                menu_item = 1 ; 
                default_y = 7 ;
            }
            needed = true ; 
            break;
        case KEY_RIGHT:
            running = false ; 
            break;
        default:
            needed = true ; 
            break ; 

        /* ... etc ... */
    }
}
    else {
        if(ch == 13){
            running = false ; 
        }
        
    }
    }
    system("cls") ; 
    return menu_item;
}
void play(vector<vector<myfield>> Field, int rows, int column, int mines)
{
    int y_position = 4, x_position = 2;
    std::cout << "Enter first player's name: \n";
    std::string player_1_name;
    std::getline(std::cin, player_1_name);
    std::cout << "Enter second player's name: \n";
    std::string player_2_name;
    std::getline(std::cin, player_2_name);
    int mine_collected_player_1 = 0;
    int mine_collected_player_2 = 0;
    bool running = true;
    bool running_arrowkey = true;
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
                if (Field[i][j].visited == 0)
                {
                    std::cout << std::setw(5) << std::setfill(' ') << "#";
                }
                else
                {
                    if (Field[i][j].area == -1)
                    {
                        std::cout << std::setw(5) << std::setfill(' ') << "*";
                    }
                    else
                    {
                        std::cout << std::setw(5) << std::setfill(' ') << Field[i][j].area;
                    }
                }
            }
            std::cout << std::endl;
        }
        gotoXY(x_position, y_position);
        std::cout << "->";
        while (running_arrowkey)
        {
            system("pause>nul");                                     // the >nul bit causes it the print no message
            if (GetAsyncKeyState(VK_DOWN) && y_position != 4 + rows-1) // down button pressed
            {
                gotoXY(x_position, y_position);
                std::cout << "  ";
                y_position++;
                gotoXY(x_position, y_position);
                std::cout << "->";
                continue;
            }
            if (GetAsyncKeyState(VK_UP) && y_position != 4) // up button pressed
            {
                gotoXY(x_position, y_position);
                std::cout << "  ";
                y_position--;
                gotoXY(x_position, y_position);
                std::cout << "->";
                continue;
            }
            if (GetAsyncKeyState(VK_RIGHT) && x_position != (2 + 5 * column)) // right button pressed
            {
                gotoXY(x_position, y_position);
                std::cout << "  ";
                x_position += 5;
                gotoXY(x_position, y_position);
                std::cout << "->";
                continue;
            }
            if (GetAsyncKeyState(VK_LEFT) && x_position != 2) // left button pressed
            {
                gotoXY(x_position, y_position);
                std::cout << "  ";
                x_position -= 5;
                gotoXY(x_position, y_position);
                std::cout << "->";
            }
            if (GetAsyncKeyState(VK_RETURN))
            {
                if (Field[y_position][x_position].visited == 0)
                {
                    Field[y_position][x_position].visited = 1;
                    running_arrowkey = false;
                }
            }
        }
    }
}
void show_how_to_play(){
    std::cout << "how to play" <<std::endl; 
}