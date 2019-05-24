#include "Projeto_Final.h"

int main () {

	int option, deg;
	char dir;
	Img img_in;

	abre_img (&img_in);


	printf("                O que deseja fazer com esta imagem? \n");
	printf("                0 - Sair do Programa\n");
	printf("                1 - Preto e Branco\n");
	printf("                2 - Blurring\n");
	printf("                3 - Sharpening\n");
	printf("                4 - Rotacionar\n");
	printf("                5 - Ampliar\n");
	printf("                6 - Reduzir\n");
	printf("                7 - Salvar Imagem\n");
	scanf ("%d", &option);

	while (option != 0) {
	switch (option)
	{
		case 1 :
		grayscale(&img_in);
		break;

	/*	case 2:
		blurring();
		break;

		case 3:
		sharpening();
		break;*/

		case 4:
		rotaciona(&img_in);
		break;

	/*	case 5:
		amplia();
		break;


		case 6:
		reduz();
		break;*/

		case 7:
		salva_img(&img_in);
		break;

		default :
		printf("Valor Inválido!\n");
		break;
	}

		printf("                O que deseja fazer com esta imagem? \n");
	printf("                0 - Sair do Programa\n");
	printf("                1 - Preto e Branco\n");
	printf("                2 - Blurring\n");
	printf("                3 - Sharpening\n");
	printf("                4 - Rotacionar\n");
	printf("                5 - Ampliar\n");
	printf("                6 - Reduzir\n");
	printf("                7 - Salvar Imagem\n");
	scanf ("%d", &option);

}

	return 0;
}