#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int is_keyword(const char *word)
{
    const char *keywords[] = {
        "auto", "break", "case", "char", "const", "continue", "default", "do", "double",
        "else", "enum", "extern", "float", "for", "goto", "if", "inline", "int", "long",
        "register", "restrict", "return", "short", "signed", "sizeof", "static",
        "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"};

    int n = sizeof(keywords) / sizeof(keywords[0]);
    for (int i = 0; i < n; i++)
    {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

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
        if (isalpha(ch))
        {
            index = 0;
            new_word[index] = ch;
            index++;

            while ((ch = fgetc(fp)) != EOF && isalpha(ch))
            {
                new_word[index] = ch;
                index++;
            }

            new_word[index] = '\0';

            // printf("%s@ ", new_word);

            if (is_keyword(new_word))
            {
                printf("%s : keyword \n", new_word);
            }
        }
    }

    fclose(fp);

    return 0;
}