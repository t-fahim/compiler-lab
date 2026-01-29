#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{

    FILE *fp = NULL;
    char ch;
    int character = 0;
    int word = 0;
    int line = 0;
    int word_flag = 0;

    fp = fopen("task1.txt", "r");
    if (fp == NULL)
    {
        printf("file not found");
        exit(1);
    }

    // reading character by character
    while ((ch = fgetc(fp)) != EOF)
    {
        character++;
        if (ch == '\n')
        {
            line++;
        }

        if (isspace(ch))
        {
            word_flag = 1;
        }
        else if (word_flag == 1)
        {
            word_flag = 0;
            word++;
        }

        // printf("%c ",ch);
    }

    word++;

    fclose(fp);
    printf("Characters: %d\n", character);
    printf("Words: %d\n", word);
    printf("Lines: %d\n", line);

    return 0;
}