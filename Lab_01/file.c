#include <stdio.h>
#include <stdlib.h>


int main() {
    
    FILE *fp = NULL;
    char ch;
    char str[10];
    fp = fopen("text.txt","r");
    if(fp==NULL){
        printf("file not found");
        exit(1);
    }
     
    // reading character by character
    // while (!feof(fp))
    // {
    //     ch = fgetc(fp);
    //     printf("%c ",ch);
    // }
    
    //ch = fgetc(fp);
    //printf("%c",ch);

    // reading string by string
    while (!feof(fp))
    {
        fgets(str,9,fp);
        printf("%s@ ",str);
    }
    
    // fgets(str,9,fp);
    // printf("%s",str);
    fclose(fp);


    return 0;
}