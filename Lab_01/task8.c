#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main() {
FILE *fp = NULL;
    fp = fopen("task8.txt", "r");
    if (fp == NULL)
    {
        printf("file not found");
        exit(1);
    }

char ch, next_ch;

while ((ch = fgetc(fp)) != EOF) {
    // Detect string literals
    if (ch == '"') {
        char buffer[200];
        int i = 0;
        buffer[i++] = ch;
        int valid = 0;

        while ((next_ch = fgetc(fp)) != EOF) {
            if (next_ch == '"') {
                valid = 1;
                break;
            } else if (next_ch == '\n') {
                break;
            }
            buffer[i++] = next_ch;
        }
        buffer[i] = '\0';

        if (valid) {
            printf("%s : Valid String Literal\n", buffer);
        } else {
            printf("%s : Unterminated String Literal\n", buffer);
        }
    }
    // Detect character constants
    else if (ch == '\'') {
    char buffer[50];
    int i = 0;
    buffer[i++] = ch;

    next_ch = fgetc(fp);
    if (next_ch == EOF || next_ch == '\n') {
        buffer[i] = '\0';
        printf("%s : Unterminated Character Constant(Invalid)\n", buffer);
        continue;
    }

    buffer[i++] = next_ch;

    char next_next = fgetc(fp);
    if (next_next == '\'') {
        buffer[i++] = next_next;
        buffer[i] = '\0';
        printf("%s : valid Character Constant\n", buffer);
    } else {
        buffer[i++] = next_next;
        // read until end of line or closing quote
        while ((next_ch = fgetc(fp)) != EOF && next_ch != '\'' && next_ch != '\n') {
            buffer[i++] = next_ch;
        }
        if (next_ch == '\'') {
            buffer[i++] = next_ch;
            buffer[i] = '\0';
            printf("%s : Multiple Character Constant(Invalid)\n", buffer);
        } else {
            buffer[i] = '\0';
            printf("%s : Unterminated Character Constant(Invalid)\n", buffer);
        }
    }
}

}

fclose(fp);
return 0;

}
