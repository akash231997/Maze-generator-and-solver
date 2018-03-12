#include<bits/stdc++.h>
#include<cstdlib>
#include<windows.h>
using namespace std;

#define NORTH   0
#define SOUTH   1
#define EAST    2
#define WEST    3
#define SIZEX   15
#define SIZEY   15


char grid[SIZEY][SIZEX];
int N,M;
void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}


int nGood = 0;
int locX = 1, locY = 1;

int moveEW(int direction, int x){
    if (direction == EAST)
            return x + 1;
    else if (direction == WEST)
            return x - 1;
    else
            return x;
}

int moveNS(int direction, int y){
    if (direction == NORTH)
            return y - 1;
    else if (direction == SOUTH)
            return y + 1;
    else
            return y;
}

bool isGood(int x, int y, int direction, char grid[SIZEY][SIZEX]){
x = moveEW(direction,x);
y = moveNS(direction,y);

if (grid[y][x] == '.' || x >= (SIZEX - 1) || x <= 0 || y <= 0 || y >= (SIZEY - 1)){
    return false;
}

// check cardinal directions
if (direction == NORTH){
    if (grid[y][x-1] != '.' &&  grid[y-1][x] != '.' && grid[y][x+1] != '.' &&  grid[y-1][x-1] != '.' && grid[y-1][x+1] != '.'){
        return true;
    }
}
if (direction == SOUTH){
            if (grid[y][x-1] != '.' &&  grid[y+1][x] != '.' && grid[y][x+1] != '.' && grid[y+1][x-1] != '.' && grid[y+1][x+1] != '.'){
                    return true;
            }
    }
if (direction == EAST){
            if (grid[y][x+1] != '.' &&  grid[y-1][x] != '.' && grid[y+1][x] != '.' && grid[y-1][x+1] != '.' && grid[y+1][x+1] != '.'){
                    return true;
            }
    }
if (direction == WEST){
            if (grid[y][x-1] != '.' &&  grid[y-1][x] != '.' && grid[y+1][x] != '.' && grid[y-1][x-1] != '.' && grid[y+1][x-1] != '.'){
                    return true;
            }
    }
return false;
}

void xy(int xpos, int ypos)
{
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = xpos; scrn.Y = ypos;
    SetConsoleCursorPosition(hOuput,scrn);
}

void Sc(int ForgC, int BackC)
{
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
     return;
}
//char grid[100][100];

bool isSafe(int x, int y)
{
    if(x >= 0 && x < N && y >= 0 && y < M && grid[x][y] == '.')
        return true;
    return false;
}
bool solveMazeUtil(int x, int y,int last)
{


    if(x == N-1 && y == M-1)
    {
        Sc(12,0);
        xy(2*y,x);
        cout<<grid[x][y];
        grid[x][y] = 'o';
        return true;
    }
    delay(100);

    if(isSafe(x, y) == true)
    {
        grid[x][y] = 'o';
        Sc(14,0);
        xy(2*y,x);
        cout<<grid[x][y];

        if (last!=2&&solveMazeUtil(x+1, y,0) == true)
            { return true; }

        if (last!=3&&solveMazeUtil(x, y+1,1) == true)
            { return true; }

        if (last!=0&&solveMazeUtil(x-1, y,2) == true)
            { return true; }

        if (last!=1&&solveMazeUtil(x, y-1,3) == true)
            { return true; }

        Sc(12,3);
        grid[x][y] = '.';
        Sc(11,0);
        xy(2*y,x);
        cout<<grid[x][y];
        return false;
    }

    return false;
}




int main(){


for (int i = 0; i < SIZEY; i++)
    {
        for(int j = 0; j < SIZEX; j++)
           {
                xy(j,i);
                Sc(9,0);
                grid[i][j]='#';
                cout<<grid[i][j];
            }
    }

//init rand
srand(time(0));

stack<int> xValues;
stack<int> yValues;

int direction = 0;

do{
//delay(100);
    for (int i = 0; i < 4; i++){
        if (isGood(locX,locY,i,grid))
            nGood++;
    }

    if (nGood == 1)
        {
        if (isGood(locX,locY,NORTH,grid))
            locY = moveNS(NORTH,locY);
        else if (isGood(locX,locY,SOUTH,grid))
            locY = moveNS(SOUTH,locY);
        else if (isGood(locX,locY,EAST,grid))
            locX = moveEW(EAST,locX);
        else if (isGood(locX,locY,WEST,grid))
            locX = moveEW(WEST,locX);
    }

    else if (nGood == 0)
        {
        locX = xValues.top();
        locY = yValues.top();
        xValues.pop();
        yValues.pop();

    }

    else if (nGood > 1)
        {
        xValues.push(locX);
        yValues.push(locY);

        do{
            direction = rand() % 4;
        }while (!isGood(locX,locY,direction,grid));

        locX = moveEW(direction,locX);
        locY = moveNS(direction,locY);
    }
     //Sc(14,0);
    xy(locY,locX);
    Sc(14,0);
    grid[locY][locX] ='.';
    cout<<grid[locY][locX];

    nGood = 0;
    delay(60);

}while(!xValues.empty());

Sc(12,0);
xy(0,0);
Sc(12,0);
grid[0][0]='.';
cout<<grid[0][0];

xy(0,1);
Sc(12,0);
grid[0][1]='.';
cout<<grid[0][1];

xy(SIZEY-1,SIZEX-2);
Sc(12,0);
grid[SIZEY-1][SIZEX-2]='.';
cout<<grid[SIZEY-1][SIZEX-2];

xy(SIZEY-1,SIZEX-1);
Sc(12,0);
grid[SIZEY-1][SIZEX-1]='.';
cout<<grid[SIZEY-1][SIZEX-1];
cout<<endl;

    cout<<"Press Enter to find the path: \n";
    getchar();
    system("cls");
    N=SIZEX;
    M=SIZEY;

    for(int i=0;i<N;i++)
    {
        for(int j=0;j<M;j++)
        {
            if(grid[i][j]=='#')
                Sc(4,0);
            else Sc(2,0);
                xy(2*j,i);
            cout<<grid[i][j];
        }
        cout<<endl;
    }


    if(solveMazeUtil(0,0,1) || solveMazeUtil(0,0,0))
    {
        delay(200);
        grid[N-1][M-1]='o';

        for(int i=0;i<N;i++)
        {
        for(int j=0;j<M;j++)
        {
            if(grid[i][j]=='#')
                Sc(12,0);
            else Sc(10,0);
                xy(2*j,i);
            cout<<grid[i][j];
        }
        cout<<endl;
    }
    }
    else
    {
        cout<<"No way possible ";
    }


return 0;
}
