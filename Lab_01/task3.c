#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int is_identifier(const char *word)
{
    const char *keywords[] = {
        "auto", "break", "case", "char", "const", "continue", "default", "do", "double",
        "else", "enum", "extern", "float", "for", "goto", "if", "inline", "int", "long",
        "register", "restrict", "return", "short", "signed", "sizeof", "static",
        "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"};

    if (isdigit(word[0]))
    {
        return 0;
    }

    int n = sizeof(keywords) / sizeof(keywords[0]);
    for (int i = 0; i < n; i++)
    {
        if (strcmp(word, keywords[i]) == 0)
            return 0;
    }
    return 1;
}

int main()
{

    FILE *fp = NULL;
    char ch;
    char new_word[40];
    int index = 0;

    fp = fopen("task3.txt", "r");
    if (fp == NULL)
    {
        printf("file not found");
        exit(1);
    }

    while ((ch = fgetc(fp)) != EOF)
    {
        if (isalnum(ch) || ch == '_')
        {
            index = 0;
            new_word[index] = ch;
            index++;

            while ((ch = fgetc(fp)) != EOF && (isalnum(ch) || ch == '_'))
            {
                new_word[index] = ch;
                index++;
            }

            new_word[index] = '\0';

            // printf("%s@ ", new_word);

            if (is_identifier(new_word) == 1)
            {
                printf("%s : Valid Indentifier \n", new_word);
            }
            else
            {
                printf("%s : Invalid Indentifier \n", new_word);
            }
        }
    }

    fclose(fp);

    return 0;
}