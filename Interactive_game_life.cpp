#include <stdio.h>
#include <windows.h>
#include "TXLib.h"

void show_life (int a[], int n, int m              );
void setka     (                                   );
int  live      (int x, int y                       );
int  fon       (                                   );
int  next_state(int a[], int n, int m, int i, int j);

int main()
{
    txCreateWindow(500,500);
    fon();
    txClear();
    int i, j, x, y, pom1, pom2;
    int n=10;
    int m=10;
    int a[n][m];
    int b[n][m];

    for(i=0; i<n; i++)
    {
        for(j=0; j<m; j++)
        {
            a[i][j] = 0;
            b[i][j] = 0;
        }
    }
    setka();

    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        while(!GetAsyncKeyState(VK_SHIFT))
        {
            if(txMouseButtons() == 1)
            {
                txSetFillColor(TX_MAGENTA);
                txSetColor(TX_WHITE);
                for(i=0; i<n; i++)
                {
                    for(j=0; j<m; j++)
                    {
                        if((txMouseX() >= j*50) && (txMouseX() <= j*50+50))
                        {
                            x=j*50+25;
                            pom1=j;
                        }
                        if((txMouseY() >= i*50) && (txMouseY() <= i*50+50))
                        {
                            y=i*50+25;
                            pom2=i;
                        }
                    }
                }
                live(x, y);
                a[pom2][pom1]=1;
            }
            if(txMouseButtons() == 2)
            {
                txSetFillColor(TX_BLACK);
                txSetColor(TX_BLACK);
                for(i=0; i<n; i++)
                {
                    for(j=0; j<m; j++)
                    {
                        if((txMouseX() >= j*50) && (txMouseX() <= j*50+50))
                        {
                            x=j*50+25;
                            pom1=j;
                        }
                        if((txMouseY() >= i*50) && (txMouseY() <= i*50+50))
                        {
                            y=i*50+25;
                            pom2=i;
                        }
                    }
                }
                txCircle(x, y, 20);
                a[pom2][pom1]=0;
            }
        }
        while(!GetAsyncKeyState(VK_RETURN))
        {
            txSetFillColor(TX_BLACK);
            txClear();
            setka();

            for(i=0; i<n; i++)
            {
                for(j=0; j<m; j++)
                {
                    b[i][j] = next_state(&a[0][0], n, m, i, j);
                }
            }

            for(i=0; i<n; i++)
            {
                for(j=0; j<m; j++)
                {
                    a[i][j] = b[i][j];
                }
            }
            txSetFillColor(TX_MAGENTA);
            show_life(&a[0][0], n, m);

            txSleep(500);
        }
    }
}


void show_life(int a[], int n, int m)
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            if(a[i*m+j]==1)
            {

                live((j*50)+25,(i*50)+25);
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
}

int next_state(int a[], int n, int m, int i, int j)
{
    int summa=0;

    summa=((a[((n+(i-1))% n)*m + ((m+(j-1))%m)])+
           (a[((n+(i-1))% n)*m + j            ])+
           (a[((n+(i-1))% n)*m + ((j+1)%m)    ])+
           (a[i             *m + ((m+(j-1))%m)])+
           (a[i             *m + ((j+1)%m)    ])+
           (a[((i+1)%n)     *m + ((m+(j-1))%m)])+
           (a[((i+1)%n)     *m + j            ])+
           (a[((i+1)%n)     *m + ((j+1)%m)    ]));
    if( (summa==3)  || ( (a[i*m+j]==1) && (summa==2) ) )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int fon()
{
    int time=0;
    txSetFillColor(TX_BLACK);
    txSetColor(TX_WHITE);
    txClear();
    txSelectFont("Comic Sans MS",23, 12, true);
    txDrawText(50, 0, 450, 500, "\nС помощью правой кнопки мыши введите начальное состояние жизни\n\n"
                                "С помощью левой кнопки мыши можно убрать жизнь из клетки     \n\n"
                                "По окончанию ввода нажмите Shift для наблюдения следующих состояний \n\n"
                                "Для изменения текущего состояния нажмите Enter   \n\n"
                                "Чтобы завершить программу нажмите Escape\n\n"
                                "(Для пропуска нажмите пробел)"
                );
    while(time<301)
    {
        time++;
        txSleep(50);
        if(GetAsyncKeyState(VK_SPACE))
        {
            return 0;
        }
    }
    return 0;
}

void setka()
{
    txSetColor(TX_WHITE);
    for(int i=0; i<=500; i+=50)
    {
        txLine(i, 0, i, 500);
        txLine(0, i, 500, i);
    }
}

int live(int x, int y)
{
    txSetFillColor(TX_RED);
    txSetColor(TX_RED);
    txCircle (x, y, 20);
    txSetFillColor(TX_ORANGE);
    txSetColor(TX_ORANGE);
    txCircle (x, y, 17);
    txSetFillColor(TX_YELLOW);
    txSetColor(TX_YELLOW);
    txCircle (x, y, 14);
    txSetFillColor(TX_LIGHTGREEN);
    txSetColor(TX_GREEN);
    txCircle (x, y, 11);
    txSetFillColor(TX_LIGHTBLUE);
    txSetColor(TX_LIGHTBLUE);
    txCircle (x, y, 8);
    txSetFillColor(TX_BLUE);
    txSetColor(TX_BLUE);
    txCircle (x, y, 5);
    txSetFillColor(TX_MAGENTA);
    txSetColor(TX_MAGENTA);
    txCircle (x, y, 3);
}
