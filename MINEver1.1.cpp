/* mine ver1.1 */
// 2019/02/03
// Create by Eric W.
#include <stdio.h>
#include <iostream>
#include <conio.h>
//#include <cstdlib>
#include "utilwin32.h"
#include<time.h>

#define BOUNDARY -2
#define MINE -1

char *BNUM[10]={"��","��","��","��","��","��","��","��","��","��"};

class field
{
  private:
    int data[22][22];
    bool signaled[22][22];
    bool opened[22][22];
    bool gamepause;
    int mines, opens;

    void makenumber(int x, int y)
    {
        for (int j = y - 1; j <= y + 1; j++)
        {
            for (int i = x - 1; i <= x + 1; i++)
            {
                if (data[i][j] > -1) //EXCLUDE -1 -2 (BOUNDARY AND MINE)
                    data[i][j]++;
            }
        }
    }

  public:
    field()
    { //INITIALIZE
        initialize();
    }
    void initialize(void)
    {
        for (int i = 0; i < 22; i++)
        {
            data[i][0] = BOUNDARY;
            data[i][21] = BOUNDARY;
        }
        for (int i = 1; i < 21; i++)
        {
            data[0][i] = BOUNDARY;
            data[21][i] = BOUNDARY;
        }
        for (int j = 0; j < 22; j++)
            for (int i = 0; i < 22; i++)
            {
                data[i][j] = 0;
                signaled[i][j] = false;
                opened[i][j] = false;
            }
        gamepause = false;
        mines = 30;
        opens = 0;
    }
    void print(void)
    {
        setTextColor(FOREGROUND_GREEN);
        gotoxy(1, 1);
        for (int j = 1; j < 21; j++)
        {
            for (int i = 1; i < 21; i++)
            {
                std::cout << "�� ";
            }
            std::cout << std::endl;
            delay(10);
        }
    }
    void setfield(void)
    {
        initialize();
        int x, y;
        for (int i = 0; i < mines;)
        {
            if (data[x = (rand() % 20 + 1)][y = (rand() % 20 + 1)] != MINE)
            {
                data[x][y] = MINE;
                makenumber(x, y);
                i++;
            }
            else
                continue;
        }
    }
    bool gameisfinish(void)
    {
        if (opens == 20 * 20 - mines)
            return true;
        else
            return false;
    }
    bool bang(int x, int y)
    {
        if (signaled[x][y] || opened[x][y])
            return false;
        else if (data[x][y] == MINE)
            return true;
    }
    void showmine(int x,int y){
        setTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        for (int j = 1; j <= 20; j ++){
            for (int i = 1; i <= 20; i++){
                if(signaled[i][j])
                    continue;
                if(data[i][j]==MINE){
                    gotoxy(i * 2 - 1, j);
                    std::cout << "��";
                    delay(50);
                }
            }
        }
        gotoxy(x * 2 - 1, y);
        setTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
        std::cout << "��";
    }
    void youdied(void)
    {
        //ANIMATION
        setTextColor(FOREGROUND_RED);
        for (int i = 1; i <= (20 / 2) * 2; i++)
        {
            for (int j = 1; j <= (20); j++)
            {
                gotoxy(i, j);
                std::cout << '=';
            }
            for (int j = 1; j <= (20); j++)
            {
                gotoxy(41 - i, j);
                std::cout << '=';
            }
            delay(20);
        }
        setTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
        gotoxy(15, 6);
        std::cout << "            ";
        gotoxy(15, 7);
        std::cout << "  YOU DIED  ";
        gotoxy(15, 8);
        std::cout << "            ";
    }
    void youwin(void)
    {
        //ANIMATION
        setTextColor(FOREGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
        for (int i = 1; i <= 20; i++)
        {
            for (int j = 1; j <= (20) * 2; j++)
            {
                gotoxy(j, i);
                std::cout << '_';
            }
            delay(20);
        }
        setTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        gotoxy(15, 6);
        std::cout << "            ";
        gotoxy(15, 7);
        std::cout << "  YOU WIN!  ";
        gotoxy(15, 8);
        std::cout << "            ";
    }
    bool newgame(void)
    {
        //CONTROL
        int f_key = -1, d_key = -1;
        bool tonewgame = false;
        setTextColor(FOREGROUND_RED|FOREGROUND_GREEN);
        gotoxy(12, 11);  std::cout << " NEW GAME ";
        setTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
        gotoxy(22, 11);  std::cout << " EXIT ";
        while(1){
            if(kbhit()){
                switch(f_key=getch()){
                    case ' ':
                        return tonewgame;
                        break;
                    case 0xe0:
                    case 0x00:
                        if((d_key=getch())==72 || d_key==75 || d_key==77 || d_key==80){
                            if(tonewgame){
                                setTextColor(FOREGROUND_RED|FOREGROUND_GREEN);
                                gotoxy(12, 11);  std::cout << " NEW GAME ";
                                setTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
                                gotoxy(22, 11);  std::cout << " EXIT ";
                            }
                            else{
                                setTextColor(FOREGROUND_RED|FOREGROUND_GREEN);
                                gotoxy(22, 11);  std::cout << " EXIT ";
                                setTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
                                gotoxy(12, 11);  std::cout << " NEW GAME ";
                            }
                            tonewgame = !tonewgame;
                        }
                        break;
                }
            }
        }

    }
    int getdataxy(int x, int y)
    {
        return data[x][y];
    }
    void setdataxy(int x, int y, int state)
    {
        data[x][y] = state;
    }
    void open(int x, int y)
    {
        if (x > 20 || y > 20 || x < 1 || y < 1)
            return;
        if (opened[x][y] || signaled[x][y] || data[x][y] < 0)
            return;

        opened[x][y] = true;
        opens++;
        gotoxy(x * 2 - 1, y);
        setTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        if (data[x][y] == 0)
            std::cout << "  ";
        else
            std::cout << BNUM[data[x][y]];

        if (data[x][y] == 0)
        {
            open(x - 1, y - 1);
            open(x - 1, y);
            open(x - 1, y + 1);

            open(x + 1, y - 1);
            open(x + 1, y);
            open(x + 1, y + 1);

            open(x, y - 1);
            open(x, y + 1);
        }
    }
    void select(int x, int y)
    {
        gotoxy(2 * x - 1, y);
        if (opened[x][y])
        {
            setTextColor(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
            if (data[x][y] == 0)
                std::cout << "  ";
            else
                std::cout<< BNUM[data[x][y]];
        }
        else if (signaled[x][y])
        {
            setTextColor(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            std::cout << "��";
        }
        else
        {
            setTextColor(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_GREEN);
            std::cout << "�� ";
        }
    }
    void unselect(int x, int y)
    {
        gotoxy(2 * x - 1, y);
        if (opened[x][y])
        {
            setTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            if (data[x][y] == 0)
                std::cout << "  ";
            else
                std::cout << BNUM[data[x][y]];
        }
        else if (signaled[x][y])
        {
            setTextColor(FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            std::cout << "��";
        }
        else
        {
            setTextColor(FOREGROUND_GREEN);
            std::cout << "�� ";
        }
    }
    void signal(int x, int y)
    {
        if (opened[x][y])
            return;
        /*if(signaled[x][y])
            std::cout<<"  ";
        else
        
            std::cout<<" P";*/
        //do in the select()
        signaled[x][y] = !signaled[x][y];
    }
    /*  FOR_TEST  */
    void printfield(void)
    {
        //print detail
        for (int j = 1; j < 21; j++)
        {
            for (int i = 1; i < 21; i++)
            {
                if (data[i][j] == MINE)
                {
                    setTextColor(FOREGROUND_RED);
                    std::cout << "��";
                    setTextColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
                }
                else
                    std::cout << ' ' << data[i][j];
            }
            std::cout << std::endl;
        }
    }
};

int main(void)
{
    int fkey = -1, dkey = -1;
    int x, y;
    bool cheat = false;
    field game1;
/*
    game1.setfield();
    game1.printfield();
    std::cout<<std::endl;
    game1.setfield();
    game1.printfield();
    system("pause");
*/
	//srand(time(NULL));
gamestart:
    game1.print();
    game1.initialize();
    game1.setfield();
    game1.select(x = 1, y = 1);

    while (1)
    {
        if (kbhit())
        {
            fkey = getch();
            switch (fkey)
            {
                case 27:  //ESC
                    return 0;
                    break;
                case ' ':
                    //open
                    game1.open(x, y);
                    if (game1.bang(x, y) && !cheat)
                    {
                        game1.showmine(x, y);
                        getch();
                        game1.youdied();
                        if(game1.newgame()){
                            goto gamestart;
                        }
                        else{
                            return 0;
                        }
                    }
                    game1.select(x, y);
                    break;
                case 'F':
                case 'f':
                    game1.signal(x, y);
                    game1.select(x, y);
                    break;
                case 'R':
                case 'r':
                    goto gamestart;
                    break;
                case 'S':
                case 's':
                    cheat = !cheat;
                    gotoxy(50, 1);
                    setTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                    if (cheat)
                        std::cout << "��";
                    else
                        std::cout << "  ";
                    break;
                case 'D':
                case 'd':
                    game1.youdied();
                    break;
                case 'W':
                case 'w':
                    game1.youwin();
                    break;
                case 0xe0:
                case 0x00:
                    switch (dkey = getch())
                    {
                        case 72: //UP
                            if (y > 1)
                            {
                                game1.unselect(x, y);
                                game1.select(x, --y);
                            }
                            break;
                        case 80: //DOWN
                            if (y < 20)
                            {
                                game1.unselect(x, y);
                                game1.select(x, ++y);
                            }
                            break;
                        case 75: //LEFT
                            if (x > 1)
                            {
                                game1.unselect(x, y);
                                game1.select(--x, y);
                            }
                            break;
                        case 77: //RIGHT
                            if (x < 20)
                            {
                                game1.unselect(x, y);
                                game1.select(++x, y);
                            }
                            break;
                    }
                    break;
            }
        }
        if (game1.gameisfinish())
        {
            game1.youwin();
            if(game1.newgame()){
                goto gamestart;
            }
            else{
                return 0;
            }
        }
    }

    return 0;
}
