#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>






char high[100] = "��";
char medium[100] = "��";
char low[100] = "��";
char calculate[100] = "�W�v";

int PriceHigh = 100;
int PriceMedium = 50;
int PriceLow = 20;

typedef struct Node{
    char name[100];         // ���i��
    double price;        //�P��
    int number;         // ��
    double tprice;      // ���v���i
    struct Node *next;
}node;

int main(void)
{
    //File
    FILE *fp;
    //Time
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    struct Node *head, *pt, *p;
    head = (struct Node *)malloc(sizeof(node));
    p = head;
    char fname[50];
    sprintf(fname, "%d_%d_%d_%d_%d_%d_����.csv", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    char KeyInput[100] = " ";

    int TotalNumber = 0;
    float TotalBenefit = 0;
    int count = 0;

    while (true){
        while (true)
        {
            printf("���i���́i���A���A��j,���������͂��Ă��������A�h�W�v�h����͂��ďW�v����B\n");
            printf("�i��:\n");
            scanf("%s", &KeyInput);
            if (strcmp(KeyInput, calculate) == 0)
            {
                printf("�W�v���܂��B\n");
                head = head->next;
                p->next = NULL;
                break;
            }
            while (true)
            {
                if (strcmp(KeyInput, high) == 0)
                {
                    pt = (struct Node *)malloc(sizeof(node));
                    strcpy(pt->name, KeyInput);
                    pt->price = PriceHigh;
                    break;
                }
                else if (strcmp(KeyInput, medium) == 0)
                {
                    pt = (struct Node *)malloc(sizeof(node));
                    strcpy(pt->name, KeyInput);
                    pt->price = PriceMedium;
                    break;
                }
                else if (strcmp(KeyInput, low) == 0)
                {
                    pt = (struct Node *)malloc(sizeof(node));
                    strcpy(pt->name, KeyInput);
                    pt->price = PriceLow;
                    break;
                }
                else
                {
                    printf("�i����������x���͂��Ă��������B\n");
                    scanf("%s", &KeyInput);
                }
            }


            printf("�����:\n");
            scanf("%d", &pt->number);
            while (true)
            {
                if (pt->number > 0)
                {
                    break;
                }
                else
                {
                    printf("����������x���͂��Ă��������B\n");
                    getchar();
                    scanf("%d", &pt->number);
                }
            }
            pt->tprice = pt->price * pt->number;
            count++;

            printf("���i %s ��o�^���܂����B\n", pt->name);
            p->next = pt;
            p = pt;
        }


        p = head;
        while (p != NULL)
        {
            TotalNumber = TotalNumber + p->number;
            TotalBenefit = TotalBenefit + p->tprice;
            p = p->next;
        }



        //������̓t�@�C������̕����B
        //
        fp = fopen(fname, "w");
        if (fp == NULL)
        {
            printf("%s�t�@�C�����J���܂���\n", fname);
            getchar();
            return -1;
        }
        fprintf(fp, " \n");
        fprintf(fp, "���͎���, %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
        fprintf(fp, " \n");
        fprintf(fp, "���v������F,%d\n", TotalNumber);
        fprintf(fp, "���v���z�F,%f\n", TotalBenefit);
        fprintf(fp, " \n");
        fprintf(fp, " \n");
        fprintf(fp, "�ڍׁF\n");

        fprintf(fp, "���i����,�P��,�����,���v\n");
        fprintf(fp, " \n");
        p = head;
        while (p != NULL)
        {
            fprintf(fp, "%s,%f,%d,%f\n", p->name, p->price, p->number, p->tprice);
            p = p->next;
        }
        fclose(fp);
        printf("%s�t�@�C���������݂��I���܂����A�����l�ł��B\n", fname);
        getchar();
        getchar();
        return 0;
    }
    
}