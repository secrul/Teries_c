#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#define Framex 13
#define Framey 3
#define Frame_hight 20
#define Frame_width 18

int i,j, temp, temp1, temp2; //三个中间值分别记住和转换方块变量的值

int a[80][80] = {0};
int clean = 0;
int ma = 0;
int cl[19] = {10,13,13,11,11,11,11,14,14,14,14,12,12,12,12,12,12,12,12};
typedef struct Teries
{
    int x;
    int y;
    int flag;
    int next;
    int speed;
    int number;
    int sorce;
    int max;
} node;
HANDLE hOut;//控制台句柄

int color(int c);//
void gotoxy(int x, int y);//移动光标到指定位置
void DrawGameframe();//绘制游戏裱框
void Flag(struct Teries* s);//随机产生方块类型序号
void MakeTeries(struct Teries*);//产生俄罗斯方块
void PrintTeries(struct Teries*);//打印俄罗斯方块
void CleanTeries(struct Teries*);//消除俄罗斯方块的痕迹
int ifMove(struct Teries*);//判断是否移动，返回值为1时移动，否则不移动
void Del_Fullline(struct Teries*);//判断是否满行，并删除满行的俄罗斯方块
void Gameplay();//开始游戏
void regulation();//游戏规则
void explation();//按键说明
void welcom();//欢迎界面
void Reply(struct Teries *teries);//重新开始游戏
void title();//欢迎界面上方标题
void flower();//欢迎界面字符装饰
void close();//关闭游戏



int color(int c)//设置文字的颜色
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
    return 0;
}

void gotoxy(int x, int y)//设置文字显示位置
{
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void title()//设计标题部分
{
    color(15);
    gotoxy(24,3);
    printf("趣  味  俄  罗  斯  方  块\n");
    color(11);
    gotoxy(18,5);
    printf("█");
    gotoxy(18,6);
    printf("██");
    gotoxy(18,7);
    printf("█");

    color(14);
    gotoxy(26,6);
    printf("██");
    gotoxy(28,7);
    printf("██");

    color(10);
    gotoxy(36,6);
    printf("██");
    gotoxy(36,7);
    printf("██");

    color(13);
    gotoxy(45,5);
    printf("█");
    gotoxy(45,6);
    printf("█");
    gotoxy(45,7);
    printf("█");
    gotoxy(45,8);
    printf("█");

    color(12);
    gotoxy(56,6);
    printf("█");
    gotoxy(54,7);
    printf("███");
}

void flower()//设置字符装饰
{
    gotoxy(66,11);
    color(12);
    printf("(_)");

    gotoxy(64,12);
    printf("(_)");

    gotoxy(68,12);
    printf("(_)");

    gotoxy(66,13);
    printf("(_)");

    gotoxy(67,12);
    color(6);
    printf("(_)");

    gotoxy(72,10);
    color(13);
    printf("(_)");

    gotoxy(76,10);
    printf("(_)");

    gotoxy(74,11);
    printf("(_)");

    gotoxy(75,10);
    color(6);
    printf("(_)");

    gotoxy(71,12);
    printf("|");

    gotoxy(72,11);
    printf("/");

    gotoxy(70,13);
    printf("\\|");

    gotoxy(70,14);
    printf("'|/");

    gotoxy(70,15);
    printf("\\|");

    gotoxy(71,16);
    printf("|  /");

    gotoxy(71,17);
    printf("|");

    gotoxy(67,17);
    color(10);
    printf("\\\\\\\\");

    gotoxy(73,17);
    printf("////");

    gotoxy(67,18);
    color(2);
    printf("^^^^^^");

    gotoxy(68,20);
    printf("刘金昊");
}

void welcom()//设计菜单选项边框
{
    int i, j = 1;
    color(14);
    for(i = 9; i <= 20; i ++)
    {
        for(j = 15; j <= 60; j ++)
        {
            gotoxy(j, i);
            if(i == 9 || i == 20)
                printf("=");
            else if(j == 15 || j == 59)
                printf("||");
        }
    }
    /*
    设计菜单选项中的文字
    */
    int n;
    color(12);
    gotoxy(25,12);
    printf("1. 开始游戏");

    gotoxy(40,12);
    printf("2.按键说明");

    gotoxy(25,17);
    printf("3.游戏规则");

    gotoxy(40,17);
    printf("4.退出游戏");

    gotoxy(21,22);
    color(3);
    printf("请选择[1 2 3 4]:[ ]\b\b");
    color(14);
    scanf("%d",&n);
    switch (n)
    {
    case 1:
        system("cls");//清屏函数
        DrawGameframe();
        Gameplay();
        break;
    case 2:
        explation();      	//按键说明函数
        break;
    case 3:
        regulation();     	//游戏规则函数
        break;
    case 4:
        close();    		//关闭游戏函数
        break;
    }
}

//游戏主体窗口设计
void DrawGameframe()//制作游戏窗口
{
    gotoxy(Framex +Frame_width - 7, Framey - 2);
    color(11);
    printf("趣味俄罗斯方块");
    gotoxy(Framex + 2 * Frame_width + 3, Framey + 7);
    color(2);
    printf("***********");
    gotoxy(Framex +2 * Frame_width + 13, Framey + 7);
    color(3);
    printf("下一出现的方块： ");
    gotoxy(Framex + 2 * Frame_width  + 3, Framey + 13);
    color(2);
    printf("**********");
    gotoxy(Framex + 2 * Frame_width + 3, Framey + 17);
    color(14);
    printf("up键：旋转");
    gotoxy(Framex + 2 * Frame_width + 3, Framey + 19);
    printf("空格键：暂停");
    gotoxy(Framex + 2 * Frame_width + 3, Framey + 15);
    printf("Esc：退出游戏");

    gotoxy(Framex, Framey);
    color(12);
    printf("《 ");
    gotoxy(Framex + 2 * Frame_width - 2, Framey);
    printf("》");
    gotoxy(Framex, Framey + Frame_hight);
    printf("《");
    gotoxy(Framex+ 2 * Frame_width - 2, Framey + Frame_hight);
    printf("》");

    a[Framex][Framey + Frame_hight] = -1;
    a[Framex+ 2 * Frame_width - 2][Framey + Frame_hight] = -1;
    int i;
    for(i = 2; i < 2 * Frame_width - 2 ; i += 2)
    {
        gotoxy(Framex + i, Framey);
        printf("==");
    }
    for(i = 2; i < 2 * Frame_width - 2; i += 2)
    {
        gotoxy(Framex + i, Framey + Frame_hight);
        printf("==");
        a[Framex + i][Framey + Frame_hight] = -1;
    }
    for(i = 1; i < Frame_hight; i ++)
    {
        gotoxy(Framex, Framey + i);
        printf("||");
        a[Framex][Framey + i] = -1;
    }
    for(i = 1; i < Frame_hight; i ++)
    {
        gotoxy(Framex + 2 * Frame_width - 2, Framey + i);
        printf("||");
        a[Framex + 2 * Frame_width - 2][Framey + i] = -1;
    }
}

//制作俄罗斯方块
void MakeTeries(struct Teries *teries)
{
    if(clean)
    {
        a[teries->x][teries->y] = 0;
    }
    else
    {
        a[teries->x][teries->y] = teries->flag;
    }
    switch(teries->flag)
    {
    case 1://田字方块
    {
        if(clean)
        {
            a[teries->x][teries->y - 1] = 0;
            a[teries->x + 2][teries->y - 1] =0;
            a[teries->x + 2][teries->y] = 0;
        }
        else
        {
            a[teries->x][teries->y - 1] = teries->flag;
            a[teries->x + 2][teries->y - 1] =teries->flag;
            a[teries->x + 2][teries->y] = teries->flag;
        }
        break;
    }
    case 2://横线直线方块
    {
        if(clean)
        {
            a[teries->x - 2][teries->y] =0;
            a[teries->x + 2][teries->y] = 0;
            a[teries->x + 4][teries->y] = 0;
        }
        else
        {
            a[teries->x - 2][teries->y] =teries->flag;
            a[teries->x + 2][teries->y] = teries->flag;
            a[teries->x + 4][teries->y] = teries->flag;
        }
        break;
    }
    case 3://竖直直线方块
    {
        if(clean)
        {
            a[teries->x][teries->y - 1] = 0;
            a[teries->x][teries->y - 2] = 0;
            a[teries->x][teries->y + 1] = 0;
        }
        else
        {
            a[teries->x][teries->y - 1] = teries->flag;
            a[teries->x][teries->y - 2] = teries->flag;
            a[teries->x][teries->y + 1] = teries->flag;
        }
        break;
    }
    case 4://T字方块
    {
        if(clean)
        {
            a[teries->x -2][teries->y] =0;
            a[teries->x + 2][teries->y] =0;
            a[teries->x][teries->y + 1] = 0;
        }
        else
        {
            a[teries->x -2][teries->y] = teries->flag;
            a[teries->x + 2][teries->y] = teries->flag;
            a[teries->x][teries->y + 1] = teries->flag;
        }

        break;
    }
    case 5://顺时针90T字方块
    {
        if(clean)
        {
            a[teries->x][teries->y - 1] = 0;
            a[teries->x][teries->y + 1] = 0;
            a[teries->x - 2][teries->y] = 0;
        }
        else
        {
            a[teries->x][teries->y - 1] = teries->flag;
            a[teries->x][teries->y + 1] = teries->flag;
            a[teries->x - 2][teries->y] = teries->flag;
        }

        break;
    }
    case 6://顺时针180T字方块
    {
        if(clean)
        {
            a[teries->x][teries->y - 1] = 0;
            a[teries->x - 2][teries->y] = 0;
            a[teries->x + 2][teries->y] = 0;
        }
        else
        {
            a[teries->x][teries->y - 1] = teries->flag;
            a[teries->x - 2][teries->y] = teries->flag;
            a[teries->x + 2][teries->y] = teries->flag;
        }

        break;
    }
    case 7://顺时针270T字方块
    {
        if(clean)
        {
            a[teries->x][teries->y - 1] = 0;
            a[teries->x][teries->y+1] = 0;
            a[teries->x + 2][teries->y] = 0;
        }
        else
        {
            a[teries->x][teries->y - 1] = teries->flag;
            a[teries->x][teries->y+1] = teries->flag;
            a[teries->x + 2][teries->y] = teries->flag;
        }

        break;
    }
    case 8://z字方块
    {
        if(clean)
        {
            a[teries->x][teries->y + 1] = 0;
            a[teries->x - 2][teries->y] = 0;
            a[teries->x +2][teries->y + 1] = 0;
        }
        else
        {
            a[teries->x][teries->y + 1] = teries->flag;
            a[teries->x - 2][teries->y] = teries->flag;
            a[teries->x +2][teries->y + 1] = teries->flag;
        }

        break;
    }
    case 9://顺时针Z字
    {
        if(clean)
        {
            a[teries->x][teries->y - 1] = 0;
            a[teries->x - 2][teries->y] = 0;
            a[teries->x -2][teries->y + 1] = 0;
        }
        else
        {
            a[teries->x][teries->y - 1] = teries->flag;
            a[teries->x - 2][teries->y] = teries->flag;
            a[teries->x -2][teries->y + 1] = teries->flag;
        }

        break;
    }
    case 10://反Z字
    {
        if(clean)
        {
            a[teries->x][teries->y - 1] = 0;
            a[teries->x - 2][teries->y-1] = 0;
            a[teries->x + 2][teries->y] =0;
        }
        else
        {
            a[teries->x][teries->y - 1] = teries->flag;
            a[teries->x - 2][teries->y-1] = teries->flag;
            a[teries->x + 2][teries->y] = teries->flag;
        }

        break;
    }
    case 11://顺时针反Z字
    {
        if(clean)
        {
            a[teries->x][teries->y + 1] = 0;
            a[teries->x - 2][teries->y - 1] = 0;
            a[teries->x - 2][teries->y] = 0;
        }
        else
        {
            a[teries->x][teries->y + 1] = teries->flag;
            a[teries->x - 2][teries->y - 1] = teries->flag;
            a[teries->x - 2][teries->y] = teries->flag;
        }

        break;
    }
    case 12:
    {
        if(clean)
        {
            a[teries->x][teries->y - 1] = 0;
            a[teries->x][teries->y + 1] = 0;
            a[teries->x - 2][teries->y - 1] = 0;
        }
        else
        {
            a[teries->x][teries->y - 1] = teries->flag;
            a[teries->x][teries->y + 1] = teries->flag;
            a[teries->x - 2][teries->y - 1] = teries->flag;
        }

        break;
    }
    case 13:
    {
        if(clean)
        {
            a[teries->x - 2][teries->y] = 0;
            a[teries->x + 2][teries->y - 1] = 0;
            a[teries->x + 2][teries->y] = 0;
        }
        else
        {
            a[teries->x - 2][teries->y] = teries->flag;
            a[teries->x + 2][teries->y - 1] = teries->flag;
            a[teries->x + 2][teries->y] = teries->flag;
        }

        break;
    }
    case 14:
    {
        if(clean)
        {
            a[teries->x][teries->y - 1] = 0;
            a[teries->x][teries->y + 1] = 0;
            a[teries->x + 2][teries->y + 1] = 0;
        }
        else
        {
            a[teries->x][teries->y - 1] = teries->flag;
            a[teries->x][teries->y + 1] = teries->flag;
            a[teries->x + 2][teries->y + 1] = teries->flag;
        }

        break;
    }
    case 15:
    {
        if(clean)
        {
            a[teries->x - 2][teries->y] = 0;
            a[teries->x - 2][teries->y + 1] =0;
            a[teries->x + 2][teries->y] = 0;
        }
        else
        {
            a[teries->x - 2][teries->y] = teries->flag;
            a[teries->x - 2][teries->y + 1] = teries->flag;
            a[teries->x + 2][teries->y] = teries->flag;
        }

        break;
    }
    case 16:
    {
        if(clean)
        {
            a[teries->x][teries->y  + 1] = 0;
            a[teries->x][teries->y - 1] = 0;
            a[teries->x +2][teries->y - 1] = 0;
        }
        else
        {
            a[teries->x][teries->y  + 1] = teries->flag;
            a[teries->x][teries->y - 1] = teries->flag;
            a[teries->x +2][teries->y - 1] = teries->flag;
        }

        break;
    }
    case 17:
    {
        if(clean)
        {
            a[teries->x - 2][teries->y] = 0;
            a[teries->x + 2][teries->y +1] = 0;
            a[teries->x + 2][teries->y] = 0;
        }
        else
        {
            a[teries->x - 2][teries->y] = teries->flag;
            a[teries->x + 2][teries->y +1] = teries->flag;
            a[teries->x + 2][teries->y] = teries->flag;
        }

        break;
    }
    case 18:
    {
        if(clean)
        {
            a[teries->x][teries->y - 1] =0;
            a[teries->x][teries->y + 1] = 0;
            a[teries->x - 2][teries->y + 1] = 0;
        }
        else
        {
            a[teries->x][teries->y - 1] = teries->flag;
            a[teries->x][teries->y + 1] = teries->flag;
            a[teries->x - 2][teries->y + 1] = teries->flag;
        }

        break;
    }
    case 19:
    {
        if(clean)
        {
            a[teries->x - 2][teries->y] =0;
            a[teries->x - 2][teries->y - 1] = 0;
            a[teries->x + 2][teries->y] = 0;
        }
        else
        {
            a[teries->x - 2][teries->y] = teries->flag;
            a[teries->x - 2][teries->y - 1] = teries->flag;
            a[teries->x + 2][teries->y] = teries->flag;
        }

        break;
    }
    }
}

void PrintTeries(struct Teries* teries)//打印方块
{
    clean =0;
    MakeTeries(teries);
    for(i = teries->x-2; i <= teries->x + 4; i += 2)
    {   //if(i < Framex +2* Frame_width - 2 )
        for(j = teries->y - 2; j <= teries->y + 1; j++)
        {
            if(a[i][j] >= 1 && j > Framey )
            {
                gotoxy(i, j);
                color(cl[a[i][j] -1]);
                printf("█");
            }
        }
    }
    gotoxy(Framex + 2 * Frame_width + 3, Framey + 1);
    color(4);
    printf("max sorce : ");
    color(12);
    printf(" %d",teries->max);
    gotoxy(Framex + 2 * Frame_width + 3, Framey);
    color(4);
    printf("sorce : ");
    color(12);
    printf(" %d",teries->sorce);
    gotoxy(Framex + 2 * Frame_width + 3, Framey + 5);
    color(4);
    printf("speed : ");
    color(12);
    printf(" %dms",teries->speed);
}

int ifMove(struct Teries* teries)
{
    if(a[teries->x][teries->y] != 0)
    {
        return 0;
    }
    else
    {
        if((teries->flag == 1 && (a[teries->x][teries->y - 1] == 0 && a[teries->x + 2][teries->y - 1] == 0 && a[teries->x + 2][teries->y] == 0)) ||
                (teries->flag == 2 &&(a[teries->x - 2][teries->y] == 0 && a[teries->x + 2][teries->y] == 0 && a[teries->x + 4][teries->y] == 0)) ||
                (teries->flag == 3 &&(a[teries->x][teries->y - 1] == 0 && a[teries->x][teries->y - 2] == 0 && a[teries->x][teries->y +1] == 0)) ||
                (teries->flag == 4 &&(a[teries->x - 2][teries->y] == 0 && a[teries->x + 2][teries->y] == 0 && a[teries->x][teries->y + 1] == 0)) ||
                (teries->flag == 5 &&(a[teries->x][teries->y - 1] == 0 && a[teries->x][teries->y + 1] == 0 && a[teries->x - 2][teries->y] == 0)) ||
                (teries->flag == 6 &&(a[teries->x][teries->y - 1] == 0 && a[teries->x - 2][teries->y] == 0 && a[teries->x + 2][teries->y] == 0)) ||
                (teries->flag == 7 &&(a[teries->x][teries->y - 1] == 0 && a[teries->x][teries->y + 1] == 0 && a[teries->x + 2][teries->y] == 0)) ||
                (teries->flag == 8 &&(a[teries->x][teries->y + 1] == 0 && a[teries->x - 2][teries->y] == 0 && a[teries->x + 2][teries->y + 1] == 0)) ||
                (teries->flag == 9 &&(a[teries->x][teries->y - 1] == 0 && a[teries->x - 2][teries->y] == 0 && a[teries->x - 2][teries->y + 1] == 0)) ||
                (teries->flag == 10 &&(a[teries->x][teries->y - 1] == 0 && a[teries->x - 2][teries->y - 1] == 0 && a[teries->x + 2][teries->y] == 0)) ||
                (teries->flag == 11 &&(a[teries->x][teries->y + 1] == 0 && a[teries->x - 2][teries->y - 1] == 0 && a[teries->x - 2][teries->y] == 0)) ||
                (teries->flag == 12 &&(a[teries->x][teries->y - 1] == 0 && a[teries->x][teries->y + 1] == 0 && a[teries->x - 2][teries->y - 1] == 0)) ||
                (teries->flag == 13 &&(a[teries->x - 2][teries->y] == 0 && a[teries->x + 2][teries->y - 1] == 0 && a[teries->x + 2][teries->y] == 0)) ||
                (teries->flag == 14 &&(a[teries->x][teries->y - 1] == 0 && a[teries->x][teries->y + 1] == 0 && a[teries->x + 2][teries->y + 1] == 0)) ||
                (teries->flag == 15 &&(a[teries->x - 2][teries->y] == 0 && a[teries->x - 2][teries->y + 1] == 0 && a[teries->x + 2][teries->y] == 0)) ||
                (teries->flag == 16 &&(a[teries->x][teries->y + 1] == 0 && a[teries->x][teries->y - 1] == 0 && a[teries->x + 2][teries->y - 1] == 0)) ||
                (teries->flag == 17 &&(a[teries->x - 2][teries->y] == 0 && a[teries->x + 2][teries->y + 1] == 0 && a[teries->x + 2][teries->y] == 0)) ||
                (teries->flag == 18 &&(a[teries->x][teries->y - 1] == 0 && a[teries->x][teries->y + 1] == 0 && a[teries->x - 2][teries->y + 1] == 0)) ||
                (teries->flag == 19 &&(a[teries->x - 2][teries->y] == 0 && a[teries->x - 2][teries->y - 1] == 0 && a[teries->x + 2][teries->y] == 0)) )
        {
            return 1;
        }
    }
    return 0;
}

void CleanTeries(struct Teries* teries)//清除痕迹
{
    clean = 1;
    MakeTeries(teries);
    for(i = teries->x - 2; i <= teries->x + 4; i += 2)
    {
        for(j = teries->y - 2; j <= teries->y + 1; j ++)
        {
            if(a[i][j] == 0 && j > Framey)
            {
                gotoxy(i, j);
                printf("  ");
            }
        }
    }
}

void Del_Fullline(struct Teries* teries)//判断是否满行
{
    int k, del_rows = 0;
    for(j = Framey + Frame_hight - 1; j >= Framey+1; j --)
    {
        k = 0;
        for(i = Framex + 2; i < Framex + 2*Frame_width - 2; i += 2)
        {
            if(a[i][j] >= 1)
            {
                k ++;
                if(k == Frame_width - 2)
                {
                    for(k = Framex + 2; k < Framex + 2*Frame_width - 2; k += 2)
                    {
                        a[k][j] = 0;
                        gotoxy(k, j);
                        printf("  ");
                    }
                    for(k = j - 1; k > Framey; k --)
                    {
                        for(i = Framex + 2; i < Framex + 2 * Frame_width - 2; i += 2)
                        {
                            if(a[i][k] >= 1)
                            {
                                int ttt = a[i][k];
                                a[i][k] = 0;
                                gotoxy(i, k);
                                printf("  ");
                                a[i][k+1] = ttt;
                                gotoxy(i, k +1);
								color(cl[a[i][k+1] - 1]);
                                printf("█");
                            }
                        }
                    }
                    j ++;
                    del_rows ++;
                }
            }
        }
    }
    teries->sorce += 100 * del_rows;
    if(del_rows > 0 && (teries->sorce % 1000 == 0))
    {
        teries->speed -= 20;
    }
}

void Flag(struct Teries* teries)//随机产生方块
{
    teries->number ++;
    srand(time(NULL));
    if(teries->number == 1)
    {
        teries->flag = rand() % 19 + 1;
    }
    teries->next = rand() % 19 + 1;
}

void Gameplay()
{
    int n;
    struct Teries t;
    struct Teries *teries = &t;
    char ch;
    teries->number = 0;
    teries->speed = 300;
    teries->sorce = 0;
    teries->max = 0;
    while(1)
    {
        ma= ma > teries->sorce ? ma : teries->sorce;
        teries->max = ma;
        Flag(teries);
        temp = teries->flag;
        teries->x = Framex + 2 * Frame_width + 6;
        teries->y = Framey + 10;
        teries->flag = teries->next;
        PrintTeries(teries);
        teries->x = Framex + Frame_width;
        teries->y = Framey - 1;
        teries->flag = temp;
        while(1)  										//控制方块方向，直至方块不再下移
        {
label:
            PrintTeries(teries);					//打印俄罗斯方块
            Sleep(teries->speed);   					//延缓时间
            CleanTeries(teries);  						//清除痕迹
            temp1=teries->x;    						//记住中心方块横坐标的值
            temp2=teries->flag;    						//记住当前俄罗斯方块序号
            if(kbhit())       				  	 		//判断是否有键盘输入，有则用ch↓接收
            {
                ch=getch();
                if(ch==75)     							//按 ←键则向左动，中心横坐标减2
                {
                    teries->x-=2;
                }
                if(ch==77)     							//按 →键则向右动，中心横坐标加2
                {
                    teries->x+=2;
                }
                if(ch==80)     							//按 ↓键则加速下落
                {
                    if(ifMove(teries)!=0)
                    {
                        teries->y+=2;
                    }
                    if(ifMove(teries)==0)
                    {
                        teries->y=Framey+Frame_hight-2;
                    }
                }
                if(ch==72)     						//按 ↑键则变体,即当前方块顺时针转90度
                {
                    if( teries->flag>=2 && teries->flag<=3 )
                    {
                        teries->flag++;
                        teries->flag%=2;
                        teries->flag+=2;
                    }
                    if( teries->flag>=4 && teries->flag<=7 )
                    {
                        teries->flag++;
                        teries->flag%=4;
                        teries->flag+=4;
                    }
                    if( teries->flag>=8 && teries->flag<=11 )
                    {
                        teries->flag++;
                        teries->flag%=4;
                        teries->flag+=8;
                    }
                    if( teries->flag>=12 && teries->flag<=15 )
                    {
                        teries->flag++;
                        teries->flag%=4;
                        teries->flag+=12;
                    }
                    if( teries->flag>=16 && teries->flag<=19 )
                    {
                        teries->flag++;
                        teries->flag%=4;
                        teries->flag+=16;
                    }
                }
                if(ch == 32)     					//按空格键，暂停
                {
                    PrintTeries(teries);
                    while(1)
                    {
                        if(kbhit())   			//再按空格键，继续游戏
                        {
                            ch=getch();
                            if(ch == 32)
                            {
                                goto label;
                            }
                        }
                    }
                }
                if(ch == 27)
                {
                    system("cls");
                    memset(a,0,6400*sizeof(int));       //初始化BOX数组
                    welcom();
                }
                if(ifMove(teries)==0) 			//如果不可动，上面操作无效
                {
                    teries->x=temp1;
                    teries->flag=temp2;
                }
                else      						//如果可动，执行操作
                {
                    goto label;
                }
            }
            teries->y++;     					//如果没有操作指令，方块向下移动
            if(ifMove(teries)==0)  				//如果向下移动且不可动，方块放在此处
            {
                teries->y--;
                PrintTeries(teries);
                Del_Fullline(teries);
                break;
            }
        }
        for(i=teries->y-2; i<teries->y+2; i++)	//游戏结束条件：方块触到框顶位置
        {
            if(i==Framey)
            {
                system("cls");
                gotoxy(29,7);
                printf("   \n");
                color(12);
                printf("\t\t\t■■■■   ■     ■   ■■     \n");
                printf("\t\t\t■         ■■   ■   ■  ■   \n");
                printf("\t\t\t■■■     ■  ■ ■   ■   ■  \n");
                printf("\t\t\t■         ■   ■■   ■  ■   \n");
                printf("\t\t\t■■■■   ■     ■   ■■     \n");
                gotoxy(17,18);
                color(14);
                printf("我要重新玩一局-------1");
                gotoxy(44,18);
                printf("不玩了，退出吧-------2\n");
                int n;
                gotoxy(32,20);
                printf("选择【1/2】：");
                color(11);
                scanf("%d", &n);
                switch (n)
                {
                case 1:
                    system("cls");
                    Replay(teries);       	//重新开始游戏
                    break;
                case 2:
                    exit(0);
                    break;
                }
            }
        }
        teries->flag = teries->next;  			//清除下一个俄罗斯方块的图形(右边窗口)
        teries->x=Framex+2*Frame_width+6;
        teries->y=Framey+10;
        CleanTeries(teries);
    }

}

void close()
{
    exit(0);
}

/**
* 按键说明
*/
void explation()
{
    int i,j = 1;
    system("cls");
    color(13);
    gotoxy(32,3);
    printf("按键说明");
    color(2);
    for (i = 6; i <= 16; i++)   //输出上下边框===
    {
        for (j = 15; j <= 60; j++)  //输出左右边框||
        {
            gotoxy(j, i);
            if (i == 6 || i == 16) printf("=");
            else if (j == 15 || j == 59) printf("||");
        }
    }
    color(3);
    gotoxy(18,7);
    printf("tip1: 玩家可以通过 ← →方向键来移动方块");
    color(10);
    gotoxy(18,9);
    printf("tip2: 通过 ↑使方块旋转");
    color(14);
    gotoxy(18,11);
    printf("tip3: 通过 ↓加速方块下落");
    color(11);
    gotoxy(18,13);
    printf("tip4: 按空格键暂停游戏，再按空格键继续");
    color(4);
    gotoxy(18,15);
    printf("tip5: 按ESC退出游戏");
    getch();                //按任意键返回主界面
    system("cls");
    main();
}

/**
* 游戏规则
*/
void regulation()
{
    int i,j = 1;
    system("cls");
    color(13);
    gotoxy(34,3);
    printf("游戏规则");
    color(2);
    for (i = 6; i <= 18; i++)   //输出上下边框===
    {
        for (j = 12; j <= 70; j++)  //输出左右边框||
        {
            gotoxy(j, i);
            if (i == 6 || i == 18) printf("=");
            else if (j == 12 || j == 69) printf("||");
        }
    }
    color(12);
    gotoxy(16,7);
    printf("tip1: 不同形状的小方块从屏幕上方落下，玩家通过调整");
    gotoxy(22,9);
    printf("方块的位置和方向，使他们在屏幕底部拼出完整的");
    gotoxy(22,11);
    printf("一条或几条");
    color(14);
    gotoxy(16,13);
    printf("tip2: 每消除一行，积分增加100");
    color(11);
    gotoxy(16,15);
    printf("tip3: 每累计1000分，会提升一个等级");
    color(10);
    gotoxy(16,17);
    printf("tip4: 提升等级会使方块下落速度加快，游戏难度加大");
    getch();                //按任意键返回主界面
    system("cls");
    welcom();
}

void Replay(struct Tetris *teries)
{
    system("cls");                  	//清屏
    memset(a,0,6400*sizeof(int));       //初始化BOX数组，否则不会正常显示方块，导致游戏直接结束
    DrawGameframe();       	//制作游戏窗口
    Gameplay(); 			//开始游戏
}

int main()
{
    title();
    flower();
    welcom();
    return 0;
}
