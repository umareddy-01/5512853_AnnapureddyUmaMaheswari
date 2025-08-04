void miniMaxSum(int arr_count, int* arr) {
    long sum=0;
    int i;
    int minimum_value=arr[0];
    int maximum_value=arr[0];
    long minimum_sum;
    long maximum_sum;
    for(i=0;i<arr_count;i++){
        sum=sum+arr[i];
        if (arr[i]<minimum_value){
            minimum_value=arr[i];
        }
        
        if (arr[i]>maximum_value){
            maximum_value=arr[i];
        }
    }
    minimum_sum=sum-maximum_value;
    maximum_sum=sum-minimum_value;
    printf("%ld %ld\n",minimum_sum,maximum_sum);

}