#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pixel {
	int r;
	int g;
	int b;
}pixel;

typedef struct Img {
	char code[3];
	int nc;
	int nl;
	int max;
	pixel **cor;
} Img;

typedef enum Menu {
	Sair,
	Salvar,
	PeB,
 	Rot,
    Amp,
    Red,
    Blur,
    Shar,
	Detec,
	abre_nova
} menu;

void preenche_filtros(Img *img, Img img_temp);

void cria_matriz (Img *img);

void abre_img (Img *img);

void salva_img (Img *img);

void grayscale(Img *img);

void amplia (Img *img, int zoom);

void reduz (Img *img, int zoom);

void rotaciona (Img *img, int opc);

void sharpening(Img *img);

void blurring (Img *img);

void detecta_bordas (Img *img);

void abrir_nova (Img *img);



