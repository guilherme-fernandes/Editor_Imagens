#include "Projeto_Final.h"

void cria_matriz (Img *img) {
	int i;

	img->cor = (pixel**) malloc((img->nl)*sizeof(pixel));

	for (i=0; i<img->nl; i++) {
		img->cor[i] = (pixel*) malloc((img->nc)*sizeof(pixel));
	}

	if (img->cor == NULL) {
		printf("Erro na alocação da memória\n");
		exit (1);
	}
}

void abre_img (Img *img) {
	FILE *arq;
	int i,j;

	char nome_arq[50];
	printf("Digite o nome do arquivo que deseja abrir: \n");
	scanf("%s", nome_arq);

	arq = fopen(nome_arq, "r");

	if (arq == NULL) {
		printf("Erro na abertura do arquivo\n");
		exit(1);
	}

	fscanf (arq,"%s", img->code);
	fscanf (arq,"%d", &img->nc);
	fscanf (arq,"%d", &img->nl);
	fscanf (arq, "%d", &img->max);

	cria_matriz (img);

	for (i=0; i < img->nl; i++) {
		for (j=0; j < img->nc; j++) {	
			fscanf (arq, "%d", (&img->cor[i][j].r));
			fscanf (arq, "%d", (&img->cor[i][j].g));
			fscanf (arq, "%d", (&img->cor[i][j].b));
		}
	}

	fclose (arq);
}

void salva_img (Img *img) {
	int i,j;
	FILE *arq;
	char nomearq [50];

	printf("Digite o nome como sera salvo seu arquivo: \n");
	scanf ("%s", nomearq);

	arq = fopen (nomearq, "w");

	fprintf(arq, "P3\n");
	fprintf(arq, "%d ", img->nc);
	fprintf(arq, "%d\n",img->nl);
	fprintf(arq, "%d\n",img->max);

	for (i=0; i < img->nl; i++) {
		for (j=0; j < img->nc; j++) {
			fprintf (arq, "%d ",(img->cor[i][j].r));
			fprintf (arq, "%d ",(img->cor[i][j].g));
			fprintf (arq, "%d\n",(img->cor[i][j].b));
		}
	}

	fclose (arq);
}

void grayscale (Img *img) {

	int i, j;

	for (i = 0; i<img->nl;i++) {
		for (j = 0; j<img->nc; j++) {
			img->cor[i][j].r = (int)((0.299 * img->cor[i][j].r) + (0.587 * img->cor[i][j].g) + (0.144 * img->cor[i][j].b));
            img->cor[i][j].g = img->cor[i][j].r; 
            img->cor[i][j].b = img->cor[i][j].r; 


			if (img->cor[i][j].r > 255) {
				img->cor[i][j].r = 255;
				img->cor[i][j].g = 255;
				img->cor[i][j].b = 255;
			}
		}
	}
}

void rotaciona (Img *img) {

	int i,j,k;
	Img img_temp;

	img_temp.nl = img->nc;
	img_temp.nc = img->nl;

	cria_matriz (&img_temp);

	for (k=img->nc-1, i=0; i<img->nl, k>=0; i++, k--) {
		for (j=0; j < img->nc; j++) {
			img_temp.cor[j][k] = img->cor[i][j];
		}
	}

	free(img->cor);
	img->cor = img_temp.cor;
	img->nc = img_temp.nc;
	img->nl = img_temp.nl;
}