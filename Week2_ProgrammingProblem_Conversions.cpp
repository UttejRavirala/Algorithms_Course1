#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

using namespace std;

unsigned long merge(long arr[], long l, long m, long r)
{
    long i, j, k;
    long n1 = m - l + 1;
    long n2 =  r - m;
	
	//copying two arrays into temp arrays L and R
	//number of split inversions in this merge subproblem are stored in "split" variable and initialized to zero
    long L[n1], R[n2], split=0;
 
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
 
	//merge temp arrays into arr
    i = 0; // index of first subarray
    j = 0; // index of second subarray
    k = l; // index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            split+=n1-i;
            j++;
        }
        k++;
    }
 	
 	//copy the remaining elements of L[]
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
 
 	//copy the remaining elements of R[]
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
    
    return split;
}
 
unsigned long mergeSort(long arr[], long l, long r)
{
    if (l < r)
    {
    	//middle index
        long m = (r+l)/2;
        //number of left inversions, rightt inversions and split inversions are stored in left, right and split variables
        long left, right, split;
 
        // Sort first and second halves
        left=mergeSort(arr, l, m);
        right=mergeSort(arr, m+1, r);
 
        split=merge(arr, l, m, r);
        
        //return the number of inversions in this arr[l,r]
        return left+right+split;
    }
    else{
    	return 0;
	}
}

int main(void){
	
	FILE * fp;
   	fp = fopen ("IntegerArray.txt", "r");
   	if (!fp)
        		return 1;

   	long buff, i=0, ar[100000];
	while(i<100000){
		fscanf(fp, "%ld", &buff);
		ar[i]=buff;
		i++;
	}
	
	cout<<mergeSort(ar, 0, 99999);
	
	return 0;
}
