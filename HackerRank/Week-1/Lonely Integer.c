int lonelyinteger(int a_count, int* a) {
    int distinct=0;
    int i;
    for(i=0;i<a_count;i++){
        distinct=distinct^a[i];
    }
    return distinct;

}
