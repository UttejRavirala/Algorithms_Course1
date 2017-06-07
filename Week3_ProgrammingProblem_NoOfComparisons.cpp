#include <iostream>

using namespace std;

int partition(int arr[], int left, int right, int pivot_type){
	
	if(pivot_type==2){
		int tem=arr[left];
		arr[left]=arr[right];
		arr[right]=tem;
	}
	else if(pivot_type==3){
		if((right-left+1)>=3){
			int middle=(left+right)/2;
			int median[3];
			median[0]=arr[left];
			median[1]=arr[middle];
			median[2]=arr[right];
			for (int i = 0; i < 2; i++)
	   		{
     			for (int j = 0; j < 2-i; j++)
     			{
    	    		if (median[j] > median[j+1])
	        		{
        				int temp=median[j];
        				median[j]=median[j+1];
        				median[j+1]=temp;
        			}
    	 		}
	 		}

   			if(median[1]==arr[left]){
			}
			else if(median[1]==arr[middle]){
				int temp=arr[left];
				arr[left]=arr[middle];
				arr[middle]=temp;
			}
			else{
				int temp=arr[left];
				arr[left]=arr[right];
				arr[right]=temp;			
			}		
		}
	}

	int pivot = arr[left];
	int i=left;
	for(int j=left+1; j<=right; j++){
		if(arr[j]<=pivot){
			i++;
			int temp=arr[i];
			arr[i]=arr[j];
			arr[j]=temp;
		}
	}
	
	int tem=arr[i];
	arr[i]=arr[left];
	arr[left]=tem;
	
	return i;
}

int quickSort(int arr[], int l, int r, int pivot_type){
	if(l<r){
		int comparisons;
		int p=partition(arr, l, r, pivot_type);
		comparisons = quickSort(arr, l, p-1, pivot_type) + quickSort(arr, p+1, r, pivot_type) + r - l;
		return comparisons;
	}
	return 0;
}

int main(void){
	
	FILE * fp;
   	fp = fopen ("QuickSort.txt", "r");
   	if (!fp)
        		return 1;

   	int buff, i=0, ar[10000];
	while(i<10000){
		fscanf(fp, "%d", &buff);
		ar[i]=buff;
		i++;
	}
	
	cout<<"Pivot element: first\t"<<quickSort(ar, 0, 9999, 1)<<endl;
	
	i=0;
   	fp = fopen ("QuickSort.txt", "r");
	while(i<10000){
		fscanf(fp, "%d", &buff);
		ar[i]=buff;
		i++;
	}
	cout<<"Pivot element: last\t"<<quickSort(ar, 0, 9999, 2)<<endl;
	
	i=0;
   	fp = fopen ("QuickSort.txt", "r");
	while(i<10000){
		fscanf(fp, "%d", &buff);
		ar[i]=buff;
		i++;
	}
	cout<<"Pivot element: Three pivot rule\t"<<quickSort(ar, 0, 9999, 3)<<endl;

	return 0;
}
