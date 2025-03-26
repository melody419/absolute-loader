#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define MAX 1048575

int main(int argc, char *argv[])
{
    char *start;     // 起始位址
    char *source;    // 來源檔案
    char chr[3];     // 讀取的字元(兩個字元為一個單位)
    int hex;         // 將讀取的字元轉換為兩個十進制位元，輸出再轉為十六進制
    int f = 0;       // 判斷輸出位置
    int h_start = 0; // 起始位址轉換為十進制位元，輸出再轉為十六進制

    if (argc == 4) // 包含-f參數
    {
        start = argv[1] + 2; // 起始位址為第一個參數的第三個字元開始
        f = 1;
        source = argv[3];
    }
    else if (argc == 3)
    {
        start = argv[1] + 2;
        source = argv[2];
    }

    FILE *fp1 = fopen(source, "r");
    FILE *fp2 = fopen("AbsLoader.mem", "w");

    for (int s = 0; s < 5; s++) // 起始位址轉換為十進制位元
    {
        if (start[s] - 48 < 10)
        {
            start[s] -= 48;
        }
        else
        {
            start[s] -= 55;
        }
        h_start = h_start * 16 + start[s];
    }

    while (fscanf(fp1, "%c%c", &chr[0], &chr[1]) != EOF) // 讀取來源檔案的字元(兩個字元為一個byte)
    {
        // 將讀取的兩個字元先轉換為十進制

        for (int i = 0; i < 2; i++)
        {
            if (chr[i] - 48 < 10)
                chr[i] = chr[i] - 48;
            else
                chr[i] = chr[i] - 55;
        }
        hex = chr[0] * 16 + chr[1];

        if (f) // 轉十六進制輸出到.mem檔案
        {
            fprintf(fp2, "%05x %02x\n", h_start, hex);
        }
        else // 轉十六進制輸出到螢幕
        {
            printf("%05x %02x\n", h_start, hex);
        }

        h_start++;

        // 檢測記憶體是否超出範圍
        if (h_start > MAX)
        {
            printf("Memory Overflow\n");
            return 0;
        }
    }
    fclose(fp1);
    fclose(fp2);

    return 0;
}