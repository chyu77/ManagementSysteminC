#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>






char high[100] = "高";
char medium[100] = "中";
char low[100] = "低";
char calculate[100] = "集計";

int PriceHigh = 100;
int PriceMedium = 50;
int PriceLow = 20;

typedef struct Node{
    char name[100];         // 商品名
    double price;        //単価
    int number;         // 個数
    double tprice;      // 合計価格
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
    sprintf(fname, "%d_%d_%d_%d_%d_%d_売上.csv", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    char KeyInput[100] = " ";

    int TotalNumber = 0;
    float TotalBenefit = 0;
    int count = 0;

    while (true){
        while (true)
        {
            printf("商品名称（高、中、低）,売上個数を入力してください、”集計”を入力して集計する。\n");
            printf("品名:\n");
            scanf("%s", &KeyInput);
            if (strcmp(KeyInput, calculate) == 0)
            {
                printf("集計します。\n");
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
                    printf("品名をもう一度入力してください。\n");
                    scanf("%s", &KeyInput);
                }
            }


            printf("売上個数:\n");
            scanf("%d", &pt->number);
            while (true)
            {
                if (pt->number > 0)
                {
                    break;
                }
                else
                {
                    printf("個数をもう一度入力してください。\n");
                    getchar();
                    scanf("%d", &pt->number);
                }
            }
            pt->tprice = pt->price * pt->number;
            count++;

            printf("商品 %s を登録しました。\n", pt->name);
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



        //こちらはファイル操作の部分。
        //
        fp = fopen(fname, "w");
        if (fp == NULL)
        {
            printf("%sファイルが開けません\n", fname);
            getchar();
            return -1;
        }
        fprintf(fp, " \n");
        fprintf(fp, "入力時間, %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
        fprintf(fp, " \n");
        fprintf(fp, "合計売上個数：,%d\n", TotalNumber);
        fprintf(fp, "合計金額：,%f\n", TotalBenefit);
        fprintf(fp, " \n");
        fprintf(fp, " \n");
        fprintf(fp, "詳細：\n");

        fprintf(fp, "商品名称,単価,売上個数,合計\n");
        fprintf(fp, " \n");
        p = head;
        while (p != NULL)
        {
            fprintf(fp, "%s,%f,%d,%f\n", p->name, p->price, p->number, p->tprice);
            p = p->next;
        }
        fclose(fp);
        printf("%sファイル書き込みが終わりました、お疲れ様です。\n", fname);
        getchar();
        getchar();
        return 0;
    }
    
}