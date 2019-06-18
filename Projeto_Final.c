#include "Projeto_Final.h"

/* função que cria a matriz dinâmica, que irá alocar
os pixels rgb da imagem. */

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

/* função utilizada para abrir o arquivo da imagem
e passar as informações contidas neste mesmo para7
a struct da Img. Chama a subrotina cria_matriz para 
alocar a matriz dinâmica de pixel. */

void abre_img (Img *img) {
	FILE *arq;
	int i,j,c;

	char nome_arq[50], comentario[100];
	printf("Digite o nome do arquivo que deseja abrir: \n");			
	scanf("%s", nome_arq);												
																		
	arq = fopen(nome_arq, "r");

	if (arq == NULL) {
		printf("Erro na abertura do arquivo\n");
		exit(1);
	}

	char buf[0x1000];

	while (fgets(buf,sizeof(buf), arq)!= NULL) {
		if (buf[0] == '#') continue;

		fscanf (arq,"%s", img->code);
		fscanf (arq,"%d", &img->nc);
		fscanf (arq,"%d", &img->nl);
		fscanf (arq, "%d", &img->max);

		printf("%d %d %d\n", img->nc, img->nl );
	}
	
			cria_matriz (img);


			for (i=0; i < img->nl; i++) {
				for (j=0; j < img->nc; j++) 
				{	
					fscanf (arq, "%d", (&img->cor[i][j].r));
					fscanf (arq, "%d", (&img->cor[i][j].g));
					fscanf (arq, "%d", (&img->cor[i][j].b));
				}
			}		
	fclose (arq);
}

void abrir_nova (Img *img) {

	free (img->cor);

	abre_img (img);
}

/* função utilizada para passar as informações
que foram alteradas (ou não) dentro da struct 
para um novo arquivo ppm.*/

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

void preenche_filtros(Img *img, Img img_temp) {

	int i,j;

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

/* Função que transforma uma imagem escala de cinza
através de combinação linear. No fim, testa se os valores
do pixel são maiores que 255. */

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

/* Subrotina que rotaciona a imagem dada pelo usuário.
Passa como parâmetro a imagem e a opção do sentido que 
a imagem será rotacionada. Entramos com uma imagem temporária
que vai sofrer alterações na largura e na altura, e depois, de
acordo com o sentido que o usuário deseja girar, fará as altera-
ções na posição dos pixels na matriz.
*/

void rotaciona (Img *img, int opc) {									

	int i,j,k;
	Img img_temp;

	img_temp.nl = img->nc;
	img_temp.nc = img->nl;

	cria_matriz (&img_temp);

	if (opc == 1) {														// Gira 90° para a esquerda (Antihorário) 
		for (i=0; i<img->nl; i++) {
			for (j=0; j < img->nc; j++) {                                  
				img_temp.cor[img->nc-j-1][i].r = img->cor[i][j].r;
				img_temp.cor[img->nc-j-1][i].g = img->cor[i][j].g;
				img_temp.cor[img->nc-j-1][i].b = img->cor[i][j].b;
			}	
		}
	}

	else if (opc == 2) {												 // Gira 90° para a Direita (Horário)
		for (i=0; i<img->nl; i++) {
			for (j=0; j < img->nc; j++) {                                 
				img_temp.cor[j][img->nl-i-1].r = img->cor[i][j].r;
				img_temp.cor[j][img->nl-i-1].g = img->cor[i][j].g;
				img_temp.cor[j][img->nl-i-1].b = img->cor[i][j].b;
			}	
		}
	}

	else if (opc == 3) {												// Gira imagem 180°

		free (img_temp.cor);

		img_temp.nl = img->nl;
		img_temp.nc = img->nc;

		cria_matriz (&img_temp);

		printf("%d\t%d\n", img_temp.nl, img_temp.nc);

		for (i=0; i<img->nl; i++) {												
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

	preenche_filtros(img, img_temp);
	}

/*Subrotina que amplia uma imagem dada. Para isso, cada 
pixel da imagem é repetido (zoom*zoom) vezes, fazendo com 
que a imagem fique maior.*/

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

	preenche_filtros(img, img_temp);
}

/*Subrotina que reduz a imagem. Usando a lógica inversa
da subrotina amplia, essa função transforma (zoom*zoom) 
pixels da imagem em um só, reduzindo o img->nl e o img->nc,
diminuindo a imagem.*/

void reduz (Img *img, int zoom) {

	int area = zoom*zoom,k,l,i,j,t,s;
	Img img_temp;
	pixel p = {0,0,0};

	img_temp.nl = img->nl / zoom;
	img_temp.nc = img->nc / zoom;
	
	cria_matriz (&img_temp);

	for (i=0,t=0; i<=img->nl-zoom,t<img_temp.nl; i+=zoom,t++) 
		for (j=0,s=0;i<img->nc-zoom,s<img_temp.nc; j+=zoom, s++, p.r=0, p.g=0, p.b=0) {
			for (k=0; k<zoom; k++) 
				for (l=0;l<zoom;l++)
					p.r += img->cor[i+k][j+l].r,
					p.g += img->cor[i+k][j+l].g,
					p.b += img->cor[i+k][j+l].b;

			img_temp.cor[t][s].r = p.r/area;
			img_temp.cor[t][s].g = p.g/area;
			img_temp.cor[t][s].b = p.b/area;

		}


	preenche_filtros(img, img_temp);

}

void blurring (Img *img) {

	Img img_temp;
	int i,j;

	img_temp.nl = img->nl;
	img_temp.nc = img->nc;

	cria_matriz (&img_temp);

	/*Como as bordas não tem vizinho, não sofre alteração.
	  Portanto, só vai receber a mesma coisa da imagem original.*/

	for (i=0; i<img->nl;i++) {
		img_temp.cor[i][0].r = img->cor[i][0].r;
		img_temp.cor[i][0].g = img->cor[i][0].g;
		img_temp.cor[i][0].b = img->cor[i][0].b;

		img_temp.cor[i][img->nc-1].r = img->cor[i][img->nc-1].r;
		img_temp.cor[i][img->nc-1].g = img->cor[i][img->nc-1].g;
		img_temp.cor[i][img->nc-1].b = img->cor[i][img->nc-1].b;
	}

	for (i=0; i<img->nc; i++) {
		img_temp.cor[0][i].r = img->cor[0][i].r;
		img_temp.cor[0][i].g = img->cor[0][i].g;
		img_temp.cor[0][i].b = img->cor[0][i].b;

		img_temp.cor[img->nl-1][i].r = img->cor[img->nl-1][i].r;
		img_temp.cor[img->nl-1][i].g = img->cor[img->nl-1][i].g;
		img_temp.cor[img->nl-1][i].b = img->cor[img->nl-1][i].b;
	}
 
	/*Para os demais pixels da imagem, pega o valor (RGB)
	dos vizinhos e do próprio pixel, soma e depois divide
	por 9.*/

	for (i=1; i<img->nl-1; i++) {
		for (j=1; j<img->nc-1; j++) {

			img_temp.cor[i][j].r = (img->cor[i-1][j-1].r + img->cor[i-1][j].r + img->cor[i-1][j+1].r + img->cor[i][j-1].r +
			img->cor[i][j].r + img->cor[i][j+1].r + img->cor[i+1][j-1].r + img->cor[i+1][j].r + img->cor[i][j+1].r)/9;

			img_temp.cor[i][j].g = (img->cor[i-1][j-1].g + img->cor[i-1][j].g + img->cor[i-1][j+1].g + img->cor[i][j-1].g +
			img->cor[i][j].g + img->cor[i][j+1].g + img->cor[i+1][j-1].g + img->cor[i+1][j].g + img->cor[i][j+1].g)/9;

			img_temp.cor[i][j].b = (img->cor[i-1][j-1].b + img->cor[i-1][j].b + img->cor[i-1][j+1].b + img->cor[i][j-1].b +
			img->cor[i][j].b + img->cor[i][j+1].b + img->cor[i+1][j-1].b + img->cor[i+1][j].b + img->cor[i][j+1].b)/9;
		}
	}

	preenche_filtros(img, img_temp);
}

/*No efeito de sharpening, utilizado para aumentar
  a clareza da imagem, subtrai-se do pixel (i,j) aumentado
  5x os pixels que estão ao seu lado. 
  | 0 -1  0|
  |-1  5 -1|	
  | 0 -1  0| 
 */

void sharpening (Img *img) {

	Img img_temp;
	int i,j;

	img_temp.nl = img->nl;
	img_temp.nc = img->nc;

	cria_matriz (&img_temp);

	/*Laço começa de 1 e vai até img->nl-1 e img->nc-1
	 para diminuir os quatro laterais.*/

	for (i=1; i<img->nl-1; i++) {
		for (j=1; j<img->nc-1; j++) {
			img_temp.cor[i][j].r = ((5*img->cor[i][j].r) - (img->cor[i][j-1].r + img->cor[i-1][j].r + 
			img->cor[i][j+1].r + img->cor[i+1][j].r));

			img_temp.cor[i][j].g = ((5*img->cor[i][j].g) - (img->cor[i][j-1].g + img->cor[i-1][j].g + 
			img->cor[i][j+1].g + img->cor[i+1][j].g));

			img_temp.cor[i][j].b = ((5*img->cor[i][j].b) - (img->cor[i][j-1].b + img->cor[i-1][j].b + 
			img->cor[i][j+1].b + img->cor[i+1][j].b));

		}
	}

	for (i=0; i<img->nl; i++) {
		for (j=0; j<img->nc; j++) { 
			
			if (img_temp.cor[i][j].r < 0)
				img_temp.cor[i][j].r = 0;
			
			if (img_temp.cor[i][j].g < 0)
				img_temp.cor[i][j].g = 0;
			
			if (img_temp.cor[i][j].b < 0)
				img_temp.cor[i][j].b = 0;
		}
	}

	preenche_filtros(img, img_temp);
}

/*Aplica o filtro de Detecção de bordas a partir da matriz:
					| -1 -1 -1 |
					| -1  8 -1 |
					| -1 -1 -1 |						*/

void detecta_bordas (Img *img) {

	Img img_temp;
	int i,j;

	img_temp.nl = img->nl;
	img_temp.nc = img->nc;

	cria_matriz (&img_temp);

	for (i=1; i<img->nl-1; i++) {
		for (j=1; j<img->nc-1; j++) {

			img_temp.cor[i][j].r = (8*img->cor[i][j].r) - (img->cor[i-1][j-1].r + img->cor[i-1][j].r + img->cor[i-1][j+1].r + img->cor[i][j-1].r +
			img->cor[i][j+1].r + img->cor[i+1][j-1].r + img->cor[i+1][j].r + img->cor[i][j+1].r);

			img_temp.cor[i][j].g = (8*img->cor[i][j].g) - (img->cor[i-1][j-1].g + img->cor[i-1][j].g + img->cor[i-1][j+1].g + img->cor[i][j-1].g +
			img->cor[i][j+1].g + img->cor[i+1][j-1].g + img->cor[i+1][j].g + img->cor[i][j+1].g);

			img_temp.cor[i][j].b = (8*img->cor[i][j].b) - (img->cor[i-1][j-1].b + img->cor[i-1][j].b + img->cor[i-1][j+1].b + img->cor[i][j-1].b +
			img->cor[i][j+1].b + img->cor[i+1][j-1].b + img->cor[i+1][j].b + img->cor[i][j+1].b);
		}
	}

	for (i=0; i<img->nl; i++) {
		for (j=0; j<img->nc; j++) { 
			
			if (img_temp.cor[i][j].r < 0)
				img_temp.cor[i][j].r = 0;
			
			if (img_temp.cor[i][j].g < 0)
				img_temp.cor[i][j].g = 0;
			
			if (img_temp.cor[i][j].b < 0)
				img_temp.cor[i][j].b = 0;
		}
	}

	preenche_filtros(img, img_temp);
}







