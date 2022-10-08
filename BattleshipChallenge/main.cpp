#include <iostream>
#include <windows.h>
#include <tuple>
#include <vector>
#include <stdlib.h>

#define dimTable 10
using namespace std;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


//[P]ortaaviones(5), [A]corazado(4), [C]rucero(3), [S]ubmarino(3), [D]estructor(2)

void showTable(string player[dimTable][dimTable])
{
    int color;
    for(int i=0; i<dimTable; i++)
    {
        SetConsoleTextAttribute(hConsole,7);
        if((i+1)==10)cout<<i+1;
        else cout<<i+1<<" ";

        for(int j=0; j<dimTable; j++)
        {
            if(player[i][j]=="o")color=8;
            else if(player[i][j]=="+")color=2;
            else if(player[i][j]=="-")color=9;
            else if(player[i][j]=="*")color=4;
            SetConsoleTextAttribute(hConsole,color);
            cout << player[i][j]<<" ";
        }
        cout<<"\n";
    }
    return;
}

void buildTerrain(string playerABlank[dimTable][dimTable],string playerBBlank[dimTable][dimTable])
{
    SetConsoleTextAttribute(hConsole,7);
    cout<<"  A B C D E F G H I J"<<endl;
    SetConsoleTextAttribute(hConsole,2);
    showTable(playerABlank);
    SetConsoleTextAttribute(hConsole,7);
    cout<<"___________________\n\n";
    SetConsoleTextAttribute(hConsole,2);
    showTable(playerBBlank);
    SetConsoleTextAttribute(hConsole,7);
    cout<<"  A B C D E F G H I J";
}
int getCoordinateX()
{
    bool invalidCoordinate = true;
    char letter;
    int coordinateX;
    do
    {
        cout<<"Ingrese la Letra de la posicion que desea atacar"<<endl;
        cin>>letter;
        letter=toupper(letter);
        coordinateX= letter-65;
        if(coordinateX<dimTable && coordinateX>=0)
        {
            invalidCoordinate=false;
        }
        else
        {
            cout<<"!!!!La letra no es valida"<<endl;
        }
    }
    while(invalidCoordinate);
    return coordinateX;
}
int getCoordinateY()
{
    bool invalidCoordinate = true;
    int coordinateY;
    do
    {

        cout<<"Ingrese el numero de la posicion que desea atacar"<<endl;
        cin>>coordinateY;
        coordinateY= coordinateY-1;
        if(coordinateY<dimTable && coordinateY>=0)
        {
            invalidCoordinate=false;
        }
        else
        {
            cout<<"!!!!El numero no es valido"<<endl;
        }
    }
    while(invalidCoordinate);
    return coordinateY;
}
bool verifyImpact (int x, int y, string playerShips[dimTable][dimTable])
{
    bool impact =false;
    if(playerShips[y][x]!= "o")
    {
        impact = true;
    }
    return impact;
}
bool verifyWinner(int vecShipLife[5])
{
    return (vecShipLife[0] == 0 && vecShipLife[1] == 0 && vecShipLife[2] == 0 && vecShipLife[3] == 0 && vecShipLife[4] == 0);
}
void modifyCharInMap(int ini,int fin, vector<tuple<int,int>> posShips, string playerBoard[dimTable][dimTable])
{
    int y;
    int x;
    for(int i=ini; i<=fin; i++)
    {
        y=get<0>(posShips[i]);
        x=get<1>(posShips[i]);
        playerBoard[y][x] = "*";
    }
}
bool movePlayer(string player, string playerShips[dimTable][dimTable], string playerBoard[dimTable][dimTable],int vecShipsLife[5],vector<tuple<int,int>> posShips)
{
    int x,y;
    string shipLetter;
    bool winner = false;
    cout<<"\n Es el turno del jugador "<< player<< endl;
    x = getCoordinateX();
    y = getCoordinateY();
    if(verifyImpact(x,y,playerShips))
    {
        if(playerBoard[y][x]=="+")
        {
            cout<<"REPETISTE COORDENADAS DE ATAQUE"<<endl;
        }
        else if(playerBoard[y][x]=="o")
        {
            playerBoard[y][x]="+";
            cout<<"--------------------  IMPACTO  ---------------------------!!! \n"<<endl;
            shipLetter=playerShips[y][x];

            if(shipLetter=="P")
            {
                vecShipsLife[0]--;
                if(vecShipsLife[0]==0)modifyCharInMap(0,4,posShips,playerBoard);
            }
            else if(shipLetter=="A")
            {
                vecShipsLife[1]--;
                if(vecShipsLife[1]==0)modifyCharInMap(5,8,posShips,playerBoard);
            }
            else if(shipLetter=="C")
            {
                vecShipsLife[2]--;
                if(vecShipsLife[2]==0)modifyCharInMap(9,11,posShips,playerBoard);
            }
            else if(shipLetter=="S")
            {
                vecShipsLife[3]--;
                if(vecShipsLife[3]==0)modifyCharInMap(12,14,posShips,playerBoard);
            }
            else if(shipLetter=="D")
            {
                vecShipsLife[4]--;
                if(vecShipsLife[4]==0)modifyCharInMap(15,16,posShips,playerBoard);
            }
            winner = verifyWinner(vecShipsLife);
            if(winner)cout<<"*--*--*--*--*--*--*WINNER*--*--*--*--*--*--* \n GANASTE "<<player<<" gracias por jugar"<<endl;
        }
    }
    else
    {
        if(playerBoard[y][x]=="-")
        {
            cout<<"REPETISTE COORDENADAS DE ATAQUE"<<endl;
        }
        else
        {
            playerBoard[y][x]="-";
            cout<<"xxxxxxxxxxxxxxxxxx  FALLASTE  xxxxxxxxxxxxxxxxxx!!! \n"<<endl;
        }
    }
    return winner;
}

void gameController(string boardShipA[dimTable][dimTable],string boardShipB[dimTable][dimTable],string boardABlank[dimTable][dimTable],string boardBBlank[dimTable][dimTable],vector<tuple<int,int>> posShipsA, vector<tuple<int,int>> posShipsB)
{
    bool winner=false;
    string player = "P1";
    int vecShipsLifePlayerA[5] = {5,4,3,3,2};
    int vecShipsLifePlayerB[5] = {5,4,3,3,2};
    while(winner!=true)
    {
        cout<<"#############################################################################################"<<endl;
        buildTerrain(boardABlank,boardBBlank);
        if(player == "P1")
        {
            if(movePlayer(player,boardShipB,boardBBlank,vecShipsLifePlayerB,posShipsB))winner = true;
            player = "P2";
        }
        else
        {
            if(movePlayer(player,boardShipA,boardABlank,vecShipsLifePlayerA,posShipsA))winner = true;
            player = "P1";
        }
    }
    buildTerrain(boardShipA,boardShipB);
}

void putShipsPredeterminate(string playerA[dimTable][dimTable],string playerB[dimTable][dimTable], vector<tuple<int,int>>& posShipsA, vector<tuple<int,int>>& posShipsB)
{
    //Portaaviones
    playerA[2][2] = "P";
    posShipsA.emplace_back(2,2);
    playerA[3][2] = "P";
    posShipsA.emplace_back(3,2);
    playerA[4][2] = "P";
    posShipsA.emplace_back(4,2);
    playerA[5][2] = "P";
    posShipsA.emplace_back(5,2);
    playerA[6][2] = "P";
    posShipsA.emplace_back(6,2);
    //Acorazado
    playerA[1][4] = "A";
    posShipsA.emplace_back(1,4);
    playerA[1][5] = "A";
    posShipsA.emplace_back(1,5);
    playerA[1][6] = "A";
    posShipsA.emplace_back(1,6);
    playerA[1][7] = "A";
    posShipsA.emplace_back(1,7);
    //Crucero
    playerA[8][3] = "C";
    posShipsA.emplace_back(8,3);
    playerA[8][4] = "C";
    posShipsA.emplace_back(8,4);
    playerA[8][5] = "C";
    posShipsA.emplace_back(8,5);
    //Submarino
    playerA[3][7] = "S";
    posShipsA.emplace_back(3,7);
    playerA[4][7] = "S";
    posShipsA.emplace_back(4,7);
    playerA[5][7] = "S";
    posShipsA.emplace_back(5,7);
    //Destructor
    playerA[8][8] = "D";
    posShipsA.emplace_back(8,8);
    playerA[9][8] = "D";
    posShipsA.emplace_back(9,8);

    //-----------------------B-------------
    //Portaaviones
    playerB[0][2] = "P";
    posShipsB.emplace_back(0,2);
    playerB[0][3] = "P";
    posShipsB.emplace_back(0,3);
    playerB[0][4] = "P";
    posShipsB.emplace_back(0,4);
    playerB[0][5] = "P";
    posShipsB.emplace_back(0,5);
    playerB[0][6] = "P";
    posShipsB.emplace_back(0,6);
    //Acorazado
    playerB[2][1] = "A";
    posShipsB.emplace_back(2,1);
    playerB[3][1] = "A";
    posShipsB.emplace_back(3,1);
    playerB[4][1] = "A";
    posShipsB.emplace_back(4,1);
    playerB[5][1] = "A";
    posShipsB.emplace_back(5,1);
    //Crucero
    playerB[1][8] = "C";
    posShipsB.emplace_back(1,8);
    playerB[2][8] = "C";
    posShipsB.emplace_back(2,8);
    playerB[3][8] = "C";
    posShipsB.emplace_back(3,8);
    //Submarino
    playerB[5][3] = "S";
    posShipsB.emplace_back(5,3);
    playerB[5][4] = "S";
    posShipsB.emplace_back(5,4);
    playerB[5][5] = "S";
    posShipsB.emplace_back(5,5);
    //Destructor
    playerB[6][8] = "D";
    posShipsB.emplace_back(6,8);
    playerB[6][9] = "D";
    posShipsB.emplace_back(6,9);
}
int main()
{
    string boardShipsPlayerA[dimTable][dimTable];
    string boardShipsPlayerB[dimTable][dimTable];
    string boardPlayerABlank[dimTable][dimTable];
    string boardPlayerBBlank[dimTable][dimTable];
    vector<tuple<int,int>> posShipsA;
    vector<tuple<int,int>> posShipsB;
    std::fill(*boardShipsPlayerA, *boardShipsPlayerA + dimTable*dimTable,"o");
    std::fill(*boardShipsPlayerB, *boardShipsPlayerB + dimTable*dimTable,"o");
    std::fill(*boardPlayerABlank, *boardPlayerABlank + dimTable*dimTable,"o");
    std::fill(*boardPlayerBBlank, *boardPlayerBBlank + dimTable*dimTable,"o");

    putShipsPredeterminate(boardShipsPlayerA,boardShipsPlayerB,posShipsA,posShipsB);
    gameController(boardShipsPlayerA,boardShipsPlayerB,boardPlayerABlank,boardPlayerBBlank,posShipsA,posShipsB);
    return 0;
}
