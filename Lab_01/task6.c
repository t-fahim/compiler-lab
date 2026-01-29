#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main()
{

    FILE *fp = NULL;
    char ch;
    char new_word[40];
    int index = 0;

    fp = fopen("task2.txt", "r");
    if (fp == NULL)
    {
        printf("file not found");
        exit(1);
    }

    while ((ch = fgetc(fp)) != EOF)
    {
        if (ispunct(ch))
        {
            printf("%c : Punctuation Symbol\n", ch);
        }
        else if (!isdigit(ch) && !isalpha(ch) && !isspace(ch))
        {
            printf("%c : special Symbol\n", ch);
        }
    }

    fclose(fp);

    return 0;
}