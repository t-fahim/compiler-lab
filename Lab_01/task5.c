#include <stdio.h>

int main()
{
    FILE *fp = fopen("task5.txt", "r");
    if (fp == NULL)
    {
        printf("File not found\n");
        return 1;
    }

    char ch, next_ch;

    while ((ch = fgetc(fp)) != EOF)
    {
        int next_ch = fgetc(fp);
        if (next_ch != EOF)
        {
            // Check 2-character operators
            if (ch == '+' && next_ch == '+')
            {
                printf("++ : arithmetic Operator\n");
                continue;
            }
            else if (ch == '-' && next_ch == '-')
            {
                printf("-- : arithmetic Operator\n");
                continue;
            }
            else if (ch == '=' && next_ch == '=')
            {
                printf("== : relational Operator\n");
                continue;
            }
            else if (ch == '!' && next_ch == '=')
            {
                printf("!= : relational Operator\n");
                continue;
            }
            else if (ch == '>' && next_ch == '=')
            {
                printf(">= : relational Operator\n");
                continue;
            }
            else if (ch == '<' && next_ch == '=')
            {
                printf("<= : relational Operator\n");
                continue;
            }
            else if (ch == '&' && next_ch == '&')
            {
                printf("&& : logical Operator\n");
                continue;
            }
            else if (ch == '|' && next_ch == '|')
            {
                printf("|| : logical Operator\n");
                continue;
            }
            else if (ch == '+' && next_ch == '=')
            {
                printf("+= : assignment Operator\n");
                continue;
            }
            else if (ch == '-' && next_ch == '=')
            {
                printf("-= : assignment Operator\n");
                continue;
            }
            else if (ch == '*' && next_ch == '=')
            {
                printf("*= : assignment Operator\n");
                continue;
            }
            else if (ch == '/' && next_ch == '=')
            {
                printf("/= : assignment Operator\n");
                continue;
            }
            else
            {
                ungetc(next_ch, fp);
            }
        }

        // Single-character operators
        if (ch == '=')
            printf("= : assignment Operator\n");
        else if (ch == '+')
            printf("+ : arithmetic Operator\n");
        else if (ch == '-')
            printf("- : arithmetic Operator\n");
        else if (ch == '*')
            printf("* : arithmetic Operator\n");
        else if (ch == '/')
            printf("/ : arithmetic Operator\n");
        else if (ch == '%')
            printf("%% : arithmetic Operator\n");
        else if (ch == '>')
            printf("> : relational Operator\n");
        else if (ch == '<')
            printf("< : relational Operator\n");
        else if (ch == '!')
            printf("! : logical Operator\n");
    }

    fclose(fp);
    return 0;
}
