#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void check_string(const char *word)
{
    int len = strlen(word);

    if (len >= 2 && word[0] == '"' && word[len-1] == '"')
        printf("%s : Valid String Literal\n", word);
    else if (len >= 2 && word[0] == '"' && word[len-1] != '"')
        printf("%s : InValid String Literal\n", word);
    else if (len >= 1 && word[0] == '"' && word[len-1] != '"')
        printf("%s : Unterminated String Literal\n", word);
    else if (len >= 2 && word[0] == '\'' && word[len-1] == '\'')
        printf("%s : Multiple Character Constant(Invalid)\n", word);
    else if (len = 3 && word[0] == '\'' && word[len-1] == '\'')
    {
        printf("%s : valid Character Constant\n", word);
    }
    else if (len = 2 && word[0] == '\'' && word[len-1] == '\'')
    {
        printf("%s : Empty Character Constant(Invalid)\n", word);
    }
    else{
        printf("%s : Unterminated Character Constant(Invalid)\n", word);
    }
    
    
}

int main()
{
    FILE *fp = fopen("task8.txt", "r");
    if (!fp) {
        printf("file not found");
        return 1;
    }

    char ch;
    char buffer[30];
    int i;

    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch == '"')
        {
            i = 0;
            buffer[i++] = ch;

            while ((ch = fgetc(fp)) != EOF && ch != '\n')
            {
                buffer[i++] = ch;
                if (ch == '"')
                    break;
            }

            buffer[i] = '\0';
            ///printf("@%s@\n", buffer);
            check_string(buffer);
        }
    }

    fclose(fp);
    return 0;
}
