#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define MAX 1048575

int main(int argc, char *argv[])
{
    char *start;     // �_�l��}
    char *source;    // �ӷ��ɮ�
    char chr[3];     // Ū�����r��(��Ӧr�����@�ӳ��)
    int hex;         // �NŪ�����r���ഫ����Ӣ̶i��줸�A��X�A�ର�̤��i��
    int f = 0;       // �P�_��X��m
    int h_start = 0; // �_�l��}�ഫ���̶i��줸�A��X�A�ର�̤��i��

    if (argc == 4) // �]�t-f�Ѽ�
    {
        start = argv[1] + 2; // �_�l��}���Ĥ@�ӰѼƪ��ĤT�Ӧr���}�l
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

    for (int s = 0; s < 5; s++) // �_�l��}�ഫ���̶i��줸
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

    while (fscanf(fp1, "%c%c", &chr[0], &chr[1]) != EOF) // Ū���ӷ��ɮת��r��(��Ӧr�����@��byte)
    {
        // �NŪ������Ӧr�����ഫ���̶i��

        for (int i = 0; i < 2; i++)
        {
            if (chr[i] - 48 < 10)
                chr[i] = chr[i] - 48;
            else
                chr[i] = chr[i] - 55;
        }
        hex = chr[0] * 16 + chr[1];

        if (f) // ��̤��i���X��.mem�ɮ�
        {
            fprintf(fp2, "%05x %02x\n", h_start, hex);
        }
        else // ��̤��i���X��ù�
        {
            printf("%05x %02x\n", h_start, hex);
        }

        h_start++;

        // �˴��O����O�_�W�X�d��
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