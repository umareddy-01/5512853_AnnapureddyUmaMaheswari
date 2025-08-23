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
 * Complete the 'bomberMan' function below.
 *
 * The function is expected to return a STRING_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. STRING_ARRAY grid
 */

/*
 * To return the string array from the function, you should:
 *     - Store the size of the array to be returned in the result_count variable
 *     - Allocate the array statically or dynamically
 *
 * For example,
 * char** return_string_array_using_static_allocation(int* result_count) {
 *     *result_count = 5;
 *
 *     static char* a[5] = {"static", "allocation", "of", "string", "array"};
 *
 *     return a;
 * }
 *
 * char** return_string_array_using_dynamic_allocation(int* result_count) {
 *     *result_count = 5;
 *
 *     char** a = malloc(5 * sizeof(char*));
 *
 *     for (int i = 0; i < 5; i++) {
 *         *(a + i) = malloc(20 * sizeof(char));
 *     }
 *
 *     *(a + 0) = "dynamic";
 *     *(a + 1) = "allocation";
 *     *(a + 2) = "of";
 *     *(a + 3) = "string";
 *     *(a + 4) = "array";
 *
 *     return a;
 * }
 *
 */
 
char** bomberMan(int n, int grid_count, char** grid, int* result_count) {
    int l=grid_count;
    int m=strlen(grid[0]);
    
    *result_count=l;
    
    char** out=malloc(l*sizeof(char*));
    for(int i=0;i<l;i++){
        out[i]=malloc((m+1)*sizeof(char));
    }
    
    if(n==1){
        for(int i=0;i<l;i++){
            strcpy(out[i],grid[i]);
            
        }
        return out;
    }
    
    if(n%2==0){
        for(int i=0;i<l;i++){
            for(int j=0;j<m;j++){
                out[i][j]='O';
            }
            out[i][m]='\0';
        }
        return out;
    }
    
    auto void exp(char** first, char** end){
        int dl[4]={1,-1,0,0};
        int dm[4]={0,0,1,-1};
        
        for(int i=0;i<l;i++){
            for(int j=0;j<m;j++){
                end[i][j]='O';
            }
            end[i][m]='\0';
        }
        
        for(int i=0;i<l;i++){
            for(int j=0;j<m;j++){
                if(first[i][j]=='O'){
                    end[i][j]='.';
                    for(int b=0;b<4;b++){
                        int ni=i+dl[b],nj=j+dm[b];
                        if(ni>=0 && ni < l && nj>=0 && nj<m){
                            end[ni][nj]='.';
                        }
                    }
                }
            }
        }
    }
    
    char** gr3=malloc(l*sizeof(char*));
    for(int i=0;i<l;i++) gr3[i]=malloc(m+1);
    exp(grid,gr3);
    
    
    char** gr5=malloc(l*sizeof(char*));
    for(int i=0;i<l;i++) gr5[i]=malloc(m+1);
    exp(gr3,gr5);
    
    if(n%4==3){
        for(int i=0;i<l;i++) strcpy(out[i],gr3[i]);
        
        
    }
    else{
         for(int i=0;i<l;i++) strcpy(out[i],gr5[i]);
        
    }
    return out;
    
    }

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** first_multiple_input = split_string(rtrim(readline()));

    int r = parse_int(*(first_multiple_input + 0));

    int c = parse_int(*(first_multiple_input + 1));

    int n = parse_int(*(first_multiple_input + 2));

    char** grid = malloc(r * sizeof(char*));

    for (int i = 0; i < r; i++) {
        char* grid_item = readline();

        *(grid + i) = grid_item;
    }

    int result_count;
    char** result = bomberMan(n, r, grid, &result_count);

    for (int i = 0; i < result_count; i++) {
        fprintf(fptr, "%s", *(result + i));

        if (i != result_count - 1) {
            fprintf(fptr, "\n");
        }
    }

    fprintf(fptr, "\n");

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
