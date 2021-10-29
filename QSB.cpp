#include<stdio.h>

typedef int keytype;
typedef float othertype;
typedef struct{
	keytype key;
	othertype otherfields;
}recordtype;

void Swap(recordtype &x, recordtype &y){
	recordtype temp;
	temp = x;
	x = y;
	y = temp;
}

//Tim chot PindPivot
int FindPivot(recordtype a[], int i, int j){
	keytype firstkey;
	int k;
	k=i+1;
	firstkey = a[i].key;
	while((k<=j) && (a[k].key == firstkey)) k++;
	if(k>j) return -1;
	if(a[k].key>firstkey) return k;
	return i;
}

//Phan hoach Partition
int Partition(recordtype a[], int i, int j, keytype pivot){
	int L,R;
	L = i;
	R = j;
	while(L <= R){
		while(a[L].key < pivot) L++;
		while(a[R].key >= pivot) R--;
		if(L<R) Swap(a[L], a[R]);
	}
	return L; //Tra ve diem phan hoach
}
//sap xep QuickSort
void QuickSort(recordtype a[], int i, int j){
	keytype pivot;
	int pivotindex, k;
	pivotindex = FindPivot(a,i,j);
	if(pivotindex != -1){
		pivot = a[pivotindex].key;
		k = Partition(a,i,j,pivot);
		QuickSort(a,i,k-1);
		QuickSort(a,k,j);
	}
}
//Tim chotB
int FindPivotB(recordtype a[], int i, int j){
	keytype firstkey;
	int k;
	k=i+1;
	firstkey = a[i].key;
	while((k<=j) && (a[k].key == firstkey)) k++;
	if(k>j) return -1;
	if(a[k].key<firstkey) return k;
	return i;
}

//Phan hoach PartitionB
int PartitionB(recordtype a[], int i, int j, keytype pivot){
	int L,R;
	L = i;
	R = j;
	while(L <= R){
		while(a[L].key <= pivot) L++;
		while(a[R].key > pivot) R--;
		if(L<R) Swap(a[L], a[R]);
	}
	return L;
}

//QuickSort bien the
void QuickSortB(recordtype a[], int i, int j){
	keytype pivot;
	int pivotindex, k;
	pivotindex = FindPivotB(a,i,j);
	if(pivotindex != -1){
		pivot = a[pivotindex].key;
		k = PartitionB(a,i,j,pivot);
		QuickSort(a,i,k-1);
		QuickSort(a,k,j);
	}
}



int main(){
	//khai bao
	int n,i;
	recordtype a[100];
	
	//Read File
	FILE *file = fopen("dayso.INP", "r");
	fscanf(file, "%d",&n);
	for(i=0;i<=n-1;i++){
		fscanf(file, "%d",&a[i]);
	}
	
	//OUTPUT
	printf("\n");
	printf("Thuat toan sap xep nhanh B: \n\n");
	printf("Day so truoc khi sap xep: ");
	for(i=0;i<=n-1;i++){
		printf("%d ",a[i]);
	}
	printf("\n\n");
	QuickSortB(a,0,n);
	printf("Day so sau khi da sap xep: ");
	for(i=0;i<=n-1;i++){
		printf("%d ",a[i]);
	}
	printf("\n");
	
}
