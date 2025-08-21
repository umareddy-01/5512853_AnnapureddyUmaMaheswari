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
 * Complete the 'solve' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY arr
 *  2. INTEGER_ARRAY queries
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
 typedef struct{
    int *info;
    int f;
    int r;
    int strength;
    
 }Deq;
 
 Deq* cd(int strength){
    Deq *deq=(Deq*)malloc(sizeof(Deq));
    deq->info=(int*)malloc(strength*sizeof(int));
    deq->f=-1;
    deq->r=-1;
    deq->strength=strength;
    return deq;
 }
 
 void pb(Deq *deq, int val){
    if(deq->f==-1){
        deq->f=0;
        deq->r=0;
        deq->info[deq->r]=val;
    }else{
        deq->r++;
        deq->info[deq->r]=val;
    }
 }
 
 void pf(Deq *deq){
    if(deq->f==deq->r){
        deq->f=-1;
        deq->r=-1;
    }else{
        deq->f++;
    }
 }
 
 void pop(Deq *deq){
    if(deq->f==deq->r){
        deq->f=-1;
        deq->r=-1;
    }else{
        deq->r--;
    }
    
 }
 
 int f(Deq *deq){
    return deq->info[deq->f];
 }
 
 int bck(Deq *deq){
    return deq->info[deq->r];
 }
 
 int emp(Deq *deq){
    return deq->f==-1;
 }
 
 void freedeq(Deq *deq){
    free(deq->info);
    free(deq);
    
 }
 

int* solve(int arr_count, int* arr, int queries_count, int* queries, int* result_count) {
    int *out=(int*)malloc(queries_count*sizeof(int));
    *result_count=queries_count;
    
    for(int index=0;index<queries_count;index++){
        int d=queries[index];
        if(d==1){
            int min=INT_MAX;
            for(int i=0;i<arr_count;i++){
                if(arr[i]<min){
                    min=arr[i];
                }
            }
            out[index]=min;
            continue;
        }
        Deq *deq=cd(arr_count);
        int *max=(int*)malloc((arr_count-d+1)*sizeof(int));
        int inx=0;
        for(int i=0;i<arr_count;i++){
            if(!emp(deq) && f(deq)<=i-d){
                pf(deq);
            }
            while(!emp(deq) && arr[bck(deq)]<=arr[i]){
                pop(deq);
            }
            pb(deq,i);
            if(i>=d-1){
                max[inx++]=arr[f(deq)];
            }
            
            
        }
        int mm=INT_MAX;
        for(int i=0;i<inx;i++){
            if(max[i]<mm){
                mm=max[i];
            }
        }
        out[index]=mm;
        free(max);
        freedeq(deq);
        
    }
    return out;
    

}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** first_multiple_input = split_string(rtrim(readline()));

    int n = parse_int(*(first_multiple_input + 0));

    int q = parse_int(*(first_multiple_input + 1));

    char** arr_temp = split_string(rtrim(readline()));

    int* arr = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        int arr_item = parse_int(*(arr_temp + i));

        *(arr + i) = arr_item;
    }

    int* queries = malloc(q * sizeof(int));

    for (int i = 0; i < q; i++) {
        int queries_item = parse_int(ltrim(rtrim(readline())));

        *(queries + i) = queries_item;
    }

    int result_count;
    int* result = solve(n, arr, q, queries, &result_count);

    for (int i = 0; i < result_count; i++) {
        fprintf(fptr, "%d", *(result + i));

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
