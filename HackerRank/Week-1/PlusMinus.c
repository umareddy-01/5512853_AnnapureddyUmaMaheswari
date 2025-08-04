void plusMinus(int arr_count, int* arr) {
    int positive_count=0;
    int negative_count=0;
    int zero_count=0;
    int i;
    double total_no_of_elements;
    for(i=0;i<arr_count;i++){
        if(arr[i]>0){
            positive_count++;
            
        }else if(arr[i]<0){
            negative_count++;
        }
        else{
            zero_count++;
        }
    }
    total_no_of_elements=(double)arr_count;
    printf("%.6f\n",positive_count/total_no_of_elements);
    printf("%.6f\n",negative_count/total_no_of_elements);
    printf("%.6f\n",zero_count/total_no_of_elements);



}