#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct {
    char* info;
    int strength;
    int len;
} stk;

void in_stk(stk*x){
    x->strength=16;
    x->len=0;
    x->info=(char*)malloc(x->strength*sizeof(char));
    
}

void p_stk(stk*x,char ch){
    if(x->len>=x->strength){
        x->strength *=2;
        x->info=(char*)realloc(x->info,x->strength*sizeof(char));
        
    }
    x->info[x->len++]=ch;
}

void pop_stk(stk*x,int m){
    x->len-=m;
    if(x->len<0)x->len=0;
}

char get_stk(stk*x,int m){
    return x->info[m-1];
}

void free_stk(stk*x){
    free(x->info);
}


int main() {
    int L;
    scanf("%d",&L);
    stk present;
    in_stk(&present);
    
    stk* hist=(stk*)malloc(L*sizeof(stk));
    int hist_up=-1;
    char ln[1000005];
    fgets(ln,sizeof(ln),stdin);
    for(int i=0;i<L;i++){
        fgets(ln,sizeof(ln),stdin);
        int p;
        char argu[1000005];
        if(sscanf(ln, "%d %s",&p,argu)==2){
            if(p==1){
                hist_up++;
                in_stk(&hist[hist_up]);
                for(int j=0;j<present.len;j++){
                p_stk(&hist[hist_up],present.info[j]);
                
            }
            int le=strlen(argu);
            for(int j=0;j<le;j++){
                p_stk(&present,argu[j]);
                
            }
            
        }
            else if(p==2){
                int x=atoi(argu);
                hist_up++;
                in_stk(&hist[hist_up]);
                for(int j=0;j<present.len;j++){
                    p_stk(&hist[hist_up],present.info[j]);
                
            }
                pop_stk(&present,x);
        } 
            else if(p==3){
                int x=atoi(argu);
                printf("%c\n",get_stk(&present,x));
        }
    }
        else if(sscanf(ln,"%d",&p)==1 && p==4){
            if(hist_up>=0){
                free_stk(&present);
                present=hist[hist_up];
                hist_up--;
                }
            
            
            
            
            
        
        
    
        }
    }
    free_stk(&present);
    for(int i=0;i<=hist_up;i++){
        free_stk(&hist[i]);
    }
    free(hist);
    


    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    
    return 0;
}
