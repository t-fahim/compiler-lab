#include <stdio.h>
#include <ctype.h>
#include <string.h>

int is_keyword(const char *word) {
    char *keywords[] = {
        "int","float","char","double","long","short","void","return",
        "if","else","while","for","break","continue","struct","union"
    };
    int n = sizeof(keywords) / sizeof(keywords[0]);

    for (int i = 0; i < n; i++) {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int is_valid_identifier(const char *word) {
    if (!isalpha(word[0]) && word[0] != '_')
        return 0;

    for (int i = 1; word[i] != '\0'; i++)
        if (!isalnum(word[i]) && word[i] != '_')
            return 0;

    return 1;
}

int main() {
    FILE *fp = fopen("task10.txt", "r");
    if (!fp) {
        printf("Cannot open file.\n");
        return 1;
    }

    char ch;

    while ((ch = fgetc(fp)) != EOF) {

        /* =========================================
           INVALID IDENTIFIERS (start with digit, contain symbols)
        ========================================== */
        if (isalnum(ch) || ch == '_' || ch == '@' || ch == '$' || ch == '#') {

            char word[100];
            int i = 0;
            word[i++] = ch;

            while ((ch = fgetc(fp)) != EOF &&
                   (isalnum(ch) || ch == '_' || ch == '@' || ch == '$' || ch == '#'))
            {
                word[i++] = ch;
            }

            word[i] = '\0';
            ungetc(ch, fp);

            int invalid_char = 0;
            for (int j = 0; word[j]; j++) {
                if (word[j] == '@' || word[j] == '$' || word[j] == '#')
                    invalid_char = 1;
            }

            if (isdigit(word[0]) || invalid_char || !is_valid_identifier(word)) {
                printf("Error: Invalid identifier '%s'\n", word);
            }

            continue;
        }

        /* =========================================
           UNTERMINATED STRING
        ========================================== */
        if (ch == '"') {
            char buffer[200];
            int i = 0;
            buffer[i++] = ch;
            int closed = 0;

            while ((ch = fgetc(fp)) != EOF) {
                if (ch == '"') {
                    closed = 1;
                    buffer[i++] = ch;
                    break;
                }
                if (ch == '\n')
                    break;

                buffer[i++] = ch;
            }

            buffer[i] = '\0';

            if (!closed)
                printf("Error: Unterminated string literal %s\n", buffer);

            continue;
        }

        /* =========================================
           UNCLOSED COMMENTS  /*  comment ...
        ========================================== */
        if (ch == '/') {
            char next = fgetc(fp);

            if (next == '*') {
                int closed = 0;
                char prev = 0;

                while ((ch = fgetc(fp)) != EOF) {
                    if (prev == '*' && ch == '/') {
                        closed = 1;
                        break;
                    }
                    prev = ch;
                }

                if (!closed)
                    printf("Error: Unclosed comment '/*'\n");

                continue;
            }

            ungetc(next, fp);
        }

        /* =========================================
           INVALID STANDALONE CHARACTERS
        ========================================== */
        if (ch == '@' || ch == '$' || ch == '#') {
            printf("Error: Invalid character '%c'\n", ch);
        }
    }

    fclose(fp);
    return 0;
}
