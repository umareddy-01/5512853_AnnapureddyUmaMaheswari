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

/*
 * Complete the 'isValid' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
 */

/*
 * To return the string from the function, you should either do static allocation or dynamic allocation
 *
 * For example,
 * char* return_string_using_static_allocation() {
 *     static char s[] = "static allocation of string";
 *
 *     return s;
 * }
 *
 * char* return_string_using_dynamic_allocation() {
 *     char* s = malloc(100 * sizeof(char));
 *
 *     s = "dynamic allocation of string";
 *
 *     return s;
 * }
 *
 */
char* isValid(char* s) {
    static char y[]="YES";
    static char n[]="NO";
    
    int frequency[26]={0};
    int i;
    for(i=0;s[i]!='\0';i++){
        frequency[s[i]-'a']++;
        
    }
    
    int val[26],c=0;
    for(i=0;i<26;i++){
        if(frequency[i]>0){
            val[c++]=frequency[i];
        }
    }
    
    int minimum=INT_MAX ,maximum=INT_MIN;
    for(i=0;i<c;i++){
        if(val[i]<minimum) minimum=val[i];
        if(val[i]>maximum) maximum=val[i];
        
    }
    
    if(minimum==maximum) return y;
    
    int mc=0, mac=0;
    for(i=0;i<c;i++){
        if(val[i]==minimum)mc++;
        if(val[i]==maximum)mac++;
    }
    
    if(minimum==1 && mc==1 &&(mac+mc==c)) return y;
    
    if((maximum-minimum==1) && mac==1 && (mac+mc==c)) return y;
    
    return n;
    

    
    

}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* s = readline();

    char* result = isValid(s);

    fprintf(fptr, "%s\n", result);

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
