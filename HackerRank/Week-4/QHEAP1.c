#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAX_QUREY 100000

typedef struct min_heap{
    long long *a;
    int strength;
    int s;
}min_heap;

min_heap* crh(int strength){
    min_heap *hp=(min_heap*)malloc(sizeof(min_heap));
    hp->strength=strength;
    hp->s=0;
    hp->a=(long long*)malloc(strength*sizeof(long long));
    return hp;
    
}

void swp(long long *x,long long *y){
    long long temporary=*x;
    *x=*y;
    *y=temporary;
}

void hup(min_heap *hp, int index){
    int pt=(index-1)/2;
    while(index>0 && hp->a[index]<hp->a[pt]){
        swp(&hp->a[index], &hp->a[pt]);
        index=pt;
        pt=(index-1)/2;
    }
    
}

void psh(min_heap *hp,long long val){
    if(hp->s==hp->strength){
        return;
    }
    hp->a[hp->s]=val;
    hp->s++;
    hup(hp,hp->s-1);
}

void hd(min_heap *hp,int index){
    int l=2*index+1;
    int r=2*index+2;
    int tiny=index;
    
    if(l<hp->s && hp->a[l] < hp->a[tiny]){
        tiny=l;
    }
    if(r<hp->s && hp->a[r]<hp->a[tiny]){
        tiny=r;
    }
    if(tiny!=index){
        swp(&hp->a[index],&hp->a[tiny]);
        hd(hp,tiny);
    }
}

long long pop(min_heap *hp){
    if(hp->s==0){
        return -1;
    }
    long long root=hp->a[0];
    hp->a[0]=hp->a[hp->s-1];
    hp->s--;
    hd(hp,0);
    return root;
}

long long up(min_heap *hp){
    if(hp->s==0){
        return -1;
    }
    return hp->a[0];
}
int main() {
    
    int G,i;
    scanf("%d",&G);
    min_heap *mh=crh(MAX_QUREY);
    min_heap *dh=crh(MAX_QUREY);
    
    for(i=0;i<G;i++){
        int out;
        scanf("%d",&out);
        
        if(out==1){
            long long k;
            scanf("%lld",&k);
            psh(mh,k);
            
        }else if(out==2){
            long long k;
            scanf("%lld",&k);
            psh(dh,k);
            
        }else if(out==3){
            while(dh->s>0 && up(mh)==up(dh)){
                pop(mh);
                pop(dh);
            }
            printf("%lld\n",up(mh));
        }
    }
    free(mh->a);
    free(mh);
    free(dh->a);
    free(dh);
    


    /* Enter your code here. Read input from STDIN. Print output to STDOUT */    
    return 0;
}
