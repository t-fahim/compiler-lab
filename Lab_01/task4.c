#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int is_number(const char *word)
{
    int flag = 0;
    int i = 0;
    while (word[i] != '\0')
    {
        if (word[i] == '.')
        {
            flag++;
        }
        i++;
    }
    if (flag > 1)
    {
        return 0;
    }
    else if (flag == 1)
    {
        return 1;
    }
    else
    {
        return 2;
    }
}

int main()
{

    FILE *fp = NULL;
    char ch;
    char new_word[40];
    int index = 0;

    fp = fopen("task4.txt", "r");
    if (fp == NULL)
    {
        printf("file not found");
        exit(1);
    }

    while ((ch = fgetc(fp)) != EOF)
    {
        if (isdigit(ch) || ch == '.')
        {
            index = 0;
            new_word[index] = ch;
            index++;

            while ((ch = fgetc(fp)) != EOF && (isdigit(ch) || ch == '.'))
            {
                new_word[index] = ch;
                index++;
            }

            new_word[index] = '\0';

            // printf("%s@ ", new_word);

            if (is_number(new_word) == 1)
            {
                printf("%s : Float \n", new_word);
            }
            else if (is_number(new_word) == 2)
            {
                printf("%s : Integer \n", new_word);
            }
            else
            {
                printf("%s : Not a number \n", new_word);
            }
        }
    }

    fclose(fp);

    return 0;
}