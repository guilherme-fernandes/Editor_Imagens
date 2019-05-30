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

void rotaciona (Img *img, int opc) {

	int i,j,k;
	Img img_temp;

	img_temp.nl = img->nc;
	img_temp.nc = img->nl;

	cria_matriz (&img_temp);

	if (opc == 1) {
		for (i=0; i<img->nl; i++) {
			for (j=0; j < img->nc; j++) {                                  // Gira 90° para a esquerda (Antihorário) 
				img_temp.cor[img->nc-j-1][i].r = img->cor[i][j].r;
				img_temp.cor[img->nc-j-1][i].g = img->cor[i][j].g;
				img_temp.cor[img->nc-j-1][i].b = img->cor[i][j].b;
			}	
		}
	}

	else if (opc == 2) {
		for (i=0; i<img->nl; i++) {
			for (j=0; j < img->nc; j++) {                                    // Gira 90° para a Direita (Horário)
				img_temp.cor[j][img->nl-i-1].r = img->cor[i][j].r;
				img_temp.cor[j][img->nl-i-1].g = img->cor[i][j].g;
				img_temp.cor[j][img->nl-i-1].b = img->cor[i][j].b;
			}	
		}
	}

	else if (opc == 3) {

		free (img_temp.cor);

		img_temp.nl = img->nl;
		img_temp.nc = img->nc;

		cria_matriz (&img_temp);

		printf("%d\t%d\n", img_temp.nl, img_temp.nc);

		for (i=0; i<img->nl; i++) {												// Gira imagem 180°
			for (j=0; j < img->nc; j++) {
				img_temp.cor[img->nl-i-1][img->nc-j-1].r = img->cor[i][j].r;
				img_temp.cor[img->nl-i-1][img->nc-j-1].g = img->cor[i][j].g;
				img_temp.cor[img->nl-i-1][img->nc-j-1].b = img->cor[i][j].b;
			}	
		}
	}

	else {
		printf("DIREÇÃO INVALIDA\n");
	}

	free (img->cor);

	img->nc = img_temp.nc;
	img->nl = img_temp.nl;

	cria_matriz (img);

	for (i=0; i<img->nl; i++) {
		for (j=0; j < img->nc; j++) {
				img->cor[i][j].r = img_temp.cor[i][j].r;
				img->cor[i][j].g = img_temp.cor[i][j].g;
				img->cor[i][j].b = img_temp.cor[i][j].b;
			}	
		}
	}

void amplia (Img *img, int zoom) {
	int i,j,k,l;
	Img img_temp;

	img_temp.nl = img->nl * zoom;
	img_temp.nc = img->nc * zoom;
	
	cria_matriz (&img_temp);
 
		for (i=0,k=0; i<img->nl,k<img_temp.nl; k++) {
				if (k%zoom == 0  && k!=0) {
					i++;
				}
			for (j=0,l=0;j<img->nc, l<img_temp.nc; l++) {			
					if (l%zoom==0 && l!=0) {
						j++;
					}
					img_temp.cor[k][l].r = img->cor[i][j].r;
					img_temp.cor[k][l].g = img->cor[i][j].g;
					img_temp.cor[k][l].b = img->cor[i][j].b;
			}
		}

	free (img->cor);
	img->nl = img_temp.nl;
	img->nc = img_temp.nc;

	cria_matriz (img);

	for (i=0; i<img->nl; i++) {
		for (j=0; j < img->nc; j++) {
				img->cor[i][j].r = img_temp.cor[i][j].r;
				img->cor[i][j].g = img_temp.cor[i][j].g;
				img->cor[i][j].b = img_temp.cor[i][j].b;
		}	
	}

}

void reduz (Img *img, int zoom) {

	int i, j, k, l,mediar=0, mediag=0, mediab=0;

	Img img_temp;

	img_temp.nl = img->nl / zoom;
	img_temp.nc = img->nc / zoom;
	
	cria_matriz (&img_temp);

	for (i = 0, k = 1; i<img_temp.nl, k<img->nl; i++ ,k+=zoom) {
		for (j=0, l = 1; j<img_temp.nc, l<img->nc; j++, l+=zoom) {
			img_temp.cor[i][j].r = (img->cor[k-1][l-1].r + img->cor[k-1][l].r + img->cor[k][l-1].r + img->cor[k][l].r)/(zoom*zoom);
			img_temp.cor[i][j].g = (img->cor[k-1][l-1].g + img->cor[k-1][l].g + img->cor[k][l-1].g + img->cor[k][l].g)/(zoom*zoom);
			img_temp.cor[i][j].b = (img->cor[k-1][l-1].b + img->cor[k-1][l].b + img->cor[k][l-1].b + img->cor[k][l].b)/(zoom*zoom);	
		}
	}

	free (img->cor);
	img->nl = img_temp.nl;
	img->nc = img_temp.nc;

	cria_matriz (img);

	for (i=0; i<img->nl; i++) {
		for (j=0; j < img->nc; j++) {
				img->cor[i][j].r = img_temp.cor[i][j].r;
				img->cor[i][j].g = img_temp.cor[i][j].g;
				img->cor[i][j].b = img_temp.cor[i][j].b;
		}	
	}
}