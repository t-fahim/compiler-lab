#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char *keywords[] = {
    "auto","break","case","char","const","continue","default","do","double",
    "else","enum","extern","float","for","goto","if","inline","int","long",
    "register","restrict","return","short","signed","sizeof","static",
    "struct","switch","typedef","union","unsigned","void","volatile","while"
};
int keyword_count = 34;

int is_keyword(const char *word) {
    for (int i = 0; i < keyword_count; i++) {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int is_identifier(const char *word) {
    if (!isalpha(word[0]) && word[0] != '_')
        return 0;

    for (int i = 1; word[i] != '\0'; i++)
        if (!isalnum(word[i]) && word[i] != '_')
            return 0;

    return !is_keyword(word);
}

int is_number(const char *word) {
    int dots = 0;
    for (int i = 0; word[i] != '\0'; i++) {
        if (word[i] == '.') dots++;
        else if (!isdigit(word[i])) return 0;
    }
    return dots <= 1;
}

int main() {
    FILE *fp = fopen("task9.txt", "r");
    if (!fp) {
        printf("File not found!\n");
        return 1;
    }

    char ch;

    while ((ch = fgetc(fp)) != EOF) {

        /* -----------------------------------------
           IDENTIFIERS & KEYWORDS
        ------------------------------------------ */
        if (isalpha(ch) || ch == '_') {
            char word[100];
            int i = 0;
            word[i++] = ch;

            while ((ch = fgetc(fp)) != EOF && (isalnum(ch) || ch == '_'))
                word[i++] = ch;

            word[i] = '\0';
            ungetc(ch, fp);

            if (is_keyword(word))
                printf("%s : Keyword\n", word);
            else
                printf("%s : Identifier\n", word);

            continue;
        }

        /* -----------------------------------------
           NUMBERS (INTEGER / FLOAT)
        ------------------------------------------ */
        if (isdigit(ch)) {
            char num[100];
            int i = 0;
            num[i++] = ch;

            while ((ch = fgetc(fp)) != EOF && (isdigit(ch) || ch == '.'))
                num[i++] = ch;

            num[i] = '\0';
            ungetc(ch, fp);

            if (is_number(num)) {
                if (strchr(num, '.'))
                    printf("%s : Float Constant\n", num);
                else
                    printf("%s : Integer Constant\n", num);
            } else {
                printf("%s : Invalid Number\n", num);
            }
            continue;
        }

        /* -----------------------------------------
           STRING LITERALS
        ------------------------------------------ */
        if (ch == '"') {
            char buffer[200];
            int i = 0;
            buffer[i++] = ch;

            while ((ch = fgetc(fp)) != EOF && ch != '"') {
                if (ch == '\n') break;
                buffer[i++] = ch;
            }

            buffer[i++] = '"';
            buffer[i] = '\0';

            if (ch == '"')
                printf("%s : String Literal\n", buffer);
            else
                printf("%s : Unterminated String Literal\n", buffer);

            continue;
        }

        /* -----------------------------------------
           CHARACTER CONSTANTS
        ------------------------------------------ */
        if (ch == '\'') {
            char buf[10];
            int i = 0;
            buf[i++] = ch;
            buf[i++] = fgetc(fp);
            buf[i++] = fgetc(fp);
            buf[i] = '\0';

            if (buf[2] == '\'')
                printf("%s : Character Constant\n", buf);
            else
                printf("%s : Invalid Character Constant\n", buf);

            continue;
        }

        /* -----------------------------------------
           COMMENTS
        ------------------------------------------ */
        if (ch == '/') {
            char next = fgetc(fp);

            if (next == '/') {
                printf("// : Single-line Comment\n");
                while ((ch = fgetc(fp)) != EOF && ch != '\n');
                continue;
            }

            else if (next == '*') {
                printf("/* */ : Multi-line Comment\n");
                char prev = 0;
                while ((ch = fgetc(fp)) != EOF) {
                    if (prev == '*' && ch == '/') break;
                    prev = ch;
                }
                continue;
            }

            ungetc(next, fp);
        }

        /* -----------------------------------------
           OPERATORS
        ------------------------------------------ */
        char next = fgetc(fp);
        if (next != EOF) {
            char op[3] = {ch, next, '\0'};

            if (!strcmp(op, "==") || !strcmp(op, "!=") ||
                !strcmp(op, ">=") || !strcmp(op, "<="))
            { printf("%s : Relational Operator\n", op); continue; }

            if (!strcmp(op, "++") || !strcmp(op, "--"))
            { printf("%s : Arithmetic Operator\n", op); continue; }

            if (!strcmp(op, "&&") || !strcmp(op, "||"))
            { printf("%s : Logical Operator\n", op); continue; }

            if (!strcmp(op, "+=") || !strcmp(op, "-=") ||
                !strcmp(op, "*=") || !strcmp(op, "/="))
            { printf("%s : Assignment Operator\n", op); continue; }

            ungetc(next, fp);
        }

        /* Single-character operators */
        if (strchr("=+-*/%><!&|", ch)) {
            printf("%c : Operator\n", ch);
            continue;
        }

        /* -----------------------------------------
           SPECIAL SYMBOLS & PUNCTUATIONS
        ------------------------------------------ */
        if (ispunct(ch)) {
            printf("%c : Special Symbol\n", ch);
        }
    }

    fclose(fp);
    return 0;
}
