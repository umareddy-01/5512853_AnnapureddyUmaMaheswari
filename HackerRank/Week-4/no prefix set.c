#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char* ltrim(char*);
char* rtrim(char*);

int parse_int(char*);

/*
 * Complete the 'noPrefix' function below.
 *
 * The function accepts STRING_ARRAY words as parameter.
 */
 # define A_SIZE 10
 typedef struct tn{
    struct tn *ch[A_SIZE];
    bool ew;
 }tn;
 
 tn* cn(){
    tn *node=(tn*)malloc(sizeof(tn));
    node->ew=false;
    for(int i=0;i<A_SIZE;i++){
        node->ch[i]=NULL;
    }
    return node;
 }
 

void noPrefix(int words_count, char** words) {
    tn *rt=cn();
    for(int i=0;i<words_count;i++){
        char *wd=words[i];
        tn *present=rt;
        int length=strlen(wd);
        bool fp=false;
        for(int j=0;j<length;j++){
            int idx=wd[j]-'a';
            if(present->ch[idx]==NULL){
                present->ch[idx]=cn();
                
            }else{
                if(present->ch[idx]->ew){
                    fp=true;
                }
            }
            present=present->ch[idx];
            if(fp) break;
        }
        if(fp){
            printf("BAD SET\n%s\n",wd);
            return;
        }
        if(present->ew){
            printf("BAD SET\n%s\n",wd);
            return;
        }
        for(int j=0;j<A_SIZE;j++){
            if(present->ch[j]!=NULL){
                printf("BAD SET\n%s\n",wd);
                return;
            }
        }
        present->ew=true;
    }
    printf("GOOD SET\n");

}

int main()
{
    int n = parse_int(ltrim(rtrim(readline())));

    char** words = malloc(n * sizeof(char*));

    for (int i = 0; i < n; i++) {
        char* words_item = readline();

        *(words + i) = words_item;
    }

    noPrefix(n, words);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;

    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!data) {
            data = '\0';

            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);

        if (!data) {
            data = '\0';
        }
    } else {
        data = realloc(data, data_length + 1);

        if (!data) {
            data = '\0';
        } else {
            data[data_length] = '\0';
        }
    }

    return data;
}

char* ltrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    while (*str != '\0' && isspace(*str)) {
        str++;
    }

    return str;
}

char* rtrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    char* end = str + strlen(str) - 1;

    while (end >= str && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
