#include <stdio.h>
#include <malloc.h>
#include <string.h>
typedef struct {
	char TenDV[20];
	float TL, GT, DG;
	int PA, SL;
}
DoVat;
DoVat *ReadFromFile(float *W, int *n){
	FILE *f;
	f = fopen("CaiBalo2.INP", "r");
	fscanf(f, "%f",W); // Xac dinh trong luong Ba lo
	DoVat *dsdv;
	dsdv=(DoVat*)malloc(sizeof(DoVat));
	int i=0;
	while (!feof(f)){
		fscanf(f, "%f%f%d%[^\n]",&dsdv[i].TL,&dsdv[i].GT,&dsdv[i].SL,&dsdv[i].TenDV);
		dsdv[i].DG=dsdv[i].GT/dsdv[i].TL;
		dsdv[i].PA=0;
		i++;
		dsdv=(DoVat*)realloc(dsdv, sizeof(DoVat)*(i+1));
	}
	*n=i;
	fclose(f);
	return dsdv;
}
void swap(DoVat *x, DoVat *y){
	DoVat t;
	t = *x;
	*x = *y;
	*y = t;
}
void BS(DoVat *dsdv, int n){
	int i, j;
	for(i = 0; i <= n - 2; i++)
		for(j = n - 1; j >= i + 1; j--){
			if(dsdv[j].DG > dsdv[j - 1].DG)
				swap(&dsdv[j], &dsdv[j-1]);
		}
}
void inds(DoVat *dsdv, int n, float W){
	int i;
	float TongTL=0.0, TongGT=0.0;
	printf("\nPhuong an Cai Ba lo 2 dung thuat toan THAM AN nhu sau:\n");
	printf("|---|-------------------|---------|---------|---------|-----------|-----------|\n");
	printf("|STT|       Ten Do Vat  | T Luong | Gia Tri | Don Gia | So Luong  | Phuong an |\n");
	printf("|---|-------------------|---------|---------|---------|-----------|-----------|\n");
	for(i=0;i<n;i++){
	printf("|%2d |%-19s|%9.2f|%9.2f|%9.2f|%6d     |%5d      |\n",i+1,dsdv[i].TenDV,dsdv[i].TL,dsdv[i].GT,dsdv[i].DG,dsdv[i].SL,dsdv[i].PA);
	TongTL=TongTL+dsdv[i].PA * dsdv[i].TL;
	TongGT=TongGT+dsdv[i].PA * dsdv[i].GT;
	}
	printf("|---|-------------------|---------|---------|---------|-----------|-----------|\n");
	printf("Trong luong cua ba lo = %-9.2f\n",W);
	printf("Tong trong luong = %-9.2f\n",TongTL);
	printf("Tong gia tri = %-9.2f\n",TongGT);
	printf("x = (");
	for(i=0;i<n;i++){
	printf("%d",dsdv[i].PA);
		if(i<n-1) printf(",");
	}
	printf(")");
}
void Greedy(DoVat *dsdv,int n, float W){
	int i;
	for(i=0;i<n;i++){
	dsdv[i].PA = (W/dsdv[i].TL);
	if(dsdv[i].PA > dsdv[i].SL)
		dsdv[i].PA = dsdv[i].SL;
		W = W-dsdv[i].PA * dsdv[i].TL;
	}
}
int main(){
	int n;
	float w;
	DoVat *dsdv;
	dsdv = ReadFromFile(&w, &n);
	BS(dsdv, n);
	Greedy(dsdv, n, w);
	inds(dsdv, n, w);
	free(dsdv);
	return 0;
}
