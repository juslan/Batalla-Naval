#include <iostream>
#include <windows.h>

#define dimTable 10
using namespace std;

void gotoxy(int x,int y)
{
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y= y;
    SetConsoleCursorPosition(hcon,dwPos);
}


//[P]ortaaviones(5), [A]corazado(4), [C]rucero(3), [S]ubmarino(3), [D]estructor(2)

//void showBoard(string playerA[dimTable][dimTable],string playerB[dimTable][dimTable])
void showBoard(int playerA[dimTable][dimTable])
{
    int x1=0,x2=0;
    for(int i=0; i<dimTable; i++)
    {
        for(int j=0; j<dimTable; j++)
        {
            cout << playerA[i][j]<<" ";
        }
        cout<<"\n";
    }
    return;
}
int main()
{
    int matPlayerA[dimTable][dimTable];
    int matPlayerB[dimTable][dimTable];
    int val = 100;
    for (auto &row: matPlayerA)
    {
        for (auto &e: row)
        {
            e = val;
            val++;
        }
    }
    //std::fill(*matPlayerA, *matPlayerA + dimTable*dimTable,"*");
    //std::fill(*matPlayerB, *matPlayerB + dimTable*dimTable,"*");
    showBoard(matPlayerA);
    //showTables(matPlayerB,15);
    return 0;
}
