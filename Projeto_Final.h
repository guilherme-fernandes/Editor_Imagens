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

void cria_matriz (Img *img);

void abre_img (Img *img);

void salva_img (Img *img);

void grayscale(Img *img);

//void amplia (Img *img, int qnt);

//void reduz (Img *img, int qnt);

void rotaciona (Img *img);

/*void sharpening();

void rotaciona ();

void amplia ();

void reduz ();*/