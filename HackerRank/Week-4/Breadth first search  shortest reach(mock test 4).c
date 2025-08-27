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
 * Complete the 'bfs' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER m
 *  3. 2D_INTEGER_ARRAY edges
 *  4. INTEGER s
 */

/*
 * To return the integer array from the function, you should:
 *     - Store the size of the array to be returned in the result_count variable
 *     - Allocate the array statically or dynamically
 *
 * For example,
 * int* return_integer_array_using_static_allocation(int* result_count) {
 *     *result_count = 5;
 *
 *     static int a[5] = {1, 2, 3, 4, 5};
 *
 *     return a;
 * }
 *
 * int* return_integer_array_using_dynamic_allocation(int* result_count) {
 *     *result_count = 5;
 *
 *     int *a = malloc(5 * sizeof(int));
 *
 *     for (int i = 0; i < 5; i++) {
 *         *(a + i) = i + 1;
 *     }
 *
 *     return a;
 * }
 *
 */
int* bfs(int n, int m, int edges_rows, int edges_columns, int** edges, int s, int* result_count) {
    int** adjacent=malloc((n+1)*sizeof(int*));
    int* ads=calloc(n+1,sizeof(int));
    int* adc=calloc(n+1,sizeof(int));
    
    int i;
    for(i=0;i<=n;i++){
        adjacent[i]=NULL;
        ads[i]=0;
        adc[i]=0;
    }
    
    for(i=0;i<m;i++){
        int l=edges[i][0];
        int m=edges[i][1];
        if(ads[l]==adc[l]){
            adc[l]=adc[l]==0?2:adc[l]*2;
            adjacent[l]=realloc(adjacent[l],adc[l]*sizeof(int));
        }
        if(ads[m]==adc[m]){
            adc[m]=adc[m]==0?2:adc[m]*2;
            adjacent[m]=realloc(adjacent[m],adc[m]*sizeof(int));
        }
        
        adjacent[l][ads[l]++]=m;
        adjacent[m][ads[m]++]=l;
    }
    int* range=malloc((n+1)*sizeof(int));
    for(i=1;i<=n;i++){
        range[i]=-1;
        
    }
    
    int*que=malloc(n*sizeof(int));
    int f=0,r=0;
    range[s]=0;
    que[r++]=s;
    while(f<r){
        int nd=que[f++];
        for(i=0;i<ads[nd];i++){
            int sur=adjacent[nd][i];
            if(range[sur]==-1){
                range[sur]=range[nd]+6;
                que[r++]=sur;
            }
        }
    }
    *result_count=n-1;
    int* out=malloc((*result_count)*sizeof(int));
    int index=0;
    for(i=1;i<=n;i++){
        if(i==s) continue;
        out[index++]=range[i];
    }
    
    for(i=0;i<=n;i++){
        free(adjacent[i]);
        
    }
    free(adjacent);
    free(ads);
    free(adc);
    free(range);
    free(que);
    
    return out;
    
    

}
int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int q = parse_int(ltrim(rtrim(readline())));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        char** first_multiple_input = split_string(rtrim(readline()));

        int n = parse_int(*(first_multiple_input + 0));

        int m = parse_int(*(first_multiple_input + 1));

        int** edges = malloc(m * sizeof(int*));

        for (int i = 0; i < m; i++) {
            *(edges + i) = malloc(2 * (sizeof(int)));

            char** edges_item_temp = split_string(rtrim(readline()));

            for (int j = 0; j < 2; j++) {
                int edges_item = parse_int(*(edges_item_temp + j));

                *(*(edges + i) + j) = edges_item;
            }
        }

        int s = parse_int(ltrim(rtrim(readline())));

        int result_count;
        int* result = bfs(n, m, m, 2, edges, s, &result_count);

        for (int i = 0; i < result_count; i++) {
            fprintf(fptr, "%d", *(result + i));

            if (i != result_count - 1) {
                fprintf(fptr, " ");
            }
        }

        fprintf(fptr, "\n");
    }

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
