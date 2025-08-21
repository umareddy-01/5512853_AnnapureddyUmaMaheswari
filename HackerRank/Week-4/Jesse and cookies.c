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
char** split_string(char*);

int parse_int(char*);

/*
 * Complete the 'cookies' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER k
 *  2. INTEGER_ARRAY A
 */
 typedef struct{
    int* info;
    int s;
    int strength;
 }min_hp;
 
 min_hp* cmh(int strength){
    min_hp* hp=(min_hp*)malloc(sizeof(min_hp));
    hp->info=(int*)malloc(strength*sizeof(int));
    hp->s=0;
    hp->strength=strength;
    return hp;
 }
 
 void swp(int* x,int* y){
    int temporary=*x;
    *x=*y;
    *y=temporary;
    
 }
 
 void mh(min_hp* hp, int index){
    int tiny=index;
    int l=2*index+1;
    int r=2*index+2;
    
    if(l<hp->s && hp->info[l] < hp->info[tiny]){
        tiny=l;
    }
    if(r<hp->s && hp->info[r]<hp->info[tiny]){
        tiny=r;
    }
    if(tiny!=index){
        swp(&hp->info[index], &hp->info[tiny]);
        mh(hp,tiny);
    }
    
    
 }
 
 void ins(min_hp* hp,int value){
    if(hp->s==hp->strength){
        hp->strength*=2;
        hp->info=realloc(hp->info,hp->strength*sizeof(int));
    }
    hp->info[hp->s]=value;
    int i=hp->s;
    hp->s++;
    
    while(i!=0 && hp->info[(i-1)/2]>hp->info[i]){
        swp(&hp->info[i],&hp->info[(i-1)/2]);
        i=(i-1)/2;
    }
 }
 
 int em(min_hp* hp){
    if(hp->s<=0){
        return -1;
    }
    if(hp->s==1){
        hp->s--;
        return hp->info[0];
    }
    int root=hp->info[0];
    hp->info[0]=hp->info[hp->s-1];
    hp->s--;
    mh(hp,0);
    return root;
 }
 
 int gm(min_hp* hp){
    if(hp->s<=0){
        return -1;
    
    }
    return hp->info[0];
 }
 
 

int cookies(int k, int A_count, int* A) {
    min_hp* hp=cmh(A_count);
    int i;
    for(i=0;i<A_count;i++){
        ins(hp,A[i]);
    }
    
    int op=0;
    while(hp->s >1 && gm(hp)<k){
        int f=em(hp);
        int sec=em(hp);
        int nc=f+2*sec;
        ins(hp,nc);
        op++;
    }
    
    if(gm(hp)<k){
        op= -1;
    }
    free(hp->info);
    free(hp);
    return op;
   
    

}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** first_multiple_input = split_string(rtrim(readline()));

    int n = parse_int(*(first_multiple_input + 0));

    int k = parse_int(*(first_multiple_input + 1));

    char** A_temp = split_string(rtrim(readline()));

    int* A = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        int A_item = parse_int(*(A_temp + i));

        *(A + i) = A_item;
    }

    int result = cookies(k, n, A);

    fprintf(fptr, "%d\n", result);

    fclose(fptr);

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

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);

        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
