#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#define Framex 13
#define Framey 3
#define Frame_hight 20
#define Frame_width 18

int i,j, temp, temp1, temp2; //�����м�ֵ�ֱ��ס��ת�����������ֵ

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
HANDLE hOut;//����̨���

int color(int c);//
void gotoxy(int x, int y);//�ƶ���굽ָ��λ��
void DrawGameframe();//������Ϸ�ѿ�
void Flag(struct Teries* s);//������������������
void MakeTeries(struct Teries*);//��������˹����
void PrintTeries(struct Teries*);//��ӡ����˹����
void CleanTeries(struct Teries*);//��������˹����ĺۼ�
int ifMove(struct Teries*);//�ж��Ƿ��ƶ�������ֵΪ1ʱ�ƶ��������ƶ�
void Del_Fullline(struct Teries*);//�ж��Ƿ����У���ɾ�����еĶ���˹����
void Gameplay();//��ʼ��Ϸ
void regulation();//��Ϸ����
void explation();//����˵��
void welcom();//��ӭ����
void Reply(struct Teries *teries);//���¿�ʼ��Ϸ
void title();//��ӭ�����Ϸ�����
void flower();//��ӭ�����ַ�װ��
void close();//�ر���Ϸ



int color(int c)//�������ֵ���ɫ
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
    return 0;
}

void gotoxy(int x, int y)//����������ʾλ��
{
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void title()//��Ʊ��ⲿ��
{
    color(15);
    gotoxy(24,3);
    printf("Ȥ  ζ  ��  ��  ˹  ��  ��\n");
    color(11);
    gotoxy(18,5);
    printf("��");
    gotoxy(18,6);
    printf("����");
    gotoxy(18,7);
    printf("��");

    color(14);
    gotoxy(26,6);
    printf("����");
    gotoxy(28,7);
    printf("����");

    color(10);
    gotoxy(36,6);
    printf("����");
    gotoxy(36,7);
    printf("����");

    color(13);
    gotoxy(45,5);
    printf("��");
    gotoxy(45,6);
    printf("��");
    gotoxy(45,7);
    printf("��");
    gotoxy(45,8);
    printf("��");

    color(12);
    gotoxy(56,6);
    printf("��");
    gotoxy(54,7);
    printf("������");
}

void flower()//�����ַ�װ��
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
    printf("�����");
}

void welcom()//��Ʋ˵�ѡ��߿�
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
    ��Ʋ˵�ѡ���е�����
    */
    int n;
    color(12);
    gotoxy(25,12);
    printf("1. ��ʼ��Ϸ");

    gotoxy(40,12);
    printf("2.����˵��");

    gotoxy(25,17);
    printf("3.��Ϸ����");

    gotoxy(40,17);
    printf("4.�˳���Ϸ");

    gotoxy(21,22);
    color(3);
    printf("��ѡ��[1 2 3 4]:[ ]\b\b");
    color(14);
    scanf("%d",&n);
    switch (n)
    {
    case 1:
        system("cls");//��������
        DrawGameframe();
        Gameplay();
        break;
    case 2:
        explation();      	//����˵������
        break;
    case 3:
        regulation();     	//��Ϸ������
        break;
    case 4:
        close();    		//�ر���Ϸ����
        break;
    }
}

//��Ϸ���崰�����
void DrawGameframe()//������Ϸ����
{
    gotoxy(Framex +Frame_width - 7, Framey - 2);
    color(11);
    printf("Ȥζ����˹����");
    gotoxy(Framex + 2 * Frame_width + 3, Framey + 7);
    color(2);
    printf("***********");
    gotoxy(Framex +2 * Frame_width + 13, Framey + 7);
    color(3);
    printf("��һ���ֵķ��飺 ");
    gotoxy(Framex + 2 * Frame_width  + 3, Framey + 13);
    color(2);
    printf("**********");
    gotoxy(Framex + 2 * Frame_width + 3, Framey + 17);
    color(14);
    printf("up������ת");
    gotoxy(Framex + 2 * Frame_width + 3, Framey + 19);
    printf("�ո������ͣ");
    gotoxy(Framex + 2 * Frame_width + 3, Framey + 15);
    printf("Esc���˳���Ϸ");

    gotoxy(Framex, Framey);
    color(12);
    printf("�� ");
    gotoxy(Framex + 2 * Frame_width - 2, Framey);
    printf("��");
    gotoxy(Framex, Framey + Frame_hight);
    printf("��");
    gotoxy(Framex+ 2 * Frame_width - 2, Framey + Frame_hight);
    printf("��");

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

//��������˹����
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
    case 1://���ַ���
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
    case 2://����ֱ�߷���
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
    case 3://��ֱֱ�߷���
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
    case 4://T�ַ���
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
    case 5://˳ʱ��90T�ַ���
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
    case 6://˳ʱ��180T�ַ���
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
    case 7://˳ʱ��270T�ַ���
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
    case 8://z�ַ���
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
    case 9://˳ʱ��Z��
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
    case 10://��Z��
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
    case 11://˳ʱ�뷴Z��
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

void PrintTeries(struct Teries* teries)//��ӡ����
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
                printf("��");
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

void CleanTeries(struct Teries* teries)//����ۼ�
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

void Del_Fullline(struct Teries* teries)//�ж��Ƿ�����
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
                                printf("��");
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

void Flag(struct Teries* teries)//�����������
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
        while(1)  										//���Ʒ��鷽��ֱ�����鲻������
        {
label:
            PrintTeries(teries);					//��ӡ����˹����
            Sleep(teries->speed);   					//�ӻ�ʱ��
            CleanTeries(teries);  						//����ۼ�
            temp1=teries->x;    						//��ס���ķ���������ֵ
            temp2=teries->flag;    						//��ס��ǰ����˹�������
            if(kbhit())       				  	 		//�ж��Ƿ��м������룬������ch������
            {
                ch=getch();
                if(ch==75)     							//�� ���������󶯣����ĺ������2
                {
                    teries->x-=2;
                }
                if(ch==77)     							//�� ���������Ҷ������ĺ������2
                {
                    teries->x+=2;
                }
                if(ch==80)     							//�� �������������
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
                if(ch==72)     						//�� ���������,����ǰ����˳ʱ��ת90��
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
                if(ch == 32)     					//���ո������ͣ
                {
                    PrintTeries(teries);
                    while(1)
                    {
                        if(kbhit())   			//�ٰ��ո����������Ϸ
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
                    memset(a,0,6400*sizeof(int));       //��ʼ��BOX����
                    welcom();
                }
                if(ifMove(teries)==0) 			//������ɶ������������Ч
                {
                    teries->x=temp1;
                    teries->flag=temp2;
                }
                else      						//����ɶ���ִ�в���
                {
                    goto label;
                }
            }
            teries->y++;     					//���û�в���ָ����������ƶ�
            if(ifMove(teries)==0)  				//��������ƶ��Ҳ��ɶ���������ڴ˴�
            {
                teries->y--;
                PrintTeries(teries);
                Del_Fullline(teries);
                break;
            }
        }
        for(i=teries->y-2; i<teries->y+2; i++)	//��Ϸ�������������鴥����λ��
        {
            if(i==Framey)
            {
                system("cls");
                gotoxy(29,7);
                printf("   \n");
                color(12);
                printf("\t\t\t��������   ��     ��   ����     \n");
                printf("\t\t\t��         ����   ��   ��  ��   \n");
                printf("\t\t\t������     ��  �� ��   ��   ��  \n");
                printf("\t\t\t��         ��   ����   ��  ��   \n");
                printf("\t\t\t��������   ��     ��   ����     \n");
                gotoxy(17,18);
                color(14);
                printf("��Ҫ������һ��-------1");
                gotoxy(44,18);
                printf("�����ˣ��˳���-------2\n");
                int n;
                gotoxy(32,20);
                printf("ѡ��1/2����");
                color(11);
                scanf("%d", &n);
                switch (n)
                {
                case 1:
                    system("cls");
                    Replay(teries);       	//���¿�ʼ��Ϸ
                    break;
                case 2:
                    exit(0);
                    break;
                }
            }
        }
        teries->flag = teries->next;  			//�����һ������˹�����ͼ��(�ұߴ���)
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
* ����˵��
*/
void explation()
{
    int i,j = 1;
    system("cls");
    color(13);
    gotoxy(32,3);
    printf("����˵��");
    color(2);
    for (i = 6; i <= 16; i++)   //������±߿�===
    {
        for (j = 15; j <= 60; j++)  //������ұ߿�||
        {
            gotoxy(j, i);
            if (i == 6 || i == 16) printf("=");
            else if (j == 15 || j == 59) printf("||");
        }
    }
    color(3);
    gotoxy(18,7);
    printf("tip1: ��ҿ���ͨ�� �� ����������ƶ�����");
    color(10);
    gotoxy(18,9);
    printf("tip2: ͨ�� ��ʹ������ת");
    color(14);
    gotoxy(18,11);
    printf("tip3: ͨ�� �����ٷ�������");
    color(11);
    gotoxy(18,13);
    printf("tip4: ���ո����ͣ��Ϸ���ٰ��ո������");
    color(4);
    gotoxy(18,15);
    printf("tip5: ��ESC�˳���Ϸ");
    getch();                //�����������������
    system("cls");
    main();
}

/**
* ��Ϸ����
*/
void regulation()
{
    int i,j = 1;
    system("cls");
    color(13);
    gotoxy(34,3);
    printf("��Ϸ����");
    color(2);
    for (i = 6; i <= 18; i++)   //������±߿�===
    {
        for (j = 12; j <= 70; j++)  //������ұ߿�||
        {
            gotoxy(j, i);
            if (i == 6 || i == 18) printf("=");
            else if (j == 12 || j == 69) printf("||");
        }
    }
    color(12);
    gotoxy(16,7);
    printf("tip1: ��ͬ��״��С�������Ļ�Ϸ����£����ͨ������");
    gotoxy(22,9);
    printf("�����λ�úͷ���ʹ��������Ļ�ײ�ƴ��������");
    gotoxy(22,11);
    printf("һ������");
    color(14);
    gotoxy(16,13);
    printf("tip2: ÿ����һ�У���������100");
    color(11);
    gotoxy(16,15);
    printf("tip3: ÿ�ۼ�1000�֣�������һ���ȼ�");
    color(10);
    gotoxy(16,17);
    printf("tip4: �����ȼ���ʹ���������ٶȼӿ죬��Ϸ�ѶȼӴ�");
    getch();                //�����������������
    system("cls");
    welcom();
}

void Replay(struct Tetris *teries)
{
    system("cls");                  	//����
    memset(a,0,6400*sizeof(int));       //��ʼ��BOX���飬���򲻻�������ʾ���飬������Ϸֱ�ӽ���
    DrawGameframe();       	//������Ϸ����
    Gameplay(); 			//��ʼ��Ϸ
}

int main()
{
    title();
    flower();
    welcom();
    return 0;
}
