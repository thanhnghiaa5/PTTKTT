#include<stdio.h>
#include<malloc.h>
#include<string.h>
typedef struct{
	int PA, SL;
	char TenDV[30];
	float TL, GT, DG;
}DoVat;
DoVat *ReadFromFile(float *W, int *n){
	FILE *f;
	f = fopen("CaiBalo2.INP", "r");
	fscanf(f, "%f", W);
	DoVat *dsdv;
	dsdv = (DoVat*)malloc(sizeof(DoVat));
	int i = 0;
	while(!feof(f)){
		fscanf(f, "%f%f%d%[^\n]", &dsdv[i].TL, &dsdv[i].GT, &dsdv[i].SL, &dsdv[i].TenDV);
		dsdv[i].DG = dsdv[i].GT / dsdv[i].TL;
		dsdv[i].PA = 0;
		i++;
		dsdv = (DoVat*)realloc(dsdv, sizeof(DoVat)*(i+1));	
	}
	*n = i;
	fclose(f);
	return dsdv;
}
void swap(DoVat *x, DoVat *y){
	DoVat a = *x;
	*x = *y;
	*y = a;
}
void BS(DoVat *dsdv, int n){
	int i, j;
	for(i = 0; i <= n - 2; i++)
		for(j = n - 1; j >= i + 1; j--)
			if(dsdv[j].DG > dsdv[j - 1].DG)
				swap(&dsdv[j], &dsdv[j - 1]);
}
void inds(DoVat *dsdv, int n, float W){
	int i;
	float TongTL = 0.0, TongGT = 0.0;
	printf("|---|----------------------|-----------|-----------|------------|------------|------------|\n");
	printf("|STT|Ten do vat            |T Luong    |Gia tri    | Don gia    | So luong   | Phuog an   |\n");
	printf("|---|----------------------|-----------|-----------|------------|------------|------------|\n");
	for(i = 0; i < n; i++){
		printf("|%2d |%-20s|%-10.2f|%-10.2f|%-10.2f|%7d      |%7d      |\n", i + 1, dsdv[i].TenDV, dsdv[i].TL, dsdv[i].GT, dsdv[i].DG, dsdv[i].SL, dsdv[i].PA);
		TongTL = TongTL + dsdv[i].PA * dsdv[i].TL;
		TongGT = TongGT + dsdv[i].PA * dsdv[i].GT;
	}
	printf("Trong luong cua ba lo: %-9.2f\n", W);
	printf("Tong trong luong: %-9.2f\n", TongTL);
	printf("TongGT: %-9.2f\n", TongGT);
}
void Tao_Nut_Goc(float W, float *V, float *CT, float *GLNTT, float*TGT, float DG_Max){
	*TGT = 0.0;
	*V= W;
	*CT = *V * DG_Max;
	*GLNTT = 0.0;
}
void Cap_Nhat_GLNTT(float TGT, float *GLNTT, int x[], DoVat *dsdv, int n){
	int i;
	if(*GLNTT < TGT){
		*GLNTT = TGT;
		for(i = 0; i < n; i++)
			dsdv[i].PA = x[i];
	}
}
int min(int a, int b){
	return a<b? a:b;
}
void Nhanh_Can(int i, float *TGT, float *CT, float *V, float *GLNTT, int x[], DoVat *dsdv, int n){
	int j, yk;
	yk = min(dsdv[i].SL, *V/dsdv[i].TL);
	for(j = yk; j >= 0; j--){
		*TGT = *TGT + j*dsdv[i].GT;
		*V = *V - j*dsdv[i].TL;
		*CT = *TGT + *V * dsdv[i+1].DG;
		if(*CT > *GLNTT)
			x[i] = j;
			if((i == n-1) || (*V==0))
				Cap_Nhat_GLNTT(*TGT, GLNTT, x, dsdv, n);
			else
				Nhanh_Can(i+1, TGT, CT, V, GLNTT, x, dsdv, n);
	}
	x[i] = 0;
	*TGT = *TGT - j*dsdv[i].GT;
	*V = *V + j*dsdv[i].TL;
}
int main(){
	int n;
	float TGT, CT, V, GLNTT, W;
	DoVat *dsdv;
	int x[n];
	dsdv = ReadFromFile(&W, &n);
	BS(dsdv, n);
	Tao_Nut_Goc(W, &V, &CT, &GLNTT, &TGT, dsdv[0].DG);
	Nhanh_Can(0, &TGT, &CT , &V, &GLNTT, x, dsdv, n);
	inds(dsdv, n, W);
	free(dsdv);
	return 0;
}
