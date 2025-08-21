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
 * Complete the 'lilysHomework' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY arr as parameter.
 */
 typedef struct{
    int val;
    int idx;
 }ele;
 
 int comp(const void *x,const void *y){
    return((ele*)x)->val-((ele*)y)->val;
    
 }
 int comp_des(const void *x,const void *y){
    return((ele*)y)->val-((ele*)x)->val;
    
 }
 int bs(int* arr,int m,int val){
    int l=0,r=m-1;
    while(l<=r){
        int midddle=l+(r-l)/2;
        if(arr[midddle]==val){
            return midddle;
        }else if(arr[midddle]<val){
            l=midddle+1;
        }else{
            r=midddle-1;
        }
    }
    return -1;
 }
 
 int m_swp(int arr_count,int* arr,int* tar,int is_sc ){
    int *di=(int*)malloc(arr_count*sizeof(int));
    for(int i=0;i<arr_count;i++){
        int position=bs(tar,arr_count,arr[i]);
        if(is_sc){
            di[i]=position;
        }else{
            di[i]=arr_count-1-position;
        }
        
    }
    
    int *vis=(int*)calloc(arr_count,sizeof(int));
    int c=0;
    for(int i=0;i<arr_count;i++){
        if(!vis[i]){
            c++;
            int j=i;
            while(!vis[j]){
                vis[j]=1;
                j=di[j];
                }
        }
    }
  
    free(vis);
    free(di);
    return arr_count-c;
 }

int lilysHomework(int arr_count, int* arr) {
    int* tar=(int*)malloc(arr_count*sizeof(int));
    
    memcpy(tar,arr,arr_count*sizeof(int));
    qsort(tar,arr_count,sizeof(int),comp);
    
    
    
    
    
    int swp_asc=m_swp(arr_count,arr,tar,1);
    
    int swp_des=m_swp(arr_count,arr,tar,0);
    
    free(tar);
    
    return (swp_asc<swp_des)? swp_asc:swp_des;

}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int n = parse_int(ltrim(rtrim(readline())));

    char** arr_temp = split_string(rtrim(readline()));

    int* arr = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        int arr_item = parse_int(*(arr_temp + i));

        *(arr + i) = arr_item;
    }

    int result = lilysHomework(n, arr);

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
