#include <iostream>
#include <cstdlib>
#include <ctime>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <iomanip>
#include <map>
#include <tchar.h>
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
vector<vector<myfield>> global_field ; 
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
    for (int i = 0; i < mines;)
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
    bool overwriting_is_needed = false ; 
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
    while (running)
    {     
           if(overwriting_is_needed==true){
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
            overwriting_is_needed = false ; 
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
            overwriting_is_needed = true ;
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
            overwriting_is_needed = true ; 
            break;
        case KEY_RIGHT:
            running = false ; 
            break;
        default: 
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
void print_field(vector<vector<myfield>> Field, int rows, int column){
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
                    else if(Field[i][j].area == 0)  {
                        std::cout << std::setw(5) << std::setfill(' ') << "O";
                    }
                    else
                    {
                        std::cout << std::setw(5) << std::setfill(' ') << Field[i][j].area;
                    }
                }
            }
            std::cout << std::endl;
        }
}

void if_area_is_zero(int field_row , int field_column , int rows , int column){
                            int previous_row = 0 , previous_column = 0 , next_row = 0 , next_column = 0 ;
                            std::cout << field_row << field_column << std::endl ;
                            if(field_row==rows-1){
                                previous_row = field_row -1 ; 
                                next_row = field_row ; 
                            }
                            else if(field_row==0){
                                previous_row = field_row ; 
                                next_row = field_row + 1 ; 
                            }
                            else {
                                previous_row = field_row -1 ; 
                                next_row = field_row + 1 ; 
                            }
                            if(field_column==column-1){
                                previous_column = field_column -1 ; 
                                next_column = field_column ; 
                            }
                            else if(field_column==0){
                                previous_column = field_column ; 
                                next_column = field_column + 1 ; 
                            }
                            else {
                                previous_column = field_column -1 ; 
                                next_column = field_column + 1 ; 
                            }
                            for(int k = previous_row ; k<=next_row ; k++){
                                for(int p = previous_column ; p<=next_column ; p++){                                    
                                        
                                        if(k!=field_row || p!=field_column){
                                         if(global_field[k][p].area==0){
                                            if(global_field[k][p].visited==0){
                                                global_field[k][p].visited = 1; 
                                                if_area_is_zero(k,p , rows , column) ; 
                                            }
                                            
                                         }
                                         else {
                                            global_field[k][p].visited = 1 ;
                                         }        
                                        }
                                       
                                }
                            }
}
void play(vector<vector<myfield>> Field, int rows, int column, int mines)
{
    int y_position = 4, x_position = 2;
    int field_row = 0, field_column = 0 ; 
    bool status_players_name = false ;
    std::string player_1_name;
    std::string player_2_name;
    while(status_players_name == false) {
          std::cout << "\npresss ESC or x to exit the game when playing ... \n";
          std::cout << "Enter first player's name: \n";    
          std::getline(std::cin, player_1_name);
          std::cout << "Enter second player's name: \n";
          std::getline(std::cin, player_2_name);
          if(player_1_name == player_2_name ){
                system("cls") ;
                std::cout << "ERROR! | Names are the same, please enter different names.\n";
          }
          else {
                status_players_name = true ;
          }
    }
    int mine_collected_player_1 = 0;
    int mine_collected_player_2 = 0;
    std::map<bool,int> players_status ; 
    players_status[true] = mine_collected_player_1;
    players_status[false] = mine_collected_player_2;
    bool running = true;
    bool running_arrowkey;
    bool round = true;
    while (running)
    {
        system("cls");
        std::cout << player_1_name << ": " << players_status[true] << "\n";
        std::cout << player_2_name << ": " << players_status[false] << "\n";
        if(players_status[true]==(mines/2)+1 || players_status[false] == (mines/2)+1 ){
             if(players_status[true]==players_status[false]){
               std::cout << "both of you are winner :D " ; 
             }
             else if(players_status[true]>players_status[false]){
               std::cout << "player " << player_1_name << " is winner :)" << std::endl ; 
             }
             else {
              std::cout << "player " << player_2_name << " is winner :)" << std::endl ; 
             }
             running = false ; 
        }
        else {
                   if (round)
        {
            std::cout << "\n"<< player_1_name << "\'s turn\n";
        }
        else
        {
            std::cout << "\n"<< player_2_name << "\'s turn\n";
        }
        print_field(Field , rows, column) ;
        gotoXY(x_position, y_position);
        std::cout << "->";
        running_arrowkey = true ; 
        while (running_arrowkey)
        {
        int ch ;
        ch = _getch ();
        if (ch == 0 || ch == 224)
        {
        int gch = _getch () ; 
        switch (gch)
        {
        case KEY_UP:
            gotoXY(x_position, y_position);
            std::cout << "  ";
            y_position--;
            field_row--;
            if(y_position<4){
                y_position+=rows ;
                field_row = rows - 1 ; 
            }
            gotoXY(x_position, y_position);
            std::cout << "->";
            break;
        case KEY_DOWN:
                gotoXY(x_position, y_position);
                std::cout << "  ";
                y_position++;
                field_row++ ; 
                if(y_position>(3+rows)){
                 y_position=4 ; 
                 field_row = 0 ;
                }
                gotoXY(x_position, y_position);
                std::cout << "->";
                break;
        case KEY_RIGHT:
            gotoXY(x_position, y_position);
            std::cout << "  ";
            x_position += 5;
            field_column++ ; 
            if(x_position>(2+(column-1)*5)){
                 x_position=2 ; 
                 field_column = 0 ;
            }
            gotoXY(x_position, y_position);
            std::cout << "->";
            break;
        case KEY_LEFT:
                gotoXY(x_position, y_position);
                std::cout << "  ";
                x_position -= 5;
                field_column-- ; 
                if(x_position<2){
                  x_position = (2+(column-1)*5) ; 
                  field_column = column-1 ; 
                }
                gotoXY(x_position, y_position);
                std::cout << "->";
                break;
        default: 
            break ; 

        /* ... etc ... */
    }
}
    else {
        if(ch == 13){
            if (Field[field_row][field_column].visited == 0)
                {
                    Field[field_row][field_column].visited = 1;
                    if(Field[field_row][field_column].area!=-1){
                        if(Field[field_row][field_column].area == 0){
                           Field[field_row][field_column].visited = 0;
                           global_field = Field ; 
                           if_area_is_zero(field_row , field_column , rows , column)  ;
                           Field = global_field ;
                           Field[field_row][field_column].visited = 1;
                        }
                        x_position = 2 ; 
                        y_position = 4 ;
                        field_row = 0 ; 
                        field_column = 0 ;
                        if(round){
                            round = false ; 
                        }
                        else {
                            round = true ; 
                        }
                    }
                    else {
                        if(round){
                            players_status[true] = players_status[true]+1 ; 
                        }
                        else {
                            players_status[false] = players_status[false]+1 ; 
                        }
                    }
                    running_arrowkey = false;
                }
        }
        else {
            if(ch == 27 || ch==120){
                running_arrowkey = false ;
                running = false ;
                system("cls") ; 
                std::cout << "bye bye game :)" ; 
            }
        }
        
    }
        }
        }
    }
}
void show_how_to_play(){
        ShellExecute(NULL, NULL, _T("www.just-fucking-google.it/?s=how%20to%20play%20minesweeper%20PVP%3F&e=finger"), NULL, NULL, SW_SHOWNORMAL);
}