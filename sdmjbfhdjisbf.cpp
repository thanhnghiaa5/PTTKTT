#include<stdio.h>
typedef int keytype;
typedef int othertype;
typedef struct{
	keytype key;
	othertype otherfields;
}recordtype;
void swap(recordtype &x, recordtype &y){
	recordtype temp;
	temp = x;
	x = y;
	y = temp;
}
int FindPivot(recordtype a[], int i, int j){
	keytype b;
	int k;
	k = i + 1;
	b = a[i].key;
	while((k <= j) && a[k].key == b) k++;
	if(k>j) return -1;
	if(a[k].key > b) return k;
	return 1;
}
int Partion(recordtype a[], int i, int j, keytype p){
	int c, d;
	c = i;
	d = j;
	while(c <= d){
		while(a[c].key < p) c++;
		while(a[d].key >= p) d--;
		if(c < d) swap(a[c], a[d]);
	}
	return c;
}
void Qs(recordtype a[], int i, int j){
	keytype p;
	int pindex, k;
	pindex = FindPivot(a, i, j);
	if(pindex != -1){
		p = a[pindex].key;
		k = Partion(a, i, j, p);
		Qs(a, i, k-1);
		Qs(a, k, j);
	}
}
int main(){
	int n, i;
	recordtype a[1000];
	
	FILE *file = fopen("dayso.inp","r");
	fscanf(file, "%d", &n);
	for(i=0; i <= n-1; i++){
		fscanf(file, "%d", &a[i]);
	}
		printf("\n");
	printf("Thuat toan QuickSort\n\n");
	printf("Day so truoc khi sap xep: ");
	for(i = 0; i < n-1; i++){
		printf("%d ",a[i]);
	}
	printf("\n\n");
	Qs(a, 0, n-1);
	printf("Day so sau khi sap xep: ");
	for(i = 0; i <= n-1; i++){
		printf("%d ", a[i]);
	}
	return 0;
}
