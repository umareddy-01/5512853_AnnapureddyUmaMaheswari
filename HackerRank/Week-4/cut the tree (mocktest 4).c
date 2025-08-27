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
 * Complete the 'cutTheTree' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY data
 *  2. 2D_INTEGER_ARRAY edges
 */

int cutTheTree(int data_count, int* data, int edges_rows, int edges_columns, int** edges) {
    int m=data_count;
    int i;
    int *d=calloc(m+1,sizeof(int));
    for(i=0;i<edges_rows;i++){
        int l=edges[i][0],m=edges[i][1];
        d[l]++; d[m]++;
    }
    
    int **adjacent=malloc((m+1)*sizeof(int*));
    for(i=1;i<=m;i++) adjacent[i]=malloc(d[i]*sizeof(int));
    int *index=calloc(m+1,sizeof(int));
    for(i=0;i<edges_rows;i++){
        int l=edges[i][0],m=edges[i][1];
        adjacent[l][index[l]++]=m;
        adjacent[m][index[m]++]=l;
    }
    
    long long sum=0;
    for(i=0;i<m;i++) sum+=data[i];
    
    int *par=calloc(m+1,sizeof(int));
    int *stk=malloc(m*sizeof(int));
    int *ord=malloc(m*sizeof(int));
    int up=0, or=0;
    par[1]=0;
    stk[up++]=1;
    while(up){
        int l=stk[--up];
        ord[or++]=l;
        for(i=0;i<d[l];i++){
            int m=adjacent[l][i];
            if(m==par[l]) continue;
            par[m]=l;
            stk[up++]=m;
        }
    }
    long long *s=calloc(m+1,sizeof(long long));
    long long b=LLONG_MAX;
    for(i=or-1;i>=0;i--){
        int l=ord[i];
        long long tot=data[l-1];
        for(int j=0;j<d[l];j++){
            int m=adjacent[l][j];
            if(par[m]==l) tot+=s[m];
            
        }
        s[l]=tot;
        if(l!=1){
            long long dif=llabs(sum-2*tot);
            if(dif<b) b=dif;
        }
    }
    return (int)b;
    
    

}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int n = parse_int(ltrim(rtrim(readline())));

    char** data_temp = split_string(rtrim(readline()));

    int* data = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        int data_item = parse_int(*(data_temp + i));

        *(data + i) = data_item;
    }

    int** edges = malloc((n - 1) * sizeof(int*));

    for (int i = 0; i < n - 1; i++) {
        *(edges + i) = malloc(2 * (sizeof(int)));

        char** edges_item_temp = split_string(rtrim(readline()));

        for (int j = 0; j < 2; j++) {
            int edges_item = parse_int(*(edges_item_temp + j));

            *(*(edges + i) + j) = edges_item;
        }
    }

    int result = cutTheTree(n, data, n - 1, 2, edges);

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
