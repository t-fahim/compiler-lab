#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main()
{

    FILE *fp = NULL;
    char ch, next_ch;

    fp = fopen("task7.txt", "r");
    if (fp == NULL)
    {
        printf("file not found");
        exit(1);
    }

    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch == '/')
        {
            next_ch = fgetc(fp);
            if (next_ch == '/')
            {
                printf("Single-line comments\n");
                while ((ch = fgetc(fp)) != EOF && ch != '\n');
            }
            else if (next_ch == '*')
            {
                int flag = 0;
                while ((ch = fgetc(fp)) != EOF)
                {
                    next_ch = fgetc(fp);
                    // printf("%c\n",ch);
                    // printf("%c\n", next_ch);
                    if (ch == '*' && next_ch == '/')
                    {
                        flag = 1;
                        break;
                    }
                    ungetc(next_ch, fp);
                }

                if (flag == 1)
                {
                    printf("Multi-line comments\n");
                }
                else
                {
                    printf("Unterminated Multi-line comments, Lexical error\n");
                }
            }
        }
    }

    fclose(fp);

    return 0;
}